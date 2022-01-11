#include "StdInc.h"

#include "AEAudioHardware.h"

CAEAudioHardware& AEAudioHardware = *reinterpret_cast<CAEAudioHardware*>(0xB5F8B8);

void CAEAudioHardware::InjectHooks() {
    using namespace ReversibleHooks;
    // Install("CAEAudioHardware", "CAEAudioHardware", 0x4D83E0, &CAEAudioHardware::Constructor);
    // Install("CAEAudioHardware", "~CAEAudioHardware", 0x4D83A0, &CAEAudioHardware::Destructor);
    Install("CAEAudioHardware", "AllocateChannels", 0x5B9340, &CAEAudioHardware::AllocateChannels);
    Install("CAEAudioHardware", "RequestVirtualChannelSoundInfo", 0x4D8E60, &CAEAudioHardware::RequestVirtualChannelSoundInfo);
    // Install("CAEAudioHardware", "Query3DSoundEffects", 0x4D8490, &CAEAudioHardware::Query3DSoundEffects);
    Install("CAEAudioHardware", "GetNumAvailableChannels", 0x4D8810, &CAEAudioHardware::GetNumAvailableChannels);
    // Install("CAEAudioHardware", "GetChannelPlayTimes", 0x4D8820, &CAEAudioHardware::GetChannelPlayTimes);
    Install("CAEAudioHardware", "SetChannelVolume", 0x4D8870, &CAEAudioHardware::SetChannelVolume);
    Install("CAEAudioHardware", "LoadSoundBank", 0x4D88A0, &CAEAudioHardware::LoadSoundBank);
    // Install("CAEAudioHardware", "IsSoundBankLoaded", 0x4D88C0, &CAEAudioHardware::IsSoundBankLoaded);
    // Install("CAEAudioHardware", "GetSoundBankLoadingStatus", 0x4D88D0, &CAEAudioHardware::GetSoundBankLoadingStatus);
    Install("CAEAudioHardware", "LoadSound", 0x4D8ED0, &CAEAudioHardware::LoadSound);
    // Install("CAEAudioHardware", "IsSoundLoaded", 0x4D8EF0, &CAEAudioHardware::IsSoundLoaded);
    // Install("CAEAudioHardware", "GetSoundLoadingStatus", 0x4D8F00, &CAEAudioHardware::GetSoundLoadingStatus);
    // Install("CAEAudioHardware", "StopSound", 0x4D88E0, &CAEAudioHardware::StopSound);
    // Install("CAEAudioHardware", "SetChannelPosition", 0x4D8920, &CAEAudioHardware::SetChannelPosition);
    // Install("CAEAudioHardware", "SetChannelFrequencyScalingFactor", 0x4D8960, &CAEAudioHardware::SetChannelFrequencyScalingFactor);
    // Install("CAEAudioHardware", "RescaleChannelVolumes", 0x4D8990, &CAEAudioHardware::RescaleChannelVolumes);
    // Install("CAEAudioHardware", "UpdateReverbEnvironment", 0x4D8DA0, &CAEAudioHardware::UpdateReverbEnvironment);
    // Install("CAEAudioHardware", "GetSoundHeadroom", 0x4D8E30, &CAEAudioHardware::GetSoundHeadroom);
    // Install("CAEAudioHardware", "EnableEffectsLoading", 0x4D8E40, &CAEAudioHardware::EnableEffectsLoading);
    // Install("CAEAudioHardware", "DisableEffectsLoading", 0x4D8E50, &CAEAudioHardware::DisableEffectsLoading);
    // Install("CAEAudioHardware", "RequestVirtualChannelSoundInfo", 0x4D8E60, &CAEAudioHardware::RequestVirtualChannelSoundInfo);
    Install("CAEAudioHardware", "GetVirtualChannelSoundLengths", 0x4D8E90, &CAEAudioHardware::GetVirtualChannelSoundLengths);
    Install("CAEAudioHardware", "GetVirtualChannelSoundLoopStartTimes", 0x4D8EB0, &CAEAudioHardware::GetVirtualChannelSoundLoopStartTimes);
    // Install("CAEAudioHardware", "PlayTrack", 0x4D8F10, &CAEAudioHardware::PlayTrack);
    Install("CAEAudioHardware", "StartTrackPlayback", 0x4D8F30, &CAEAudioHardware::StartTrackPlayback);
    // Install("CAEAudioHardware", "StopTrack", 0x4D8F50, &CAEAudioHardware::StopTrack);
    // Install("CAEAudioHardware", "GetTrackPlayTime", 0x4D8F60, &CAEAudioHardware::GetTrackPlayTime);
    // Install("CAEAudioHardware", "GetTrackLengthMs", 0x4D8F70, &CAEAudioHardware::GetTrackLengthMs);
    // Install("CAEAudioHardware", "GetActiveTrackID", 0x4D8F80, &CAEAudioHardware::GetActiveTrackID);
    // Install("CAEAudioHardware", "GetPlayingTrackID", 0x4D8F90, &CAEAudioHardware::GetPlayingTrackID);
    // Install("CAEAudioHardware", "GetBeatInfo", 0x4D8FA0, &CAEAudioHardware::GetBeatInfo);
    // Install("CAEAudioHardware", "SetBassSetting", 0x4D94A0, &CAEAudioHardware::SetBassSetting);
    // Install("CAEAudioHardware", "DisableBassEq", 0x4D94D0, &CAEAudioHardware::DisableBassEq);
    // Install("CAEAudioHardware", "EnableBassEq", 0x4D94E0, &CAEAudioHardware::EnableBassEq);
    Install("CAEAudioHardware", "SetChannelFlags", 0x4D9500, &CAEAudioHardware::SetChannelFlags);
    Install("CAEAudioHardware", "SetMusicMasterScalingFactor", 0x4D9530, &CAEAudioHardware::SetMusicMasterScalingFactor);
    Install("CAEAudioHardware", "SetEffectsMasterScalingFactor", 0x4D9540, &CAEAudioHardware::SetEffectsMasterScalingFactor);
    Install("CAEAudioHardware", "SetMusicFaderScalingFactor", 0x4D9550, &CAEAudioHardware::SetMusicFaderScalingFactor);
    Install("CAEAudioHardware", "SetEffectsFaderScalingFactor", 0x4D9560, &CAEAudioHardware::SetEffectsFaderScalingFactor);
    Install("CAEAudioHardware", "GetEffectsMasterScalingFactor", 0x4D9570, &CAEAudioHardware::GetEffectsMasterScalingFactor);
    Install("CAEAudioHardware", "GetMusicMasterScalingFactor", 0x4D9580, &CAEAudioHardware::GetMusicMasterScalingFactor);
    Install("CAEAudioHardware", "GetEffectsFaderScalingFactor", 0x4D9590, &CAEAudioHardware::GetEffectsFaderScalingFactor);
    Install("CAEAudioHardware", "SetNonStreamFaderScalingFactor", 0x4D95A0, &CAEAudioHardware::SetNonStreamFaderScalingFactor);
    Install("CAEAudioHardware", "SetStreamFaderScalingFactor", 0x4D95B0, &CAEAudioHardware::SetStreamFaderScalingFactor);
    // Install("CAEAudioHardware", "IsStreamingFromDVD", 0x4D95C0, &CAEAudioHardware::IsStreamingFromDVD);
    // Install("CAEAudioHardware", "GetDVDDriveLetter", 0x4D95D0, &CAEAudioHardware::GetDVDDriveLetter);
    // Install("CAEAudioHardware", "CheckDVD", 0x4D95E0, &CAEAudioHardware::CheckDVD);
    // Install("CAEAudioHardware", "PauseAllSounds", 0x4D95F0, &CAEAudioHardware::PauseAllSounds);
    // Install("CAEAudioHardware", "ResumeAllSounds", 0x4D9630, &CAEAudioHardware::ResumeAllSounds);
    // Install("CAEAudioHardware", "InitDirectSoundListener", 0x4D9640, &CAEAudioHardware::InitDirectSoundListener);
    // Install("CAEAudioHardware", "Terminate", 0x4D97A0, &CAEAudioHardware::Terminate);
    // Install("CAEAudioHardware", "Service", 0x4D9870, &CAEAudioHardware::Service);
    // Install("CAEAudioHardware", "Initialise", 0x4D9930, &CAEAudioHardware::Initialise);
    // Install("CAEAudioHardware", "AllocateChannels", 0x5B9340, &CAEAudioHardware::AllocateChannels);
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
    plugin::CallMethodAndReturn<int32, 0x4D8820, CAEAudioHardware*, int16, int16*>(this, channel, playTimes);
}

