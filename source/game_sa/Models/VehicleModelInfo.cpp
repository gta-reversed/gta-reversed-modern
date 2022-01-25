/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

CVehicleModelInfo::CLinkedUpgradeList& CVehicleModelInfo::ms_linkedUpgrades = *(CVehicleModelInfo::CLinkedUpgradeList*)0xB4E6D8;
RwTexture* &CVehicleModelInfo::ms_pRemapTexture = *(RwTexture**)0xB4E47C;
RwTexture* &CVehicleModelInfo::ms_pLightsTexture = *(RwTexture**)0xB4E68C;
RwTexture* &CVehicleModelInfo::ms_pLightsOnTexture = *(RwTexture**)0xB4E690;
uint8 (&CVehicleModelInfo::ms_currentCol)[NUM_CURRENT_COLORS] = *(uint8(*)[NUM_CURRENT_COLORS])0xB4E3F0;
CRGBA (&CVehicleModelInfo::ms_vehicleColourTable)[NUM_VEHICLE_COLORS] = *(CRGBA(*)[NUM_VEHICLE_COLORS])0xB4E480;
char (&CVehicleModelInfo::ms_compsUsed)[NUM_COMPS_USAGE] = *(char(*)[NUM_COMPS_USAGE])0xB4E478;
char (&CVehicleModelInfo::ms_compsToUse)[NUM_COMPS_USAGE] = *(char(*)[NUM_COMPS_USAGE])0x8A6458;
int16(&CVehicleModelInfo::ms_numWheelUpgrades)[NUM_WHEELS] = *(int16(*)[NUM_WHEELS])0xB4E470;
int32 (&CVehicleModelInfo::ms_wheelFrameIDs)[NUM_WHEELS] = *(int32(*)[NUM_WHEELS])0x8A7770;
int16(&CVehicleModelInfo::ms_upgradeWheels)[NUM_WHEEL_UPGRADES][NUM_WHEELS] = *(int16(*)[NUM_WHEEL_UPGRADES][NUM_WHEELS])0xB4E3F8;
uint8(&CVehicleModelInfo::ms_lightsOn)[NUM_LIGHTS] = *(uint8(*)[NUM_LIGHTS])0xB4E3E8;
RwObjectNameIdAssocation* (&CVehicleModelInfo::ms_vehicleDescs)[NUM_VEHICLE_MODEL_DESCS] = *(RwObjectNameIdAssocation*(*)[NUM_VEHICLE_MODEL_DESCS])0x8A7740;

RwTextureCallBackFind & CVehicleModelInfo::SavedTextureFindCallback = *(RwTextureCallBackFind*)0xB4E6A0;
RwTexDictionary* &vehicleTxd = *(RwTexDictionary**)0xB4E688;
RwFrame* &carFrame = *(RwFrame**)0xB4E6B8;
RwSurfaceProperties& gLightSurfProps = *(RwSurfaceProperties*)0x8A645C;
tRestoreEntry(&gRestoreEntries)[NUM_RESTORE_ENTRIES] = *(tRestoreEntry(*)[NUM_RESTORE_ENTRIES])0xB4DBE8;
RwTexture*& gpWhiteTexture = *(RwTexture**)0xB4E3EC;
float& fEnvMapDefaultCoeff = *(float*)0x8A7780;
float& fRearDoubleWheelOffsetFactor = *(float*)0x8A7784;

typedef CVehicleModelInfo::CVehicleStructure CVehicleStructure;
CPool<CVehicleModelInfo::CVehicleStructure>*& CVehicleModelInfo::CVehicleStructure::m_pInfoPool = *(CPool<CVehicleModelInfo::CVehicleStructure> **)0xB4E680;

void CVehicleModelInfo::InjectHooks()
{
// ClinkedUpgradeList
    ReversibleHooks::Install("CLinkedUpgradeList", "AddUpgradeLink", 0x4C74B0, &CLinkedUpgradeList::AddUpgradeLink);
    ReversibleHooks::Install("CLinkedUpgradeList", "FindOtherUpgrade", 0x4C74D0, &CLinkedUpgradeList::FindOtherUpgrade);

// VTable
    ReversibleHooks::Install("CVehicleModelInfo", "GetModelType", 0x4C7650, &CVehicleModelInfo::GetModelType_Reversed);
    ReversibleHooks::Install("CVehicleModelInfo", "Init", 0x4C7630, &CVehicleModelInfo::Init_Reversed);
    ReversibleHooks::Install("CVehicleModelInfo", "DeleteRwObject", 0x4C9890, &CVehicleModelInfo::DeleteRwObject_Reversed);
    ReversibleHooks::Install("CVehicleModelInfo", "CreateInstance", 0x4C9680, &CVehicleModelInfo::CreateInstance_Reversed);
    ReversibleHooks::Install("CVehicleModelInfo", "SetAnimFile", 0x4C7670, &CVehicleModelInfo::SetAnimFile_Reversed);
    ReversibleHooks::Install("CVehicleModelInfo", "ConvertAnimFileIndex", 0x4C76D0, &CVehicleModelInfo::ConvertAnimFileIndex_Reversed);
    ReversibleHooks::Install("CVehicleModelInfo", "GetAnimFileIndex", 0x4C7660, &CVehicleModelInfo::GetAnimFileIndex_Reversed);
    ReversibleHooks::Install("CVehicleModelInfo", "SetClump", 0x4C95C0, &CVehicleModelInfo::SetClump_Reversed);

// Class methods
    ReversibleHooks::Install("CVehicleModelInfo", "SetAtomicRenderCallbacks", 0x4C7B10, &CVehicleModelInfo::SetAtomicRenderCallbacks);
    ReversibleHooks::Install("CVehicleModelInfo", "SetVehicleComponentFlags", 0x4C7C10, &CVehicleModelInfo::SetVehicleComponentFlags);
    ReversibleHooks::Install("CVehicleModelInfo", "GetWheelPosn", 0x4C7D20, &CVehicleModelInfo::GetWheelPosn);
    ReversibleHooks::Install("CVehicleModelInfo", "GetOriginalCompPosition", 0x4C7DD0, &CVehicleModelInfo::GetOriginalCompPosition);
    ReversibleHooks::Install("CVehicleModelInfo", "ChooseComponent", 0x4C8040, &CVehicleModelInfo::ChooseComponent);
    ReversibleHooks::Install("CVehicleModelInfo", "ChooseSecondComponent", 0x4C8120, &CVehicleModelInfo::ChooseSecondComponent);
    ReversibleHooks::Install("CVehicleModelInfo", "IsUpgradeAvailable", 0x4C8200, &CVehicleModelInfo::IsUpgradeAvailable);
    ReversibleHooks::Install("CVehicleModelInfo", "SetVehicleColour", 0x4C84B0, &CVehicleModelInfo::SetVehicleColour);
    ReversibleHooks::Install("CVehicleModelInfo", "ChooseVehicleColour", 0x4C8500, &CVehicleModelInfo::ChooseVehicleColour);
    ReversibleHooks::Install("CVehicleModelInfo", "GetNumRemaps", 0x4C86B0, &CVehicleModelInfo::GetNumRemaps);
    ReversibleHooks::Install("CVehicleModelInfo", "AddRemap", 0x4C86D0, &CVehicleModelInfo::AddRemap);
    ReversibleHooks::Install("CVehicleModelInfo", "SetRenderPipelines", 0x4C8900, &CVehicleModelInfo::SetRenderPipelines);
    ReversibleHooks::Install("CVehicleModelInfo", "GetCustomCarPlateText", 0x4C8970, &CVehicleModelInfo::GetCustomCarPlateText);
    ReversibleHooks::Install("CVehicleModelInfo", "SetCustomCarPlateText", 0x4C8980, &CVehicleModelInfo::SetCustomCarPlateText);
    ReversibleHooks::Install("CVehicleModelInfo", "ReduceMaterialsInVehicle", 0x4C8BD0, &CVehicleModelInfo::ReduceMaterialsInVehicle);
    ReversibleHooks::Install("CVehicleModelInfo", "SetCarCustomPlate", 0x4C9450, &CVehicleModelInfo::SetCarCustomPlate);
    ReversibleHooks::Install("CVehicleModelInfo", "DisableEnvMap", 0x4C97E0, &CVehicleModelInfo::DisableEnvMap);
    ReversibleHooks::Install("CVehicleModelInfo", "SetEnvMapCoeff", 0x4C9800, &CVehicleModelInfo::SetEnvMapCoeff);
    ReversibleHooks::Install("CVehicleModelInfo", "GetNumDoors", 0x4C73C0, &CVehicleModelInfo::GetNumDoors);
    ReversibleHooks::Install("CVehicleModelInfo", "PreprocessHierarchy", 0x4C8E60, &CVehicleModelInfo::PreprocessHierarchy);

// Static methods
    ReversibleHooks::Install("CVehicleModelInfo", "SetupLightFlags", 0x4C8C90, &CVehicleModelInfo::SetupLightFlags);
    ReversibleHooks::Install("CVehicleModelInfo", "ShutdownLightTexture", 0x4C7470, &CVehicleModelInfo::ShutdownLightTexture);
    ReversibleHooks::Install("CVehicleModelInfo", "GetMaximumNumberOfPassengersFromNumberOfDoors", 0x4C89B0, &CVehicleModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors);
    ReversibleHooks::Install("CVehicleModelInfo", "UseCommonVehicleTexDicationary", 0x4C75A0, &CVehicleModelInfo::UseCommonVehicleTexDicationary);
    ReversibleHooks::Install("CVehicleModelInfo", "StopUsingCommonVehicleTexDicationary", 0x4C75C0, &CVehicleModelInfo::StopUsingCommonVehicleTexDicationary);
    ReversibleHooks::Install("CVehicleModelInfo", "FindTextureCB", 0x4C7510, &CVehicleModelInfo::FindTextureCB);
    ReversibleHooks::Install("CVehicleModelInfo", "MoveObjectsCB", 0x4C7700, &CVehicleModelInfo::MoveObjectsCB);
    ReversibleHooks::Install("CVehicleModelInfo", "ResetEditableMaterials", 0x4C8460, &CVehicleModelInfo::ResetEditableMaterials);
    ReversibleHooks::Install("CVehicleModelInfo", "SetEditableMaterials", 0x4C8430, &CVehicleModelInfo::SetEditableMaterials);
    ReversibleHooks::Install("CVehicleModelInfo", "SetEditableMaterialsCB_RpMaterial", 0x4C8220, (RpMaterial*(*)(RpMaterial*, void*))(&CVehicleModelInfo::SetEditableMaterialsCB));
    ReversibleHooks::Install("CVehicleModelInfo", "SetEditableMaterialsCB_RpAtomic", 0x4C83E0, (RpAtomic * (*)(RpAtomic*, void*))(&CVehicleModelInfo::SetEditableMaterialsCB));
    ReversibleHooks::Install("CVehicleModelInfo", "StoreAtomicUsedMaterialsCB", 0x4C8B60, &CVehicleModelInfo::StoreAtomicUsedMaterialsCB);
    ReversibleHooks::Install("CVehicleModelInfo", "HideDamagedAtomicCB", 0x4C7720, &CVehicleModelInfo::HideDamagedAtomicCB);
    ReversibleHooks::Install("CVehicleModelInfo", "HideAllComponentsAtomicCB", 0x4C7790, &CVehicleModelInfo::HideAllComponentsAtomicCB);
    ReversibleHooks::Install("CVehicleModelInfo", "HasAlphaMaterialCB", 0x4C77C0, &CVehicleModelInfo::HasAlphaMaterialCB);
    ReversibleHooks::Install("CVehicleModelInfo", "SetAtomicRendererCB", 0x4C77E0, &CVehicleModelInfo::SetAtomicRendererCB);
    ReversibleHooks::Install("CVehicleModelInfo", "SetAtomicRendererCB_RealHeli", 0x4C7870, &CVehicleModelInfo::SetAtomicRendererCB_RealHeli);
    ReversibleHooks::Install("CVehicleModelInfo", "SetAtomicRendererCB_Plane", 0x4C7930, &CVehicleModelInfo::SetAtomicRendererCB_Plane);
    ReversibleHooks::Install("CVehicleModelInfo", "SetAtomicRendererCB_Boat", 0x4C79A0, &CVehicleModelInfo::SetAtomicRendererCB_Boat);
    ReversibleHooks::Install("CVehicleModelInfo", "SetAtomicRendererCB_Heli", 0x4C7A30, &CVehicleModelInfo::SetAtomicRendererCB_Heli);
    ReversibleHooks::Install("CVehicleModelInfo", "SetAtomicRendererCB_Train", 0x4C7AA0, &CVehicleModelInfo::SetAtomicRendererCB_Train);
    ReversibleHooks::Install("CVehicleModelInfo", "SetAtomicFlagCB", 0x4C7B90, &CVehicleModelInfo::SetAtomicFlagCB);
    ReversibleHooks::Install("CVehicleModelInfo", "ClearAtomicFlagCB", 0x4C7BB0, &CVehicleModelInfo::ClearAtomicFlagCB);
    ReversibleHooks::Install("CVehicleModelInfo", "AddWheelUpgrade", 0x4C8700, &CVehicleModelInfo::AddWheelUpgrade);
    ReversibleHooks::Install("CVehicleModelInfo", "GetNumWheelUpgrades", 0x4C8740, &CVehicleModelInfo::GetNumWheelUpgrades);
    ReversibleHooks::Install("CVehicleModelInfo", "GetWheelUpgrade", 0x4C8750, &CVehicleModelInfo::GetWheelUpgrade);
    ReversibleHooks::Install("CVehicleModelInfo", "DeleteVehicleColourTextures", 0x4C8770, &CVehicleModelInfo::DeleteVehicleColourTextures);
    ReversibleHooks::Install("CVehicleModelInfo", "SetDirtTextures", 0x5D5DB0, &CVehicleModelInfo::SetDirtTextures);
    ReversibleHooks::Install("CVehicleModelInfo", "ShutdownEnvironmentMaps", 0x4C87D0, &CVehicleModelInfo::ShutdownEnvironmentMaps);
    ReversibleHooks::Install("CVehicleModelInfo", "GetMatFXEffectMaterialCB", 0x4C8810, &CVehicleModelInfo::GetMatFXEffectMaterialCB);
    ReversibleHooks::Install("CVehicleModelInfo", "SetEnvironmentMapCB", 0x4C8840, &CVehicleModelInfo::SetEnvironmentMapCB);
    ReversibleHooks::Install("CVehicleModelInfo", "SetEnvMapCoeffCB", 0x4C88B0, &CVehicleModelInfo::SetEnvMapCoeffCB);
    ReversibleHooks::Install("CVehicleModelInfo", "SetRenderPipelinesCB", 0x4C88F4, &CVehicleModelInfo::SetRenderPipelinesCB);
    ReversibleHooks::Install("CVehicleModelInfo", "CollapseFramesCB", 0x4C8E30, &CVehicleModelInfo::CollapseFramesCB);
    ReversibleHooks::Install("CVehicleModelInfo", "SetEnvironmentMapAtomicCB", 0x4C9410, &CVehicleModelInfo::SetEnvironmentMapAtomicCB);
    ReversibleHooks::Install("CVehicleModelInfo", "SetEnvMapCoeffAtomicCB", 0x4C9430, &CVehicleModelInfo::SetEnvMapCoeffAtomicCB);
    ReversibleHooks::Install("CVehicleModelInfo", "AssignRemapTxd", 0x4C9360, &CVehicleModelInfo::AssignRemapTxd);

// Setup
    ReversibleHooks::Install("CVehicleModelInfo", "SetupCommonData", 0x5B8F00, &CVehicleModelInfo::SetupCommonData);
    ReversibleHooks::Install("CVehicleModelInfo", "LoadVehicleColours", 0x5B6890, &CVehicleModelInfo::LoadVehicleColours);
    ReversibleHooks::Install("CVehicleModelInfo", "LoadVehicleUpgrades", 0x5B65A0, &CVehicleModelInfo::LoadVehicleUpgrades);
    ReversibleHooks::Install("CVehicleModelInfo", "LoadEnvironmentMaps", 0x4C8780, &CVehicleModelInfo::LoadEnvironmentMaps);

// Other
    ReversibleHooks::Install("CVehicleModelInfo", "HELP_IsValidCompRule", 0x4C7E10, &IsValidCompRule);
    ReversibleHooks::Install("CVehicleModelInfo", "HELP_ChooseComponent", 0x4C7FB0, &::ChooseComponent);
    ReversibleHooks::Install("CVehicleModelInfo", "HELP_CountCompsInRule", 0x4C7F80, &CountCompsInRule);
    ReversibleHooks::Install("CVehicleModelInfo", "HELP_GetListOfComponentsNotUsedByRules", 0x4C7E50, &GetListOfComponentsNotUsedByRules);
    ReversibleHooks::Install("CVehicleModelInfo", "HELP_RemoveWindowAlphaCB", 0x4C83B0, &RemoveWindowAlphaCB);
    ReversibleHooks::Install("CVehicleModelInfo", "HELP_GetOkAndDamagedAtomicCB", 0x4C7BD0, &GetOkAndDamagedAtomicCB);
    ReversibleHooks::Install("CVehicleModelInfo", "HELP_atomicDefaultRenderCB", 0x7323C0, &atomicDefaultRenderCB);
}

