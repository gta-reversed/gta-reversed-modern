/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"

class  CCrimeBeingQd {
public:
    unsigned int m_nCrimeType; // see eCrimeType
    unsigned int m_nCrimeID;
    unsigned int m_nTimeOfQing;
    CVector      m_vecCoors;
    bool         m_bAlreadyReported;
    bool         m_bPoliceDontReallyCare;
private:
    char _pad1A[2];
public:
};

VALIDATE_SIZE(CCrimeBeingQd, 0x1C);
