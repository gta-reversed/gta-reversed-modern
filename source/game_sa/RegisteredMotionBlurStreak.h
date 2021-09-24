/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CVector.h"
#include "CRGBA.h"

class CRegisteredMotionBlurStreak {
public:
    uint32  m_nId;
    CRGBA   m_color;
    CVector m_avecLeftPoints[3];
    CVector m_avecRightPoints[3];
    bool    m_acRenderHistory[3];

public:
    static void InjectHooks();

    void Update();
    void Render();
};

VALIDATE_SIZE(CRegisteredMotionBlurStreak, 0x54);
