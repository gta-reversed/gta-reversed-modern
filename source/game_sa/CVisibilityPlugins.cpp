/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

std::int32_t& CVisibilityPlugins::ms_atomicPluginOffset = *(std::int32_t*)0x8D608C;
std::int32_t& CVisibilityPlugins::ms_clumpPluginOffset = *(std::int32_t*)0x8D6094;
std::int32_t& CVisibilityPlugins::ms_framePluginOffset = *(std::int32_t*)0x8D6090;

CLinkList<CVisibilityPlugins::AlphaObjectInfo>& CVisibilityPlugins::m_alphaEntityList = *(CLinkList<CVisibilityPlugins::AlphaObjectInfo>*)0xC88120;
CLinkList<CVisibilityPlugins::AlphaObjectInfo>& CVisibilityPlugins::m_alphaList = *(CLinkList<CVisibilityPlugins::AlphaObjectInfo>*)0xC88070;
CLinkList<CVisibilityPlugins::AlphaObjectInfo>& CVisibilityPlugins::m_alphaBoatAtomicList = *(CLinkList<CVisibilityPlugins::AlphaObjectInfo>*)0xC880C8;
CLinkList<CVisibilityPlugins::AlphaObjectInfo>& CVisibilityPlugins::m_alphaUnderwaterEntityList = *(CLinkList<CVisibilityPlugins::AlphaObjectInfo>*)0xC88178;
CLinkList<CVisibilityPlugins::AlphaObjectInfo>& CVisibilityPlugins::m_alphaReallyDrawLastList = *(CLinkList<CVisibilityPlugins::AlphaObjectInfo>*)0xC881D0;
CLinkList<CPed*>& CVisibilityPlugins::ms_weaponPedsForPC = *(CLinkList<CPed*>*)0xC88224;
RwCamera*& CVisibilityPlugins::ms_pCamera = *(RwCamera**)0xC8804C;
RwV3d*& CVisibilityPlugins::ms_pCameraPosn = *(RwV3d**)0xC88050;
float& CVisibilityPlugins::ms_cullCompsDist = *(float*)0x0C8802C;
float& CVisibilityPlugins::ms_cullBigCompsDist = *(float*)0x0C88028;
float& CVisibilityPlugins::ms_vehicleLod0RenderMultiPassDist = *(float*)0xC88044;
float& CVisibilityPlugins::ms_vehicleLod0Dist = *(float*)0xC88040;
float& CVisibilityPlugins::ms_vehicleLod1Dist = *(float*)0xC8803C;
float& CVisibilityPlugins::ms_bigVehicleLod0Dist = *(float*)0xC88038;
float& CVisibilityPlugins::ms_pedLodDist = *(float*)0xC88034;
float& CVisibilityPlugins::ms_pedFadeDist = *(float*)0xC88030;
float& CVisibilityPlugins::gVehicleDistanceFromCamera = *(float*)0xC88024;
float& CVisibilityPlugins::gVehicleAngleToCamera = *(float*)0xC88020;

