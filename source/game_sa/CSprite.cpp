#include "StdInc.h"

void CSprite::InitSpriteBuffer()
{
    plugin::Call<0x70CFB0>();
}

void CSprite::RenderOneXLUSprite(float x, float y, float z, float halfWidth, float halfHeight,
    uint8 red, uint8 green, uint8 blue,
    int16 alpha, float rhw, uint8 intensity, uint8 udir,
    uint8 vdir)
{
    ((void(__cdecl*)(float, float, float, float, float, uint8, uint8, uint8,
        int16, float, uint8, uint8, uint8))0x70D000)(x, y, z, halfWidth, halfHeight,
            red, green, blue, alpha, rhw, intensity, udir, vdir);
}

bool CSprite::CalcScreenCoors(RwV3d const& posn, RwV3d* out, float* w, float* h, bool checkMaxVisible, bool checkMinVisible)
{
    return ((bool(__cdecl*)(RwV3d const&, RwV3d *, float*, float*, bool, bool))0x70CE30)(posn, out, w, h, checkMaxVisible, checkMinVisible);
}
