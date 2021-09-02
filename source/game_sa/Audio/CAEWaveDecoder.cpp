#include "StdInc.h" // TODO: Remove

#include <cmath>
#include <cstdio>

#include "CAEWaveDecoder.h"

CAEWaveDecoder::CAEWaveDecoder(CAEDataStream* dataStream)
: CAEStreamingDecoder(dataStream)
, initialized(false)
, _dataStreamCopy(dataStream)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using Constructor = void(__thiscall *)(CAEWaveDecoder*, CAEDataStream*);
    ((Constructor) 0x503250)(this, dataStream);
#endif
}

CAEWaveDecoder::~CAEWaveDecoder()
{
}

bool CAEWaveDecoder::Initialise()
{
#ifdef USE_DEFAULT_FUNCTIONS
    using InitFunc = bool(__thiscall *)(CAEWaveDecoder*);
    return ((InitFunc) 0x5032b0)(this);
#else
    // RIFF<size>WAVEfmt<space><WAVEFORMAT><WORD>
    constexpr size_t HEADER_READ_SIZE = 36;
    size_t readed = dataStream->FillBuffer(fileHeaderArray, HEADER_READ_SIZE);

    if (readed == HEADER_READ_SIZE && bitsPerSample == 16 && (channelCount == 1 || channelCount == 2))
    {
        // Look for "data" tag
        char tag[4] = {0, 0, 0, 0};
        std::uint32_t size;

        while (true)
        {
            if (dataStream->FillBuffer(tag, sizeof(tag)) != sizeof(tag))
                // EOF
                return false;
            if (dataStream->FillBuffer(&size, sizeof(std::uint32_t)) != sizeof(std::uint32_t))
                return false;

            if (memcmp(tag, "data", sizeof(tag)) == 0)
                break;

            dataStream->Seek(size, SEEK_CUR);
        }

        dataPosition = dataStream->GetCurrentPosition();
        dataChunkSize = size;
        initialized = true;

        if (GetStreamLengthMs() < 7000)
            initialized = false;
    }

    return initialized;
#endif
}

size_t CAEWaveDecoder::FillBuffer(void* dest, size_t size)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using ReadFunc = size_t(__thiscall *)(CAEWaveDecoder*, void*, size_t);
    return ((ReadFunc) 0x5032a0)(this, dest, size);
#else
    switch (channelCount)
    {
        case 1:
        {
            // Read half of it
            size_t readed = dataStream->FillBuffer(dest, size / 2);
            std::int16_t *byteStream = reinterpret_cast<std::int16_t *> (dest);

            // Duplicate channel data
            for (int i = static_cast<int> (readed / sizeof(std::int16_t)) - 1; i >= 0; i--)
                byteStream[i * 2] = byteStream[i * 2 + 1] = byteStream[i];

            return readed * 2;
        }
        case 2:
            // Use fast path
            return dataStream->FillBuffer(dest, size);
        default:
            return 0;
    }
#endif
}

long CAEWaveDecoder::GetStreamLengthMs()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((long(__thiscall *)(CAEWaveDecoder*)) 0x503310)(this);
#else
    if (initialized)
    {
        std::uint32_t samples = dataChunkSize / blockAlign;
        // More precise way would be involving using GCD
        return long((float) samples * 1000.0f / (float) sampleRate);
    }

    return -1;
#endif
}

long CAEWaveDecoder::GetStreamPlayTimeMs()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((long(__thiscall *)(CAEWaveDecoder*)) 0x503360)(this);
#else
    if (initialized)
    {
        std::uint32_t posByte = dataStream->GetCurrentPosition() - dataPosition;
        std::uint32_t posSamples = posByte / blockAlign;
        // More precise way would be involving using GCD
        return long((float) posSamples * 1000.0f / (float) sampleRate);
    }

    return -1;
#endif
}

void CAEWaveDecoder::SetCursor(unsigned long pos)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using SeekFunc = void(__thiscall *)(CAEWaveDecoder*, unsigned long);
    ((SeekFunc) 0x5033c0)(this, pos);
#else
    if (initialized)
    {
        // The calculation is exactly in this order!
        std::uint32_t posByte = pos * sampleRate / 1000 * blockAlign;
        dataStream->Seek(static_cast<long> (posByte + dataPosition), SEEK_SET);
    }
#endif
}

int CAEWaveDecoder::GetSampleRate()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((int(__thiscall *)(CAEWaveDecoder*)) 0x503300)(this);
#else
    return initialized ? static_cast<int> (sampleRate) : -1;
#endif
}

int CAEWaveDecoder::GetStreamID()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((int(__thiscall *)(CAEWaveDecoder*)) 0x503280)(this);
#else
    return dataStream->m_nTrackId;
#endif
}

CAEWaveDecoder *CAEWaveDecoder::ctor(CAEDataStream *dataStream)
{
    this->CAEWaveDecoder::CAEWaveDecoder(dataStream);
    return this;
}

void CAEWaveDecoder::dtor()
{
    this->CAEWaveDecoder::~CAEWaveDecoder();
}

void CAEWaveDecoder::InjectHooks()
{
#ifndef USE_DEFAULT_FUNCTIONS
    ReversibleHooks::Install("CAEWaveDecoder", "CAEWaveDecoder", 0x503250, &CAEWaveDecoder::ctor);
    ReversibleHooks::Install("CAEWaveDecoder", "~CAEWaveDecoder", 0x503290, &CAEWaveDecoder::dtor);
    ReversibleHooks::Install("CAEWaveDecoder", "Initialise", 0x5032b0, &CAEWaveDecoder::Initialise);
    ReversibleHooks::Install("CAEWaveDecoder", "FillBuffer", 0x502470, &CAEWaveDecoder::FillBuffer);
    ReversibleHooks::Install("CAEWaveDecoder", "GetStreamLengthMs", 0x503310, &CAEWaveDecoder::GetStreamLengthMs);
    ReversibleHooks::Install("CAEWaveDecoder", "GetStreamPlayTimeMs", 0x503360, &CAEWaveDecoder::GetStreamPlayTimeMs);
    ReversibleHooks::Install("CAEWaveDecoder", "SetCursor", 0x5033c0, &CAEWaveDecoder::SetCursor);
    ReversibleHooks::Install("CAEWaveDecoder", "GetSampleRate", 0x503300, &CAEWaveDecoder::GetSampleRate);
    ReversibleHooks::Install("CAEWaveDecoder", "GetStreamID", 0x503280, &CAEWaveDecoder::GetStreamID);
#endif
}
