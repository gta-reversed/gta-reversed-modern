#pragma once
#include "AEAudioChannel.h"

class NOTSA_EXPORT_VTABLE CAEStaticChannel : public CAEAudioChannel {
public:
    bool                  m_bUnkn1;
    bool                  m_bUnkn2;
    bool                  m_bNeedsSynch;
    bool                  m_bUnkn4;
    int32                 m_nCurrentBufferOffset;
    int32                 field_68;
    int32                 field_6C;
    uint32                m_nSyncTime;
    int32                 field_74;
    int32                 m_dwLockOffset;
    int32                 m_nNumLockBytes;
    uint16                field_80;
    uint16                field_82;
    IDirectSound3DBuffer* m_pBuffer;
    uint16                field_88;
    bool                  field_8A;
    char                  field_8B;
    int32                 field_8C;

public:
    CAEStaticChannel(IDirectSound* pDirectSound, uint16 channelId, bool arg3, uint32 samplesPerSec, uint16 bitsPerSample);

    // VIRTUAL
    void   Service() override { assert(false); /* Needs reversing */ };
    bool   IsSoundPlaying() override;
    int16  GetPlayTime() override;
    uint16 GetLength() override;
    void   Play(int16, int8, float) override { assert(false); /* Needs reversing */ };
    void   SynchPlayback() override;
    void   Stop() override;

    // CLASS
    bool SetAudioBuffer(IDirectSound3DBuffer* buffer, uint16 soundIdInSlot, int16, int16, uint16 loopOffset);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    void   Service_Reversed();
    bool   IsSoundPlaying_Reversed();
    int16  GetPlayTime_Reversed();
    uint16 GetLength_Reversed();
    void   Play_Reversed(int16, int8, float);
    void   SynchPlayback_Reversed();
    void   Stop_Reversed();
};
VALIDATE_SIZE(CAEStaticChannel, 0x90);