// 0x4D8870
void CAEAudioHardware::SetChannelVolume(int16 channel, uint16 channelId, float volume, uint8 a4) {
    if (channel >= 0 && channelId < m_anNumChannelsInSlot[channel])
        m_afChannelVolumes[channel + channelId] = volume;
}

// 0x4D88A0
bool CAEAudioHardware::LoadSoundBank(uint16 bankId, int16 bankSlotId) {
    if (!m_bDisableEffectsLoading) {
        return plugin::CallMethodAndReturn<bool, 0x4E0670>(m_pMP3BankLoader, bankId, bankSlotId);
        // todo: return m_pMP3BankLoader->LoadSoundBank(bankId, bankSlotId);
    }

    return m_bDisableEffectsLoading;
}

// 0x4D88C0
bool CAEAudioHardware::IsSoundBankLoaded(uint16 bankId, int16 bankSlotId) {
    return plugin::CallMethodAndReturn<bool, 0x4D88C0, CAEAudioHardware*, uint16, int16>(this, bankId, bankSlotId);
    // todo: return m_pMP3BankLoader->IsSoundBankLoaded(bankId, bankSlotId);
}

// 0x4D88D0
int8 CAEAudioHardware::GetSoundBankLoadingStatus(uint16 bankId, int16 bankSlotId) {
    return plugin::CallMethodAndReturn<int8, 0x4D88D0, CAEAudioHardware*, uint16, int16>(this, bankId, bankSlotId);
    // todo: return m_pMP3BankLoader->GetSoundBankLoadingStatus(bankId, bankSlotId);
}

