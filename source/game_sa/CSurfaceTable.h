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

class CSurfaceTable 
{
public:
    bool IsSprint(int surfaceNumber);
    float GetFriction(CColPoint* pColPoint);
};