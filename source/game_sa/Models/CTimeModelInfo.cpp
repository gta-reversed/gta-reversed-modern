#include "StdInc.h"
#include "CModelInfo.h"

void CTimeModelInfo::InjectHooks() {
    ReversibleHooks::Install("CTimeModelInfo", "GetModelType", 0x4C5660, &CTimeModelInfo::GetModelType_Reversed);
    ReversibleHooks::Install("CTimeModelInfo", "GetTimeInfo", 0x4C5670, &CTimeModelInfo::GetTimeInfo_Reversed);
    // ReversibleHooks::Install("CTimeModelInfo", "FindOtherTimeModel", 0x4C47E0, &CTimeModelInfo::FindOtherTimeModel);
}

// 0x4C5660
ModelInfoType CTimeModelInfo::GetModelType() {
    return ModelInfoType::MODEL_INFO_TIME;
}

// 0x4C5670
CTimeInfo* CTimeModelInfo::GetTimeInfo() {
    return &m_timeInfo;
}

ModelInfoType CTimeModelInfo::GetModelType_Reversed() {
    return CTimeModelInfo::GetModelType();
}

CTimeInfo* CTimeModelInfo::GetTimeInfo_Reversed() {
    return CTimeModelInfo::GetTimeInfo();
}
