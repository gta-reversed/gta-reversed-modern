#include "StdInc.h"

bool CPlantMgr::Initialise()
{
    return plugin::CallAndReturn<bool, 0x5DD910>();
}
