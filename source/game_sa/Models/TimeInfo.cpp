#include "StdInc.h"
#include "TimeInfo.h"

void CTimeInfo::InjectHooks() {
    Install("CTimeInfo", "FindOtherTimeModel", 0x4C47E0, &CTimeInfo::FindOtherTimeModel);
    Install("CTimeInfo", "GetOtherTimeModel", 0x4C4A30, &CTimeInfo::GetOtherTimeModel);
    Install("CTimeInfo", "GetTimeOff", 0x407330, &CTimeInfo::GetTimeOff);
    Install("CTimeInfo", "GetTimeOn", 0x407320, &CTimeInfo::GetTimeOn);
    Install("CTimeInfo", "SetOtherTimeModel", 0x5B3440, &CTimeInfo::SetOtherTimeModel);
    Install("CTimeInfo", "SetTimes", 0x5B3430, &CTimeInfo::SetTimes);
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

    int32 index = 0;
    CBaseModelInfo* modelInfo = CModelInfo::GetModelInfoFromHashKey(CKeyGen::GetUppercaseKey(timeSwitchModelName), &index);
    CTimeInfo* timeInfo = modelInfo ? modelInfo->GetTimeInfo() : nullptr;

    if (timeInfo) {
        m_nOtherTimeModel = index;
        return timeInfo;
    }

    return nullptr;
}
