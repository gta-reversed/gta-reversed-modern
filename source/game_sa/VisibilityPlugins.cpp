/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

int32& CVisibilityPlugins::ms_atomicPluginOffset = *(int32*)0x8D608C;
int32& CVisibilityPlugins::ms_clumpPluginOffset = *(int32*)0x8D6094;
int32& CVisibilityPlugins::ms_framePluginOffset = *(int32*)0x8D6090;

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
    using namespace ReversibleHooks;
    Install("CVisibilityPlugins", "Initialise", 0x733A20, &CVisibilityPlugins::Initialise);
    Install("CVisibilityPlugins", "Shutdown", 0x732EB0, &CVisibilityPlugins::Shutdown);
    Install("CVisibilityPlugins", "AtomicCopyConstructor", 0x732170, &CVisibilityPlugins::AtomicCopyConstructor);
    Install("CVisibilityPlugins", "AtomicDestructor", 0x7321A0, &CVisibilityPlugins::AtomicDestructor);
    Install("CVisibilityPlugins", "CalculateFadingAtomicAlpha", 0x732500, &CVisibilityPlugins::CalculateFadingAtomicAlpha);
    Install("CVisibilityPlugins", "ClearAtomicFlag_0", 0x732310, &CVisibilityPlugins::ClearAtomicFlag);
    Install("CVisibilityPlugins", "ClearAtomicFlag_1", 0x732330, &CVisibilityPlugins::ClearAtomicFlag);
    Install("CVisibilityPlugins", "ClearClumpForAllAtomicsFlag", 0x732350, &CVisibilityPlugins::ClearClumpForAllAtomicsFlag);
    Install("CVisibilityPlugins", "ClumpConstructor", 0x732E10, &CVisibilityPlugins::ClumpConstructor);
    Install("CVisibilityPlugins", "ClumpCopyConstructor", 0x732200, &CVisibilityPlugins::ClumpCopyConstructor);
    Install("CVisibilityPlugins", "ClumpDestructor", 0x732220, &CVisibilityPlugins::ClumpDestructor);
    Install("CVisibilityPlugins", "DefaultVisibilityCB", 0x732A30, &CVisibilityPlugins::DefaultVisibilityCB);
    Install("CVisibilityPlugins", "FrameConstructor", 0x7321B0, &CVisibilityPlugins::FrameConstructor);
    Install("CVisibilityPlugins", "FrameCopyConstructor", 0x7321D0, &CVisibilityPlugins::FrameCopyConstructor);
    Install("CVisibilityPlugins", "FrameDestructor", 0x7321F0, &CVisibilityPlugins::FrameDestructor);
    Install("CVisibilityPlugins", "FrustumSphereCB", 0x732A40, &CVisibilityPlugins::FrustumSphereCB);
    Install("CVisibilityPlugins", "GetAtomicId", 0x732370, &CVisibilityPlugins::GetAtomicId);
    Install("CVisibilityPlugins", "GetAtomicModelInfo", 0x732260, &CVisibilityPlugins::GetAtomicModelInfo);
    Install("CVisibilityPlugins", "GetClumpAlpha", 0x732B20, &CVisibilityPlugins::GetClumpAlpha);
    Install("CVisibilityPlugins", "GetClumpModelInfo", 0x732AC0, &CVisibilityPlugins::GetClumpModelInfo);
    Install("CVisibilityPlugins", "GetDistanceSquaredFromCamera_0", 0x732C80, static_cast<float (*)(RwFrame*)>(&CVisibilityPlugins::GetDistanceSquaredFromCamera));
    Install("CVisibilityPlugins", "GetDistanceSquaredFromCamera_1", 0x732CC0, static_cast<float (*)(CVector*)>(&CVisibilityPlugins::GetDistanceSquaredFromCamera));
    Install("CVisibilityPlugins", "GetDotProductWithCameraVector", 0x7326D0, &CVisibilityPlugins::GetDotProductWithCameraVector);
    Install("CVisibilityPlugins", "GetFrameHierarchyId", 0x732A20, &CVisibilityPlugins::GetFrameHierarchyId);
    Install("CVisibilityPlugins", "GetModelInfoIndex", 0x732250, &CVisibilityPlugins::GetModelInfoIndex);
    Install("CVisibilityPlugins", "GetUserValue", 0x7323A0, &CVisibilityPlugins::GetUserValue);
    Install("CVisibilityPlugins", "InitAlphaAtomicList", 0x734530, &CVisibilityPlugins::InitAlphaAtomicList);
    Install("CVisibilityPlugins", "InitAlphaEntityList", 0x734540, &CVisibilityPlugins::InitAlphaEntityList);
    Install("CVisibilityPlugins", "InsertEntityIntoEntityList", 0x733DD0, &CVisibilityPlugins::InsertEntityIntoEntityList);
    Install("CVisibilityPlugins", "InsertEntityIntoUnderwaterEntities", 0x733D90, &CVisibilityPlugins::InsertEntityIntoUnderwaterEntities);
    Install("CVisibilityPlugins", "InsertAtomicIntoReallyDrawLastList", 0x733E10, &CVisibilityPlugins::InsertAtomicIntoReallyDrawLastList);
    Install("CVisibilityPlugins", "InsertEntityIntoReallyDrawLastList", 0x733E50, &CVisibilityPlugins::InsertEntityIntoReallyDrawLastList);
    Install("CVisibilityPlugins", "InsertEntityIntoSortedList", 0x734570, &CVisibilityPlugins::InsertEntityIntoSortedList);
    Install("CVisibilityPlugins", "IsAtomicVisible", 0x732990, &CVisibilityPlugins::IsAtomicVisible);
    Install("CVisibilityPlugins", "PluginAttach", 0x732E30, &CVisibilityPlugins::PluginAttach);
    Install("CVisibilityPlugins", "RenderAlphaAtomic", 0x732480, &CVisibilityPlugins::RenderAlphaAtomic);
    Install("CVisibilityPlugins", "RenderAlphaAtomics", 0x733E90, &CVisibilityPlugins::RenderAlphaAtomics);
    Install("CVisibilityPlugins", "RenderAtomicWithAlphaCB", 0x732660, &CVisibilityPlugins::RenderAtomicWithAlphaCB);
    Install("CVisibilityPlugins", "RenderBoatAlphaAtomics", 0x733EC0, &CVisibilityPlugins::RenderBoatAlphaAtomics);
    Install("CVisibilityPlugins", "RenderEntity", 0x732B40, &CVisibilityPlugins::RenderEntity);
    Install("CVisibilityPlugins", "RenderFadingAtomic", 0x732610, &CVisibilityPlugins::RenderFadingAtomic);
    Install("CVisibilityPlugins", "RenderFadingClump", 0x732680, &CVisibilityPlugins::RenderFadingClump);
    Install("CVisibilityPlugins", "RenderFadingClumpCB", 0x733630, &CVisibilityPlugins::RenderFadingClumpCB);
    Install("CVisibilityPlugins", "RenderFadingEntities", 0x733F10, &CVisibilityPlugins::RenderFadingEntities);
    Install("CVisibilityPlugins", "RenderFadingUnderwaterEntities", 0x7337D0, &CVisibilityPlugins::RenderFadingUnderwaterEntities);
    Install("CVisibilityPlugins", "RenderHeliRotorAlphaCB", 0x7340B0, &CVisibilityPlugins::RenderHeliRotorAlphaCB);
    Install("CVisibilityPlugins", "RenderHeliTailRotorAlphaCB", 0x734170, &CVisibilityPlugins::RenderHeliTailRotorAlphaCB);
    Install("CVisibilityPlugins", "RenderObjNormalAtomic", 0x7323E0, &CVisibilityPlugins::RenderObjNormalAtomic);
    Install("CVisibilityPlugins", "RenderOrderedList", 0x7337A0, &CVisibilityPlugins::RenderOrderedList);
    Install("CVisibilityPlugins", "RenderPedCB", 0x7335B0, &CVisibilityPlugins::RenderPedCB);
    Install("CVisibilityPlugins", "RenderPlayerCB", 0x732870, &CVisibilityPlugins::RenderPlayerCB);
    Install("CVisibilityPlugins", "RenderReallyDrawLastObjects", 0x733800, &CVisibilityPlugins::RenderReallyDrawLastObjects);
    Install("CVisibilityPlugins", "RenderTrainHiDetailAlphaCB", 0x734240, &CVisibilityPlugins::RenderTrainHiDetailAlphaCB);
    Install("CVisibilityPlugins", "RenderTrainHiDetailCB", 0x733330, &CVisibilityPlugins::RenderTrainHiDetailCB);
    Install("CVisibilityPlugins", "RenderVehicleHiDetailAlphaCB", 0x733F80, &CVisibilityPlugins::RenderVehicleHiDetailAlphaCB);
    Install("CVisibilityPlugins", "RenderVehicleHiDetailAlphaCB_BigVehicle", 0x734370, &CVisibilityPlugins::RenderVehicleHiDetailAlphaCB_BigVehicle);
    Install("CVisibilityPlugins", "RenderVehicleHiDetailAlphaCB_Boat", 0x7344A0, &CVisibilityPlugins::RenderVehicleHiDetailAlphaCB_Boat);
    Install("CVisibilityPlugins", "RenderVehicleHiDetailCB", 0x733240, &CVisibilityPlugins::RenderVehicleHiDetailCB);
    Install("CVisibilityPlugins", "RenderVehicleHiDetailCB_BigVehicle", 0x733420, &CVisibilityPlugins::RenderVehicleHiDetailCB_BigVehicle);
    Install("CVisibilityPlugins", "RenderVehicleHiDetailCB_Boat", 0x733550, &CVisibilityPlugins::RenderVehicleHiDetailCB_Boat);
    Install("CVisibilityPlugins", "RenderVehicleLoDetailCB_Boat", 0x7334F0, &CVisibilityPlugins::RenderVehicleLoDetailCB_Boat);
    Install("CVisibilityPlugins", "RenderVehicleReallyLowDetailCB", 0x7331E0, &CVisibilityPlugins::RenderVehicleReallyLowDetailCB);
    Install("CVisibilityPlugins", "RenderVehicleReallyLowDetailCB_BigVehicle", 0x732820, &CVisibilityPlugins::RenderVehicleReallyLowDetailCB_BigVehicle);
    Install("CVisibilityPlugins", "RenderWeaponCB", 0x733670, &CVisibilityPlugins::RenderWeaponCB);
    Install("CVisibilityPlugins", "RenderWeaponPedsForPC", 0x732F30, &CVisibilityPlugins::RenderWeaponPedsForPC);
    Install("CVisibilityPlugins", "SetAtomicFlag_0", 0x7322D0, &CVisibilityPlugins::SetAtomicFlag);
    Install("CVisibilityPlugins", "SetAtomicFlag_1", 0x7322B0, &CVisibilityPlugins::SetAtomicFlag);
    Install("CVisibilityPlugins", "SetClumpForAllAtomicsFlag", 0x732307, &CVisibilityPlugins::SetClumpForAllAtomicsFlag);
    Install("CVisibilityPlugins", "SetAtomicId", 0x732230, &CVisibilityPlugins::SetAtomicId);
    Install("CVisibilityPlugins", "SetAtomicRenderCallback", 0x7328A0, &CVisibilityPlugins::SetAtomicRenderCallback);
    Install("CVisibilityPlugins", "SetClumpAlpha", 0x732B00, &CVisibilityPlugins::SetClumpAlpha);
    Install("CVisibilityPlugins", "SetClumpModelInfo", 0x733750, &CVisibilityPlugins::SetClumpModelInfo);
    Install("CVisibilityPlugins", "SetFrameHierarchyId", 0x732A00, &CVisibilityPlugins::SetFrameHierarchyId);
    Install("CVisibilityPlugins", "SetRenderWareCamera", 0x7328C0, &CVisibilityPlugins::SetRenderWareCamera);
    Install("CVisibilityPlugins", "SetUserValue", 0x732380, &CVisibilityPlugins::SetUserValue);
    Install("CVisibilityPlugins", "SetupVehicleVariables", 0x733160, &CVisibilityPlugins::SetupVehicleVariables);
    Install("CVisibilityPlugins", "VehicleVisibilityCB", 0x7336F0, &CVisibilityPlugins::VehicleVisibilityCB);
    Install("CVisibilityPlugins", "VehicleVisibilityCB_BigVehicle", 0x732AB0, &CVisibilityPlugins::VehicleVisibilityCB_BigVehicle);
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
    AlphaObjectInfo info{};
    info.m_distance = distance;
    info.m_entity = entity;
    info.m_pCallback = CVisibilityPlugins::RenderEntity;
    return m_alphaUnderwaterEntityList.InsertSorted(info);
}

