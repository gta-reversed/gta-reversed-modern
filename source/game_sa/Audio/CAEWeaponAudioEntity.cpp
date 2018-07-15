/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

// Converted from thiscall void CAEWeaponAudioEntity::CAEWeaponAudioEntity(void)	0x507560	
CAEWeaponAudioEntity::CAEWeaponAudioEntity() {
    plugin::CallMethod<0x507560, CAEWeaponAudioEntity *>(this);
}

// Converted from thiscall void CAEWeaponAudioEntity::WeaponReload(eWeaponType weaptype,CPhysical *entity,int AudioEventId)	0x503690	
void CAEWeaponAudioEntity::WeaponReload(eWeaponType weaptype, CPhysical* entity, int AudioEventId) {
    plugin::CallMethod<0x503690, CAEWeaponAudioEntity *, eWeaponType, CPhysical*, int>(this, weaptype, entity, AudioEventId);
}

// Converted from thiscall void CAEWeaponAudioEntity::WeaponFire(eWeaponType weaptype,CPhysical *entity,int AudioEventId)	0x504F80	
void CAEWeaponAudioEntity::WeaponFire(eWeaponType weaptype, CPhysical* entity, int AudioEventId) {
    plugin::CallMethod<0x504F80, CAEWeaponAudioEntity *, eWeaponType, CPhysical*, int>(this, weaptype, entity, AudioEventId);
}

// Converted from thiscall void CAEWeaponAudioEntity::Terminate(void)	0x503480	
void CAEWeaponAudioEntity::Terminate() {
    plugin::CallMethod<0x503480, CAEWeaponAudioEntity *>(this);
}

// Converted from thiscall void CAEWeaponAudioEntity::StopFlameThrowerIdleGasLoop(void)	0x5034E0	
void CAEWeaponAudioEntity::StopFlameThrowerIdleGasLoop() {
    plugin::CallMethod<0x5034E0, CAEWeaponAudioEntity *>(this);
}

// Converted from thiscall void CAEWeaponAudioEntity::Reset(void)	0x503490	
void CAEWeaponAudioEntity::Reset() {
    plugin::CallMethod<0x503490, CAEWeaponAudioEntity *>(this);
}

// Converted from thiscall void CAEWeaponAudioEntity::ReportStealthKill(eWeaponType weaptype,CPhysical *entity,int AudioEventId)	0x503B20	
void CAEWeaponAudioEntity::ReportStealthKill(eWeaponType weaptype, CPhysical* entity, int AudioEventId) {
    plugin::CallMethod<0x503B20, CAEWeaponAudioEntity *, eWeaponType, CPhysical*, int>(this, weaptype, entity, AudioEventId);
}

// Converted from thiscall void CAEWeaponAudioEntity::ReportChainsawEvent(CPhysical *entity,int AudioEventId)	0x503910	
void CAEWeaponAudioEntity::ReportChainsawEvent(CPhysical* entity, int AudioEventId) {
    plugin::CallMethod<0x503910, CAEWeaponAudioEntity *, CPhysical*, int>(this, entity, AudioEventId);
}

// Converted from thiscall void CAEWeaponAudioEntity::PlayWeaponLoopSound(CPhysical *,short sfxId,int AudioEventId,float audability,float speed,int finalEvent)	0x504610	
void CAEWeaponAudioEntity::PlayWeaponLoopSound(CPhysical* arg0, short sfxId, int AudioEventId, float audability, float speed, int finalEvent) {
    plugin::CallMethod<0x504610, CAEWeaponAudioEntity *, CPhysical*, short, int, float, float, int>(this, arg0, sfxId, AudioEventId, audability, speed, finalEvent);
}

// Converted from thiscall void CAEWeaponAudioEntity::PlayMiniGunStopSound(CPhysical *entity)	0x504960	
void CAEWeaponAudioEntity::PlayMiniGunStopSound(CPhysical* entity) {
    plugin::CallMethod<0x504960, CAEWeaponAudioEntity *, CPhysical*>(this, entity);
}

// Converted from thiscall void CAEWeaponAudioEntity::PlayMiniGunFireSounds(CPhysical *entity,int AudioEventId)	0x5047C0	
void CAEWeaponAudioEntity::PlayMiniGunFireSounds(CPhysical* entity, int AudioEventId) {
    plugin::CallMethod<0x5047C0, CAEWeaponAudioEntity *, CPhysical*, int>(this, entity, AudioEventId);
}

// Converted from thiscall void CAEWeaponAudioEntity::PlayGunSounds(CPhysical *entity,short emptySfxId,short farSfxId2,short highPitchSfxId3,short lowPitchSfxId4,short echoSfxId5,int nAudioEventId,float volumeChange,float speed1,float speed2)	0x503CE0	
void CAEWeaponAudioEntity::PlayGunSounds(CPhysical* entity, short emptySfxId, short farSfxId2, short highPitchSfxId3, short lowPitchSfxId4, short echoSfxId5, int nAudioEventId, float volumeChange, float speed1, float speed2) {
    plugin::CallMethod<0x503CE0, CAEWeaponAudioEntity *, CPhysical*, short, short, short, short, short, int, float, float, float>(this, entity, emptySfxId, farSfxId2, highPitchSfxId3, lowPitchSfxId4, echoSfxId5, nAudioEventId, volumeChange, speed1, speed2);
}

// Converted from thiscall void CAEWeaponAudioEntity::PlayGoggleSound(short sfxId,int AudioEventId)	0x503500	
void CAEWeaponAudioEntity::PlayGoggleSound(short sfxId, int AudioEventId) {
    plugin::CallMethod<0x503500, CAEWeaponAudioEntity *, short, int>(this, sfxId, AudioEventId);
}

// Converted from thiscall void CAEWeaponAudioEntity::PlayFlameThrowerSounds(CPhysical *entity,short sfx1,short sfx2,int AudioEventId,float audability,float speed)	0x504470	
void CAEWeaponAudioEntity::PlayFlameThrowerSounds(CPhysical* entity, short sfx1, short sfx2, int AudioEventId, float audability, float speed) {
    plugin::CallMethod<0x504470, CAEWeaponAudioEntity *, CPhysical*, short, short, int, float, float>(this, entity, sfx1, sfx2, AudioEventId, audability, speed);
}

// Converted from thiscall void CAEWeaponAudioEntity::PlayFlameThrowerIdleGasLoop(CPhysical *entity)	0x503870	
void CAEWeaponAudioEntity::PlayFlameThrowerIdleGasLoop(CPhysical* entity) {
    plugin::CallMethod<0x503870, CAEWeaponAudioEntity *, CPhysical*>(this, entity);
}

// Converted from thiscall void CAEWeaponAudioEntity::PlayChainsawStopSound(CPhysical *entity)	0x504AA0	
void CAEWeaponAudioEntity::PlayChainsawStopSound(CPhysical* entity) {
    plugin::CallMethod<0x504AA0, CAEWeaponAudioEntity *, CPhysical*>(this, entity);
}

// Converted from thiscall void CAEWeaponAudioEntity::PlayCameraSound(CPhysical *entity,int AudioEventId,float audability)	0x5046F0	
void CAEWeaponAudioEntity::PlayCameraSound(CPhysical* entity, int AudioEventId, float audability) {
    plugin::CallMethod<0x5046F0, CAEWeaponAudioEntity *, CPhysical*, int, float>(this, entity, AudioEventId, audability);
}

// Converted from thiscall void CAEWeaponAudioEntity::Initialise(void)	0x503450	
void CAEWeaponAudioEntity::Initialise() {
    plugin::CallMethod<0x503450, CAEWeaponAudioEntity *>(this);
}