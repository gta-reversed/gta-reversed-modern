#include "StdInc.h"
#include "ObjectPotentialCollisionScanner.h"

void CObjectPotentialCollisionScanner::InjectHooks() {
    RH_ScopedClass(CObjectPotentialCollisionScanner);
    RH_ScopedCategory("Events/Scanners");

    RH_ScopedInstall(ScanForObjectPotentialCollisionEvents, 0x606890, { .reversed = false });
}

// 0x606890
void CObjectPotentialCollisionScanner::ScanForObjectPotentialCollisionEvents(const CPed& ped) {
    return plugin::CallMethodAndReturn<void, 0x606890, CObjectPotentialCollisionScanner*, const CPed&>(this, ped);
}