bool CVisibilityPlugins::InsertAtomicIntoReallyDrawLastList(RpAtomic* atomic, float distance) {
    AlphaObjectInfo info{};
    info.m_distance = distance;
    info.m_atomic = atomic;
    info.m_pCallback = DefaultAtomicRenderCallback;
    return m_alphaReallyDrawLastList.InsertSorted(info);
}

bool CVisibilityPlugins::InsertEntityIntoReallyDrawLastList(CEntity* entity, float distance) {
    AlphaObjectInfo info{};
    info.m_distance = distance;
    info.m_entity = entity;
    info.m_pCallback = CVisibilityPlugins::RenderEntity;
    return m_alphaReallyDrawLastList.InsertSorted(info);
}

// 0x734570
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
        AtomicCopyConstructor
    );
    ms_clumpPluginOffset = RpClumpRegisterPlugin(
        sizeof(tClumpVisibilityPlugin),
        MAKECHUNKID(rwVENDORID_ROCKSTAR, 0x01),
        ClumpConstructor,
        ClumpDestructor,
        ClumpCopyConstructor
    );
    ms_framePluginOffset = RwFrameRegisterPlugin(
        sizeof(tFrameVisibilityPlugin),
        MAKECHUNKID(rwVENDORID_ROCKSTAR, 0x02),
        FrameConstructor,
        FrameDestructor,
        FrameCopyConstructor
    );
    return ms_atomicPluginOffset != -1 && ms_clumpPluginOffset != -1;
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