CVehicleModelInfo::CVehicleModelInfo() : CClumpModelInfo()
{
    m_pVehicleStruct = nullptr;
    m_nNumColorVariations = 0;
    m_nFlags = 0;
    m_dwAnimBlockIndex = -1;
    memset(m_anUpgrades, 0xFF, sizeof(m_anUpgrades));
    for (int32 i = 0; i < 4; ++i)
        m_anRemapTxds[i] = -1;
}

ModelInfoType CVehicleModelInfo::GetModelType()
{
    return CVehicleModelInfo::GetModelType_Reversed();
}
ModelInfoType CVehicleModelInfo::GetModelType_Reversed()
{
    return ModelInfoType::MODEL_INFO_VEHICLE;
}

void CVehicleModelInfo::Init()
{
    CVehicleModelInfo::Init_Reversed();
}
void CVehicleModelInfo::Init_Reversed()
{
    CClumpModelInfo::Init();
    m_nVehicleType     = VEHICLE_TYPE_IGNORE;
    m_nWheelModelIndex = -1;
    m_fBikeSteerAngle  = 999.99F;
}

void CVehicleModelInfo::DeleteRwObject()
{
    CVehicleModelInfo::DeleteRwObject_Reversed();
}
void CVehicleModelInfo::DeleteRwObject_Reversed()
{
    if (m_pVehicleStruct)
        delete m_pVehicleStruct;

    m_pVehicleStruct = nullptr;
    CClumpModelInfo::DeleteRwObject();
}

RwObject* CVehicleModelInfo::CreateInstance()
{
    return CVehicleModelInfo::CreateInstance_Reversed();
}
RwObject* CVehicleModelInfo::CreateInstance_Reversed()
{
    auto pClump = reinterpret_cast<RpClump*>(CClumpModelInfo::CreateInstance());
    if (m_pVehicleStruct->m_nNumExtras) {
        RwFrame* frame;
        if (m_nVehicleType != VEHICLE_TYPE_BIKE
            && m_nVehicleType != VEHICLE_TYPE_BMX
            && m_nVehicleType >= VEHICLE_TYPE_BOAT) {

            frame = RpClumpGetFrame(pClump);
        }
        else {
            frame = CClumpModelInfo::GetFrameFromId(pClump, 1);
            if (!frame)
                frame = RpClumpGetFrame(pClump);
        }

        auto iFirstComp = CVehicleModelInfo::ChooseComponent();
        if (iFirstComp != -1 && m_pVehicleStruct->m_apExtras[iFirstComp]) {
            auto& pExtra = m_pVehicleStruct->m_apExtras[iFirstComp];
            auto pAtomicClone = RpAtomicClone(pExtra);
            auto pNewFrame = RwFrameCreate();
            RwFrameTransform(pNewFrame, RwFrameGetMatrix(RpAtomicGetFrame(pExtra)), RwOpCombineType::rwCOMBINEREPLACE);
            RpAtomicSetFrame(pAtomicClone, pNewFrame);
            RpClumpAddAtomic(pClump, pAtomicClone);
            RwFrameAddChild(frame, pNewFrame);
        }
        CVehicleModelInfo::ms_compsUsed[0] = iFirstComp;

        auto iSecondComp = CVehicleModelInfo::ChooseSecondComponent();
        if (iSecondComp != -1 && m_pVehicleStruct->m_apExtras[iSecondComp]) {
            auto& pExtra = m_pVehicleStruct->m_apExtras[iSecondComp];
            auto pAtomicClone = RpAtomicClone(pExtra);
            auto pNewFrame = RwFrameCreate();
            RwFrameTransform(pNewFrame, RwFrameGetMatrix(RpAtomicGetFrame(pExtra)), RwOpCombineType::rwCOMBINEREPLACE);
            RpAtomicSetFrame(pAtomicClone, pNewFrame);
            RpClumpAddAtomic(pClump, pAtomicClone);
            RwFrameAddChild(frame, pNewFrame);
        }
        CVehicleModelInfo::ms_compsUsed[1] = iSecondComp;
    }
    else {
        CVehicleModelInfo::ms_compsUsed[0] = -1;
        CVehicleModelInfo::ms_compsUsed[1] = -1;
    }

    RpClumpForAllAtomics(pClump, CVehicleModelInfo::SetEnvironmentMapAtomicCB, nullptr);
    return reinterpret_cast<RwObject*>(pClump);
}

