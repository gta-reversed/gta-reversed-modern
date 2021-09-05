/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"

class CSprite {
public:
    static void InitSpriteBuffer();

    static void RenderOneXLUSprite(float x, float y, float z, float halfWidth, float halfHeight, uint8 red, uint8 green, uint8 blue, int16 alpha, float rhw, uint8 intensity,
                                   uint8 udir, uint8 vdir);
    static bool CalcScreenCoors(RwV3d const& posn, RwV3d* out, float* w, float* h, bool checkMaxVisible, bool checkMinVisible);
};
