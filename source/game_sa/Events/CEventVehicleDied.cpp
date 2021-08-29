#include "StdInc.h"

void CEventVehicleDied::InjectHooks()
{
    ReversibleHooks::Install("CEventVehicleDied", "Constructor", 0x4B0D10, &CEventVehicleDied::Constructor);
    ReversibleHooks::Install("CEventVehicleDied", "Clone_Reversed", 0x4B76D0, &CEventVehicleDied::Clone_Reversed);
    ReversibleHooks::Install("CEventVehicleDied", "AffectsPed_Reversed", 0x4B0E00, &CEventVehicleDied::AffectsPed_Reversed);
}

CEventVehicleDied::CEventVehicleDied (CVehicle* vehicle)
{
    m_vehicle = vehicle;
    m_IsOccupantLeavingCar = false;
    m_vehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventVehicleDied::~CEventVehicleDied ()
{
    if (m_vehicle)
        m_vehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventVehicleDied* CEventVehicleDied::Constructor(CVehicle* vehicle)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventVehicleDied*, 0x4B0D10, CEvent*, CVehicle*>(this, vehicle);
#else
    this->CEventVehicleDied::CEventVehicleDied(vehicle);
    return this;
#endif
}

CEvent* CEventVehicleDied::Clone()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEvent*, 0x4B76D0, CEvent*>(this);
#else
    return CEventVehicleDied::Clone_Reversed();
#endif
}

bool CEventVehicleDied::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B0E00, CEvent*, CPed*>(this, ped);
#else
    return CEventVehicleDied::AffectsPed_Reversed(ped);
#endif
}

CEvent* CEventVehicleDied::Clone_Reversed()
{
    return new CEventVehicleDied(m_vehicle);
}

bool CEventVehicleDied::AffectsPed_Reversed(CPed* ped)
{
    if (ped->IsAlive() && !m_IsOccupantLeavingCar) {
        CTask* pTaskComplexLeaveCar = ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_LEAVE_CAR);
        m_IsOccupantLeavingCar = pTaskComplexLeaveCar ? true : false;
        if ((m_IsOccupantLeavingCar || ped->bInVehicle) && m_vehicle)
            return ped->m_pVehicle == m_vehicle;
    }
    return false;
}
