/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CVector.h"

enum eBrightLightColor {
    BRIGHTLIGHT_GREEN_BIG = 1,
    BRIGHTLIGHT_YELLOW_BIG = 2,
    BRIGHTLIGHT_RED_BIG = 3,
    BRIGHTLIGHT_GREEN_SMALL = 13,
    BRIGHTLIGHT_YELLOW_SMALL = 14,
    BRIGHTLIGHT_RED_SMALL = 15
};

struct tBrightLight {
    CVector       m_vecPosition;
    CVector       m_vecRight;
    CVector       m_vecTop;
    CVector       m_vecAt;
    float         m_fDistanceToCamera;
    unsigned char m_nColor; // see eBrightLightColor
    char field_35;
    char field_36;
    char field_37;
};

VALIDATE_SIZE(tBrightLight, 0x38);

extern unsigned int MAX_NUM_BRIGHTLIGHTS; // default 32

class  CBrightLights {
public:
    static tBrightLight *aBrightLights; // static tBrightLight aBrightLights[32]
    static unsigned int &NumBrightLights;

    static void RenderOutGeometryBuffer();
    static void Render();
    static void RegisterOne(CVector posn, CVector top, CVector right, CVector at, unsigned char color, unsigned char arg5, unsigned char arg6, unsigned char arg7);
    static void Init();
};