void CVisibilityPlugins::InjectHooks() {
    ReversibleHooks::Install("CVisibilityPlugins", "AtomicCopyConstructor",0x732170, &CVisibilityPlugins::AtomicCopyConstructor);
    ReversibleHooks::Install("CVisibilityPlugins", "AtomicDestructor",0x7321A0, &CVisibilityPlugins::AtomicDestructor);
    ReversibleHooks::Install("CVisibilityPlugins", "CalculateFadingAtomicAlpha",0x732500, &CVisibilityPlugins::CalculateFadingAtomicAlpha);
    ReversibleHooks::Install("CVisibilityPlugins", "ClearAtomicFlag_0",0x732310, &CVisibilityPlugins::ClearAtomicFlag);
    ReversibleHooks::Install("CVisibilityPlugins", "ClearAtomicFlag_1",0x732330, &CVisibilityPlugins::ClearAtomicFlag);
    ReversibleHooks::Install("CVisibilityPlugins", "ClearClumpForAllAtomicsFlag",0x732350, &CVisibilityPlugins::ClearClumpForAllAtomicsFlag);
    ReversibleHooks::Install("CVisibilityPlugins", "ClumpConstructor",0x732E10, &CVisibilityPlugins::ClumpConstructor);
    ReversibleHooks::Install("CVisibilityPlugins", "ClumpCopyConstructor",0x732200, &CVisibilityPlugins::ClumpCopyConstructor);
    ReversibleHooks::Install("CVisibilityPlugins", "ClumpDestructor",0x732220, &CVisibilityPlugins::ClumpDestructor);
    ReversibleHooks::Install("CVisibilityPlugins", "DefaultVisibilityCB",0x732A30, &CVisibilityPlugins::DefaultVisibilityCB);
    ReversibleHooks::Install("CVisibilityPlugins", "FrameConstructor",0x7321B0, &CVisibilityPlugins::FrameConstructor);
    ReversibleHooks::Install("CVisibilityPlugins", "FrameCopyConstructor",0x7321D0, &CVisibilityPlugins::FrameCopyConstructor);
    ReversibleHooks::Install("CVisibilityPlugins", "FrameDestructor",0x7321F0, &CVisibilityPlugins::FrameDestructor);
    ReversibleHooks::Install("CVisibilityPlugins", "FrustumSphereCB",0x732A40, &CVisibilityPlugins::FrustumSphereCB);
    ReversibleHooks::Install("CVisibilityPlugins", "GetAtomicId",0x732370, &CVisibilityPlugins::GetAtomicId);
    ReversibleHooks::Install("CVisibilityPlugins", "GetAtomicModelInfo",0x732260, &CVisibilityPlugins::GetAtomicModelInfo);
    ReversibleHooks::Install("CVisibilityPlugins", "GetClumpAlpha",0x732B20, &CVisibilityPlugins::GetClumpAlpha);
    ReversibleHooks::Install("CVisibilityPlugins", "GetClumpModelInfo",0x732AC0, &CVisibilityPlugins::GetClumpModelInfo);
    ReversibleHooks::Install("CVisibilityPlugins", "GetDistanceSquaredFromCamera_0",0x732C80, (float(*)(RwFrame*)) &CVisibilityPlugins::GetDistanceSquaredFromCamera);
    ReversibleHooks::Install("CVisibilityPlugins", "GetDistanceSquaredFromCamera_1",0x732CC0, (float(*)(CVector*)) &CVisibilityPlugins::GetDistanceSquaredFromCamera);
    ReversibleHooks::Install("CVisibilityPlugins", "GetDotProductWithCameraVector",0x7326D0, &CVisibilityPlugins::GetDotProductWithCameraVector);
    ReversibleHooks::Install("CVisibilityPlugins", "GetFrameHierarchyId",0x732A20, &CVisibilityPlugins::GetFrameHierarchyId);
    ReversibleHooks::Install("CVisibilityPlugins", "GetModelInfoIndex",0x732250, &CVisibilityPlugins::GetModelInfoIndex);
    ReversibleHooks::Install("CVisibilityPlugins", "GetUserValue",0x7323A0, &CVisibilityPlugins::GetUserValue);
    ReversibleHooks::Install("CVisibilityPlugins", "InitAlphaAtomicList",0x734530, &CVisibilityPlugins::InitAlphaAtomicList);
    ReversibleHooks::Install("CVisibilityPlugins", "InitAlphaEntityList",0x734540, &CVisibilityPlugins::InitAlphaEntityList);
    ReversibleHooks::Install("CVisibilityPlugins", "InsertEntityIntoEntityList",0x733DD0, &CVisibilityPlugins::InsertEntityIntoEntityList);
    ReversibleHooks::Install("CVisibilityPlugins", "InsertEntityIntoUnderwaterEntities",0x733D90, &CVisibilityPlugins::InsertEntityIntoUnderwaterEntities);
    ReversibleHooks::Install("CVisibilityPlugins", "Initialise",0x733A20, &CVisibilityPlugins::Initialise);
    ReversibleHooks::Install("CVisibilityPlugins", "InsertAtomicIntoReallyDrawLastList",0x733E10, &CVisibilityPlugins::InsertAtomicIntoReallyDrawLastList);
    ReversibleHooks::Install("CVisibilityPlugins", "InsertEntityIntoReallyDrawLastList",0x733E50, &CVisibilityPlugins::InsertEntityIntoReallyDrawLastList);
    ReversibleHooks::Install("CVisibilityPlugins", "InsertEntityIntoSortedList",0x734570, &CVisibilityPlugins::InsertEntityIntoSortedList);
    ReversibleHooks::Install("CVisibilityPlugins", "IsAtomicVisible",0x732990, &CVisibilityPlugins::IsAtomicVisible);
    ReversibleHooks::Install("CVisibilityPlugins", "PluginAttach",0x732E30, &CVisibilityPlugins::PluginAttach);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderAlphaAtomic",0x732480, &CVisibilityPlugins::RenderAlphaAtomic);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderAlphaAtomics",0x733E90, &CVisibilityPlugins::RenderAlphaAtomics);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderAtomicWithAlphaCB",0x732660, &CVisibilityPlugins::RenderAtomicWithAlphaCB);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderBoatAlphaAtomics",0x733EC0, &CVisibilityPlugins::RenderBoatAlphaAtomics);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderEntity",0x732B40, &CVisibilityPlugins::RenderEntity);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderFadingAtomic",0x732610, &CVisibilityPlugins::RenderFadingAtomic);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderFadingClump",0x732680, &CVisibilityPlugins::RenderFadingClump);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderFadingClumpCB",0x733630, &CVisibilityPlugins::RenderFadingClumpCB);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderFadingEntities",0x733F10, &CVisibilityPlugins::RenderFadingEntities);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderFadingUnderwaterEntities",0x7337D0, &CVisibilityPlugins::RenderFadingUnderwaterEntities);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderHeliRotorAlphaCB",0x7340B0, &CVisibilityPlugins::RenderHeliRotorAlphaCB);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderHeliTailRotorAlphaCB",0x734170, &CVisibilityPlugins::RenderHeliTailRotorAlphaCB);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderObjNormalAtomic",0x7323E0, &CVisibilityPlugins::RenderObjNormalAtomic);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderOrderedList",0x7337A0, &CVisibilityPlugins::RenderOrderedList);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderPedCB",0x7335B0, &CVisibilityPlugins::RenderPedCB);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderPlayerCB",0x732870, &CVisibilityPlugins::RenderPlayerCB);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderReallyDrawLastObjects",0x733800, &CVisibilityPlugins::RenderReallyDrawLastObjects);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderTrainHiDetailAlphaCB",0x734240, &CVisibilityPlugins::RenderTrainHiDetailAlphaCB);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderTrainHiDetailCB",0x733330, &CVisibilityPlugins::RenderTrainHiDetailCB);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderVehicleHiDetailAlphaCB",0x733F80, &CVisibilityPlugins::RenderVehicleHiDetailAlphaCB);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderVehicleHiDetailAlphaCB_BigVehicle",0x734370, &CVisibilityPlugins::RenderVehicleHiDetailAlphaCB_BigVehicle);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderVehicleHiDetailAlphaCB_Boat",0x7344A0, &CVisibilityPlugins::RenderVehicleHiDetailAlphaCB_Boat);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderVehicleHiDetailCB",0x733240, &CVisibilityPlugins::RenderVehicleHiDetailCB);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderVehicleHiDetailCB_BigVehicle",0x733420, &CVisibilityPlugins::RenderVehicleHiDetailCB_BigVehicle);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderVehicleHiDetailCB_Boat",0x733550, &CVisibilityPlugins::RenderVehicleHiDetailCB_Boat);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderVehicleLoDetailCB_Boat",0x7334F0, &CVisibilityPlugins::RenderVehicleLoDetailCB_Boat); 
    ReversibleHooks::Install("CVisibilityPlugins", "RenderVehicleReallyLowDetailCB",0x7331E0, &CVisibilityPlugins::RenderVehicleReallyLowDetailCB);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderVehicleReallyLowDetailCB_BigVehicle",0x732820, &CVisibilityPlugins::RenderVehicleReallyLowDetailCB_BigVehicle); 
    ReversibleHooks::Install("CVisibilityPlugins", "RenderWeaponCB",0x733670, &CVisibilityPlugins::RenderWeaponCB);
    ReversibleHooks::Install("CVisibilityPlugins", "RenderWeaponPedsForPC",0x732F30, &CVisibilityPlugins::RenderWeaponPedsForPC);
    ReversibleHooks::Install("CVisibilityPlugins", "SetAtomicFlag_0",0x7322D0, &CVisibilityPlugins::SetAtomicFlag);
    ReversibleHooks::Install("CVisibilityPlugins", "SetAtomicFlag_1",0x7322B0, &CVisibilityPlugins::SetAtomicFlag);
    ReversibleHooks::Install("CVisibilityPlugins", "SetClumpForAllAtomicsFlag", 0x732307, &CVisibilityPlugins::SetClumpForAllAtomicsFlag);
    ReversibleHooks::Install("CVisibilityPlugins", "SetAtomicId", 0x732230, &CVisibilityPlugins::SetAtomicId);
    ReversibleHooks::Install("CVisibilityPlugins", "SetAtomicRenderCallback", 0x7328A0, &CVisibilityPlugins::SetAtomicRenderCallback);
    ReversibleHooks::Install("CVisibilityPlugins", "SetClumpAlpha", 0x732B00, &CVisibilityPlugins::SetClumpAlpha);
    ReversibleHooks::Install("CVisibilityPlugins", "SetClumpModelInfo", 0x733750, &CVisibilityPlugins::SetClumpModelInfo);
    ReversibleHooks::Install("CVisibilityPlugins", "SetFrameHierarchyId", 0x732A00, &CVisibilityPlugins::SetFrameHierarchyId);
    ReversibleHooks::Install("CVisibilityPlugins", "SetRenderWareCamera", 0x7328C0, &CVisibilityPlugins::SetRenderWareCamera);
    ReversibleHooks::Install("CVisibilityPlugins", "SetUserValue", 0x732380, &CVisibilityPlugins::SetUserValue);
    ReversibleHooks::Install("CVisibilityPlugins", "SetupVehicleVariables", 0x733160, &CVisibilityPlugins::SetupVehicleVariables);
    ReversibleHooks::Install("CVisibilityPlugins", "Shutdown", 0x732EB0, &CVisibilityPlugins::Shutdown);
    ReversibleHooks::Install("CVisibilityPlugins", "VehicleVisibilityCB", 0x7336F0, &CVisibilityPlugins::VehicleVisibilityCB);
    ReversibleHooks::Install("CVisibilityPlugins", "VehicleVisibilityCB_BigVehicle", 0x732AB0, &CVisibilityPlugins::VehicleVisibilityCB_BigVehicle);
}

void CVisibilityPlugins::Initialise() {
    m_alphaList.Init(TOTAL_ALPHA_LISTS);
    m_alphaList.usedListHead.data.m_distance = 0.0f;
    m_alphaList.usedListTail.data.m_distance = 100000000.0f;
    m_alphaBoatAtomicList.Init(TOTAL_ALPHA_BOAT_ATOMIC_LISTS);
    m_alphaBoatAtomicList.usedListHead.data.m_distance = 0.0f;
    m_alphaBoatAtomicList.usedListTail.data.m_distance = 100000000.0f;
    m_alphaEntityList.Init(TOTAL_ALPHA_ENTITY_LISTS);
    m_alphaEntityList.usedListHead.data.m_distance = 0.0f;
    m_alphaEntityList.usedListTail.data.m_distance = 100000000.0f;
    m_alphaUnderwaterEntityList.Init(TOTAL_ALPHA_UNDERWATER_ENTITY_LISTS);
    m_alphaUnderwaterEntityList.usedListHead.data.m_distance = 0.0f;
    m_alphaUnderwaterEntityList.usedListTail.data.m_distance = 100000000.0f;
    m_alphaReallyDrawLastList.Init(TOTAL_ALPHA_DRAW_LAST_LISTS);
    m_alphaReallyDrawLastList.usedListHead.data.m_distance = 0.0f;
    m_alphaReallyDrawLastList.usedListTail.data.m_distance = 100000000.0f;
    ms_weaponPedsForPC.Init(TOTAL_WEAPON_PEDS_FOR_PC);
}

