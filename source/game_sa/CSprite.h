/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "RenderWare.h"

class CSprite
{
public:
    static void CSprite::InitSpriteBuffer();

	static void RenderOneXLUSprite(float x, float y, float z, float halfWidth, float halfHeight, 
		unsigned char red, unsigned char green, unsigned char blue, short alpha, float rhw, 
		unsigned char intensity, unsigned char udir, unsigned char vdir);
	static bool CalcScreenCoors(RwV3d const &posn, RwV3d *out, float *w, float *h, bool checkMaxVisible, bool checkMinVisible);
};
