/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CAtomicModelInfo.h"
#include "CTimeInfo.h"

class CTimeModelInfo : public CAtomicModelInfo {
public:
    CTimeInfo m_timeInfo;

public:
    static void InjectHooks();

    ModelInfoType GetModelType() override;
    CTimeInfo* GetTimeInfo() override;

private:
    ModelInfoType GetModelType_Reversed();
    CTimeInfo* GetTimeInfo_Reversed();
};

VALIDATE_SIZE(CTimeModelInfo, 0x24);
