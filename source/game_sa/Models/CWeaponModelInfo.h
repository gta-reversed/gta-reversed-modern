/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CClumpModelInfo.h"
#include "eWeaponType.h"

class CWeaponModelInfo : public CClumpModelInfo {
public:
    CWeaponModelInfo() : CClumpModelInfo() {}
public:
	eWeaponType m_weaponInfo;

public:
    static void InjectHooks();

public:
// VTable
    ModelInfoType GetModelType() override;
    void Init() override;
    void SetClump(RpClump* clump) override;

// VTable implementations
    ModelInfoType GetModelType_Reversed();
    void Init_Reversed();
    void SetClump_Reversed(RpClump* clump);
};


VALIDATE_SIZE(CWeaponModelInfo, 0x28);
