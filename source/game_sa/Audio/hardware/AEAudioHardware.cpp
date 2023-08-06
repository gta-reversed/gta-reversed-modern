#include "StdInc.h"

#include "AEAudioHardware.h"
#include "AEMP3BankLoader.h"
#include "AEMP3TrackLoader.h"
#include "AEAudioEnvironment.h"

CAEAudioHardware& AEAudioHardware = *reinterpret_cast<CAEAudioHardware*>(0xB5F8B8);

void CAEAudioHardware::InjectHooks() {
    RH_ScopedClass(CAEAudioHardware);
    RH_ScopedCategory("Audio/Hardware");

    // RH_ScopedInstall(Constructor, 0x4D83E0, { .reversed = false });
    // RH_ScopedInstall(Destructor, 0x4D83A0, { .reversed = false });

    RH_ScopedInstall(AllocateChannels, 0x5B9340);
    RH_ScopedInstall(RequestVirtualChannelSoundInfo, 0x4D8E60);
    RH_ScopedInstall(Query3DSoundEffects, 0x4D8490, { .reversed = false });
    RH_ScopedInstall(GetNumAvailableChannels, 0x4D8810);
    RH_ScopedInstall(GetChannelPlayTimes, 0x4D8820);
    RH_ScopedInstall(SetChannelVolume, 0x4D8870);
    RH_ScopedInstall(LoadSoundBank, 0x4D88A0);
    RH_ScopedInstall(IsSoundBankLoaded, 0x4D88C0);
    RH_ScopedInstall(GetSoundBankLoadingStatus, 0x4D88D0);
    RH_ScopedInstall(LoadSound, 0x4D8ED0);
    RH_ScopedInstall(IsSoundLoaded, 0x4D8EF0);
    RH_ScopedInstall(GetSoundLoadingStatus, 0x4D8F00);
    RH_ScopedInstall(StopSound, 0x4D88E0);
    RH_ScopedInstall(SetChannelPosition, 0x4D8920);
    RH_ScopedInstall(SetChannelFrequencyScalingFactor, 0x4D8960);
    RH_ScopedInstall(RescaleChannelVolumes, 0x4D8990, { .reversed = false });
    RH_ScopedInstall(UpdateReverbEnvironment, 0x4D8DA0);
    RH_ScopedInstall(GetSoundHeadroom, 0x4D8E30);
    RH_ScopedInstall(EnableEffectsLoading, 0x4D8E40);
    RH_ScopedInstall(DisableEffectsLoading, 0x4D8E50);
    RH_ScopedInstall(GetVirtualChannelSoundLengths, 0x4D8E90);
    RH_ScopedInstall(GetVirtualChannelSoundLoopStartTimes, 0x4D8EB0);
    RH_ScopedInstall(PlayTrack, 0x4D8F10);
    RH_ScopedInstall(StartTrackPlayback, 0x4D8F30);
    RH_ScopedInstall(StopTrack, 0x4D8F50);
    RH_ScopedInstall(GetTrackPlayTime, 0x4D8F60);
    RH_ScopedInstall(GetTrackLengthMs, 0x4D8F70);
    RH_ScopedInstall(GetActiveTrackID, 0x4D8F80);
    RH_ScopedInstall(GetPlayingTrackID, 0x4D8F90);
    RH_ScopedInstall(GetBeatInfo, 0x4D8FA0);
    RH_ScopedInstall(SetBassSetting, 0x4D94A0);
    RH_ScopedInstall(DisableBassEq, 0x4D94D0);
    RH_ScopedInstall(EnableBassEq, 0x4D94E0);
    RH_ScopedInstall(SetChannelFlags, 0x4D9500);
    RH_ScopedInstall(SetMusicMasterScalingFactor, 0x4D9530);
    RH_ScopedInstall(SetEffectsMasterScalingFactor, 0x4D9540);
    RH_ScopedInstall(SetMusicFaderScalingFactor, 0x4D9550);
    RH_ScopedInstall(SetEffectsFaderScalingFactor, 0x4D9560);
    RH_ScopedInstall(GetEffectsMasterScalingFactor, 0x4D9570);
    RH_ScopedInstall(GetMusicMasterScalingFactor, 0x4D9580);
    RH_ScopedInstall(GetEffectsFaderScalingFactor, 0x4D9590);
    RH_ScopedInstall(SetNonStreamFaderScalingFactor, 0x4D95A0);
    RH_ScopedInstall(SetStreamFaderScalingFactor, 0x4D95B0);
    RH_ScopedInstall(IsStreamingFromDVD, 0x4D95C0);
    RH_ScopedInstall(GetDVDDriveLetter, 0x4D95D0);
    RH_ScopedInstall(CheckDVD, 0x4D95E0);
    RH_ScopedInstall(PauseAllSounds, 0x4D95F0, { .reversed = false });
    RH_ScopedInstall(ResumeAllSounds, 0x4D9630, { .reversed = false });
    RH_ScopedInstall(InitDirectSoundListener, 0x4D9640, { .reversed = false });
    RH_ScopedInstall(Terminate, 0x4D97A0, { .reversed = false });
    RH_ScopedInstall(Service, 0x4D9870, { .reversed = false });
    RH_ScopedInstall(Initialise, 0x4D9930, { .reversed = false });
}

