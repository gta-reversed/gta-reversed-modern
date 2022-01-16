#pragma once

#include "AtomicModelInfo.h"
#include "TimeInfo.h"

class CLodTimeModelInfo : public CLodAtomicModelInfo {
public:
    CTimeInfo m_lodTimeInfo;

public:
    static void InjectHooks();

    // virtual
    ModelInfoType GetModelType() override;
    CTimeInfo*    GetTimeInfo() override;

    // virtual implementations
    ModelInfoType GetModelType_Reversed();
    CTimeInfo*    GetTimeInfo_Reversed();
};

VALIDATE_SIZE(CLodTimeModelInfo, 0x28);
