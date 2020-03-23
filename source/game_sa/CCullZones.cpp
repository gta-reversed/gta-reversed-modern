#include "StdInc.h"

bool CCullZones::DoExtraAirResistanceForPlayer()
{
    return plugin::CallAndReturn<bool, 0x72DDD0>();
}