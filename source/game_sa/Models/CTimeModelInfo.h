/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CAtomicModelInfo.h"

class  CTimeModelInfo : public CAtomicModelInfo {
public:
    CTimeModelInfo();
public:
	tTimeInfo m_timeInfo;

public:
    static void InjectHooks();

// virtual
    ModelInfoType GetModelType() override;
    tTimeInfo* GetTimeInfo() override;

// virtual implementations
    ModelInfoType GetModelType_Reversed();
    tTimeInfo* GetTimeInfo_Reversed();
};

VALIDATE_SIZE(CTimeModelInfo, 0x24);
