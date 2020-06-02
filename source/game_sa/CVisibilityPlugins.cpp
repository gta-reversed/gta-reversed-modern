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

void CVisibilityPlugins::InjectHooks() {
   HookInstall(0x734530, &CVisibilityPlugins::InitAlphaAtomicList, 7);
   HookInstall(0x734540, &CVisibilityPlugins::InitAlphaEntityList, 7);
   HookInstall(0x733DD0, &CVisibilityPlugins::InsertEntityIntoEntityList, 5);
   HookInstall(0x733D90, &CVisibilityPlugins::InsertEntityIntoUnderwaterEntities, 5);
   HookInstall(0x734570, &CVisibilityPlugins::InsertEntityIntoSortedList, 5);
   HookInstall(0x732B40, &CVisibilityPlugins::RenderEntity, 5);
   HookInstall(0x733E90, &CVisibilityPlugins::RenderAlphaAtomics, 7);
   HookInstall(0x733EC0, &CVisibilityPlugins::RenderBoatAlphaAtomics, 7);
   HookInstall(0x733F10, &CVisibilityPlugins::RenderFadingEntities, 7);
   HookInstall(0x7337D0, &CVisibilityPlugins::RenderFadingUnderwaterEntities, 7);
   HookInstall(0x733800, &CVisibilityPlugins::RenderReallyDrawLastObjects, 7);
}


void CVisibilityPlugins::Initialise() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x733A20>();
#else
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
#endif
}

void CVisibilityPlugins::Shutdown() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x732EB0>();
#else
    m_alphaList.Shutdown();
    m_alphaBoatAtomicList.Shutdown();
    m_alphaEntityList.Shutdown();
    m_alphaUnderwaterEntityList.Shutdown();
    m_alphaReallyDrawLastList.Shutdown();
    ms_weaponPedsForPC.Shutdown();
#endif
}

void CVisibilityPlugins::InitAlphaAtomicList() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x734530>();
#else
    m_alphaList.Clear();
#endif
}

void CVisibilityPlugins::InitAlphaEntityList() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x734540>();

#else
    m_alphaEntityList.Clear();
    m_alphaBoatAtomicList.Clear();
    m_alphaUnderwaterEntityList.Clear();
    m_alphaReallyDrawLastList.Clear();
#endif
}

bool CVisibilityPlugins::InsertEntityIntoEntityList(CEntity* entity, float distance, void* callback)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<bool, 0x733DD0, CEntity*, float, void*>(entity, distance, callback);
#else
    AlphaObjectInfo info;
    info.m_entity = entity;
    info.m_pCallback = callback;
    info.m_distance = distance;
    return m_alphaEntityList.InsertSorted(info);
#endif
}

bool CVisibilityPlugins::InsertEntityIntoUnderwaterEntities(CEntity* entity, float distance)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<bool, 0x733D90, CEntity*, float>(entity, distance);
#else
    AlphaObjectInfo entityAlphaObjectInfo;
    entityAlphaObjectInfo.m_distance = distance;
    entityAlphaObjectInfo.m_entity = entity;
    entityAlphaObjectInfo.m_pCallback = CVisibilityPlugins::RenderEntity;
    return m_alphaUnderwaterEntityList.InsertSorted(entityAlphaObjectInfo);
#endif
}

bool CVisibilityPlugins::InsertAtomicIntoReallyDrawLastList(RpAtomic* pRpAtomic, float distance) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<bool, 0x733E10, RpAtomic*, float>(pRpAtomic, distance);
#else
    AlphaObjectInfo objectInfo;
    objectInfo.m_distance = distance;
    objectInfo.m_atomic = pRpAtomic;
    objectInfo.m_pCallback = gtaDefaultAtomicRenderCallback;
    m_alphaReallyDrawLastList.InsertSorted(objectInfo);
#endif
}

bool CVisibilityPlugins::InsertEntityIntoReallyDrawLastList(CEntity* pEntity, float distance) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<bool, 0x733E50, CEntity*, float>(pEntity, distance);
#else
    AlphaObjectInfo objectInfo; 
    objectInfo.m_distance = distance;
    objectInfo.m_entity = pEntity;
    objectInfo.m_pCallback = CVisibilityPlugins::RenderEntity;
    m_alphaReallyDrawLastList.InsertSorted(objectInfo);
