/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "WeaponInfo.h"

CWeaponInfo* aWeaponInfo = (CWeaponInfo*)0xC8AAB8;

void CWeaponInfo::InjectHooks() {
    RH_ScopedClass(CWeaponInfo);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(GetSkillStatIndex, 0x743CD0);
}

CWeaponInfo::CWeaponInfo() {
    ((void(__thiscall*)(CWeaponInfo*))0x743C30)(this);
}

CWeaponInfo::~CWeaponInfo() {
    ((void(__thiscall*)(CWeaponInfo*))0x743C40)(this);
}

void CWeaponInfo::Initialise() {
    ((void(__cdecl*)())0x5BF750)();
}

void CWeaponInfo::Shutdown() {
    ((void(__cdecl*)())0x743C50)();
}

AnimationId CWeaponInfo::GetCrouchReloadAnimationID() {
    return plugin::CallMethodAndReturn<AnimationId, 0x685700, CWeaponInfo*>(this);
}

char** CWeaponInfo::ms_aWeaponNames = (char**)0x8D6150;

void CWeaponInfo::LoadWeaponData() {
    ((void(__cdecl*)())0x5BE670)();
}

// 0x00743CD0
int32 CWeaponInfo::GetSkillStatIndex(int32 weaponType) {
    if (weaponType < WEAPON_PISTOL || weaponType > WEAPON_TEC9)
        return -1;

    if (weaponType <= WEAPON_M4)
        return weaponType - WEAPON_PISTOL + STAT_PISTOL_SKILL;

    if (weaponType == WEAPON_TEC9)
        return STAT_MACHINE_PISTOL_SKILL;

    if (weaponType == WEAPON_COUNTRYRIFLE)
        return STAT_GAMBLING;

    return weaponType + STAT_PISTOL_SKILL;
}

CWeaponInfo* CWeaponInfo::GetWeaponInfo(eWeaponType weaponType, eWeaponSkill skill) {
    return ((CWeaponInfo * (__cdecl*)(eWeaponType, eWeaponSkill))0x743C60)(weaponType, skill);
}

eWeaponType CWeaponInfo::FindWeaponType(char* name) {
    return ((eWeaponType(__cdecl*)(char*))0x743D10)(name);
}

eWeaponFire CWeaponInfo::FindWeaponFireType(char* name) {
    return ((eWeaponFire(__cdecl*)(char*))0x5BCF30)(name);
}
