/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CRGBA.h"
#include "CVector.h"

class  CCheckpoint {
public:
    unsigned short m_nType;
    bool           m_bIsUsed;
    bool           m_bMustBeRenderedThisFrame;
    int            m_nIdentifier;
    CRGBA          m_colour;
    short          m_nPulsePeriod;
    short          m_nRotateRate;
    CVector        m_vecPosition;
    CVector        m_vecDirection;
    float          m_fPulseFraction;
    float          m_fSize;
    float          m_fDistanceToPlayer; //or CameraRange
    float m_multiSize;

    void Render();
};

VALIDATE_SIZE(CCheckpoint, 0x38);