#include "StdInc.h"

void CVehicleScanner::ScanForVehiclesInRange(CPed* pPed)
{
    plugin::CallMethod<0x5FFE60, CVehicleScanner*, CPed*>(this, pPed);
}