#include "StdInc.h"
#include "ShotInfo.h"

void CShotInfo::InjectHooks() {
    RH_ScopedClass(CShotInfo);
    RH_ScopedCategory();

    RH_ScopedInstall(Initialise, 0x739B60, {.reversed = false});
    RH_ScopedInstall(Shutdown, 0x739C20, {.reversed = false});
    RH_ScopedInstall(AddShot, 0x739C30, {.reversed = false});
    RH_ScopedInstall(GetFlameThrowerShotPosn, 0x739DE0, {.reversed = false});
    RH_ScopedInstall(Update, 0x739E60, {.reversed = false});
}

// 0x739B60
void CShotInfo::Initialise() {
    return plugin::CallAndReturn<void, 0x739B60>();
}

// 0x739C20
void CShotInfo::Shutdown() {
    return plugin::CallAndReturn<void, 0x739C20>();
}

// 0x739C30
bool CShotInfo::AddShot(CEntity* creator, eWeaponType weaponType, CVector origin, CVector target) {
    return plugin::CallAndReturn<bool, 0x739C30, CEntity*, eWeaponType, CVector, CVector>(creator, weaponType, origin, target);
}

// 0x739DE0
bool CShotInfo::GetFlameThrowerShotPosn(uint8 shotId, CVector* pPosn) {
    return plugin::CallAndReturn<bool, 0x739DE0, uint8, CVector*>(shotId, pPosn);
}

// 0x739E60
void CShotInfo::Update() {
    return plugin::CallAndReturn<void, 0x739E60>();
}
