#pragma once

#include "AEWeaponAudioEntity.h"

class CAEGlobalWeaponAudioEntity : public CAEWeaponAudioEntity {
public:
    CAEGlobalWeaponAudioEntity();
    ~CAEGlobalWeaponAudioEntity() = default; // 0x506C50

    void UpdateParameters(CAESound* sound, int16 curPlayPos) override;

    void AddAudioEvent(eAudioEvents audioId, eWeaponType weaponType, CPhysical* entity);
    void ProjectileFire(eWeaponType weaponType, CPhysical* physical, eAudioEvents event);
    void ServiceAmbientGunFire();

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CAEGlobalWeaponAudioEntity* Constructor();
    CAEGlobalWeaponAudioEntity* Destructor();
};

VALIDATE_SIZE(CAEGlobalWeaponAudioEntity, 0xA8);
