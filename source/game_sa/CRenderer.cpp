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
bool &CRenderer::ms_bRenderTunnels = *(bool *)0xB745C0;
bool &CRenderer::ms_bRenderOutsideTunnels = *(bool *)0xB745C1;
tRenderListEntry *&CRenderer::ms_pLodDontRenderList = *(tRenderListEntry **)0xB745CC;
tRenderListEntry *&CRenderer::ms_pLodRenderList = *(tRenderListEntry **)0xB745D0;
CVehicle *&CRenderer::m_pFirstPersonVehicle = *(CVehicle **)0xB745D4;
CEntity **CRenderer::ms_aInVisibleEntityPtrs = (CEntity **)0xB745D8;
CEntity **CRenderer::ms_aVisibleSuperLodPtrs = (CEntity **)0xB74830;
CEntity **CRenderer::ms_aVisibleLodPtrs = (CEntity **)0xB748F8;
CEntity **CRenderer::ms_aVisibleEntityPtrs = (CEntity **)0xB75898;
unsigned int &CRenderer::ms_nNoOfVisibleSuperLods = *(unsigned int *)0xB76838;
unsigned int &CRenderer::ms_nNoOfInVisibleEntities = *(unsigned int *)0xB7683C;
unsigned int &CRenderer::ms_nNoOfVisibleLods = *(unsigned int *)0xB76840;
unsigned int &CRenderer::ms_nNoOfVisibleEntities = *(unsigned int *)0xB76844;
float &CRenderer::ms_fFarClipPlane = *(float *)0xB76848;
float &CRenderer::ms_fCameraHeading = *(float *)0xB7684C;
unsigned char &CRenderer::m_loadingPriority = *(unsigned char *)0xB76850;
bool &CRenderer::ms_bInTheSky = *(bool *)0xB76851;
CVector &CRenderer::ms_vecCameraPosition = *(CVector *)0xB76870;
float &CRenderer::ms_lodDistScale = *(float *)0x8CD800;
float &CRenderer::ms_lowLodDistScale = *(float *)0x8CD804;
unsigned int &gnRendererModelRequestFlags = *(unsigned int *)0xB745C4;
CEntity **&gpOutEntitiesForGetObjectsInFrustum = *(CEntity ***)0xB76854;

void CRenderer::InjectHooks()
{
    InjectHook(0x05534B0, &CRenderer::AddEntityToRenderList, PATCH_JUMP);
    InjectHook(0x554230, &CRenderer::SetupEntityVisibility, PATCH_JUMP);
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
    plugin::Call<0x5531E0>();
}

