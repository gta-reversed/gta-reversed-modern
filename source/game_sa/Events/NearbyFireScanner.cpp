#include "StdInc.h"
#include "NearbyFireScanner.h"

void CNearbyFireScanner::InjectHooks() {
    RH_ScopedClass(CNearbyFireScanner);
    RH_ScopedCategory("Events/Scanners");

    RH_ScopedInstall(ScanForNearbyFires, 0x603E70, { .reversed = false });
}

// 0x603E70
void CNearbyFireScanner::ScanForNearbyFires(const CPed& ped) {
    return plugin::CallMethodAndReturn<void, 0x603E70, CNearbyFireScanner*, const CPed&>(this, ped);
}
