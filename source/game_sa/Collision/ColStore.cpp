#include "StdInc.h"

CVector& CColStore::ms_vecCollisionNeeded = *(CVector*)0x965580;
bool& CColStore::ms_bCollisionNeeded = *(bool*)0x965558;
int32 CColStore::ms_nRequiredCollisionArea = *(int32*)0x965554;

CPool<ColDef>* &CColStore::ms_pColPool = *(CPool<ColDef>**)0x965560;
CQuadTreeNode* &CColStore::ms_pQuadTree = *(CQuadTreeNode**)0x96555C;

void CColStore::InjectHooks()
{
// CLASS
    ReversibleHooks::Install("CColStore", "Initialise", 0x4113F0, &CColStore::Initialise);
    ReversibleHooks::Install("CColStore", "Shutdown", 0x4114D0, &CColStore::Shutdown);
    ReversibleHooks::Install("CColStore", "AddCollisionNeededAtPosn", 0x4103A0, &CColStore::AddCollisionNeededAtPosn);
    ReversibleHooks::Install("CColStore", "AddColSlot", 0x411140, &CColStore::AddColSlot);
    ReversibleHooks::Install("CColStore", "AddRef", 0x4107A0, &CColStore::AddRef);
    ReversibleHooks::Install("CColStore", "RemoveRef", 0x4107D0, &CColStore::RemoveRef);
    ReversibleHooks::Install("CColStore", "EnsureCollisionIsInMemory", 0x410AD0, &CColStore::EnsureCollisionIsInMemory);
    ReversibleHooks::Install("CColStore", "SetCollisionRequired", 0x4104E0, &CColStore::SetCollisionRequired);
    ReversibleHooks::Install("CColStore", "RequestCollision", 0x410C00, &CColStore::RequestCollision);
    ReversibleHooks::Install("CColStore", "RemoveColSlot", 0x411330, &CColStore::RemoveColSlot);
    ReversibleHooks::Install("CColStore", "RemoveCol", 0x410730, &CColStore::RemoveCol);
    ReversibleHooks::Install("CColStore", "LoadCol", 0x410690, (void(*)(int32, char const*))&CColStore::LoadCol);
    ReversibleHooks::Install("CColStore", "LoadCol_2", 0x4106D0, (bool(*)(int32, uint8*, int32))&CColStore::LoadCol);
    ReversibleHooks::Install("CColStore", "IncludeModelIndex", 0x410820, &CColStore::IncludeModelIndex);
    ReversibleHooks::Install("CColStore", "RemoveAllCollision", 0x410E00, &CColStore::RemoveAllCollision);
    ReversibleHooks::Install("CColStore", "LoadAllCollision", 0x410E60, &CColStore::LoadAllCollision);
    ReversibleHooks::Install("CColStore", "LoadAllBoundingBoxes", 0x4113D0, &CColStore::LoadAllBoundingBoxes);
    ReversibleHooks::Install("CColStore", "BoundingBoxesPostProcess", 0x410EC0, &CColStore::BoundingBoxesPostProcess);
    ReversibleHooks::Install("CColStore", "GetBoundingBox", 0x410800, &CColStore::GetBoundingBox);
    ReversibleHooks::Install("CColStore", "HasCollisionLoaded", 0x410CE0, &CColStore::HasCollisionLoaded);
    ReversibleHooks::Install("CColStore", "LoadCollision", 0x410860, &CColStore::LoadCollision);

// OTHER
    ReversibleHooks::Install("CColStore", "SetIfCollisionIsRequired", 0x4103D0, &SetIfCollisionIsRequired);
    ReversibleHooks::Install("CColStore", "SetIfCollisionIsRequiredReducedBB", 0x410470, &SetIfCollisionIsRequiredReducedBB);
}

void* ColDef::operator new(uint32 size)
{
    return CColStore::ms_pColPool->New();
}

void ColDef::operator delete(void* data)
{
    CColStore::ms_pColPool->Delete(static_cast<ColDef*>(data));
}

void CColStore::Initialise()
{
    const auto rect = CRect(-3000.0F, -3000.0F, 3000.0F, 3000.0F);
    CColStore::ms_bCollisionNeeded = false;
    if (!CColStore::ms_pColPool)
        ms_pColPool = new CPool<ColDef>(TOTAL_COL_MODEL_IDS, "CollisionFiles");

    CColStore::AddColSlot("generic");
    CColStore::ms_pQuadTree = new CQuadTreeNode(rect, 3);
}

void CColStore::Shutdown()
{
    for (int32 i = 0; i < TOTAL_COL_MODEL_IDS; ++i)
        if (CColStore::ms_pColPool->GetAt(i))
            CColStore::RemoveColSlot(i);

    delete CColStore::ms_pColPool;
    CColStore::ms_pColPool = nullptr;

    delete CColStore::ms_pQuadTree;
    CColStore::ms_pQuadTree = nullptr;
}

