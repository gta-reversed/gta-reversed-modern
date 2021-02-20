/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"

struct tColLighting
{
    unsigned char day : 4;
    unsigned char night : 4;

    tColLighting() = default;
    tColLighting(const unsigned char ucLighting)
    {
        day = ucLighting & 0xF;
        night = (ucLighting >> 4) & 0xF;
    }

    // Original func: 0x59F0C0
    float GetCurrentLighting(float fScale = 0.5F) const;
};
VALIDATE_SIZE(tColLighting, 0x1);

class  CColPoint {
public:
	/* https://code.google.com/p/mtasa-blue/source/browse/tags/1.3.4/MTA10/game_sa/CColPointSA.h */
	CVector       m_vecPoint;                               // 0
	float field_C;                                          // 12
	CVector       m_vecNormal;                              // 16
	float field_1C;                                         // 28
    // col shape 1 info
	unsigned char m_nSurfaceTypeA; // see eSurfaceType      // 32
	unsigned char m_nPieceTypeA;                            // 33
    tColLighting m_nLightingA;                              // 34
    // col shape 2 info     
	unsigned char m_nSurfaceTypeB; // see eSurfaceType      // 35
	unsigned char m_nPieceTypeB;                            // 36
    tColLighting m_nLightingB;
    char padding [2];
    // col depth
	float         m_fDepth;

	void operator=(CColPoint const& right);
};

VALIDATE_SIZE(CColPoint, 0x2C);
