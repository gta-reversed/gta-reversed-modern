#include "StdInc.h"

int32_t& gBuildings = *(int32_t*)0xB71804;

bool IsBuildingPointerValid(CBuilding* pBuilding)
{
    return plugin::CallAndReturn<bool, 0x4040E0, CBuilding*>(pBuilding);
}
