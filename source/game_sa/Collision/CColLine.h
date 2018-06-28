/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"

class CColLine {
public:
	CVector m_vecStart;
	float m_fStartSize;
	CVector m_vecEnd;
	float m_fEndSize;

	CColLine(CVector  const& start, CVector  const& end);
	void Set(CVector  const& start, CVector  const& end);
};

VALIDATE_SIZE(CColLine, 0x20);