#pragma once
#include "PluginBase.h"

class CColPoint;

class CSurfaceTable 
{
public:
    bool IsSprint(int surfaceNumber);
    float GetFriction(CColPoint* pColPoint);
};

extern CSurfaceTable* g_surfaceInfos;