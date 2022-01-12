#pragma once
#include "AtomicModelInfo.h"

class CLodAtomicModelInfo : public CAtomicModelInfo {
public:
    CLodAtomicModelInfo();
public:
    int16 field_20;
    int16 field_22;

public:
    static void InjectHooks();

    // VTABLE
    CLodAtomicModelInfo* AsLodAtomicModelInfoPtr() override;
    ModelInfoType GetModelType() override;
    void Init() override;

    // VTABLE Implementations
    CLodAtomicModelInfo* AsLodAtomicModelInfoPtr_Reversed();
    ModelInfoType GetModelType_Reversed();
    void Init_Reversed();
};

VALIDATE_SIZE(CLodAtomicModelInfo, 0x24);
