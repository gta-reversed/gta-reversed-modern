/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"

struct  tColLighting
{
    unsigned char day : 4;
    unsigned char night : 4;
};


class  CColPoint {
public:
	/* https://code.google.com/p/mtasa-blue/source/browse/tags/1.3.4/MTA10/game_sa/CColPointSA.h */
	CVector       m_vecPoint;
	float field_C;
	CVector       m_vecNormal;
	float field_1C;
    // col shape 1 info
	unsigned char m_nSurfaceTypeA; // see eSurfaceType
	unsigned char m_nPieceTypeA;
    tColLighting m_nLightingA;
private:
    char _pad;
public:
    // col shape 2 info
	unsigned char m_nSurfaceTypeB; // see eSurfaceType
	unsigned char m_nPieceTypeB;
    tColLighting m_nLightingB;
private:
    char _pad2;
public:
    // col depth
	float         m_fDepth;

	void operator=(CColPoint const& right);
};

VALIDATE_SIZE(CColPoint, 0x2C);