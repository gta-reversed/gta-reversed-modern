/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CompressedVector.h"
#include "CVector.h"
#include "CColTriangle.h"

enum eTrianglePlaneOrientation : unsigned char {
    POS_X = 0,
    NEG_X = 1,
    POS_Y = 2,
    NEG_Y = 3,
    POS_Z = 4,
    NEG_Z = 5,
};

class CColTrianglePlane {
public:
	CompressedVector m_normal;
	unsigned short m_nDistance;
	unsigned char m_nOrientation;

public:
    static void InjectHooks();

	void GetNormal(CVector &out);
	void Set(CompressedVector  const* vertices, CColTriangle & triangle);
};
VALIDATE_SIZE(CColTrianglePlane, 0xA);
