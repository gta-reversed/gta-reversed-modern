#include "StdInc.h"

#include "LodTimeModelInfo.h"

void CLodTimeModelInfo::InjectHooks()
{
    RH_ScopedClass(CLodTimeModelInfo);
    RH_ScopedCategory("Models");

    RH_ScopedVirtualInstall(GetModelType, 0x4C5660);
    RH_ScopedVirtualInstall(GetTimeInfo, 0x4C5670);
}

ModelInfoType CLodTimeModelInfo::GetModelType()
{
    return CLodTimeModelInfo::GetModelType_Reversed();
}
ModelInfoType CLodTimeModelInfo::GetModelType_Reversed()
{
    return ModelInfoType::MODEL_INFO_TIME;
}

CTimeInfo* CLodTimeModelInfo::GetTimeInfo()
{
    return CLodTimeModelInfo::GetTimeInfo_Reversed();
}
CTimeInfo* CLodTimeModelInfo::GetTimeInfo_Reversed()
{
    return &m_lodTimeInfo;
}
