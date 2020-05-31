/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

int& CVisibilityPlugins::ms_atomicPluginOffset = *(int *)0x8D608C;
CLinkList<CVisibilityPlugins::AlphaObjectInfo>& CVisibilityPlugins::m_alphaEntityList = *(CLinkList<CVisibilityPlugins::AlphaObjectInfo>*)0xC88120;
CLinkList<CVisibilityPlugins::AlphaObjectInfo>& CVisibilityPlugins::m_alphaList = *(CLinkList<CVisibilityPlugins::AlphaObjectInfo>*)0xC88070;
CLinkList<CVisibilityPlugins::AlphaObjectInfo>& CVisibilityPlugins::m_alphaBoatAtomicList = *(CLinkList<CVisibilityPlugins::AlphaObjectInfo>*)0xC880C8;
CLinkList<CVisibilityPlugins::AlphaObjectInfo>& CVisibilityPlugins::m_alphaUnderwaterEntityList = *(CLinkList<CVisibilityPlugins::AlphaObjectInfo>*)0xC88178;
CLinkList<CVisibilityPlugins::AlphaObjectInfo>& CVisibilityPlugins::m_alphaReallyDrawLastList = *(CLinkList<CVisibilityPlugins::AlphaObjectInfo>*)0xC881D0;

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

void CVisibilityPlugins::AtomicConstructor(void* object) {
    plugin::Call<0x732150, void*>(object);
}

// Converted from cdecl void CVisibilityPlugins::AtomicCopyConstructor(void *object,void const*originalObject)	0x732170
void CVisibilityPlugins::AtomicCopyConstructor(void* object, void const* originalObject) {
    plugin::Call<0x732170, void*, void const*>(object, originalObject);
}

// Converted from cdecl void* CVisibilityPlugins::AtomicDestructor(void *object)	0x7321A0
void* CVisibilityPlugins::AtomicDestructor(void* object) {
    return plugin::CallAndReturn<void*, 0x7321A0, void*>(object);
}

// Converted from cdecl int CVisibilityPlugins::CalculateFadingAtomicAlpha(CBaseModelInfo *pBaseModelInfo,CEntity *pEntity,float arg3)	0x732500
int CVisibilityPlugins::CalculateFadingAtomicAlpha(CBaseModelInfo* pBaseModelInfo, CEntity* pEntity, float arg3) {
    return plugin::CallAndReturn<int, 0x732500, CBaseModelInfo*, CEntity*, float>(pBaseModelInfo, pEntity, arg3);
}

// Converted from cdecl void CVisibilityPlugins::ClearAtomicFlag(RpAtomic *pRpAtomic,int flag)	0x732310
void CVisibilityPlugins::ClearAtomicFlag(RpAtomic* pRpAtomic, int flag) {
    plugin::Call<0x732310, RpAtomic*, int>(pRpAtomic, flag);
}

// Converted from cdecl void CVisibilityPlugins::ClearAtomicFlag(RpAtomic *pRpAtomic,ushort flag)	0x732330
void CVisibilityPlugins::ClearAtomicFlag(RpAtomic* pRpAtomic, unsigned short flag) {
    plugin::Call<0x732330, RpAtomic*, unsigned short>(pRpAtomic, flag);
}

// Converted from cdecl void CVisibilityPlugins::ClearClumpForAllAtomicsFlag(RpClump *pRpClump,int flag)	0x732350
void CVisibilityPlugins::ClearClumpForAllAtomicsFlag(RpClump* pRpClump, int flag) {
    plugin::Call<0x732350, RpClump*, int>(pRpClump, flag);
}

// Converted from cdecl void CVisibilityPlugins::ClumpConstructor(void *object)	0x732E10
void CVisibilityPlugins::ClumpConstructor(void* object) {
    plugin::Call<0x732E10, void*>(object);
}

// Converted from cdecl void CVisibilityPlugins::ClumpCopyConstructor(void *object,void const*originalObject)	0x732200
void CVisibilityPlugins::ClumpCopyConstructor(void* object, void const* originalObject) {
    plugin::Call<0x732200, void*, void const*>(object, originalObject);
}

// Converted from cdecl void* CVisibilityPlugins::ClumpDestructor(void *object)	0x732220
void* CVisibilityPlugins::ClumpDestructor(void* object) {
    return plugin::CallAndReturn<void*, 0x732220, void*>(object);
}

