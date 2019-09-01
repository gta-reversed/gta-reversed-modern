#include "StdInc.h"

void CEventScanner::ScanForEvents(CPed* pPed)
{
    plugin::CallMethod<0x607E30, CEventScanner*, CPed*>(this, pPed);
}
