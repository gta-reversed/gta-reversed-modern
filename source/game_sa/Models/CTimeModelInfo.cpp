#include "StdInc.h"

void CTimeModelInfo::InjectHooks()
{
    ReversibleHooks::Install("CTimeModelInfo", "GetModelType", 0x4C5660, &CTimeModelInfo::GetModelType_Reversed);
    ReversibleHooks::Install("CTimeModelInfo", "GetTimeInfo", 0x4C5670, &CTimeModelInfo::GetTimeInfo_Reversed);
}

CTimeModelInfo::CTimeModelInfo() : CAtomicModelInfo()
{
    m_timeInfo.m_wOtherTimeModel = -1;
}

ModelInfoType CTimeModelInfo::GetModelType()
{
    return CTimeModelInfo::GetModelType_Reversed();
}
ModelInfoType CTimeModelInfo::GetModelType_Reversed()
{
    return ModelInfoType::MODEL_INFO_TIME;
}

tTimeInfo* CTimeModelInfo::GetTimeInfo()
{
    return CTimeModelInfo::GetTimeInfo_Reversed();
}
tTimeInfo* CTimeModelInfo::GetTimeInfo_Reversed()
{
    return &m_timeInfo;
}
