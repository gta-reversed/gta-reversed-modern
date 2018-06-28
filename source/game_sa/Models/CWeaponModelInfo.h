/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CClumpModelInfo.h"
#include "eWeaponType.h"

class  CWeaponModelInfo : public CClumpModelInfo {
public:
	eWeaponType m_weaponInfo;
};


VALIDATE_SIZE(CWeaponModelInfo, 0x28);