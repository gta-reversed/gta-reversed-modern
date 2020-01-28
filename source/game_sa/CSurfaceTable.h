#pragma once
#include "PluginBase.h"

class CColPoint;

enum eAdhesionGroup
{
    ADHESION_GROUP_RUBBER = 0,
    ADHESION_GROUP_HARD,
    ADHESION_GROUP_ROAD,
    ADHESION_GROUP_LOOSE,
    ADHESION_GROUP_SAND,
    ADHESION_GROUP_WET,
};

enum eFrictionEffect
{
    FRICTION_EFFECT_NONE = 0,
    FRICTION_EFFECT_SPARKS,
    FRICTION_EFFECT_MORE // not sure what this is, but it's probably not used
};

class CSurfaceTable 
{
public:
    bool IsSprint(int surfaceNumber);
    float GetFriction(CColPoint* pColPoint);
};