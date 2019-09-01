#include "StdInc.h"

void CEntityScanner::Clear()
{
    plugin::CallMethod<0x5FF9D0, CEntityScanner*>(this);
}

void CEntityScanner::ScanForEntitiesInRange(int arg2, CPed* pPed)
{
    plugin::CallMethod<0x5FFA20, CEntityScanner*, int, CPed*>(this, arg2, pPed);
}