// 0x4D83E0
CAEAudioHardware::CAEAudioHardware() {
    plugin::CallMethod<0x4D83E0, CAEAudioHardware*>(this);
}

// 0x4D83A0
CAEAudioHardware::~CAEAudioHardware() {
    plugin::CallMethod<0x4D83A0, CAEAudioHardware*>(this);
}

// 0x4D9930
bool CAEAudioHardware::Initialise() {
    return plugin::CallMethodAndReturn<bool, 0x4D9930, CAEAudioHardware*>(this);
}

// 0x4D9640
bool CAEAudioHardware::InitDirectSoundListener(uint32 numChannels, uint32 samplesPerSec, uint32 bitsPerSample) {
    return plugin::CallMethodAndReturn<bool, 0x4D9640, CAEAudioHardware*, uint32, uint32, uint32>(this, numChannels, samplesPerSec, bitsPerSample);
}

// 0x4D97A0
void CAEAudioHardware::Terminate() {
    plugin::CallMethod<0x4D97A0, CAEAudioHardware*>(this);
}

void CAEAudioHardware::PlaySound(int16 channel, uint16 channelSlot, uint16 soundIdInSlot, uint16 bankSlot, int16 playPosition, int16 flags, float speed) {
    plugin::CallMethod<0x4D86B0, CAEAudioHardware*, int16, uint16, uint16, uint16, int16, int16, float>(this, channel, channelSlot, soundIdInSlot, bankSlot, playPosition, flags, speed);
}

// 0x5B9340
int16 CAEAudioHardware::AllocateChannels(uint16 numChannels) {
    if (!numChannels || numChannels > m_nNumAvailableChannels)
        return -1;

    auto slot = 0;
    while (m_anNumChannelsInSlot[slot] && slot < MAX_NUM_AUDIO_CHANNELS)
        slot += m_anNumChannelsInSlot[slot];

    if (slot >= MAX_NUM_AUDIO_CHANNELS)
        return -1;

    m_anNumChannelsInSlot[slot] = numChannels;
    m_nNumAvailableChannels -= numChannels;
    return slot;
}

// 0x4D94A0
void CAEAudioHardware::SetBassSetting(int8 nBassSet, float fBassEqGain) {
    plugin::CallMethod<0x4D94A0, CAEAudioHardware*, int8, float>(this, nBassSet, fBassEqGain);
    /*
    m_nBassSet    = nBassSet;
    m_fBassEqGain = fBassEqGain;
    ??? m_pStreamingChannel->SetBassEQ(reinterpret_cast<IDirectSoundFXParamEq*>(nBassSet), fBassEqGain);
    */
}

// 0x4D8810
uint16 CAEAudioHardware::GetNumAvailableChannels() const {
    return m_nNumAvailableChannels;
}

// 0x4D8820
void CAEAudioHardware::GetChannelPlayTimes(int16 channel, int16* playTimes) {
    assert(playTimes); // NOTE: Originally just an if check, but I don't like quit errors

    for (auto i = m_anNumChannelsInSlot[channel]; i-- > 0;) {
        playTimes[i] = m_aChannels[channel + i]->GetPlayTime();
    }
}

