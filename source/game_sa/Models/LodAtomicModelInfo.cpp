#include "StdInc.h"


void CLodAtomicModelInfo::InjectHooks()
{
    ReversibleHooks::Install("CLodAtomicModelInfo", "AsLodAtomicModelInfoPtr", 0x4C5610, &CLodAtomicModelInfo::AsLodAtomicModelInfoPtr_Reversed);
    ReversibleHooks::Install("CLodAtomicModelInfo", "GetModelType", 0x4C5600, &CLodAtomicModelInfo::GetModelType_Reversed);
    ReversibleHooks::Install("CLodAtomicModelInfo", "Init", 0x4C54D0, &CLodAtomicModelInfo::Init_Reversed);
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
