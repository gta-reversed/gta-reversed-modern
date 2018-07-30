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
}

void CRenderer::AddEntityToRenderList(CEntity *pEntity, float fDistance)
{
    CBaseModelInfo* pBaseModelInfo = CModelInfo::ms_modelInfoPtrs[pEntity->m_nModelIndex];
    pBaseModelInfo->m_nFlags &= 0xFEu; // set first 7 bits to true, and 8th bit (bIsLod) to false

    if (!pEntity->m_bDistanceFade)
    {
        if (pEntity->m_bDrawLast && CVisibilityPlugins::InsertEntityIntoSortedList(pEntity, fDistance))
        {
            pEntity->m_nFlags &= 0xFFFF7FFF; // bDistanceFade
            return;
        }
    }
    else if (CVisibilityPlugins::InsertEntityIntoSortedList(pEntity, fDistance))
    {
        return;
    }

    if (!pEntity->m_nNumLodChildren || pEntity->m_bUnderwater)
    {
        ms_aVisibleEntityPtrs[ms_nNoOfVisibleEntities] = pEntity;
        ms_nNoOfVisibleEntities++;
    }
    else
    {
        ms_aVisibleLodPtrs[ms_nNoOfVisibleLods] = pEntity;
        ms_nNoOfVisibleLods++;
    }
}