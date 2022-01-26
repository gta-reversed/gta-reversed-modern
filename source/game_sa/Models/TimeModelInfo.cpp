#include "StdInc.h"
#include "ModelInfo.h"

void CTimeModelInfo::InjectHooks() {
    RH_ScopedInstall(GetModelType_Reversed, 0x4C5660);
    RH_ScopedInstall(GetTimeInfo_Reversed, 0x4C5670);
    // RH_ScopedInstall(FindOtherTimeModel, 0x4C47E0);
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
