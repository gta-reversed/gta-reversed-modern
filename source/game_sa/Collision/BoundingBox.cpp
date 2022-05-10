#include "StdInc.h"

#include "BoundingBox.h"

int32& numBBFailed = *(int32*)0xB71808;

CBoundingBox::CBoundingBox()
{
    m_vecMin.Set(1.0F, 1.0F, 1.0F);
    m_vecMax.Set(-1.0F, -1.0F, -1.0F);
}

CBoundingBox::CBoundingBox(CVector vecMin, CVector vecMax) {
    m_vecMin = vecMin;
    m_vecMax = vecMax;
}

// 0x49C300
bool CBoundingBox::IsPointWithin(const CVector& point) const {
    return point.x >= m_vecMin.x
        && point.y >= m_vecMin.y
        && point.z >= m_vecMin.z
        && point.x <= m_vecMax.x
        && point.y <= m_vecMax.y
        && point.z <= m_vecMax.z;
}

// 0x470100
void CBoundingBox::SetMinMax(CVector min, CVector max) {
    m_vecMin = min;
    m_vecMax = max;
}
