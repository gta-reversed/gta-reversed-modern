#pragma once

#include "dsound.h"
#include "PluginBase.h"

enum eSmoothFadeEntryStatus : uint32_t
{
    STATE_INACTIVE = 0,
    STATE_ACTIVE = 1,
    STATE_CANCELLED = 2,
};
struct tSmoothFadeEntry
{
    IDirectSoundBuffer*    m_pSoundBuffer;
    float                  m_fStartVolume;
    float                  m_fTargetVolume;
    float                  m_fVolumeDiff;
    float                  m_fCurVolume;
    bool                   m_bStopBufferAfterFade;
    uint8_t               _pad;
    uint16_t               m_wFadeTime;
    eSmoothFadeEntryStatus m_nStatus;
    uint32_t               m_nStartTime;
};
VALIDATE_SIZE(tSmoothFadeEntry, 0x20);


class CAESmoothFadeThread
{
public:
    CAESmoothFadeThread();

public:
    static constexpr int NUM_SMOOTHFADE_ENTRIES = 64;

public:
    HANDLE m_threadHandle;
    DWORD m_dwThreadId;
    tSmoothFadeEntry m_aEntries[NUM_SMOOTHFADE_ENTRIES];
    bool m_bThreadCreated;
    bool m_bActive;
    uint16_t m_wUnkn;
    uint16_t m_wUnkn2;
    uint16_t m_wUnkn3;
    uint32_t m_nLastServiceTime;
    bool m_bThreadInvalid;
    uint8_t pad2[3];
    uint32_t m_nNumAvailableBuffers;

public:
    static void InjectHooks();

    void Initialise();
    void InitialiseRequestSlots();
    void Start();
    void Stop();
    void WaitForExit();
    void Service();
    void CancelFade(IDirectSoundBuffer* buffer);
    bool RequestFade(IDirectSoundBuffer* buffer, float fTargetVolume, short fadeTime, bool bStopBufferAfterFade);
    void SetBufferVolume(IDirectSoundBuffer* buffer, float volume);

public:
    static DWORD WINAPI SmoothFadeProc(void* pSmoothFade);
};
VALIDATE_SIZE(CAESmoothFadeThread, 0x81C);

extern CAESmoothFadeThread& AESmoothFadeThread;
