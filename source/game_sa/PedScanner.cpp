#include "StdInc.h"
#include "PedScanner.h"

// 0x5FFEF0
void CPedScanner::ScanForPedsInRange(const CPed& ped) {
    if (ped.IsAlive())
        CEntityScanner::ScanForEntitiesInRange(1, ped);
}
