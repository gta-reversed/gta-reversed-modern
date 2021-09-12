#pragma once

#include "CAEAudioChannel.h"

struct CAEStreamingDecoder;

class CAEStreamingChannel : public CAEAudioChannel {
public:
    uint8                field_60;
    uint8                field_61;
    uint8                field_62;
    uint8                field_63;
    uint8                field_64;
    uint8                m_bFxEnabled;
    uint8                field_66;
    uint8                field_67;
    uint8                m_aBuffer[0x60000];
    uint32               field_6006C;
    CAEStreamingDecoder* m_pStreamingDecoder;
    CAEStreamingDecoder* m_pNextStreamingDecoder;
    uint32               field_60078;
    uint32               m_nStreamLength;
    uint32               m_unkn;
    uint32               field_60084;
    uint32               field_60088;
    uint64               m_nLastUpdateTime;
    IDirectSoundBuffer*  m_pSilenceBuffer;
    float                m_fSomething;

public:
    static void InjectHooks();

    CAEStreamingChannel(IDirectSound* pSound, uint16 channelId);
    ~CAEStreamingChannel() override;

    // VTABLE
    void   Service() override;
    bool   IsSoundPlaying() override;
    uint16 GetPlayTime() override;
    uint16 GetLength() override;
    void   Play(int16, int8, float) override;
    void   SynchPlayback() override;
    void   Stop() override;
    void   SetFrequencyScalingFactor(float factor) override;

    // CLASS
    int32  GetActiveTrackID();
    int32  GetPlayingTrackID();
    void   InitialiseSilence();
    bool   SetNextStream(CAEStreamingDecoder* stream);
    uint32 FillBuffer(void* buffer, uint32 size);
    void   SetBassEQ(IDirectSoundFXParamEq* fxParamEq, float gain);
    void   SetReady();
    void   PrepareStream(CAEStreamingDecoder* stream, int8 arg2, bool bStopCurrent);
};
