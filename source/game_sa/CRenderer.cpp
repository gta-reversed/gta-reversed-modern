/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

unsigned int MAX_INVISIBLE_ENTITY_PTRS = 150;
unsigned int MAX_VISIBLE_ENTITY_PTRS = 1000;
unsigned int MAX_VISIBLE_LOD_PTRS = 1000;
unsigned int MAX_VISIBLE_SUPERLOD_PTRS = 50;
bool& CRenderer::ms_bRenderTunnels = *(bool*)0xB745C0;
bool& CRenderer::ms_bRenderOutsideTunnels = *(bool*)0xB745C1;
tRenderListEntry*& CRenderer::ms_pLodDontRenderList = *(tRenderListEntry * *)0xB745CC;
tRenderListEntry*& CRenderer::ms_pLodRenderList = *(tRenderListEntry * *)0xB745D0;
CVehicle*& CRenderer::m_pFirstPersonVehicle = *(CVehicle * *)0xB745D4;
CEntity** CRenderer::ms_aInVisibleEntityPtrs = (CEntity * *)0xB745D8;
CEntity** CRenderer::ms_aVisibleSuperLodPtrs = (CEntity * *)0xB74830;
CEntity** CRenderer::ms_aVisibleLodPtrs = (CEntity * *)0xB748F8;
CEntity** CRenderer::ms_aVisibleEntityPtrs = (CEntity * *)0xB75898;
unsigned int& CRenderer::ms_nNoOfVisibleSuperLods = *(unsigned int*)0xB76838;
unsigned int& CRenderer::ms_nNoOfInVisibleEntities = *(unsigned int*)0xB7683C;
unsigned int& CRenderer::ms_nNoOfVisibleLods = *(unsigned int*)0xB76840;
unsigned int& CRenderer::ms_nNoOfVisibleEntities = *(unsigned int*)0xB76844;
float& CRenderer::ms_fFarClipPlane = *(float*)0xB76848;
float& CRenderer::ms_fCameraHeading = *(float*)0xB7684C;
unsigned char& CRenderer::m_loadingPriority = *(unsigned char*)0xB76850;
bool& CRenderer::ms_bInTheSky = *(bool*)0xB76851;
CVector& CRenderer::ms_vecCameraPosition = *(CVector*)0xB76870;
float& CRenderer::ms_lodDistScale = *(float*)0x8CD800;
float& CRenderer::ms_lowLodDistScale = *(float*)0x8CD804;
unsigned int& gnRendererModelRequestFlags = *(unsigned int*)0xB745C4;
CEntity**& gpOutEntitiesForGetObjectsInFrustum = *(CEntity * **)0xB76854;

void CRenderer::InjectHooks()
{
    HookInstall(0x5531E0, &CRenderer::RenderFadingInEntities, 7);
    HookInstall(0x553220, &CRenderer::RenderFadingInUnderwaterEntities, 7);
    HookInstall(0x5534B0, &CRenderer::AddEntityToRenderList, 7);
    HookInstall(0x5536F0, &CRenderer::ResetLodRenderLists, 7);
    HookInstall(0x553710, &CRenderer::AddToLodRenderList, 7);
    HookInstall(0x554230, &CRenderer::SetupEntityVisibility, 7);
    HookInstall(0x553F60, &CRenderer::SetupMapEntityVisibility, 7);
    HookInstall(0x554650, &CRenderer::SetupBigBuildingVisibility, 7);
    HookInstall(0x553540, &CRenderer::SetupScanLists, 7);
    HookInstall(0x554840, &CRenderer::ScanSectorList, 7);
}

// Converted from cdecl void CRenderer::Init(void) 0x5531C0
void CRenderer::Init() {
    plugin::Call<0x5531C0>();
}

// Converted from cdecl void CRenderer::Shutdown(void) 0x5531D0
void CRenderer::Shutdown() {
    plugin::Call<0x5531D0>();
}

// Converted from cdecl void CRenderer::RenderFadingInEntities(void) 0x5531E0
void CRenderer::RenderFadingInEntities() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x5531E0>();
#else
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)rwCULLMODECULLBACK);
    DeActivateDirectional();
    SetAmbientColours();
    CVisibilityPlugins::RenderFadingEntities();
#endif
}

// Converted from cdecl void CRenderer::RenderFadingInUnderwaterEntities(void) 0x553220
void CRenderer::RenderFadingInUnderwaterEntities() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x553220>();
#else
    DeActivateDirectional();
    SetAmbientColours();
    CVisibilityPlugins::RenderFadingUnderwaterEntities();
