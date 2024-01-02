#include "StdInc.h"

#include "WeaponModelInfo.h"

void CWeaponModelInfo::InjectHooks()
{
    RH_ScopedClass(CWeaponModelInfo);
    RH_ScopedCategory("Models");

    RH_ScopedVirtualInstall(GetModelType, 0x4C5780);
    RH_ScopedVirtualInstall(Init, 0x4C98F0);
    RH_ScopedVirtualInstall(SetClump, 0x4C9910);
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

    auto flashFrame = CClumpModelInfo::GetFrameFromName(clump, "gunflash");
    if (!flashFrame)
        return;

    auto firstAtomic = reinterpret_cast<RpAtomic*>(GetFirstObject(flashFrame));
    if (!firstAtomic)
        return;

    CVehicle::SetComponentAtomicAlpha(firstAtomic, 0);
    RpAtomicSetFlags(firstAtomic, 0);
    auto geometry = RpAtomicGetGeometry(firstAtomic);
    RpMaterialGetSurfaceProperties(RpGeometryGetMaterial(geometry, 0))->ambient = 16.0F;

}
