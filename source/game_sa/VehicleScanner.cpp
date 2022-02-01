#include "StdInc.h"

#include "VehicleScanner.h"

void CVehicleScanner::ScanForVehiclesInRange(CPed* ped)
{
    plugin::CallMethod<0x5FFE60, CVehicleScanner*, CPed*>(this, ped);
}
