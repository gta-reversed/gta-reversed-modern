#pragma once

#include "AEAudioChannel.h"

class CAEStreamingDecoder;

class NOTSA_EXPORT_VTABLE CAEStreamingChannel : public CAEAudioChannel {
public:
    uint8                field_60;
    uint8                field_61;
    bool                 m_bPrepareNewStream;
    uint8                field_63;
    uint8                field_64;
    uint8                m_bFxEnabled;
    uint8                m_nCurrentlyLoadedChunk;
    uint8                field_67;
    void*                m_pBuffer;
    uint8                m_aBuffer[0x60000];
    CAEStreamingDecoder* m_pStreamingDecoder;
    CAEStreamingDecoder* m_pNextStreamingDecoder;
    uint32               m_nState;
    uint32               m_nStreamPlayTimeMs;
    uint32               m_nPlayTime;
    uint32               field_60084;
    int32                field_60088;
    uint64               m_nLastUpdateTime;
    IDirectSoundBuffer*  m_pSilenceBuffer;
    float                m_fSomething;

public:
    CAEStreamingChannel(IDirectSound* directSound, uint16 channelId);
    ~CAEStreamingChannel() override;

    void   Service() override;
    bool   IsSoundPlaying() override;
    int16  GetPlayTime() override;
    uint16 GetLength() override;
    void   Play(int16, int8, float) override;
    void   SynchPlayback() override;
    void   Stop() override;
    void   SetFrequencyScalingFactor(float factor) override;

    void  Initialise();
    void  InitialiseSilence();

    bool AddFX();
    void RemoveFX();

    int32 UpdatePlayTime();

    int32  GetActiveTrackID();
    int32  GetPlayingTrackID();
    void   SetNextStream(CAEStreamingDecoder* decoder);
    uint32 FillBuffer(void* buffer, uint32 size);
    void   SetBassEQ(IDirectSoundFXParamEq* paramEq, float gain);
    void   SetReady();
    void   PrepareStream(CAEStreamingDecoder* stream, int8 arg2, bool bStopCurrent);
    void   Pause();

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CAEStreamingChannel* Constructor(IDirectSound* directSound, uint16 channelId);
    CAEStreamingChannel* Destructor();

    void  Service_Reversed();
    bool  IsSoundPlaying_Reversed();
    int32 GetPlayTime_Reversed();
    int32 GetLength_Reversed();
    void  Play_Reversed(int16 a2,  char a3, float a4);
    void  Stop_Reversed();
    void  SetFrequencyScalingFactor_Reversed(float a2);
};

VALIDATE_SIZE(CAEStreamingChannel, 0x60098);
