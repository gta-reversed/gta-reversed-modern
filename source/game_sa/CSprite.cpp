#include "StdInc.h"

void CSprite::InitSpriteBuffer()
{
    plugin::Call<0x70CFB0>();
}

void CSprite::RenderOneXLUSprite(float x, float y, float z, float halfWidth, float halfHeight,
    unsigned char red, unsigned char green, unsigned char blue,
    short alpha, float rhw, unsigned char intensity, unsigned char udir,
    unsigned char vdir)
{
    ((void(__cdecl*)(float, float, float, float, float, unsigned char, unsigned char, unsigned char,
        short, float, unsigned char, unsigned char, unsigned char))0x70D000)(x, y, z, halfWidth, halfHeight,
            red, green, blue, alpha, rhw, intensity, udir, vdir);
}

bool CSprite::CalcScreenCoors(RwV3d const& posn, RwV3d* out, float* w, float* h, bool checkMaxVisible, bool checkMinVisible)
{
    return ((bool(__cdecl*)(RwV3d const&, RwV3d *, float*, float*, bool, bool))0x70CE30)(posn, out, w, h, checkMaxVisible, checkMinVisible);
}
