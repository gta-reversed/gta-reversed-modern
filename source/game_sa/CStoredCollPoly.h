/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"

class  CStoredCollPoly {
public:
    CVector      m_aMeshVertices[3]; // triangle vertices
    bool         m_bIsActual;
    unsigned int m_nLighting;
};

VALIDATE_SIZE(CStoredCollPoly, 0x2C);
