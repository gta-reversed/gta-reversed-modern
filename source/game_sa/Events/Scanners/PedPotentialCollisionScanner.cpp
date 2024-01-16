#include "StdInc.h"
#include "PedPotentialCollisionScanner.h"

void CPedPotentialCollisionScanner::InjectHooks() {
    RH_ScopedClass(CPedPotentialCollisionScanner);
    RH_ScopedCategory("Events/Scanners");

    RH_ScopedGlobalInstall(ScanForPedPotentialCollisionEvents, 0x606580, { .reversed = false });
}

// 0x606580
void CPedPotentialCollisionScanner::ScanForPedPotentialCollisionEvents(const CPed& a1, CPed* a2) {
    return plugin::CallAndReturn<void, 0x606580, const CPed&, CPed*>(a1, a2);
}
