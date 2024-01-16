#include "StdInc.h"
#include "SexyPedScanner.h"

void CSexyPedScanner::InjectHooks() {
    RH_ScopedClass(CSexyPedScanner);
    RH_ScopedCategory("Events/Scanners");

    RH_ScopedInstall(ScanForSexyPedEvents, 0x603BF0, { .reversed = false });
}

// 0x603BF0
void CSexyPedScanner::ScanForSexyPedEvents(const CPed& ped, CPed** nearbyPeds, size_t numNearbyPeds) {
    return plugin::CallMethodAndReturn<void, 0x603BF0>(this, &ped, nearbyPeds, numNearbyPeds);
}
