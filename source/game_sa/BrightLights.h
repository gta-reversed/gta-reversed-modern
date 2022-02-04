/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"
#include "RGBA.h"

enum eBrightLightColor : uint8 {
    BRIGHTLIGHT_NONE         = 0,
    BRIGHTLIGHT_GREEN_BIG    = 1,
    BRIGHTLIGHT_YELLOW_BIG   = 2,
    BRIGHTLIGHT_RED_BIG      = 3,
    BRIGHTLIGHT_GREEN_SMALL  = 13,
    BRIGHTLIGHT_YELLOW_SMALL = 14,
    BRIGHTLIGHT_RED_SMALL    = 15
};

struct tBrightLight {
    CVector           m_vecPosition;
    CVector           m_vecRight;
    CVector           m_vecTop;
    CVector           m_vecAt;
    float             m_fDistanceToCamera;
    eBrightLightColor m_nColor;
    uint8             field_35;
    uint8             field_36;
    uint8             field_37;

    CRGBA GetColorRGBA() const;
    void  Render() const;
};
VALIDATE_SIZE(tBrightLight, 0x38);

constexpr auto MAX_NUM_BRIGHTLIGHTS{32u};

class CBrightLights {
public:
    static uint32& NumBrightLights;
    static tBrightLight (&aBrightLights)[MAX_NUM_BRIGHTLIGHTS];

public:
    static void InjectHooks();
        
    static void Init();
    static void RenderOutGeometryBuffer();
    static void Render();
    static void RegisterOne(CVector posn, CVector top, CVector right, CVector at, eBrightLightColor color, uint8 arg5, uint8 arg6, uint8 arg7);
};
