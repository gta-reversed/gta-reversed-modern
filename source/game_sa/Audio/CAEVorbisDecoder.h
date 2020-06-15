#pragma once

#include "vorbis/vorbisfile.h"

#include "CAEStreamingDecoder.h"

class CAEVorbisDecoder: public CAEStreamingDecoder
{
public:
    CAEVorbisDecoder(CAEDataStream *dataStream, int userTrack);
    ~CAEVorbisDecoder() override;
    bool Initialise() override;
    size_t FillBuffer(void* dest,size_t size) override;
    long GetStreamLengthMs() override;
    long GetStreamPlayTimeMs() override;
    void SetCursor(unsigned long pos) override;
    int GetSampleRate() override;
    int GetStreamID() override;

private:
    ov_callbacks callbacks;
    OggVorbis_File *vorbisFileHandle;
    bool initialized;
    bool isUserTrack;
    CAEDataStream *_dataStreamCopy;
    vorbis_info *vorbisInfo;

    static ov_callbacks staticCallbacks;

    static size_t ReadCallback(void *ptr, size_t size, size_t nmemb, void *opaque);
    static int CloseCallback(void *opaque);
    static int SeekCallback(void *opaque, ogg_int64_t offset, int whence);
    static long TellCallback(void *opaque);

private:
    friend void InjectHooksMain(void);

    CAEVorbisDecoder *ctor(CAEDataStream *dataStream, int unknown);
    void dtor();

    static void InjectHooks();
};

VALIDATE_SIZE(CAEVorbisDecoder, 0x28);
