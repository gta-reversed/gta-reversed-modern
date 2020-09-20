#pragma once
#include "PluginBase.h"
enum ePedType : unsigned int;

class CPedType
{
public:
    static unsigned int GetPedFlag(ePedType pedType);
    static bool PoliceDontCareAboutCrimesAgainstPedType(ePedType pedType);
};
