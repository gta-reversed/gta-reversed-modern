#include "StdInc.h"

#include "LodAtomicModelInfo.h"

void CLodAtomicModelInfo::InjectHooks()
{
    RH_ScopedClass(CLodAtomicModelInfo);
    RH_ScopedCategory("Models");

    RH_ScopedVirtualInstall(AsLodAtomicModelInfoPtr, 0x4C5610);
    RH_ScopedVirtualInstall(GetModelType, 0x4C5600);
    RH_ScopedVirtualInstall(Init, 0x4C54D0);
}

CLodAtomicModelInfo::CLodAtomicModelInfo() : CAtomicModelInfo()
{
    m_numChildren = 0;
    m_numChildrenRendered = 0;
}

CLodAtomicModelInfo* CLodAtomicModelInfo::AsLodAtomicModelInfoPtr()
{
    return CLodAtomicModelInfo::AsLodAtomicModelInfoPtr_Reversed();
}
CLodAtomicModelInfo* CLodAtomicModelInfo::AsLodAtomicModelInfoPtr_Reversed()
{
    return this;
}

ModelInfoType CLodAtomicModelInfo::GetModelType()
{
    return CLodAtomicModelInfo::GetModelType_Reversed();
}
ModelInfoType CLodAtomicModelInfo::GetModelType_Reversed()
{
    return ModelInfoType::MODEL_INFO_LOD;
}

void CLodAtomicModelInfo::Init()
{
    CLodAtomicModelInfo::Init_Reversed();
}
void CLodAtomicModelInfo::Init_Reversed()
{
    CAtomicModelInfo::Init();
}
