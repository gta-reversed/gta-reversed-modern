#include "StdInc.h"
#include "Sphere.h"

// 0x40FCF0
void CSphere::Set(float radius, const CVector& center) {
    m_fRadius = radius;
    m_vecCenter = center;
}
