/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CBaseModelInfo.h"

class  CAtomicModelInfo : public CBaseModelInfo {
public:
	// vtable

	void SetAtomic(struct RpAtomic *atomic);

	struct RpAtomic *GetAtomicFromDistance(float distance);
};

VALIDATE_SIZE(CAtomicModelInfo, 0x20);