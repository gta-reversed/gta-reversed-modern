#include "StdInc.h"
#include "VehiclePotentialCollisionScanner.h"

// 0x603720
void CVehiclePotentialCollisionScanner::ScanForVehiclePotentialCollisionEvents(const CPed& ped, CEntity** entities, size_t count) {
    plugin::CallMethod<0x603720, CVehiclePotentialCollisionScanner*, const CPed&, CEntity**, size_t>(this, ped, entities, count);
}

void CVehiclePotentialCollisionScanner::ResetTimer() {
    m_timer.SetAsOutOfTime();
}
