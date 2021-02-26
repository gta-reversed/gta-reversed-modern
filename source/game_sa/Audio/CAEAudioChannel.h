#pragma once
#include "dsound.h"
#include "PluginBase.h"
#include "CVector.h"

#pragma pack(push, 1)
class CAEAudioChannel
{
public:
    CAEAudioChannel(IDirectSound* pDirectSound, unsigned short channelId, unsigned int samplesPerSec, unsigned short bitsPerSample);
    virtual ~CAEAudioChannel();

public:
    IDirectSound* m_pDirectSound;
    IDirectSoundBuffer* m_pDirectSoundBuffer;
    IDirectSound3DBuffer* m_pDirectSound3DBuffer;
    uint8_t gap10[24];
    uint32_t m_dwFlags;
    uint32_t m_dwLengthInBytes;
    uint32_t field_30;
    float m_fVolume;
    bool m_bNoScalingFactor;
    uint8_t field_39;
    uint16_t m_nChannelId;
    uint32_t m_dwFrequency;
    uint32_t m_dwOriginalFrequency;
    bool m_bLooped;
    uint8_t field_45;
    uint8_t field_46[1];
    uint16_t field_47;
    uint16_t m_wFrequencyMult;
    uint32_t m_dwBufferFrequency;
    uint32_t m_nBytesPerSec;
    uint16_t field_53;
    uint16_t m_wBitsPerSample;
    uint16_t field_57;
    uint16_t field_59;
    uint8_t pad;
    uint32_t m_dwBufferStatus;

// VTABLE
public:
    virtual void Service() = 0;
    virtual bool IsSoundPlaying() = 0;
    virtual uint16_t GetPlayTime() = 0;
    virtual uint16_t GetLength() = 0;
    virtual void Play(short, signed char, float) = 0;
    virtual void SynchPlayback() = 0;
    virtual void Stop() = 0;
    virtual void SetFrequencyScalingFactor(float factor);

private:
    void SetFrequencyScalingFactor_Reversed(float factor);

public:
    static void InjectHooks();

    void SetPosition(CVector* vecPos);
    float GetVolume() const { return m_fVolume; };
    void SetVolume(float volume);
    bool IsBufferPlaying() const { return m_dwBufferStatus & DSBSTATUS_PLAYING; };
    int GetCurrentPlaybackPosition();
    uint32_t ConvertFromBytesToMS(uint32_t bytes);
    uint32_t ConvertFromMsToBytes(uint32_t ms);
    void SetFrequency(uint32_t freq);
    void SetOriginalFrequency(uint32_t freq);
    void UpdateStatus();

// Methods not in android IDB
    bool Lost();

// Those 2 require DirectSound EAX 4.0 extensions or some alternative to be available in project
    bool SetReverbAndDepth(uint32_t reverb, uint32_t depth);
    void SetNotInRoom(uint8_t type); // 0 - frontend, 1 - world
};
#pragma pack(pop)
VALIDATE_SIZE(CAEAudioChannel, 0x60);

extern uint32_t& g_numSoundChannelsUsed;