// 0x4D8870
void CAEAudioHardware::SetChannelVolume(int16 channel, uint16 channelId, float volume, uint8 a4) {
    if (channel >= 0 && channelId < m_anNumChannelsInSlot[channel])
        m_afChannelVolumes[channel + channelId] = volume;
}

// 0x4D88A0
void CAEAudioHardware::LoadSoundBank(uint16 bankId, int16 bankSlotId) {
    if (!m_bDisableEffectsLoading) {
        m_pMP3BankLoader->LoadSoundBank(bankId, bankSlotId);
    }
}

// 0x4D88C0
bool CAEAudioHardware::IsSoundBankLoaded(uint16 bankId, int16 bankSlotId) {
    return m_pMP3BankLoader->IsSoundBankLoaded(bankId, bankSlotId);
}

// 0x4D88D0
int8 CAEAudioHardware::GetSoundBankLoadingStatus(uint16 bankId, int16 bankSlotId) {
    return m_pMP3BankLoader->GetSoundBankLoadingStatus(bankId, bankSlotId);
}

// 0x4D8ED0
void CAEAudioHardware::LoadSound(uint16 bank, uint16 sound, int16 slot) {
    if (!m_bDisableEffectsLoading) {
        m_pMP3BankLoader->LoadSound(bank, sound, slot);
    }
}

// 0x4D8EF0
bool CAEAudioHardware::IsSoundLoaded(uint16 bankId, uint16 sfxId, int16 bankSlot) {
    return m_pMP3BankLoader->IsSoundLoaded(bankId, sfxId, bankSlot);
}

// 0x4D8F00
bool CAEAudioHardware::GetSoundLoadingStatus(uint16 bankId, uint16 sfxId, int16 bankSlot) {
    return m_pMP3BankLoader->GetSoundLoadingStatus(bankId, sfxId, bankSlot);
}

// 0x4D88E0
void CAEAudioHardware::StopSound(int16 channel, uint16 channelId) {
    if (channel >= 0 && channelId < m_anNumChannelsInSlot[channel]) {
        const auto ch = m_aChannels[channel + channelId];
        if (ch) {
            ch->Stop();
        }
    }
}

// 0x4D8920
void CAEAudioHardware::SetChannelPosition(int16 channel, uint16 channelId, CVector* posn, uint8 unused) {
    if (channel >= 0 && channelId < m_anNumChannelsInSlot[channel]) {
        const auto ch = m_aChannels[channel + channelId];
        if (ch) {
            ch->SetPosition(posn);
        }
    }
}

// 0x4D8960
void CAEAudioHardware::SetChannelFrequencyScalingFactor(int16 channel, uint16 channelId, float factor) {
    if (channel >= 0 && channelId < m_anNumChannelsInSlot[channel]) {
        m_afChannelsFrqScalingFactor[channel + channelId] = factor;
    }
}

// 0x4D8990
void CAEAudioHardware::RescaleChannelVolumes() {
    return plugin::Call<0x4D8990, CAEAudioHardware*>(this);
}

// 0x4D8DA0
void CAEAudioHardware::UpdateReverbEnvironment() {
    int8 reverb;
    int32 depth;
    CAEAudioEnvironment::GetReverbEnvironmentAndDepth(&reverb, &depth);
    if (reverb == m_nReverbEnvironment && depth == m_nReverbDepth) { // Nothing is changing?
        return;
    }
    if (!rng::none_of(GetChannels(), [=](CAEAudioChannel* ch) { // Also covers the case of `m_nNumChannels == 0`
        return ch && ch->SetReverbAndDepth(reverb, depth); }
    )) {
        return;
    }
    m_nReverbEnvironment = reverb;
    m_nReverbDepth       = depth;
}

// 0x4D8E30
float CAEAudioHardware::GetSoundHeadroom(uint16 sfxId, int16 bankSlotId) {
    return m_pMP3BankLoader->GetSoundHeadroom(sfxId, bankSlotId);
}

