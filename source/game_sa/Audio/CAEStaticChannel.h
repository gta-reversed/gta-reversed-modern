#pragma once
#include "CAEAudioChannel.h"

class CAEStaticChannel : public CAEAudioChannel
{
public:
    CAEStaticChannel(IDirectSound* pDirectSound, unsigned short channelId, bool arg3, unsigned int samplesPerSec, unsigned short bitsPerSample);

public:
    bool m_bUnkn1;
    bool m_bUnkn2;
    bool m_bNeedsSynch;
    bool m_bUnkn4;
    int m_nCurrentBufferOffset;
    int field_68;
    int field_6C;
    uint32_t m_nSyncTime;
    int field_74;
    int m_dwLockOffset;
    int m_nNumLockBytes;
    uint16_t field_80;
    uint16_t field_82;
    IDirectSound3DBuffer* m_pBuffer;
    uint16_t field_88;
    bool field_8A;
    char field_8B;
    int field_8C;

public:
    static void InjectHooks();

// VIRTUAL
    void Service() override { assert(false); /* Needs reversing */ };
    bool IsSoundPlaying() override;
    uint16_t GetPlayTime() override;
    uint16_t GetLength() override;
    void Play(short, signed char, float) override { assert(false); /* Needs reversing */ };
    void SynchPlayback() override;
    void Stop() override;

private:
    void Service_Reversed();
    bool IsSoundPlaying_Reversed();
    uint16_t GetPlayTime_Reversed();
    uint16_t GetLength_Reversed();
    void Play_Reversed(short, signed char, float);
    void SynchPlayback_Reversed();
    void Stop_Reversed();

// CLASS
public:
    bool SetAudioBuffer(IDirectSound3DBuffer* buffer, uint16_t soundIdInSlot, int16_t, int16_t, uint16_t loopOffset);
};
VALIDATE_SIZE(CAEStaticChannel, 0x90);
