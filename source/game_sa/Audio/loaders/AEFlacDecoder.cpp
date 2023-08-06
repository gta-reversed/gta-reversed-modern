#include "StdInc.h" // TODO: Remove

#ifdef USERTRACK_FLAC_SUPPORT

#include "AEFlacDecoder.h"
#include "FLAC/all.h"

FLAC__StreamDecoderReadStatus read_callback(const FLAC__StreamDecoder* decoder, FLAC__byte buffer[],
    size_t* bytes, void* client_data)
{
    if (!client_data || *bytes <= 0)
        return FLAC__STREAM_DECODER_READ_STATUS_ABORT;

    auto* dataStream = reinterpret_cast<CAEFlacDecoder*>(client_data)->GetDataStream();
    *bytes = dataStream->FillBuffer(buffer, *bytes);

    if (dataStream->GetCurrentPosition() >= dataStream->m_nLength || *bytes == 0)
        return FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM;

    return FLAC__STREAM_DECODER_READ_STATUS_CONTINUE;
}

FLAC__StreamDecoderSeekStatus seek_callback(const FLAC__StreamDecoder* decoder, FLAC__uint64 absolute_byte_offset,
    void* client_data)
{
    if (!client_data)
        return FLAC__STREAM_DECODER_SEEK_STATUS_ERROR;

    auto* dataStream = reinterpret_cast<CAEFlacDecoder*>(client_data)->GetDataStream();
    if (dataStream->Seek(static_cast<long>(absolute_byte_offset), SEEK_SET) < 0)
        return FLAC__STREAM_DECODER_SEEK_STATUS_ERROR;

    return FLAC__STREAM_DECODER_SEEK_STATUS_OK;
}

FLAC__StreamDecoderTellStatus tell_callback(const FLAC__StreamDecoder* decoder, FLAC__uint64* absolute_byte_offset,
    void* client_data)
{
    if (!client_data)
        return FLAC__STREAM_DECODER_TELL_STATUS_ERROR;

    auto* dataStream = reinterpret_cast<CAEFlacDecoder*>(client_data)->GetDataStream();
    *absolute_byte_offset = dataStream->GetCurrentPosition(); // this can't fail unlike tell.
    return FLAC__STREAM_DECODER_TELL_STATUS_OK;
}

FLAC__StreamDecoderLengthStatus length_callback(const FLAC__StreamDecoder* decoder, FLAC__uint64* stream_length,
    void* client_data)
{
    if (!client_data)
        return FLAC__STREAM_DECODER_LENGTH_STATUS_ERROR;

    auto* dataStream = reinterpret_cast<CAEFlacDecoder*>(client_data)->GetDataStream();
    STATSTG stat{};
    if (FAILED(dataStream->Stat(&stat, STATFLAG_NONAME)))
        return FLAC__STREAM_DECODER_LENGTH_STATUS_ERROR;

    *stream_length = static_cast<uint64>(stat.cbSize.LowPart);
    return FLAC__STREAM_DECODER_LENGTH_STATUS_OK;
}

FLAC__bool eof_callback(const FLAC__StreamDecoder* decoder, void* client_data) {
    if (!client_data)
        return true;

    auto* dataStream = reinterpret_cast<CAEFlacDecoder*>(client_data)->GetDataStream();
    return feof(dataStream->m_pFileHandle);
}

FLAC__StreamDecoderWriteStatus write_callback(const FLAC__StreamDecoder* decoder, const FLAC__Frame* frame,
    const FLAC__int32* const buffer[], void* client_data)
{
    if (!client_data)
        return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;

    auto* flacDecoder = reinterpret_cast<CAEFlacDecoder*>(client_data);

    const auto& metadata = flacDecoder->GetMetadata();
    assert(metadata.bps <= 32);

    if (metadata.totalSamples == 0) {
        NOTSA_LOG_ERR("FLAC decoder error: STREAMINFO doesn't have 'total_samples' info.");
        return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
    }

    const auto totalSize = metadata.totalSamples * metadata.channels * (metadata.bps / 8);

    if (frame->header.number.sample_number == 0) {
        const auto fname_static = std::tmpnam(nullptr);
        if (!fname_static) {
            NOTSA_LOG_ERR("FLAC decoder error: Couldn't create a temporary file to decode FLAC into WAV.");
            return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
        }
        char* fname = new char[strlen(fname_static) + 1];
        strcpy(fname, fname_static);

        flacDecoder->AssignWaveFile(fopen(fname, "wb+"), fname, (uint32)totalSize + 44);
    }

    const auto wavFile = flacDecoder->GetWaveFile();

    if (!wavFile)
        return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;

    const auto WriteIntToFile = [wavFile](auto value, size_t size) {
        assert(fwrite(&value, 1, size, wavFile) == size);
    };
    
    if (frame->header.number.sample_number == 0) {
        assert(fwrite("RIFF", 1, 4, wavFile) == 4);
        WriteIntToFile(totalSize + 36, sizeof(uint32));
        assert(fwrite("WAVEfmt ", 1, 8, wavFile) == 8);
        WriteIntToFile(16, sizeof(uint32));
        WriteIntToFile(1, sizeof(uint16));
        WriteIntToFile(metadata.channels, sizeof(uint16));
        WriteIntToFile(metadata.sampleRate, sizeof(uint32));
        WriteIntToFile(metadata.sampleRate * metadata.channels * (metadata.bps / 8), sizeof(uint32));
        WriteIntToFile(metadata.channels * (metadata.bps / 8), sizeof(uint16));
        WriteIntToFile(16 /* metadata.bps */, sizeof(uint16));
        assert(fwrite("data", 1, 4, wavFile) == 4);
        WriteIntToFile(totalSize, sizeof(uint32));
    }

    const auto ConvertSample = [bps = metadata.bps](int32 sample) -> int16 {
        if (bps == 16) {
            return static_cast<int16>(sample);
        } else {
            // We can't use floats here to (de-)normalize because floats lose integer precision for
            // n such that n > 2^24.
            // Doubles lose after n > 2^53, beyond our needs.
            const auto normalized = (double)sample / (double)(2ull << (bps - 2u));

            return static_cast<int16>(normalized * (double)(2ull << (16u - 2u)));
        }
    };

    for (auto i = 0u; i < frame->header.blocksize; i++) {
        WriteIntToFile(ConvertSample(buffer[0][i]), sizeof(int16)); // left/mono

        if (metadata.channels == 2)
            WriteIntToFile(ConvertSample(buffer[1][i]), sizeof(int16)); // right
        else
            WriteIntToFile(ConvertSample(buffer[0][i]), sizeof(int16)); // mono
    }

    return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}

