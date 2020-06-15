#pragma once

#include <cstdint>

#include <mfidl.h>
#include <mfreadwrite.h>

#include "CAEStreamingDecoder.h"

class CAEMFDecoder: public CAEStreamingDecoder
{
public:
    CAEMFDecoder(char *filename, int trackID);
    ~CAEMFDecoder() override;
    bool Initialise() override;
    size_t FillBuffer(void *dest, size_t size) override;
    long GetStreamLengthMs() override;
    long GetStreamPlayTimeMs() override;
    void SetCursor(unsigned long pos) override;
    int GetSampleRate() override;
    int GetStreamID() override;

    static bool InitLibrary();
    static void Shutdown();

private:
    static constexpr size_t TEMPBUFFRAME = 65536;

    char *filename; // index 8
    bool initialized; // index 12
    union
    {
        std::uint32_t _unknown2[36];
        struct
        {
            IMFSourceReader *sourceReader;
            IMFMediaType *pcmAudio;
            std::int16_t *tempBuffer;
            size_t tempBufferUsed;
        };
    };
    long playTime; // index 160
    long length; // index 164
    union
    {
        std::uint32_t _unknown3[3];
    };
    int trackID; // index 180
    long lengthMs; // index 184
    int sampleRate; // index 188
    float timeDivider; // index 192

    static bool &quickTimeInitialized;
    static HMODULE mfPlatModule, mfReadWriteModule;
    static HRESULT(__stdcall *MFCreateSourceReaderFromURL)(LPCWSTR pwszURL, IMFAttributes *pAttributes, IMFSourceReader **ppSourceReader);
    static HRESULT(__stdcall *MFCreateMediaType)(IMFMediaType **ppMFType); 

private:
    friend void InjectHooksMain(void);

    CAEMFDecoder *ctor(char *filename, int trackID);
    void dtor();

    static void InjectHooks();
};

VALIDATE_SIZE(CAEMFDecoder, 0xc4);
