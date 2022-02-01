#include "StdInc.h"

CColAccelColBound*& CColAccel::m_colBounds = *(CColAccelColBound**)0xBC4090;
IplDef*& CColAccel::m_iplDefs = *(IplDef**)0xBC4094;
int32*& CColAccel::m_iSectionSize = *(int32**)0xBC4098;
int32& CColAccel::m_iCachingColSize = *(int32*)0xBC409C;
eColAccelState& CColAccel::m_iCacheState = *(eColAccelState*)0xBC40A0;
CColAccelColEntry*& CColAccel::mp_caccColItems = *(CColAccelColEntry**)0xBC40A4;
int32& CColAccel::m_iNumColItems = *(int32*)0xBC40A8;
CColAccelIPLEntry*& CColAccel::mp_caccIPLItems = *(CColAccelIPLEntry**)0xBC40AC;
int32& CColAccel::m_iNumIPLItems = *(int32*)0xBC40B0;
int32& CColAccel::m_iNumSections = *(int32*)0xBC40B4;
int32& CColAccel::m_iNumColBounds = *(int32*)0xBC40B8;
char const* CColAccel::mp_cCacheName = *(char const**)0x8D0F84; // MODELS\CINFO.BIN

void CColAccel::InjectHooks()
{
    RH_ScopedClass(CColAccel);
    RH_ScopedCategory("Collision");

    RH_ScopedInstall(isCacheLoading, 0x5B2AC0);
    RH_ScopedInstall(endCache, 0x5B2AD0);
    RH_ScopedInstall(addCacheCol, 0x5B2C20);
    RH_ScopedInstall(cacheLoadCol, 0x5B2CC0);
    RH_ScopedInstall(addColDef, 0x5B2DD0);
    RH_ScopedInstall(getColDef, 0x5B2E60);
    RH_ScopedInstall(setIplDef, 0x5B2ED0);
    RH_ScopedInstall(getIplDef, 0x5B2EF0);
    RH_ScopedInstall(cacheIPLSection, 0x5B2F10);
    RH_ScopedInstall(addIPLEntity, 0x5B3040);
    RH_ScopedInstall(startCache, 0x5B31A0);
}

bool CColAccel::isCacheLoading()
{
    return CColAccel::m_iCacheState == eColAccelState::COLACCEL_LOADING;
}

void CColAccel::endCache()
{
    if (CColAccel::m_iCacheState == eColAccelState::COLACCEL_STARTED) {
        auto* pFile = CFileMgr::OpenFileForWriting(CColAccel::mp_cCacheName);
        CFileMgr::Write(pFile, &CColAccel::m_iNumColItems, sizeof(int32));
        CFileMgr::Write(pFile, CColAccel::mp_caccColItems, sizeof(CColAccelColEntry) * CColAccel::m_iNumColItems);
        CFileMgr::Write(pFile, &CColAccel::m_iNumSections, sizeof(int32));
        CFileMgr::Write(pFile, CColAccel::m_iSectionSize, sizeof(int32) * CColAccel::m_iNumSections);
        CFileMgr::Write(pFile, CColAccel::m_iplDefs, sizeof(IplDef) * TOTAL_IPL_MODEL_IDS);
        CFileMgr::Write(pFile, &CColAccel::m_iNumColBounds, sizeof(int32));
        CFileMgr::Write(pFile, CColAccel::m_colBounds, sizeof(CColAccelColBound) * CColAccel::m_iNumColBounds);
        CFileMgr::Write(pFile, &CColAccel::m_iNumIPLItems, sizeof(int32));
        CFileMgr::Write(pFile, CColAccel::mp_caccIPLItems, sizeof(CColAccelIPLEntry) * CColAccel::m_iNumIPLItems);
        CFileMgr::CloseFile(pFile);
    }

    delete[] CColAccel::mp_caccIPLItems;
    CColAccel::mp_caccIPLItems = nullptr;

    delete[] CColAccel::mp_caccColItems;
    CColAccel::mp_caccColItems = nullptr;

    delete[] CColAccel::m_iSectionSize;
    CColAccel::m_iSectionSize = nullptr;

    delete[] CColAccel::m_iplDefs;
    CColAccel::m_iplDefs = nullptr;

    delete[] CColAccel::m_colBounds;
    CColAccel::m_colBounds = nullptr;

    CColAccel::m_iCacheState = eColAccelState::COLACCEL_ENDED;
}

void CColAccel::addCacheCol(PackedModelStartEnd startEnd, CColModel const& colModel)
{
    if (CColAccel::m_iCacheState != eColAccelState::COLACCEL_STARTED)
        return;

    auto& colEntry = CColAccel::mp_caccColItems[CColAccel::m_iNumColItems];
    colEntry.m_wModelStart = startEnd.wModelStart;
    colEntry.m_wModelEnd = startEnd.wModelEnd;
    colEntry.m_boundBox = colModel.m_boundBox;
    colEntry.m_boundSphere = colModel.m_boundSphere;
    colEntry.m_nColSlot = colModel.m_nColSlot;
    colEntry.m_bColModelNotEmpty = colModel.m_bNotEmpty;

    ++CColAccel::m_iNumColItems;
}

void CColAccel::cacheLoadCol()
{
    if (!CColAccel::isCacheLoading())
        return;

    for (auto i = 0; i < CColAccel::m_iNumColItems; ++i) {
        auto& colEntry = CColAccel::mp_caccColItems[i];
        auto* pModelInfo = CModelInfo::GetModelInfo(colEntry.m_wModelStart);

        auto pColModel = new CColModel();
        pColModel->m_boundBox = colEntry.m_boundBox;
        pColModel->m_boundSphere = colEntry.m_boundSphere;
        pColModel->m_nColSlot = colEntry.m_nColSlot;
        pColModel->m_bNotEmpty = colEntry.m_bColModelNotEmpty;

        pModelInfo->SetColModel(pColModel, true);
        CColStore::IncludeModelIndex(colEntry.m_nColSlot, colEntry.m_wModelStart);
    }
}