// 0x4D8E40
void CAEAudioHardware::EnableEffectsLoading() {
    m_bDisableEffectsLoading = false; // weird name
}

// 0x4D8E50
void CAEAudioHardware::DisableEffectsLoading() {
    m_bDisableEffectsLoading = true; // weird name
}

// 0x4D8E60
void CAEAudioHardware::RequestVirtualChannelSoundInfo(uint16 channel, uint16 sfxId, uint16 bankSlotId) {
    if (channel < MAX_NUM_SOUNDS) {
        m_aBankSlotIds[channel] = bankSlotId;
        m_aSoundIdsInSlots[channel] = sfxId;
    }
}

// 0x4D8E90
void CAEAudioHardware::GetVirtualChannelSoundLengths(int16* soundLengths) {
    memcpy(soundLengths, m_anVirtualChannelSoundLengths, sizeof(m_anVirtualChannelSoundLengths));
}

// 0x4D8EB0
void CAEAudioHardware::GetVirtualChannelSoundLoopStartTimes(int16* soundLoopStartTimes) {
    memcpy(soundLoopStartTimes, m_anVirtualChannelSoundLoopStartTimes, sizeof(m_anVirtualChannelSoundLoopStartTimes)); // size is 600, replaced by loop?
}

// 0x4D8F10
void CAEAudioHardware::PlayTrack(uint32 trackId, int32 nextTrackId, uint32 a3, char a4, bool isUserTrack, bool nextIsUserTrack) {
    field_1010 = a4;
    m_pStreamThread.PlayTrack(trackId, nextTrackId, a3, a4, isUserTrack, nextIsUserTrack);
}

// 0x4D8F30
void CAEAudioHardware::StartTrackPlayback() const {
    m_pStreamingChannel->Play(0, field_1010, 1.0f);
}

// 0x4D8F50
void CAEAudioHardware::StopTrack() {
    m_pStreamThread.StopTrack();
}

// 0x4D8F60
int32 CAEAudioHardware::GetTrackPlayTime() const {
    return m_pStreamThread.GetTrackPlayTime();
}

// 0x4D8F70
int32 CAEAudioHardware::GetTrackLengthMs() const {
    return m_pStreamThread.GetTrackLengthMs();
}

// 0x4D8F80
int32 CAEAudioHardware::GetActiveTrackID() const {
    return m_pStreamThread.GetActiveTrackID();
}

// 0x4D8F90
int32 CAEAudioHardware::GetPlayingTrackID() const {
    return m_pStreamThread.GetPlayingTrackID();
}

// 0x4D8FA0
void CAEAudioHardware::GetBeatInfo(tBeatInfo* beatInfo) {
    const auto bi = &gBeatInfo;

    if (m_pStreamThread.GetActiveTrackID() == -1) {
        bi->IsBeatInfoPresent = false;
        rng::fill(bi->BeatWindow, tTrackInfo::tBeat{});
        return;
    }

    const auto tId       = m_pStreamThread.GetActiveTrackID();
    const auto tInfo     = std::unique_ptr<tTrackInfo>{m_pMP3TrackLoader->GetTrackInfo(tId)};
    const auto tPlayTime = m_pStreamThread.GetTrackPlayTime();

    size_t i = 0;

    if (tPlayTime < 0 || tInfo->m_aBeats[0].m_nTime < 0) {
        if (tPlayTime != -7) {
            bi->IsBeatInfoPresent = false;
            rng::fill(bi->BeatWindow, tTrackInfo::tBeat{});
        }
    } else {
        const auto beatTimeWindowBegin = bi->BeatNumber
            ? std::max(0u, (uint32)tPlayTime - 50u)
            : (uint32)tPlayTime;

        bi->IsBeatInfoPresent  = true;
        bi->BeatTypeThisFrame = 0;
        bi->BeatNumber        = -1;
        rng::fill(bi->BeatWindow, tTrackInfo::tBeat{});

        //> 0x4D904C - Find first beat in the given time window
        for (; tInfo->m_aBeats[i].m_nKey && tInfo->m_aBeats[i].m_nTime < beatTimeWindowBegin; i++);
    }

    // 0x4D9346 and 0x4D9088 combined - Copy beats at the beginning of the time window
    for (auto k = 0u; k < std::min(10u, i); k++) {
        auto& beat    = bi->BeatWindow[10 - i];
        beat          = tInfo->m_aBeats[i - k - 1];
        beat.m_nTime -= tPlayTime;
    }

    if (tInfo->m_aBeats[i].m_nKey != 0) {
        // 0x4D9078
        if (i != bi->BeatNumber && i > 0) {
            bi->BeatTypeThisFrame = tInfo->m_aBeats[i - 1].m_nKey;
        }

        // 0x4D91A9
        for (auto k = 0u; k < std::min(std::size(tInfo->m_aBeats) - i, 10u); k++) { // Copy beats towards the end
            auto& beat = bi->BeatWindow[10 + i];
            if (beat.m_nKey) {
                beat         =  tInfo->m_aBeats[i + k];
                beat.m_nTime -= tPlayTime;
            }
        }
    }
}

