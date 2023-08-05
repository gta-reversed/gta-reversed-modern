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
    const auto out = reinterpret_cast<int16*>(flacDecoder->GetWriteBuffer());

    if (!out)
        return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;

    const auto bps = flacDecoder->GetMetadata().bps;
    assert(bps <= 32);

    const auto ConvertSample = [bps](int32 sample) -> int16 {
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
        out[2u * i + 0u] = ConvertSample(buffer[0][i]); // left
        out[2u * i + 1u] = ConvertSample(buffer[1][i]); // right
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

bool CAEFlacDecoder::InitLibrary() {
    // Test stream decoder.
    if (const auto d = FLAC__stream_decoder_new(); d) {
        FLAC__stream_decoder_delete(d);
        return true;
    }
    return false;
}

bool CAEFlacDecoder::Initialise() {
    m_FlacStreamDecoder = FLAC__stream_decoder_new();
    if (!m_FlacStreamDecoder) {
        NOTSA_LOG_WARN("FLAC__stream_decoder_new failed.");
        return false;
    }
    
    const auto s = FLAC__stream_decoder_init_stream(
        m_FlacStreamDecoder,
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

    if (s != FLAC__STREAM_DECODER_INIT_STATUS_OK) {
        NOTSA_LOG_WARN("FLAC__stream_decoder_init_FILE failed.");
        FLAC__stream_decoder_delete(std::exchange(m_FlacStreamDecoder, nullptr));
        return false;
    }

    // Decode one stream just for checking metadata.
    FLAC__stream_decoder_process_until_end_of_metadata(m_FlacStreamDecoder);
    DEV_LOG("FLAC metadata:\nTotal samples: {}\nSample rate: {}\nChannels: {}\nBits per second: {}\n", m_metadata.totalSamples, m_metadata.sampleRate, m_metadata.channels,
            m_metadata.bps);

    // Seek back after a dry run.
    FLAC__stream_decoder_seek_absolute(m_FlacStreamDecoder, 0u);

    if (m_metadata.channels != 2) {
        NOTSA_LOG_WARN("FLAC decoder: Found non-stereo audio, skipping...");
        FLAC__stream_decoder_delete(std::exchange(m_FlacStreamDecoder, nullptr));
        return false;
    }

    /*
    if (m_metadata.bps != 16) {
        NOTSA_LOG_WARN("FLAC decoder: Found != 16 BPS audio, skipping...");
        FLAC__stream_decoder_delete(std::exchange(m_FlacStreamDecoder, nullptr));
        return false;
    }
    */

    m_bInitialized = true;
    return true;
}

CAEFlacDecoder::~CAEFlacDecoder() {
    if (m_FlacStreamDecoder)
        FLAC__stream_decoder_delete(std::exchange(m_FlacStreamDecoder, nullptr));
}

size_t CAEFlacDecoder::FillBuffer(void* dest, size_t size) {
    if (!m_bInitialized || !m_metadata.channels || size == 0)
        return 0u;

    m_CurrentWriteBuffer = reinterpret_cast<uint8*>(dest);

    size_t totalRead = 0;
    uint64 initialPos{};
    FLAC__stream_decoder_get_decode_position(m_FlacStreamDecoder, &initialPos);

    while (totalRead < size) {
        const auto result = FLAC__stream_decoder_process_single(m_FlacStreamDecoder);

        if (!result) {
            NOTSA_LOG_ERR("FLAC__stream_decoder_process_single returned error!");
            return totalRead;
        }

        uint64 newPos{};
        FLAC__stream_decoder_get_decode_position(m_FlacStreamDecoder, &newPos);

        assert(newPos > initialPos);
        const auto dist = newPos - initialPos;

        m_CurrentWriteBuffer += dist;
        totalRead += static_cast<size_t>(dist);
    }
    m_CurrentWriteBuffer = nullptr;

    return totalRead;
}

long CAEFlacDecoder::GetStreamLengthMs() {
    // this is correct... right?
    if (!m_bInitialized || !m_metadata.totalSamples || !m_metadata.sampleRate)
        return 0;

    return static_cast<long>((float)(m_metadata.totalSamples) / (float)(m_metadata.sampleRate) * 1000.0f);
}

long CAEFlacDecoder::GetStreamPlayTimeMs() {
    // this is correct... right?
    if (!m_bInitialized || !m_metadata.sampleRate)
        return 0;

    FLAC__uint64 position{};
    FLAC__stream_decoder_get_decode_position(m_FlacStreamDecoder, &position);

    return static_cast<long>((float)(position) / (float)(m_metadata.sampleRate) * 1000.0f);
}

void CAEFlacDecoder::SetCursor(unsigned long pos) {
    if (!m_bInitialized || !m_metadata.sampleRate)
        return;

    // pos(in ms) = pos(in samples) / sample_rate
    // <=> 1 / pos(in samples) = pos(in ms) / sample_rate
    // <=> pos(in samples) = sample_rate / pos(in ms)
    const auto absolutePos = m_metadata.sampleRate / (pos * 1000);

    FLAC__stream_decoder_seek_absolute(m_FlacStreamDecoder, absolutePos);
}

int32 CAEFlacDecoder::GetSampleRate() {
    if (!m_bInitialized || !m_metadata.sampleRate)
        return -1;

    if (m_metadata.sampleRate > (uint32)std::numeric_limits<int32>::max()) {
        NOTSA_LOG_WARN("Unsigned sample rate (={}) is casted to signed int, this will surely brake something...", m_metadata.sampleRate);
    }

    return static_cast<int32>(m_metadata.sampleRate);
}

int32 CAEFlacDecoder::GetStreamID() {
    return m_dataStream->m_nTrackId;
}
#endif
