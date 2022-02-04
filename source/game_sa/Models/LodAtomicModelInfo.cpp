#include "StdInc.h"

#include "LodAtomicModelInfo.h"

void CLodAtomicModelInfo::InjectHooks()
{
    RH_ScopedClass(CLodAtomicModelInfo);
    RH_ScopedCategory("Models");

    RH_ScopedInstall(AsLodAtomicModelInfoPtr_Reversed, 0x4C5610);
    RH_ScopedInstall(GetModelType_Reversed, 0x4C5600);
    RH_ScopedInstall(Init_Reversed, 0x4C54D0);
}

CLodAtomicModelInfo::CLodAtomicModelInfo() : CAtomicModelInfo()
{
    field_20 = 0;
    field_22 = 0;
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
