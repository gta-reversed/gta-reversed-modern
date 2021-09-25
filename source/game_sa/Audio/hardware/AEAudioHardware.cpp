#include "StdInc.h"

#include "AEAudioHardware.h"

CAEAudioHardware& AEAudioHardware = *reinterpret_cast<CAEAudioHardware*>(0xB5F8B8);

void CAEAudioHardware::InjectHooks() {
    ReversibleHooks::Install("CAEAudioHardware", "RequestVirtualChannelSoundInfo", 0x4D8E60, &CAEAudioHardware::RequestVirtualChannelSoundInfo);
    ReversibleHooks::Install("CAEAudioHardware", "AllocateChannels", 0x5B9340, &CAEAudioHardware::AllocateChannels);
}

void CAEAudioHardware::PlaySound(int16 channel, uint16 channelSlot, uint16 soundIdInSlot, uint16 bankSlot, int16 playPosition, int16 flags, float speed) {
    plugin::CallMethod<0x4D86B0, CAEAudioHardware*, int16, uint16, uint16, uint16, int16, int16, float>(this, channel, channelSlot, soundIdInSlot, bankSlot, playPosition, flags, speed);
}

void CAEAudioHardware::GetChannelPlayTimes(int16 channel, int16* outArr) {
    plugin::CallMethod<0x4D8820, CAEAudioHardware*, int16, int16*>(this, channel, outArr);
}

void CAEAudioHardware::SetChannelVolume(int16 channel, uint16 channelSlot, float volume, uint8 unused) {
    plugin::CallMethod<0x4D8870, CAEAudioHardware*, int16, uint16, float, uint8>(this, channel, channelSlot, volume, unused);
}

void CAEAudioHardware::LoadSoundBank(uint16 bankId, int16 bankSlotId) {
    plugin::CallMethod<0x4D88A0, CAEAudioHardware*, uint16, int16>(this, bankId, bankSlotId);
}

bool CAEAudioHardware::IsSoundBankLoaded(uint16 bankId, int16 bankSlotId) {
    return plugin::CallMethodAndReturn<bool, 0x4D88C0, CAEAudioHardware*, uint16, int16>(this, bankId, bankSlotId);
}

void CAEAudioHardware::StopSound(int16 channel, uint16 channelSlot) {
    plugin::CallMethod<0x4D88E0, CAEAudioHardware*, int16, uint16>(this, channel, channelSlot);
}

void CAEAudioHardware::SetChannelPosition(int16 channel, uint16 channelSlot, CVector* vecPos, uint8 unused) {
    plugin::CallMethod<0x4D8920, CAEAudioHardware*, int16, uint16, CVector*, uint8>(this, channel, channelSlot, vecPos, unused);
}

void CAEAudioHardware::SetChannelFrequencyScalingFactor(int16 channel, uint16 channelSlot, float freqFactor) {
    plugin::CallMethod<0x4D8960, CAEAudioHardware*, int16, uint16, float>(this, channel, channelSlot, freqFactor);
}

void CAEAudioHardware::Service() {
    plugin::CallMethod<0x4D9870, CAEAudioHardware*>(this);
}

float CAEAudioHardware::GetSoundHeadroom(uint16 soundId, int16 bankSlotId) {
    return plugin::CallMethodAndReturn<float, 0x4D8E30, CAEAudioHardware*, uint16, int16>(this, soundId, bankSlotId);
}

void CAEAudioHardware::RequestVirtualChannelSoundInfo(uint16 soundIndex, uint16 soundIdInSlot, uint16 bankSlotId) {
    if (soundIndex >= MAX_NUM_SOUNDS)
        return;

    m_aBankSlotIds[soundIndex] = bankSlotId;
    m_aSoundIdsInSlots[soundIndex] = soundIdInSlot;
}

void CAEAudioHardware::GetVirtualChannelSoundLengths(int16* outArr) {
    plugin::CallMethod<0x4D8E90, CAEAudioHardware*, int16*>(this, outArr);
}

void CAEAudioHardware::GetVirtualChannelSoundLoopStartTimes(int16* outArr) {
    plugin::CallMethod<0x4D8EB0, CAEAudioHardware*, int16*>(this, outArr);
}

int16 CAEAudioHardware::AllocateChannels(uint16 numChannels) {
    if (!numChannels || numChannels > m_wNumAvailableChannels)
        return -1;

    auto slot = 0;
    while (m_anNumChannelsInSlot[slot] && slot < MAX_NUM_AUDIO_CHANNELS)
        slot += m_anNumChannelsInSlot[slot];

    if (slot >= MAX_NUM_AUDIO_CHANNELS)
        return -1;

    m_anNumChannelsInSlot[slot] = numChannels;
    m_wNumAvailableChannels -= numChannels;
    return slot;
}

void CAEAudioHardware::LoadSound(uint16 bank, uint16 sound, int16 slot) {
    return plugin::CallMethod<0x4D8ED0, CAEAudioHardware*, uint16, uint16, int16>(this, bank, sound, slot);
}
