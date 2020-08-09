#pragma once

class CVector;
class CEntity;
class CPed;
class CEntity;

class CPedGeometryAnalyser
{
public:
    static bool IsInAir(CPed* ped);
    static std::int32_t ComputeEntityHitSide(CVector const& point, CEntity const& entity);
    static std::int32_t ComputeEntityHitSide(CPed const& ped, CEntity const& entity);
    static void ComputeEntityBoundingBoxPlanes(float zPos, CEntity& entity, CVector* planes, float* planes_D);
    static void ComputeEntityBoundingBoxPlanesUncached(float zPos, CVector const* corners, CVector* planes, float* planes_D);
};