int32 CVisibilityPlugins::CalculateFadingAtomicAlpha(CBaseModelInfo* modelInfo, CEntity* entity, float distance) {
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
    return static_cast<int32>(modelInfo->m_nAlpha * fFade);
}

void CVisibilityPlugins::ClearAtomicFlag(RpAtomic* atomic, uint16 flag) {
    ATOMICPLG(atomic, m_flags) &= ~flag;
}

RpAtomic* CVisibilityPlugins::ClearAtomicFlagCB(RpAtomic* atomic, void* data) {
    uint16 flag = *reinterpret_cast<uint16*>(&data);
    ATOMICPLG(atomic, m_flags) &= ~flag;
    return atomic;
}

void CVisibilityPlugins::ClearClumpForAllAtomicsFlag(RpClump* clump, uint16 flag) {
    RpClumpForAllAtomics(clump, ClearAtomicFlagCB, (void*)flag);
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

int32 CVisibilityPlugins::DefaultVisibilityCB() {
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

bool CVisibilityPlugins::FrustumSphereCB(RpClump* clump) {
    RwSphere sphere{};
    RwFrame* frame = RpClumpGetFrame(clump);
    CBaseModelInfo* modelInfo = FRAMEPLG(frame, m_modelInfo);
    sphere.radius = modelInfo->GetColModel()->GetBoundRadius();
    sphere.center = modelInfo->GetColModel()->GetBoundCenter();
    RwMatrixTag* transformMatrix = RwFrameGetLTM(frame);
    RwV3dTransformPoints(&sphere.center, &sphere.center, 1, transformMatrix);
    return RwCameraFrustumTestSphere(ms_pCamera, &sphere) != rwSPHEREOUTSIDE;
}

// The function name is misleading, it returns the flags
uint16 CVisibilityPlugins::GetAtomicId(RpAtomic* atomic) {
    return ATOMICPLG(atomic, m_flags);
}

CAtomicModelInfo* CVisibilityPlugins::GetAtomicModelInfo(RpAtomic* atomic) {
    int16 modelId = ATOMICPLG(atomic, m_modelId);
    if (modelId == -1)
        return nullptr;
    return static_cast<CAtomicModelInfo*>(CModelInfo::ms_modelInfoPtrs[modelId]);
}

int32 CVisibilityPlugins::GetClumpAlpha(RpClump* clump) {
    return CLUMPPLG(clump, m_alpha);
}

CClumpModelInfo* CVisibilityPlugins::GetClumpModelInfo(RpClump* clump) {
    return FRAMEPLG(RpClumpGetFrame(clump), m_modelInfo);
}

float CVisibilityPlugins::GetDistanceSquaredFromCamera(RwFrame* frame) {
    RwMatrixTag* transformMatrix = RwFrameGetLTM(frame);
    CVector distance;
    RwV3dSub(&distance, &transformMatrix->pos, ms_pCameraPosn);
    return distance.SquaredMagnitude();
}

float CVisibilityPlugins::GetDistanceSquaredFromCamera(CVector* pPos) {
    CVector distance;
    RwV3dSub(&distance, pPos, ms_pCameraPosn);
    return distance.SquaredMagnitude();
}

float CVisibilityPlugins::GetDotProductWithCameraVector(RwMatrixTag* atomicMatrix, RwMatrixTag* clumpMatrix, uint16 flags) {
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

int32 CVisibilityPlugins::GetFrameHierarchyId(RwFrame* frame) {
    return FRAMEPLG(frame, m_hierarchyId);
}

int16 CVisibilityPlugins::GetModelInfoIndex(RpAtomic* atomic) {
    return ATOMICPLG(atomic, m_modelId);
}

int16 CVisibilityPlugins::GetUserValue(RpAtomic* atomic) {
    return ATOMICPLG(atomic, m_userValue);
}

// Unused
bool CVisibilityPlugins::IsAtomicVisible(RpAtomic* atomic) {
    if (atomic->interpolator.flags & rpINTERPOLATORDIRTYSPHERE)
        _rpAtomicResyncInterpolatedSphere(atomic);
    RwSphere sphere = atomic->boundingSphere;
    RwMatrixTag* transformMatrix = RwFrameGetMatrix(RpAtomicGetFrame(atomic));
    RwV3d point;
    RwV3dTransformPoints(&point, &sphere.center, 1, transformMatrix);
    return RwCameraFrustumTestSphere(CVisibilityPlugins::ms_pCamera, &sphere) != rwSPHEREOUTSIDE;
}

// Unused
bool CVisibilityPlugins::IsClumpVisible(RpClump* clump) {
    return plugin::CallAndReturn<bool, 0x732AE0, RpClump*>(clump);
}

void CVisibilityPlugins::RenderAlphaAtomic(RpAtomic* atomic, int32 alpha) {
    uint8 alphas[152];
    RpGeometry* geometry = atomic->geometry;
    uint32 geometryFlags = RpGeometryGetFlags(geometry);
    RpGeometrySetFlags(geometry, geometryFlags | rpGEOMETRYMODULATEMATERIALCOLOR);
    const int32 numMaterials = RpGeometryGetNumMaterials(geometry);
    for (int32 i = 0; i < numMaterials; i++) {
        RpMaterial* material = RpGeometryGetMaterial(geometry, i);
        RwRGBA* color = RpMaterialGetColor(material);
        alphas[i] = color->alpha;
        color->alpha = std::min(color->alpha, (uint8)alpha);
    }
    AtomicDefaultRenderCallBack(atomic);
    for (int32 i = 0; i < numMaterials; i++) {
        RpMaterial* material = RpGeometryGetMaterial(geometry, i);
        RwRGBA* color = RpMaterialGetColor(material);
        color->alpha = alphas[i];
    }
    geometry->flags = geometryFlags;
}

void CVisibilityPlugins::RenderAlphaAtomics() {
    RenderOrderedList(m_alphaList);
}

RpAtomic* CVisibilityPlugins::RenderAtomicWithAlphaCB(RpAtomic* atomic, void* data) {
    if (RpAtomicGetFlags(atomic) & rpATOMICRENDER)
        RenderAlphaAtomic(atomic, *reinterpret_cast<int32*>(data));
    return atomic;
}

void CVisibilityPlugins::RenderBoatAlphaAtomics() {
    RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLNONE));
    RenderOrderedList(m_alphaBoatAtomicList);
    RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLBACK));
}