// Converted from cdecl int CVisibilityPlugins::DefaultVisibilityCB()	0x732A30
int CVisibilityPlugins::DefaultVisibilityCB() {
    return plugin::CallAndReturn<int, 0x732A30>();
}

// Converted from cdecl void CVisibilityPlugins::FrameConstructor(void *object)	0x7321B0
void CVisibilityPlugins::FrameConstructor(void* object) {
    plugin::Call<0x7321B0, void*>(object);
}

// Converted from cdecl void CVisibilityPlugins::FrameCopyConstructor(void *object,void const*originalObject)	0x7321D0
void CVisibilityPlugins::FrameCopyConstructor(void* object, void const* originalObject) {
    plugin::Call<0x7321D0, void*, void const*>(object, originalObject);
}

// Converted from cdecl void* CVisibilityPlugins::FrameDestructor(void *,int,int)	0x7321F0
void* CVisibilityPlugins::FrameDestructor(void* arg0, int arg1, int arg2) {
    return plugin::CallAndReturn<void*, 0x7321F0, void*, int, int>(arg0, arg1, arg2);
}

// Converted from cdecl bool CVisibilityPlugins::FrustumSphereCB(RpClump *pRpClump)	0x732A40
bool CVisibilityPlugins::FrustumSphereCB(RpClump* pRpClump) {
    return plugin::CallAndReturn<bool, 0x732A40, RpClump*>(pRpClump);
}

// Converted from cdecl short CVisibilityPlugins::GetAtomicId(RpAtomic *pRpAtomic)	0x732370
short CVisibilityPlugins::GetAtomicId(RpAtomic* pRpAtomic) {
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

// Converted from cdecl void CVisibilityPlugins::InitAlphaAtomicList(void)	0x734530
void CVisibilityPlugins::InitAlphaAtomicList() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x734530>();
#else
    m_alphaList.Clear();
#endif
}

