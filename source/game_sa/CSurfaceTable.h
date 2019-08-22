#pragma once
#include "PluginBase.h"

class CSurfaceTable 
{
public:
    bool IsSprint(int surfaceNumber);
};

extern CSurfaceTable* g_surfaceInfos;