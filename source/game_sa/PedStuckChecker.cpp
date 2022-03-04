#include "StdInc.h"

#include "PedStuckChecker.h"

bool CPedStuckChecker::TestPedStuck(CPed* ped, CEventGroup* eventGroup)
{
    return plugin::CallMethodAndReturn<bool, 0x602C00, CPedStuckChecker*, CPed*, CEventGroup*>(this, ped, eventGroup);
}
