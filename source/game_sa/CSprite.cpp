#include "StdInc.h"

void CSprite::RenderOneXLUSprite(float x, float y, float z, float halfWidth, float halfHeight,
    unsigned char red, unsigned char green, unsigned char blue,
    short alpha, float rhw, unsigned char intensity, unsigned char udir,
    unsigned char vdir)
{
    ((void(__cdecl*)(float, float, float, float, float, unsigned char, unsigned char, unsigned char,
        short, float, unsigned char, unsigned char, unsigned char))0x70D000)(x, y, z, halfWidth, halfHeight,
            red, green, blue, alpha, rhw, intensity, udir, vdir);
}
