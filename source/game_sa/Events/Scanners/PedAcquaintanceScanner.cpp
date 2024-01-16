#include "StdInc.h"
#include "PedAcquaintanceScanner.h"

void CPedAcquaintanceScanner::InjectHooks() {
    RH_ScopedClass(CPedAcquaintanceScanner);
    RH_ScopedCategory("Events/Scanners");

    RH_ScopedInstall(CanJoinLARiot, 0x603AF0, { .reversed = false });
    RH_ScopedInstall(IsScanPermitted, 0x603A30, { .reversed = false });
    RH_ScopedInstall(AddAcquaintanceEvent, 0x606BA0, { .reversed = false });
    RH_ScopedInstall(ScanAcquaintanceTypes, 0x607560, { .reversed = false });
    RH_ScopedInstall(FindClosestAcquaintance, 0x607A90, { .reversed = false });
    RH_ScopedInstall(ScanForPedAcquaintanceEvents, 0x607D80, { .reversed = false });
}

// 0x603AF0
bool CPedAcquaintanceScanner::CanJoinLARiot(const CPed* ped, const CPed* otherPed) {
    return plugin::CallAndReturn<bool, 0x603AF0, const CPed*, const CPed*>(ped, otherPed);
}

// 0x603A30
bool CPedAcquaintanceScanner::IsScanPermitted(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x603A30, CPedAcquaintanceScanner*, CPed*>(this, ped);
}

// 0x606BA0
bool CPedAcquaintanceScanner::AddAcquaintanceEvent(const CPed* ped, const int32 acquaintanceType, CPed* acquaintancePed) {
    return plugin::CallMethodAndReturn<bool, 0x606BA0, CPedAcquaintanceScanner*, const CPed*, const int32, CPed*>(this, ped, acquaintanceType, acquaintancePed);
}

// 0x607560
int32 CPedAcquaintanceScanner::ScanAcquaintanceTypes(const CPed* ped, const int32 acquaintanceScanTypeExclusive, const int32 addedType, CPed* otherPed, CPed** outAcquaintancePed, int32* outAcquaintancePedScanType) {
    return plugin::CallMethodAndReturn<int32, 0x607560, CPedAcquaintanceScanner*, const CPed*, const int32, const int32, CPed*, CPed**, int32*>(this, ped, acquaintanceScanTypeExclusive, addedType, otherPed, outAcquaintancePed, outAcquaintancePedScanType);
}

// 0x607A90
void CPedAcquaintanceScanner::FindClosestAcquaintance(CPed& ped, int32 acquaintanceScanTypeExclusive, CEntity** outNearbyPeds, int32 maxNumPeds, CPed*& outAcquaintancePed, int32& outAcquaintancePedScanType) {
    return plugin::CallMethodAndReturn<void, 0x607A90, CPedAcquaintanceScanner*, CPed&, int32, CEntity**, int32, CPed*&, int32&>(this, ped, acquaintanceScanTypeExclusive, outNearbyPeds, maxNumPeds, outAcquaintancePed, outAcquaintancePedScanType);
}

// 0x607D80
void CPedAcquaintanceScanner::ScanForPedAcquaintanceEvents(CPed& ped, CEntity** outNearbyPeds, int32 maxNumPeds) {
    return plugin::CallMethodAndReturn<void, 0x607D80, CPedAcquaintanceScanner*, CPed&, CEntity**, int32>(this, ped, outNearbyPeds, maxNumPeds);
}
