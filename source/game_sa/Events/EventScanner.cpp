#include "StdInc.h"

#include "EventScanner.h"

float& CPedAcquaintanceScanner::ms_fThresholdDotProduct = *(float*)0xC0B034;

void CEventScanner::ScanForEvents(CPed* ped)
{
    plugin::CallMethod<0x607E30, CEventScanner*, CPed*>(this, ped);
}

void CEventScanner::ScanForEventsNow(CPed* ped, bool bDontScan)
{
    plugin::CallMethod<0x6053D0, CEventScanner*, CPed*, bool>(this, ped, bDontScan);
}