// 0x732B40
void CVisibilityPlugins::RenderEntity(CEntity* entity, int32 unused, float distance) {
    if (!entity->m_pRwObject)
        return;
    
    CBaseModelInfo* mi = CModelInfo::GetModelInfo(entity->m_nModelIndex);
    if (mi->bDontWriteZBuffer)
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, RWRSTATE(FALSE));

    if (!entity->m_bDistanceFade) {
        if (CGame::currArea || mi->bDontWriteZBuffer)
            RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, RWRSTATE(0));
        else
            RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, RWRSTATE(100u));
        CRenderer::RenderOneNonRoad(entity);
    }
    else {
        RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, RWRSTATE(0));
        int32 alpha = CalculateFadingAtomicAlpha(mi, entity, distance);
        entity->m_bImBeingRendered = true;
        if (!entity->m_bBackfaceCulled)
            RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLNONE));
        bool bLightingSetup = entity->SetupLighting();
        if (RwObjectGetType(entity->m_pRwObject) == rpATOMIC)
            RenderFadingAtomic(mi, entity->m_pRwAtomic, alpha);
        else
            RenderFadingClump(mi, entity->m_pRwClump, alpha);
        entity->RemoveLighting(bLightingSetup);
        entity->m_bImBeingRendered = false;
        if (!entity->m_bBackfaceCulled)
            RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLBACK));
    }
    
    if (mi->bDontWriteZBuffer)
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, RWRSTATE(TRUE));
}

void CVisibilityPlugins::RenderFadingAtomic(CBaseModelInfo* modelInfo, RpAtomic* atomic, int32 alpha) {
    if (modelInfo->bAdditiveRender)
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, RWRSTATE(rwBLENDONE));
    RenderAlphaAtomic(atomic, alpha);
    if (modelInfo->bAdditiveRender)
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, RWRSTATE(rwBLENDINVSRCALPHA));
}

void CVisibilityPlugins::RenderFadingClump(CBaseModelInfo* modelInfo, RpClump* clump, int32 alpha) {
    if (modelInfo->bAdditiveRender)
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, RWRSTATE(rwBLENDONE));
    RpClumpForAllAtomics(clump, RenderAtomicWithAlphaCB, &alpha);
    if (modelInfo->bAdditiveRender)
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, RWRSTATE(rwBLENDINVSRCALPHA));
}

RpAtomic* CVisibilityPlugins::RenderFadingClumpCB(RpAtomic* atomic) {
    if (GetClumpAlpha(RpAtomicGetClump(atomic)) == 255)
        AtomicDefaultRenderCallBack(atomic);
    else
        RenderAlphaAtomic(atomic, GetClumpAlpha(RpAtomicGetClump(atomic)));
    return atomic;
}

void CVisibilityPlugins::RenderFadingEntities() {
    RenderOrderedList(m_alphaEntityList);
    RenderBoatAlphaAtomics();
}