#endif
}

bool CVisibilityPlugins::InsertEntityIntoSortedList(CEntity* entity, float distance) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<bool, 0x734570, CEntity*, float>(entity, distance);
#else
    if (entity->m_nModelIndex == MI_GRASSHOUSE && InsertEntityIntoReallyDrawLastList(entity, distance))
        return true;
    if (entity->m_bUnderwater)
        return InsertEntityIntoUnderwaterEntities(entity, distance);
    return InsertEntityIntoEntityList(entity, distance, CVisibilityPlugins::RenderEntity);
#endif
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
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<bool, 0x732E30>();
#else
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
#endif
}
static RpAtomic* gtaDefaultAtomicRenderCallback(RpAtomic* atomic)
{
    return AtomicDefaultRenderCallBack(atomic);
}

void* CVisibilityPlugins::AtomicConstructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallAndReturn<void*, 0x732150, void*, RwInt32, RwInt32>(object, offsetInObject, sizeInObject);
#else
    SetAtomicId(object, 0xFFFF);
    SetAtomicFlag(object, 0);
#endif
}

void* CVisibilityPlugins::AtomicCopyConstructor(void* dstObject, const void* srcObject, RwInt32 offsetInObject, RwInt32 sizeInObject)
 {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallAndReturn<void*, 0x732170, void*, const void*, RwInt32, RwInt32>(dstObject, srcObject, offsetInObject, sizeInObject);

#else
    ATOMICPLG(dstObject, m_id) = ATOMICPLGCONST(srcObject, m_id);
    ATOMICPLG(dstObject, m_flags) = ATOMICPLGCONST(srcObject, m_flags);
    return dstObject;
#endif
}

void* CVisibilityPlugins::AtomicDestructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<void*, 0x7321A0, void*, RwInt32, RwInt32>(object, offsetInObject, sizeInObject);
#else
    return object;
#endif
}

int CVisibilityPlugins::CalculateFadingAtomicAlpha(CBaseModelInfo* modelInfo, CEntity* entity, float distance) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<int, 0x732500, CBaseModelInfo*, CEntity*, float>(modelInfo, entity, distance);
#else
    float fFadingDistance = MAX_FADING_DISTANCE;
    float fDrawDistanceRadius = modelInfo->m_pColModel->m_boundSphere.m_fRadius + CRenderer::ms_fFarClipPlane;
    fDrawDistanceRadius = std::min(fDrawDistanceRadius, TheCamera.m_fLODDistMultiplier * modelInfo->m_fDrawDistance);
    if (!entity->m_pLod) {
        const float fDrawDistance = std::min(modelInfo->m_fDrawDistance, fDrawDistanceRadius);
        if (fDrawDistance > MAX_LOWLOD_DISTANCE)
            fFadingDistance = fDrawDistance / 15.0f + 10.0f;
        if (entity->m_bIsBIGBuilding)
            fDrawDistanceRadius *= CRenderer::ms_lowLodDistScale;
    }
    float fFade = std::min((fDrawDistanceRadius + MAX_FADING_DISTANCE - distance) / fFadingDistance, 1.0f);
    return modelInfo->m_nAlpha * fFade;
#endif
}

void CVisibilityPlugins::ClearAtomicFlag(RpAtomic* pRpAtomic, std::uint16_t flag) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x732310, RpAtomic*, int>(pRpAtomic, flag);
#else
    ATOMICPLG(pRpAtomic, m_flags) &= ~flag;
#endif
}

RpAtomic* CVisibilityPlugins::ClearAtomicFlag(RpAtomic* atomic, void* data) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x732330, RpAtomic*, unsigned short>(pRpAtomic, flag);
#else
    std::uint16_t flag = reinterpret_cast<std::uint16_t>(data);
    ATOMICPLG(atomic, m_flags) &= ~flag;
    return atomic;
#endif
}

void CVisibilityPlugins::ClearClumpForAllAtomicsFlag(RpClump* pRpClump, std::uint16_t flag) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x732350, RpClump*, int>(pRpClump, flag);
#else
    RpClumpForAllAtomics(pRpClump, CVisibilityPlugins::ClearAtomicFlag, (void*)flag);
#endif
}