void CVehicleModelInfo::SetAnimFile(char const* filename)
{
    return CVehicleModelInfo::SetAnimFile_Reversed(filename);
}
void CVehicleModelInfo::SetAnimFile_Reversed(char const* filename)
{
    if (!strcmp(filename, "null")) {
        m_dwAnimBlockIndex = -1;
        return;
    }

    auto pName = new char[strlen(filename) + 1];
    m_animBlockFileName = pName;
    strcpy(pName, filename);
}

void CVehicleModelInfo::ConvertAnimFileIndex()
{
    CVehicleModelInfo::ConvertAnimFileIndex_Reversed();
}
void CVehicleModelInfo::ConvertAnimFileIndex_Reversed()
{
    if (m_dwAnimBlockIndex == -1)
        return;

    auto iIndex = CAnimManager::GetAnimationBlockIndex(m_animBlockFileName);
    delete[] m_animBlockFileName;
    m_dwAnimBlockIndex = iIndex;
}

signed int CVehicleModelInfo::GetAnimFileIndex()
{
    return CVehicleModelInfo::GetAnimFileIndex_Reversed();
}
signed int CVehicleModelInfo::GetAnimFileIndex_Reversed()
{
    return m_dwAnimBlockIndex;
}

void CVehicleModelInfo::SetClump(RpClump* clump)
{
    CVehicleModelInfo::SetClump_Reversed(clump);
}
void CVehicleModelInfo::SetClump_Reversed(RpClump* clump)
{
    m_pVehicleStruct = new CVehicleStructure();
    CClumpModelInfo::SetClump(clump);
    CVehicleModelInfo::SetAtomicRenderCallbacks();
    CClumpModelInfo::SetFrameIds(ms_vehicleDescs[m_nVehicleType]);
    CVehicleModelInfo::SetRenderPipelines();
    CVehicleModelInfo::PreprocessHierarchy();
    CVehicleModelInfo::ReduceMaterialsInVehicle();
    m_nCurrentPrimaryColor = 255;
    m_nCurrentSecondaryColor = 255;
    m_nCurrentTertiaryColor = 255;
    m_nCurrentQuaternaryColor = 255;
    CVehicleModelInfo::SetCarCustomPlate();
}

void CVehicleModelInfo::SetAtomicRenderCallbacks()
{
    if (m_nVehicleType == VEHICLE_TYPE_TRAIN)
        RpClumpForAllAtomics(m_pRwClump, CVehicleModelInfo::SetAtomicRendererCB_Train, nullptr);
    else if (m_nVehicleType == VEHICLE_TYPE_PLANE || m_nVehicleType == VEHICLE_TYPE_FPLANE)
        RpClumpForAllAtomics(m_pRwClump, CVehicleModelInfo::SetAtomicRendererCB_Plane, nullptr);
    else if (m_nVehicleType == VEHICLE_TYPE_BOAT)
        RpClumpForAllAtomics(m_pRwClump, CVehicleModelInfo::SetAtomicRendererCB_Boat, m_pRwClump);
    else if (m_nVehicleType == VEHICLE_TYPE_HELI)
        RpClumpForAllAtomics(m_pRwClump, CVehicleModelInfo::SetAtomicRendererCB_RealHeli, m_pRwClump);
    else
        RpClumpForAllAtomics(m_pRwClump, CVehicleModelInfo::SetAtomicRendererCB, m_pRwClump);
}

void CVehicleModelInfo::SetVehicleComponentFlags(RwFrame* component, uint32 flags)
{
    tVehicleComponentFlagsUnion flagsUnion;
    flagsUnion.m_nFlags = flags;

    auto pHandling = &gHandlingDataMgr.m_aVehicleHandling[m_nHandlingId];
    if (flagsUnion.bCull)
        RwFrameForAllObjects(component, CVehicleModelInfo::SetAtomicFlagCB, (void*)eAtomicComponentFlag::ATOMIC_CULL);

    if (flagsUnion.bRenderAlways)
        RwFrameForAllObjects(component, CVehicleModelInfo::SetAtomicFlagCB, (void*)eAtomicComponentFlag::ATOMIC_RENDER_ALWAYS);

    if (flagsUnion.bDisableReflections)
        RwFrameForAllObjects(component, CVehicleModelInfo::SetAtomicFlagCB, (void*)eAtomicComponentFlag::ATOMIC_DISABLE_REFLECTIONS);

    if (flagsUnion.bIsFront)
        RwFrameForAllObjects(component, CVehicleModelInfo::SetAtomicFlagCB, (void*)eAtomicComponentFlag::ATOMIC_IS_FRONT);
    else if (flagsUnion.bIsRear && (pHandling->m_bIsVan || !(flagsUnion.bIsLeft || flagsUnion.bIsRight)))
        RwFrameForAllObjects(component, CVehicleModelInfo::SetAtomicFlagCB, (void*)eAtomicComponentFlag::ATOMIC_IS_REAR);
    else if (flagsUnion.bIsLeft)
        RwFrameForAllObjects(component, CVehicleModelInfo::SetAtomicFlagCB, (void*)eAtomicComponentFlag::ATOMIC_IS_LEFT);
    else if (flagsUnion.bIsRight)
        RwFrameForAllObjects(component, CVehicleModelInfo::SetAtomicFlagCB, (void*)eAtomicComponentFlag::ATOMIC_IS_RIGHT);

    if (flagsUnion.bSwinging && (pHandling->m_bIsHatchback || flagsUnion.bIsFrontDoor || flagsUnion.bIsRearDoor))
        RwFrameForAllObjects(component, CVehicleModelInfo::SetAtomicFlagCB, (void*)eAtomicComponentFlag::ATOMIC_VEHCOMP_15);

    if (flagsUnion.bIsRearDoor)
        RwFrameForAllObjects(component, CVehicleModelInfo::SetAtomicFlagCB, (void*)eAtomicComponentFlag::ATOMIC_IS_REAR_DOOR);
    else if (flagsUnion.bIsFrontDoor)
        RwFrameForAllObjects(component, CVehicleModelInfo::SetAtomicFlagCB, (void*)eAtomicComponentFlag::ATOMIC_IS_FRONT_DOOR);

    if (flagsUnion.bHasAlpha)
        RwFrameForAllObjects(component, CVehicleModelInfo::SetAtomicFlagCB, (void*)eAtomicComponentFlag::ATOMIC_HAS_ALPHA);
}

void CVehicleModelInfo::GetWheelPosn(int32 wheel, CVector& outVec, bool local)
{
    auto frame = CClumpModelInfo::GetFrameFromId(m_pRwClump, CVehicleModelInfo::ms_wheelFrameIDs[wheel]);

    if (m_nVehicleType != VEHICLE_TYPE_PLANE || local)
        outVec = *RwMatrixGetPos(RwFrameGetMatrix(frame));
    else {
        auto pMatrix = RwMatrixCreate();
        memcpy(pMatrix, RwFrameGetMatrix(frame), sizeof(CMatrix));
        auto pParent = RwFrameGetParent(frame);
        while (pParent) {
            RwMatrixTransform(pMatrix, RwFrameGetMatrix(pParent), RwOpCombineType::rwCOMBINEPOSTCONCAT);
            pParent = RwFrameGetParent(pParent);
        }

        outVec = *RwMatrixGetPos(pMatrix);
        RwMatrixDestroy(pMatrix);
    }
}

bool CVehicleModelInfo::GetOriginalCompPosition(CVector& outVec, int32 component)
{
    auto frame = CClumpModelInfo::GetFrameFromId(m_pRwClump, component);
    if (!frame)
        return false;

    outVec = *RwMatrixGetPos(RwFrameGetMatrix(frame));
    return true;
}

int32 CVehicleModelInfo::ChooseComponent()
{
    auto result = CVehicleModelInfo::ms_compsToUse[0];
    if (result != -2) {
        CVehicleModelInfo::ms_compsToUse[0] = -2;
        return result;
    }

    if (m_extraComps.nExtraARule && IsValidCompRule(m_extraComps.nExtraARule)) {
        return ::ChooseComponent(m_extraComps.nExtraARule, m_extraComps.nExtraAComp);
    }
    else if (CGeneral::GetRandomNumberInRange(0, 3) < 2) {
        int32 anVariations[6];
        auto numComps = GetListOfComponentsNotUsedByRules(m_extraComps.m_nComps, m_pVehicleStruct->m_nNumExtras, anVariations);
        if (numComps)
            return anVariations[CGeneral::GetRandomNumberInRange(0, numComps)];
    }

    return -1;
}

int32 CVehicleModelInfo::ChooseSecondComponent()
{
    auto result = CVehicleModelInfo::ms_compsToUse[1];
    if (result != -2) {
        CVehicleModelInfo::ms_compsToUse[1] = -2;
        return result;
    }

    if (m_extraComps.nExtraBRule && IsValidCompRule(m_extraComps.nExtraBRule)) {
        return ::ChooseComponent(m_extraComps.nExtraBRule, m_extraComps.nExtraBComp);
    }
    else if (CGeneral::GetRandomNumberInRange(0, 3) < 2) {
        int32 anVariations[6];
        auto numComps = GetListOfComponentsNotUsedByRules(m_extraComps.m_nComps, m_pVehicleStruct->m_nNumExtras, anVariations);
        if (numComps)
            return anVariations[CGeneral::GetRandomNumberInRange(0, numComps)];
    }

    return -1;
}

bool CVehicleModelInfo::IsUpgradeAvailable(eVehicleUpgradePosn upgrade)
{
    return m_pVehicleStruct->m_aUpgrades[upgrade].m_nParentComponentId >= 0;
}

void CVehicleModelInfo::SetVehicleColour(uint8 prim, uint8 sec, uint8 tert, uint8 quat)
{
    CVehicleModelInfo::ms_currentCol[0] = prim;
    CVehicleModelInfo::ms_currentCol[1] = sec;
    CVehicleModelInfo::ms_currentCol[2] = tert;
    CVehicleModelInfo::ms_currentCol[3] = quat;

    m_nCurrentPrimaryColor = prim;
    m_nCurrentSecondaryColor = sec;
    m_nCurrentTertiaryColor = tert;
    m_nCurrentQuaternaryColor = quat;
}

