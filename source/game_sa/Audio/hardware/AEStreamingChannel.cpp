#include "StdInc.h"

#include "AEStreamingChannel.h"

// 0x4F1800
CAEStreamingChannel::CAEStreamingChannel(IDirectSound* directSound, uint16 channelId) : CAEAudioChannel(directSound, channelId, 48000, 16) {
    plugin::CallMethod<0x4F1800, CAEStreamingChannel*, IDirectSound*, uint16>(this, directSound, channelId);
}

// 0x4F2200
CAEStreamingChannel::~CAEStreamingChannel() {
    plugin::CallMethod<0x4F2200, CAEStreamingChannel*>(this);
}

// 0x4F22F0
void CAEStreamingChannel::Initialise() {
    plugin::CallMethod<0x4F22F0, CAEStreamingChannel*>(this);
}

// 0x4F1C70
void CAEStreamingChannel::InitialiseSilence() {
    return plugin::CallMethod<0x4F1C70, CAEStreamingChannel*>(this);
}

// 0x4F1FF0
void CAEStreamingChannel::SetReady() {
    plugin::CallMethod<0x4F1FF0, CAEStreamingChannel*>(this);
}

// 0x4F1F30
void CAEStreamingChannel::SetBassEQ(IDirectSoundFXParamEq* paramEq, float gain) {
    plugin::CallMethod<0x4F1F30, CAEStreamingChannel*, IDirectSoundFXParamEq*, float>(this, paramEq, gain);
}

// 0x4F2060
void CAEStreamingChannel::SetFrequencyScalingFactor(float a2) {
    plugin::CallMethod<0x4F2060, CAEStreamingChannel*, float>(this, a2);
}

// 0x4F1870
void CAEStreamingChannel::SynchPlayback() {
    // NOP
}

// 0x4F1E20
uint32 CAEStreamingChannel::FillBuffer(void* buffer, uint32 size) {
    return plugin::CallMethodAndReturn<uint32, 0x4F1E20, CAEStreamingChannel*, void*, uint32>(this, buffer, size);
}

// 0x4F23D0
void CAEStreamingChannel::PrepareStream(CAEStreamingDecoder* stream, int8 arg2, bool bStopCurrent) {
    plugin::CallMethod<0x4F23D0, CAEStreamingChannel*, CAEStreamingDecoder*, int8, bool>(this, stream, arg2, bStopCurrent);
}

// 0x4F1DE0
void CAEStreamingChannel::SetNextStream(CAEStreamingDecoder* decoder) {
    return plugin::CallMethod<0x4F1DE0, CAEStreamingChannel*, CAEStreamingDecoder*>(this, decoder);
}

// 0x4F1A60
int32 CAEStreamingChannel::GetPlayingTrackID() {
    return plugin::CallMethodAndReturn<int32, 0x4F1A60, CAEStreamingChannel*>(this);
}

// 0x4F1A40
int32 CAEStreamingChannel::GetActiveTrackID() {
    return plugin::CallMethodAndReturn<int32, 0x4F1A40, CAEStreamingChannel*>(this);
}

// 0x4F18A0
int32 CAEStreamingChannel::UpdatePlayTime() {
    return plugin::CallMethodAndReturn<int32, 0x4F18A0, CAEStreamingChannel*>(this);
}

// 0x4F1AE0
bool CAEStreamingChannel::AddFX() {
    return plugin::CallMethodAndReturn<bool, 0x4F1AE0, CAEStreamingChannel*>(this);
}

// 0x4F1C20
void CAEStreamingChannel::RemoveFX() {
    plugin::CallMethod<0x4F1C20, CAEStreamingChannel*>(this);
}

// 0x4F2040
bool CAEStreamingChannel::IsSoundPlaying() {
    return plugin::CallMethodAndReturn<bool, 0x4F2040, CAEStreamingChannel*>(this);
}

// 0x4F19E0
int16 CAEStreamingChannel::GetPlayTime() {
    return plugin::CallMethodAndReturn<int16, 0x4F19E0, CAEStreamingChannel*>(this);
}

// 0x4F1880
uint16 CAEStreamingChannel::GetLength() {
    return plugin::CallMethodAndReturn<uint16, 0x4F1880, CAEStreamingChannel*>(this);
}

// 0x4F1D40
void CAEStreamingChannel::Play(int16 a2, int8 a3, float a4) {
    plugin::CallMethod<0x4F1D40, CAEStreamingChannel*, int16, int8, float>(this, a2, a3, a4);
}

// 0x4F2170
void CAEStreamingChannel::Pause() {
    plugin::CallMethod<0x4F2170, CAEStreamingChannel*>(this);
}