// 0x4D94E0
void CAEAudioHardware::EnableBassEq() {
    m_pStreamingChannel->SetBassEQ(m_nBassSet, m_fBassEqGain);
}

// 0x4D94D0
void CAEAudioHardware::DisableBassEq() {
    m_pStreamingChannel->SetBassEQ(0, 0.f);
}

// 0x4D9500
void CAEAudioHardware::SetChannelFlags(int16 channel, uint16 channelId, int16 flags) {
    if (channel >= 0 && channelId < m_anNumChannelsInSlot[channel])
        m_awChannelFlags[channel + channelId] = flags;
}

// 0x4D9530
void CAEAudioHardware::SetMusicMasterScalingFactor(float factor) {
    m_fMusicMasterScalingFactor = factor;
}

// 0x4D9540
void CAEAudioHardware::SetEffectsMasterScalingFactor(float factor) {
    m_fEffectMasterScalingFactor = factor;
}

// 0x4D9550
void CAEAudioHardware::SetMusicFaderScalingFactor(float factor) {
    m_fMusicFaderScalingFactor = factor;
}

// 0x4D9560
void CAEAudioHardware::SetEffectsFaderScalingFactor(float factor) {
    m_fEffectsFaderScalingFactor = factor;
}

// 0x4D9570
float CAEAudioHardware::GetEffectsMasterScalingFactor() const {
    return m_fEffectMasterScalingFactor;
}

// 0x4D9580
float CAEAudioHardware::GetMusicMasterScalingFactor() const {
    return m_fMusicMasterScalingFactor;
}

// 0x4D9590
float CAEAudioHardware::GetEffectsFaderScalingFactor() const {
    return m_fEffectsFaderScalingFactor;
}

// 0x4D95A0
void CAEAudioHardware::SetNonStreamFaderScalingFactor(float factor) {
    m_fNonStreamFaderScalingFactor = factor;
}

// 0x4D95B0
void CAEAudioHardware::SetStreamFaderScalingFactor(float factor) {
    m_fStreamFaderScalingFactor = factor;
}

// 0x4D95C0
bool CAEAudioHardware::IsStreamingFromDVD() {
    return m_pMP3TrackLoader->m_bStreamingFromDVD;
}

// 0x4D95D0
char CAEAudioHardware::GetDVDDriveLetter() {
    return m_pMP3TrackLoader->m_pszDvdDrivePath[0];
}

// 0x4D95E0
bool CAEAudioHardware::CheckDVD() {
    return m_pMP3TrackLoader->IsCurrentAudioStreamAvailable();
}

// 0x4D95F0
void CAEAudioHardware::PauseAllSounds() {
    plugin::CallMethod<0x4D95F0, CAEAudioHardware*>(this);
}

// 0x4D9630
void CAEAudioHardware::ResumeAllSounds() {
    plugin::CallMethod<0x4D9630, CAEAudioHardware*>(this);
}

// 0x4D8490
void CAEAudioHardware::Query3DSoundEffects() {
    return plugin::CallMethod<0x4D8490, CAEAudioHardware*>(this);
}

// 0x4D9870
void CAEAudioHardware::Service() {
    plugin::CallMethod<0x4D9870, CAEAudioHardware*>(this);
}
