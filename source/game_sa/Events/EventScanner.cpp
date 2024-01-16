#include "StdInc.h"

#include "EventScanner.h"
#include "PedPotentialCollisionScanner.h"

void CEventScanner::InjectHooks() {
    RH_ScopedClass(CEventScanner);
    RH_ScopedCategory("Events/Scanners");

    RH_ScopedInstall(Constructor, 0x605300);

    RH_ScopedInstall(ScanForEventsNow, 0x6053D0);
    RH_ScopedInstall(ScanForEvents, 0x607E30);
}

// 0x605300
CEventScanner::CEventScanner() :
    m_NextScanTime{CTimer::GetTimeInMS() + CGeneral::GetRandomNumberInRange<uint32>(3000)}   
{
    m_AttractorScanner.Clear();
}

void CEventScanner::Clear() {
    m_AttractorScanner.Clear();
}

// 0x607E30
void CEventScanner::ScanForEvents(CPed& ped) {
    if (CTimer::GetTimeInMS() <= m_NextScanTime) {
        return;
    }
    const auto intel = ped.GetIntelligence();

    m_VehCollisionScanner.ScanForVehiclePotentialCollisionEvents(ped, intel->GetVehicleScanner().GetEntitiesPtr(), CEntityScanner::MAX_ENTITIES);
    CPedPotentialCollisionScanner::ScanForPedPotentialCollisionEvents(ped, intel->GetPedScanner().GetClosestPedInRange());
    m_ObjCollisionScanner.ScanForObjectPotentialCollisionEvents(ped);
    m_AcquaintanceScanner.
    m_AttractorScanner.ScanForAttractorsInRange(ped);
    m_FireScanner.ScanForNearbyFires(ped);
    m_SexyPedScanner
}

// 0x6053D0
void CEventScanner::ScanForEventsNow(const CPed& ped, bool bDontScan) {
    if (bDontScan) {
        return;
    }

    m_VehCollisionScanner.ResetTimer();
    m_VehCollisionScanner.ScanForVehiclePotentialCollisionEvents(ped, ped.GetIntelligence()->GetVehicleEntities(), CEntityScanner::MAX_ENTITIES);
}
