#pragma once
#include "PluginBase.h"
#include "CAtomicModelInfo.h"

class  CLodTimeModelInfo : public CLodAtomicModelInfo {
public:
    CLodTimeModelInfo();
public:
    tTimeInfo m_lodTimeInfo;

public:
    static void InjectHooks();

    // virtual
    ModelInfoType GetModelType() override;
    tTimeInfo* GetTimeInfo() override;

    // virtual implementations
    ModelInfoType GetModelType_Reversed();
    tTimeInfo* GetTimeInfo_Reversed();
};

VALIDATE_SIZE(CLodTimeModelInfo, 0x28);
