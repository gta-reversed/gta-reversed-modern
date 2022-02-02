/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "AEWeaponAudioEntity.h"

#include "AESoundManager.h"
#include "AEAudioHardware.h"

// 0x5DE990
CAEWeaponAudioEntity::CAEWeaponAudioEntity() : CAEAudioEntity() {
    Clear();

    m_pPed = nullptr;
    m_Physical = nullptr;
}

// 0x507560
CAEWeaponAudioEntity::~CAEWeaponAudioEntity() {
    Clear();
}

// 0x503450
void CAEWeaponAudioEntity::Initialise() {
    m_nState = 3;
    m_nChainsawSoundState = 4;
    if (!AudioEngine.IsLoadingTuneActive())
        AEAudioHardware.LoadSoundBank(143, 5);
}

void CAEWeaponAudioEntity::AddAudioEvent(int32 audioEventId) {
    plugin::CallMethod<0x4E69F0, CAEWeaponAudioEntity*, int32>(this, audioEventId);
}

// 0x503480
void CAEWeaponAudioEntity::Terminate() {
    plugin::CallMethod<0x503480, CAEWeaponAudioEntity*>(this);
}

// 0x503490
void CAEWeaponAudioEntity::Reset() {
    AESoundManager.CancelSoundsOwnedByAudioEntity(this, true);
    Clear();
}

// 0x504F80
void CAEWeaponAudioEntity::WeaponFire(eWeaponType type, CPhysical* entity, int32 audioEventId) {
    if (!entity)
        return;

    switch (type) {
    case WEAPON_PISTOL:
        return PlayGunSounds(entity, 52, 53, 6, 7, 8, audioEventId, 0.0f, 1.41421f, 1.0f);

    case WEAPON_PISTOL_SILENCED:
        return PlayGunSounds(entity, 76, 77, 24, 24, -1, audioEventId, -7.0f, 1.0f, 1.0f);

    case WEAPON_DESERT_EAGLE:
        return PlayGunSounds(entity, 52, 53, 6, 7, 8, audioEventId, 0.0f, 0.94387001f, 1.0f);

    case WEAPON_SHOTGUN:
    case WEAPON_SPAS12_SHOTGUN:
        return PlayGunSounds(entity, 73, 74, 21, 22, 23, audioEventId, 0.0f, 1.0f, 1.0f);

    case WEAPON_SAWNOFF_SHOTGUN:
        return PlayGunSounds(entity, 73, 74, 21, 22, 23, audioEventId, 0.0f, 0.79369998f, 0.93f);

    case WEAPON_MICRO_UZI:
        return PlayGunSounds(entity, 29, 30, 0, 1, 2, audioEventId, 0.0f, 1.0f, 1.0f);

    case WEAPON_MP5:
        return PlayGunSounds(entity, 29, 30, 17, 18, 2, audioEventId, 0.0f, 1.0f, 1.0f);

    case WEAPON_AK47:
    case WEAPON_M4:
        return PlayGunSounds(entity, 33, 53, 3, 4, 5, audioEventId, 0.0f, 1.0f, 1.0f);

    case WEAPON_TEC9:
        return PlayGunSounds(entity, 29, 30, 0, 1, 2, audioEventId, 0.0f, 1.25992, 1.0f);

    case WEAPON_COUNTRYRIFLE:
        return PlayGunSounds(entity, 52, 53, 26, 27, 23, audioEventId, 0.0f, 0.89f, 1.0f);

    case WEAPON_SNIPERRIFLE:
        return PlayGunSounds(entity, 52, 53, 26, 27, 23, audioEventId, 0.0f, 1.0f, 1.0f);

    case WEAPON_FLAMETHROWER:
        if (!m_nFlameThrowerLastPlayedTime)
            PlayFlameThrowerSounds(entity, 83, 26, audioEventId, -14.0f, 1.0f);
        m_nFlameThrowerLastPlayedTime = CTimer::GetTimeInMS();
        break;

    case WEAPON_MINIGUN:
        return PlayMiniGunFireSounds(entity, audioEventId);

    case WEAPON_DETONATOR:
        return PlayGunSounds(entity, 49, -1, -1, -1, -1, audioEventId, -14.0f, 1.0f, 1.0f);

    case WEAPON_SPRAYCAN:
        if (!m_nSpraycanLastPlayedTime)
            PlayWeaponLoopSound(entity, 28, audioEventId, -20.0f, 1.0f, 3u);

        m_nSpraycanLastPlayedTime = CTimer::GetTimeInMS();
        break;

    case WEAPON_EXTINGUISHER:
        if (!m_nExtinguisherLastPlayedTime)
            PlayWeaponLoopSound(entity, 9, audioEventId, -20.0f, 0.79369998f, 4u);

        m_nExtinguisherLastPlayedTime = CTimer::GetTimeInMS();
        break;

    case WEAPON_CAMERA:
        return PlayCameraSound(entity, audioEventId, -14.0);

    case WEAPON_NIGHTVISION:
    case WEAPON_INFRARED:
        return PlayGoggleSound(64, audioEventId);

    default:
        return;
    }
}