// 0x4C8500
void CVehicleModelInfo::ChooseVehicleColour(uint8& prim, uint8& sec, uint8& tert, uint8& quat, int32 variationShift)
{
    if (!m_nNumColorVariations || CCheat::m_aCheatsActive[eCheats::CHEAT_BLACK_TRAFFIC]) {
        prim = 0;
        sec = 0;
        tert = 0;
        quat = 0;
        return;
    }

    if (CCheat::m_aCheatsActive[eCheats::CHEAT_PINK_TRAFFIC]) {
        prim = 126;
        sec = 126;
        tert = 126;
        quat = 126;
        return;
    }

    auto iVariation = (variationShift + m_nLastColorVariation) % m_nNumColorVariations;
    m_nLastColorVariation = iVariation;
    prim = m_anPrimaryColors[iVariation];
    sec = m_anSecondaryColors[iVariation];
    tert = m_anTertiaryColors[iVariation];
    quat = m_anQuaternaryColors[iVariation];

    if (m_nNumColorVariations <= 1)
        return;

    auto vehicle = FindPlayerVehicle(-1, false);
    if (!vehicle)
        return;

    if (CModelInfo::GetModelInfo(vehicle->m_nModelIndex) == this
        && vehicle->m_nPrimaryColor == prim
        && vehicle->m_nSecondaryColor == sec
        && vehicle->m_nTertiaryColor == tert
        && vehicle->m_nQuaternaryColor == quat) {

        iVariation = (variationShift + m_nLastColorVariation) % m_nNumColorVariations;
        m_nLastColorVariation = iVariation;
        prim = m_anPrimaryColors[iVariation];
        sec = m_anSecondaryColors[iVariation];
        tert = m_anTertiaryColors[iVariation];
        quat = m_anQuaternaryColors[iVariation];
    }
}

// 0x4C86B0
int32 CVehicleModelInfo::GetNumRemaps()
{
    auto iCount = 0;
    for (int32 i = 0; i < 4; ++i) {
        if (m_anRemapTxds[i] == -1)
            break;

        ++iCount;
    }

    return iCount;
}

// 0x4C86D0
void CVehicleModelInfo::AddRemap(int32 txd)
{
    auto numRemaps = CVehicleModelInfo::GetNumRemaps();
    m_anRemapTxds[numRemaps] = txd;

}

void CVehicleModelInfo::SetRenderPipelines()
{
    CCarFXRenderer::CustomCarPipeClumpSetup(m_pRwClump);
    if (carFrame)
        return;

    carFrame = RwFrameCreate();
    const CVector axis{1.0F, 0.0f, 0.0f};
    RwMatrixRotate(RwFrameGetMatrix(carFrame), &axis, 60.0F, RwOpCombineType::rwCOMBINEREPLACE);
    RwFrameUpdateObjects(carFrame);
    RwFrameGetLTM(carFrame);
}

char* CVehicleModelInfo::GetCustomCarPlateText()
{
    if (!m_szPlateText[0])
        return nullptr;

    return m_szPlateText;
}

void CVehicleModelInfo::SetCustomCarPlateText(char* text)
{
    if (!text) {
        m_szPlateText[0] = '\0';
        return;
    }

    strncpy(m_szPlateText, text, 8);
}

void CVehicleModelInfo::ReduceMaterialsInVehicle()
{
    CMemoryMgr::LockScratchPad();
    CMemoryMgr::InitScratchPad();

    RpMaterialList matList;
    matList.space = 20;
    matList.numMaterials = 0;
    matList.materials = new RpMaterial*[matList.space];

    // CTimer::GetCurrentTimeInCycles(); // unused code used for performance diagnostics i guess
    RpClumpForAllAtomics(m_pRwClump, CVehicleModelInfo::StoreAtomicUsedMaterialsCB, &matList);
    for (int32 i = 0; i < m_pVehicleStruct->m_nNumExtras; ++i)
        StoreAtomicUsedMaterialsCB(m_pVehicleStruct->m_apExtras[i], &matList);

    // CTimer::GetCurrentTimeInCycles();
    // CTimer::GetCyclesPerMillisecond();
    _rpMaterialListDeinitialize(&matList);
    CMemoryMgr::ReleaseScratchPad();
    CVisibilityPlugins::ClearClumpForAllAtomicsFlag(m_pRwClump, eAtomicComponentFlag::ATOMIC_DISABLE_REFLECTIONS);
}

void CVehicleModelInfo::SetCarCustomPlate()
{
    m_pPlateMaterial = nullptr;
    CVehicleModelInfo::SetCustomCarPlateText(nullptr);

    char plateBuffer[8];
    CCustomCarPlateMgr::GeneratePlateText(plateBuffer, 8);
    auto pMaterial = CCustomCarPlateMgr::SetupClump(m_pRwClump, plateBuffer, m_nPlateType);
    if (pMaterial)
        m_pPlateMaterial = pMaterial;
}

void CVehicleModelInfo::DisableEnvMap()
{
    if (!m_pRwObject)
        return;

    RpClumpForAllAtomics(m_pRwClump, CVehicleModelInfo::SetEnvironmentMapAtomicCB, (void*)0xFFFF);
}

void CVehicleModelInfo::SetEnvMapCoeff(float coeff)
{
    auto iUsedCoeff = static_cast<int32>(floor(coeff * 1000.0F));
    if (!m_pRwObject)
        return;

    RpClumpForAllAtomics(m_pRwClump, CVehicleModelInfo::SetEnvMapCoeffAtomicCB, (void*)iUsedCoeff);
}

int32 CVehicleModelInfo::GetNumDoors()
{
    return m_nNumDoors;
}

void CVehicleModelInfo::PreprocessHierarchy()
{
    m_nNumDoors = 0;
    RpAtomic* pMainWheelAtomic = nullptr;
    RpAtomic* pTrainBogieAtomic = nullptr;
    auto& pHandling = gHandlingDataMgr.m_aVehicleHandling[m_nHandlingId];
    RwObjectNameIdAssocation* pNameIdAssoc = CVehicleModelInfo::ms_vehicleDescs[m_nVehicleType];
    while (pNameIdAssoc->m_pName) {
        auto flags = pNameIdAssoc->AsFlagsUnion();

        if (flags.bIsDummy || flags.bIsExtra || flags.bIsUpgrade) {
            auto searchStruct = tCompSearchStructByName(pNameIdAssoc->m_pName, nullptr);
            RwFrameForAllChildren(RpClumpGetFrame(m_pRwClump), CClumpModelInfo::FindFrameFromNameWithoutIdCB, &searchStruct);
            if (searchStruct.m_pFrame) {
                if (flags.bIsDummy) {
                    auto& pVecDummyPos = m_pVehicleStruct->m_avDummyPos[pNameIdAssoc->m_dwHierarchyId];
                    pVecDummyPos = *RwMatrixGetPos(RwFrameGetMatrix(searchStruct.m_pFrame));
                    auto pParent = RwFrameGetParent(searchStruct.m_pFrame);
                    if (pParent) {
                        while (RwFrameGetParent(pParent)) {
                            RwV3dTransformPoints(&pVecDummyPos, &pVecDummyPos, 1, RwFrameGetMatrix(pParent));
                            pParent = RwFrameGetParent(pParent);
                        }
                    }
                    RwFrameDestroy(searchStruct.m_pFrame);
                }
                else if (flags.bIsUpgrade) {
                    auto pParent = RwFrameGetParent(searchStruct.m_pFrame);
                    auto parentHierarchyId = CVisibilityPlugins::GetFrameHierarchyId(pParent);
                    auto& upgrade = m_pVehicleStruct->m_aUpgrades[pNameIdAssoc->m_dwHierarchyId];
                    upgrade.m_vPosition = *RwMatrixGetPos(RwFrameGetMatrix(searchStruct.m_pFrame));
                    upgrade.m_qRotation.Set(*RwFrameGetMatrix(searchStruct.m_pFrame));
                    upgrade.m_nParentComponentId = parentHierarchyId;
                }
                else {
                    auto pAtomic = reinterpret_cast<RpAtomic*>(GetFirstObject(searchStruct.m_pFrame));
                    RpClumpRemoveAtomic(m_pRwClump, pAtomic);
                    RwFrameRemoveChild(searchStruct.m_pFrame);
                    CVehicleModelInfo::SetVehicleComponentFlags(searchStruct.m_pFrame, pNameIdAssoc->m_dwFlags);
                    m_pVehicleStruct->m_apExtras[m_pVehicleStruct->m_nNumExtras] = pAtomic;
                    ++m_pVehicleStruct->m_nNumExtras;
                }
            }
        }

        if (flags.bIsMainWheel || flags.bIsTrainFrontBogie) {
            auto searchStruct = tCompSearchStructById(pNameIdAssoc->m_dwHierarchyId, nullptr);
            RwFrameForAllChildren(RpClumpGetFrame(m_pRwClump), CClumpModelInfo::FindFrameFromIdCB, &searchStruct);
            if (searchStruct.m_pFrame) {
                auto frame = searchStruct.m_pFrame;
                auto bNoChild = false;
                while (!GetFirstObject(frame)) {
                    frame = GetFirstChild(frame);
                    if (!frame) {
                        bNoChild = true;
                        break;
                    }
                }

                if (!bNoChild) {
                    if (flags.bIsMainWheel)
                        pMainWheelAtomic = reinterpret_cast<RpAtomic*>(GetFirstObject(frame));
                    else
                        pTrainBogieAtomic = reinterpret_cast<RpAtomic*>(GetFirstObject(frame));
                }
            }
        }

        pNameIdAssoc++;
    }

    pNameIdAssoc = CVehicleModelInfo::ms_vehicleDescs[m_nVehicleType];
    while (pNameIdAssoc->m_pName) {
        auto flags = pNameIdAssoc->AsFlagsUnion();

        if (flags.bIsDummy || flags.bIsExtra || flags.bIsUpgrade) {
            pNameIdAssoc++;
            continue;
        }

        auto searchStruct = tCompSearchStructById(pNameIdAssoc->m_dwHierarchyId, nullptr);
        RwFrameForAllChildren(RpClumpGetFrame(m_pRwClump), CClumpModelInfo::FindFrameFromIdCB, &searchStruct);
        if (!searchStruct.m_pFrame) {
            pNameIdAssoc++;
            continue;
        }

        auto frame = searchStruct.m_pFrame;
        if (flags.bIsDoor)
            ++m_nNumDoors;

        if (flags.bIsDamageable) {
            RpAtomic* aOkDamAtomics[2]{ nullptr, nullptr };
            RwFrameForAllChildren(frame, CVehicleModelInfo::CollapseFramesCB, frame);
            RwFrameUpdateObjects(frame);
            RwFrameForAllObjects(frame, GetOkAndDamagedAtomicCB, aOkDamAtomics);
            if (aOkDamAtomics[0] && aOkDamAtomics[1]) {
                RpAtomicSetRenderCallBack(aOkDamAtomics[1], RpAtomicGetRenderCallBack(aOkDamAtomics[0]));
                m_pVehicleStruct->m_nMaskComponentsDamagable |= (1 << pNameIdAssoc->m_dwHierarchyId);
            }
        }

        CVehicleModelInfo::SetVehicleComponentFlags(frame, pNameIdAssoc->m_dwFlags);

        if (flags.bIsWheel || flags.bIsMainWheel) {
            if (pMainWheelAtomic) {
                if (flags.bIsMainWheel) {
                    RwFrameForAllChildren(frame, CVehicleModelInfo::CollapseFramesCB, frame);
                    RwFrameUpdateObjects(frame);
                    CVisibilityPlugins::SetAtomicRenderCallback(pMainWheelAtomic, atomicDefaultRenderCB); // in android idb it's CVisibilityPlugins::RenderWheelAtomicCB
                }
                else {
                    auto pClone = RpAtomicClone(pMainWheelAtomic);
                    RpAtomicSetFrame(pClone, frame);
                    RpClumpAddAtomic(m_pRwClump, pClone);
                    if (pNameIdAssoc->m_dwHierarchyId != CAR_WHEEL_RF
                        && pNameIdAssoc->m_dwHierarchyId != CAR_WHEEL_LF
                        && pHandling.m_bDoubleRwheels) {

                        auto pClone2 = RpAtomicClone(pMainWheelAtomic);
                        auto pNewFrame = RwFrameCreate();
                        RpAtomicSetFrame(pClone2, pNewFrame);
                        RwFrameAddChild(frame, pNewFrame);
                        auto fOffset = fRearDoubleWheelOffsetFactor * -0.25F;
                        auto pMatrix = RwFrameGetMatrix(pNewFrame);
                        *RwMatrixGetRight(pMatrix) = { 1.0F, 0.0F, 0.0F };
                        *RwMatrixGetUp(pMatrix)    = { 0.0F, 1.0F, 0.0F };
                        *RwMatrixGetAt(pMatrix)    = { 0.0F, 0.0F, 1.0F };
                        *RwMatrixGetPos(pMatrix)   = { fOffset, 0.0F, 0.0F };
                        pMatrix->flags |= (rwMATRIXINTERNALIDENTITY | rwMATRIXTYPEORTHONORMAL);
                        RpClumpAddAtomic(m_pRwClump, pClone2);
                        CVisibilityPlugins::SetAtomicRenderCallback(pClone2, atomicDefaultRenderCB); // in android idb it's CVisibilityPlugins::RenderWheelAtomicCB
                    }
                }
            }
        }
        else if (flags.bIsTrainRearBogie && pTrainBogieAtomic) {
            auto pClone = RpAtomicClone(pTrainBogieAtomic);
            RpAtomicSetFrame(pClone, frame);
            RpClumpAddAtomic(m_pRwClump, pClone);
            CVisibilityPlugins::SetAtomicRenderCallback(pClone, atomicDefaultRenderCB);
        }

        pNameIdAssoc++;
    }
}