#endif
}

// Converted from cdecl void CRenderer::RenderOneRoad(CEntity *entity) 0x553230
void CRenderer::RenderOneRoad(CEntity* entity) {
    plugin::Call<0x553230, CEntity*>(entity);
}

// Converted from cdecl void CRenderer::RenderOneNonRoad(CEntity *entity) 0x553260
void CRenderer::RenderOneNonRoad(CEntity* entity) {
    plugin::Call<0x553260, CEntity*>(entity);
}

// Converted from cdecl void CRenderer::RemoveVehiclePedLights(CPhysical *entity) 0x553390
void CRenderer::RemoveVehiclePedLights(CPhysical* entity) {
    plugin::Call<0x553390, CPhysical*>(entity);
}

void CRenderer::AddEntityToRenderList(CEntity* pEntity, float fDistance)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x05534B0, CEntity*, float>(pEntity, fDistance);
#else
    CBaseModelInfo* pBaseModelInfo = CModelInfo::ms_modelInfoPtrs[pEntity->m_nModelIndex];
    pBaseModelInfo->bHasBeenPreRendered = false;

    if (!pEntity->m_bDistanceFade)
    {
        if (pEntity->m_bDrawLast && CVisibilityPlugins::InsertEntityIntoSortedList(pEntity, fDistance))
        {
            pEntity->m_bDistanceFade = false;
            return;
        }
    }
    else
    {
        if (CVisibilityPlugins::InsertEntityIntoSortedList(pEntity, fDistance))
        {
            return;
        }
    }

    if (pEntity->m_nNumLodChildren && !pEntity->m_bUnderwater)
    {
        ms_aVisibleLodPtrs[ms_nNoOfVisibleLods] = pEntity;
        ms_nNoOfVisibleLods++;
    }
    else
    {
        ms_aVisibleEntityPtrs[ms_nNoOfVisibleEntities] = pEntity;
        ms_nNoOfVisibleEntities++;
    }
#endif
}

// Converted from cdecl void CRenderer::ScanSectorList_ListModels(int sector_x,int sector_y) 0x5535D0
void CRenderer::ScanSectorList_ListModels(int sector_x, int sector_y) {
    plugin::Call<0x5535D0, int, int>(sector_x, sector_y);
}

// Converted from cdecl void CRenderer::ScanSectorList_ListModelsVisible(int sector_x,int sector_y) 0x553650
void CRenderer::ScanSectorList_ListModelsVisible(int sector_x, int sector_y) {
    plugin::Call<0x553650, int, int>(sector_x, sector_y);
}

// Converted from cdecl tRenderListEntry* CRenderer::GetLodRenderListBase(void) 0x5536D0
tRenderListEntry* CRenderer::GetLodRenderListBase() {
    return plugin::CallAndReturn<tRenderListEntry*, 0x5536D0>();
}

// Converted from cdecl tRenderListEntry* CRenderer::GetLodDontRenderListBase(void) 0x5536E0
tRenderListEntry* CRenderer::GetLodDontRenderListBase() {
    return plugin::CallAndReturn<tRenderListEntry*, 0x5536E0>();
}

// Converted from cdecl void CRenderer::ResetLodRenderLists(void) 0x5536F0
void CRenderer::ResetLodRenderLists() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x5536F0>();
#else
    ms_pLodRenderList = GetLodRenderListBase();
    ms_pLodDontRenderList = GetLodDontRenderListBase();
#endif
}

// Converted from cdecl void CRenderer::AddToLodRenderList(CEntity *entity,float distance) 0x553710
void CRenderer::AddToLodRenderList(CEntity* entity, float distance) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x553710, CEntity*, float>(entity, distance);
#else
    ms_pLodRenderList->pEntity = entity;
    ms_pLodRenderList->distance = distance;
    ++ms_pLodRenderList;
#endif
}

// Converted from cdecl void CRenderer::AddToLodDontRenderList(CEntity *entity,float distance) 0x553740
void CRenderer::AddToLodDontRenderList(CEntity* entity, float distance) {
    plugin::Call<0x553740, CEntity*, float>(entity, distance);
}

// Converted from cdecl void CRenderer::ProcessLodRenderLists(void) 0x553770
void CRenderer::ProcessLodRenderLists() {
    plugin::Call<0x553770>();
}