void CVisibilityPlugins::Shutdown() {
    m_alphaList.Shutdown();
    m_alphaBoatAtomicList.Shutdown();
    m_alphaEntityList.Shutdown();
    m_alphaUnderwaterEntityList.Shutdown();
    m_alphaReallyDrawLastList.Shutdown();
    ms_weaponPedsForPC.Shutdown();
}

void CVisibilityPlugins::InitAlphaAtomicList() {
    m_alphaList.Clear();
}

void CVisibilityPlugins::InitAlphaEntityList() {
    m_alphaEntityList.Clear();
    m_alphaBoatAtomicList.Clear();
    m_alphaUnderwaterEntityList.Clear();
    m_alphaReallyDrawLastList.Clear();
}

bool CVisibilityPlugins::InsertEntityIntoEntityList(CEntity* entity, float distance, void* callback)
{
    AlphaObjectInfo info{};
    info.m_entity = entity;
    info.m_pCallback = callback;
    info.m_distance = distance;
    return m_alphaEntityList.InsertSorted(info);
}

bool CVisibilityPlugins::InsertEntityIntoUnderwaterEntities(CEntity* entity, float distance)
{
    AlphaObjectInfo entityAlphaObjectInfo{};
    entityAlphaObjectInfo.m_distance = distance;
    entityAlphaObjectInfo.m_entity = entity;
    entityAlphaObjectInfo.m_pCallback = CVisibilityPlugins::RenderEntity;
    return m_alphaUnderwaterEntityList.InsertSorted(entityAlphaObjectInfo);
}

bool CVisibilityPlugins::InsertAtomicIntoReallyDrawLastList(RpAtomic* pRpAtomic, float distance) {
    AlphaObjectInfo objectInfo{};
    objectInfo.m_distance = distance;
    objectInfo.m_atomic = pRpAtomic;
    objectInfo.m_pCallback = DefaultAtomicRenderCallback;
    return m_alphaReallyDrawLastList.InsertSorted(objectInfo);
}

bool CVisibilityPlugins::InsertEntityIntoReallyDrawLastList(CEntity* pEntity, float distance) {
    AlphaObjectInfo objectInfo{};
    objectInfo.m_distance = distance;
    objectInfo.m_entity = pEntity;
    objectInfo.m_pCallback = CVisibilityPlugins::RenderEntity;
    return m_alphaReallyDrawLastList.InsertSorted(objectInfo);
}

bool CVisibilityPlugins::InsertEntityIntoSortedList(CEntity* entity, float distance) {
    if (entity->m_nModelIndex == ModelIndices::MI_GRASSHOUSE && InsertEntityIntoReallyDrawLastList(entity, distance))
        return true;
    if (entity->m_bUnderwater)
        return InsertEntityIntoUnderwaterEntities(entity, distance);
    return InsertEntityIntoEntityList(entity, distance, CVisibilityPlugins::RenderEntity);
}

#define ATOMICPLG(atomic, var) \
    (RWPLUGINOFFSET(tAtomicVisibilityPlugin, atomic, ms_atomicPluginOffset)->var)

#define ATOMICPLGCONST(atomic, var) \
    (RWPLUGINOFFSETCONST(tAtomicVisibilityPlugin, atomic, ms_atomicPluginOffset)->var)

#define FRAMEPLG(frame, var) \
    (RWPLUGINOFFSET(tFrameVisibilityPlugin, frame, ms_framePluginOffset)->var)

#define FRAMEPLGCONST(frame, var) \
    (RWPLUGINOFFSETCONST(tFrameVisibilityPlugin, frame, ms_framePluginOffset)->var)

#define CLUMPPLG(clump, var) \
    (RWPLUGINOFFSET(tClumpVisibilityPlugin, clump, ms_clumpPluginOffset)->var)

#define CLUMPPLGCONST(clump, var) \
    (RWPLUGINOFFSETCONST(tClumpVisibilityPlugin, clump, ms_clumpPluginOffset)->var)

bool CVisibilityPlugins::PluginAttach() {
    ms_atomicPluginOffset = RpAtomicRegisterPlugin(
        sizeof(tAtomicVisibilityPlugin),
        MAKECHUNKID(rwVENDORID_ROCKSTAR, 0x00),
        AtomicConstructor,
        AtomicDestructor,
        AtomicCopyConstructor);
    ms_clumpPluginOffset = RpClumpRegisterPlugin(
        sizeof(tClumpVisibilityPlugin),
        MAKECHUNKID(rwVENDORID_ROCKSTAR, 0x01),
        ClumpConstructor,
        ClumpDestructor,
        ClumpCopyConstructor);
    ms_framePluginOffset = RwFrameRegisterPlugin(
        sizeof(tFrameVisibilityPlugin),
        MAKECHUNKID(rwVENDORID_ROCKSTAR, 0x02),
        FrameConstructor,
        FrameDestructor,
        FrameCopyConstructor);
    return CVisibilityPlugins::ms_atomicPluginOffset != -1 && ms_clumpPluginOffset != -1;
}

RpAtomic* CVisibilityPlugins::DefaultAtomicRenderCallback(RpAtomic* atomic)
{
    return AtomicDefaultRenderCallBack(atomic);
}

void* CVisibilityPlugins::AtomicConstructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    ATOMICPLG(object, m_modelId) = -1;
    ATOMICPLG(object, m_flags) = 0;
    return object;
}

void* CVisibilityPlugins::AtomicCopyConstructor(void* dstObject, const void* srcObject, RwInt32 offsetInObject, RwInt32 sizeInObject)
{
    ATOMICPLG(dstObject, m_modelId) = ATOMICPLGCONST(srcObject, m_modelId);
    ATOMICPLG(dstObject, m_flags) = ATOMICPLGCONST(srcObject, m_flags);
    return dstObject;
}

void* CVisibilityPlugins::AtomicDestructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    return object;
}

std::int32_t CVisibilityPlugins::CalculateFadingAtomicAlpha(CBaseModelInfo* modelInfo, CEntity* entity, float distance) {
    float fFadingDistance = MAX_FADING_DISTANCE;
    float fDrawDistanceRadius = modelInfo->GetColModel()->GetBoundRadius() + CRenderer::ms_fFarClipPlane;
    fDrawDistanceRadius = std::min(fDrawDistanceRadius, TheCamera.m_fLODDistMultiplier * modelInfo->m_fDrawDistance);
    if (!entity->m_pLod) {
        const float fDrawDistance = std::min(modelInfo->m_fDrawDistance, fDrawDistanceRadius);
        if (fDrawDistance > MAX_LOWLOD_DISTANCE)
            fFadingDistance = fDrawDistance / 15.0f + 10.0f;
        if (entity->m_bIsBIGBuilding)
            fDrawDistanceRadius *= CRenderer::ms_lowLodDistScale;
    }
    float fFade = std::min((fDrawDistanceRadius + MAX_FADING_DISTANCE - distance) / fFadingDistance, 1.0f);
    return static_cast<std::int32_t>(modelInfo->m_nAlpha * fFade);
}

void CVisibilityPlugins::ClearAtomicFlag(RpAtomic* pRpAtomic, std::uint16_t flag) {
    ATOMICPLG(pRpAtomic, m_flags) &= ~flag;
}

RpAtomic* CVisibilityPlugins::ClearAtomicFlagCB(RpAtomic* atomic, void* data) {
    std::uint16_t flag = *reinterpret_cast<std::uint16_t*>(&data);
    ATOMICPLG(atomic, m_flags) &= ~flag;
    return atomic;
}

void CVisibilityPlugins::ClearClumpForAllAtomicsFlag(RpClump* pRpClump, std::uint16_t flag) {
    RpClumpForAllAtomics(pRpClump, ClearAtomicFlagCB, (void*)flag);
}

