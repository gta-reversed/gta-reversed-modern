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
    using namespace ReversibleHooks;
    // Install("CAEStreamingChannel", "CAEStreamingChannel", 0x4F1800, &CAEStreamingChannel::Constructor);
    // Install("CAEStreamingChannel", "~CAEStreamingChannel", 0x4F2200, static_cast<CAEStreamingChannel*(CAEStreamingChannel::*)()>(&CAEStreamingChannel::Destructor));
    // Install("CAEStreamingChannel", "SynchPlayback", 0x4F1870, &CAEStreamingChannel::SynchPlayback);
    // Install("CAEStreamingChannel", "PrepareStream", 0x4F23D0, &CAEStreamingChannel::PrepareStream);
    // Install("CAEStreamingChannel", "Initialise", 0x4F22F0, &CAEStreamingChannel::Initialise);
    // Install("CAEStreamingChannel", "Pause", 0x4F2170, &CAEStreamingChannel::Pause);
    // Install("CAEStreamingChannel", "SetReady", 0x4F1FF0, &CAEStreamingChannel::SetReady);
    // Install("CAEStreamingChannel", "SetBassEQ", 0x4F1F30, &CAEStreamingChannel::SetBassEQ);
    // Install("CAEStreamingChannel", "FillBuffer", 0x4F1E20, &CAEStreamingChannel::FillBuffer);
    // Install("CAEStreamingChannel", "InitialiseSilence", 0x4F1C70, &CAEStreamingChannel::InitialiseSilence);
    // Install("CAEStreamingChannel", "SetNextStream", 0x4F1DE0, &CAEStreamingChannel::SetNextStream);
    // Install("CAEStreamingChannel", "AddFX", 0x4F1AE0, &CAEStreamingChannel::AddFX);
    // Install("CAEStreamingChannel", "Stop", 0x4F1A90, static_cast<int8(CAEStreamingChannel::*)(bool)>(&CAEStreamingChannel::Stop));
    // Install("CAEStreamingChannel", "GetPlayingTrackID", 0x4F1A60, &CAEStreamingChannel::GetPlayingTrackID);
    // Install("CAEStreamingChannel", "GetActiveTrackID", 0x4F1A40, &CAEStreamingChannel::GetActiveTrackID);
    // Install("CAEStreamingChannel", "UpdatePlayTime", 0x4F18A0, &CAEStreamingChannel::UpdatePlayTime);
    // Install("CAEStreamingChannel", "RemoveFX", 0x4F1C20, &CAEStreamingChannel::RemoveFX);
    // Install("CAEStreamingChannel", "Service", 0x4F2550, &CAEStreamingChannel::Service_Reversed);
    // Install("CAEStreamingChannel", "IsSoundPlaying", 0x4F2040, &CAEStreamingChannel::IsSoundPlaying_Reversed);
    // Install("CAEStreamingChannel", "GetPlayTime", 0x4F19E0, &CAEStreamingChannel::GetPlayTime_Reversed);
    // Install("CAEStreamingChannel", "GetLength", 0x4F1880, &CAEStreamingChannel::GetLength_Reversed);
    // Install("CAEStreamingChannel", "Play", 0x4F1D40, &CAEStreamingChannel::Play_Reversed);
    // Install("CAEStreamingChannel", "Stop", 0x4F21C0, static_cast<int8(CAEStreamingChannel::*)()>(&CAEStreamingChannel::Stop_Reversed));
    // Install("CAEStreamingChannel", "SetFrequencyScalingFactor", 0x4F2060, &CAEStreamingChannel::SetFrequencyScalingFactor_Reversed);
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