void CColAccel::addColDef(ColDef colDef)
{
    auto& colBound = CColAccel::m_colBounds[CColAccel::m_iNumColBounds];
    colBound.m_Area = colDef.m_Area;
    colBound.m_wModelStart = colDef.m_nModelIdStart;
    colBound.m_wModelEnd = colDef.m_nModelIdEnd;
    colBound.m_bInterior = colDef.m_bInterior;
    colBound.m_bProcedural = colDef.m_bProcedural;

    ++CColAccel::m_iNumColBounds;
}

void CColAccel::getColDef(ColDef& colDef)
{
    auto& colBound = CColAccel::m_colBounds[CColAccel::m_iNumColBounds];
    colDef.m_Area = colBound.m_Area;
    colDef.m_nModelIdStart = colBound.m_wModelStart;
    colDef.m_nModelIdEnd = colBound.m_wModelEnd;
    colDef.m_bInterior = colBound.m_bInterior;
    colDef.m_bProcedural = colBound.m_bProcedural;

    ++CColAccel::m_iNumColBounds;
}

void CColAccel::setIplDef(int32 iplIndex, IplDef iplDef)
{
    CColAccel::m_iplDefs[iplIndex] = iplDef;
}

IplDef CColAccel::getIplDef(int32 iplIndex)
{
    return CColAccel::m_iplDefs[iplIndex];
}

void CColAccel::cacheIPLSection(CEntity** ppEntities, int32 entitiesCount)
{
    if (CColAccel::isCacheLoading())
    {
        for (auto i = CColAccel::m_iNumIPLItems; i < CColAccel::m_iSectionSize[CColAccel::m_iNumSections]; ++i)
        {
            auto& iplEntry = CColAccel::mp_caccIPLItems[i];
            if (iplEntry.m_bIsUnderwater)
                ppEntities[iplEntry.m_nEntityIndex]->m_bUnderwater = true;

            if (iplEntry.m_bOwnsColModel)
                CModelInfo::GetModelInfo(iplEntry.m_nModelId)->SetOwnsColModel(true);

            if (iplEntry.m_bIsFarDrawDist)
                CModelInfo::GetModelInfo(iplEntry.m_nModelId)->m_fDrawDistance = 400.0F;

            if (iplEntry.m_bHasColModel)
            {
                auto* lodModelInfo = CModelInfo::GetModelInfo(iplEntry.m_nLodModelId);
                auto* entModelInfo = CModelInfo::GetModelInfo(iplEntry.m_nModelId);
                lodModelInfo->DeleteCollisionModel();
                lodModelInfo->SetColModel(entModelInfo->GetColModel(), false);
            }

            ++CColAccel::m_iNumIPLItems;
        }

        ++CColAccel::m_iNumSections;
    }
    else if (CColAccel::m_iCacheState == eColAccelState::COLACCEL_STARTED) {
        CColAccel::m_iSectionSize[CColAccel::m_iNumSections] = CColAccel::m_iNumIPLItems;
        ++CColAccel::m_iNumSections;
    }
}

void CColAccel::addIPLEntity(CEntity** ppEntities, int32 entitiesCount, int32 entityIndex)
{
    if (CColAccel::m_iCacheState != eColAccelState::COLACCEL_STARTED)
        return;

    CColAccelIPLEntry iplEntry;
    auto& pEntity = ppEntities[entityIndex];
    auto* pLod = pEntity->m_pLod;
    auto* entModelInfo = CModelInfo::GetModelInfo(pEntity->m_nModelIndex);

    iplEntry.m_nFlags = 0;
    iplEntry.m_nEntityIndex = entityIndex;
    iplEntry.m_nModelId = pEntity->m_nModelIndex;
    iplEntry.m_nLodModelId = pLod->m_nModelIndex;
    iplEntry.m_nLodIndex = -1;

    if (pEntity->m_nNumLodChildren || TheCamera.m_fLODDistMultiplier * entModelInfo->m_fDrawDistance > 300.0F)
        iplEntry.m_bIsFarDrawDist = true;

    for (auto i = 0; i < entitiesCount; ++i)
    {
        if (ppEntities[i] != pEntity->m_pLod)
            continue;

        iplEntry.m_nLodIndex = i;
        break;
    }

    auto* lodModelInfo = CModelInfo::GetModelInfo(iplEntry.m_nLodModelId);
    if (pLod->m_nNumLodChildren == 1)
    {
        if (pEntity->m_bUnderwater)
            iplEntry.m_bIsUnderwater = true;

        if (lodModelInfo->GetColModel() != entModelInfo->GetColModel() || !entModelInfo->GetColModel())
            iplEntry.m_bHasColModel = true;
    }
    else
    {
        if (entModelInfo->bDoWeOwnTheColModel)
            iplEntry.m_bOwnsColModel = true;
    }

    if (iplEntry.m_nFlags)
    {
        CColAccel::mp_caccIPLItems[CColAccel::m_iNumIPLItems] = iplEntry;
        ++CColAccel::m_iNumIPLItems;
    }
}

void CColAccel::startCache()
{
    CColAccel::m_iCachingColSize = CPools::ms_pColModelPool->GetSize();
    CColAccel::m_iSectionSize = new int32[64];
    CColAccel::m_iplDefs = new IplDef[TOTAL_IPL_MODEL_IDS]();
    CColAccel::m_colBounds = new CColAccelColBound[TOTAL_IPL_MODEL_IDS]();
}
