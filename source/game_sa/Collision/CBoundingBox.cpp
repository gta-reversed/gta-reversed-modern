#include "StdInc.h"

int32_t& numBBFailed = *(int32_t*)0xB71808;

CBoundingBox::CBoundingBox()
{
    m_vecMin.Set(1.0F, 1.0F, 1.0F);
    m_vecMax.Set(-1.0F, -1.0F, -1.0F);
}

CBoundingBox::CBoundingBox(CVector vecMin, CVector vecMax) {
    m_vecMin = vecMin;
    m_vecMax = vecMax;
}
