/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CVector.h"

enum eBrightLightColor : uint8 {
    BRIGHTLIGHT_GREEN_BIG = 1,
    BRIGHTLIGHT_YELLOW_BIG = 2,
    BRIGHTLIGHT_RED_BIG = 3,
    BRIGHTLIGHT_GREEN_SMALL = 13,
    BRIGHTLIGHT_YELLOW_SMALL = 14,
    BRIGHTLIGHT_RED_SMALL = 15
};

struct tBrightLight {
    CVector m_vecPosition;
    CVector m_vecRight;
    CVector m_vecTop;
    CVector m_vecAt;
    float m_fDistanceToCamera;
    eBrightLightColor m_nColor; // see eBrightLightColor
    char field_35;
    char field_36;
    char field_37;
};
VALIDATE_SIZE(tBrightLight, 0x38);

constexpr auto MAX_NUM_BRIGHTLIGHTS{32u};

class CBrightLights {
public:
    static int32_t& NumBrightLights;
    static tBrightLight (&aBrightLights)[MAX_NUM_BRIGHTLIGHTS];

public:
    static void InjectHooks();
        
    static void Init();
    static void RenderOutGeometryBuffer();
    static void Render();
    static void RegisterOne(CVector posn, CVector top, CVector right, CVector at, uint8_t color, uint8_t arg5, uint8_t arg6, uint8_t arg7);
};
