#include "StdInc.h"

void CShinyTexts::RegisterOne(CVector cornerAA, CVector cornerBA, CVector cornerBB, CVector cornerAB, float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, float maxDistance)
{
    plugin::Call<0x724B60, CVector, CVector, CVector, CVector, float, float, float, float, float, float, float, float, unsigned char, unsigned char, unsigned char, unsigned char, float >
        (cornerAA, cornerBA, cornerBB, cornerAB, u1, v1, u2, v2, u3, v3, u4, v4, red, green, blue, alpha, maxDistance);
}