// Converted from cdecl void CRenderer::RenderFadingInUnderwaterEntities(void) 0x553220
void CRenderer::RenderFadingInUnderwaterEntities() {
    plugin::Call<0x553220>();
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

void CRenderer::AddEntityToRenderList(CEntity *pEntity, float fDistance)
{
    CBaseModelInfo* pBaseModelInfo = CModelInfo::ms_modelInfoPtrs[pEntity->m_nModelIndex];
    pBaseModelInfo->m_nFlagsUpperByte &= ~MODELINFO_FLAGS_LOD;

    if (pEntity->m_bDistanceFade >= 0)
    {
        if (pEntity->m_bDrawLast && CVisibilityPlugins::InsertEntityIntoSortedList(pEntity, fDistance))
        {
            pEntity->m_nFlags &= ~MODELINFO_FLAGS_DISTANCE_FADE;
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
    plugin::Call<0x5536F0>();
}

// Converted from cdecl void CRenderer::AddToLodRenderList(CEntity *entity,float distance) 0x553710
void CRenderer::AddToLodRenderList(CEntity* entity, float distance) {
    plugin::Call<0x553710, CEntity*, float>(entity, distance);
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
int CRenderer::SetupMapEntityVisibility(CEntity* entity, CBaseModelInfo* modelInfo, float distance, bool arg3) {
    return plugin::CallAndReturn<int, 0x553F60, CEntity*, CBaseModelInfo*, float, bool>(entity, modelInfo, distance, arg3);
}

// Converted from cdecl int CRenderer::SetupEntityVisibility(CEntity *entity,float &outDistance) 0x554230
int CRenderer::SetupEntityVisibility(CEntity* pEntity, float * outDistance) {
    //return plugin::CallAndReturn<int, 0x554230, CEntity*, float&>(entity, outDistance);
    int modelIndex = pEntity->m_nModelIndex;
    CBaseModelInfo *pBaseModelInfo = CModelInfo::ms_modelInfoPtrs[modelIndex];
    CBaseModelInfo *pBaseAtomicModelInfo = pBaseModelInfo->AsAtomicModelInfoPtr();
    bool bDoSomething = 1;
    if ((pEntity->m_nType & 7) == 2)
    {
        unsigned int entityFlags = pEntity->m_nFlags;
        if (entityFlags >= 0
            && (!ms_bRenderTunnels && entityFlags & 0x40000000 || !ms_bRenderOutsideTunnels && !(entityFlags & 0x40000000)))
        {
            return 0;
        }
    }

    if (!pBaseAtomicModelInfo)
    {
        if (pBaseModelInfo->GetModelType() != 5 && pBaseModelInfo->GetModelType() != 4)
        {
            if (FindPlayerVehicle(-1, 0) == pEntity)
            {
                if (gbFirstPersonRunThisFrame)
                {
                    if (CReplay::Mode != 1)
                    {

                        DWORD dwDirectionWasLooking = TheCamera.m_aCams[TheCamera.m_nActiveCam].m_nDirectionWasLooking;
                        CAutomobile * pVehicle = FindPlayerVehicle(-1, 0);
                        if (pVehicle->m_nVehicleClass != CLASS_LEISUREBOAT
                            || !(pVehicle->m_doors[3].m_nDoorFlags & 0x80))
                        {
                            if (dwDirectionWasLooking == 3)
                                return 2;
                            if (modelIndex == 432 || modelIndex == 437 || TheCamera.m_bInATunnelAndABigVehicle)
                                return 2;
                            if (dwDirectionWasLooking)
                                goto LABEL_81;
                            if (pVehicle->m_pHandlingData->m_nModelFlags & 0x4000)
                                return 2;
                            if (pVehicle->m_nVehicleClass != CLASS_BIG
                                || modelIndex == 453
                                || modelIndex == 454
                                || modelIndex == 430
                                || modelIndex == 460)
                            {
                            LABEL_81:
                                m_pFirstPersonVehicle = static_cast<CVehicle*>(pEntity);
                                return 2;
                            }
                        }
                    }
                }
            }
            if (!pEntity->m_pRwObject
                || !(pEntity->m_nFlags & 0x80) && (!CMirrors::TypeOfMirror || pEntity->m_nModelIndex)
                || !pEntity->IsCurrentAreaOrBarberShopInterior() && (pEntity->m_nType & 7) == 2)
            {
                return 0;
            }
            if (!pEntity->GetIsOnScreen() || pEntity->IsEntityOccluded())
                return 2;

            if (pEntity->m_nFlags & 0x40)
            {
                pEntity->m_nFlags = pEntity->m_nFlags & 0xFFFF7FFF;
                CMatrixLink * entityMatrix = pEntity->m_matrix;
                CVector *vecPosition;
                if (entityMatrix)
                    vecPosition = &entityMatrix->pos;
                else
                    vecPosition = &pEntity->m_placement.m_vPosn;

                CVector out;
                CVector * vectorSubResult = VectorSub(&out, vecPosition, &ms_vecCameraPosition);
                AddEntityToRenderList(pEntity, vectorSubResult->Magnitude());
                return 0;
            }
            return 1;
        }
        goto LABEL_49;
    }
    if (pBaseModelInfo->GetModelType() == 3)
    {
        tTimeInfo* pModelTimeInfo = pBaseModelInfo->GetTimeInfo();
        int wOtherTimeModel = pModelTimeInfo->m_wOtherTimeModel;          // m_wOtherTimeModel
        if (CClock::GetIsTimeInRange(pModelTimeInfo->m_nTimeOn, pModelTimeInfo->m_nTimeOff))// m_nTimeOn, m_nTimeOff
        {
            if (wOtherTimeModel != -1 && CModelInfo::ms_modelInfoPtrs[wOtherTimeModel]->m_pRwObject)
                pBaseModelInfo->m_nAlpha = -1;
        }
        else
        {
            if (wOtherTimeModel == -1 || CModelInfo::ms_modelInfoPtrs[wOtherTimeModel]->m_pRwObject)
            {
                pEntity->DeleteRwObject();
                return 0;
            }
            bDoSomething = 0;
        }
    LABEL_49:
        unsigned __int8 entityInterior = pEntity->m_nAreaCode;
        if (entityInterior == CGame::currArea || entityInterior == 13)
        {
            CVector * vecPosition;
            CEntity * pEntityLod = pEntity->m_pLod;
            if (pEntityLod)
            {
                CMatrixLink *entityMatrix = pEntityLod->m_matrix;
                if (entityMatrix)
                    vecPosition = &entityMatrix->pos;
                else
                    vecPosition = &pEntityLod->m_placement.m_vPosn;
            }
            else
            {
                CMatrixLink *entityMatrix = pEntity->m_matrix;
                if (entityMatrix)
                    vecPosition = &entityMatrix->pos;
                else
                    vecPosition = &pEntity->m_placement.m_vPosn;
            }
            float posX = vecPosition->x;
            float posY = vecPosition->y;
            float posZ = vecPosition->z;
            float distanceBetweenCameraAndEntity = sqrt(
                (posZ - ms_vecCameraPosition.z)
                * (posZ - ms_vecCameraPosition.z)
                + (posY - ms_vecCameraPosition.y)
                * (posY - ms_vecCameraPosition.y)
                + (posX - ms_vecCameraPosition.x)
                * (posX - ms_vecCameraPosition.x));
            *outDistance = distanceBetweenCameraAndEntity;
            if (distanceBetweenCameraAndEntity > 300.0)
            {
                float lodMultiplierAndDrawDistance = TheCamera.m_fLODDistMultiplier * pBaseModelInfo->m_fDrawDistance;
                if (lodMultiplierAndDrawDistance > 300.0
                    && lodMultiplierAndDrawDistance + 20.0 > distanceBetweenCameraAndEntity)
                {
                    *outDistance = lodMultiplierAndDrawDistance - 300.0 + distanceBetweenCameraAndEntity;
                }
            }
            return SetupMapEntityVisibility(pEntity, pBaseModelInfo, *outDistance, bDoSomething);
        }
        return 0;
    }
    if (!(pEntity->m_nFlags & 0x80000))
        goto LABEL_49;
    if (!pEntity->m_pRwObject
        || (pEntity->m_nFlags & 0x80u) == 0 && (!CMirrors::TypeOfMirror || pEntity->m_nModelIndex))
    {
        return 0;
    }
    if (!pEntity->GetIsOnScreen() || pEntity->IsEntityOccluded())
        return 2;

    if (!(pEntity->m_nFlags & 0x40))
        return 1;
    CMatrixLink *entityMatrix = pEntity->m_matrix;
    CVector * vecPosition;
    if (entityMatrix)
        vecPosition = &entityMatrix->pos;
    else
        vecPosition = &pEntity->m_placement.m_vPosn;
    CVector out;
    CVector * vectorSubResult = VectorSub(&out, vecPosition, &ms_vecCameraPosition);
    CVisibilityPlugins::InsertEntityIntoSortedList(pEntity, vectorSubResult->Magnitude());
    pEntity->m_nFlags &= 0xFFFF7FFF;
    return 0;
}

// Converted from cdecl int CRenderer::SetupBigBuildingVisibility(CEntity *entity,float &outDistance) 0x554650
int CRenderer::SetupBigBuildingVisibility(CEntity* entity, float& outDistance) {
    return plugin::CallAndReturn<int, 0x554650, CEntity*, float&>(entity, outDistance);
}

// Converted from cdecl void CRenderer::ScanSectorList(int sector_x,int sector_y) 0x554840
void CRenderer::ScanSectorList(int sector_x, int sector_y) {
    plugin::Call<0x554840, int, int>(sector_x, sector_y);
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

// Converted from cdecl void CRenderer::SetupScanLists(int sector_x, int sector_y) 0x553540
void CRenderer::SetupScanLists(int sector_x, int sector_y) {
    plugin::Call<0x553540, int, int>(sector_x, sector_y);
}