void* CVisibilityPlugins::ClumpConstructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    CLUMPPLG(object, m_visibilityCallBack) = CVisibilityPlugins::DefaultVisibilityCB;
    CLUMPPLG(object, m_alpha) = 255;
    return object;
}

void* CVisibilityPlugins::ClumpCopyConstructor(void* dstObject, const void* srcObject, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    CLUMPPLG(dstObject, m_visibilityCallBack) = CLUMPPLGCONST(srcObject, m_visibilityCallBack);
    return dstObject;
}

void* CVisibilityPlugins::ClumpDestructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    return object;
}

int CVisibilityPlugins::DefaultVisibilityCB() {
    return 1;
}

void* CVisibilityPlugins::FrameConstructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    FRAMEPLG(object, m_hierarchyId) = 0;
    return object;
}

void* CVisibilityPlugins::FrameCopyConstructor(void* dstObject, const void* srcObject, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    FRAMEPLG(dstObject, m_hierarchyId) = FRAMEPLGCONST(srcObject, m_hierarchyId);
    return dstObject;
}

void* CVisibilityPlugins::FrameDestructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
    return object;
}

bool CVisibilityPlugins::FrustumSphereCB(RpClump* pRpClump) {
    RwSphere sphere;
    RwFrame* frame = RpClumpGetFrame(pRpClump);
    CBaseModelInfo* modelInfo = FRAMEPLG(frame, m_modelInfo);
    sphere.radius = modelInfo->GetColModel()->GetBoundRadius();
    sphere.center = modelInfo->GetColModel()->GetBoundCenter();
    RwMatrixTag* transformMatrix = RwFrameGetLTM(frame);
    RwV3dTransformPoints(&sphere.center, &sphere.center, 1, transformMatrix);
    return RwCameraFrustumTestSphere(ms_pCamera, &sphere) != rwSPHEREOUTSIDE;
}

// The function name is misleading, it returns the flags
std::uint16_t CVisibilityPlugins::GetAtomicId(RpAtomic* pRpAtomic) {
    return ATOMICPLG(pRpAtomic, m_flags);
}


CAtomicModelInfo* CVisibilityPlugins::GetAtomicModelInfo(RpAtomic* pRpAtomic) {
    std::int16_t modelId = ATOMICPLG(pRpAtomic, m_modelId);
    if (modelId == -1)
        return nullptr;
    return static_cast<CAtomicModelInfo*>(CModelInfo::ms_modelInfoPtrs[modelId]);
}

std::int32_t CVisibilityPlugins::GetClumpAlpha(RpClump* pRpClump) {
    return CLUMPPLG(pRpClump, m_alpha);
}

CClumpModelInfo* CVisibilityPlugins::GetClumpModelInfo(RpClump* pRpClump) {
    return FRAMEPLG(RpClumpGetFrame(pRpClump), m_modelInfo);
}

float CVisibilityPlugins::GetDistanceSquaredFromCamera(RwFrame* pRwFrame) {
    RwMatrixTag* transformMatrix = RwFrameGetLTM(pRwFrame);
    CVector distance;
    RwV3dSub(&distance, &transformMatrix->pos, ms_pCameraPosn);
    return distance.SquaredMagnitude();
}

float CVisibilityPlugins::GetDistanceSquaredFromCamera(CVector* pPos) {
    CVector distance;
    RwV3dSub(&distance, pPos, ms_pCameraPosn);
    return distance.SquaredMagnitude();
}

float CVisibilityPlugins::GetDotProductWithCameraVector(RwMatrixTag* atomicMatrix, RwMatrixTag* clumpMatrix, std::uint16_t flags) {
    float dotProduct1 = 0.0f;
    float dotProduct2 = *(float*)&atomicMatrix; // really?
    RwV3d distance;
    RwV3dSub(&distance, &atomicMatrix->pos, ms_pCameraPosn);
    if (flags & (ATOMIC_IS_REAR | ATOMIC_IS_FRONT))
        dotProduct1 = RwV3dDotProduct(&clumpMatrix->up, &distance);
    else if (flags & (ATOMIC_IS_RIGHT | ATOMIC_IS_LEFT))
        dotProduct1 = RwV3dDotProduct(&clumpMatrix->right, &distance);
    if (flags & (ATOMIC_IS_REAR | ATOMIC_IS_LEFT))
        dotProduct1 = -dotProduct1;
    if (flags & ATOMIC_VEHCOMP_15) {
        const float dot = RwV3dDotProduct(&clumpMatrix->at, &distance);
        if (flags & (ATOMIC_IS_FRONT_DOOR | ATOMIC_IS_REAR_DOOR))
            dotProduct1 += dot * 0.25f;
        else
            dotProduct1 += dot * 2.5f;
    }
    if (!(flags & (ATOMIC_IS_FRONT_DOOR | ATOMIC_IS_REAR_DOOR)))
        return dotProduct1;
    if (flags & ATOMIC_IS_REAR_DOOR)
        dotProduct2 = -RwV3dDotProduct(&clumpMatrix->up, &distance);
    else if (flags & ATOMIC_IS_FRONT_DOOR)
        dotProduct2 = RwV3dDotProduct(&clumpMatrix->up, &distance);
    if (dotProduct1 < 0.0f && dotProduct2 < 0.0f)
        return dotProduct1 + dotProduct2;
    if (dotProduct1 > 0.0f && dotProduct2 > 0.0f)
        return dotProduct1 + dotProduct2;
    return dotProduct1;
}

std::int32_t CVisibilityPlugins::GetFrameHierarchyId(RwFrame* pRwFrame) {
    return FRAMEPLG(pRwFrame, m_hierarchyId);
}

std::int16_t CVisibilityPlugins::GetModelInfoIndex(RpAtomic* pRpAtomic) {
    return ATOMICPLG(pRpAtomic, m_modelId);
}

std::int16_t CVisibilityPlugins::GetUserValue(RpAtomic* pRpAtomic) {
    return ATOMICPLG(pRpAtomic, m_userValue);
}

// Unused
bool CVisibilityPlugins::IsAtomicVisible(RpAtomic* pRpAtomic) {
    if (pRpAtomic->interpolator.flags & rpINTERPOLATORDIRTYSPHERE)
        _rpAtomicResyncInterpolatedSphere(pRpAtomic);
    RwSphere sphere = pRpAtomic->boundingSphere;
    RwMatrixTag* transformMatrix = RwFrameGetMatrix(RpAtomicGetFrame(pRpAtomic));
    RwV3d point;
    RwV3dTransformPoints(&point, &sphere.center, 1, transformMatrix);
    return RwCameraFrustumTestSphere(CVisibilityPlugins::ms_pCamera, &sphere) != rwSPHEREOUTSIDE;
}

// Unused
bool CVisibilityPlugins::IsClumpVisible(RpClump* pRpClump) {
    return plugin::CallAndReturn<bool, 0x732AE0, RpClump*>(pRpClump);
}

void CVisibilityPlugins::RenderAlphaAtomic(RpAtomic* atomic, std::int32_t alpha) {
    std::uint8_t alphas[152];
    RpGeometry* geometry = atomic->geometry;
    std::uint32_t geometryFlags = RpGeometryGetFlags(geometry);
    RpGeometrySetFlags(geometry, geometryFlags | rpGEOMETRYMODULATEMATERIALCOLOR);
    const std::int32_t numMaterials = RpGeometryGetNumMaterials(geometry);
    for (std::int32_t i = 0; i < numMaterials; i++) {
        RpMaterial* material = RpGeometryGetMaterial(geometry, i);
        RwRGBA* color = RpMaterialGetColor(material);
        alphas[i] = color->alpha;
        color->alpha = std::min(color->alpha, (std::uint8_t)alpha);
    }
    AtomicDefaultRenderCallBack(atomic);
    for (std::int32_t i = 0; i < numMaterials; i++) {
        RpMaterial* material = RpGeometryGetMaterial(geometry, i);
        RwRGBA* color = RpMaterialGetColor(material);
        color->alpha = alphas[i];
    }
    geometry->flags = geometryFlags;
}

void CVisibilityPlugins::RenderAlphaAtomics() {
    RenderOrderedList(m_alphaList);
}