int32 CColStore::AddColSlot(const char* name)
{
    auto pColDef = new ColDef();
    pColDef->m_bActive = false;
    pColDef->m_bCollisionIsRequired = false;
    pColDef->m_bProcedural = false;
    pColDef->m_bInterior = false;
    pColDef->m_Area = CRect();
    pColDef->m_nModelIdStart = -1;
    pColDef->m_nModelIdEnd = SHRT_MIN;
    pColDef->m_nRefCount = 0;

    if (!strcmp(name, "procobj") || !strcmp(name, "proc_int") || !strcmp(name, "proc_int2"))
        pColDef->m_bProcedural = true;

    if (!strncmp(name, "int_la", 6)
        || !strncmp(name, "int_sf", 6)
        || !strncmp(name, "int_veg", 7)
        || !strncmp(name, "int_cont", 8)
        || !strncmp(name, "gen_int1", 8)
        || !strncmp(name, "gen_int2", 8)
        || !strncmp(name, "gen_int3", 8)
        || !strncmp(name, "gen_int4", 8)
        || !strncmp(name, "gen_int5", 8)
        || !strncmp(name, "gen_intb", 8)
        || !strncmp(name, "savehous", 8)
        || !strcmp(name, "props")
        || !strcmp(name, "props2")
        || !strncmp(name, "levelmap", 8)
        || !strncmp(name, "stadint", 7))
    {
        pColDef->m_bInterior = true;
    }

    return CColStore::ms_pColPool->GetIndex(pColDef);
}

void CColStore::AddCollisionNeededAtPosn(const CVector& pos)
{
    ms_vecCollisionNeeded = pos;
    ms_bCollisionNeeded = true;
}

void CColStore::AddRef(int32 colNum)
{
    auto *pColDef = CColStore::ms_pColPool->GetAt(colNum);
    ++pColDef->m_nRefCount; //BUG: We don't check whether the GetAt returned nullptr, which it can
}

int32 CColStore::FindColSlot()
{
    return -1;
}

void CColStore::BoundingBoxesPostProcess()
{
    for (auto i = 1; i < TOTAL_COL_MODEL_IDS; ++i)
    {
        auto* pDef = CColStore::ms_pColPool->GetAt(i);
        if (!pDef)
            continue;

        if (CColAccel::isCacheLoading())
        {
            CColAccel::getColDef(*pDef);
        }
        else
        {
            pDef->m_Area.Resize(120.0F, 120.0F);
            CColAccel::addColDef(*pDef);
        }

        CColStore::ms_pQuadTree->AddItem(pDef, pDef->m_Area);
    }
}

void CColStore::EnsureCollisionIsInMemory(CVector const& pos)
{
    if (CStreaming::ms_disableStreaming)
        return;

    auto* pPlayer = FindPlayerPed(-1);
    const auto area = pPlayer ? pPlayer->m_nAreaCode : CGame::currArea;
    if (area != CGame::currArea)
        return;

    CColStore::SetCollisionRequired(pos, area);
    for (auto i = 1; i < TOTAL_COL_MODEL_IDS; ++i)
    {
        auto* pDef = CColStore::ms_pColPool->GetAt(i);
        if (!pDef || !pDef->m_bCollisionIsRequired)
            continue;

        auto* pStreamingInfo = &CStreaming::ms_aInfoForModel[RESOURCE_ID_COL + i];
        if (pDef->m_Area.IsPointInside(pos, -110.0F) && pStreamingInfo->m_nLoadState != LOADSTATE_LOADED)
        {
            CStreaming::RequestModel(RESOURCE_ID_COL + i, STREAMING_PRIORITY_REQUEST | STREAMING_KEEP_IN_MEMORY);
            if (!TheCamera.GetScreenFadeStatus())
                FrontEndMenuManager.MessageScreen("LOADCOL", false, false);

            CTimer::Suspend();
            CStreaming::LoadAllRequestedModels(true);
            CTimer::Resume();
        }

        pDef->m_bCollisionIsRequired = false;
    }
}

CRect* CColStore::GetBoundingBox(int32 colSlot)
{
    auto* pDef = CColStore::ms_pColPool->GetAt(colSlot);
    return &pDef->m_Area;
}

void CColStore::IncludeModelIndex(int32 colSlot, int32 modelId)
{
    auto* pDef = CColStore::ms_pColPool->GetAt(colSlot);

    if (modelId < pDef->m_nModelIdStart)
        pDef->m_nModelIdStart = modelId;

    if (modelId > pDef->m_nModelIdEnd)
        pDef->m_nModelIdEnd = modelId;
}

