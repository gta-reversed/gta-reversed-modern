#pragma once

#include "TaskTimer.h"
#include "Ped.h"

class CEntity;
class CPed;

class CPedAcquaintanceScanner {
public:
    static inline auto& ms_iAcquaintanceScanPeriod            = StaticRef<int32, 0x8D2358>();
    static inline auto& ms_iAcquaintanceLatencyPeriodDefinite = StaticRef<int32, 0x8D235C>();
    static inline auto& ms_iAcquaintanceLatencyPeriodMaybe    = StaticRef<int32, 0x8D2360>();
    static inline auto& ms_fThresholdDotProduct               = StaticRef<float, 0xC0B034>();

public:
    static void InjectHooks();

    static bool CanJoinLARiot(const CPed* ped, const CPed* otherPed);

    bool IsScanPermitted(CPed * ped);
    bool AddAcquaintanceEvent(const CPed * ped, const int32 acquaintanceType, CPed * acquaintancePed);
    int32 ScanAcquaintanceTypes(const CPed * ped, const int32 acquaintanceScanTypeExclusive, const int32 addedType, CPed * otherPed, CPed ** outAcquaintancePed, int32 * outAcquaintancePedScanType);
    void FindClosestAcquaintance(CPed & ped, int32 acquaintanceScanTypeExclusive, CEntity ** outNearbyPeds, int32 maxNumPeds, CPed*& outAcquaintancePed, int32 & outAcquaintancePedScanType);
    void ScanForPedAcquaintanceEvents(CPed & ped, CEntity ** outNearbyPeds, int32 maxNumPeds);

    void SetThreatScannerActivationState(bool bActivatedEverywhere, bool bActivatedInVehicle, bool bActivatedDuringScriptCommands);

private:
    CTaskTimer m_timer{};
    bool       m_bActivatedEverywhere{};
    bool       m_bActivatedInVehicle{};
    bool       m_bActivatedDuringScriptCommands{};
};
VALIDATE_SIZE(CPedAcquaintanceScanner, 0x10);