// 0x503690
void CAEWeaponAudioEntity::WeaponReload(eWeaponType type, CPhysical* entity, int32 audioEventId) {
    if (!entity)
        return;

    if (!AEAudioHardware.IsSoundBankLoaded(143, 5)) {
        if (!AudioEngine.IsLoadingTuneActive()) {
            AEAudioHardware.LoadSoundBank(143, 5);
            return;
        }
        return;
    }

    int16 soundType;
    float volumeOffset = 0.0f;

    switch (type) {
    case WEAPON_PISTOL:
    case WEAPON_PISTOL_SILENCED:
        soundType = audioEventId != AE_WEAPON_RELOAD_A ? 66 : 55;
        break;
    case WEAPON_DESERT_EAGLE:
        soundType = 4 * (audioEventId == AE_WEAPON_RELOAD_A) + 51;
        break;
    case WEAPON_SHOTGUN:
    case WEAPON_SPAS12_SHOTGUN:
        soundType = (audioEventId != AE_WEAPON_RELOAD_A) + 71;
        break;
    case WEAPON_SAWNOFF_SHOTGUN:
        soundType = (audioEventId != AE_WEAPON_RELOAD_A) + 69;
        break;
    case WEAPON_MICRO_UZI:
    case WEAPON_MP5:
    case WEAPON_TEC9:
        soundType = (audioEventId != AE_WEAPON_RELOAD_A) + 84;
        break;
    case WEAPON_AK47:
    case WEAPON_M4:
        soundType = (audioEventId != AE_WEAPON_RELOAD_A) + 31;
        break;
    case WEAPON_COUNTRYRIFLE:
        if (audioEventId != AE_WEAPON_RELOAD_A)
            return;
        soundType = 32;
        volumeOffset = -6.0f;
        break;
    case WEAPON_SNIPERRIFLE:
        soundType = audioEventId != AE_WEAPON_RELOAD_A ? 32 : 55;
        break;
    default:
        return;
    }

    auto volume = CAEAudioEntity::m_pAudioEventVolumes[audioEventId] + volumeOffset;

    m_tempSound.Initialise(5, soundType, this, entity->GetPosition(), volume, 0.66f, 1.0f, 1.0f, 0, SOUND_LIFESPAN_TIED_TO_PHYSICAL_ENTITY, 0.0f, 0);
    m_tempSound.RegisterWithPhysicalEntity(entity);
    AESoundManager.RequestNewSound(&m_tempSound);
}

// 0x503B20
void CAEWeaponAudioEntity::ReportStealthKill(eWeaponType type, CPhysical* entity, int32 audioEventId) {
    plugin::CallMethod<0x503B20, CAEWeaponAudioEntity*, eWeaponType, CPhysical*, int32>(this, type, entity, audioEventId);
}

// 0x503910
void CAEWeaponAudioEntity::ReportChainsawEvent(CPhysical* entity, int32 audioEventId) {
    plugin::CallMethod<0x503910, CAEWeaponAudioEntity*, CPhysical*, int32>(this, entity, audioEventId);
}

// 0x504610
void CAEWeaponAudioEntity::PlayWeaponLoopSound(CPhysical* arg0, int16 sfxId, int32 audioEventId, float audability, float speed, int32 finalEvent) {
    plugin::CallMethod<0x504610, CAEWeaponAudioEntity*, CPhysical*, int16, int32, float, float, int32>(this, arg0, sfxId, audioEventId, audability, speed, finalEvent);
}

// 0x504960
void CAEWeaponAudioEntity::PlayMiniGunStopSound(CPhysical* entity) {
    plugin::CallMethod<0x504960, CAEWeaponAudioEntity*, CPhysical*>(this, entity);
}

// 0x5047C0
void CAEWeaponAudioEntity::PlayMiniGunFireSounds(CPhysical* entity, int32 audioEventId) {
    plugin::CallMethod<0x5047C0, CAEWeaponAudioEntity*, CPhysical*, int32>(this, entity, audioEventId);
}