bool CColStore::HasCollisionLoaded(CVector const& pos, int32 areaCode)
{
    CColStore::SetCollisionRequired(pos, areaCode);
    auto foundInd = -1;
    for (auto i = 1; i < TOTAL_COL_MODEL_IDS; ++i)
    {
        auto* pDef = CColStore::ms_pColPool->GetAt(i);
        if (!pDef || !pDef->m_bCollisionIsRequired)
            continue;

        pDef->m_bCollisionIsRequired = false;
        if (pDef->m_Area.IsPointInside(pos, -110.0F) && !pDef->m_bActive)
        {
            foundInd = i; // Slightly modified the method logic to be more readable, result is the same
            break;
        }
    }

    if (foundInd == -1)
        return true;

    for (auto i = foundInd; i < TOTAL_COL_MODEL_IDS; ++i)
    {
        auto* pInnerDef = CColStore::ms_pColPool->GetAt(i);
        if (!pInnerDef)
            continue;

        pInnerDef->m_bCollisionIsRequired = false;
    }

    return false;
}

void CColStore::LoadAllBoundingBoxes()
{
    if (CColAccel::isCacheLoading())
        CColAccel::cacheLoadCol();
    else
        CColStore::LoadAllCollision();
}

void CColStore::LoadAllCollision()
{
    for (auto i = 1; i < TOTAL_COL_MODEL_IDS; ++i)
    {
        auto* pDef = CColStore::ms_pColPool->GetAt(i);
        if (!pDef)
            continue;

        CStreaming::RequestModel(RESOURCE_ID_COL + i, 0);
        CStreaming::LoadAllRequestedModels(false);
        CStreaming::RemoveModel(RESOURCE_ID_COL + i);
    }
}

void CColStore::LoadCol(int32 colSlot, char const* filename)
{
    auto* pDef = CColStore::ms_pColPool->GetAt(colSlot);
    CFileLoader::LoadCollisionFile(filename, colSlot);
    pDef->m_bActive = true;
}

bool CColStore::LoadCol(int32 colSlot, uint8* data, int32 dataSize)
{
    auto* pDef = CColStore::ms_pColPool->GetAt(colSlot);

    bool bLoaded;
    if (pDef->m_nModelIdStart <= pDef->m_nModelIdEnd)
        bLoaded = CFileLoader::LoadCollisionFile(data, dataSize, colSlot);
    else
        bLoaded = CFileLoader::LoadCollisionFileFirstTime(data, dataSize, colSlot);

    if (!bLoaded)
        return false;

    pDef->m_bActive = true;
    return true;
}

void CColStore::LoadCollision(CVector pos, bool bIgnorePlayerVeh)
{
    if (CStreaming::ms_disableStreaming)
        return;

    auto* pPlayer = FindPlayerPed(-1);
    if (pPlayer && !bIgnorePlayerVeh)
    {
        auto* pVeh = FindPlayerVehicle(-1, false);
        if (pVeh)
        {
            pos += pVeh->m_vecMoveSpeed * CVector(20.0F, 20.0F, 0.0F);
        }
    }

    CColStore::SetCollisionRequired(pos, -1);
    if (CColStore::ms_bCollisionNeeded)
        CColStore::SetCollisionRequired(CColStore::ms_vecCollisionNeeded, CGame::currArea);

    for (auto& obj : CTheScripts::MissionCleanUp.m_Objects)
    {
        CEntity* pEntity = nullptr;
        if (obj.type == MissionCleanUpEntityType::MISSION_CLEANUP_ENTITY_TYPE_VEHICLE)
        {
            pEntity = CPools::ms_pVehiclePool->GetAtRef(obj.handle);
            if (!pEntity || pEntity->m_nStatus == eEntityStatus::STATUS_WRECKED)
                continue;
        }
        else if (obj.type == MissionCleanUpEntityType::MISSION_CLEANUP_ENTITY_TYPE_PED)
        {
            pEntity = CPools::ms_pPedPool->GetAtRef(obj.handle);
            if (!pEntity || pEntity->AsPed()->m_nPedState == ePedState::PEDSTATE_DIE || pEntity->AsPed()->m_nPedState == ePedState::PEDSTATE_DEAD)
                continue;
        }

        if (!pEntity || pEntity->AsPhysical()->physicalFlags.b15 || pEntity->AsPhysical()->physicalFlags.bDontApplySpeed)
            continue;

        CColStore::ms_nRequiredCollisionArea = pEntity->m_nAreaCode;
        CColStore::ms_pQuadTree->ForAllMatching(pEntity->GetPosition(), SetIfCollisionIsRequiredReducedBB);
    }

    for (auto i = 1; i < TOTAL_COL_MODEL_IDS; ++i)
    {
        auto* pDef = CColStore::ms_pColPool->GetAt(i);
        if (!pDef)
            continue;

        if (pDef->m_bCollisionIsRequired || pDef->m_bProcedural || pDef->m_nRefCount > 0)
        {
            if (!pDef->m_bActive)
                CStreaming::RequestModel(RESOURCE_ID_COL + i, STREAMING_PRIORITY_REQUEST | STREAMING_KEEP_IN_MEMORY);

            pDef->m_bCollisionIsRequired = false;
        }
        else if (pDef->m_bActive)
            CStreaming::RemoveModel(RESOURCE_ID_COL + i);
    }

    if (!bIgnorePlayerVeh)
        CColStore::ms_bCollisionNeeded = false;
}

