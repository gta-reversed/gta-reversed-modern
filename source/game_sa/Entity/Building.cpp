#include "StdInc.h"

int32& gBuildings = *(int32*)0xB71804;

void CBuilding::InjectHooks()
{
    ReversibleHooks::Install("CBuilding", "ReplaceWithNewModel", 0x403EC0, &CBuilding::ReplaceWithNewModel);
    ReversibleHooks::Install("CBuilding", "IsBuildingPointerValid", 0x4040E0, &IsBuildingPointerValid);
}

CBuilding::CBuilding() : CEntity()
{
    m_nType = eEntityType::ENTITY_TYPE_BUILDING;
    m_bUsesCollision = true;
}

void* CBuilding::operator new(unsigned size)
{
    return CPools::ms_pBuildingPool->New();
}

void CBuilding::operator delete(void* data)
{
    CPools::ms_pBuildingPool->Delete(static_cast<CBuilding*>(data));
}

void CBuilding::ReplaceWithNewModel(int32 newModelIndex)
{
    this->DeleteRwObject();
    if (!CModelInfo::GetModelInfo(m_nModelIndex)->m_nRefCount)
        CStreaming::RemoveModel(m_nModelIndex);

    m_nModelIndex = newModelIndex;
}

bool IsBuildingPointerValid(CBuilding* pBuilding)
{
    if (!pBuilding)
        return false;

    return CPools::ms_pBuildingPool->IsObjectValid(pBuilding);
}