// Converted from cdecl void CRenderer::PreRender(void) 0x553910
void CRenderer::PreRender() {
    plugin::Call<0x553910>();
}

// Converted from cdecl void CRenderer::RenderRoads(void) 0x553A10
void CRenderer::RenderRoads() {
    plugin::Call<0x553A10>();
}

// Converted from cdecl void CRenderer::RenderEverythingBarRoads(void) 0x553AA0
void CRenderer::RenderEverythingBarRoads() {
    plugin::Call<0x553AA0>();
}

// Converted from cdecl void CRenderer::RenderFirstPersonVehicle(void) 0x553D00
void CRenderer::RenderFirstPersonVehicle() {
    plugin::Call<0x553D00>();
}

// Converted from cdecl bool CRenderer::SetupLightingForEntity(CEntity *entity) 0x553E40
bool CRenderer::SetupLightingForEntity(CEntity* entity) {
    return plugin::CallAndReturn<bool, 0x553E40, CEntity*>(entity);
}

// Converted from cdecl int CRenderer::SetupMapEntityVisibility(CEntity *entity,CBaseModelInfo *modelInfo,float distance,bool) 0x553F60
int CRenderer::SetupMapEntityVisibility(CEntity* pEntity, CBaseModelInfo* pBaseModelInfo, float fDistance, bool bIsTimeInRange) {

#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<int, 0x553F60, CEntity*, CBaseModelInfo*, float, bool>(pEntity, pBaseModelInfo, fDistance, bIsTimeInRange);
#else
    CEntity* pEntityLod = pEntity->m_pLod;
    RpClump* pClump = reinterpret_cast<RpClump*>(pBaseModelInfo->m_pRwObject);
    float fFarClipDistance = pBaseModelInfo->m_pColModel->m_boundSphere.m_fRadius + CRenderer::ms_fFarClipPlane;

    float fLodDistMultipliedWithDrawDist = TheCamera.m_fLODDistMultiplier * pBaseModelInfo->m_fDrawDistance;
    float fMinimumDrawDistance = fLodDistMultipliedWithDrawDist;
    if (fLodDistMultipliedWithDrawDist >= fFarClipDistance)
    {
        fMinimumDrawDistance = fFarClipDistance;
    }

    if (!pEntity->m_bTunnelTransition
        && ((!CRenderer::ms_bRenderTunnels && pEntity->m_bTunnel) || (!CRenderer::ms_bRenderOutsideTunnels && !pEntity->m_bTunnel)))
    {
        return RENDERER_INVISIBLE;
    }

    float fDrawDistanceMultiplied = 20.0f;
    if (!pEntityLod)
    {
        float fDrawDistanceMultiplier = pBaseModelInfo->m_fDrawDistance;
        if (fDrawDistanceMultiplier >= fMinimumDrawDistance)
        {
            fDrawDistanceMultiplier = fMinimumDrawDistance;
        }
        if (fDrawDistanceMultiplier > 150.0f)
        {
            fDrawDistanceMultiplied = fDrawDistanceMultiplier * 0.06666667f + 10.0f;
        }

        if (pEntity->m_bIsBIGBuilding)
        {
            fMinimumDrawDistance = CRenderer::ms_lowLodDistScale * fMinimumDrawDistance;
        }
    }

    if (!pClump)
    {
        if (pEntityLod
            && pEntityLod->m_nNumLodChildren > 1u
            && fDrawDistanceMultiplied + fDistance - 20.0f < fMinimumDrawDistance)
        {
            CRenderer::AddToLodRenderList(pEntity, fDistance);
            return RENDERER_STREAMME;
        }
    }

    if (!pClump || (fDrawDistanceMultiplied + fDistance - 20.0f >= fMinimumDrawDistance))
    {
        int result = 0;
        if (pEntity->m_bDontStream)
        {
            return RENDERER_INVISIBLE;
        }
        if (pClump && fDistance - 20.0f < fMinimumDrawDistance)
        {
            if (!pEntity->m_pRwObject
                && (pEntity->CreateRwObject(), !pEntity->m_pRwObject))
            {
                return RENDERER_INVISIBLE;
            }

            if (!pEntity->m_bIsVisible)
            {
                return RENDERER_INVISIBLE;
            }

            if (!pEntity->GetIsOnScreen() || pEntity->IsEntityOccluded())
            {

                if (!pBaseModelInfo->bHasBeenPreRendered)
                {
                    pBaseModelInfo->m_nAlpha = 255;
                }
                pBaseModelInfo->bHasBeenPreRendered = false;
                result = RENDERER_INVISIBLE;
            }
            else
            {
                pEntity->m_bDistanceFade = true;
                if (pEntity->m_pLod && pEntity->m_pLod->m_nNumLodChildren > 1u)
                {
                    CRenderer::AddToLodRenderList(pEntity, fDistance);
                    result = RENDERER_INVISIBLE;
                }
                else
                {
                    CRenderer::AddEntityToRenderList(pEntity, fDistance);
                    result = RENDERER_INVISIBLE;
                }
            }
            return result;
        }
        if (fDistance - 50.0f >= fMinimumDrawDistance || !bIsTimeInRange || pEntity->m_bIsVisible == false)
        {
            return RENDERER_INVISIBLE;
        }
        if (!pEntity->m_pRwObject)
        {
            pEntity->CreateRwObject();
        }
        return RENDERER_STREAMME;
    }

    if (!pEntity->m_pRwObject)
    {
        pEntity->CreateRwObject();
        if (!pEntity->m_pRwObject)
        {
            return RENDERER_INVISIBLE;
        }
    }

    if (!pEntity->m_bIsVisible)
    {
        return RENDERER_INVISIBLE;
    }

    if (pEntity->GetIsOnScreen() && !pEntity->IsEntityOccluded())
    {
        if (pBaseModelInfo->m_nAlpha == 255)
        {
            pEntity->m_bDistanceFade = false;
        }
        else
        {
            pEntity->m_bDistanceFade = true;
        }

        if (!pEntityLod)
        {
            return RENDERER_VISIBLE;
        }

        if (pBaseModelInfo->m_nAlpha == 255)
        {
            ++pEntityLod->m_nNumLodChildrenRendered;
        }

        if (pEntityLod->m_nNumLodChildren <= 1u)
        {
            return RENDERER_VISIBLE;
        }

        CRenderer::AddToLodRenderList(pEntity, fDistance);
        return RENDERER_INVISIBLE;
    }

    if (!pBaseModelInfo->bHasBeenPreRendered)
    {
        pBaseModelInfo->m_nAlpha = 255;
    }

    pBaseModelInfo->bHasBeenPreRendered = false;
    return RENDERER_CULLED;
#endif
}

