#pragma once
#include "CSurfaceTable.h"

class SurfaceInfos_c : public CSurfaceTable
{
public:
    int GetAdhesionGroup(int surfaceId);
    int GetFrictionEffect(int surfaceId);
};

extern SurfaceInfos_c* g_surfaceInfos;