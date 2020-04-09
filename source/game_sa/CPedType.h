#pragma once
#include "PluginBase.h"
#include "ePedType.h"

class CPedType
{
public:
    static unsigned int GetPedFlag(ePedType pedType);
    static bool PoliceDontCareAboutCrimesAgainstPedType(ePedType pedType);
};