// 0x4F1A90
void CAEStreamingChannel::Stop() {
    plugin::CallMethod<0x4F1A90, CAEStreamingChannel*>(this);
}

// 0x4F2550
void CAEStreamingChannel::Service() {
    plugin::CallMethod<0x4F2550, CAEStreamingChannel*>(this);
}

void CAEStreamingChannel::InjectHooks() {
    RH_ScopedClass(CAEStreamingChannel);
    RH_ScopedCategory("Audio/Hardware");

    RH_ScopedInstall(Constructor, 0x4F1800, { .reversed = false });
    // Install("CAEStreamingChannel", "~CAEStreamingChannel", 0x4F2200, static_cast<CAEStreamingChannel*(CAEStreamingChannel::*)()>(&CAEStreamingChannel::Destructor));
    RH_ScopedInstall(SynchPlayback, 0x4F1870, { .reversed = false });
    RH_ScopedInstall(PrepareStream, 0x4F23D0, { .reversed = false });
    RH_ScopedInstall(Initialise, 0x4F22F0, { .reversed = false });
    RH_ScopedInstall(Pause, 0x4F2170, { .reversed = false });
    RH_ScopedInstall(SetReady, 0x4F1FF0, { .reversed = false });
    RH_ScopedInstall(SetBassEQ, 0x4F1F30, { .reversed = false });
    RH_ScopedInstall(FillBuffer, 0x4F1E20, { .reversed = false });
    RH_ScopedInstall(InitialiseSilence, 0x4F1C70, { .reversed = false });
    RH_ScopedInstall(SetNextStream, 0x4F1DE0, { .reversed = false });
    RH_ScopedInstall(AddFX, 0x4F1AE0, { .reversed = false });
    // RH_ScopedOverloadedInstall(Stop, "", 0x4F1A90, int8(CAEStreamingChannel::*)(bool));
    RH_ScopedInstall(GetPlayingTrackID, 0x4F1A60, { .reversed = false });
    RH_ScopedInstall(GetActiveTrackID, 0x4F1A40, { .reversed = false });
    RH_ScopedInstall(UpdatePlayTime, 0x4F18A0, { .reversed = false });
    RH_ScopedInstall(RemoveFX, 0x4F1C20, { .reversed = false });
    RH_ScopedVirtualInstall(Service, 0x4F2550, { .reversed = false });
    RH_ScopedVirtualInstall(IsSoundPlaying, 0x4F2040, { .reversed = false });
    RH_ScopedVirtualInstall(GetPlayTime, 0x4F19E0, { .reversed = false });
    RH_ScopedVirtualInstall(GetLength, 0x4F1880, { .reversed = false });
    RH_ScopedVirtualInstall(Play, 0x4F1D40, { .reversed = false });
    // RH_ScopedVirtualOverloadedInstall(Stop, "", 0x4F21C0, int8(CAEStreamingChannel::*)());
    RH_ScopedVirtualInstall(SetFrequencyScalingFactor, 0x4F2060, { .reversed = false });
}

// 0x4F1800
CAEStreamingChannel* CAEStreamingChannel::Constructor(IDirectSound* directSound, uint16 channelId) {
    this->CAEStreamingChannel::CAEStreamingChannel(directSound, channelId);
    return this;
}

//
CAEStreamingChannel* CAEStreamingChannel::Destructor() {
    this->CAEStreamingChannel::~CAEStreamingChannel();
    return this;
}

// 0x4F2550
void CAEStreamingChannel::Service_Reversed() {
    CAEStreamingChannel::Service();
}

// 0x4F2040
bool CAEStreamingChannel::IsSoundPlaying_Reversed() {
    return CAEStreamingChannel::IsSoundPlaying();
}

// 0x4F19E0
int32 CAEStreamingChannel::GetPlayTime_Reversed() {
    return CAEStreamingChannel::GetPlayTime();
}

// 0x4F1880
int32 CAEStreamingChannel::GetLength_Reversed() {
    return CAEStreamingChannel::GetLength();
}

// 0x4F1D40
void CAEStreamingChannel::Play_Reversed(int16 a2, char a3, float a4) {
    CAEStreamingChannel::Play(a2, a3, a4);
}

// 0x4F21C0
void CAEStreamingChannel::Stop_Reversed() {
    CAEStreamingChannel::Stop();
}

// 0x4F2060
void CAEStreamingChannel::SetFrequencyScalingFactor_Reversed(float a2) {
    CAEStreamingChannel::SetFrequencyScalingFactor(a2);
}