void CVehicleModelInfo::SetupLightFlags(CVehicle* vehicle)
{
    CVehicleModelInfo::ms_lightsOn[0] = vehicle->m_renderLights.m_bLeftFront;
    CVehicleModelInfo::ms_lightsOn[1] = vehicle->m_renderLights.m_bRightFront;
    CVehicleModelInfo::ms_lightsOn[2] = vehicle->m_renderLights.m_bLeftRear;
    CVehicleModelInfo::ms_lightsOn[3] = vehicle->m_renderLights.m_bRightRear;
}

int32 CVehicleModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors(int32 modelId)
{
    auto mi = CModelInfo::GetModelInfo(modelId)->AsVehicleModelInfoPtr();
    if (mi->IsBoat() || mi->IsTrailer())
        return 0;

    int32 iDoorsNum;
    switch (modelId) {
    case -1:
        iDoorsNum = 3;
        break;

    case eModelID::MODEL_FIRETRUK:
    case eModelID::MODEL_JOURNEY:
        iDoorsNum = 2;
        break;

    case eModelID::MODEL_HUNTER:
        iDoorsNum = 1;
        break;

    default:
        iDoorsNum = mi->GetNumDoors();
        if (iDoorsNum)
            break;

        if (mi->IsBike() || gHandlingDataMgr.GetVehiclePointer(mi->m_nHandlingId)->m_bTandemSeats) {
            return mi->m_pVehicleStruct->IsDummyActive(eVehicleDummies::DUMMY_SEAT_REAR) ? 1 : 0;
        }
        else {
            if (modelId == eModelID::MODEL_RCBANDIT || modelId == eModelID::MODEL_RCTIGER)
                return 0;
            return 1;
        }
    }

    if (gHandlingDataMgr.GetVehiclePointer(mi->m_nHandlingId)->m_bTandemSeats)
        return std::max(0, (iDoorsNum - 2) / 2);

    if (modelId == eModelID::MODEL_COACH || modelId == eModelID::MODEL_BUS)
        return 8;

    return iDoorsNum - 1;
}

RwObject* CVehicleModelInfo::MoveObjectsCB(RwObject* object, void* data)
{
    RpAtomicSetFrame(reinterpret_cast<RpAtomic*>(object), reinterpret_cast<RwFrame*>(data));
    return object;
}

RpMaterial* CVehicleModelInfo::SetEditableMaterialsCB(RpMaterial* material, void* data)
{
    auto ppEntries = reinterpret_cast<tRestoreEntry**>(data);

    CRGBA color = *RpMaterialGetColor(material);
    color.a = 0;

    if (CVehicleModelInfo::ms_pRemapTexture
        && RpMaterialGetTexture(material)
        && RwTextureGetName(RpMaterialGetTexture(material))[0] == '#') {

        (*ppEntries)->m_pAddress = &material->texture;
        (*ppEntries)->m_pValue = material->texture;
        (*ppEntries)++;

        material->texture = CVehicleModelInfo::ms_pRemapTexture;
    }

    if (RpMaterialGetTexture(material) == CVehicleModelInfo::ms_pLightsTexture) {
        int32 iLightIndex = -1;
        if (color == CRGBA(255, 175, 0, 0))
            iLightIndex = 0;
        else if (color == CRGBA(0, 255, 200, 0))
            iLightIndex = 1;
        else if (color == CRGBA(185, 255, 0, 0))
            iLightIndex = 2;
        else if (color == CRGBA(255, 60, 0, 0))
            iLightIndex = 3;

        (*ppEntries)->m_pAddress = RpMaterialGetColor(material);
        (*ppEntries)->m_pValue = *reinterpret_cast<void**>(RpMaterialGetColor(material));
        (*ppEntries)++;

        RpMaterialGetColor(material)->red = 255;
        RpMaterialGetColor(material)->green = 255;
        RpMaterialGetColor(material)->blue = 255;

        if (iLightIndex != -1 && CVehicleModelInfo::ms_lightsOn[iLightIndex]) {
            (*ppEntries)->m_pAddress = &material->texture;
            (*ppEntries)->m_pValue = material->texture;
            (*ppEntries)++;

            (*ppEntries)->m_pAddress = RpMaterialGetSurfaceProperties(material);
            (*ppEntries)->m_pValue = *(void**)RpMaterialGetSurfaceProperties(material);
            (*ppEntries)++;

            material->texture = CVehicleModelInfo::ms_pLightsOnTexture;
            RpMaterialSetSurfaceProperties(material, &gLightSurfProps);
        }
    }
    else {
        int32 iColorIndex;
        if (color == CRGBA(60, 255, 0, 0))
            iColorIndex = CVehicleModelInfo::ms_currentCol[0];
        else if (color == CRGBA(255, 0, 175, 0))
            iColorIndex = CVehicleModelInfo::ms_currentCol[1];
        else if (color == CRGBA(0, 255, 255, 0))
            iColorIndex = CVehicleModelInfo::ms_currentCol[2];
        else if (color == CRGBA(255, 0, 255, 0))
            iColorIndex = CVehicleModelInfo::ms_currentCol[3];
        else
            return material;

        (*ppEntries)->m_pAddress = RpMaterialGetColor(material);
        (*ppEntries)->m_pValue = *reinterpret_cast<void**>(RpMaterialGetColor(material));
        (*ppEntries)++;

        auto& pColor = CVehicleModelInfo::ms_vehicleColourTable[iColorIndex];
        RpMaterialGetColor(material)->red = pColor.r;
        RpMaterialGetColor(material)->green = pColor.g;
        RpMaterialGetColor(material)->blue = pColor.b;
    }

    return material;
}

RpAtomic* CVehicleModelInfo::SetEditableMaterialsCB(RpAtomic* atomic, void* data)
{
    if (rwObjectTestFlags(atomic, RpAtomicFlag::rpATOMICRENDER) == 0)
        return atomic;

    if (CVisibilityPlugins::GetAtomicId(atomic) & eAtomicComponentFlag::ATOMIC_IS_DOOR_WINDOW_OPENED)
        RpGeometryForAllMaterials(RpAtomicGetGeometry(atomic), RemoveWindowAlphaCB, data);

    RpGeometryForAllMaterials(RpAtomicGetGeometry(atomic), CVehicleModelInfo::SetEditableMaterialsCB, data);
    return atomic;
}

void CVehicleModelInfo::ShutdownLightTexture()
{
    if (CVehicleModelInfo::ms_pLightsTexture) {
        RwTextureDestroy(CVehicleModelInfo::ms_pLightsTexture);
        CVehicleModelInfo::ms_pLightsTexture = nullptr;
    }

    if (CVehicleModelInfo::ms_pLightsOnTexture) {
        RwTextureDestroy(CVehicleModelInfo::ms_pLightsOnTexture);
        CVehicleModelInfo::ms_pLightsOnTexture = nullptr;
    }
}

RwTexture* CVehicleModelInfo::FindTextureCB(char const* name)
{
    auto dictTex = RwTexDictionaryFindNamedTexture(vehicleTxd, name);
    if (dictTex)
        return dictTex;

    auto pCurrent = RwTexDictionaryGetCurrent();
    auto pNamed = RwTexDictionaryFindNamedTexture(pCurrent, name);
    if (strncmp(name, "remap", 5))
        return pNamed;

    // Remap below this point
    if (pNamed) {
        pNamed->name[0] = '#';
        return pNamed;
    }

    char buffer[32];
    strcpy(buffer, name);
    buffer[0] = '#';
    return RwTexDictionaryFindNamedTexture(pCurrent, buffer);
}

void CVehicleModelInfo::UseCommonVehicleTexDicationary()
{
    CVehicleModelInfo::SavedTextureFindCallback = RwTextureGetFindCallBack();
    RwTextureSetFindCallBack(CVehicleModelInfo::FindTextureCB);
}

