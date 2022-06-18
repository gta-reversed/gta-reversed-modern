#include "StdInc.h"
#include "Gangs.h"

void CGangs::InjectHooks() {
    RH_ScopedClass(CGangs);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Initialise, 0x5DE680);
    RH_ScopedInstall(Load, 0x5D3A90);
    RH_ScopedInstall(Save, 0x5D3A60);
    RH_ScopedInstall(SetGangWeapons, 0x5DE550);
    // RH_ScopedInstall(ChooseGangPedModel, 0x5DE5A0);
    RH_ScopedInstall(GetWillAttackPlayerWithCops, 0x5DE500);
    RH_ScopedInstall(SetWillAttackPlayerWithCops, 0x5DE4E0);
    RH_ScopedInstall(SetGangPedModelOverride, 0x5DE580);
}

// 0x5DE680
void CGangs::Initialise() {
    SetGangWeapons(GANG_BALLAS,     WEAPON_PISTOL,       WEAPON_MICRO_UZI, WEAPON_UNARMED);
    SetGangWeapons(GANG_GROVE,      WEAPON_PISTOL,       WEAPON_UNARMED,   WEAPON_UNARMED);
    SetGangWeapons(GANG_VAGOS,      WEAPON_PISTOL,       WEAPON_UNARMED,   WEAPON_UNARMED);
    SetGangWeapons(GANG_DANANGBOYS, WEAPON_PISTOL,       WEAPON_MICRO_UZI, WEAPON_UNARMED);
    SetGangWeapons(GANG_MAFIA,      WEAPON_DESERT_EAGLE, WEAPON_UNARMED,   WEAPON_UNARMED);
    SetGangWeapons(GANG_TRIAD,      WEAPON_PISTOL,       WEAPON_AK47,      WEAPON_UNARMED);
    SetGangWeapons(GANG_AZTECAS,    WEAPON_PISTOL,       WEAPON_MICRO_UZI, WEAPON_UNARMED);
}

// 0x5D3A90
bool CGangs::Load() {
    for (auto& gang : Gang) {
        CGenericGameStorage::LoadDataFromWorkBuffer(&gang, sizeof(CGangInfo));
    }
    return true;
}

// 0x5D3A60
bool CGangs::Save() {
    for (auto& gang : Gang) {
        CGenericGameStorage::SaveDataToWorkBuffer(&gang, sizeof(CGangInfo));
    }
    return true;
}

// 0x5DE550
void CGangs::SetGangWeapons(int16 gangId, int32 weapId1, int32 weapId2, int32 weapId3) {
    assert(weapId1 >= 0 && weapId2 >= 0 && weapId3 >= 0);
    Gang[gangId].m_nGangWeapons = {weapId1, weapId2, weapId3};
}

// 0x5DE5A0
int32 CGangs::ChooseGangPedModel(int16 gangId) {
    return plugin::CallAndReturn<int32, 0x5DE5A0, int16>(gangId);
}

// unused (0x5DE500)
bool CGangs::GetWillAttackPlayerWithCops(ePedType pedType) {
    assert(pedType >= PED_TYPE_GANG1 && pedType <= PED_TYPE_GANG10);
    return GangAttackWithCops[pedType - PED_TYPE_GANG1];
}

// unused (0x5DE4E0)
void CGangs::SetWillAttackPlayerWithCops(ePedType pedType, bool attackPlayerWithCops) {
    assert(pedType >= PED_TYPE_GANG1 && pedType <= PED_TYPE_GANG10);
    GangAttackWithCops[pedType - PED_TYPE_GANG1] = attackPlayerWithCops;
}

// unused (0x5DE580)
void CGangs::SetGangPedModelOverride(int16 gangId, int8 pedModelOverride) {
    Gang[gangId].m_nPedModelOverride = pedModelOverride;
}
