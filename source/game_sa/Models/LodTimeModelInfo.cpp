#include "StdInc.h"

void CLodTimeModelInfo::InjectHooks()
{
    RH_ScopedClass(CLodTimeModelInfo);
    RH_ScopedCategory("Models");

    RH_ScopedInstall(GetModelType_Reversed, 0x4C5660);
    RH_ScopedInstall(GetTimeInfo_Reversed, 0x4C5670);
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