void CVisibilityPlugins::RenderFadingUnderwaterEntities() {
    RenderOrderedList(m_alphaUnderwaterEntityList);
}

RpAtomic* CVisibilityPlugins::RenderHeliRotorAlphaCB(RpAtomic* atomic) {
    if (gVehicleDistanceFromCamera >= ms_bigVehicleLod0Dist)
        return atomic;
    
    RwMatrixTag* atomicMatrix = RwFrameGetLTM(RpAtomicGetFrame(atomic));
    RwMatrixTag* clumpMatrix = RwFrameGetLTM(RpClumpGetFrame(RpAtomicGetClump(atomic)));
    RwV3d distance;
    RwV3dSub(&distance, &atomicMatrix->pos, ms_pCameraPosn);
    const float dotProduct = RwV3dDotProduct(&clumpMatrix->at, &distance);
    AlphaObjectInfo objectInfo{};
    objectInfo.m_atomic = atomic;
    objectInfo.m_pCallback = DefaultAtomicRenderCallback;
    objectInfo.m_distance = dotProduct * MAX_FADING_DISTANCE + gVehicleDistanceFromCamera;
    if (!m_alphaList.InsertSorted(objectInfo))
        AtomicDefaultRenderCallBack(atomic);
    return atomic;
}

RpAtomic* CVisibilityPlugins::RenderHeliTailRotorAlphaCB(RpAtomic* atomic) {
    if (gVehicleDistanceFromCamera >= ms_vehicleLod0Dist)
        return atomic;
    
    RwMatrixTag* atomicMatrix = RwFrameGetLTM(RpAtomicGetFrame(atomic));
    RwMatrixTag* clumpMatrix = RwFrameGetLTM(RpClumpGetFrame(RpAtomicGetClump(atomic)));
    RwV3d distance;
    RwV3dSub(&distance, &atomicMatrix->pos, ms_pCameraPosn);
    const float dotProduct1 = RwV3dDotProduct(&clumpMatrix->right, &distance);
    const float dotProduct2 = RwV3dDotProduct(&clumpMatrix->up, &distance);
    AlphaObjectInfo info{};
    info.m_atomic = atomic;
    info.m_pCallback = DefaultAtomicRenderCallback;
    info.m_distance = -dotProduct1 - dotProduct2 + gVehicleDistanceFromCamera;
    if (!m_alphaList.InsertSorted(info))
        AtomicDefaultRenderCallBack(atomic);
    return atomic;
}

// Unused
RpAtomic* CVisibilityPlugins::RenderObjNormalAtomic(RpAtomic* atomic) {
    RwMatrixTag* atomicMatrix = RwFrameGetLTM(RpAtomicGetFrame(atomic));
    RwV3d distance;
    RwV3dSub(&distance, &atomicMatrix->pos, ms_pCameraPosn);
    const float length = RwV3dLength(&distance);
    if (RwV3dDotProduct(&atomicMatrix->up, &distance) < length * -0.3f && length > 8.0f)
        return atomic;
    AtomicDefaultRenderCallBack(atomic);
    return atomic;
}

void CVisibilityPlugins::RenderOrderedList(CLinkList<CVisibilityPlugins::AlphaObjectInfo>& alphaObjectInfoList) {
    auto link = alphaObjectInfoList.usedListTail.prev;
    for (; link != &alphaObjectInfoList.usedListHead; link = link->prev) {
        auto callBack = reinterpret_cast<tAlphaRenderOrderedListCB>(link->data.m_pCallback);
        callBack(link->data.m_entity, link->data.m_distance);
    }
}

RpAtomic* CVisibilityPlugins::RenderPedCB(RpAtomic* atomic) {
    const float distanceSquared = GetDistanceSquaredFromCamera(RpAtomicGetFrame(atomic));
    if (distanceSquared >= ms_pedLodDist)
        return atomic;
    int32 alpha = GetClumpAlpha(RpAtomicGetClump(atomic));
    if (alpha == 255) {
        AtomicDefaultRenderCallBack(atomic);
        return atomic;
    }
    RenderAlphaAtomic(atomic, alpha);
    return atomic;
}

RpMaterial* CVisibilityPlugins::SetTextureCB(RpMaterial* material, void* texture)
{
    RpMaterialSetTexture(material, reinterpret_cast<RwTexture*>(texture));
    return material;
}

RpAtomic* CVisibilityPlugins::RenderPlayerCB(RpAtomic* atomic) {
    RwTexture* skinTexture = CWorld::Players[0].m_pSkinTexture;
    if (skinTexture)
        RpGeometryForAllMaterials(RpAtomicGetGeometry(atomic), SetTextureCB, skinTexture);
    AtomicDefaultRenderCallBack(atomic);
    return atomic;
}

void CVisibilityPlugins::RenderReallyDrawLastObjects() {
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,     RWRSTATE(NULL));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,          RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,         RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,         RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATECULLMODE,          RWRSTATE(rwCULLMODECULLNONE));
    SetAmbientColours();
    DeActivateDirectional();
    RenderOrderedList(m_alphaReallyDrawLastList);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,         RWRSTATE(FALSE));
}