void* CVisibilityPlugins::ClumpConstructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallAndReturn<void*, 0x732E10, void*, RwInt32, RwInt32>(object, offsetInObject, sizeInObject);
#else
    CLUMPPLG(object, m_visibilityCallBack) = CVisibilityPlugins::DefaultVisibilityCB;
    CLUMPPLG(object, m_alpha) = 255;
    return object;
#endif
}

void* CVisibilityPlugins::ClumpCopyConstructor(void* dstObject, const void* srcObject, RwInt32 offsetInObject, RwInt32 sizeInObject) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallAndReturn<void*, 0x732200, void*, void const*>(dstObject, srcObject, offsetInObject, sizeInObject);
#else
    CLUMPPLG(dstObject, m_visibilityCallBack) = CLUMPPLGCONST(srcObject, m_visibilityCallBack);
    return dstObject;
#endif
}

void* CVisibilityPlugins::ClumpDestructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<void*, 0x732220, void*, RwInt32, RwInt32>(object, offsetInObject, sizeInObject);
#else
    return object;
#endif
}

int CVisibilityPlugins::DefaultVisibilityCB() {
    return 1;
}

void* CVisibilityPlugins::FrameConstructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallAndReturn<void*, 0x7321B0, void*, RwInt32, RwInt32>(object, offsetInObject, sizeInObject);
#else
    FRAMEPLG(object, m_hierarchyId) = 0;
    return object;
#endif
}

void* CVisibilityPlugins::FrameCopyConstructor(void* dstObject, const void* srcObject, RwInt32 offsetInObject, RwInt32 sizeInObject) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallAndReturn<void*, 0x7321D0, void*, const void*, RwInt32, RwInt32>(dstObject, srcObject, offsetInObject, sizeInObject);
#else
    FRAMEPLG(dstObject, m_hierarchyId) = FRAMEPLGCONST(srcObject, m_hierarchyId);
    return dstObject;
#endif
}

void* CVisibilityPlugins::FrameDestructor(void* object, RwInt32 offsetInObject, RwInt32 sizeInObject) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<void*, 0x7321F0, void*, RwInt32, RwInt32>(object, offsetInObject, sizeInObject);
#else
    return object;
#endif
}

bool CVisibilityPlugins::FrustumSphereCB(RpClump* pRpClump) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<bool, 0x732A40, RpClump*>(pRpClump);
#else
    RwSphere sphere;
    RwFrame* frame = RpClumpGetFrame(pRpClump);
    CBaseModelInfo* modelInfo = FRAMEPLG(frame, m_modelInfo); 
    sphere.radius = modelInfo->GetBoundingRadius();
    sphere.center = modelInfo->GetBoundingCenter();
    RwMatrixTag* transformMatrix = RwFrameGetLTM(frame);
    RwV3dTransformPoints(&sphere.center, &sphere.center, 1, transformMatrix);
    return RwCameraFrustumTestSphere(ms_pCamera, &sphere) != rwSPHEREOUTSIDE;
#endif
}

// Converted from cdecl short CVisibilityPlugins::GetAtomicId(RpAtomic *pRpAtomic)	0x732370
std::uint16_t CVisibilityPlugins::GetAtomicId(RpAtomic* pRpAtomic) {
    return plugin::CallAndReturn<short, 0x732370, RpAtomic*>(pRpAtomic);


}

