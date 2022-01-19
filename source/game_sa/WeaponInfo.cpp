/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"
#include "WeaponInfo.h"
#include <ranges>
namespace rng = std::ranges;

void CWeaponInfo::InjectHooks() {
    // Constructors (1x)
    ReversibleHooks::Install("CWeaponInfo", "CWeaponInfo", 0x743C30, &CWeaponInfo::Constructor);

    // Static functions (7x)
    ReversibleHooks::Install("CWeaponInfo", "FindWeaponFireType", 0x5BCF30, &CWeaponInfo::FindWeaponFireType);
    // ReversibleHooks::Install("CWeaponInfo", "LoadWeaponData", 0x5BE670, &CWeaponInfo::LoadWeaponData);
    // ReversibleHooks::Install("CWeaponInfo", "Initialise", 0x5BF750, &CWeaponInfo::Initialise);
    // ReversibleHooks::Install("CWeaponInfo", "Shutdown", 0x743C50, &CWeaponInfo::Shutdown);
    // ReversibleHooks::Install("CWeaponInfo", "GetWeaponInfo", 0x743C60, &CWeaponInfo::GetWeaponInfo);
    ReversibleHooks::Install("CWeaponInfo", "GetSkillStatIndex", 0x743CD0, &CWeaponInfo::GetSkillStatIndex);

    // Methods (4x)
    // ReversibleHooks::Install("CWeaponInfo", "GetCrouchReloadAnimationID", 0x685700, &CWeaponInfo::GetCrouchReloadAnimationID);
    // ReversibleHooks::Install("CWeaponInfo", "FindWeaponType", 0x743D10, &CWeaponInfo::FindWeaponType);
    // ReversibleHooks::Install("CWeaponInfo", "GetTargetHeadRange", 0x743D50, &CWeaponInfo::GetTargetHeadRange);
    // ReversibleHooks::Install("CWeaponInfo", "GetWeaponReloadTime", 0x743D70, &CWeaponInfo::GetWeaponReloadTime);
}

// 0x743C30
CWeaponInfo* CWeaponInfo::Constructor() {
    this->CWeaponInfo::CWeaponInfo();
    return this;
}

// Static functions
// 0x5BCF30
eWeaponFire CWeaponInfo::FindWeaponFireType(const char* name) {
    static constexpr struct { std::string_view name; eWeaponFire wf; } mapping[]{
        {"MELEE",       eWeaponFire::WEAPON_FIRE_MELEE},
        {"INSTANT_HIT", eWeaponFire::WEAPON_FIRE_INSTANT_HIT},
        {"PROJECTILE",  eWeaponFire::WEAPON_FIRE_PROJECTILE},
        {"AREA_EFFECT", eWeaponFire::WEAPON_FIRE_AREA_EFFECT},
        {"CAMERA",      eWeaponFire::WEAPON_FIRE_CAMERA},
        {"USE",         eWeaponFire::WEAPON_FIRE_USE},
    };
    if (const auto it = rng::find(mapping, name, [](const auto& e) { return e.name; }); it != std::end(mapping))
        return it->wf;
    return eWeaponFire::WEAPON_FIRE_INSTANT_HIT;
}

// 0x5BE670
void CWeaponInfo::LoadWeaponData() {
    return plugin::CallAndReturn<void, 0x5BE670>();
}

// 0x5BF750
void CWeaponInfo::Initialise() {
    return plugin::CallAndReturn<void, 0x5BF750>();
}

// 0x743C50
void CWeaponInfo::Shutdown() {
    plugin::Call<0x743C50>();
}

// 0x743C60
CWeaponInfo* CWeaponInfo::GetWeaponInfo(eWeaponType weaponID, eWeaponSkill skill) {
    return plugin::CallAndReturn<CWeaponInfo*, 0x743C60, eWeaponType, eWeaponSkill>(weaponID, skill);
}

// 0x743CD0
int32 CWeaponInfo::GetSkillStatIndex(eWeaponType weaponType) {
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

// 0x743D10
eWeaponType CWeaponInfo::FindWeaponType(const char* type) {
    return plugin::CallAndReturn<eWeaponType, 0x743D10>(type);
}

// Methods
// 0x685700
AnimationId CWeaponInfo::GetCrouchReloadAnimationID() {
    return plugin::CallMethodAndReturn<AnimationId, 0x685700, CWeaponInfo*>(this);
}

// 0x743D50
float CWeaponInfo::GetTargetHeadRange() {
    return plugin::CallMethodAndReturn<float, 0x743D50, CWeaponInfo*>(this);
}

// 0x743D70
int32 CWeaponInfo::GetWeaponReloadTime() {
    return plugin::CallMethodAndReturn<int32, 0x743D70, CWeaponInfo*>(this);
}