void CColStore::RemoveAllCollision()
{
    for (auto i = 1; i < TOTAL_COL_MODEL_IDS; ++i)
    {
        auto* pDef = CColStore::ms_pColPool->GetAt(i);
        if (!pDef)
            continue;

        auto* pStreamingInfo = &CStreaming::ms_aInfoForModel[RESOURCE_ID_COL + i];
        if (!pStreamingInfo->bMissionRequired && !pStreamingInfo->bGameRequired)
            CStreaming::RemoveModel(RESOURCE_ID_COL + i);
    }
}

void CColStore::RemoveCol(int32 colSlot)
{
    auto* pDef = CColStore::ms_pColPool->GetAt(colSlot);
    pDef->m_bActive = false;
    for (auto i = pDef->m_nModelIdStart; i <= pDef->m_nModelIdEnd; ++i)
    {
        auto* pModelInfo = CModelInfo::GetModelInfo(i);
        if (!pModelInfo)
            continue;

        auto* pCol = pModelInfo->GetColModel();
        if (!pCol)
            continue;

        if (pModelInfo->IsLod() && pCol->m_boundSphere.m_nColSlot == colSlot)
            pCol->RemoveCollisionVolumes();
    }
}

void CColStore::RemoveColSlot(int32 colSlot)
{
    auto* pDef = CColStore::ms_pColPool->GetAt(colSlot);
    if (pDef->m_bActive)
        CColStore::RemoveCol(colSlot);

    CColStore::ms_pQuadTree->DeleteItem(pDef);
    delete pDef;
}

void CColStore::RemoveRef(int32 colNum)
{
    auto* pColDef = CColStore::ms_pColPool->GetAt(colNum);
    --pColDef->m_nRefCount; //BUG: We don't check whether the GetAt returned nullptr, which it can
}

void CColStore::RequestCollision(CVector const& pos, int32 areaCode)
{
    CColStore::SetCollisionRequired(pos, areaCode);
    for (auto i = 1; i < TOTAL_COL_MODEL_IDS; ++i)
    {
        auto* pDef = CColStore::ms_pColPool->GetAt(i);
        if (!pDef || !pDef->m_bCollisionIsRequired)
            continue;

        if (pDef->m_Area.IsPointInside(pos, -110.0F))
            CStreaming::RequestModel(RESOURCE_ID_COL + i, STREAMING_PRIORITY_REQUEST | STREAMING_KEEP_IN_MEMORY);

        pDef->m_bCollisionIsRequired = false;
    }
}

void CColStore::SetCollisionRequired(const CVector& pos, int32 areaCode)
{
    auto usedArea = areaCode;
    if (areaCode == -1)
    {
        auto* pPlayer = FindPlayerPed(-1);
        usedArea = pPlayer ? pPlayer->m_nAreaCode : CGame::currArea;
    }

    CColStore::ms_nRequiredCollisionArea = usedArea;
    if (usedArea == CGame::currArea)
        CColStore::ms_pQuadTree->ForAllMatching(pos, SetIfCollisionIsRequired);
    else
        CColStore::ms_pQuadTree->ForAllMatching(pos, SetIfCollisionIsRequiredReducedBB);
}

void SetIfCollisionIsRequired(CVector2D const& vecPos, void* data)
{
    auto* pDef = static_cast<ColDef*>(data);
    if (!CColStore::ms_nRequiredCollisionArea && pDef->m_bInterior)
        return;

    if (!pDef->m_Area.IsPointInside(vecPos))
        return;

    pDef->m_bCollisionIsRequired = true;
}

void SetIfCollisionIsRequiredReducedBB(CVector2D const& vecPos, void* data)
{
    auto* pDef = static_cast<ColDef*>(data);
    if (!pDef->m_Area.IsPointInside(vecPos, -80.0F))
        return;

    if (!CColStore::ms_nRequiredCollisionArea && pDef->m_bInterior)
        return;

    pDef->m_bCollisionIsRequired = true;
}
