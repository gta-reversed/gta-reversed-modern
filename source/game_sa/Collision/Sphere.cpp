#include "StdInc.h"
#include "Sphere.h"

void CSphere::Set(float radius, CVector const& center) {
    m_fRadius = radius;
    m_vecCenter = center;
}
