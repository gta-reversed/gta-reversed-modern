/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CRGBA.h"

enum eHudColours
{
	HUD_COLOUR_RED,
	HUD_COLOUR_GREEN,
	HUD_COLOUR_BLUEDARK,
	HUD_COLOUR_BLUELIGHT,
	HUD_COLOUR_WHITE,
	HUD_COLOUR_BLACK,
	HUD_COLOUR_ORANGE,
	HUD_COLOUR_PURPLE,
	HUD_COLOUR_GREY,
	HUD_COLOUR_REDDARK,
	HUD_COLOUR_GREENDARK,
	HUD_COLOUR_ORANGELIGHT,
	HUD_COLOUR_GREYDARK,
	HUD_COLOUR_BLUE,
	HUD_COLOUR_YELLOW,
	HUD_COLOUR_NUM_COLOURS
};


class  CHudColour
{
public:
	unsigned char red, green, blue, alpha;
};


VALIDATE_SIZE(CHudColour, 4);


class  CHudColours
{
public:
	CHudColour m_aColours[15];

	CHudColours();
	~CHudColours();
	// setup the color in color table. "color" parameter - index of color in the table, see eHudColours 
	// enum.
	void SetRGBAValue(unsigned char color, unsigned char red, unsigned char green, unsigned char blue,
		unsigned char alpha);
	// get color from color table as integer value. "color" parameter - index of color in the table, 
	// see eHudColours enum.
	unsigned int GetIntColour(unsigned char color);
	// get color RGB and set alpha manually. "color" parameter - index of color in the table, see 
	// eHudColours enum.
	CRGBA GetRGB(unsigned char color, unsigned char alpha);
	// get color RGBA. "color" parameter - index of color in the table, see eHudColours enum.
	CRGBA GetRGBA(unsigned char color);
};


VALIDATE_SIZE(CHudColours, 0x3C);

extern  CHudColours &HudColour;