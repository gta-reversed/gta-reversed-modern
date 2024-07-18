/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "AEWeaponAudioEntity.h"
#include "AEAudioEnvironment.h"
#include "AESoundManager.h"
#include "AEAudioHardware.h"
#include "AEAudioUtility.h"

constexpr std::array<float, 2> gfWeaponPlaneFrequencyVariations{ 1.08f, 1.0f };

void CAEWeaponAudioEntity::InjectHooks() {
    RH_ScopedClass(CAEWeaponAudioEntity);
    RH_ScopedCategory("Audio/Entities");

    RH_ScopedInstall(Constructor, 0x5DE990);
    RH_ScopedInstall(Destructor, 0x507560);
    RH_ScopedInstall(Initialise, 0x503450);
    RH_ScopedInstall(Reset, 0x503490);
    RH_ScopedInstall(Terminate, 0x503480);
    RH_ScopedInstall(WeaponFire, 0x504F80);
    RH_ScopedInstall(WeaponReload, 0x503690);
    RH_ScopedInstall(PlayChainsawStopSound, 0x504AA0);
    RH_ScopedInstall(PlayMiniGunStopSound, 0x504960);
    RH_ScopedInstall(PlayMiniGunFireSounds, 0x5047C0);
    RH_ScopedInstall(PlayCameraSound, 0x5046F0);
    RH_ScopedInstall(PlayWeaponLoopSound, 0x504610);
    RH_ScopedInstall(PlayFlameThrowerSounds, 0x504470, { .reversed = false });
    RH_ScopedInstall(PlayGunSounds, 0x503CE0);
    RH_ScopedInstall(ReportStealthKill, 0x503B20);
    RH_ScopedInstall(ReportChainsawEvent, 0x503910, { .reversed = false });
    RH_ScopedInstall(PlayFlameThrowerIdleGasLoop, 0x503870);
    RH_ScopedInstall(PlayGoggleSound, 0x503500);
    RH_ScopedInstall(StopFlameThrowerIdleGasLoop, 0x5034E0);
    RH_ScopedInstall(UpdateParameters, 0x504B70, { .reversed = false });

}

// 0x507560
CAEWeaponAudioEntity::CAEWeaponAudioEntity() {
    Clear();
}

// 0x503450
void CAEWeaponAudioEntity::Initialise() {
    m_MiniGunState = eMiniGunState::STOPPED;
    m_ChainsawState = 4;
    if (!AudioEngine.IsLoadingTuneActive()) {
        AEAudioHardware.LoadSoundBank(143, 5);
    }
}

// 0x503480
void CAEWeaponAudioEntity::Terminate() {
    AESoundManager.CancelSoundsOwnedByAudioEntity(this, true);
}

// 0x503490
void CAEWeaponAudioEntity::Reset() {
    AESoundManager.CancelSoundsOwnedByAudioEntity(this, true);
    Clear();
}

