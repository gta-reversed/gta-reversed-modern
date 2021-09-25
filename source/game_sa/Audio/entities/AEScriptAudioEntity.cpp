#include "StdInc.h"

#include "AEScriptAudioEntity.h"

// 0x5074D0
CAEScriptAudioEntity::CAEScriptAudioEntity() {
    plugin::CallMethod<0x5074D0, CAEScriptAudioEntity*>(this);
}

// 0x5B9B60
void CAEScriptAudioEntity::Initialise() {
    for (auto& link : wavLinks) {
        link.Init();
    }
}

// 0x4EC150
void CAEScriptAudioEntity::Reset() {
    plugin::CallMethod<0x4EC150, CAEScriptAudioEntity*>(this);
}

// 0x0
void CAEScriptAudioEntity::AddAudioEvent(int32) {
    /* Android NOP */
}

// 0x4EC100
CVector* CAEScriptAudioEntity::AttachMissionAudioToPhysical(uint8 sampleId, CPhysical* physical) {
    return plugin::CallMethodAndReturn<CVector*, 0x4EC100, CAEScriptAudioEntity*, uint8, CPhysical*>(this, sampleId, physical);
}

// 0x4EC040
void CAEScriptAudioEntity::ClearMissionAudio(uint8 sampleId) {
    plugin::CallMethod<0x4EC040, CAEScriptAudioEntity*, uint8>(this, sampleId);
}

// 0x4EBFE0
bool CAEScriptAudioEntity::IsMissionAudioSampleFinished(uint8 sampleId) {
    return plugin::CallMethodAndReturn<bool, 0x4EBFE0, uint8>(sampleId);
}

// 0x4EBF60
int8 CAEScriptAudioEntity::GetMissionAudioLoadingStatus(uint8 sampleId) {
    return plugin::CallMethodAndReturn<int8, 0x4EBF60, CAEScriptAudioEntity*, uint8>(this, sampleId);
}

// 0x4EC020
int32 CAEScriptAudioEntity::GetMissionAudioEvent(uint8 sampleId) {
    return wavLinks[sampleId].m_nAudioEvent;
}

// 0x4EC0C0
void CAEScriptAudioEntity::SetMissionAudioPosition(uint8 sampleId, CVector& posn) {
    plugin::CallMethod<0x4EC0C0, CAEScriptAudioEntity*, uint8, CVector&>(this, sampleId, posn);
}

// 0x4EC4D0
CVector* CAEScriptAudioEntity::GetMissionAudioPosition(uint8 sampleId) {
    return plugin::CallMethodAndReturn<CVector*, 0x4EC4D0, CAEScriptAudioEntity*, uint8>(this, sampleId);
}

// 0x4EC6D0
void CAEScriptAudioEntity::PlayMissionBankSound(uint8 sampleId, CVector& posn, CPhysical* physical, int16 a4, uint8 a5, uint8 a6, float a7, float a8, float a9) {
    plugin::CallMethod<0x4EC6D0, CAEScriptAudioEntity*, uint8, CVector&, CPhysical*, int16, uint8, uint8, float, float, float>(this, sampleId, posn, physical, a4, a5, a6, a7, a8, a9);
}

// 0x4EC550
void CAEScriptAudioEntity::PlayResidentSoundEvent(int16 a1, int16 a2, int16 a3, uint16 a4, CVector& posn, CPhysical* physical, float a7, float a8, int16 a9, float a10) {
    plugin::CallMethod<0x4EC550, CAEScriptAudioEntity*, int16, int16, int16, uint16, CVector, CPhysical*, float, float, int16, float>(this, a1, a2, a3, a4, posn, physical, a7, a8, a9, a10);
}

// 0x4EC270
void CAEScriptAudioEntity::PlayLoadedMissionAudio(uint8 sampleId) {
    plugin::CallMethod<0x4EC270, CAEScriptAudioEntity*, uint8>(this, sampleId);
}

// 0x4EC190
void CAEScriptAudioEntity::PreloadMissionAudio(uint8 sampleId, int32 a2) {
    plugin::CallMethod<0x4EC190, CAEScriptAudioEntity*>(this, sampleId, a2);
}

// 0x4ECCF0
void CAEScriptAudioEntity::ProcessMissionAudioEvent(eAudioEvents eventId, CVector& coords, CPhysical* physical, float a6, float a7) {
    plugin::CallMethod<0x4ECCF0, CAEScriptAudioEntity*, eAudioEvents, CVector&, CPhysical*, float, float>(this, eventId, coords, physical, a6, a7);
}

