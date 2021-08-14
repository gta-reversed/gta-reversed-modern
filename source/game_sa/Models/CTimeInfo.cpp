#include "CTimeInfo.h"

void CTimeInfo::InjectHooks() {
    ReversibleHooks::Install("CTimeInfo", "FindOtherTimeModel", 0x4C47E0, &CTimeInfo::FindOtherTimeModel);
    ReversibleHooks::Install("CTimeInfo", "GetOtherTimeModel", 0x4C4A30, &CTimeInfo::GetOtherTimeModel);
    ReversibleHooks::Install("CTimeInfo", "GetTimeOff", 0x407330, &CTimeInfo::GetTimeOff);
    ReversibleHooks::Install("CTimeInfo", "GetTimeOn", 0x407320, &CTimeInfo::GetTimeOn);
    ReversibleHooks::Install("CTimeInfo", "SetOtherTimeModel", 0x5B3440, &CTimeInfo::SetOtherTimeModel);
    ReversibleHooks::Install("CTimeInfo", "SetTimes", 0x5B3430, &CTimeInfo::SetTimes);
}

// 0x4C47E0
CTimeInfo* CTimeInfo::FindOtherTimeModel(const char* modelName) {
    char timeSwitchModelName[24];
    strcpy(timeSwitchModelName, modelName);

    char* nightSuffix = strstr(timeSwitchModelName, "_nt");

    if (nightSuffix) {
        strncpy(nightSuffix, "_dy", 4);
    }
    else {
        char* daySuffix = strstr(timeSwitchModelName, "_dy");

        if (!daySuffix)
            return nullptr;

        strncpy(daySuffix, "_nt", 4);
    }

    int index = 0;
    CBaseModelInfo* modelInfo = CModelInfo::GetModelInfoFromHashKey(CKeyGen::GetUppercaseKey(timeSwitchModelName), &index);
    CTimeInfo* timeInfo = modelInfo ? modelInfo->GetTimeInfo() : nullptr;

    if (timeInfo) {
        m_nOtherTimeModel = index;
        return timeInfo;
    }

    return nullptr;
}