// 0x503CE0
void CAEWeaponAudioEntity::PlayGunSounds(CPhysical* entity, int16 emptySfxId, int16 farSfxId2, int16 highPitchSfxId3, int16 lowPitchSfxId4, int16 echoSfxId5, int32 audioEventId, float volumeChange, float speed1, float speed2) {
    plugin::CallMethod<0x503CE0, CAEWeaponAudioEntity*, CPhysical*, int16, int16, int16, int16, int16, int32, float, float, float>(
        this, entity, emptySfxId, farSfxId2, highPitchSfxId3, lowPitchSfxId4, echoSfxId5, audioEventId, volumeChange, speed1, speed2);
}

// 0x503500
void CAEWeaponAudioEntity::PlayGoggleSound(int16 sfxId, int32 audioEventId) {
    plugin::CallMethod<0x503500, CAEWeaponAudioEntity*, int16, int32>(this, sfxId, audioEventId);
}

// 0x504470
void CAEWeaponAudioEntity::PlayFlameThrowerSounds(CPhysical* entity, int16 sfx1, int16 sfx2, int32 audioEventId, float audability, float speed) {
    plugin::CallMethod<0x504470, CAEWeaponAudioEntity*, CPhysical*, int16, int16, int32, float, float>(this, entity, sfx1, sfx2, audioEventId, audability, speed);
}

// 0x503870
void CAEWeaponAudioEntity::PlayFlameThrowerIdleGasLoop(CPhysical* entity) {
    plugin::CallMethod<0x503870, CAEWeaponAudioEntity*, CPhysical*>(this, entity);
}

// 0x5034E0
void CAEWeaponAudioEntity::StopFlameThrowerIdleGasLoop() {
    plugin::CallMethod<0x5034E0, CAEWeaponAudioEntity*>(this);
}

// 0x504AA0
void CAEWeaponAudioEntity::PlayChainsawStopSound(CPhysical* entity) {
    plugin::CallMethod<0x504AA0, CAEWeaponAudioEntity*, CPhysical*>(this, entity);
}

// 0x5046F0
void CAEWeaponAudioEntity::PlayCameraSound(CPhysical* entity, int32 audioEventId, float audability) {
    plugin::CallMethod<0x5046F0, CAEWeaponAudioEntity*, CPhysical*, int32, float>(this, entity, audioEventId, audability);
}

// 0x504B70
void CAEWeaponAudioEntity::UpdateParameters(CAESound *sound, int16 curPlayPos) {
    plugin::CallMethod<0x504B70, CAEWeaponAudioEntity*, CAESound*, int16>(this, sound, curPlayPos);
}

void CAEWeaponAudioEntity::InjectHooks() {
    RH_ScopedClass(CAEWeaponAudioEntity);
    RH_ScopedCategory("Audio/Entities");

    // RH_ScopedInstall(Constructor, 0x5DE990);
    // RH_ScopedInstall(Destructor, 0x507560);
    RH_ScopedInstall(Initialise, 0x503450);
    RH_ScopedInstall(Reset, 0x503490);
    // RH_ScopedInstall(Terminate, 0x503480);
    RH_ScopedInstall(WeaponFire, 0x504F80);
    RH_ScopedInstall(WeaponReload, 0x503690);
    // RH_ScopedInstall(PlayChainsawStopSound, 0x504AA0);
    // RH_ScopedInstall(PlayMiniGunStopSound, 0x504960);
    // RH_ScopedInstall(PlayMiniGunFireSounds, 0x5047C0);
    // RH_ScopedInstall(PlayCameraSound, 0x5046F0);
    // RH_ScopedInstall(PlayWeaponLoopSound, 0x504610);
    // RH_ScopedInstall(PlayFlameThrowerSounds, 0x504470);
    // RH_ScopedInstall(PlayGunSounds, 0x503CE0);
    // RH_ScopedInstall(ReportStealthKill, 0x503B20);
    // RH_ScopedInstall(ReportChainsawEvent, 0x503910);
    // RH_ScopedInstall(PlayFlameThrowerIdleGasLoop, 0x503870);
    // RH_ScopedInstall(PlayGoggleSound, 0x503500);
    // RH_ScopedInstall(StopFlameThrowerIdleGasLoop, 0x5034E0);
    // RH_ScopedInstall(UpdateParameters, 0x504B70);

}

CAEWeaponAudioEntity* CAEWeaponAudioEntity::Constructor() {
    this->CAEWeaponAudioEntity::CAEWeaponAudioEntity();
    return this;
}

CAEWeaponAudioEntity* CAEWeaponAudioEntity::Destructor() {
    this->CAEWeaponAudioEntity::~CAEWeaponAudioEntity();
    return this;
}

// 0x504B70
void CAEWeaponAudioEntity::UpdateParameters_Reversed(CAESound *sound, int16 curPlayPos) {
    CAEWeaponAudioEntity::UpdateParameters(sound, curPlayPos);
}