RpAtomic* CVisibilityPlugins::RenderAtomicWithAlphaCB(RpAtomic* pRpAtomic, void* pData) {
    if (RpAtomicGetFlags(pRpAtomic) & rpATOMICRENDER)
        RenderAlphaAtomic(pRpAtomic, *reinterpret_cast<std::int32_t*>(pData));
    return pRpAtomic;
}

void CVisibilityPlugins::RenderBoatAlphaAtomics() {
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)rwCULLMODECULLNONE);
    RenderOrderedList(m_alphaBoatAtomicList);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)rwCULLMODECULLBACK);
}

void CVisibilityPlugins::RenderEntity(CEntity* entity, int unused, float distance) {
    if (!entity->m_pRwObject)
        return;
    
    CBaseModelInfo* pModelInfo = CModelInfo::GetModelInfo(entity->m_nModelIndex);
    if (pModelInfo->bDontWriteZBuffer)
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, 0);
    if (!entity->m_bDistanceFade) {
        if (CGame::currArea || pModelInfo->bDontWriteZBuffer)
            RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, (void*)0);
        else
            RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, (void*)100u);
        CRenderer::RenderOneNonRoad(entity);
    }
    else {
        RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, (void*)0);
        std::int32_t alpha = CalculateFadingAtomicAlpha(pModelInfo, entity, distance);
        entity->m_bImBeingRendered = true;
        if (!entity->m_bBackfaceCulled)
            RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)rwCULLMODECULLNONE);
        bool bLightingSetup = entity->SetupLighting();
        if (RwObjectGetType(entity->m_pRwObject) == rpATOMIC)
            RenderFadingAtomic(pModelInfo, entity->m_pRwAtomic, alpha);
        else
            RenderFadingClump(pModelInfo, entity->m_pRwClump, alpha);
        entity->RemoveLighting(bLightingSetup);
        entity->m_bImBeingRendered = false;
        if (!entity->m_bBackfaceCulled)
            RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)rwCULLMODECULLBACK);
    }
    
    if (pModelInfo->bDontWriteZBuffer)
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
}

void CVisibilityPlugins::RenderFadingAtomic(CBaseModelInfo* modelInfo, RpAtomic* atomic, std::int32_t alpha) {
    if (modelInfo->bAdditiveRender)
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDONE);
    RenderAlphaAtomic(atomic, alpha);
    if (modelInfo->bAdditiveRender)
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
}

void CVisibilityPlugins::RenderFadingClump(CBaseModelInfo* modelInfo, RpClump* clump, std::int32_t alpha) {
    if (modelInfo->bAdditiveRender)
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDONE);
    RpClumpForAllAtomics(clump, RenderAtomicWithAlphaCB, &alpha);
    if (modelInfo->bAdditiveRender)
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
}

RpAtomic* CVisibilityPlugins::RenderFadingClumpCB(RpAtomic* pRpAtomic) {
    if (GetClumpAlpha(RpAtomicGetClump(pRpAtomic)) == 255)
        AtomicDefaultRenderCallBack(pRpAtomic);
    else
        RenderAlphaAtomic(pRpAtomic, GetClumpAlpha(RpAtomicGetClump(pRpAtomic)));
    return pRpAtomic;
}

void CVisibilityPlugins::RenderFadingEntities() {
    RenderOrderedList(m_alphaEntityList);
    RenderBoatAlphaAtomics();
}

void CVisibilityPlugins::RenderFadingUnderwaterEntities() {
    RenderOrderedList(m_alphaUnderwaterEntityList);
}

RpAtomic* CVisibilityPlugins::RenderHeliRotorAlphaCB(RpAtomic* pRpAtomic) {
    if (gVehicleDistanceFromCamera >= ms_bigVehicleLod0Dist)
        return pRpAtomic;
    
    RwMatrixTag* atomicMatrix = RwFrameGetLTM(RpAtomicGetFrame(pRpAtomic));
    RwMatrixTag* clumpMatrix = RwFrameGetLTM(RpClumpGetFrame(RpAtomicGetClump(pRpAtomic)));
    RwV3d distance;
    RwV3dSub(&distance, &atomicMatrix->pos, ms_pCameraPosn);
    const float dotProduct = RwV3dDotProduct(&clumpMatrix->at, &distance);
    AlphaObjectInfo objectInfo{};
    objectInfo.m_atomic = pRpAtomic;
    objectInfo.m_pCallback = DefaultAtomicRenderCallback;
    objectInfo.m_distance = dotProduct * MAX_FADING_DISTANCE + gVehicleDistanceFromCamera;
    if (!m_alphaList.InsertSorted(objectInfo))
        AtomicDefaultRenderCallBack(pRpAtomic);
    return pRpAtomic;
}

RpAtomic* CVisibilityPlugins::RenderHeliTailRotorAlphaCB(RpAtomic* pRpAtomic) {
    if (gVehicleDistanceFromCamera >= ms_vehicleLod0Dist)
        return pRpAtomic;
    
    RwMatrixTag* atomicMatrix = RwFrameGetLTM(RpAtomicGetFrame(pRpAtomic));
    RwMatrixTag* clumpMatrix = RwFrameGetLTM(RpClumpGetFrame(RpAtomicGetClump(pRpAtomic)));
    RwV3d distance;
    RwV3dSub(&distance, &atomicMatrix->pos, ms_pCameraPosn);
    const float dotProduct1 = RwV3dDotProduct(&clumpMatrix->right, &distance);
    const float dotProduct2 = RwV3dDotProduct(&clumpMatrix->up, &distance);
    AlphaObjectInfo objectInfo{};
    objectInfo.m_atomic = pRpAtomic;
    objectInfo.m_pCallback = DefaultAtomicRenderCallback;
    objectInfo.m_distance = -dotProduct1 - dotProduct2 + gVehicleDistanceFromCamera;
    if (!m_alphaList.InsertSorted(objectInfo))
        AtomicDefaultRenderCallBack(pRpAtomic);
    return pRpAtomic;
}

// Unused
RpAtomic* CVisibilityPlugins::RenderObjNormalAtomic(RpAtomic* pRpAtomic) {
    RwMatrixTag* atomicMatrix = RwFrameGetLTM(RpAtomicGetFrame(pRpAtomic));
    RwV3d distance;
    RwV3dSub(&distance, &atomicMatrix->pos, ms_pCameraPosn);
    const float length = RwV3dLength(&distance);
    if (RwV3dDotProduct(&atomicMatrix->up, &distance) < length * -0.3f && length > 8.0f)
        return pRpAtomic;
    AtomicDefaultRenderCallBack(pRpAtomic);
    return pRpAtomic;
}

void CVisibilityPlugins::RenderOrderedList(CLinkList<CVisibilityPlugins::AlphaObjectInfo>& alphaObjectInfoList) {
    auto link = alphaObjectInfoList.usedListTail.prev;
    for (; link != &alphaObjectInfoList.usedListHead; link = link->prev) {
        auto callBack = reinterpret_cast<tAlphaRenderOrderedListCB>(link->data.m_pCallback);
        callBack(link->data.m_entity, link->data.m_distance);
    }
}

RpAtomic* CVisibilityPlugins::RenderPedCB(RpAtomic* pRpAtomic) {
    const float distanceSquared = GetDistanceSquaredFromCamera(RpAtomicGetFrame(pRpAtomic));
    if (distanceSquared >= ms_pedLodDist)
        return pRpAtomic;
    std::int32_t alpha = GetClumpAlpha(RpAtomicGetClump(pRpAtomic));
    if (alpha == 255) {
        AtomicDefaultRenderCallBack(pRpAtomic);
        return pRpAtomic;
    }
    RenderAlphaAtomic(pRpAtomic, alpha);
    return pRpAtomic;
}

RpMaterial* CVisibilityPlugins::SetTextureCB(RpMaterial* material, void* texture)
{
    RpMaterialSetTexture(material, reinterpret_cast<RwTexture*>(texture));
    return material;
}

