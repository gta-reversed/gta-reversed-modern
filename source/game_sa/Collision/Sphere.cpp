#include "StdInc.h"

#include "Sphere.h"

// 0x40FCF0
void CSphere::Set(float radius, const CVector& center) {
    m_fRadius = radius;
    m_vecCenter = center;
}

/*!
* @notsa
*/
bool CSphere::IsPointWithin(const CVector& p) const {
    return (p - m_vecCenter).SquaredMagnitude() <= m_fRadius * m_fRadius;
}