// Converted from cdecl int CRenderer::SetupEntityVisibility(CEntity *entity,float &outDistance) 0x554230
int CRenderer::SetupEntityVisibility(CEntity* pEntity, float* outDistance) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<int, 0x554230, CEntity*, float*>(pEntity, outDistance);
#else
    int modelIndex = pEntity->m_nModelIndex;
    CBaseModelInfo* pBaseModelInfo = CModelInfo::ms_modelInfoPtrs[modelIndex];
    CBaseModelInfo* pBaseAtomicModelInfo = pBaseModelInfo->AsAtomicModelInfoPtr();

    if (pEntity->m_nType == ENTITY_TYPE_VEHICLE)
    {
        if (!pEntity->m_bTunnelTransition)
        {
            if ((!ms_bRenderTunnels && pEntity->m_bTunnel || !ms_bRenderOutsideTunnels && !pEntity->m_bTunnel))
            {
                return RENDERER_INVISIBLE;
            }
        }
    }

    bool bIsTimeInRange = true;
    if (!pBaseAtomicModelInfo)
    {
        if (pBaseModelInfo->GetModelType() != MODEL_INFO_CLUMP && pBaseModelInfo->GetModelType() != MODEL_INFO_WEAPON)
        {
            if (FindPlayerVehicle(-1, 0) == pEntity)
            {
                if (gbFirstPersonRunThisFrame)
                {
                    if (CReplay::Mode != 1)
                    {
                        DWORD dwDirectionWasLooking = TheCamera.m_aCams[TheCamera.m_nActiveCam].m_nDirectionWasLooking;
                        CAutomobile* pVehicle = FindPlayerVehicle(-1, 0);
                        CBike* pBike = reinterpret_cast<CBike*>(pVehicle);
                        if (pVehicle->m_nVehicleClass != CLASS_LEISUREBOAT || !(pBike->m_nDamageFlags & 0x80))
                        {
                            if (dwDirectionWasLooking == 3)
                            {
                                return RENDERER_CULLED;
                            }

                            if (modelIndex == MODEL_RHINO || modelIndex == MODEL_COACH || TheCamera.m_bInATunnelAndABigVehicle)
                            {
                                return RENDERER_CULLED;
                            }

                            if (dwDirectionWasLooking)
                            {
                                m_pFirstPersonVehicle = static_cast<CVehicle*>(pEntity);
                                return RENDERER_CULLED;
                            }

                            if (pVehicle->m_pHandlingData->m_bNo1fpsLookBehind)
                            {
                                return RENDERER_CULLED;
                            }

                            if (pVehicle->m_nVehicleClass != CLASS_BIG
                                || modelIndex == MODEL_REEFER || modelIndex == MODEL_TROPIC || modelIndex == MODEL_PREDATOR
                                || modelIndex == MODEL_SKIMMER)
                            {
                                m_pFirstPersonVehicle = static_cast<CVehicle*>(pEntity);
                                return RENDERER_CULLED;
                            }
                        }
                    }
                }
            }

            if (!pEntity->m_pRwObject
                || !pEntity->m_bIsVisible && (!CMirrors::TypeOfMirror || pEntity->m_nModelIndex)
                || !pEntity->IsCurrentAreaOrBarberShopInterior() && pEntity->m_nType == ENTITY_TYPE_VEHICLE)
            {
                return RENDERER_INVISIBLE;
            }

            if (!pEntity->GetIsOnScreen() || pEntity->IsEntityOccluded())
            {
                return RENDERER_CULLED;
            }

            if (pEntity->m_bWasPostponed)
            {
                pEntity->m_bDistanceFade = false;
                AddEntityToRenderList(pEntity, (pEntity->GetPosition() - ms_vecCameraPosition).Magnitude());
                return RENDERER_INVISIBLE;
            }
            return RENDERER_VISIBLE;
        }
    }
    else
    {
        if (pBaseModelInfo->GetModelType() == MODEL_INFO_TIME)
        {
            tTimeInfo* pModelTimeInfo = pBaseModelInfo->GetTimeInfo();
            int wOtherTimeModel = pModelTimeInfo->m_wOtherTimeModel;
            if (CClock::GetIsTimeInRange(pModelTimeInfo->m_nTimeOn, pModelTimeInfo->m_nTimeOff))
            {
                if (wOtherTimeModel != -1 && CModelInfo::ms_modelInfoPtrs[wOtherTimeModel]->m_pRwObject)
                {
                    pBaseModelInfo->m_nAlpha = 255;
                }
            }
            else
            {
                if (wOtherTimeModel == -1 || CModelInfo::ms_modelInfoPtrs[wOtherTimeModel]->m_pRwObject)
                {
                    pEntity->DeleteRwObject();
                    return RENDERER_INVISIBLE;
                }
                bIsTimeInRange = false;
            }
        }
        else
        {
            if (pEntity->m_bDontStream)
            {
                if (!pEntity->m_pRwObject || !pEntity->m_bIsVisible && (!CMirrors::TypeOfMirror || pEntity->m_nModelIndex))
                {
                    return RENDERER_INVISIBLE;
                }
                if (!pEntity->GetIsOnScreen() || pEntity->IsEntityOccluded())
                {
                    return RENDERER_CULLED;
                }

                if (!pEntity->m_bWasPostponed)
                {
                    return RENDERER_VISIBLE;
                }

                CVisibilityPlugins::InsertEntityIntoSortedList(pEntity, (pEntity->GetPosition() - ms_vecCameraPosition).Magnitude());
                pEntity->m_bDistanceFade = false;
                return RENDERER_INVISIBLE;
            }
        }
    }

    if (pEntity->m_nAreaCode == CGame::currArea || pEntity->m_nAreaCode == 13)
    {
        CVector* pPosition = &pEntity->GetPosition();;
        if (pEntity->m_pLod)
        {
            pPosition = &pEntity->m_pLod->GetPosition();
        }

        float distanceBetweenCameraAndEntity = (*pPosition - ms_vecCameraPosition).Magnitude();
        *outDistance = distanceBetweenCameraAndEntity;
        if (distanceBetweenCameraAndEntity > 300.0f)
        {
            float lodMultiplierAndDrawDistance = TheCamera.m_fLODDistMultiplier * pBaseModelInfo->m_fDrawDistance;
            if (lodMultiplierAndDrawDistance > 300.0f
                && lodMultiplierAndDrawDistance + 20.0f > distanceBetweenCameraAndEntity)
            {
                *outDistance = lodMultiplierAndDrawDistance - 300.0f + distanceBetweenCameraAndEntity;
            }
        }
        return SetupMapEntityVisibility(pEntity, pBaseModelInfo, *outDistance, bIsTimeInRange);
    }
    return RENDERER_INVISIBLE;