void CVehicleModelInfo::StopUsingCommonVehicleTexDicationary()
{
    RwTextureSetFindCallBack(CVehicleModelInfo::SavedTextureFindCallback);
    CVehicleModelInfo::SavedTextureFindCallback = nullptr;
}

void CVehicleModelInfo::SetEditableMaterials(RpClump* clump)
{
    auto pEntry = gRestoreEntries;
    RpClumpForAllAtomics(clump, CVehicleModelInfo::SetEditableMaterialsCB, &pEntry);
    pEntry->m_pAddress = nullptr;
}

void CVehicleModelInfo::ResetEditableMaterials(RpClump* clump)
{
    auto pEntry = gRestoreEntries;
    while (pEntry->m_pAddress) {
        *(uint32*)pEntry->m_pAddress = (uint32)pEntry->m_pValue;
        pEntry++;
    }
}

RpAtomic* CVehicleModelInfo::HideDamagedAtomicCB(RpAtomic* atomic, void* data)
{
    auto frame = RpAtomicGetFrame(atomic);
    auto pNodeName = GetFrameNodeName(frame);
    if (strstr(pNodeName, "_dam")) {
        RpAtomicSetFlags(atomic, 0);
        CVisibilityPlugins::SetAtomicFlag(atomic, eAtomicComponentFlag::ATOMIC_IS_DAM_STATE);
        return atomic;
    }

    if (strstr(pNodeName, "_ok"))
        CVisibilityPlugins::SetAtomicFlag(atomic, eAtomicComponentFlag::ATOMIC_IS_OK_STATE);

    return atomic;
}

RpAtomic* CVehicleModelInfo::HideAllComponentsAtomicCB(RpAtomic* atomic, void* data)
{
    auto uiData = reinterpret_cast<uint32>(data);
    auto checkedFlags = uiData & CVisibilityPlugins::GetAtomicId(atomic);
    if (checkedFlags)
        RpAtomicSetFlags(atomic, 0);
    else
        RpAtomicSetFlags(atomic, RpAtomicFlag::rpATOMICRENDER);

    return atomic;
}

RpMaterial* CVehicleModelInfo::HasAlphaMaterialCB(RpMaterial* material, void* data)
{
    if (RpMaterialGetColor(material)->alpha != 255) {
        *reinterpret_cast<bool*>(data) = true;
        return nullptr;
    }

    return material;
}

RpAtomic* CVehicleModelInfo::SetAtomicRendererCB(RpAtomic* atomic, void* data)
{
    auto pNodeName = GetFrameNodeName(RpAtomicGetFrame(atomic));
    if (strstr(pNodeName, "_vlo")) {
        CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderVehicleReallyLowDetailCB);
    }
    else {
        auto pGeometry = RpAtomicGetGeometry(atomic);
        bool bHasAlpha = false;
        RpGeometryForAllMaterials(pGeometry, CVehicleModelInfo::HasAlphaMaterialCB, &bHasAlpha);
        if (bHasAlpha || !strncmp(pNodeName, "windscreen", 10))
            CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderVehicleHiDetailAlphaCB);
        else
            CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderVehicleHiDetailCB);
    }

    CVehicleModelInfo::HideDamagedAtomicCB(atomic, nullptr);
    return atomic;
}

RpAtomic* CVehicleModelInfo::SetAtomicRendererCB_RealHeli(RpAtomic* atomic, void* data)
{
    auto pNodeName = GetFrameNodeName(RpAtomicGetFrame(atomic));
    if (!strcmp(pNodeName, "moving_rotor"))
        CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderHeliRotorAlphaCB);
    else if (!strcmp(pNodeName, "moving_rotor2"))
        CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderHeliTailRotorAlphaCB);
    else if (strstr(pNodeName, "_vlo")) {
        CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderVehicleReallyLowDetailCB);
    }
    else {
        auto pGeometry = RpAtomicGetGeometry(atomic);
        bool bHasAlpha = false;
        RpGeometryForAllMaterials(pGeometry, CVehicleModelInfo::HasAlphaMaterialCB, &bHasAlpha);
        if (bHasAlpha || !strncmp(pNodeName, "windscreen", 10))
            CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderVehicleHiDetailAlphaCB);
        else
            CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderVehicleHiDetailCB);
    }

    CVehicleModelInfo::HideDamagedAtomicCB(atomic, nullptr);
    return atomic;
}

RpAtomic* CVehicleModelInfo::SetAtomicRendererCB_Plane(RpAtomic* atomic, void* data)
{
    auto pNodeName = GetFrameNodeName(RpAtomicGetFrame(atomic));
    if (strstr(pNodeName, "_vlo")) {
        CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderVehicleReallyLowDetailCB_BigVehicle);
    }
    else {
        auto pGeometry = RpAtomicGetGeometry(atomic);
        bool bHasAlpha = false;
        RpGeometryForAllMaterials(pGeometry, CVehicleModelInfo::HasAlphaMaterialCB, &bHasAlpha);
        if (bHasAlpha)
            CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderVehicleHiDetailAlphaCB_BigVehicle);
        else
            CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderVehicleHiDetailCB_BigVehicle);
    }

    CVehicleModelInfo::HideDamagedAtomicCB(atomic, nullptr);
    return atomic;
}

RpAtomic* CVehicleModelInfo::SetAtomicRendererCB_Boat(RpAtomic* atomic, void* data)
{
    auto pNodeName = GetFrameNodeName(RpAtomicGetFrame(atomic));
    if (!strcmp(pNodeName, "boat_hi"))
        CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderVehicleHiDetailCB_Boat);
    else if (strstr(pNodeName, "_vlo")) {
        CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderVehicleLoDetailCB_Boat);
    }
    else {
        auto pGeometry = RpAtomicGetGeometry(atomic);
        bool bHasAlpha = false;
        RpGeometryForAllMaterials(pGeometry, CVehicleModelInfo::HasAlphaMaterialCB, &bHasAlpha);
        if (bHasAlpha)
            CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderVehicleHiDetailAlphaCB_Boat);
        else
            CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderVehicleHiDetailCB_Boat);
    }

    CVehicleModelInfo::HideDamagedAtomicCB(atomic, nullptr);
    return atomic;
}

RpAtomic* CVehicleModelInfo::SetAtomicRendererCB_Heli(RpAtomic* atomic, void* data)
{
    auto pNodeName = GetFrameNodeName(RpAtomicGetFrame(atomic));
    if (!strncmp(pNodeName, "toprotor", 8))
        CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderHeliRotorAlphaCB);
    else if (!strncmp(pNodeName, "rearrotor", 9))
        CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderHeliTailRotorAlphaCB);
    else
        CVisibilityPlugins::SetAtomicRenderCallback(atomic, nullptr);

    return atomic;
}

RpAtomic* CVehicleModelInfo::SetAtomicRendererCB_Train(RpAtomic* atomic, void* data)
{
    auto pNodeName = GetFrameNodeName(RpAtomicGetFrame(atomic));
    if (strstr(pNodeName, "_vlo")) {
        CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderVehicleReallyLowDetailCB_BigVehicle);
    }
    else {
        auto pGeometry = RpAtomicGetGeometry(atomic);
        bool bHasAlpha = false;
        RpGeometryForAllMaterials(pGeometry, CVehicleModelInfo::HasAlphaMaterialCB, &bHasAlpha);
        if (bHasAlpha)
            CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderTrainHiDetailAlphaCB);
        else
            CVisibilityPlugins::SetAtomicRenderCallback(atomic, CVisibilityPlugins::RenderTrainHiDetailCB);
    }

    CVehicleModelInfo::HideDamagedAtomicCB(atomic, nullptr);
    return atomic;
}

RwObject* CVehicleModelInfo::SetAtomicFlagCB(RwObject* object, void* data)
{
    CVisibilityPlugins::SetAtomicFlag(reinterpret_cast<RpAtomic*>(object), (uint16)data);
    return object;
}

RwObject* CVehicleModelInfo::ClearAtomicFlagCB(RwObject* object, void* data)
{
    CVisibilityPlugins::ClearAtomicFlag(reinterpret_cast<RpAtomic*>(object), (uint16)data);
    return object;
}

// 0x4C8700
void CVehicleModelInfo::AddWheelUpgrade(int32 wheelSetNumber, int32 modelId)
{
    auto iUpgradesNum = CVehicleModelInfo::ms_numWheelUpgrades[wheelSetNumber];
    CVehicleModelInfo::ms_upgradeWheels[wheelSetNumber][iUpgradesNum] = modelId;
    CVehicleModelInfo::ms_numWheelUpgrades[wheelSetNumber] = iUpgradesNum + 1;
}

int32 CVehicleModelInfo::GetWheelUpgrade(int32 wheelSetNumber, int32 wheelUpgradeNumber)
{
    return CVehicleModelInfo::ms_upgradeWheels[wheelSetNumber][wheelUpgradeNumber];
}

int32 CVehicleModelInfo::GetNumWheelUpgrades(int32 wheelSetNumber)
{
    return CVehicleModelInfo::ms_numWheelUpgrades[wheelSetNumber];
}

void CVehicleModelInfo::DeleteVehicleColourTextures()
{}

void CVehicleModelInfo::SetDirtTextures(CVehicleModelInfo* info, int32 dirtLevel)
{
    for (auto i = 0; i < CCarFXRenderer::NUM_DIRT_TEXTURES; ++i)
        if (info->m_apDirtMaterials[i])
            RpMaterialSetTexture(info->m_apDirtMaterials[i], CCarFXRenderer::ms_aDirtTextures[dirtLevel]);
}

void CVehicleModelInfo::ShutdownEnvironmentMaps()
{
    static bool bEnvMapsLoaded = false; //Not used anywhere else
    RwTextureDestroy(gpWhiteTexture);
    gpWhiteTexture = nullptr;

    if (carFrame)
        RwFrameDestroy(carFrame);
    carFrame = nullptr;
}

RpMaterial* CVehicleModelInfo::GetMatFXEffectMaterialCB(RpMaterial* material, void* data)
{
    auto iEffects = RpMatFXMaterialGetEffects(material);
    if (!iEffects)
        return material;

    *reinterpret_cast<RpMatFXMaterialFlags*>(data) = iEffects;
    return nullptr;
}

RpMaterial* CVehicleModelInfo::SetEnvironmentMapCB(RpMaterial* material, void* data)
{
    if ((uint16)data == 0xFFFF) {
        RpMatFXMaterialSetEffects(material, RpMatFXMaterialFlags::rpMATFXEFFECTNULL);
        return material;
    }

    if (RpMatFXMaterialGetEffects(material) != RpMatFXMaterialFlags::rpMATFXEFFECTENVMAP)
        return material;

    RpMatFXMaterialSetEnvMapFrame(material, carFrame);
    if (!RpMaterialGetTexture(material))
        RpMaterialSetTexture(material, gpWhiteTexture);

    RpMatFXMaterialSetEnvMapCoefficient(material, fEnvMapDefaultCoeff);
    return material;
}

