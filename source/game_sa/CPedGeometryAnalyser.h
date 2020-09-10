#pragma once
#include "PluginBase.h"

class CVector;
class CEntity;
class CPed;
class CEntity;

class CPointRoute
{
public:
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
};

VALIDATE_SIZE(CPointRoute, 0x64);

class CPedGeometryAnalyser
{
public:
    static bool IsInAir(CPed* ped);
    static std::int32_t ComputeEntityHitSide(CVector const& point, CEntity const& entity);
    static std::int32_t ComputeEntityHitSide(CPed const& ped, CEntity const& entity);
    static void ComputeEntityBoundingBoxPlanes(float zPos, CEntity& entity, CVector* planes, float* planes_D);
    static void ComputeEntityBoundingBoxPlanesUncached(float zPos, CVector const* corners, CVector* planes, float* planes_D);
    static std::int32_t ComputeEntityHitSide(CVector* point, CEntity* entity);
    static std::int8_t ComputeClosestSurfacePoint(CPed* ped, CEntity* entity, CVector* point);
    static std::int32_t ComputeEntityHitSide(CPed* ped, CEntity* entity);
};