RpAtomic* CVisibilityPlugins::RenderTrainHiDetailAlphaCB(RpAtomic* atomic) {
    if (gVehicleDistanceFromCamera >= ms_bigVehicleLod0Dist)
        return atomic;

    if (gVehicleDistanceFromCamera >= ms_vehicleLod0RenderMultiPassDist)
        SetAtomicFlag(atomic, ATOMIC_DISABLE_REFLECTIONS);
    else
        ClearAtomicFlag(atomic, ATOMIC_DISABLE_REFLECTIONS);
    RwMatrixTag* atomicMatrix = RwFrameGetLTM(RpAtomicGetFrame(atomic));
    uint16 atomicFlags = GetAtomicId(atomic);
    RwMatrixTag* clumpMatrix = RwFrameGetLTM(RpClumpGetFrame(RpAtomicGetClump(atomic)));
    const float dot = GetDotProductWithCameraVector(atomicMatrix, clumpMatrix, atomicFlags);
    if (gVehicleDistanceFromCamera > ms_cullCompsDist
        && !(atomicFlags & ATOMIC_RENDER_ALWAYS)
        && gVehicleAngleToCamera < 0.2f
        && dot > 0.0f
        && ((atomicFlags & ATOMIC_CULL) || gVehicleDistanceFromCamera * 0.1f < dot * dot))
    {
        return atomic;
    }
    AlphaObjectInfo info{};
    info.m_pCallback = DefaultAtomicRenderCallback;
    info.m_atomic = atomic;
    if (atomicFlags & ATOMIC_HAS_ALPHA)
        info.m_distance = gVehicleDistanceFromCamera;
    else
        info.m_distance = gVehicleDistanceFromCamera + dot;
    if (!m_alphaList.InsertSorted(info))
        AtomicDefaultRenderCallBack(atomic);

    return atomic;
}

RpAtomic* CVisibilityPlugins::RenderTrainHiDetailCB(RpAtomic* atomic) {
    if (gVehicleDistanceFromCamera >= ms_bigVehicleLod0Dist)
        return atomic;

    if (gVehicleDistanceFromCamera >= ms_vehicleLod0RenderMultiPassDist)
        SetAtomicFlag(atomic, ATOMIC_DISABLE_REFLECTIONS);
    else
        ClearAtomicFlag(atomic, ATOMIC_DISABLE_REFLECTIONS);
    uint16 atomicFlags = GetAtomicId(atomic);
    if (gVehicleDistanceFromCamera > ms_cullCompsDist && !(atomicFlags & ATOMIC_RENDER_ALWAYS)) {
        if (gVehicleAngleToCamera < 0.2f) {
            RwMatrixTag* atomicMatrix = RwFrameGetLTM(RpAtomicGetFrame(atomic));
            RwMatrixTag* clumpMatrix = RwFrameGetLTM(RpClumpGetFrame(RpAtomicGetClump(atomic)));
            const float dot = GetDotProductWithCameraVector(atomicMatrix, clumpMatrix, atomicFlags);
            if (dot > 0.0f && ((atomicFlags & ATOMIC_CULL) || gVehicleDistanceFromCamera * 0.1f < dot * dot))
                return atomic;
        }
    }
    AtomicDefaultRenderCallBack(atomic);
    return atomic;

}

RpAtomic* CVisibilityPlugins::RenderVehicleHiDetailAlphaCB(RpAtomic* atomic) {
    if (gVehicleDistanceFromCamera >= ms_vehicleLod0Dist)
        return atomic;

    if (gVehicleDistanceFromCamera >= ms_vehicleLod0RenderMultiPassDist)
        SetAtomicFlag(atomic, ATOMIC_DISABLE_REFLECTIONS);
    else
        ClearAtomicFlag(atomic, ATOMIC_DISABLE_REFLECTIONS);
    uint16 atomicFlags = GetAtomicId(atomic);
    RwMatrixTag* atomicMatrix = RwFrameGetLTM(RpAtomicGetFrame(atomic));
    RwMatrixTag* clumpMatrix = RwFrameGetLTM(RpClumpGetFrame(RpAtomicGetClump(atomic)));
    const float dot = GetDotProductWithCameraVector(atomicMatrix, clumpMatrix, atomicFlags);
    if (gVehicleDistanceFromCamera > ms_cullCompsDist
        && !(atomicFlags & ATOMIC_RENDER_ALWAYS)
        && gVehicleAngleToCamera < 0.2f
        && dot > 0.0f
        && ((atomicFlags & ATOMIC_CULL) || gVehicleDistanceFromCamera * 0.1f < dot * dot))
    {
        return atomic;
    }
    AlphaObjectInfo info{};
    info.m_pCallback = DefaultAtomicRenderCallback;
    info.m_atomic = atomic;
    if (atomicFlags & ATOMIC_HAS_ALPHA)
        info.m_distance = gVehicleDistanceFromCamera - 0.0001f;
    else
        info.m_distance = gVehicleDistanceFromCamera + dot;
    if (!m_alphaList.InsertSorted(info))
        AtomicDefaultRenderCallBack(atomic);

    return atomic;
}

RpAtomic* CVisibilityPlugins::RenderVehicleHiDetailAlphaCB_BigVehicle(RpAtomic* atomic) {
    if (gVehicleDistanceFromCamera >= ms_bigVehicleLod0Dist)
        return atomic;

    if (gVehicleDistanceFromCamera >= ms_vehicleLod0RenderMultiPassDist)
        SetAtomicFlag(atomic, ATOMIC_DISABLE_REFLECTIONS);
    else
        ClearAtomicFlag(atomic, ATOMIC_DISABLE_REFLECTIONS);
    uint16 atomicFlags = GetAtomicId(atomic);
    RwMatrixTag* atomicMatrix = RwFrameGetLTM(RpAtomicGetFrame(atomic));
    RwMatrixTag* clumpMatrix = RwFrameGetLTM(RpClumpGetFrame(RpAtomicGetClump(atomic)));
    const float dot = GetDotProductWithCameraVector(atomicMatrix, clumpMatrix, atomicFlags);
    if (gVehicleDistanceFromCamera > ms_cullBigCompsDist
        && !(atomicFlags & ATOMIC_RENDER_ALWAYS)
        && gVehicleAngleToCamera < 0.2f
        && dot > 0.0f
        && ((atomicFlags & ATOMIC_CULL) || gVehicleDistanceFromCamera * 0.1f < dot * dot))
    {
        return atomic;
    }
    AlphaObjectInfo info{};
    info.m_pCallback = DefaultAtomicRenderCallback;
    info.m_atomic = atomic;
    if (atomicFlags & ATOMIC_HAS_ALPHA)
        info.m_distance = gVehicleDistanceFromCamera - 0.0001f;
    else
        info.m_distance = gVehicleDistanceFromCamera + dot;
    if (!m_alphaList.InsertSorted(info))
        AtomicDefaultRenderCallBack(atomic);

    return atomic;
}

