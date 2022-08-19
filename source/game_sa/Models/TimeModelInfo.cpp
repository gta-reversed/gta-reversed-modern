#include "StdInc.h"

#include "ModelInfo.h"

void CTimeModelInfo::InjectHooks() {
    RH_ScopedClass(CTimeModelInfo);
    RH_ScopedCategory("Models");

    RH_ScopedVirtualInstall(GetModelType, 0x4C5660);
    RH_ScopedVirtualInstall(GetTimeInfo, 0x4C5670);
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
