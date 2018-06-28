/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class CColTriangle {
public:
	unsigned short m_nVertA; // vertex index in vertices array
	unsigned short m_nVertB; // vertex index in vertices array
	unsigned short m_nVertC; // vertex index in vertices array
	unsigned char m_nMaterial;
	unsigned char m_nLight;
};

VALIDATE_SIZE(CColTriangle, 8);