RpAtomic* CVisibilityPlugins::RenderVehicleHiDetailAlphaCB_Boat(RpAtomic* atomic) {
    if (gVehicleDistanceFromCamera >= ms_vehicleLod0Dist)
        return atomic;

    if (gVehicleDistanceFromCamera >= ms_vehicleLod0RenderMultiPassDist)
        SetAtomicFlag(atomic, ATOMIC_DISABLE_REFLECTIONS);
    else
        ClearAtomicFlag(atomic, ATOMIC_DISABLE_REFLECTIONS);
    uint16 atomicFlags = GetAtomicId(atomic);
    if (atomicFlags & ATOMIC_HAS_ALPHA) {
        AlphaObjectInfo info{};
        info.m_distance = gVehicleDistanceFromCamera;
        info.m_atomic = atomic;
        info.m_pCallback = CVisibilityPlugins::DefaultAtomicRenderCallback;
        if (m_alphaBoatAtomicList.InsertSorted(info))
            return atomic;
    }
    AtomicDefaultRenderCallBack(atomic);
    return atomic;
}

RpAtomic* CVisibilityPlugins::RenderVehicleHiDetailCB(RpAtomic* atomic) {
    if (gVehicleDistanceFromCamera >= ms_vehicleLod0Dist)
        return atomic;

    if (gVehicleDistanceFromCamera >= ms_vehicleLod0RenderMultiPassDist)
        SetAtomicFlag(atomic, ATOMIC_DISABLE_REFLECTIONS);
    else
        ClearAtomicFlag(atomic, ATOMIC_DISABLE_REFLECTIONS);
    uint16 atomicFlags = GetAtomicId(atomic);
    if (gVehicleDistanceFromCamera > ms_cullCompsDist && !(atomicFlags & ATOMIC_RENDER_ALWAYS)) {
        if (gVehicleAngleToCamera < 0.2f) {
            RwMatrixTag* atomicMatrix = RwFrameGetLTM(RpAtomicGetFrame(atomic));
            RwMatrixTag* clumpMatrix = RwFrameGetLTM(RpClumpGetFrame(RpAtomicGetClump(atomic)));
            const float dot = GetDotProductWithCameraVector(atomicMatrix, clumpMatrix, atomicFlags);
            if (dot > 0.0f && ((atomicFlags & ATOMIC_CULL) || gVehicleDistanceFromCamera * 0.1f < dot * dot))
                return atomic;
        }
    }
    AtomicDefaultRenderCallBack(atomic);

    return atomic;
}

RpAtomic* CVisibilityPlugins::RenderVehicleHiDetailCB_BigVehicle(RpAtomic* atomic) {
    if (gVehicleDistanceFromCamera >= ms_bigVehicleLod0Dist)
        return atomic;
    if (gVehicleDistanceFromCamera >= ms_vehicleLod0RenderMultiPassDist)
        SetAtomicFlag(atomic, ATOMIC_DISABLE_REFLECTIONS);
    else
        ClearAtomicFlag(atomic, ATOMIC_DISABLE_REFLECTIONS);
    uint16 atomicFlags = GetAtomicId(atomic);
    if (gVehicleDistanceFromCamera > ms_cullBigCompsDist && !(atomicFlags & ATOMIC_RENDER_ALWAYS)) {
        if (gVehicleAngleToCamera < 0.2f) {
            RwMatrixTag* atomicMatrix = RwFrameGetLTM(RpAtomicGetFrame(atomic));
            RwMatrixTag* clumpMatrix = RwFrameGetLTM(RpClumpGetFrame(RpAtomicGetClump(atomic)));
            const float dot = GetDotProductWithCameraVector(atomicMatrix, clumpMatrix, atomicFlags);
            if (dot > 0.0f)
                return atomic;
        }
    }
    AtomicDefaultRenderCallBack(atomic);

    return atomic;
}

RpAtomic* CVisibilityPlugins::RenderVehicleHiDetailCB_Boat(RpAtomic* atomic) {
    if (gVehicleDistanceFromCamera >= ms_vehicleLod0Dist)
        return atomic;
    if (gVehicleDistanceFromCamera >= ms_vehicleLod0RenderMultiPassDist)
        SetAtomicFlag(atomic, ATOMIC_DISABLE_REFLECTIONS);
    else
        ClearAtomicFlag(atomic, ATOMIC_DISABLE_REFLECTIONS);
    AtomicDefaultRenderCallBack(atomic);

    return atomic;
}

RpAtomic* CVisibilityPlugins::RenderVehicleLoDetailCB_Boat(RpAtomic* atomic) {
    if (gVehicleDistanceFromCamera < ms_vehicleLod0Dist)
        return atomic;

    SetAtomicFlag(atomic, ATOMIC_DISABLE_REFLECTIONS);
    if (GetClumpAlpha(RpAtomicGetClump(atomic)) == 255)
        AtomicDefaultRenderCallBack(atomic);
    else
        RenderAlphaAtomic(atomic, GetClumpAlpha(RpAtomicGetClump(atomic)));

    return atomic;
}

RpAtomic* CVisibilityPlugins::RenderVehicleReallyLowDetailCB(RpAtomic* atomic) {
    if (gVehicleDistanceFromCamera < ms_vehicleLod0Dist)
        return atomic;

    SetAtomicFlag(atomic, ATOMIC_DISABLE_REFLECTIONS);
    if (GetClumpAlpha(RpAtomicGetClump(atomic)) == 255)
        AtomicDefaultRenderCallBack(atomic);
    else
        RenderAlphaAtomic(atomic, GetClumpAlpha(RpAtomicGetClump(atomic)));

    return atomic;
}