// Converted from cdecl void CVisibilityPlugins::InitAlphaEntityList(void)	0x734540
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
// Converted from cdecl void CVisibilityPlugins::Initialise(void)	0x733A20
void CVisibilityPlugins::Initialise() {
    plugin::Call<0x733A20>();
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

// Converted from cdecl bool CVisibilityPlugins::InsertAtomicIntoReallyDrawLastList(RpAtomic *pRpAtomic,float arg2)	0x733E10
bool CVisibilityPlugins::InsertAtomicIntoReallyDrawLastList(RpAtomic* pRpAtomic, float arg2) {
    return plugin::CallAndReturn<bool, 0x733E10, RpAtomic*, float>(pRpAtomic, arg2);
}

// Converted from cdecl bool CVisibilityPlugins::InsertEntityIntoReallyDrawLastList(CEntity *pEntity,float arg2)	0x733E50
bool CVisibilityPlugins::InsertEntityIntoReallyDrawLastList(CEntity* pEntity, float arg2) {
    return plugin::CallAndReturn<bool, 0x733E50, CEntity*, float>(pEntity, arg2);
}

// Converted from cdecl bool CVisibilityPlugins::InsertEntityIntoSortedList(CEntity * pEntity,float distance)	0x734570
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

// Converted from cdecl bool CVisibilityPlugins::IsAtomicVisible(RpAtomic *pRpAtomic)	0x732990
bool CVisibilityPlugins::IsAtomicVisible(RpAtomic* pRpAtomic) {
    return plugin::CallAndReturn<bool, 0x732990, RpAtomic*>(pRpAtomic);
}

// Converted from cdecl bool CVisibilityPlugins::IsClumpVisible(RpClump *pRpClump)	0x732AE0
bool CVisibilityPlugins::IsClumpVisible(RpClump* pRpClump) {
    return plugin::CallAndReturn<bool, 0x732AE0, RpClump*>(pRpClump);
}

// Converted from cdecl bool CVisibilityPlugins::PluginAttach(void)	0x732E30
bool CVisibilityPlugins::PluginAttach() {
    return plugin::CallAndReturn<bool, 0x732E30>();
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

// Converted from cdecl void CVisibilityPlugins::SetAtomicFlag(RpAtomic *pRpAtomic,int flag)	0x7322D0
void CVisibilityPlugins::SetAtomicFlag(RpAtomic* pRpAtomic, int flag) {
    plugin::Call<0x7322D0, RpAtomic*, int>(pRpAtomic, flag);
}

// Converted from cdecl void CVisibilityPlugins::SetAtomicFlag(RpAtomic *pRpAtomic,ushort flag)	0x7322B0
void CVisibilityPlugins::SetAtomicFlag(RpAtomic* pRpAtomic, unsigned short flag) {
    plugin::Call<0x7322B0, RpAtomic*, unsigned short>(pRpAtomic, flag);
}

// Converted from cdecl void CVisibilityPlugins::SetAtomicId(RpAtomic *pRpAtomic,int id)	0x732230
void CVisibilityPlugins::SetAtomicId(RpAtomic* pRpAtomic, int id) {
    plugin::Call<0x732230, RpAtomic*, int>(pRpAtomic, id);
}

// Converted from cdecl void CVisibilityPlugins::SetAtomicRenderCallback(RpAtomic *pRpAtomic, RpAtomic * (*renderCB)(RpAtomic *))	0x7328A0
void CVisibilityPlugins::SetAtomicRenderCallback(RpAtomic *pRpAtomic, RpAtomic * (*renderCB)(RpAtomic *)) {
    plugin::Call<0x7328A0, RpAtomic*, RpAtomic * (*)(RpAtomic *)>(pRpAtomic, renderCB);
}

// Converted from cdecl void CVisibilityPlugins::SetClumpAlpha(RpClump *pRpClump,int dwAlpha)	0x732B00
void CVisibilityPlugins::SetClumpAlpha(RpClump* pRpClump, int dwAlpha) {
    plugin::Call<0x732B00, RpClump*, int>(pRpClump, dwAlpha);
}

// Converted from cdecl void CVisibilityPlugins::SetClumpModelInfo(RpClump *pRpClump,CClumpModelInfo *pClumpModelInfo)	0x733750
void CVisibilityPlugins::SetClumpModelInfo(RpClump* pRpClump, CClumpModelInfo* pClumpModelInfo) {
    plugin::Call<0x733750, RpClump*, CClumpModelInfo*>(pRpClump, pClumpModelInfo);
}

// Converted from cdecl void CVisibilityPlugins::SetFrameHierarchyId(RwFrame *pRwFrame,int id)	0x732A00
void CVisibilityPlugins::SetFrameHierarchyId(RwFrame* pRwFrame, int id) {
    plugin::Call<0x732A00, RwFrame*, int>(pRwFrame, id);
}

// Converted from cdecl void CVisibilityPlugins::SetRenderWareCamera(RwCamera *pRwCamera)	0x7328C0
void CVisibilityPlugins::SetRenderWareCamera(RwCamera* pRwCamera) {
    plugin::Call<0x7328C0, RwCamera*>(pRwCamera);
}

// Converted from cdecl void CVisibilityPlugins::SetUserValue(RpAtomic *pRpAtomic,ushort value)	0x732380
void CVisibilityPlugins::SetUserValue(RpAtomic* pRpAtomic, unsigned short value) {
    plugin::Call<0x732380, RpAtomic*, unsigned short>(pRpAtomic, value);
}

// Converted from cdecl void CVisibilityPlugins::SetupVehicleVariables(RpClump *pRpClump)	0x733160
void CVisibilityPlugins::SetupVehicleVariables(RpClump* pRpClump) {
    plugin::Call<0x733160, RpClump*>(pRpClump);
}

// Converted from cdecl void CVisibilityPlugins::Shutdown(void)	0x732EB0
void CVisibilityPlugins::Shutdown() {
    plugin::Call<0x732EB0>();
}

// Converted from cdecl bool CVisibilityPlugins::VehicleVisibilityCB(RpClump *pRpClump)	0x7336F0
bool CVisibilityPlugins::VehicleVisibilityCB(RpClump* pRpClump) {
    return plugin::CallAndReturn<bool, 0x7336F0, RpClump*>(pRpClump);
}

// Converted from cdecl bool CVisibilityPlugins::VehicleVisibilityCB_BigVehicle(RpClump *pRpClump)	0x732AB0
bool CVisibilityPlugins::VehicleVisibilityCB_BigVehicle(RpClump* pRpClump) {
    return plugin::CallAndReturn<bool, 0x732AB0, RpClump*>(pRpClump);
}
