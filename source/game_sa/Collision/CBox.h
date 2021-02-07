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

public:
    static void InjectHooks();

	void Set(CVector const& vecMin, CVector const& vecMax);
	// updates box corners, like (if left>right then swap(left, right))
	void Recalc();

public:
    inline CVector const& GetSize() const { return m_vecMax - m_vecMin; }
    inline float GetWidth() const { return m_vecMax.x - m_vecMin.x; }
    inline float GetLength() const { return m_vecMax.y - m_vecMin.y; }
    inline float GetHeight() const { return m_vecMax.z - m_vecMin.z; }
};

VALIDATE_SIZE(CBox, 0x18);