RpAtomic* CVisibilityPlugins::RenderVehicleReallyLowDetailCB_BigVehicle(RpAtomic* atomic) {
    if (gVehicleDistanceFromCamera >= ms_bigVehicleLod0Dist)
        AtomicDefaultRenderCallBack(atomic);

    return atomic;
}

RpAtomic* CVisibilityPlugins::RenderWeaponCB(RpAtomic* atomic) {
    RpClump* pClump = RpAtomicGetClump(atomic);
    CClumpModelInfo* modelInfo = GetClumpModelInfo(pClump);
    const float drawDistanceRadius = TheCamera.m_fLODDistMultiplier * modelInfo->m_fDrawDistance;
    if (GetDistanceSquaredFromCamera(RpClumpGetFrame(pClump)) < drawDistanceRadius * drawDistanceRadius)
        AtomicDefaultRenderCallBack(atomic);

    return atomic;
}

void CVisibilityPlugins::RenderWeaponPedsForPC() {
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,          RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,         RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,            RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,             RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,            RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, RWRSTATE(20));
    auto link = ms_weaponPedsForPC.usedListTail.prev;
    for (; link != &ms_weaponPedsForPC.usedListHead; link = link->prev) {
        CPed* ped = link->data;
        if (ped && ped->m_pWeaponObject) {
            ped->SetupLighting();
            const CWeapon& activeWeapon = ped->GetActiveWeapon();
            RpHAnimHierarchy* pRpAnimHierarchy = GetAnimHierarchyFromSkinClump(ped->m_pRwClump);
            const int32 boneID = activeWeapon.m_nType != WEAPON_PARACHUTE ? BONE_R_HAND : BONE_SPINE1;
            int32 animIDIndex = RpHAnimIDGetIndex(pRpAnimHierarchy, boneID);
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
                int32 animIDIndex = RpHAnimIDGetIndex(pRpAnimHierarchy, BONE_L_HAND);
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

RpAtomic* CVisibilityPlugins::SetAtomicFlagCB(RpAtomic* atomic, void* data) {
    uint16 flag = *reinterpret_cast<uint16*>(&data);
    ATOMICPLG(atomic, m_flags) |= flag;
    return atomic;
}

void CVisibilityPlugins::SetAtomicFlag(RpAtomic* atomic, uint16 flag) {
    ATOMICPLG(atomic, m_flags) |= flag;
}

void CVisibilityPlugins::SetClumpForAllAtomicsFlag(RpClump* clump, uint16 flag) {
    RpClumpForAllAtomics(clump, SetAtomicFlagCB, (void*)flag);
}

void CVisibilityPlugins::SetAtomicId(void* atomic, int16 id) {
    ATOMICPLG(atomic, m_modelId) = id;
}

void CVisibilityPlugins::SetAtomicRenderCallback(RpAtomic* atomic, RpAtomicCallBackRender renderCB) {
    if (!renderCB)
        renderCB = AtomicDefaultRenderCallBack;
    atomic->renderCallBack = renderCB;
    if (!renderCB)
        atomic->renderCallBack = AtomicDefaultRenderCallBack;
}

void CVisibilityPlugins::SetClumpAlpha(RpClump* clump, int32 dwAlpha) {
    CLUMPPLG(clump, m_alpha) = dwAlpha;
}

void CVisibilityPlugins::SetClumpModelInfo(RpClump* clump, CClumpModelInfo* clumpModelInfo) {
    FRAMEPLG(RpClumpGetFrame(clump), m_modelInfo) = clumpModelInfo;
    if (clumpModelInfo->GetModelType() != MODEL_INFO_VEHICLE)
        return;

    CVehicleModelInfo* mi = clumpModelInfo->AsVehicleModelInfoPtr();
    if (mi->IsTrain() || mi->m_nVehicleType == VEHICLE_TYPE_FPLANE)
        CLUMPPLG(clump, m_visibilityCallBack) = VehicleVisibilityCB_BigVehicle;
    else
        CLUMPPLG(clump, m_visibilityCallBack) = VehicleVisibilityCB;
}

void CVisibilityPlugins::SetFrameHierarchyId(RwFrame* frame, int32 id) {
    FRAMEPLG(frame, m_hierarchyId) = id;
}

void CVisibilityPlugins::SetRenderWareCamera(RwCamera* camera) {
    ms_pCamera = camera;
    ms_pCameraPosn = static_cast<CVector*>(RwMatrixGetPos(RwFrameGetMatrix(RwCameraGetFrame(camera))));
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

void CVisibilityPlugins::SetUserValue(RpAtomic* atomic, uint16 value) {
    ATOMICPLG(atomic, m_flags) = value;
}

void CVisibilityPlugins::SetupVehicleVariables(RpClump* clump) {
    if (RwObjectGetType(clump) != rpCLUMP)
        return;

    RwFrame* frame = RpClumpGetFrame(clump);
    RwMatrixTag* transformMatrix = RwFrameGetLTM(frame);
    CVector distance1;
    RwV3dSub(&distance1, &transformMatrix->pos, ms_pCameraPosn);
    gVehicleDistanceFromCamera = distance1.SquaredMagnitude();
    CVector2D distance2;
    RwV2dSub(&distance2, ms_pCameraPosn, RwMatrixGetPos(RwFrameGetMatrix(frame)));
    gVehicleAngleToCamera = atan2(ms_pCameraPosn->z - RwMatrixGetPos(RwFrameGetMatrix(frame))->z, distance2.Magnitude());
}

bool CVisibilityPlugins::VehicleVisibilityCB(RpClump* clump) {
    const float distanceSquared = GetDistanceSquaredFromCamera(RpClumpGetFrame(clump));
    if (distanceSquared <= ms_vehicleLod1Dist)
        return FrustumSphereCB(clump);

    return false;
}

bool CVisibilityPlugins::VehicleVisibilityCB_BigVehicle(RpClump* clump) {
    return FrustumSphereCB(clump);
}
