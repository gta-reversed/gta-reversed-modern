#include "StdInc.h" // TODO: Remove
#include "CAEVorbisDecoder.h"

ov_callbacks CAEVorbisDecoder::staticCallbacks = {
    &CAEVorbisDecoder::ReadCallback,
    &CAEVorbisDecoder::SeekCallback,
    &CAEVorbisDecoder::CloseCallback,
    &CAEVorbisDecoder::TellCallback
};

CAEVorbisDecoder::CAEVorbisDecoder(CAEDataStream* dataStream, int userTrack)
: CAEStreamingDecoder(dataStream)
, callbacks(staticCallbacks)
, vorbisFileHandle(nullptr)
, initialized(false)
, isUserTrack(static_cast<bool> (userTrack))
, _dataStreamCopy(dataStream)
, vorbisInfo(nullptr)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using Constructor = void(__thiscall *)(CAEVorbisDecoder*, CAEDataStream*, int);
    ((Constructor) 0x5026b0)(this, dataStream, userTrack);
#endif
}

CAEVorbisDecoder::~CAEVorbisDecoder()
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CAEVorbisDecoder*)) 0x5023f0)(this);
#else
    if (vorbisFileHandle)
    {
        ov_clear(vorbisFileHandle);
        delete vorbisFileHandle;
        vorbisFileHandle = nullptr;
    }
#endif
}

bool CAEVorbisDecoder::Initialise()
{
#ifdef USE_DEFAULT_FUNCTIONS
    using InitFunc = bool(__thiscall *)(CAEVorbisDecoder*);
    return ((InitFunc) 0x5024d0)(this);
#else
    vorbisFileHandle = new OggVorbis_File();
    if (ov_open_callbacks(dataStream, vorbisFileHandle, nullptr, 0, callbacks) != 0)
        return false;

    vorbisInfo = ov_info(vorbisFileHandle, -1);

    // Not support channels > 2
    if (vorbisInfo->channels > 2)
        return false;

    initialized = true;

    if (isUserTrack)
    {
        if (GetStreamLengthMs() < 7000)
            return initialized = false;
    }

    return true;
#endif
}

size_t CAEVorbisDecoder::FillBuffer(void *dest, size_t size)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using ReadFunc = size_t(__thiscall *)(CAEVorbisDecoder*, void*, size_t);
    return ((ReadFunc) 0x502470)(this, dest, size);
#else
    size_t readedTotal = 0;
    char *buffer = reinterpret_cast<char *> (dest);

    // In case of mono stream, only read half of it
    if (vorbisInfo->channels == 1)
        size /= 2;

    if (size > 0)
    {
        int dummy;

        while (readedTotal < size)
        {
            long readed = ov_read(vorbisFileHandle, buffer + readedTotal, size - readedTotal, 0, sizeof(std::int16_t), 1, &dummy);
            if (readed <= 0)
                break;

            readedTotal += static_cast<size_t> (readed);
        }
    }

    if (vorbisInfo->channels == 1)
    {
        // Duplicate channel data
        std::int16_t *bufShort = reinterpret_cast<std::int16_t *> (buffer);

        for (int i = static_cast<int> (readedTotal / sizeof(std::int16_t)) - 1; i >= 0; i--)
            bufShort[i * 2] = bufShort[i * 2 + 1] = bufShort[i];

        readedTotal *= 2;
    }

    return readedTotal;
#endif
}

long CAEVorbisDecoder::GetStreamLengthMs()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((long(__thiscall *)(CAEVorbisDecoder*)) 0x502610)(this);
#else
    if (initialized)
    {
        double length = ov_time_total(vorbisFileHandle, -1);
        return (long) (length * 1000.0);
    }

    return -1;
#endif
}

long CAEVorbisDecoder::GetStreamPlayTimeMs()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((long(__thiscall *)(CAEVorbisDecoder*)) 0x502640)(this);
#else
    if (initialized)
    {
        double length = ov_time_tell(vorbisFileHandle);
        return (long) (length * 1000.0);
    }

    return -1;
#endif
}