RpMaterial* CVehicleModelInfo::SetEnvMapCoeffCB(RpMaterial* material, void* data)
{
    if (RpMatFXMaterialGetEffects(material) != RpMatFXMaterialFlags::rpMATFXEFFECTENVMAP)
        return material;

    auto uiCoeff = reinterpret_cast<int32>(data);
    float fCoeff = static_cast<float>(uiCoeff) / 1000.0F;
    RpMatFXMaterialSetEnvMapCoefficient(material, fCoeff);
    return material;
}

RpAtomic* CVehicleModelInfo::SetRenderPipelinesCB(RpAtomic* atomic, void* data)
{
    return atomic;
}

RwFrame* CVehicleModelInfo::CollapseFramesCB(RwFrame* frame, void* data)
{
    RwFrameForAllChildren(frame, CVehicleModelInfo::CollapseFramesCB, data);
    RwFrameForAllObjects(frame, CVehicleModelInfo::MoveObjectsCB, data);
    RwFrameDestroy(frame);
    return frame;
}

RpAtomic* CVehicleModelInfo::SetEnvironmentMapAtomicCB(RpAtomic* atomic, void* data)
{
    RpGeometryForAllMaterials(RpAtomicGetGeometry(atomic), CVehicleModelInfo::SetEnvironmentMapCB, data);
    return atomic;
}

RpAtomic* CVehicleModelInfo::SetEnvMapCoeffAtomicCB(RpAtomic* atomic, void* data)
{
    RpGeometryForAllMaterials(RpAtomicGetGeometry(atomic), CVehicleModelInfo::SetEnvMapCoeffCB, data);
    return atomic;
}

void CVehicleModelInfo::AssignRemapTxd(const char* name, int16 txdSlot)
{
    auto iLen = strlen(name);
    if (!isdigit(name[iLen - 1]))
        return;

    auto iLastIndex = iLen - 2;
    while (isdigit(name[iLastIndex]))
        --iLastIndex;

    char buffer[24];
    strncpy(buffer, name, iLastIndex + 1);
    buffer[iLastIndex + 1] = '\0';

    auto mi = CModelInfo::GetModelInfo(buffer, 400, 630);
    if (mi && mi->GetModelType() == ModelInfoType::MODEL_INFO_VEHICLE)
        mi->AsVehicleModelInfoPtr()->AddRemap(txdSlot);
}

RpAtomic* CVehicleModelInfo::StoreAtomicUsedMaterialsCB(RpAtomic* atomic, void* data)
{
    auto matList = reinterpret_cast<RpMaterialList*>(data);
    auto pGeometry = RpAtomicGetGeometry(atomic);
    auto pMeshHeader = pGeometry->mesh;
    if (CVisibilityPlugins::GetAtomicId(atomic) & eAtomicComponentFlag::ATOMIC_DISABLE_REFLECTIONS)
        return atomic;

    for (int32 i = 0; i < pMeshHeader->numMeshes; ++i) {
        auto pMesh = RpGeometryGetMesh(pGeometry, i);
        // auto pMat = matList->materials; // Unused code i guess
        // for (int32 iMat = 0; iMat < matList->numMaterials; ++iMat)
        //     pMat++;

        _rpMaterialListAppendMaterial(matList, pMesh->material);
    }
    return atomic;
}

void CVehicleModelInfo::SetupCommonData()
{
    CVehicleModelInfo::LoadVehicleColours();
    CLoadingScreen::NewChunkLoaded();
    CVehicleModelInfo::LoadVehicleUpgrades();
    CLoadingScreen::NewChunkLoaded();
    CVehicleModelInfo::LoadEnvironmentMaps();
    CLoadingScreen::NewChunkLoaded();

    auto iTxd = CTxdStore::FindTxdSlot("vehicle");
    if (iTxd == -1)
        iTxd = CTxdStore::AddTxdSlot("vehicle");

    CTxdStore::LoadTxd(iTxd, "MODELS\\GENERIC\\VEHICLE.TXD");
    CTxdStore::AddRef(iTxd);

    if (iTxd != -1)
        vehicleTxd = CTxdStore::ms_pTxdPool->GetAt(iTxd)->m_pRwDictionary;

    CVehicleModelInfo::ms_pLightsTexture = RwTexDictionaryFindNamedTexture(vehicleTxd, "vehiclelights128");
    CVehicleModelInfo::ms_pLightsOnTexture = RwTexDictionaryFindNamedTexture(vehicleTxd, "vehiclelightson128");
    CLoadingScreen::NewChunkLoaded();
    CVehicleModelInfo::CVehicleStructure::m_pInfoPool = new CPool<CVehicleModelInfo::CVehicleStructure>(50, "VehicleStruct");
    CCarFXRenderer::InitialiseDirtTexture();
}

void CVehicleModelInfo::LoadVehicleColours()
{
    char buffer[1024];
    auto file = CFileMgr::OpenFile("DATA\\CARCOLS.DAT", "r");
    auto pCurColor = CVehicleModelInfo::ms_vehicleColourTable;

    eCarColLineType iLastMode = eCarColLineType::IGNORED;
    eCarColLineType iCurMode = eCarColLineType::IGNORED;
    while (CFileMgr::ReadLine(file, buffer, 1024)) {
        auto iStartInd = 0;
        while (iStartInd < 10 && buffer[iStartInd] && buffer[iStartInd] <= ' ')
            ++iStartInd;

        auto pLineStart = &buffer[iStartInd];
        auto iLength = 0;
        while (pLineStart[iLength] && pLineStart[iLength] != '\n') {
            if (pLineStart[iLength] == ',' || pLineStart[iLength] == '\r')
                pLineStart[iLength] = ' ';

            ++iLength;
        }
        pLineStart[iLength] = '\0';

        if (!pLineStart[0] || pLineStart[0] == '#')
            continue;

        if (iLastMode == eCarColLineType::IGNORED) {
            if (!strncmp(pLineStart, "col", 3)) {
                iLastMode = eCarColLineType::GLOBAL_RGB;
                iCurMode = eCarColLineType::GLOBAL_RGB;
            }
            else if (!strncmp(pLineStart, "car4", 4)) {
                iLastMode = eCarColLineType::CAR_4COL;
                iCurMode = eCarColLineType::CAR_4COL;
            }
            else if (!strncmp(pLineStart, "car", 3)) {
                iLastMode = eCarColLineType::CAR_2COL;
                iCurMode = eCarColLineType::CAR_2COL;
            }
            continue;
        }

        if (!strncmp(pLineStart, "end", 3)) {
            iLastMode = eCarColLineType::IGNORED;
            iCurMode = eCarColLineType::IGNORED;
            continue;
        }

        if (iLastMode == eCarColLineType::GLOBAL_RGB) {
            uint32 red, green, blue;
            sscanf(buffer, "%d %d %d", &red, &green, &blue);
            pCurColor->Set(red, green, blue, 255);
            auto pLineEnd = pLineStart;
            while (*pLineEnd != '#') // Seems redundant(?)
                pLineEnd++;

            pCurColor++;
            continue;
        }

        uint32 colorBuffer[8][4];
        if (iLastMode == eCarColLineType::CAR_2COL)
        {
            char modelName[64];
            auto iNumRead = sscanf(buffer, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
                modelName,
                &colorBuffer[0][0],
                &colorBuffer[0][1],
                &colorBuffer[1][0],
                &colorBuffer[1][1],
                &colorBuffer[2][0],
                &colorBuffer[2][1],
                &colorBuffer[3][0],
                &colorBuffer[3][1],
                &colorBuffer[4][0],
                &colorBuffer[4][1],
                &colorBuffer[5][0],
                &colorBuffer[5][1],
                &colorBuffer[6][0],
                &colorBuffer[6][1],
                &colorBuffer[7][0],
                &colorBuffer[7][1]);

            auto mi = CModelInfo::GetModelInfo(modelName, nullptr)->AsVehicleModelInfoPtr();
            auto iNumVariations = (iNumRead - 1) / 2;
            mi->m_nNumColorVariations = iNumVariations;

            for (int32 i = 0; i < iNumVariations; ++i) {
                mi->m_anPrimaryColors[i]    = colorBuffer[i][0];
                mi->m_anSecondaryColors[i]  = colorBuffer[i][1];
                mi->m_anTertiaryColors[i]   = 0;
                mi->m_anQuaternaryColors[i] = 0;
            }

            iLastMode = iCurMode;
            continue;
        }

        if (iLastMode == eCarColLineType::CAR_4COL) {
            char modelName[64];
            auto iNumRead = sscanf(buffer, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
                modelName,
                &colorBuffer[0][0],
                &colorBuffer[0][1],
                &colorBuffer[0][2],
                &colorBuffer[0][3],
                &colorBuffer[1][0],
                &colorBuffer[1][1],
                &colorBuffer[1][2],
                &colorBuffer[1][3],
                &colorBuffer[2][0],
                &colorBuffer[2][1],
                &colorBuffer[2][2],
                &colorBuffer[2][3],
                &colorBuffer[3][0],
                &colorBuffer[3][1],
                &colorBuffer[3][2],
                &colorBuffer[3][3],
                &colorBuffer[4][0],
                &colorBuffer[4][1],
                &colorBuffer[4][2],
                &colorBuffer[4][3],
                &colorBuffer[5][0],
                &colorBuffer[5][1],
                &colorBuffer[5][2],
                &colorBuffer[5][3],
                &colorBuffer[6][0],
                &colorBuffer[6][1],
                &colorBuffer[6][2],
                &colorBuffer[6][3],
                &colorBuffer[7][0],
                &colorBuffer[7][1],
                &colorBuffer[7][2],
                &colorBuffer[7][3]
            );

            auto mi = CModelInfo::GetModelInfo(modelName, nullptr)->AsVehicleModelInfoPtr();
            auto iNumVariations = (iNumRead - 1) / 4;
            mi->m_nNumColorVariations = iNumVariations;

            for (int32 i = 0; i < iNumVariations; ++i) {
                mi->m_anPrimaryColors[i]    = colorBuffer[i][0];
                mi->m_anSecondaryColors[i]  = colorBuffer[i][1];
                mi->m_anTertiaryColors[i]   = colorBuffer[i][2];
                mi->m_anQuaternaryColors[i] = colorBuffer[i][3];
            }

            iLastMode = iCurMode;
            continue;
        }
    }

    CFileMgr::CloseFile(file);
}

