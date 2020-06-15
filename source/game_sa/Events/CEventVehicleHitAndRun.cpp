#include "StdInc.h"

void CEventVehicleHitAndRun::InjectHooks()
{
    HookInstall(0x4AE990, &CEventVehicleHitAndRun::Constructor);
    HookInstall(0x4B7100, &CEventVehicleHitAndRun::Clone_Reversed);
    HookInstall(0x4B27D0, &CEventVehicleHitAndRun::ReportCriminalEvent_Reversed);
}

CEventVehicleHitAndRun::CEventVehicleHitAndRun(CPed* victim, CVehicle* vehicle)
{
    m_victim = victim;
    m_vehicle = vehicle;
    m_vehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_vehicle));
    m_victim->RegisterReference(reinterpret_cast<CEntity**>(&m_victim));
}

CEventVehicleHitAndRun::~CEventVehicleHitAndRun()
{
    if (m_vehicle)
        m_vehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_vehicle));
    if (m_victim)
        m_victim->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_victim));
}

CEventVehicleHitAndRun* CEventVehicleHitAndRun::Constructor(CPed* victim, CVehicle* vehicle)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventVehicleHitAndRun*, 0x4AE990, CEvent*, CPed*, CVehicle*>(this, victim, vehicle);
#else
    this->CEventVehicleHitAndRun::CEventVehicleHitAndRun(victim, vehicle);
    return this;
#endif
}

CEvent* CEventVehicleHitAndRun::Clone()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEvent*, 0x4B7100, CEvent*>(this);
#else
    return CEventVehicleHitAndRun::Clone_Reversed();
#endif
}

void CEventVehicleHitAndRun::ReportCriminalEvent(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethod<0x4B27D0, CEvent*, CPed*>(this, ped);
#else
    return CEventVehicleHitAndRun::ReportCriminalEvent_Reversed(ped);
#endif
}

CEvent* CEventVehicleHitAndRun::Clone_Reversed()
{
    return new CEventVehicleHitAndRun(m_victim, m_vehicle);
}

void CEventVehicleHitAndRun::ReportCriminalEvent_Reversed(CPed* ped)
{
    if (IsCriminalEvent()) {
        if (m_victim->m_nPedType == PED_TYPE_COP)
            FindPlayerWanted(-1)->RegisterCrime(eCrimeType::CRIME_KILL_COP_PED_WITH_CAR, m_vehicle->GetPosition(), m_vehicle->m_pDriver, false);
        else
            FindPlayerWanted(-1)->RegisterCrime(eCrimeType::CRIME_KILL_PED_WITH_CAR, m_vehicle->GetPosition(), m_vehicle->m_pDriver, false);
    }
}
