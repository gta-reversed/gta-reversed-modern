#include "StdInc.h"

void CEventVehicleDied::InjectHooks()
{
    RH_ScopedClass(CEventVehicleDied);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B0D10);
    RH_ScopedInstall(Clone_Reversed, 0x4B76D0);
    RH_ScopedInstall(AffectsPed_Reversed, 0x4B0E00);
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

// 0x4B0D10
CEventVehicleDied* CEventVehicleDied::Constructor(CVehicle* vehicle)
{
    this->CEventVehicleDied::CEventVehicleDied(vehicle);
    return this;
}

// 0x4B76D0
CEvent* CEventVehicleDied::Clone()
{
    return CEventVehicleDied::Clone_Reversed();
}

// 0x4B0E00
bool CEventVehicleDied::AffectsPed(CPed* ped)
{
    return CEventVehicleDied::AffectsPed_Reversed(ped);
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