// 0x4EE960
void CAEScriptAudioEntity::ReportMissionAudioEvent(eAudioEvents eventId, CPhysical* physical, float a4, float a5) {
    CVector coords{-1000.0f, -1000.0f, -1000.0f};
    ProcessMissionAudioEvent(eventId, coords, physical, a4, a5);
}

// 0x4EE940
void CAEScriptAudioEntity::ReportMissionAudioEvent(eAudioEvents eventId, CVector& coords) {
    ProcessMissionAudioEvent(eventId, coords, nullptr, 0.0f, 1.0f);
}

// 0x4EC970
void CAEScriptAudioEntity::UpdateParameters(CAESound* sound, int16 curPlayPos) {
    plugin::CallMethod<0x4EC970, CAEScriptAudioEntity*, CAESound*, int16>(this, sound, curPlayPos);
}

void CAEScriptAudioEntity::InjectHooks() {
    using namespace ReversibleHooks;
    // Install("CAEScriptAudioEntity", "CAEScriptAudioEntity", 0x5074D0, &CAEScriptAudioEntity::Constructor);
    Install("CAEScriptAudioEntity", "Initialise", 0x5B9B60, &CAEScriptAudioEntity::Initialise);
    // Install("CAEScriptAudioEntity", "Reset", 0x4EC150, &CAEScriptAudioEntity::Reset);
    // Install("CAEScriptAudioEntity", "GetMissionAudioLoadingStatus", 0x4EBF60, &CAEScriptAudioEntity::GetMissionAudioLoadingStatus);
    // Install("CAEScriptAudioEntity", "IsMissionAudioSampleFinished", 0x4EBFE0, &CAEScriptAudioEntity::IsMissionAudioSampleFinished);
    // Install("CAEScriptAudioEntity", "GetMissionAudioEvent", 0x4EC020, &CAEScriptAudioEntity::GetMissionAudioEvent);
    // Install("CAEScriptAudioEntity", "ClearMissionAudio", 0x4EC040, &CAEScriptAudioEntity::ClearMissionAudio);
    // Install("CAEScriptAudioEntity", "SetMissionAudioPosition", 0x4EC0C0, &CAEScriptAudioEntity::SetMissionAudioPosition);
    // Install("CAEScriptAudioEntity", "AttachMissionAudioToPhysical", 0x4EC100, &CAEScriptAudioEntity::AttachMissionAudioToPhysical);
    // Install("CAEScriptAudioEntity", "PreloadMissionAudio", 0x4EC190, &CAEScriptAudioEntity::PreloadMissionAudio);
    // Install("CAEScriptAudioEntity", "PlayLoadedMissionAudio", 0x4EC270, &CAEScriptAudioEntity::PlayLoadedMissionAudio);
    // Install("CAEScriptAudioEntity", "GetMissionAudioPosition", 0x4EC4D0, &CAEScriptAudioEntity::GetMissionAudioPosition);
    // Install("CAEScriptAudioEntity", "PlayResidentSoundEvent", 0x4EC550, &CAEScriptAudioEntity::PlayResidentSoundEvent);
    // Install("CAEScriptAudioEntity", "PlayMissionBankSound", 0x4EC6D0, &CAEScriptAudioEntity::PlayMissionBankSound);
    // Install("CAEScriptAudioEntity", "ProcessMissionAudioEvent", 0x4ECCF0, &CAEScriptAudioEntity::ProcessMissionAudioEvent);
    // Install("CAEScriptAudioEntity", "ReportMissionAudioEvent_1", 0x4EE960, static_cast<void (CAEScriptAudioEntity::*)(eAudioEvents, CPhysical*, float, float)>(&CAEScriptAudioEntity::ReportMissionAudioEvent));
    // Install("CAEScriptAudioEntity", "ReportMissionAudioEvent_2", 0x4EE940, static_cast<void (CAEScriptAudioEntity::*)(eAudioEvents, CVector&)>(&CAEScriptAudioEntity::ReportMissionAudioEvent));
    // Install("CAEScriptAudioEntity", "UpdateParameters", 0x4EC970, &CAEScriptAudioEntity::UpdateParameters_Reversed);
}

CAEScriptAudioEntity* CAEScriptAudioEntity::Constructor() {
    this->CAEScriptAudioEntity::CAEScriptAudioEntity();
    return this;
}

void CAEScriptAudioEntity::UpdateParameters_Reversed(CAESound* sound, int16 curPlayPos) {
    CAEScriptAudioEntity::UpdateParameters(sound, curPlayPos);
}
