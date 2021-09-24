#pragma once
#include "AtomicModelInfo.h"

class CDamageAtomicModelInfo : public CAtomicModelInfo
{
public:
    CDamageAtomicModelInfo() : CAtomicModelInfo() {}

public:
    RpAtomic* m_pDamagedAtomic;

public:
    static void InjectHooks();

public:
// VTable
    CDamageAtomicModelInfo* AsDamageAtomicModelInfoPtr() override;
    void Init() override;
    void DeleteRwObject() override;
    struct RwObject* CreateInstance() override;
    struct RwObject* CreateInstance(RwMatrix* matrix) override;

// VTable implementations
    CDamageAtomicModelInfo* AsDamageAtomicModelInfoPtr_Reversed();
    void Init_Reversed();
    void DeleteRwObject_Reversed();
    struct RwObject* CreateInstance_Reversed();
    struct RwObject* CreateInstance_Reversed(RwMatrix* matrix);

// Other
    void SetDamagedAtomic(RpAtomic* atomic);

public:
    static bool& ms_bCreateDamagedVersion;
};

VALIDATE_SIZE(CDamageAtomicModelInfo, 0x24);
