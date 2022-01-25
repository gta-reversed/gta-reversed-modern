#include "StdInc.h"

CHudColours& HudColour = *reinterpret_cast<CHudColours*>(0xBAB22C);

void CHudColours::InjectHooks() {
    Install("CHudColours", "Constructor", 0x58FDA0, &CHudColours::Constructor);
    Install("CHudColours", "Destructor", 0x58FD90, &CHudColours::Destructor);
    Install("CHudColours", "SetRGBAValue", 0x58FD20, &CHudColours::SetRGBAValue);
    Install("CHudColours", "GetIntColour", 0x58FD50, &CHudColours::GetIntColour);
    Install("CHudColours", "GetRGB", 0x58FEA0, &CHudColours::GetRGB);
    Install("CHudColours", "GetRGBA", 0x58FEE0, &CHudColours::GetRGBA);
}

// 0x58FDA0
CHudColours::CHudColours() {
    SetRGBAValue(HUD_COLOUR_RED, 180, 25, 29, 255);
    SetRGBAValue(HUD_COLOUR_GREEN, 54, 104, 44, 255);
    SetRGBAValue(HUD_COLOUR_DARK_BLUE, 50, 60, 127, 255);
    SetRGBAValue(HUD_COLOUR_LIGHT_BLUE, 172, 203, 241, 255);
    SetRGBAValue(HUD_COLOUR_LIGHT_GRAY, 225, 225, 225, 255);
    SetRGBAValue(HUD_COLOUR_BLACK, 0, 0, 0, 255);
    SetRGBAValue(HUD_COLOUR_GOLD, 144, 98, 16, 255);
    SetRGBAValue(HUD_COLOUR_PURPLE, 168, 110, 252, 255);
    SetRGBAValue(HUD_COLOUR_DARK_GRAY, 150, 150, 150, 255);
    SetRGBAValue(HUD_COLOUR_DARK_RED, 104, 15, 17, 255);
    SetRGBAValue(HUD_COLOUR_DARK_GREEN, 38, 71, 31, 255);
    SetRGBAValue(HUD_COLOUR_CREAM, 226, 192, 99, 255);
    SetRGBAValue(HUD_COLOUR_NIGHT_BLUE, 74, 90, 107, 255);
    SetRGBAValue(HUD_COLOUR_BLUE, 20, 25, 200, 255);
    SetRGBAValue(HUD_COLOUR_YELLOW, 255, 255, 0, 255);
}

CHudColours* CHudColours::Constructor() {
    this->CHudColours::CHudColours();
    return this;
}

// 0x58FD90
CHudColours::~CHudColours() {
    // m_aColours[15] created on stack and should not be free.
}

CHudColours* CHudColours::Destructor() {
    this->CHudColours::~CHudColours();
    return this;
}

// Setup the color in color table. "color" parameter - index of color in the table.
// 0x58FD20
void CHudColours::SetRGBAValue(eHudColours colorIndex, uint8 red, uint8 green, uint8 blue, uint8 alpha) {
    m_aColours[colorIndex] = CRGBA(red, green, blue, alpha);
}

// Get color from color table as integer value. "color" parameter - index of color in the table.
// 0x58FD50
uint32 CHudColours::GetIntColour(eHudColours colorIndex) {
    return m_aColours[colorIndex].ToInt();
}

// Get color RGB and set alpha manually. "color" parameter - index of color in the table.
// 0x58FEA0
CRGBA CHudColours::GetRGB(eHudColours colorIndex) {
    return m_aColours[colorIndex];
}

// Get color RGBA. "color" parameter - index of color in the table.
// 0x58FEE0
CRGBA CHudColours::GetRGBA(eHudColours index, uint8 alpha) {
    auto color = m_aColours[index];
    return CRGBA(color.r, color.g, color.b, alpha);
}
