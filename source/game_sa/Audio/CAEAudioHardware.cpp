#include "StdInc.h"
#include "CAEAudioHardware.h"

CAEAudioHardware& AEAudioHardware = *reinterpret_cast<CAEAudioHardware*>(0xB5F8B8);

void CAEAudioHardware::InjectHooks()
{
    ReversibleHooks::Install("CAEAudioHardware", "RequestVirtualChannelSoundInfo", 0x4D8E60, &CAEAudioHardware::RequestVirtualChannelSoundInfo);
    ReversibleHooks::Install("CAEAudioHardware", "AllocateChannels", 0x5B9340, &CAEAudioHardware::AllocateChannels);
}

void CAEAudioHardware::PlaySound(short channel,
                                 ushort channelSlot,
                                 ushort soundIdInSlot,
                                 ushort bankSlot,
                                 short playPosition,
                                 short flags,
                                 float speed)
{
    plugin::CallMethod<0x4D86B0, CAEAudioHardware*, short, unsigned short, unsigned short, unsigned short, short, short, float>
        (this, channel, channelSlot, soundIdInSlot, bankSlot, playPosition, flags, speed);
}

void CAEAudioHardware::GetChannelPlayTimes(short channel, short* outArr)
{
    plugin::CallMethod<0x4D8820, CAEAudioHardware*, short, short*>(this, channel, outArr);
}

void CAEAudioHardware::SetChannelVolume(short channel, ushort channelSlot, float volume, uchar unused)
{
    plugin::CallMethod<0x4D8870, CAEAudioHardware*, short, ushort, float, uchar>(this, channel, channelSlot, volume, unused);
}

void CAEAudioHardware::LoadSoundBank(ushort bankId, short bankSlotId)
{
    plugin::CallMethod<0x4D88A0, CAEAudioHardware*, ushort, short>(this, bankId, bankSlotId);
}

void CAEAudioHardware::StopSound(short channel, ushort channelSlot)
{
    plugin::CallMethod<0x4D88E0, CAEAudioHardware*, short, ushort>(this, channel, channelSlot);
}

void CAEAudioHardware::SetChannelPosition(short channel, ushort channelSlot, CVector* vecPos, uchar unused)
{
    plugin::CallMethod<0x4D8920, CAEAudioHardware*, short, ushort, CVector*, uchar>(this, channel, channelSlot, vecPos, unused);
}

void CAEAudioHardware::SetChannelFrequencyScalingFactor(short channel, ushort channelSlot, float freqFactor)
{
    plugin::CallMethod<0x4D8960, CAEAudioHardware*, short, ushort, float>(this, channel, channelSlot, freqFactor);
}

void CAEAudioHardware::Service()
{
    plugin::CallMethod<0x4D9870, CAEAudioHardware*>(this);
}

float CAEAudioHardware::GetSoundHeadroom(ushort soundId, short bankSlotId)
{
    return plugin::CallMethodAndReturn<float, 0x4D8E30, CAEAudioHardware*, ushort, short>(this, soundId, bankSlotId);
}

void CAEAudioHardware::RequestVirtualChannelSoundInfo(ushort soundIndex, ushort soundIdInSlot, ushort bankSlotId)
{
    if (soundIndex >= MAX_NUM_SOUNDS)
        return;

    m_aBankSlotIds[soundIndex] = bankSlotId;
    m_aSoundIdsInSlots[soundIndex] = soundIdInSlot;
}

void CAEAudioHardware::GetVirtualChannelSoundLengths(short* outArr)
{
    plugin::CallMethod<0x4D8E90, CAEAudioHardware*, short*>(this, outArr);
}

void CAEAudioHardware::GetVirtualChannelSoundLoopStartTimes(short* outArr)
{
    plugin::CallMethod<0x4D8EB0, CAEAudioHardware*, short*>(this, outArr);
}

int16_t CAEAudioHardware::AllocateChannels(ushort numChannels)
{
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
