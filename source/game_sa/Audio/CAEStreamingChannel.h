#pragma once
#include "PluginBase.h"
#include "CAEAudioChannel.h"
struct CAEStreamingDecoder;

class CAEStreamingChannel : public CAEAudioChannel
{
public:
    CAEStreamingChannel(IDirectSound* pSound, unsigned short channelId);
    ~CAEStreamingChannel() override;

public:
    uint8_t field_60;
    uint8_t field_61;
    uint8_t field_62;
    uint8_t field_63;
    uint8_t field_64;
    uint8_t m_bFxEnabled;
    uint8_t field_66;
    uint8_t field_67;
    uint8_t m_aBuffer[0x60000];
    uint32_t field_6006C;
    CAEStreamingDecoder* m_pStreamingDecoder;
    CAEStreamingDecoder* m_pNextStreamingDecoder;
    uint32_t field_60078;
    uint32_t m_nStreamLength;
    uint32_t m_unkn;
    uint32_t field_60084;
    uint32_t field_60088;
    uint64_t m_nLastUpdateTime;
    IDirectSoundBuffer* m_pSilenceBuffer;
    float m_fSomething;

public:
    static void InjectHooks();

// VTABLE
    void Service() override;
    bool IsSoundPlaying() override;
    uint16_t GetPlayTime() override;
    uint16_t GetLength() override;
    void Play(short, signed char, float) override;
    void SynchPlayback() override;
    void Stop() override;
    void SetFrequencyScalingFactor(float factor) override;

// CLASS
    int GetActiveTrackID();
    int GetPlayingTrackID();
    void InitialiseSilence();
    bool SetNextStream(CAEStreamingDecoder* stream);
    uint32_t FillBuffer(void* buffer, uint32_t size);
    void SetBassEQ(IDirectSoundFXParamEq* fxParamEq, float gain);
    void SetReady();
    void PrepareStream(CAEStreamingDecoder* stream, signed char arg2, bool bStopCurrent);
};