// Converted from cdecl CAtomicModelInfo* CVisibilityPlugins::GetAtomicModelInfo(RpAtomic *pRpAtomic)	0x732260
CAtomicModelInfo* CVisibilityPlugins::GetAtomicModelInfo(RpAtomic* pRpAtomic) {
    return plugin::CallAndReturn<CAtomicModelInfo*, 0x732260, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl int CVisibilityPlugins::GetClumpAlpha(RpClump *pRpClump)	0x732B20
int CVisibilityPlugins::GetClumpAlpha(RpClump* pRpClump) {
    return plugin::CallAndReturn<int, 0x732B20, RpClump*>(pRpClump);
}

// Converted from cdecl CClumpModelInfo* CVisibilityPlugins::GetClumpModelInfo(RpClump *pRpClump)	0x732AC0
CClumpModelInfo* CVisibilityPlugins::GetClumpModelInfo(RpClump* pRpClump) {
    return plugin::CallAndReturn<CClumpModelInfo*, 0x732AC0, RpClump*>(pRpClump);
}

// Converted from cdecl float CVisibilityPlugins::GetDistanceSquaredFromCamera(RwFrame *pRwFrame)	0x732C80
float CVisibilityPlugins::GetDistanceSquaredFromCamera(RwFrame* pRwFrame) {
    return plugin::CallAndReturn<float, 0x732C80, RwFrame*>(pRwFrame);
}

// Converted from cdecl float CVisibilityPlugins::GetDistanceSquaredFromCamera(RwV3d *pRwV3d)	0x732CC0
float CVisibilityPlugins::GetDistanceSquaredFromCamera(RwV3d* pRwV3d) {
    return plugin::CallAndReturn<float, 0x732CC0, RwV3d*>(pRwV3d);
}

// Converted from cdecl float CVisibilityPlugins::GetDotProductWithCameraVector(RwMatrixTag *atomicMat, RwMatrixTag *rootMat, unsigned int flags)	0x7326D0
float CVisibilityPlugins::GetDotProductWithCameraVector(RwMatrixTag* atomicMat, RwMatrixTag* rootMat, unsigned int flags) {
    return plugin::CallAndReturn<float, 0x7326D0, RwMatrixTag*, RwMatrixTag*, unsigned int>(atomicMat, rootMat, flags);
}

// Converted from cdecl int CVisibilityPlugins::GetFrameHierarchyId(RwFrame *pRwFrame)	0x732A20
int CVisibilityPlugins::GetFrameHierarchyId(RwFrame* pRwFrame) {
    return plugin::CallAndReturn<int, 0x732A20, RwFrame*>(pRwFrame);
}

// Converted from cdecl short CVisibilityPlugins::GetModelInfoIndex(RpAtomic *pRpAtomic)	0x732250
short CVisibilityPlugins::GetModelInfoIndex(RpAtomic* pRpAtomic) {
    return plugin::CallAndReturn<short, 0x732250, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl short CVisibilityPlugins::GetUserValue(RpAtomic *pRpAtomic)	0x7323A0
short CVisibilityPlugins::GetUserValue(RpAtomic* pRpAtomic) {
    return plugin::CallAndReturn<short, 0x7323A0, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl bool CVisibilityPlugins::IsAtomicVisible(RpAtomic *pRpAtomic)	0x732990
bool CVisibilityPlugins::IsAtomicVisible(RpAtomic* pRpAtomic) {
    return plugin::CallAndReturn<bool, 0x732990, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl bool CVisibilityPlugins::IsClumpVisible(RpClump *pRpClump)	0x732AE0
bool CVisibilityPlugins::IsClumpVisible(RpClump* pRpClump) {
    return plugin::CallAndReturn<bool, 0x732AE0, RpClump*>(pRpClump);
}

// Converted from cdecl void CVisibilityPlugins::RenderAlphaAtomic(RpAtomic *pRpAtomic, int dwAlpha)	0x732480
void CVisibilityPlugins::RenderAlphaAtomic(RpAtomic* pRpAtomic, int dwAlpha) {
    plugin::Call<0x732480, RpAtomic*, int>(pRpAtomic, dwAlpha);
}

// Converted from cdecl void CVisibilityPlugins::RenderAlphaAtomics(void)	0x733E90
void CVisibilityPlugins::RenderAlphaAtomics() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x733E90>();
#else
    RenderOrderedList(m_alphaList);
#endif
}

// Converted from cdecl void CVisibilityPlugins::RenderAtomicWithAlphaCB(RpAtomic *pRpAtomic,void *pData)	0x732660
void CVisibilityPlugins::RenderAtomicWithAlphaCB(RpAtomic* pRpAtomic, void* pData) {
    plugin::Call<0x732660, RpAtomic*, void*>(pRpAtomic, pData);
}

void CVisibilityPlugins::RenderBoatAlphaAtomics() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x733EC0>();
#else
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)rwCULLMODECULLNONE);
    RenderOrderedList(m_alphaBoatAtomicList);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)rwCULLMODECULLBACK);
#endif
}

