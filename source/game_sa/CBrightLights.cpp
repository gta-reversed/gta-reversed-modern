#include "StdInc.h"

void CBrightLights::RenderOutGeometryBuffer()
{
    plugin::Call<0x722150>();
}

void CBrightLights::RegisterOne(CVector posn, CVector top, CVector right, CVector at, unsigned char color, unsigned char arg5, unsigned char arg6, unsigned char arg7)
{
    plugin::Call<0x724770, CVector, CVector, CVector, CVector, unsigned char, unsigned char, unsigned char, unsigned char>(posn, top, right, at, color, arg5, arg6, arg7);
}
