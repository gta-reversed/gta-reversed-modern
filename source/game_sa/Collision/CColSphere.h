/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CSphere.h"

class CColSphere : public CSphere {
public:
	unsigned char m_nMaterial;
	unsigned char m_nFlags;
	unsigned char m_nLighting;
	unsigned char m_nLight;

	void Set(float radius, CVector  const& center, unsigned char material , unsigned char flags, unsigned char lighting);
	bool IntersectRay(CVector  const& rayStart, CVector  const& rayEnd, CVector& intPoint1, CVector& intPoint2);
};

VALIDATE_SIZE(CColSphere, 0x14);