// 0x4D8ED0
bool CAEAudioHardware::LoadSound(uint16 bank, uint16 sound, int16 slot) {
    if (!m_bDisableEffectsLoading) {
        return plugin::CallMethodAndReturn<bool, 0x4E07A0>(m_pMP3BankLoader, bank, sound, slot);
        // todo: return m_pMP3BankLoader->LoadSound(bank, sound, slot);
    }

    return m_bDisableEffectsLoading;
}

// 0x4D8EF0
bool CAEAudioHardware::IsSoundLoaded(uint16 bankId, uint16 sfxId, int16 bankSlot) {
    return plugin::CallMethodAndReturn<bool, 0x4D8EF0, CAEAudioHardware*, uint16, uint16, int16>(this, bankId, sfxId, bankSlot);
    // return m_pMP3BankLoader->IsSoundLoaded(bankId, sfxId, bankSlotId);
}

// 0x4D8F00
bool CAEAudioHardware::GetSoundLoadingStatus(uint16 bankId, uint16 sfxId, int16 bankSlot) {
    return plugin::CallMethodAndReturn<bool, 0x4D8F00, CAEAudioHardware*, uint16, uint16, int16>(this, bankId, sfxId, bankSlot);
    // return m_pMP3BankLoader->GetSoundLoadingStatus(bankId, sfxId, bankSlot);
}

// 0x4D88E0
void CAEAudioHardware::StopSound(int16 channel, uint16 channelId) {
    if (channel >= 0 && channelId < m_anNumChannelsInSlot[channel]) {
        auto channel_ = m_aChannels[channel + channelId];
        if (channel_)
            channel_->Stop();
    }
}

// 0x4D8920
void CAEAudioHardware::SetChannelPosition(int16 channel, uint16 channelId, CVector* posn, uint8 unused) {
    if (channel >= 0 && channelId < m_anNumChannelsInSlot[channel]) {
        auto channel_ = m_aChannels[channel + channelId];
        if (channel_)
            channel_->SetPosition(posn);
    }
}

// 0x4D8960
void CAEAudioHardware::SetChannelFrequencyScalingFactor(int16 channel, uint16 channelId, float factor) {
    if (channel >= 0 && channelId < m_anNumChannelsInSlot[channel])
        m_afChannelsFrqScalingFactor[channel + channelId] = factor;
}

// 0x4D8990
void CAEAudioHardware::RescaleChannelVolumes() {
    return plugin::Call<0x4D8990, CAEAudioHardware*>(this);
}

// 0x4D8DA0
void CAEAudioHardware::UpdateReverbEnvironment() {
    plugin::CallMethod<0x4D8DA0, CAEAudioHardware*>(this);
}

// 0x4D8E30
float CAEAudioHardware::GetSoundHeadroom(uint16 sfxId, int16 bankSlotId) {
    return plugin::CallMethodAndReturn<float, 0x4D8E30, CAEAudioHardware*, uint16, int16>(this, sfxId, bankSlotId);
    // return m_pMP3BankLoader->GetSoundHeadroom(sfxId, bankSlotId);
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
    plugin::CallMethod<0x4D8FA0, CAEAudioHardware*, tBeatInfo*>(this, beatInfo);
}

// unused?
// 0x4D94E0
void CAEAudioHardware::EnableBassEq() {
    plugin::CallMethod<0x4D94E0, CAEAudioHardware*>(this);
    // m_pStreamingChannel->SetBassEQ(m_nBassSet, m_fBassEqGain);
}

// 0x4D94D0
void CAEAudioHardware::DisableBassEq() {
    m_pStreamingChannel->SetBassEQ(nullptr, 0);
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
    return plugin::CallMethodAndReturn<bool, 0x4D95C0, CAEAudioHardware*>(this);
    // todo: return m_pMP3TrackLoader->m_bStreamingFromDVD;
}

// 0x4D95D0
char CAEAudioHardware::GetDVDDriveLetter() {
    return plugin::CallMethodAndReturn<char, 0x4D95D0, CAEAudioHardware*>(this);
    // todo: return m_pMP3TrackLoader->m_szDvdDrivePath[0];
}

// 0x4D95E0
bool CAEAudioHardware::CheckDVD() {
    return plugin::CallMethodAndReturn<bool, 0x4D95E0, CAEAudioHardware*>(this);
    // todo: return m_pMP3TrackLoader->IsCurrentAudioStreamAvailable();
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
