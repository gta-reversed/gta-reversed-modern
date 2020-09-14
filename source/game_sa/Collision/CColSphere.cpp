#include "StdInc.h"

void CColSphere::InjectHooks()
{
    HookInstall(0x40FD10, &CColSphere::Set);
    HookInstall(0x40FF20, &CColSphere::IntersectRay);
    HookInstall(0x4100E0, &CColSphere::IntersectEdge);
    HookInstall(0x410040, &CColSphere::IntersectPoint);
}

void CColSphere::Set(float radius, CVector const& center, std::uint8_t material, std::uint8_t flags, std::uint8_t lighting)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethod<0x40FD10, CColSphere*, float, CVector const&, std::uint8_t, std::uint8_t, std::uint8_t>(this, radius, center, material, flags, lighting);
#else
    m_fRadius = radius;
    m_vecCenter = center;
    m_nMaterial = material;
    m_nFlags = flags;
    m_nLighting = lighting;
#endif
}

bool CColSphere::IntersectRay(CVector const& rayOrigin, CVector const& direction, CVector& intersectPoint1, CVector& intersectPoint2)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x40FF20, CColSphere*, CVector const&, CVector const&, CVector&, CVector&>(this, rayOrigin, direction, intersectPoint1, intersectPoint2);
#else
    CVector distance = rayOrigin - m_vecCenter;
    float b = 2.0f * DotProduct(direction, distance);
    float c = DotProduct(distance, distance) - m_fRadius * m_fRadius;
    float t0 = 0.0f, t1 = 0.0f;
    if (CGeneral::SolveQuadratic(1.0f, b, c, t0, t1)) {
        intersectPoint1 = (t0 * direction) + rayOrigin;
        intersectPoint2 = (t1 * direction) + rayOrigin;
        return true;
    }
    return false;
#endif
}

bool CColSphere::IntersectEdge(CVector const& startPoint, CVector const& endPoint, CVector& intersectPoint1, CVector& intersectPoint2)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4100E0, CColSphere*, CVector const&, CVector const&, CVector&, CVector&>(this, startPoint, endPoint, intersectPoint1, intersectPoint2);
#else
    CVector originCenterDistance = startPoint - m_vecCenter;
    CVector rayDirection = endPoint - startPoint;
    float rayLength = rayDirection.Magnitude();
    rayDirection.Normalise();
    float a = DotProduct(rayDirection, rayDirection);
    float b = 2.0f * DotProduct(originCenterDistance, rayDirection);
    float c = DotProduct(originCenterDistance, originCenterDistance) - m_fRadius * m_fRadius;
    float discriminant = b * b - 4.0f * a * c; // discriminant = b^2-4ac
    // discriminant == 0: the ray intersects one point on the sphere
    // discriminant > 0: the ray intersects two points on the sphere
    if (discriminant < 0.0f)
        return false;
    float discriminantSquareRoot = sqrt(discriminant);
    float numerator1 = (-b - discriminantSquareRoot) * 0.5f;
    float numerator2 = (discriminantSquareRoot - b) * 0.5f;
    if (numerator1 > rayLength || numerator2 < 0.0f)
        return false;
    intersectPoint2 = endPoint;
    if (numerator2 < rayLength)
        intersectPoint2 = (rayDirection * numerator2) + startPoint;
    intersectPoint1 = startPoint;
    if (numerator1 > 0.0f)
        intersectPoint1 = (rayDirection * numerator1) + startPoint;
    return true;
#endif
}

// used in CTaskComplexAvoidOtherPedWhileWandering::NearbyPedsInSphere
bool CColSphere::IntersectSphere(CColSphere const& right)
{
    CVector distance = m_vecCenter - right.m_vecCenter;
    return std::powf(m_fRadius + right.m_fRadius, 2.0f) > distance.SquaredMagnitude();
}

bool CColSphere::IntersectPoint(CVector const& point)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x410040, CColSphere*, CVector const&>(this, point);
#else
    CVector distance = m_vecCenter - point;
    return m_fRadius * m_fRadius > distance.SquaredMagnitude();
#endif
}

