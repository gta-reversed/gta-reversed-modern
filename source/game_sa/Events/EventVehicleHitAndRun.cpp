#include "StdInc.h"

#include "EventVehicleHitAndRun.h"

void CEventVehicleHitAndRun::InjectHooks()
{
    RH_ScopedClass(CEventVehicleHitAndRun);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AE990);
    RH_ScopedVirtualInstall(Clone, 0x4B7100);
    RH_ScopedVirtualInstall(ReportCriminalEvent, 0x4B27D0);
}

CEventVehicleHitAndRun::CEventVehicleHitAndRun(CPed* victim, CVehicle* vehicle)
{
    m_victim = victim;
    m_vehicle = vehicle;
    m_vehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_vehicle)); // *
    m_victim->RegisterReference(reinterpret_cast<CEntity**>(&m_victim));   // ** todo: possible nullptr
}

CEventVehicleHitAndRun::~CEventVehicleHitAndRun()
{
    CEntity::SafeCleanUpRef(m_vehicle);
    CEntity::SafeCleanUpRef(m_victim);
}

// 0x4AE990
CEventVehicleHitAndRun* CEventVehicleHitAndRun::Constructor(CPed* victim, CVehicle* vehicle)
{
    this->CEventVehicleHitAndRun::CEventVehicleHitAndRun(victim, vehicle);
    return this;
}

// 0x4B7100
CEvent* CEventVehicleHitAndRun::Clone()
{
    return CEventVehicleHitAndRun::Clone_Reversed();
}

// 0x4B27D0
void CEventVehicleHitAndRun::ReportCriminalEvent(CPed* ped)
{
    return CEventVehicleHitAndRun::ReportCriminalEvent_Reversed(ped);
}

CEvent* CEventVehicleHitAndRun::Clone_Reversed()
{
    return new CEventVehicleHitAndRun(m_victim, m_vehicle);
}

void CEventVehicleHitAndRun::ReportCriminalEvent_Reversed(CPed* ped)
{
    if (IsCriminalEvent()) {
        if (m_victim->m_nPedType == PED_TYPE_COP)
            FindPlayerWanted()->RegisterCrime(eCrimeType::CRIME_KILL_COP_PED_WITH_CAR, m_vehicle->GetPosition(), m_vehicle->m_pDriver, false);
        else
            FindPlayerWanted()->RegisterCrime(eCrimeType::CRIME_KILL_PED_WITH_CAR, m_vehicle->GetPosition(), m_vehicle->m_pDriver, false);
    }
}
