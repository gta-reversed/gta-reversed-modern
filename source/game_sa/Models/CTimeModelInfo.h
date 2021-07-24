/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CAtomicModelInfo.h"

class CTimeModelInfo : public CAtomicModelInfo {
public:
    tTimeInfo m_timeInfo;

public:
    static void InjectHooks();

    CTimeModelInfo();
    ~CTimeModelInfo();

    ModelInfoType GetModelType() override;
    tTimeInfo* GetTimeInfo() override;

    tTimeInfo* FindOtherTimeModel(const char* modelName);

private:
    ModelInfoType GetModelType_Reversed();
    tTimeInfo* GetTimeInfo_Reversed();
};

VALIDATE_SIZE(CTimeModelInfo, 0x24);
