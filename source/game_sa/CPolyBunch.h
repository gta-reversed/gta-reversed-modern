/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"

class CPolyBunch {
public:
    CVector m_avecPosn[7];
    void *m_pNext;
    unsigned short m_wNumVerts;
    char m_aU[7];
    char m_aV[7];
};

VALIDATE_SIZE(CPolyBunch, 0x68);