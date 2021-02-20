/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CBox.h"
#include "CColPoint.h"

class CColBox : public CBox {
public:
	unsigned char m_nMaterial;
	unsigned char m_nFlags;
    tColLighting  m_nLighting;
	unsigned char m_nBrightness;

	void Set(CVector  const& sup, CVector  const& inf, unsigned char material , unsigned char flags, unsigned char lighting);
    CColBox& operator=(CColBox const& right);
};

VALIDATE_SIZE(CColBox, 0x1C);
