#include "StdInc.h"

void CTimeModelInfo::InjectHooks() {
    ReversibleHooks::Install("CTimeModelInfo", "GetModelType", 0x4C5660, &CTimeModelInfo::GetModelType_Reversed);
    ReversibleHooks::Install("CTimeModelInfo", "GetTimeInfo", 0x4C5670, &CTimeModelInfo::GetTimeInfo_Reversed);
}

// 0x4C5640
CTimeModelInfo::CTimeModelInfo() : CAtomicModelInfo() {
    m_timeInfo.m_nOtherTimeModel = -1;
}

// 0x4C5680, 0x4C6270
CTimeModelInfo::~CTimeModelInfo() {

}

// 0x4C5660
ModelInfoType CTimeModelInfo::GetModelType() {
    return ModelInfoType::MODEL_INFO_TIME;
}

// 0x4C5670
tTimeInfo* CTimeModelInfo::GetTimeInfo() {
    return &m_timeInfo;
}

// 0x4C47E0
tTimeInfo* CTimeModelInfo::FindOtherTimeModel(const char* modelName) {
    return plugin::CallMethodAndReturn<tTimeInfo*, 0x4C47E0, CTimeModelInfo*, const char*>(this, modelName);
}

ModelInfoType CTimeModelInfo::GetModelType_Reversed() {
    return CTimeModelInfo::GetModelType();
}

tTimeInfo* CTimeModelInfo::GetTimeInfo_Reversed() {
    return CTimeModelInfo::GetTimeInfo();
}