void CAEVorbisDecoder::SetCursor(unsigned long pos)
{
#ifdef USE_DEFAULT_FUNCTIONS
    using SeekFunc = void(__thiscall *)(CAEVorbisDecoder*, unsigned long);
    ((SeekFunc) 0x502670)(this, pos);
#else
    if (initialized)
        ov_time_seek(vorbisFileHandle, pos * 0.001);
#endif
}

int CAEVorbisDecoder::GetSampleRate()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((int(__thiscall *)(CAEVorbisDecoder*)) 0x502560)(this);
#else
    return initialized ? static_cast<int> (vorbisInfo->rate) : -1;
#endif
}

int CAEVorbisDecoder::GetStreamID()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((int(__thiscall *)(CAEVorbisDecoder*)) 0x502460)(this);
#else
    return dataStream->m_nTrackId;
#endif
}

size_t CAEVorbisDecoder::ReadCallback(void *ptr, size_t size, size_t nmemb, void *opaque)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((decltype(ReadCallback) *) 0x502580)(ptr, size, nmemb, opaque);
#else
    if (opaque == nullptr)
        return 0;

    CAEDataStream *dataStream = reinterpret_cast<CAEDataStream *> (opaque);
    return dataStream->FillBuffer(ptr, size * nmemb) / size;
#endif
}

int CAEVorbisDecoder::CloseCallback(void *opaque)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((decltype(CloseCallback) *) 0x5025d0)(opaque);
#else
    if (opaque == nullptr)
        return -1;

    CAEDataStream *dataStream = reinterpret_cast<CAEDataStream *> (opaque);
    return dataStream->Close();
#endif
}

int CAEVorbisDecoder::SeekCallback(void *opaque, ogg_int64_t offset, int whence)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((decltype(SeekCallback) *) 0x5025b0)(opaque, offset, whence);
#else
    if (opaque == nullptr)
        return -1;

    CAEDataStream *dataStream = reinterpret_cast<CAEDataStream *> (opaque);
    unsigned long result = dataStream->Seek(static_cast<long> (offset), whence);

    return static_cast<int> (result);
#endif
}

long CAEVorbisDecoder::TellCallback(void *opaque)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((decltype(TellCallback) *) 0x5025f0)(opaque);
#else
    if (opaque == nullptr)
        return -1;

    CAEDataStream *dataStream = reinterpret_cast<CAEDataStream *> (opaque);

    return static_cast<int> (dataStream->GetCurrentPosition());
#endif
}

CAEVorbisDecoder *CAEVorbisDecoder::ctor(CAEDataStream *dataStream, int unknown)
{
    this->CAEVorbisDecoder::CAEVorbisDecoder(dataStream, unknown);
    return this;
}

void CAEVorbisDecoder::dtor()
{
    this->CAEVorbisDecoder::~CAEVorbisDecoder();
}

void CAEVorbisDecoder::InjectHooks()
{
#ifndef USE_DEFAULT_FUNCTIONS
    ReversibleHooks::Install(0x5023f0, &CAEVorbisDecoder::dtor);
    ReversibleHooks::Install(0x502460, &CAEVorbisDecoder::GetStreamID);
    ReversibleHooks::Install(0x502470, &CAEVorbisDecoder::FillBuffer);
    ReversibleHooks::Install(0x5024d0, &CAEVorbisDecoder::Initialise);
    ReversibleHooks::Install(0x502560, &CAEVorbisDecoder::GetSampleRate);
    ReversibleHooks::Install(0x502580, &CAEVorbisDecoder::ReadCallback);
    ReversibleHooks::Install(0x5025d0, &CAEVorbisDecoder::CloseCallback);
    ReversibleHooks::Install(0x5025b0, &CAEVorbisDecoder::SeekCallback);
    ReversibleHooks::Install(0x5025f0, &CAEVorbisDecoder::TellCallback);
    ReversibleHooks::Install(0x502610, &CAEVorbisDecoder::GetStreamLengthMs);
    ReversibleHooks::Install(0x502640, &CAEVorbisDecoder::GetStreamPlayTimeMs);
    ReversibleHooks::Install(0x502670, &CAEVorbisDecoder::SetCursor);
    ReversibleHooks::Install(0x5026b0, &CAEVorbisDecoder::ctor);
#endif
}
