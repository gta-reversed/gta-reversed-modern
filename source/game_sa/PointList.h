/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

class CPointList {
public:
    uint32  m_nCount;
    CVector m_avCoords[24];
    bool    m_abUsedCoords[24];

    void Empty();
};

VALIDATE_SIZE(CPointList, 0x13C);
