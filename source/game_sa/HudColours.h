/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CRGBA.h"

enum eHudColours : uint8 {
    HUD_COLOUR_RED,
    HUD_COLOUR_GREEN,
    HUD_COLOUR_DARK_BLUE,
    HUD_COLOUR_LIGHT_BLUE,
    HUD_COLOUR_LIGHT_GRAY,
    HUD_COLOUR_BLACK,
    HUD_COLOUR_GOLD,
    HUD_COLOUR_PURPLE,
    HUD_COLOUR_DARK_GRAY,
    HUD_COLOUR_DARK_RED,
    HUD_COLOUR_DARK_GREEN,
    HUD_COLOUR_CREAM,
    HUD_COLOUR_NIGHT_BLUE,
    HUD_COLOUR_BLUE,
    HUD_COLOUR_YELLOW,

    HUD_COLOUR_COUNT = 16,
};

class CHudColours {
public:
    CRGBA m_aColours[15];

public:
    static void InjectHooks();

    CHudColours();
    CHudColours* Constructor();

    ~CHudColours();
    CHudColours* Destructor();

    void SetRGBAValue(eHudColours colorIndex, uint8 red, uint8 green, uint8 blue, uint8 alpha);
    uint32 GetIntColour(eHudColours colorIndex);

    CRGBA GetRGB(eHudColours colorIndex);
    CRGBA GetRGBA(eHudColours index, uint8 alpha);
};

VALIDATE_SIZE(CHudColours, 0x3C);

extern CHudColours& HudColour;