void CVisibilityPlugins::RenderEntity(CEntity* entity, int unused, float distance) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x732B40, CEntity*, int, float>(entity, unused, distance);
#else
    if (!entity->m_pRwObject)
        return;
    CBaseModelInfo* pModelInfo = CModelInfo::ms_modelInfoPtrs[entity->m_nModelIndex];
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
        float alpha = CalculateFadingAtomicAlpha(pModelInfo, entity, distance);
        entity->m_bImBeingRendered = true;
        if (!entity->m_bBackfaceCulled)
            RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)rwCULLMODECULLNONE);
        bool bLightingSetup = entity->SetupLighting();
        if (entity->m_pRwObject->type == 1)
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
#endif
}

// Converted from cdecl void CVisibilityPlugins::RenderFadingAtomic(CBaseModelInfo *pBaseModelInfo,RpAtomic *pRpAtomic,int dwAlpha)	0x732610
void CVisibilityPlugins::RenderFadingAtomic(CBaseModelInfo* pBaseModelInfo, RpAtomic* pRpAtomic, int dwAlpha) {
    plugin::Call<0x732610, CBaseModelInfo*, RpAtomic*, int>(pBaseModelInfo, pRpAtomic, dwAlpha);
}

// Converted from cdecl void CVisibilityPlugins::RenderFadingClump(CBaseModelInfo *pBaseModelInfo,RpClump *pRpClump,int dwAlpha)	0x732680
void CVisibilityPlugins::RenderFadingClump(CBaseModelInfo* pBaseModelInfo, RpClump* pRpClump, int dwAlpha) {
    plugin::Call<0x732680, CBaseModelInfo*, RpClump*, int>(pBaseModelInfo, pRpClump, dwAlpha);
}

// Converted from cdecl void CVisibilityPlugins::RenderFadingClumpCB(RpAtomic *pRpAtomic)	0x733630
void CVisibilityPlugins::RenderFadingClumpCB(RpAtomic* pRpAtomic) {
    plugin::Call<0x733630, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl void CVisibilityPlugins::RenderFadingEntities(void)	0x733F10
void CVisibilityPlugins::RenderFadingEntities() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x733F10>();
#else
    RenderOrderedList(m_alphaEntityList);
    RenderBoatAlphaAtomics();
#endif
}
// Converted from cdecl void CVisibilityPlugins::RenderFadingUnderwaterEntities(void)	0x7337D0
void CVisibilityPlugins::RenderFadingUnderwaterEntities() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x7337D0>();
#else
    RenderOrderedList(m_alphaUnderwaterEntityList);
#endif
}

