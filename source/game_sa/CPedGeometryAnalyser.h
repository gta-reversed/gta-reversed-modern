#pragma once

class CVector;
class CEntity;

class CPedGeometryAnalyser
{
public:
    static void ComputeEntityBoundingBoxPlanes(float zPos, CEntity& entity, CVector* planes, float* planesDot);
    static void ComputeEntityBoundingBoxPlanesUncached(float zPos, CVector const* corners, CVector* planes, float* planesDot);
};
