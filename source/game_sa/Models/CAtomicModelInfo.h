/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CBaseModelInfo.h"

struct tVehicleComponentFlag {
    char const* m_ucName;
    unsigned int m_nFlag;
};

class CAtomicModelInfo : public CBaseModelInfo {
public:
    CAtomicModelInfo() : CBaseModelInfo() {}

public:
    static void InjectHooks();

    // vtable overrides
    CAtomicModelInfo* AsAtomicModelInfoPtr() override;
    ModelInfoType GetModelType() override;
    void Init() override;
    void DeleteRwObject() override;
    unsigned int GetRwModelType() override;
    RwObject* CreateInstance() override;
    RwObject* CreateInstance(RwMatrix* matrix) override;

    // vtable added methods
    virtual void SetAtomic(RpAtomic* atomic);

    // vtable implementations;
    CAtomicModelInfo* AsAtomicModelInfoPtr_Reversed();
    ModelInfoType GetModelType_Reversed();
    void Init_Reversed();
    void DeleteRwObject_Reversed();
    unsigned int GetRwModelType_Reversed();
    RwObject* CreateInstance_Reversed();
    RwObject* CreateInstance_Reversed(RwMatrix* matrix);
    void SetAtomic_Reversed(RpAtomic* atomic);

    // class methods
    struct RpAtomic* GetAtomicFromDistance(float distance);
    void SetupVehicleUpgradeFlags(char const* name);
};

void SetAtomicModelInfoFlags(CAtomicModelInfo* modelInfo, unsigned int dwFlags);

VALIDATE_SIZE(CAtomicModelInfo, 0x20);
