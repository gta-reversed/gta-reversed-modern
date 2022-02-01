#include "StdInc.h"

#include "PedStuckChecker.h"

bool CPedStuckChecker::TestPedStuck(CPed* pPed, CEventGroup* pEventGroup)
{
    return plugin::CallMethodAndReturn<bool, 0x602C00, CPedStuckChecker*, CPed*, CEventGroup*>(this, pPed, pEventGroup);
}