RpAtomic* CVisibilityPlugins::RenderPlayerCB(RpAtomic* pRpAtomic) {
    RwTexture* skinTexture = CWorld::Players[0].m_pSkinTexture;
    if (skinTexture)
        RpGeometryForAllMaterials(RpAtomicGetGeometry(pRpAtomic), SetTextureCB, skinTexture);
    AtomicDefaultRenderCallBack(pRpAtomic);
    return pRpAtomic;
}

void CVisibilityPlugins::RenderReallyDrawLastObjects() {
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, 0);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)rwCULLMODECULLNONE);
    SetAmbientColours();
    DeActivateDirectional();
    RenderOrderedList(m_alphaReallyDrawLastList);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, FALSE);
}

RpAtomic* CVisibilityPlugins::RenderTrainHiDetailAlphaCB(RpAtomic* pRpAtomic) {
    if (gVehicleDistanceFromCamera >= ms_bigVehicleLod0Dist)
        return pRpAtomic;

    if (gVehicleDistanceFromCamera >= ms_vehicleLod0RenderMultiPassDist)
        SetAtomicFlag(pRpAtomic, ATOMIC_DISABLE_REFLECTIONS);
    else
        ClearAtomicFlag(pRpAtomic, ATOMIC_DISABLE_REFLECTIONS);
    RwMatrixTag* atomicMatrix = RwFrameGetLTM(RpAtomicGetFrame(pRpAtomic));
    std::uint16_t atomicFlags = GetAtomicId(pRpAtomic);
    RwMatrixTag* clumpMatrix = RwFrameGetLTM(RpClumpGetFrame(RpAtomicGetClump(pRpAtomic)));
    const float dot = GetDotProductWithCameraVector(atomicMatrix, clumpMatrix, atomicFlags);
    if (gVehicleDistanceFromCamera > ms_cullCompsDist
        && !(atomicFlags & ATOMIC_RENDER_ALWAYS)
        && gVehicleAngleToCamera < 0.2f
        && dot > 0.0f
        && ((atomicFlags & ATOMIC_CULL) || gVehicleDistanceFromCamera * 0.1f < dot * dot))
    {
        return pRpAtomic;
    }
    AlphaObjectInfo objectInfo;
    objectInfo.m_pCallback = DefaultAtomicRenderCallback;
    objectInfo.m_atomic = pRpAtomic;
    if (atomicFlags & ATOMIC_HAS_ALPHA)
        objectInfo.m_distance = gVehicleDistanceFromCamera;
    else
        objectInfo.m_distance = gVehicleDistanceFromCamera + dot;
    if (!m_alphaList.InsertSorted(objectInfo))
        AtomicDefaultRenderCallBack(pRpAtomic);

    return pRpAtomic;
}

RpAtomic* CVisibilityPlugins::RenderTrainHiDetailCB(RpAtomic* pRpAtomic) {
    if (gVehicleDistanceFromCamera >= ms_bigVehicleLod0Dist)
        return pRpAtomic;

    if (gVehicleDistanceFromCamera >= ms_vehicleLod0RenderMultiPassDist)
        SetAtomicFlag(pRpAtomic, ATOMIC_DISABLE_REFLECTIONS);
    else
        ClearAtomicFlag(pRpAtomic, ATOMIC_DISABLE_REFLECTIONS);
    std::uint16_t atomicFlags = GetAtomicId(pRpAtomic);
    if (gVehicleDistanceFromCamera > ms_cullCompsDist && !(atomicFlags & ATOMIC_RENDER_ALWAYS)) {
        if (gVehicleAngleToCamera < 0.2f) {
            RwMatrixTag* atomicMatrix = RwFrameGetLTM(RpAtomicGetFrame(pRpAtomic));
            RwMatrixTag* clumpMatrix = RwFrameGetLTM(RpClumpGetFrame(RpAtomicGetClump(pRpAtomic)));
            const float dot = GetDotProductWithCameraVector(atomicMatrix, clumpMatrix, atomicFlags);
            if (dot > 0.0f && ((atomicFlags & ATOMIC_CULL) || gVehicleDistanceFromCamera * 0.1f < dot * dot))
                return pRpAtomic;
        }
    }
    AtomicDefaultRenderCallBack(pRpAtomic);
    return pRpAtomic;

}

RpAtomic* CVisibilityPlugins::RenderVehicleHiDetailAlphaCB(RpAtomic* pRpAtomic) {
    if (gVehicleDistanceFromCamera >= ms_vehicleLod0Dist)
        return pRpAtomic;

    if (gVehicleDistanceFromCamera >= ms_vehicleLod0RenderMultiPassDist)
        SetAtomicFlag(pRpAtomic, ATOMIC_DISABLE_REFLECTIONS);
    else
        ClearAtomicFlag(pRpAtomic, ATOMIC_DISABLE_REFLECTIONS);
    std::uint16_t atomicFlags = GetAtomicId(pRpAtomic);
    RwMatrixTag* atomicMatrix = RwFrameGetLTM(RpAtomicGetFrame(pRpAtomic));
    RwMatrixTag* clumpMatrix = RwFrameGetLTM(RpClumpGetFrame(RpAtomicGetClump(pRpAtomic)));
    const float dot = GetDotProductWithCameraVector(atomicMatrix, clumpMatrix, atomicFlags);
    if (gVehicleDistanceFromCamera > ms_cullCompsDist
        && !(atomicFlags & ATOMIC_RENDER_ALWAYS)
        && gVehicleAngleToCamera < 0.2f
        && dot > 0.0f
        && ((atomicFlags & ATOMIC_CULL) || gVehicleDistanceFromCamera * 0.1f < dot * dot))
    {
        return pRpAtomic;
    }
    AlphaObjectInfo objectInfo;
    objectInfo.m_pCallback = DefaultAtomicRenderCallback;
    objectInfo.m_atomic = pRpAtomic;
    if (atomicFlags & ATOMIC_HAS_ALPHA)
        objectInfo.m_distance = gVehicleDistanceFromCamera - 0.0001f;
    else
        objectInfo.m_distance = gVehicleDistanceFromCamera + dot;
    if (!m_alphaList.InsertSorted(objectInfo))
        AtomicDefaultRenderCallBack(pRpAtomic);

    return pRpAtomic;
}

RpAtomic* CVisibilityPlugins::RenderVehicleHiDetailAlphaCB_BigVehicle(RpAtomic* pRpAtomic) {
    if (gVehicleDistanceFromCamera >= ms_bigVehicleLod0Dist)
        return pRpAtomic;

    if (gVehicleDistanceFromCamera >= ms_vehicleLod0RenderMultiPassDist)
        SetAtomicFlag(pRpAtomic, ATOMIC_DISABLE_REFLECTIONS);
    else
        ClearAtomicFlag(pRpAtomic, ATOMIC_DISABLE_REFLECTIONS);
    std::uint16_t atomicFlags = GetAtomicId(pRpAtomic);
    RwMatrixTag* atomicMatrix = RwFrameGetLTM(RpAtomicGetFrame(pRpAtomic));
    RwMatrixTag* clumpMatrix = RwFrameGetLTM(RpClumpGetFrame(RpAtomicGetClump(pRpAtomic)));
    const float dot = GetDotProductWithCameraVector(atomicMatrix, clumpMatrix, atomicFlags);
    if (gVehicleDistanceFromCamera > ms_cullBigCompsDist
        && !(atomicFlags & ATOMIC_RENDER_ALWAYS)
        && gVehicleAngleToCamera < 0.2f
        && dot > 0.0f
        && ((atomicFlags & ATOMIC_CULL) || gVehicleDistanceFromCamera * 0.1f < dot * dot))
    {
        return pRpAtomic;
    }
    AlphaObjectInfo objectInfo;
    objectInfo.m_pCallback = DefaultAtomicRenderCallback;
    objectInfo.m_atomic = pRpAtomic;
    if (atomicFlags & ATOMIC_HAS_ALPHA)
        objectInfo.m_distance = gVehicleDistanceFromCamera - 0.0001f;
    else
        objectInfo.m_distance = gVehicleDistanceFromCamera + dot;
    if (!m_alphaList.InsertSorted(objectInfo))
        AtomicDefaultRenderCallBack(pRpAtomic);

    return pRpAtomic;
}

