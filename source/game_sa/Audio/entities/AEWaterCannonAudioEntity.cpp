#include "StdInc.h"

#include "AEWaterCannonAudioEntity.h"
#include "AEAudioHardware.h"

// 0x728A90
CAEWaterCannonAudioEntity::CAEWaterCannonAudioEntity() : CAEAudioEntity() {
    m_bInitialized = false;
}

// 0x503060
void CAEWaterCannonAudioEntity::Initialise(CWaterCannon* waterCannon) {
    return plugin::CallMethod<0x503060, CAEWaterCannonAudioEntity*, CWaterCannon*>(this, waterCannon);
    /*
    ??? m_pEntity = (CEntity*)(&waterCannon);
    ClearSplashInfo();
    m_bInitialized = true;
    */
}

// 0x
void CAEWaterCannonAudioEntity::Terminate() {
    assert(false && "Not implemented.");
}

// ANDROID IDB 0x3D2F00
void CAEWaterCannonAudioEntity::StaticInitialise() {
    // NOP
}

// unused
// 0x
void CAEWaterCannonAudioEntity::AddAudioEvent(int32, CVector&) {
    // NOP
}

// 0x502F50
void CAEWaterCannonAudioEntity::SetSplashInfo(CVector posn, float magnitude) {
    m_vecPosn = posn;
    m_bSplashInfoEnabled = true;
    m_nSplashMagnitude = magnitude;
}

// 0x502F20
void CAEWaterCannonAudioEntity::ClearSplashInfo() {
    m_vecPosn.Set(0.0f, 0.0f, 0.0f);
    m_bSplashInfoEnabled = false;
    m_nSplashMagnitude = 0;
}

// 0x502EF0
void CAEWaterCannonAudioEntity::UpdateParameters(CAESound* sound, int16 curPlayPos) {
    plugin::CallMethod<0x502EF0, CAEWaterCannonAudioEntity*, CAESound*, int16>(this, sound, curPlayPos);
}

// 0x502F80
void CAEWaterCannonAudioEntity::UpdateGenericWaterCannonSound(bool splashInfoEnabled, int16 a3, int16 bankSlotId, int16 sfxId, float speed, float volume, CVector posn, float soundDistance) {
    plugin::CallMethod<0x502F80, CAEWaterCannonAudioEntity*, bool, int16, int16, int16, float, float, CVector, float>(this, splashInfoEnabled, a3, bankSlotId, sfxId, speed, volume, posn, soundDistance);
}

// 0x5030D0
void CAEWaterCannonAudioEntity::Service() {
    plugin::CallMethod<0x5030D0, CAEWaterCannonAudioEntity*>(this);
}

void CAEWaterCannonAudioEntity::InjectHooks() {
    RH_ScopedClass(CAEWaterCannonAudioEntity);
    RH_ScopedCategory("Audio/Entities");

    RH_ScopedInstall(Constructor, 0x728A90);
    // RH_ScopedInstall(Initialise, 0x503060);
    // Install("CAEWaterCannonAudioEntity", "Terminate", 0x, &CAEWaterCannonAudioEntity::Terminate);
    // RH_ScopedInstall(Service, 0x5030D0);
    RH_ScopedInstall(SetSplashInfo, 0x502F50);
    RH_ScopedInstall(ClearSplashInfo, 0x502F20);
    // RH_ScopedInstall(UpdateParameters_Reversed, 0x502EF0);
}

CAEWaterCannonAudioEntity* CAEWaterCannonAudioEntity::Constructor() {
    this->CAEWaterCannonAudioEntity::CAEWaterCannonAudioEntity();
    return this;
}

void CAEWaterCannonAudioEntity::UpdateParameters_Reversed(CAESound* sound, int16 curPlayPos) {
    CAEWaterCannonAudioEntity::UpdateParameters(sound, curPlayPos);
}
