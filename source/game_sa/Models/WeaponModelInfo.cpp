#include "StdInc.h"

void CWeaponModelInfo::InjectHooks()
{
    ReversibleHooks::Install("CWeaponModelInfo", "GetModelType", 0x4C5780, &CWeaponModelInfo::GetModelType_Reversed);
    ReversibleHooks::Install("CWeaponModelInfo", "Init", 0x4C98F0, &CWeaponModelInfo::Init_Reversed);
    ReversibleHooks::Install("CWeaponModelInfo", "SetClump", 0x4C9910, &CWeaponModelInfo::SetClump_Reversed);
}

ModelInfoType CWeaponModelInfo::GetModelType()
{
    return CWeaponModelInfo::GetModelType_Reversed();
}
ModelInfoType CWeaponModelInfo::GetModelType_Reversed()
{
    return ModelInfoType::MODEL_INFO_WEAPON;
}

void CWeaponModelInfo::Init()
{
    CWeaponModelInfo::Init_Reversed();
}
void CWeaponModelInfo::Init_Reversed()
{
    CClumpModelInfo::Init();
    m_weaponInfo = eWeaponType::WEAPON_UNARMED;
}

void CWeaponModelInfo::SetClump(RpClump* clump)
{
    CWeaponModelInfo::SetClump_Reversed(clump);
}
void CWeaponModelInfo::SetClump_Reversed(RpClump* clump)
{
    CClumpModelInfo::SetClump(clump);
    RpClumpForAllAtomics(clump, CClumpModelInfo::SetAtomicRendererCB, CVisibilityPlugins::RenderWeaponCB);

    auto pFlashFrame = CClumpModelInfo::GetFrameFromName(clump, "gunflash");
    if (!pFlashFrame)
        return;

    auto pFirstAtomic = reinterpret_cast<RpAtomic*>(GetFirstObject(pFlashFrame));
    if (!pFirstAtomic)
        return;

    CVehicle::SetComponentAtomicAlpha(pFirstAtomic, 0);
    RpAtomicSetFlags(pFirstAtomic, 0);
    auto pGeometry = RpAtomicGetGeometry(pFirstAtomic);
    RpMaterialGetSurfaceProperties(RpGeometryGetMaterial(pGeometry, 0))->ambient = 16.0F;

}
