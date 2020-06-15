#include "StdInc.h"

void CPedGeometryAnalyser::ComputeEntityBoundingBoxPlanes(float zPos, CEntity& entity, CVector* planes, float* planesDot)
{
    plugin::Call<0x5F3660, float, CEntity&, CVector*, float*>(zPos, entity, planes, planesDot);
}

void CPedGeometryAnalyser::ComputeEntityBoundingBoxPlanesUncached(float zPos, CVector const* corners, CVector* planes, float* planesDot)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x5F1670, float, CVector const*, CVector*, float*>(zPos, corners, planes, planesDot);
#else
    CVector const* corner2 = &corners[3];
    for (std::int32_t i = 0; i < 4; i++) {
        CVector const& corner = corners[i];
        CVector& plane = planes[i];
        CVector direction = corner - *corner2;
        direction.Normalise();
        plane.x = direction.y;
        plane.y = -direction.x;
        plane.z = 0.0f;
        planesDot[i] = -DotProduct(plane, *corner2);
        corner2 = &corner;
    }
#endif
}
