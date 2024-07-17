/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "AEAudioEntity.h"
#include "AESound.h"

#include "eWeaponType.h"

class CPhysical;
class CPed;

class NOTSA_EXPORT_VTABLE CAEWeaponAudioEntity : public CAEAudioEntity {
    enum class eMiniGunState : int8 {
        SPINNING = 0x0,
        FIRING = 0x1,
        STOPPING = 0x2,
        STOPPED = 0x3,
    };

public:
    CAEWeaponAudioEntity();
    ~CAEWeaponAudioEntity() = default;

    void Initialise();
    void Terminate();
    void Reset();

    void WeaponFire(eWeaponType type, CPhysical* entity, eAudioEvents audioEventId);
    void WeaponReload(eWeaponType type, CPhysical* entity, eAudioEvents event);

    void PlayGunSounds(CPhysical* entity, int16 emptySfxId, int16 farSfxId2, int16 highPitchSfxId3, int16 lowPitchSfxId4, int16 echoSfxId5, int32 audioEventId, float volumeChange, float speed1, float speed2);
    void PlayGoggleSound(int16 sfxId, eAudioEvents event);

    void ReportStealthKill(eWeaponType type, CPhysical* entity, eAudioEvents event);

    void ReportChainsawEvent(CPhysical* entity, int32 audioEventId);
    void PlayChainsawStopSound(CPhysical* entity);

    void PlayWeaponLoopSound(CPhysical* entity, int16 sfxId, eAudioEvents startEvent, float audability, float speed, eAudioEvents endEvent);

    void PlayMiniGunFireSounds(CPhysical* entity, eAudioEvents audioEventId);
    void PlayMiniGunStopSound(CPhysical* entity);

    void PlayFlameThrowerSounds(CPhysical* entity, int16 sfx1, int16 sfx2, int32 audioEventId, float audability, float speed);
    void PlayFlameThrowerIdleGasLoop(CPhysical* entity);
    void StopFlameThrowerIdleGasLoop();

    void PlayCameraSound(CPhysical* entity, eAudioEvents event, float audability);

    void UpdateParameters(CAESound* sound, int16 curPlayPos) override;

    void Clear() {
        m_FlameThrowerLastPlayedTimeMs  = 0;
        m_LastSprayCanFireTimeMs        = 0;
        m_LastFireExtFireTimeMs         = 0;
        m_FlameThrowerIdleGasLoopSound  = nullptr;
        m_LastWeaponPlaneFrequencyIndex = 0;
        m_LastMiniGunFireTimeMs         = 0;
        m_IsMiniGunSpinActive           = false;
        m_IsMiniGunFireActive           = false;
        m_LastChainsawEventTimeMs       = 0;
        m_LastGunFireTimeMs             = 0;
    }

private:
    bool          m_IsMiniGunSpinActive;
    bool          m_IsMiniGunFireActive;           // see PlayMiniGunFireSounds
    uint8         m_LastWeaponPlaneFrequencyIndex; // see PlayGunSounds, gfWeaponPlaneFrequencyVariations
    eMiniGunState m_MiniGunState;
    uint8         m_ChainsawState;
    uint32        m_FlameThrowerLastPlayedTimeMs;
    uint32        m_LastSprayCanFireTimeMs;
    uint32        m_LastFireExtFireTimeMs;
    uint32        m_LastMiniGunFireTimeMs;
    uint32        m_LastChainsawEventTimeMs;
    uint32        m_LastGunFireTimeMs;
    CAESound*     m_FlameThrowerIdleGasLoopSound;

private: // Hook stuff
    friend void InjectHooksMain();
    static void InjectHooks();

    CAEWeaponAudioEntity* Constructor();
    CAEWeaponAudioEntity* Destructor();

};
VALIDATE_SIZE(CAEWeaponAudioEntity, 0xA0);
