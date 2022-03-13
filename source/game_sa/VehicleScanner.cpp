#include "StdInc.h"

#include "VehicleScanner.h"

// 0x5FFE60
void CVehicleScanner::ScanForVehiclesInRange(const CPed& ped) {
    plugin::CallMethod<0x5FFE60, CVehicleScanner*, const CPed&>(this, ped);
}
