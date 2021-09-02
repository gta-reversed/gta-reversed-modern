#include "StdInc.h" // TODO: Remove

#include <cmath>
#include <cstdio>

#include "CAEWaveDecoder.h"

// 0x503250
CAEWaveDecoder::CAEWaveDecoder(CAEDataStream* dataStream) : CAEStreamingDecoder(dataStream), m_bInitialized(false), _dataStreamCopy(dataStream) {

}

CAEWaveDecoder::~CAEWaveDecoder() {}

// 0x5032b0
bool CAEWaveDecoder::Initialise() {
    // RIFF<size>WAVEfmt<space><WAVEFORMAT><WORD>
    constexpr size_t HEADER_READ_SIZE = 36;
    size_t           readed = m_dataStream->FillBuffer(fileHeaderArray, HEADER_READ_SIZE);

    if (readed == HEADER_READ_SIZE && bitsPerSample == 16 && (channelCount == 1 || channelCount == 2)) {
        // Look for "data" tag
        char   tag[4] = {0, 0, 0, 0};
        uint32 size;

        while (true) {
            if (m_dataStream->FillBuffer(tag, sizeof(tag)) != sizeof(tag))
                // EOF
                return false;
            if (m_dataStream->FillBuffer(&size, sizeof(uint32)) != sizeof(uint32))
                return false;

            if (memcmp(tag, "data", sizeof(tag)) == 0)
                break;

            m_dataStream->Seek(size, SEEK_CUR);
        }

        dataPosition = m_dataStream->GetCurrentPosition();
        dataChunkSize = size;
        m_bInitialized = true;

        if (GetStreamLengthMs() < 7000)
            m_bInitialized = false;
    }

    return m_bInitialized;
}

// 0x5032a0
size_t CAEWaveDecoder::FillBuffer(void* dest, size_t size) {
    switch (channelCount) {
    case 1: {
        // Read half of it
        size_t        readed = m_dataStream->FillBuffer(dest, size / 2);
        int16* byteStream = reinterpret_cast<int16*>(dest);

        // Duplicate channel data
        for (int32 i = static_cast<int32>(readed / sizeof(int16)) - 1; i >= 0; i--)
            byteStream[i * 2] = byteStream[i * 2 + 1] = byteStream[i];

        return readed * 2;
    }
    case 2:
        // Use fast path
        return m_dataStream->FillBuffer(dest, size);
    default:
        return 0;
    }
}

// 0x503310
long CAEWaveDecoder::GetStreamLengthMs() {
    if (m_bInitialized) {
        uint32 samples = dataChunkSize / blockAlign;
        // More precise way would be involving using GCD
        return long((float)samples * 1000.0f / (float)sampleRate);
    }

    return -1;
}

long CAEWaveDecoder::GetStreamPlayTimeMs() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((long(__thiscall*)(CAEWaveDecoder*))0x503360)(this);
#else
    if (m_bInitialized) {
        uint32 posByte = m_dataStream->GetCurrentPosition() - dataPosition;
        uint32 posSamples = posByte / blockAlign;
        // More precise way would be involving using GCD
        return long((float)posSamples * 1000.0f / (float)sampleRate);
    }

    return -1;
#endif
}

void CAEWaveDecoder::SetCursor(unsigned long pos) {
#ifdef USE_DEFAULT_FUNCTIONS
    using SeekFunc = void(__thiscall*)(CAEWaveDecoder*, unsigned long);
    ((SeekFunc)0x5033c0)(this, pos);
#else
    if (m_bInitialized) {
        // The calculation is exactly in this order!
        uint32 posByte = pos * sampleRate / 1000 * blockAlign;
        m_dataStream->Seek(static_cast<long>(posByte + dataPosition), SEEK_SET);
    }
#endif
}

int32 CAEWaveDecoder::GetSampleRate() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((int32(__thiscall*)(CAEWaveDecoder*))0x503300)(this);
#else
    return m_bInitialized ? static_cast<int32>(sampleRate) : -1;
#endif
}

int32 CAEWaveDecoder::GetStreamID() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((int32(__thiscall*)(CAEWaveDecoder*))0x503280)(this);
#else
    return m_dataStream->m_nTrackId;
#endif
}

CAEWaveDecoder* CAEWaveDecoder::Constructor(CAEDataStream* dataStream) {
    this->CAEWaveDecoder::CAEWaveDecoder(dataStream);
    return this;
}

void CAEWaveDecoder::Destructor() {
    this->CAEWaveDecoder::~CAEWaveDecoder();
}

void CAEWaveDecoder::InjectHooks() {
#ifndef USE_DEFAULT_FUNCTIONS
    ReversibleHooks::Install("CAEWaveDecoder", "CAEWaveDecoder", 0x503250, &CAEWaveDecoder::Constructor);
    ReversibleHooks::Install("CAEWaveDecoder", "~CAEWaveDecoder", 0x503290, &CAEWaveDecoder::Destructor);
    ReversibleHooks::Install("CAEWaveDecoder", "Initialise", 0x5032b0, &CAEWaveDecoder::Initialise);
    ReversibleHooks::Install("CAEWaveDecoder", "FillBuffer", 0x502470, &CAEWaveDecoder::FillBuffer);
    ReversibleHooks::Install("CAEWaveDecoder", "GetStreamLengthMs", 0x503310, &CAEWaveDecoder::GetStreamLengthMs);
    ReversibleHooks::Install("CAEWaveDecoder", "GetStreamPlayTimeMs", 0x503360, &CAEWaveDecoder::GetStreamPlayTimeMs);
    ReversibleHooks::Install("CAEWaveDecoder", "SetCursor", 0x5033c0, &CAEWaveDecoder::SetCursor);
    ReversibleHooks::Install("CAEWaveDecoder", "GetSampleRate", 0x503300, &CAEWaveDecoder::GetSampleRate);
    ReversibleHooks::Install("CAEWaveDecoder", "GetStreamID", 0x503280, &CAEWaveDecoder::GetStreamID);
#endif
}
