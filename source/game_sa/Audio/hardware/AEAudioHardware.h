#pragma once

#include "dsound.h"

#include "CAESoundManager.h"
#include "CVector.h"

#ifdef PlaySound
#undef PlaySound
#endif

union CAEAudioHardwarePlayFlags {
    uint16 m_nFlags;
    struct {
        uint16 m_bIsFrontend : 1;
        uint16 m_bIsUncompressable : 1;
        uint16 m_bIsUnduckable : 1;
        uint16 m_bIsStartPercentage : 1;
        uint16 m_bIsMusicMastered : 1;
        uint16 : 1;
        uint16 m_bIsRolledOff : 1;
        uint16 m_bIsSmoothDucking : 1;

        uint16 m_bIsForcedFront : 1;
        uint16 m_bUnpausable : 1;
    };
};

class CAEMP3BankLoader;

class CAEAudioHardware {
public:
    uint8                   field_0;
    bool                    m_bDisableEffectsLoading;
    uint8                   field_2;
    uint8                   field_3;
    uint8                   field_4;
    uint8                   m_nReverbEnvironment;
    int16                   m_awChannelFlags[MAX_NUM_AUDIO_CHANNELS];
    uint16                  field_86;
    int32                   m_nReverbDepth;
    uint16                  m_wNumAvailableChannels;
    int16                   m_nNumChannels;
    int16                   m_anNumChannelsInSlot[MAX_NUM_AUDIO_CHANNELS];
    float                   m_afChannelVolumes[MAX_NUM_AUDIO_CHANNELS];
    float                   m_afUnkn[MAX_NUM_AUDIO_CHANNELS];
    float                   m_afChannelsFrqScalingFactor[MAX_NUM_AUDIO_CHANNELS];
    float                   m_fMusicMasterScalingFactor;
    float                   m_fEffectMasterScalingFactor;
    float                   m_fMusicFaderScalingFactor;
    float                   m_fEffectsFaderScalingFactor;
    float                   m_fStreamFaderScalingFactor;
    float                   m_fNonStreamFaderScalingFactor;
    float                   field_428;
    float                   field_42C;
    int16                   m_aBankSlotIds[MAX_NUM_SOUNDS];
    int16                   m_aSoundIdsInSlots[MAX_NUM_SOUNDS];
    int16                   m_anVirtualChannelSoundLoopStartTimes[MAX_NUM_SOUNDS];
    int16                   m_anVirtualChannelSoundLengths[MAX_NUM_SOUNDS];
    uint8                   m_nBassSet;
    char                    _pad1[3];
    float                   m_fBassEqGain;
    CAEMP3BankLoader*       m_pMP3BankLoader;
    void*                   m_pMP3TrackLoader;
    IDirectSound8*          m_pDirectSound;
    void*                   m_dwSpeakerConfig;
    void*                   m_n3dEffectsQueryResult;
    DSCAPS                  m_dsCaps;
    IDirectSound3DListener* m_pDirectSound3dListener;
    void*                   m_pStreamingChannel;
    struct CAEStreamThread* m_pStreamThread;
    uint8                   _paвE14[76];
    void*                   m_aChannels[MAX_NUM_AUDIO_CHANNELS];
    uint32                  m_aBeatInfo[40];
    int32                   field_1004;
    int32                   field_1008;
    int32                   field_100C;
    uint8                   field_1010;
    int32                   field_1014;

public:
    static void InjectHooks();

    // Return types aren't real, I've just copied the signatures for now

    CAEAudioHardware();

    void InitOpenALListener();
    void Initialise();
    void Terminate();

    void   PlaySound(int16 channel, uint16 channelSlot, uint16 soundIdInSlot, uint16 bankSlot, int16 playPosition, int16 flags, float speed);
    void   GetActualNumberOfHardwareChannels();
    uint16 GetNumAvailableChannels() { return m_wNumAvailableChannels; };
    void  GetChannelPlayTimes(int16 channel, int16* outArr);
    void  SetChannelVolume(int16 channel, uint16 channelSlot, float volume, uint8 unused);
    void  LoadSoundBank(uint16 bankId, int16 bankSlotId);
    bool  IsSoundBankLoaded(uint16 bankId, int16 bankSlotId);
    void  GetSoundBankLoadingStatus(uint16, int16);
    void  StopSound(int16 channel, uint16 channelSlot);
    void  SetChannelPosition(int16 channel, uint16 channelSlot, CVector* vecPos, uint8 unused);
    void  SetChannelFrequencyScalingFactor(int16 channel, uint16 channelSlot, float freqFactor);
    void  RescaleChannelVolumes();
    void  Service();
    void  UpdateReverbEnvironment();
    float GetSoundHeadroom(uint16 soundId, int16 bankSlotId);
    void  EnableEffectsLoading();
    void  DisableEffectsLoading();
    void  RequestVirtualChannelSoundInfo(uint16 soundIndex, uint16 soundIdInSlot, uint16 bankSlotId);
    void  GetVirtualChannelSoundLengths(int16* outArr);
    void  GetVirtualChannelSoundLoopStartTimes(int16* outArr);
    void  LoadSound(uint16, uint16, int16);
    void  IsSoundLoaded(uint16, uint16, int16);
    void  GetSoundLoadingStatus(uint16, uint16, int16);
    void  PlayTrack(uint32, int32, uint32, char, bool, bool);
    void  StartTrackPlayback();
    void  StopTrack();
    void  GetTrackPlayTime();
    void  GetTrackLengthMs();
    void  GetActiveTrackID();
    void  GetPlayingTrackID();
    void  GetBeatInfo(struct tBeatInfo*);
    void  SetBassSetting(int8, float);
    void  DisableBassEq();
    void  EnableBassEq();
    void  SetChannelFlags(int16, uint16, int16);
    void  SetMusicMasterScalingFactor(float);
    void  SetEffectsMasterScalingFactor(float);
    void  SetMusicFaderScalingFactor(float);
    void  SetEffectsFaderScalingFactor(float);
    void  GetEffectsMasterScalingFactor();
    void  GetMusicMasterScalingFactor();
    void  GetEffectsFaderScalingFactor();
    void  SetStreamFaderScalingFactor(float);
    void  SetNonStreamFaderScalingFactor(float);
    void  IsStreamingFromDVD();
    void  GetDVDDriveLetter();
    void  CheckDVD();
    void  PauseAllSounds();
    void  ResumeAllSounds();
    int16 AllocateChannels(uint16 numChannels);
};

VALIDATE_SIZE(CAEAudioHardware, 0x1018);

extern CAEAudioHardware& AEAudioHardware;