#endif
}

// Converted from cdecl int CRenderer::SetupBigBuildingVisibility(CEntity *entity,float *outDistance) 0x554650
int CRenderer::SetupBigBuildingVisibility(CEntity* entity, float* outDistance) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<int, 0x554650, CEntity*, float*>(entity, outDistance);
#else
    CBaseModelInfo* pBaseModelInfo = CModelInfo::ms_modelInfoPtrs[entity->m_nModelIndex];
    bool bIsTimeInRange = true;
    if (entity->m_nAreaCode != CGame::currArea && entity->m_nAreaCode != 13)
        return  RENDERER_INVISIBLE;
    if (pBaseModelInfo->GetModelType() == MODEL_INFO_TIME)
    {
        tTimeInfo* pModelTimeInfo = pBaseModelInfo->GetTimeInfo();
        int wOtherTimeModel = pModelTimeInfo->m_wOtherTimeModel;
        if (CClock::GetIsTimeInRange(pModelTimeInfo->m_nTimeOn, pModelTimeInfo->m_nTimeOff))
        {
            if (wOtherTimeModel != -1 && CModelInfo::ms_modelInfoPtrs[wOtherTimeModel]->m_pRwObject)
            {
                pBaseModelInfo->m_nAlpha = 255;
            }
        }
        else
        {
            if (wOtherTimeModel == -1 || CModelInfo::ms_modelInfoPtrs[wOtherTimeModel]->m_pRwObject)
            {
                entity->DeleteRwObject();
                return RENDERER_INVISIBLE;
            }
            bIsTimeInRange = false;
        }
        
    }
    else if (pBaseModelInfo->GetModelType() == MODEL_INFO_VEHICLE)
    {
        return entity->IsVisible() && !entity->IsEntityOccluded() ?
            RENDERER_VISIBLE : RENDERER_INVISIBLE;
    }

    CVector entityPos = entity->GetPosition();
    if (entity->m_pLod)
    {
        entityPos = entity->m_pLod->GetPosition();
    }
    CVector distance = entityPos - ms_vecCameraPosition;
    *outDistance = distance.Magnitude();
    if (entity->m_nNumLodChildrenRendered <= 0)
    {
        int visbility = SetupMapEntityVisibility(entity, pBaseModelInfo, *outDistance, bIsTimeInRange);
        if (visbility != RENDERER_VISIBLE || entity->m_nNumLodChildren <= 1u)
            return visbility;
        if (entity->m_pLod && pBaseModelInfo->m_nAlpha == 255)
            ++entity->m_pLod->m_nNumLodChildrenRendered;
        AddToLodRenderList(entity, *outDistance);
        return RENDERER_INVISIBLE;
    }

    if (entity->m_pLod)
        ++entity->m_pLod->m_nNumLodChildrenRendered;
    if (entity->m_nNumLodChildren <= 1u)
    {
        entity->m_nNumLodChildrenRendered = 0;
    }
    else
    {
        ms_pLodRenderList->pEntity = entity;
        ms_pLodRenderList->distance = *outDistance;
        ms_pLodRenderList++;
    }
    if (!entity->m_pRwObject)
        entity->CreateRwObject();
    return RENDERER_STREAMME;
