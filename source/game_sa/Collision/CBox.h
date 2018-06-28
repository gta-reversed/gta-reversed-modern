/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"

class CBox {
public:
	CVector m_vecMin;
	CVector m_vecMax;

	void Set(CVector  const& vecMin, CVector  const& vecMax);
	// updates box corners, like (if left>right then swap(left, right))
	void Recalc();
};

VALIDATE_SIZE(CBox, 0x18);