// Converted from cdecl void CVisibilityPlugins::RenderHeliRotorAlphaCB(RpAtomic *pRpAtomic)	0x7340B0
void CVisibilityPlugins::RenderHeliRotorAlphaCB(RpAtomic* pRpAtomic) {
    plugin::Call<0x7340B0, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl void CVisibilityPlugins::RenderHeliTailRotorAlphaCB(RpAtomic *pRpAtomic)	0x734170
void CVisibilityPlugins::RenderHeliTailRotorAlphaCB(RpAtomic* pRpAtomic) {
    plugin::Call<0x734170, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl void CVisibilityPlugins::RenderObjNormalAtomic(RpAtomic *pRpAtomic)	0x7323E0
void CVisibilityPlugins::RenderObjNormalAtomic(RpAtomic* pRpAtomic) {
    plugin::Call<0x7323E0, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl void CVisibilityPlugins::RenderOrderedList(CLinkList<CVisibilityPlugins::AlphaObjectInfo> &AlphaObjectInfoList)	0x7337A0
void CVisibilityPlugins::RenderOrderedList(CLinkList<CVisibilityPlugins::AlphaObjectInfo>& AlphaObjectInfoList) {
    plugin::Call <0x7337A0, CLinkList<CVisibilityPlugins::AlphaObjectInfo>&>(AlphaObjectInfoList);
}

// Converted from cdecl void CVisibilityPlugins::RenderPedCB(RpAtomic *pRpAtomic)	0x7335B0
void CVisibilityPlugins::RenderPedCB(RpAtomic* pRpAtomic) {
    plugin::Call<0x7335B0, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl void CVisibilityPlugins::RenderPlayerCB(RpAtomic *pRpAtomic)	0x732870
void CVisibilityPlugins::RenderPlayerCB(RpAtomic* pRpAtomic) {
    plugin::Call<0x732870, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl void CVisibilityPlugins::RenderReallyDrawLastObjects(void)	0x733800
void CVisibilityPlugins::RenderReallyDrawLastObjects() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x733800>();
#else
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
#endif
}

// Converted from cdecl void CVisibilityPlugins::RenderTrainHiDetailAlphaCB(RpAtomic *pRpAtomic)	0x734240
void CVisibilityPlugins::RenderTrainHiDetailAlphaCB(RpAtomic* pRpAtomic) {
    plugin::Call<0x734240, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl void CVisibilityPlugins::RenderTrainHiDetailCB(RpAtomic *pRpAtomic)	0x733330
void CVisibilityPlugins::RenderTrainHiDetailCB(RpAtomic* pRpAtomic) {
    plugin::Call<0x733330, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl void CVisibilityPlugins::RenderVehicleHiDetailAlphaCB(RpAtomic *pRpAtomic)	0x733F80
void CVisibilityPlugins::RenderVehicleHiDetailAlphaCB(RpAtomic* pRpAtomic) {
    plugin::Call<0x733F80, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl void CVisibilityPlugins::RenderVehicleHiDetailAlphaCB_BigVehicle(RpAtomic *pRpAtomic)	0x734370
void CVisibilityPlugins::RenderVehicleHiDetailAlphaCB_BigVehicle(RpAtomic* pRpAtomic) {
    plugin::Call<0x734370, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl void CVisibilityPlugins::RenderVehicleHiDetailAlphaCB_Boat(RpAtomic *pRpAtomic)	0x7344A0
void CVisibilityPlugins::RenderVehicleHiDetailAlphaCB_Boat(RpAtomic* pRpAtomic) {
    plugin::Call<0x7344A0, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl void CVisibilityPlugins::RenderVehicleHiDetailCB(RpAtomic *pRpAtomic)	0x733240
void CVisibilityPlugins::RenderVehicleHiDetailCB(RpAtomic* pRpAtomic) {
    plugin::Call<0x733240, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl void CVisibilityPlugins::RenderVehicleHiDetailCB_BigVehicle(RpAtomic *pRpAtomic)	0x733420
void CVisibilityPlugins::RenderVehicleHiDetailCB_BigVehicle(RpAtomic* pRpAtomic) {
    plugin::Call<0x733420, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl void CVisibilityPlugins::RenderVehicleHiDetailCB_Boat(RpAtomic *pRpAtomic)	0x733550
void CVisibilityPlugins::RenderVehicleHiDetailCB_Boat(RpAtomic* pRpAtomic) {
    plugin::Call<0x733550, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl void CVisibilityPlugins::RenderVehicleLoDetailCB_Boat(RpAtomic *pRpAtomic)	0x7334F0
void CVisibilityPlugins::RenderVehicleLoDetailCB_Boat(RpAtomic* pRpAtomic) {
    plugin::Call<0x7334F0, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl void CVisibilityPlugins::RenderVehicleReallyLowDetailCB(RpAtomic *pRpAtomic)	0x7331E0
void CVisibilityPlugins::RenderVehicleReallyLowDetailCB(RpAtomic* pRpAtomic) {
    plugin::Call<0x7331E0, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl void CVisibilityPlugins::RenderVehicleReallyLowDetailCB_BigVehicle(RpAtomic *pRpAtomic)	0x732820
void CVisibilityPlugins::RenderVehicleReallyLowDetailCB_BigVehicle(RpAtomic* pRpAtomic) {
    plugin::Call<0x732820, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl void CVisibilityPlugins::RenderWeaponCB(RpAtomic *pRpAtomic)	0x733670
void CVisibilityPlugins::RenderWeaponCB(RpAtomic* pRpAtomic) {
    plugin::Call<0x733670, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl void CVisibilityPlugins::RenderWeaponPedsForPC(void)	0x732F30
void CVisibilityPlugins::RenderWeaponPedsForPC() {
    plugin::Call<0x732F30>();
}

void CVisibilityPlugins::SetAtomicFlag(void* pRpAtomic, std::uint16_t flag) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x7322D0, void*, int>(pRpAtomic, flag);
#else
    ATOMICPLG(pRpAtomic, m_flags) = flag;
#endif
}

void CVisibilityPlugins::SetAtomicFlag(void* pRpAtomic, std::uint16_t flag) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x7322B0, void*, unsigned short>(pRpAtomic, flag);
#else
    ATOMICPLG(pRpAtomic, m_flags) = flag;
#endif
}

void CVisibilityPlugins::SetAtomicId(void* pRpAtomic, std::uint16_t id) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x732230, void*, std::uint16_t>(pRpAtomic, id);
#else
    ATOMICPLG(pRpAtomic, m_id) = id;
#endif
}

void CVisibilityPlugins::SetAtomicRenderCallback(RpAtomic *atomic, RpAtomic * (*renderCB)(RpAtomic *)) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x7328A0, RpAtomic*, RpAtomic * (*)(RpAtomic *)>(pRpAtomic, renderCB);
#else
    if (!renderCB)
        renderCB = AtomicDefaultRenderCallBack;
    atomic->renderCallBack = renderCB;
    if (!renderCB)
        atomic->renderCallBack = AtomicDefaultRenderCallBack;
#endif
}

void CVisibilityPlugins::SetClumpAlpha(RpClump* pRpClump, int dwAlpha) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x732B00, RpClump*, int>(pRpClump, dwAlpha);
#else
    CLUMPPLG(pRpClump, m_alpha) = dwAlpha;
#endif
}

void CVisibilityPlugins::SetClumpModelInfo(RpClump* pRpClump, CClumpModelInfo* pClumpModelInfo) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x733750, RpClump*, CClumpModelInfo*>(pRpClump, pClumpModelInfo);
#else
    FRAMEPLG(RpClumpGetFrame(pRpClump), m_modelInfo) = pClumpModelInfo;
    if (pClumpModelInfo->GetModelType() != MODEL_INFO_VEHICLE)
        return;
    auto pVehicleModelInfo = reinterpret_cast<CVehicleModelInfo*>(pClumpModelInfo);
    if (pVehicleModelInfo->m_nVehicleType == VEHICLE_TRAIN || pVehicleModelInfo->m_nVehicleType == VEHICLE_FPLANE)
        CLUMPPLG(pRpClump, m_visibilityCallBack) = VehicleVisibilityCB_BigVehicle;
    else
        CLUMPPLG(pRpClump, m_visibilityCallBack) = VehicleVisibilityCB;
#endif
}

void CVisibilityPlugins::SetFrameHierarchyId(RwFrame* pRwFrame, std::int32_t id) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x732A00, RwFrame*, std::int32_t>(pRwFrame, id);
#else
    FRAMEPLG(pRwFrame, m_hierarchyId) = id;
#endif
}

void CVisibilityPlugins::SetRenderWareCamera(RwCamera* pRwCamera) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x7328C0, RwCamera*>(pRwCamera);
#else
    ms_pCamera = pRwCamera;
    ms_pCameraPosn = RwMatrixGetPos(RwFrameGetMatrix(RwCameraGetFrame(pRwCamera)));
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
#endif
}

void CVisibilityPlugins::SetUserValue(RpAtomic* pRpAtomic, unsigned short value) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x732380, RpAtomic*, unsigned short>(pRpAtomic, value);
#else
    ATOMICPLG(pRpAtomic, m_flags) = value;
#endif
}

// Converted from cdecl void CVisibilityPlugins::SetupVehicleVariables(RpClump *pRpClump)	0x733160
void CVisibilityPlugins::SetupVehicleVariables(RpClump* pRpClump) {
    plugin::Call<0x733160, RpClump*>(pRpClump);
}

// Converted from cdecl bool CVisibilityPlugins::VehicleVisibilityCB(RpClump *pRpClump)	0x7336F0
bool CVisibilityPlugins::VehicleVisibilityCB(RpClump* pRpClump) {
    return plugin::CallAndReturn<bool, 0x7336F0, RpClump*>(pRpClump);
}

// Converted from cdecl bool CVisibilityPlugins::VehicleVisibilityCB_BigVehicle(RpClump *pRpClump)	0x732AB0
bool CVisibilityPlugins::VehicleVisibilityCB_BigVehicle(RpClump* pRpClump) {
    return plugin::CallAndReturn<bool, 0x732AB0, RpClump*>(pRpClump);
}