#endif
}

void CRenderer::ScanSectorList(int sectorX, int sectorY) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x554840, int, int>(sectorX, sectorY);
#else
    bool bRequestModel = false;
    float fCameraAndSectorX = ((sectorX - 60) * 50.0f + 25.0f) - CRenderer::ms_vecCameraPosition.x;
    float fCameraAndSectorY = ((sectorY - 60) * 50.0f + 25.0f) - CRenderer::ms_vecCameraPosition.y;
    float fAngleInRadians = atan2(-fCameraAndSectorX, fCameraAndSectorY) - CRenderer::ms_fCameraHeading;
    float fCameraAndSectorDistance = fCameraAndSectorY * fCameraAndSectorY + fCameraAndSectorX * fCameraAndSectorX;
    if (fCameraAndSectorDistance < 10000.0f || fabs(CGeneral::LimitRadianAngle(fAngleInRadians)) < 0.36f)
    {
        bRequestModel = true;
    }

    CRenderer::SetupScanLists(sectorX, sectorY);
    CPtrListDoubleLink** pScanLists = reinterpret_cast<CPtrListDoubleLink * *>(&PC_Scratch);
    const int kiMaxScanLists = 5;
    for (int scanListIndex = 0; scanListIndex < kiMaxScanLists; scanListIndex++)
    {
        CPtrListDoubleLink* pDoubleLinkList = pScanLists[scanListIndex];
        if (pDoubleLinkList)
        {
            CPtrNodeDoubleLink* pDoubleLinkNode = pDoubleLinkList->GetNode();
            while (pDoubleLinkNode)
            {
                CEntity* pLodEntity = reinterpret_cast<CEntity*>(pDoubleLinkNode->pItem);
                pDoubleLinkNode = pDoubleLinkNode->pNext;
                if (pLodEntity->m_nScanCode != CWorld::ms_nCurrentScanCode)
                {
                    pLodEntity->m_nScanCode = CWorld::ms_nCurrentScanCode;
                    pLodEntity->m_bOffscreen = false;

                    bool bInvisibleEntity = false;
                    float outDistance = 0.0f;
                    switch (CRenderer::SetupEntityVisibility(pLodEntity, &outDistance))
                    {
                    case RENDERER_INVISIBLE:
                    {
                        if (pLodEntity->m_nType == ENTITY_TYPE_OBJECT)
                        {
                            CBaseModelInfo* pBaseModelInfo = CModelInfo::ms_modelInfoPtrs[pLodEntity->m_nModelIndex]->AsAtomicModelInfoPtr();
                            if (pBaseModelInfo)
                            {
                                if (pBaseModelInfo->nSpecialType == 4 || pBaseModelInfo->nSpecialType == 5)
                                {
                                    bInvisibleEntity = true;
                                    break;
                                }
                            }
                        }
                        break;
                    }
                    case RENDERER_VISIBLE:
                    {
                        CRenderer::AddEntityToRenderList(pLodEntity, outDistance);
                        break;
                    }
                    case RENDERER_CULLED:
                    {
                        bInvisibleEntity = true;
                        break;
                    }
                    case RENDERER_STREAMME:
                    {
                        if (CStreaming::ms_disableStreaming || !pLodEntity->GetIsOnScreen() || CRenderer::ms_bInTheSky)
                        {
                            break;
                        }

                        if (bRequestModel)
                        {
                            auto pStreamingInfo = &CStreaming::ms_aInfoForModel[pLodEntity->m_nModelIndex];
                            if (pStreamingInfo->m_nLoadState == LOADSTATE_LOADED)
                            {
                                CStreaming::RequestModel(pLodEntity->m_nModelIndex, 0);
                                break;
                            }
                            else
                            {
                                if (!pLodEntity->IsEntityOccluded())
                                {
                                    CRenderer::m_loadingPriority = 1;
                                    CStreaming::RequestModel(pLodEntity->m_nModelIndex, 0);
                                    break;
                                }
                            }
                        }
                        if (!CRenderer::m_loadingPriority || CStreaming::ms_numModelsRequested < 1)
                        {
                            CStreaming::RequestModel(pLodEntity->m_nModelIndex, 0);
                        }
                        break;
                    }
                    default:
                        break;
                    }

                    if (!bInvisibleEntity)
                    {
                        continue;
                    }

                    pLodEntity->m_bOffscreen = true;
                    if (pLodEntity->m_bHasPreRenderEffects)
                    {
                        CVector* vecEntityPosition = &pLodEntity->GetPosition();
                        float fDrawDistance = 30.0;
                        float fCameraAndEntityX = CRenderer::ms_vecCameraPosition.x - vecEntityPosition->x;

                        if (pLodEntity->m_nType == ENTITY_TYPE_VEHICLE)
                        {
                            CVehicle* pVehicle = static_cast<CVehicle*>(pLodEntity);
                            if (pVehicle->vehicleFlags.bAlwaysSkidMarks)
                            {
                                fDrawDistance = 200.0;
                            }
                        }

                        float fNegativeDrawDistance = -fDrawDistance;
                        if (fCameraAndEntityX > fNegativeDrawDistance && fCameraAndEntityX < fDrawDistance)
                        {
                            float fCameraAndEntityY = CRenderer::ms_vecCameraPosition.y - vecEntityPosition->y;
                            if (fCameraAndEntityY > fNegativeDrawDistance && fCameraAndEntityY < fDrawDistance)
                            {
                                if (CRenderer::ms_nNoOfInVisibleEntities < 149)
                                {
                                    CRenderer::ms_aInVisibleEntityPtrs[CRenderer::ms_nNoOfInVisibleEntities] = pLodEntity;
                                    CRenderer::ms_nNoOfInVisibleEntities++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
#endif
}

// Converted from cdecl void CRenderer::ScanBigBuildingList(int sector_x,int sector_y) 0x554B10
void CRenderer::ScanBigBuildingList(int sector_x, int sector_y) {
    plugin::Call<0x554B10, int, int>(sector_x, sector_y);
}

// Converted from cdecl int CRenderer::GetObjectsInFrustum(CEntity **outEntities,float distance,RwMatrixTag *transformMat) 0x554C60
int CRenderer::GetObjectsInFrustum(CEntity** outEntities, float distance, RwMatrixTag* transformMat) {
    return plugin::CallAndReturn<int, 0x554C60, CEntity**, float, RwMatrixTag*>(outEntities, distance, transformMat);
}

// Converted from cdecl bool CRenderer::ShouldModelBeStreamed(CEntity *entity,CVector const&origin,float farClip) 0x554EB0
bool CRenderer::ShouldModelBeStreamed(CEntity* entity, CVector const& origin, float farClip) {
    return plugin::CallAndReturn<bool, 0x554EB0, CEntity*, CVector const&, float>(entity, origin, farClip);
}

// Converted from cdecl void CRenderer::ScanWorld(void) 0x554FE0
void CRenderer::ScanWorld() {
    plugin::Call<0x554FE0>();
}

// Converted from cdecl void CRenderer::ScanPtrList_RequestModels(CPtrList &ptrList) 0x555680
void CRenderer::ScanPtrList_RequestModels(CPtrList& ptrList) {
    plugin::Call<0x555680, CPtrList&>(ptrList);
}

// Converted from cdecl void CRenderer::ConstructRenderList(void) 0x5556E0
void CRenderer::ConstructRenderList() {
    plugin::Call<0x5556E0>();
}

// Converted from cdecl void CRenderer::ScanSectorList_RequestModels(int sector_x,int sector_y) 0x555900
void CRenderer::ScanSectorList_RequestModels(int sector_x, int sector_y) {
    plugin::Call<0x555900, int, int>(sector_x, sector_y);
}

// Converted from cdecl void CRenderer::RequestObjectsInFrustum(RwMatrixTag *transformMat,int modelRequesFlags) 0x555960
void CRenderer::RequestObjectsInFrustum(RwMatrixTag* transformMat, int modelRequesFlags) {
    plugin::Call<0x555960, RwMatrixTag*, int>(transformMat, modelRequesFlags);
}

// Converted from cdecl void CRenderer::RequestObjectsInDirection(CVector const&posn,float angle,int modelRequesFlags) 0x555CB0
void CRenderer::RequestObjectsInDirection(CVector const& posn, float angle, int modelRequesFlags) {
    plugin::Call<0x555CB0, CVector const&, float, int>(posn, angle, modelRequesFlags);
}

void CRenderer::SetupScanLists(int sectorX, int sectorY)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x553540, int, int>(sectorX, sectorY);
#else
    CRepeatSector* pRepeatSector = GetRepeatSector(sectorX, sectorY);
    tScanLists* pScanLists = reinterpret_cast<tScanLists*>(&PC_Scratch);
    if (sectorX < 0 || (sectorY < 0 || (sectorX >= 0x78 || sectorY >= 0x78)))
    {
        pScanLists->buildingsList = nullptr;
        pScanLists->objectsList = &pRepeatSector->m_lists[0];
        pScanLists->vehiclesList = &pRepeatSector->m_lists[1];
        pScanLists->pedsList = &pRepeatSector->m_lists[2];
        pScanLists->dummiesList = nullptr;

        return;
    }
    else {
        CSector* pSector = GetSector(sectorX, sectorY);
        pScanLists->buildingsList = &pSector->m_buildings;
        pScanLists->objectsList = &pRepeatSector->m_lists[2];
        pScanLists->vehiclesList = &pRepeatSector->m_lists[0];
        pScanLists->pedsList = &pRepeatSector->m_lists[1];
        pScanLists->dummiesList = &pSector->m_dummies;

        return;
    }
#endif
}