// 0x504F80
void CAEWeaponAudioEntity::WeaponFire(eWeaponType type, CPhysical* entity, eAudioEvents audioEventId) {
    if (!entity) {
        return;
    }

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
        return PlayGunSounds(entity, 29, 30, 0, 1, 2, audioEventId, 0.0f, 1.25992f, 1.0f);

    case WEAPON_COUNTRYRIFLE:
        return PlayGunSounds(entity, 52, 53, 26, 27, 23, audioEventId, 0.0f, 0.89f, 1.0f);

    case WEAPON_SNIPERRIFLE:
        return PlayGunSounds(entity, 52, 53, 26, 27, 23, audioEventId, 0.0f, 1.0f, 1.0f);

    case WEAPON_FLAMETHROWER:
        if (!m_FlameThrowerLastPlayedTimeMs)
            PlayFlameThrowerSounds(entity, 83, 26, audioEventId, -14.0f, 1.0f);
        m_FlameThrowerLastPlayedTimeMs = CTimer::GetTimeInMS();
        break;

    case WEAPON_MINIGUN:
        return PlayMiniGunFireSounds(entity, audioEventId);

    case WEAPON_DETONATOR:
        return PlayGunSounds(entity, 49, -1, -1, -1, -1, audioEventId, -14.0f, 1.0f, 1.0f);

    case WEAPON_SPRAYCAN:
        if (!m_LastSprayCanFireTimeMs) {
            PlayWeaponLoopSound(entity, 28, audioEventId, -20.0f, 1.0f, AE_FRONTEND_HIGHLIGHT);
        }
        m_LastSprayCanFireTimeMs = CTimer::GetTimeInMS();
        break;

    case WEAPON_EXTINGUISHER:
        if (!m_LastFireExtFireTimeMs)
            PlayWeaponLoopSound(entity, 9, audioEventId, -20.0f, 0.79369998f, AE_FRONTEND_ERROR);

        m_LastFireExtFireTimeMs = CTimer::GetTimeInMS();
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
void CAEWeaponAudioEntity::WeaponReload(eWeaponType type, CPhysical* entity, eAudioEvents event) {
    if (!entity)
        return;

    if (!AEAudioHardware.IsSoundBankLoaded(143, 5)) {
        if (!AudioEngine.IsLoadingTuneActive()) {
            AEAudioHardware.LoadSoundBank(143, 5);
        }
        return;
    }

    int16 soundType;
    float volumeOffset = 0.0f;

    switch (type) {
    case WEAPON_PISTOL:
    case WEAPON_PISTOL_SILENCED:
        soundType = event != AE_WEAPON_RELOAD_A ? 66 : 55;
        break;
    case WEAPON_DESERT_EAGLE:
        soundType = 4 * (event == AE_WEAPON_RELOAD_A) + 51;
        break;
    case WEAPON_SHOTGUN:
    case WEAPON_SPAS12_SHOTGUN:
        soundType = (event != AE_WEAPON_RELOAD_A) + 71;
        break;
    case WEAPON_SAWNOFF_SHOTGUN:
        soundType = (event != AE_WEAPON_RELOAD_A) + 69;
        break;
    case WEAPON_MICRO_UZI:
    case WEAPON_MP5:
    case WEAPON_TEC9:
        soundType = (event != AE_WEAPON_RELOAD_A) + 84;
        break;
    case WEAPON_AK47:
    case WEAPON_M4:
        soundType = (event != AE_WEAPON_RELOAD_A) + 31;
        break;
    case WEAPON_COUNTRYRIFLE:
        if (event != AE_WEAPON_RELOAD_A)
            return;
        soundType = 32;
        volumeOffset = -6.0f;
        break;
    case WEAPON_SNIPERRIFLE:
        soundType = event != AE_WEAPON_RELOAD_A ? 32 : 55;
        break;
    default:
        return;
    }

    const auto volume = GetDefaultVolume(event) + volumeOffset;

    m_tempSound.Initialise(5, soundType, this, entity->GetPosition(), volume, 0.66f, 1.0f, 1.0f, 0, SOUND_LIFESPAN_TIED_TO_PHYSICAL_ENTITY, 0.0f, 0);
    m_tempSound.RegisterWithPhysicalEntity(entity);
    AESoundManager.RequestNewSound(&m_tempSound);
}

// 0x503B20
void CAEWeaponAudioEntity::ReportStealthKill(eWeaponType type, CPhysical* entity, eAudioEvents event) {
    if (type != WEAPON_KNIFE)
        return;

    const auto vol = GetDefaultVolume(event);
    const auto flags = static_cast<eSoundEnvironment>(SOUND_LIFESPAN_TIED_TO_PHYSICAL_ENTITY | SOUND_REQUEST_UPDATES);

    if (!AEAudioHardware.IsSoundBankLoaded(143, 5)) {
        if (!AudioEngine.IsLoadingTuneActive()) {
            AEAudioHardware.LoadSoundBank(143, 5);
        }
        return;
    }
    m_tempSound.Initialise(5, 81, this, entity->GetPosition(), vol - 6.0f, 1.0f, 0.0f, 1.0f, 0);
    m_tempSound.RegisterWithPhysicalEntity(entity);
    m_tempSound.m_nEvent = AE_FRONTEND_PICKUP_COLLECTABLE1;
    m_tempSound.m_fMaxVolume = (float)CTimer::m_snTimeInMilliseconds;
    AESoundManager.RequestNewSound(&m_tempSound);

    if (!AEAudioHardware.IsSoundBankLoaded(39, 2)) {
        if (!AudioEngine.IsLoadingTuneActive()) {
            AEAudioHardware.LoadSoundBank(39, 2);
        }
        return;
    }
    m_tempSound.Initialise(2, 47, this, entity->GetPosition(), vol, 1.0f, 0.0f, 1.0f, 0, flags);
    m_tempSound.RegisterWithPhysicalEntity(entity);
    m_tempSound.m_nEvent = AE_FRONTEND_CAR_NO_CASH;
    m_tempSound.m_fMaxVolume = (float)CTimer::GetTimeInMS();
    AESoundManager.RequestNewSound(&m_tempSound);
}

// 0x503910
void CAEWeaponAudioEntity::ReportChainsawEvent(CPhysical* entity, int32 audioEventId) {
    plugin::CallMethod<0x503910, CAEWeaponAudioEntity*, CPhysical*, int32>(this, entity, audioEventId);
}

// 0x504610
void CAEWeaponAudioEntity::PlayWeaponLoopSound(CPhysical* entity, int16 sfxId, eAudioEvents startEvent, float audability, float speed, eAudioEvents endEvent) {
    if (!AEAudioHardware.IsSoundBankLoaded(143u, 5)) {
        if (!AudioEngine.IsLoadingTuneActive()) {
            AEAudioHardware.LoadSoundBank(143, 5);
        }
        return;
    }

    const auto volume = GetDefaultVolume(startEvent) + audability;
    const auto flags = static_cast<eSoundEnvironment>(SOUND_LIFESPAN_TIED_TO_PHYSICAL_ENTITY | SOUND_START_PERCENTAGE | SOUND_REQUEST_UPDATES);
    m_tempSound.Initialise(5, sfxId, this, entity->GetPosition(), volume, 1.0f, speed, 1.0f, 0, flags);
    m_tempSound.RegisterWithPhysicalEntity(entity);
    m_tempSound.m_nEvent = endEvent;
    AESoundManager.RequestNewSound(&m_tempSound);
}

// 0x504960
void CAEWeaponAudioEntity::PlayMiniGunStopSound(CPhysical* entity) {
    if (!entity) {
        m_MiniGunState = eMiniGunState::STOPPED;
        return;
    }

    if (m_MiniGunState == eMiniGunState::STOPPING) {
        return;
    }

    if (!AEAudioHardware.IsSoundBankLoaded(143u, 5)) {
        if (!AudioEngine.IsLoadingTuneActive()) {
            AEAudioHardware.LoadSoundBank(143, 5);
        }
        return;
    }

    const auto PlayMiniGunFireStopSound = [&](float speed, float maxDist) {
        CAESound s;
        s.Initialise(
            5,
            63,
            this,
            entity->GetPosition(),
            GetDefaultVolume(AE_WEAPON_FIRE_MINIGUN_STOP),
            maxDist * 2.f / 3.f, // *0.66....f
            speed,
            1.0f,
            0,
            SOUND_LIFESPAN_TIED_TO_PHYSICAL_ENTITY | SOUND_REQUEST_UPDATES
        );
        s.RegisterWithPhysicalEntity(entity);
        s.m_nEvent = AE_FRONTEND_PICKUP_HEALTH; // ???
        AESoundManager.RequestNewSound(&s);
    };
    if (entity->IsVehicle() && entity->AsVehicle()->IsSubPlane()) {
        PlayMiniGunFireStopSound(1.8f, 0.7937f);
    } else {
        PlayMiniGunFireStopSound(1.f, 1.f);
    }
    m_MiniGunState = eMiniGunState::STOPPING;
}

// 0x5047C0
void CAEWeaponAudioEntity::PlayMiniGunFireSounds(CPhysical* entity, eAudioEvents audioEvent) {
    const auto PlayMiniGunFireSound = [&](eAudioEvents gunFireAE) {
        m_MiniGunState = eMiniGunState::FIRING;
        if (!std::exchange(m_IsMiniGunFireActive, true)) {
            PlayGunSounds(entity, 15, 16, 11, 12, 13, gunFireAE, 0.f, 1.f, 1.f);
        }
    };
    switch (audioEvent) {
    case AE_WEAPON_FIRE:
    case AE_WEAPON_FIRE_MINIGUN_AMMO: { // 0x504912
        PlayMiniGunFireSound(AE_WEAPON_FIRE_MINIGUN_AMMO);
        break;
    }
    case AE_WEAPON_FIRE_PLANE: { // 0x5047E6
        PlayMiniGunFireSound(AE_WEAPON_FIRE_MINIGUN_PLANE);
        break;
    }
    case AE_WEAPON_FIRE_MINIGUN_NO_AMMO: { // 0x5048FC - Minigun is just spinning
        if (!m_IsMiniGunSpinActive) {
            if (!AEAudioHardware.IsSoundBankLoaded(143, 5)) { // SND_BANK_GENRL_WEAPONS, SND_BANK_SLOT_WEAPON_GEN
                if (!AudioEngine.IsLoadingTuneActive()) {
                    AEAudioHardware.LoadSoundBank(143, 5);
                }
                break;
            }
            CAESound s;
            s.Initialise(
                5,
                14,
                this,
                entity->GetPosition(),
                GetDefaultVolume(AE_WEAPON_FIRE_MINIGUN_NO_AMMO),
                2.f / 3.f,
                1.f,
                0.f,
                0,
                SOUND_LIFESPAN_TIED_TO_PHYSICAL_ENTITY | SOUND_REQUEST_UPDATES
            );
            s.m_nEvent = AE_FRONTEND_NOISE_TEST;
            s.RegisterWithPhysicalEntity(entity);
            AESoundManager.RequestNewSound(&s);
            m_IsMiniGunSpinActive = true;
        }
        m_MiniGunState = eMiniGunState::SPINNING;
        break;
    }
    }
    m_LastMiniGunFireTimeMs = CTimer::GetTimeInMS();
}

// 0x503CE0
void CAEWeaponAudioEntity::PlayGunSounds(
    CPhysical*   entity,
    int16        dryFireSfxID,
    int16        subSfxID,
    int16        mainLeftSfxID,
    int16        mainRightSfxID,
    int16        tailSfxID,
    eAudioEvents audioEvent,
    float        volumeOffsetdB,
    float        primarySpeed,
    float        tailFrequencyScalingFactor
) {
    if (!AEAudioHardware.IsSoundBankLoaded(143u, 5)) {
        if (!AudioEngine.IsLoadingTuneActive()) {
            AEAudioHardware.LoadSoundBank(143, 5);
        }
        return;
    }

    if (CTimer::GetTimeInMS() < m_LastGunFireTimeMs + 25) {
        return;
    }
    m_LastGunFireTimeMs = CTimer::GetTimeInMS();

    auto baseVolume = GetDefaultVolume(audioEvent) + volumeOffsetdB;
    auto [baseRollOffFactor, baseSpeed] = [&]() -> std::pair<float, float> {
        switch (audioEvent) {
        case AE_WEAPON_FIRE_PLANE: {
            m_LastWeaponPlaneFrequencyIndex = (m_LastWeaponPlaneFrequencyIndex + 1) % 2;
            return {1.6f, gfWeaponPlaneFrequencyVariations[m_LastWeaponPlaneFrequencyIndex] * primarySpeed * 0.7937f};
        }
        case AE_WEAPON_FIRE_MINIGUN_PLANE: {
            return {1.8f, primarySpeed * 0.7937f};
        }
        default: {
            return {1.f, primarySpeed};
        }
        }
    }();

    const auto PlaySound = [&](int16 sfxID, CVector pos, float volume, float rollOffFactor, float speed, uint32 flags, eAudioEvents audioEventOverride = AE_UNDEFINED) {
        CAESound s;
        s.Initialise(
            5,
            sfxID,
            this,
            pos,
            volume,
            rollOffFactor,
            speed,
            0.f,
            0,
            flags
        );
        if (flags & SOUND_LIFESPAN_TIED_TO_PHYSICAL_ENTITY) {
            s.RegisterWithPhysicalEntity(entity);
        }
        if (audioEventOverride == AE_UNDEFINED) {
            switch (audioEvent) {
            case AE_WEAPON_FIRE_MINIGUN_PLANE:
            case AE_WEAPON_FIRE_MINIGUN_AMMO:
                s.m_nEvent = AE_FRONTEND_PICKUP_WEAPON;
            }
        } else {
            s.m_nEvent = audioEventOverride;
        }
        AESoundManager.RequestNewSound(&s);
    };

    if (dryFireSfxID != -1) { // 0x503DFF
        PlaySound(
            dryFireSfxID,
            entity->GetPosition(),
            baseVolume,
            baseRollOffFactor * (2.f / 3.f),
            baseSpeed,
            SOUND_LIFESPAN_TIED_TO_PHYSICAL_ENTITY | SOUND_REQUEST_UPDATES
        );
    }
    if (subSfxID != -1) { // 0x503E93
        PlaySound(
            subSfxID,
            entity->GetPosition(),
            baseVolume,
            baseRollOffFactor * 0.9f,
            baseSpeed,
            SOUND_LIFESPAN_TIED_TO_PHYSICAL_ENTITY | SOUND_REQUEST_UPDATES
        );
    }

    // 0x503F21
    float frontEndVolume = -100.f;
    if (!notsa::contains({ AE_WEAPON_FIRE_PLANE, AE_WEAPON_FIRE_MINIGUN_PLANE }, audioEvent)) {
        const auto dist = CAEAudioEnvironment::GetPositionRelativeToCamera(entity).Magnitude() / (baseRollOffFactor * 1.25f);
        if (dist < (5.f / baseRollOffFactor)) { // Inverted
            baseVolume    -= 3.f;
            frontEndVolume = baseVolume + CAEAudioEnvironment::GetDistanceAttenuation(dist);
        } else if (dist < (12.f / baseRollOffFactor)) {
            const auto t   = ((12.f / baseRollOffFactor) - dist) / (12.f / baseRollOffFactor) - (5.f / baseRollOffFactor);
            frontEndVolume = baseVolume + CAEAudioEnvironment::GetDistanceAttenuation(dist) + std::log10f(t * (SQRT_2 / 2.f)) * 20.f;
            baseVolume    += std::log10f(((1.f - t) * 0.2929f) + (SQRT_2 / 2.f)) * 20.f;
        }
    }

    const auto PlayMainSound = [
        &,
        mainSoundSpeed = (CAEAudioUtility::GetRandomNumberInRange(-0.02f, 0.02f) + 1.f) * baseSpeed
    ](int16 sfxID, bool isRight) {
        PlaySound(
            sfxID,
            CVector{isRight ? 1.f : -1.f, 0.f, 0.f},
            frontEndVolume,
            baseRollOffFactor * 1.25f,
            mainSoundSpeed,
            SOUND_FORCED_FRONT | SOUND_REQUEST_UPDATES | SOUND_FRONT_END
        );
        PlaySound(
            sfxID,
            entity->GetPosition(),
            baseVolume,
            baseRollOffFactor * 1.25f,
            mainSoundSpeed,
            SOUND_LIFESPAN_TIED_TO_PHYSICAL_ENTITY | SOUND_REQUEST_UPDATES
        );
    };
    if (mainLeftSfxID != -1) { // 0x5040DC + 0x5041DF
        PlayMainSound(mainLeftSfxID, false);
    }
    if (mainRightSfxID != -1) { // 0x504153 + 0x504218
        PlayMainSound(mainRightSfxID, true);
    }

    if (tailSfxID != -1 && !notsa::contains({AE_WEAPON_FIRE_PLANE, AE_WEAPON_FIRE_MINIGUN_PLANE}, audioEvent)) {
        const auto tailSoundRollOff    = baseRollOffFactor * 3.5f;
        const auto tailSoundVolume     = CAEAudioEnvironment::GetDistanceAttenuation(CAEAudioEnvironment::GetPositionRelativeToCamera(entity).Magnitude() / tailSoundRollOff) + baseVolume - 20.f;
        const auto tailSoundAudioEvent = audioEvent == AE_WEAPON_FIRE_MINIGUN_AMMO
            ? AE_FRONTEND_PICKUP_MONEY
            : AE_FRONTEND_SELECT;
        const auto PlayTailSound = [&](bool isRight, float speedMult) {
            PlaySound(
                tailSfxID,
                CVector{ isRight ? 1.f : -1, 0.f, 0.f },
                tailSoundVolume,
                tailSoundRollOff,
                tailFrequencyScalingFactor * speedMult,
                SOUND_FORCED_FRONT | SOUND_ROLLED_OFF | SOUND_REQUEST_UPDATES | SOUND_FRONT_END,
                tailSoundAudioEvent
            );
        };
        float speedMultA = 1.f,
              speedMultB = 1.1892101f;
        if (CAEAudioUtility::ResolveProbability(0.5f)) {
            std::swap(speedMultA, speedMultB);
        }
        PlayTailSound(false, speedMultA);
        PlayTailSound(true,  speedMultB);
    }
}

// 0x503500
void CAEWeaponAudioEntity::PlayGoggleSound(int16 sfxId, eAudioEvents event) {
    if (!AEAudioHardware.IsSoundBankLoaded(143u, 5)) {
        if (!AudioEngine.IsLoadingTuneActive()) {
            AEAudioHardware.LoadSoundBank(143, 5);
        }
        return;
    }
    const auto PlaySound = [&](float offsetX, float speed) {
        CAESound s;
        s.Initialise(5, sfxId, this, { offsetX, 0.0f, 0.0f }, GetDefaultVolume(event) - 9.f, 1.0f, speed, 1.0f, 0, SOUND_DEFAULT);
        s.m_nEnvironmentFlags = SOUND_FRONT_END | SOUND_FORCED_FRONT;
        AESoundManager.RequestNewSound(&s);
    };
    const auto r = CAEAudioUtility::ResolveProbability(0.5f);
    PlaySound(-1.0f, r ? 1.1892101f : 1.f);
    PlaySound(+1.0f, r ? 1.f : 1.1892101f);
}

// 0x504470
void CAEWeaponAudioEntity::PlayFlameThrowerSounds(CPhysical* entity, int16 sfx1, int16 sfx2, int32 audioEventId, float audability, float speed) {
    plugin::CallMethod<0x504470, CAEWeaponAudioEntity*, CPhysical*, int16, int16, int32, float, float>(this, entity, sfx1, sfx2, audioEventId, audability, speed);
}

// 0x503870
void CAEWeaponAudioEntity::PlayFlameThrowerIdleGasLoop(CPhysical* entity) {
    if (m_FlameThrowerIdleGasLoopSound != nullptr)
        return;

    const auto volume = GetDefaultVolume(AE_FLAMETHROWER_IDLE);
    const auto flags = static_cast<eSoundEnvironment>(SOUND_LIFESPAN_TIED_TO_PHYSICAL_ENTITY | SOUND_REQUEST_UPDATES);
    m_tempSound.Initialise(5, 10, this, entity->GetPosition(), volume, 0.66f, 1.0f, 1.0f, 0, flags);
    m_tempSound.RegisterWithPhysicalEntity(entity);
    m_FlameThrowerIdleGasLoopSound = AESoundManager.RequestNewSound(&m_tempSound);
}

// 0x5034E0
void CAEWeaponAudioEntity::StopFlameThrowerIdleGasLoop() {
    if (m_FlameThrowerIdleGasLoopSound) {
        m_FlameThrowerIdleGasLoopSound->StopSoundAndForget();
        m_FlameThrowerIdleGasLoopSound = nullptr;
    }
}

// 0x504AA0
void CAEWeaponAudioEntity::PlayChainsawStopSound(CPhysical* entity) {
    if (entity && AEAudioHardware.IsSoundBankLoaded(0x24u, 40)) {
        if (m_ChainsawState != 3) {
            const auto volume = GetDefaultVolume(AE_WEAPON_CHAINSAW_ACTIVE);
            const auto flags = static_cast<eSoundEnvironment>(SOUND_LIFESPAN_TIED_TO_PHYSICAL_ENTITY | SOUND_REQUEST_UPDATES);
            m_tempSound.Initialise(40, 2, this, entity->GetPosition(), volume, 0.66f, 1.0f, 1.0f, 0, flags);
            m_tempSound.RegisterWithPhysicalEntity(entity);
            m_tempSound.m_nEvent = AE_FRONTEND_PICKUP_DRUGS;
            AESoundManager.RequestNewSound(&m_tempSound);
        }
        m_ChainsawState = 3;
    } else {
        m_ChainsawState = 4;
    }
}

// 0x5046F0
void CAEWeaponAudioEntity::PlayCameraSound(CPhysical* entity, eAudioEvents event, float audability) {
    if (!AEAudioHardware.IsSoundBankLoaded(143, 5)) {
        if (!AudioEngine.IsLoadingTuneActive()) {
            AEAudioHardware.LoadSoundBank(143, 5);
        }
        return;
    }

    const auto vol = GetDefaultVolume(event) + audability;
    const auto flags = static_cast<eSoundEnvironment>(SOUND_LIFESPAN_TIED_TO_PHYSICAL_ENTITY | SOUND_UNPAUSABLE);
    m_tempSound.Initialise(5, 45, this, entity->GetPosition(), vol, 0.66f, 1.0f, 1.0f, 0, flags);
    m_tempSound.RegisterWithPhysicalEntity(entity);
    AESoundManager.RequestNewSound(&m_tempSound);
}

// 0x504B70
void CAEWeaponAudioEntity::UpdateParameters(CAESound *sound, int16 curPlayPos) {
    plugin::CallMethod<0x504B70, CAEWeaponAudioEntity*, CAESound*, int16>(this, sound, curPlayPos);
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