RpAtomic* CVisibilityPlugins::RenderVehicleHiDetailAlphaCB_Boat(RpAtomic* pRpAtomic) {
    if (gVehicleDistanceFromCamera >= ms_vehicleLod0Dist)
        return pRpAtomic;

    if (gVehicleDistanceFromCamera >= ms_vehicleLod0RenderMultiPassDist)
        SetAtomicFlag(pRpAtomic, ATOMIC_DISABLE_REFLECTIONS);
    else
        ClearAtomicFlag(pRpAtomic, ATOMIC_DISABLE_REFLECTIONS);
    std::uint16_t atomicFlags = GetAtomicId(pRpAtomic);
    if (atomicFlags & ATOMIC_HAS_ALPHA) {
        AlphaObjectInfo objectInfo;
        objectInfo.m_distance = gVehicleDistanceFromCamera;
        objectInfo.m_atomic = pRpAtomic;
        objectInfo.m_pCallback = CVisibilityPlugins::DefaultAtomicRenderCallback;
        if (m_alphaBoatAtomicList.InsertSorted(objectInfo))
            return pRpAtomic;
    }
    AtomicDefaultRenderCallBack(pRpAtomic);
    return pRpAtomic;
}

RpAtomic* CVisibilityPlugins::RenderVehicleHiDetailCB(RpAtomic* pRpAtomic) {
    if (gVehicleDistanceFromCamera >= ms_vehicleLod0Dist)
        return pRpAtomic;

    if (gVehicleDistanceFromCamera >= ms_vehicleLod0RenderMultiPassDist)
        SetAtomicFlag(pRpAtomic, ATOMIC_DISABLE_REFLECTIONS);
    else
        ClearAtomicFlag(pRpAtomic, ATOMIC_DISABLE_REFLECTIONS);
    std::uint16_t atomicFlags = GetAtomicId(pRpAtomic);
    if (gVehicleDistanceFromCamera > ms_cullCompsDist && !(atomicFlags & ATOMIC_RENDER_ALWAYS)) {
        if (gVehicleAngleToCamera < 0.2f) {
            RwMatrixTag* atomicMatrix = RwFrameGetLTM(RpAtomicGetFrame(pRpAtomic));
            RwMatrixTag* clumpMatrix = RwFrameGetLTM(RpClumpGetFrame(RpAtomicGetClump(pRpAtomic)));
            const float dot = GetDotProductWithCameraVector(atomicMatrix, clumpMatrix, atomicFlags);
            if (dot > 0.0f && ((atomicFlags & ATOMIC_CULL) || gVehicleDistanceFromCamera * 0.1f < dot * dot))
                return pRpAtomic;
        }
    }
    AtomicDefaultRenderCallBack(pRpAtomic);

    return pRpAtomic;
}

RpAtomic* CVisibilityPlugins::RenderVehicleHiDetailCB_BigVehicle(RpAtomic* pRpAtomic) {
    if (gVehicleDistanceFromCamera >= ms_bigVehicleLod0Dist)
        return pRpAtomic;
    if (gVehicleDistanceFromCamera >= ms_vehicleLod0RenderMultiPassDist)
        SetAtomicFlag(pRpAtomic, ATOMIC_DISABLE_REFLECTIONS);
    else
        ClearAtomicFlag(pRpAtomic, ATOMIC_DISABLE_REFLECTIONS);
    std::uint16_t atomicFlags = GetAtomicId(pRpAtomic);
    if (gVehicleDistanceFromCamera > ms_cullBigCompsDist && !(atomicFlags & ATOMIC_RENDER_ALWAYS)) {
        if (gVehicleAngleToCamera < 0.2f) {
            RwMatrixTag* atomicMatrix = RwFrameGetLTM(RpAtomicGetFrame(pRpAtomic));
            RwMatrixTag* clumpMatrix = RwFrameGetLTM(RpClumpGetFrame(RpAtomicGetClump(pRpAtomic)));
            const float dot = GetDotProductWithCameraVector(atomicMatrix, clumpMatrix, atomicFlags);
            if (dot > 0.0f)
                return pRpAtomic;
        }
    }
    AtomicDefaultRenderCallBack(pRpAtomic);

    return pRpAtomic;
}

RpAtomic* CVisibilityPlugins::RenderVehicleHiDetailCB_Boat(RpAtomic* pRpAtomic) {
    if (gVehicleDistanceFromCamera >= ms_vehicleLod0Dist)
        return pRpAtomic;
    if (gVehicleDistanceFromCamera >= ms_vehicleLod0RenderMultiPassDist)
        SetAtomicFlag(pRpAtomic, ATOMIC_DISABLE_REFLECTIONS);
    else
        ClearAtomicFlag(pRpAtomic, ATOMIC_DISABLE_REFLECTIONS);
    AtomicDefaultRenderCallBack(pRpAtomic);

    return pRpAtomic;
}

RpAtomic* CVisibilityPlugins::RenderVehicleLoDetailCB_Boat(RpAtomic* pRpAtomic) {
    if (gVehicleDistanceFromCamera < ms_vehicleLod0Dist)
        return pRpAtomic;

    SetAtomicFlag(pRpAtomic, ATOMIC_DISABLE_REFLECTIONS);
    if (GetClumpAlpha(RpAtomicGetClump(pRpAtomic)) == 255)
        AtomicDefaultRenderCallBack(pRpAtomic);
    else
        RenderAlphaAtomic(pRpAtomic, GetClumpAlpha(RpAtomicGetClump(pRpAtomic)));

    return pRpAtomic;
}

RpAtomic* CVisibilityPlugins::RenderVehicleReallyLowDetailCB(RpAtomic* pRpAtomic) {
    if (gVehicleDistanceFromCamera < ms_vehicleLod0Dist)
        return pRpAtomic;

    SetAtomicFlag(pRpAtomic, ATOMIC_DISABLE_REFLECTIONS);
    if (GetClumpAlpha(RpAtomicGetClump(pRpAtomic)) == 255)
        AtomicDefaultRenderCallBack(pRpAtomic);
    else
        RenderAlphaAtomic(pRpAtomic, GetClumpAlpha(RpAtomicGetClump(pRpAtomic)));

    return pRpAtomic;
}

RpAtomic* CVisibilityPlugins::RenderVehicleReallyLowDetailCB_BigVehicle(RpAtomic* pRpAtomic) {
    if (gVehicleDistanceFromCamera >= ms_bigVehicleLod0Dist)
        AtomicDefaultRenderCallBack(pRpAtomic);

    return pRpAtomic;
}

RpAtomic* CVisibilityPlugins::RenderWeaponCB(RpAtomic* pRpAtomic) {
    RpClump* pClump = RpAtomicGetClump(pRpAtomic);
    CClumpModelInfo* modelInfo = GetClumpModelInfo(pClump);
    const float drawDistanceRadius = TheCamera.m_fLODDistMultiplier * modelInfo->m_fDrawDistance;
    if (GetDistanceSquaredFromCamera(RpClumpGetFrame(pClump)) < drawDistanceRadius * drawDistanceRadius)
        AtomicDefaultRenderCallBack(pRpAtomic);

    return pRpAtomic;
}