void CVehicleModelInfo::LoadVehicleUpgrades()
{
    for (int32 i = 0; i < NUM_WHEELS; ++i)
        CVehicleModelInfo::ms_numWheelUpgrades[i] = 0;;

    auto file = CFileMgr::OpenFile("DATA\\CARMODS.DAT", "r");
    char* line;
    eCarModsLineType iLineType = eCarModsLineType::IGNORED;
    while ((line = CFileLoader::LoadLine(file))) {
        if (!line[0] || line[0] == '#')
            continue;

        if (iLineType == eCarModsLineType::IGNORED) {
            if (!strncmp(line, "link", 4))
                iLineType = eCarModsLineType::LINK;
            else if (!strncmp(line, "mods", 4))
                iLineType = eCarModsLineType::MODS;
            else if (!strncmp(line, "wheel", 5))
                iLineType = eCarModsLineType::WHEEL;

            continue;
        }

        if (!strncmp(line, "end", 3)) {
            iLineType = eCarModsLineType::IGNORED;
            continue;
        }

        switch (iLineType) {
        case eCarModsLineType::LINK: {
            int32 iModelId1 = -1, iModelId2 = -1;
            auto pToken = strtok(line, " \t,");
            if (pToken) {
                auto pModel1 = static_cast<CAtomicModelInfo*>(CModelInfo::GetModelInfo(pToken, &iModelId1));
                pModel1->SetupVehicleUpgradeFlags(pToken);

                auto pNextToken = strtok(nullptr, " \t,");
                auto pModel2 = static_cast<CAtomicModelInfo*>(CModelInfo::GetModelInfo(pNextToken, &iModelId2));
                pModel2->SetupVehicleUpgradeFlags(pNextToken);

                CVehicleModelInfo::ms_linkedUpgrades.AddUpgradeLink(iModelId1, iModelId2);
            }
            break;
        }

        case eCarModsLineType::MODS: {
            auto pToken = strtok(line, " \t,");
            if (!pToken)
                break;

            int32 iModelId = -1;
            auto mi = CModelInfo::GetModelInfo(pToken, &iModelId)->AsVehicleModelInfoPtr();
            auto nextToken = strtok(nullptr, " \t,");
            auto upgrade = mi->m_anUpgrades;
            while (nextToken) {
                auto ami = static_cast<CAtomicModelInfo*>(CModelInfo::GetModelInfo(nextToken, &iModelId));
                ami->SetupVehicleUpgradeFlags(nextToken);
                *upgrade = iModelId;
                ++upgrade;
                nextToken = strtok(nullptr, " \t,");
            }

            auto hydraulicsAMI = static_cast<CAtomicModelInfo*>(CModelInfo::GetModelInfo("hydralics", &iModelId));
            hydraulicsAMI->SetupVehicleUpgradeFlags("hydralics");
            *upgrade = iModelId;
            upgrade++;

            auto stereoAMI = static_cast<CAtomicModelInfo*>(CModelInfo::GetModelInfo("stereo", &iModelId));
            stereoAMI->SetupVehicleUpgradeFlags("stereo");
            *upgrade = iModelId;
            break;
        }

        case eCarModsLineType::WHEEL: {
            int32 iModelId = -1, iWheelSet;
            sscanf(line, "%d", &iWheelSet);
            strtok(line, " \t,");
            char* token;
            while ((token = strtok(nullptr, " \t,"))) {
                auto wheelMI = static_cast<CAtomicModelInfo*>(CModelInfo::GetModelInfo(token, &iModelId));
                wheelMI->SetupVehicleUpgradeFlags(token);
                CVehicleModelInfo::AddWheelUpgrade(iWheelSet, iModelId);
            }
            break;
        }
        }
    }

    CFileMgr::CloseFile(file);
}

void CVehicleModelInfo::LoadEnvironmentMaps()
{
    CTxdStore::PushCurrentTxd();
    CTxdStore::SetCurrentTxd(CTxdStore::FindTxdSlot("particle"));
    if (!gpWhiteTexture) {
        gpWhiteTexture = RwTextureRead("white", nullptr);
        RwTextureGetName(gpWhiteTexture)[0] = '@';
        RwTextureSetFilterMode(gpWhiteTexture, RwTextureFilterMode::rwFILTERLINEAR);
    }
    CTxdStore::PopCurrentTxd();
}

void CVehicleModelInfo::SetHandlingId(const char* handlingName) {
    m_nHandlingId = gHandlingDataMgr.GetHandlingId(handlingName);
}

void CVehicleModelInfo::CLinkedUpgradeList::AddUpgradeLink(int16 upgrade1, int16 upgrade2)
{
    m_anUpgrade1[m_nLinksCount] = upgrade1;
    m_anUpgrade2[m_nLinksCount] = upgrade2;
    ++m_nLinksCount;
}

int16 CVehicleModelInfo::CLinkedUpgradeList::FindOtherUpgrade(int16 upgrade)
{
    if (!m_nLinksCount)
        return -1;

    for (int32 i = m_nLinksCount - 1; i >= 0; --i) {
        if (m_anUpgrade1[i] == upgrade)
            return m_anUpgrade2[i];

        if (m_anUpgrade2[i] == upgrade)
            return m_anUpgrade1[i];
    }

    return -1;
}

CVehicleModelInfo::CVehicleStructure::CVehicleStructure() : m_aUpgrades()
{
    for (auto& pVecPos : m_avDummyPos)
        pVecPos.Set(0.0F, 0.0F, 0.0F);

    for (auto& pUpgrade : m_aUpgrades)
        pUpgrade.m_nParentComponentId = -1;

    memset(m_apExtras, 0, sizeof(m_apExtras));
    m_nNumExtras = 0;
    m_nMaskComponentsDamagable = 0;
}

CVehicleModelInfo::CVehicleStructure::~CVehicleStructure()
{
    for (int32 i = 0; i < m_nNumExtras; ++i) {
        auto atomic = m_apExtras[i];
        auto frame = RpAtomicGetFrame(atomic);
        RpAtomicDestroy(atomic);
        RwFrameDestroy(frame);
    }
}

void* CVehicleModelInfo::CVehicleStructure::operator new(uint32 size)
{
    return CVehicleModelInfo::CVehicleStructure::m_pInfoPool->New();
}

void CVehicleModelInfo::CVehicleStructure::operator delete(void* data)
{
    CVehicleModelInfo::CVehicleStructure::m_pInfoPool->Delete(reinterpret_cast<CVehicleModelInfo::CVehicleStructure*>(data));
}

bool IsValidCompRule(int32 nRule)
{
    return nRule != eComponentsRules::ONLY_WHEN_RAINING
        || CWeather::OldWeatherType == eWeatherType::WEATHER_RAINY_COUNTRYSIDE
        || CWeather::NewWeatherType == eWeatherType::WEATHER_RAINY_COUNTRYSIDE
        || CWeather::OldWeatherType == eWeatherType::WEATHER_RAINY_SF
        || CWeather::NewWeatherType == eWeatherType::WEATHER_RAINY_SF;
}

int32 ChooseComponent(int32 rule, int32 comps)
{
    if (rule == eComponentsRules::ALLOW_ALWAYS || rule == eComponentsRules::ONLY_WHEN_RAINING) {
        auto iNumComps = CountCompsInRule(comps);
        auto rand = CGeneral::GetRandomNumberInRange(0, iNumComps);
        return (comps >> (4 * rand)) & 0xF;
    }
    else if (rule == eComponentsRules::MAYBE_HIDE) {
        auto iNumComps = CountCompsInRule(comps);
        auto rand = CGeneral::GetRandomNumberInRange(-1, iNumComps);
        if (rand == -1)
            return -1;

        return (comps >> (4 * rand)) & 0xF;
    }
    else if (rule == eComponentsRules::FULL_RANDOM) {
        return CGeneral::GetRandomNumberInRange(0, 5);
    }
    else
        return -1;
}

int32 CountCompsInRule(int32 comps)
{
    int32 result = 0;
    while (comps) {
        if ((comps & 0xF) != 0xF)
            ++result;

        comps /= 16;
    }

    return result;
}

int32 GetListOfComponentsNotUsedByRules(uint32 compRules, int32 numExtras, int32* outList)
{
    int32 iCompsList[]{ 0, 1, 2, 3, 4, 5 };
    tVehicleCompsUnion comps;
    comps.m_nComps = compRules;

    if (comps.nExtraARule && IsValidCompRule(comps.nExtraARule)) {
        if (comps.nExtraARule == eComponentsRules::FULL_RANDOM)
            return 0;

        if (comps.nExtraA_comp1 != 0xF)
            iCompsList[comps.nExtraA_comp1] = 0xF;

        if (comps.nExtraA_comp2 != 0xF)
            iCompsList[comps.nExtraA_comp2] = 0xF;

        if (comps.nExtraA_comp3 != 0xF)
            iCompsList[comps.nExtraA_comp3] = 0xF;
    }

    if (comps.nExtraBRule && IsValidCompRule(comps.nExtraBRule)) {
        if (comps.nExtraBRule == eComponentsRules::FULL_RANDOM)
            return 0;

        if (comps.nExtraB_comp1 != 0xF)
            iCompsList[comps.nExtraA_comp1] = 0xF;

        if (comps.nExtraB_comp2 != 0xF)
            iCompsList[comps.nExtraA_comp2] = 0xF;

        if (comps.nExtraB_comp3 != 0xF)
            iCompsList[comps.nExtraA_comp3] = 0xF;
    }

    auto iNumComps = 0;
    for (int32 i = 0; i < numExtras; ++i) {
        if (iCompsList[i] == 0xF)
            continue;

        outList[iNumComps] = i;
        ++iNumComps;
    }

    return iNumComps;
}

RpMaterial* RemoveWindowAlphaCB(RpMaterial* material, void* data)
{
    auto color = RpMaterialGetColor(material);
    if (color->alpha == 255)
        return material;

    auto ppEntries = reinterpret_cast<tRestoreEntry**>(data);
    (*ppEntries)->m_pAddress = RpMaterialGetColor(material);
    (*ppEntries)->m_pValue = *reinterpret_cast<void**>(RpMaterialGetColor(material));
    (*ppEntries)++;

    color->red = 0;
    color->green = 0;
    color->blue = 0;
    color->alpha = 0;

    return material;
}

RwObject* GetOkAndDamagedAtomicCB(RwObject* object, void* data)
{
    auto pOut = reinterpret_cast<RwObject**>(data);
    if ((CVisibilityPlugins::GetAtomicId(reinterpret_cast<RpAtomic*>(object)) & ATOMIC_IS_OK_STATE) != 0) {
        pOut[0] = object;
    }
    else if ((CVisibilityPlugins::GetAtomicId(reinterpret_cast<RpAtomic*>(object)) & ATOMIC_IS_DAM_STATE) != 0) {
        pOut[1] = object;
    }

    return object;
}

RpAtomic* atomicDefaultRenderCB(RpAtomic* atomic)
{
    AtomicDefaultRenderCallBack(atomic);
    return atomic;
}