void metadata_callback(const FLAC__StreamDecoder* decoder, const FLAC__StreamMetadata* metadata,
    void* client_data)
{
    if (!client_data || metadata->type != FLAC__METADATA_TYPE_STREAMINFO)
        return;

    auto* flacDecoder = reinterpret_cast<CAEFlacDecoder*>(client_data);
    auto& decoderMetadata = flacDecoder->GetMetadata();

    decoderMetadata.totalSamples = metadata->data.stream_info.total_samples;
    decoderMetadata.sampleRate = metadata->data.stream_info.sample_rate;
    decoderMetadata.channels = metadata->data.stream_info.channels;
    decoderMetadata.bps = metadata->data.stream_info.bits_per_sample;

    NOTSA_LOG_DEBUG(
        "FLAC metadata:\nTotal samples: {}\nSample rate: {} Hz\nChannels: {}\nBits per sample: {} (will be converted to 16)\n",
        decoderMetadata.totalSamples,
        decoderMetadata.sampleRate,
        decoderMetadata.channels,
        decoderMetadata.bps
    );
}

void error_callback(const FLAC__StreamDecoder *decoder, FLAC__StreamDecoderErrorStatus status,
    void *client_data)
{
    if (!client_data)
        return;

    auto* flacDecoder = reinterpret_cast<CAEFlacDecoder*>(client_data);
    flacDecoder->GetMetadata() = {};

    NOTSA_LOG_ERR("FLAC Stream decoder error: {}\n", FLAC__StreamDecoderErrorStatusString[status]);
}

CAEFlacDecoder::~CAEFlacDecoder() {
    if (!m_WaveFileName.empty()) {
        m_dataStream->Close();

        std::error_code ec;
        std::filesystem::remove(m_WaveFileName, ec);
        if (ec != std::error_code{}) {
            NOTSA_LOG_TRACE("Couldn't remove temporary FLAC->WAV file '{}'. (msg={}, val={})", m_WaveFileName, ec.message(), ec.value());
        }
    }
}

bool CAEFlacDecoder::InitLibrary() {
    // Test stream decoder.
    if (const auto d = FLAC__stream_decoder_new(); d) {
        FLAC__stream_decoder_delete(d);
        return true;
    }
    return false;
}

bool CAEFlacDecoder::Initialise() {
    const auto decoder = FLAC__stream_decoder_new();
    if (!decoder) {
        NOTSA_LOG_WARN("FLAC__stream_decoder_new failed.");
        return false;
    }
    
    const auto initStatus = FLAC__stream_decoder_init_stream(
        decoder,
        read_callback,
        seek_callback,
        tell_callback,
        length_callback,
        eof_callback,
        write_callback,
        metadata_callback,
        error_callback,
        this
    );

    if (initStatus != FLAC__STREAM_DECODER_INIT_STATUS_OK) {
        NOTSA_LOG_WARN("FLAC__stream_decoder_init_FILE failed.");
        FLAC__stream_decoder_delete(decoder);
        return false;
    }

    const auto decodeRes = FLAC__stream_decoder_process_until_end_of_stream(decoder);

    NOTSA_LOG_TRACE("Decoding result: {}", decodeRes ? "Successful" : "Failed");
    if (!decodeRes)
        return false;

    CFileMgr::CloseFile(m_WaveFile);
    const auto trackId = m_dataStream->m_nTrackId;

    if (!m_WaveFileNameHeap)
        return false;

    m_WaveFileName = m_WaveFileNameHeap;

    NOTSA_LOG_TRACE("Loading temporary FLAC->WAV file '{}'", m_WaveFileName);

    delete m_dataStream;
    m_dataStream = new CAEDataStream(trackId, m_WaveFileNameHeap, 0, m_WaveFileLength, false);

    return m_dataStream->Initialise() && CAEWaveDecoder::Initialise();
}
#endif