void CVisibilityPlugins::RenderWeaponPedsForPC() {
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, (void*)20);
    auto link = ms_weaponPedsForPC.usedListTail.prev;
    for (; link != &ms_weaponPedsForPC.usedListHead; link = link->prev) {
        CPed* ped = link->data;
        if (ped && ped->m_pWeaponObject) {
            ped->SetupLighting();
            const CWeapon& activeWeapon = ped->GetActiveWeapon();
            RpHAnimHierarchy* pRpAnimHierarchy = GetAnimHierarchyFromSkinClump(ped->m_pRwClump);
            const std::int32_t boneID = activeWeapon.m_nType != WEAPON_PARACHUTE ? BONE_R_HAND : BONE_SPINE1;
            std::int32_t animIDIndex = RpHAnimIDGetIndex(pRpAnimHierarchy, boneID);
            RwMatrixTag* pRightHandMatrix = &RpHAnimHierarchyGetMatrixArray(pRpAnimHierarchy)[animIDIndex];
            if (boneID == BONE_NORMAL)
                pRightHandMatrix = ped->GetModellingMatrix();
            RwFrame* weaponFrame = RpClumpGetFrame(ped->m_pWeaponObject);
            RwMatrixTag* weaponRwMatrix = RwFrameGetMatrix(weaponFrame);
            memcpy(weaponRwMatrix, pRightHandMatrix, sizeof(RwMatrixTag));
            if (activeWeapon.m_nType == WEAPON_PARACHUTE) {
                static RwV3d rightWeaponTranslate = { 0.1f, -0.15f, 0.0f };
                RwMatrixTranslate(weaponRwMatrix, &rightWeaponTranslate, rwCOMBINEPRECONCAT);
                RwMatrixRotate(weaponRwMatrix, &CPedIK::YaxisIK, 90.0f, rwCOMBINEPRECONCAT);
            }
            ped->SetGunFlashAlpha(false);
            RwFrameUpdateObjects(weaponFrame);
            RpClumpRender(ped->m_pWeaponObject);
            eWeaponSkill weaponSkill = ped->GetWeaponSkill();
            if (CWeaponInfo::GetWeaponInfo(activeWeapon.m_nType, weaponSkill)->flags.bTwinPistol) {
                std::int32_t animIDIndex = RpHAnimIDGetIndex(pRpAnimHierarchy, BONE_L_HAND);
                RwMatrixTag* pLeftHandMatrix = &RpHAnimHierarchyGetMatrixArray(pRpAnimHierarchy)[animIDIndex];
                memcpy(weaponRwMatrix, pLeftHandMatrix, sizeof(RwMatrixTag));
                RwMatrixRotate(weaponRwMatrix, &CPedIK::XaxisIK, 180.0f, rwCOMBINEPRECONCAT);
                static RwV3d leftWeaponTranslate = { 0.04f, -0.05f, 0.0f };
                RwMatrixTranslate(weaponRwMatrix, &leftWeaponTranslate, rwCOMBINEPRECONCAT);
                ped->SetGunFlashAlpha(true);
                RwFrameUpdateObjects(weaponFrame);
                RpClumpRender(ped->m_pWeaponObject);
            }
            ped->ResetGunFlashAlpha();
        }
    }
}

RpAtomic* CVisibilityPlugins::SetAtomicFlagCB(RpAtomic* pRpAtomic, void* data) {
    std::uint16_t flag = *reinterpret_cast<std::uint16_t*>(&data);
    ATOMICPLG(pRpAtomic, m_flags) |= flag;
    return pRpAtomic;
}

void CVisibilityPlugins::SetAtomicFlag(RpAtomic* pRpAtomic, std::uint16_t flag) {
    ATOMICPLG(pRpAtomic, m_flags) |= flag;
}

void CVisibilityPlugins::SetClumpForAllAtomicsFlag(RpClump* pRpClump, std::uint16_t flag) {
    RpClumpForAllAtomics(pRpClump, SetAtomicFlagCB, (void*)flag);
}

void CVisibilityPlugins::SetAtomicId(void* pRpAtomic, std::int16_t id) {
    ATOMICPLG(pRpAtomic, m_modelId) = id;
}

void CVisibilityPlugins::SetAtomicRenderCallback(RpAtomic* atomic, RpAtomicCallBackRender renderCB) {
    if (!renderCB)
        renderCB = AtomicDefaultRenderCallBack;
    atomic->renderCallBack = renderCB;
    if (!renderCB)
        atomic->renderCallBack = AtomicDefaultRenderCallBack;
}

void CVisibilityPlugins::SetClumpAlpha(RpClump* pRpClump, int dwAlpha) {
    CLUMPPLG(pRpClump, m_alpha) = dwAlpha;
}

void CVisibilityPlugins::SetClumpModelInfo(RpClump* pRpClump, CClumpModelInfo* pClumpModelInfo) {
    FRAMEPLG(RpClumpGetFrame(pRpClump), m_modelInfo) = pClumpModelInfo;
    if (pClumpModelInfo->GetModelType() != MODEL_INFO_VEHICLE)
        return;

    auto pVehicleModelInfo = reinterpret_cast<CVehicleModelInfo*>(pClumpModelInfo);
    if (pVehicleModelInfo->m_nVehicleType == VEHICLE_TRAIN || pVehicleModelInfo->m_nVehicleType == VEHICLE_FPLANE)
        CLUMPPLG(pRpClump, m_visibilityCallBack) = VehicleVisibilityCB_BigVehicle;
    else
        CLUMPPLG(pRpClump, m_visibilityCallBack) = VehicleVisibilityCB;
}

void CVisibilityPlugins::SetFrameHierarchyId(RwFrame* pRwFrame, std::int32_t id) {
    FRAMEPLG(pRwFrame, m_hierarchyId) = id;
}

void CVisibilityPlugins::SetRenderWareCamera(RwCamera* pRwCamera) {
    ms_pCamera = pRwCamera;
    ms_pCameraPosn = static_cast<CVector*>(RwMatrixGetPos(RwFrameGetMatrix(RwCameraGetFrame(pRwCamera))));
    ms_cullCompsDist = std::powf(TheCamera.m_fLODDistMultiplier * 20.0f, 2.0f);
    ms_cullBigCompsDist = std::powf(TheCamera.m_fLODDistMultiplier * 50.0f, 2.0f);
    ms_vehicleLod0RenderMultiPassDist = std::powf(TheCamera.m_fGenerationDistMultiplier * 45.0f, 2.0f);
    ms_vehicleLod0RenderMultiPassDist += ms_vehicleLod0RenderMultiPassDist;
    ms_vehicleLod0Dist = std::powf(TheCamera.m_fGenerationDistMultiplier * 70.0f, 2.0f);
    ms_vehicleLod0Dist += ms_vehicleLod0Dist;
    float vehicleLodDistance = std::powf(TheCamera.m_fGenerationDistMultiplier * 150.0f, 2.0f);
    vehicleLodDistance += vehicleLodDistance;
    ms_vehicleLod1Dist = vehicleLodDistance;
    ms_bigVehicleLod0Dist = vehicleLodDistance;
    ms_pedLodDist = std::powf(TheCamera.m_fLODDistMultiplier * 60.0f, 2.0f);
    ms_pedLodDist += ms_pedLodDist;
    ms_pedFadeDist = std::powf(TheCamera.m_fLODDistMultiplier * 70.0f, 2.0f);
    ms_pedFadeDist += ms_pedFadeDist;
}

void CVisibilityPlugins::SetUserValue(RpAtomic* pRpAtomic, unsigned short value) {
    ATOMICPLG(pRpAtomic, m_flags) = value;
}

void CVisibilityPlugins::SetupVehicleVariables(RpClump* pRpClump) {
    if (RwObjectGetType(pRpClump) != rpCLUMP)
        return;

    RwFrame* frame = RpClumpGetFrame(pRpClump);
    RwMatrixTag* transformMatrix = RwFrameGetLTM(frame);
    CVector distance1;
    RwV3dSub(&distance1, &transformMatrix->pos, ms_pCameraPosn);
    gVehicleDistanceFromCamera = distance1.SquaredMagnitude();
    CVector2D distance2;
    RwV2dSub(&distance2, ms_pCameraPosn, RwMatrixGetPos(RwFrameGetMatrix(frame)));
    gVehicleAngleToCamera = atan2(ms_pCameraPosn->z - RwMatrixGetPos(RwFrameGetMatrix(frame))->z, distance2.Magnitude());
}

bool CVisibilityPlugins::VehicleVisibilityCB(RpClump* pRpClump) {
    const float distanceSquared = GetDistanceSquaredFromCamera(RpClumpGetFrame(pRpClump));
    if (distanceSquared <= ms_vehicleLod1Dist)
        return FrustumSphereCB(pRpClump);

    return false;
}

bool CVisibilityPlugins::VehicleVisibilityCB_BigVehicle(RpClump* pRpClump) {
    return FrustumSphereCB(pRpClump);
}
