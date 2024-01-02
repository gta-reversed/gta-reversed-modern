#pragma once

#include "AtomicModelInfo.h"

class NOTSA_EXPORT_VTABLE CLodAtomicModelInfo : public CAtomicModelInfo {
public:
    int16 m_numChildren;
    int16 m_numChildrenRendered;

public:
    CLodAtomicModelInfo();

    CLodAtomicModelInfo* AsLodAtomicModelInfoPtr() override;
    ModelInfoType GetModelType() override;
    void Init() override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CLodAtomicModelInfo* AsLodAtomicModelInfoPtr_Reversed();
    ModelInfoType GetModelType_Reversed();
    void Init_Reversed();
};

VALIDATE_SIZE(CLodAtomicModelInfo, 0x24);
