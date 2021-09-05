/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Audio/entities/CAEAudioEntity.h"
#include "CAESound.h"

#include "eWeaponType.h"

class CPhysical;
class CPed;

class CAEWeaponAudioEntity : public CAEAudioEntity {
public:
    bool      m_bPlayedMiniGunFireSound;
    char      field_7D;
    char      field_7E;
    char      field_7F;
    char      m_nChainsawSoundState;
    char      field_81[3];
    int32     m_nFlameThrowerLastPlayedTime;
    int32     m_nSpraycanLastPlayedTime;
    int32     m_nExtinguisherLastPlayedTime;
    int32     m_nMiniGunFireSoundPlayedTime;
    int32     m_nTimeChainsaw;
    int32     m_nTimeLastFired;
    CAESound* m_pSounds;
    char      m_bActive;
    char      field_A1[3];
    CPed*     m_pPed;

public:
    CAEWeaponAudioEntity();

    void Initialise();
    void Terminate();
    void Reset();

    void WeaponReload(eWeaponType weaptype, CPhysical* entity, int32 AudioEventId);
    void WeaponFire(eWeaponType weaptype, CPhysical* entity, int32 AudioEventId);
    void StopFlameThrowerIdleGasLoop();
    void ReportStealthKill(eWeaponType weaptype, CPhysical* entity, int32 AudioEventId);
    void ReportChainsawEvent(CPhysical* entity, int32 AudioEventId);
    void PlayWeaponLoopSound(CPhysical* arg0, int16 sfxId, int32 AudioEventId, float audability, float speed, int32 finalEvent);
    void PlayMiniGunStopSound(CPhysical* entity);
    void PlayMiniGunFireSounds(CPhysical* entity, int32 AudioEventId);
    void PlayGunSounds(CPhysical* entity, int16 emptySfxId, int16 farSfxId2, int16 highPitchSfxId3, int16 lowPitchSfxId4, int16 echoSfxId5, int32 nAudioEventId, float volumeChange, float speed1, float speed2);
    void PlayGoggleSound(int16 sfxId, int32 AudioEventId);
    void PlayFlameThrowerSounds(CPhysical* entity, int16 sfx1, int16 sfx2, int32 AudioEventId, float audability, float speed);
    void PlayFlameThrowerIdleGasLoop(CPhysical* entity);
    void PlayChainsawStopSound(CPhysical* entity);
    void PlayCameraSound(CPhysical* entity, int32 AudioEventId, float audability);
    void AddAudioEvent(int32 audioEventId);
};

VALIDATE_SIZE(CAEWeaponAudioEntity, 0xA8);
