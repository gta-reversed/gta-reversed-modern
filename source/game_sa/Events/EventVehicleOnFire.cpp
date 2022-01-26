#include "StdInc.h"

void CEventVehicleOnFire::InjectHooks()
{
    RH_ScopedClass(CEventVehicleOnFire);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B10C0);
    RH_ScopedInstall(AffectsPed_Reversed, 0x4B4FD0);
    RH_ScopedInstall(CloneEditable_Reversed, 0x4B7740);
}

CEventVehicleOnFire::CEventVehicleOnFire(CVehicle* vehicle)
{
    m_vehicle = vehicle;
    if (m_vehicle)
        m_vehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventVehicleOnFire::~CEventVehicleOnFire()
{
    if (m_vehicle)
        m_vehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventVehicleOnFire* CEventVehicleOnFire::Constructor(CVehicle* vehicle)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventVehicleOnFire*, 0x4B10C0, CEvent*, CVehicle*>(this, vehicle);
#else
    this->CEventVehicleOnFire::CEventVehicleOnFire(vehicle);
    return this;
#endif
}

bool CEventVehicleOnFire::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B4FD0, CEvent*, CPed*>(this, ped);
#else
    return CEventVehicleOnFire::AffectsPed_Reversed(ped);
#endif
}

CEventEditableResponse* CEventVehicleOnFire::CloneEditable()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventEditableResponse*, 0x4B7740, CEvent*>(this);
#else
    return CEventVehicleOnFire::CloneEditable_Reversed();
#endif
}

bool CEventVehicleOnFire::AffectsPed_Reversed(CPed* ped)
{
    if (m_vehicle) {
        if (!ped->m_pVehicle || !ped->bInVehicle || ped->m_pVehicle == m_vehicle) {
            if (!ped->IsPlayer() && ped->IsAlive()) {
                CPedGroup* pedGroup = CPedGroups::GetPedsGroup(ped);
                if (pedGroup && !pedGroup->GetMembership().IsLeader(ped)) {
                    if (ped->bInVehicle)
                        return false;
                }
                if (ped->bInVehicle)
                    return true;
                CVector distance = ped->GetPosition() - m_vehicle->GetPosition();
                return distance.SquaredMagnitude() <= 100.0f;
            }
        }
    }
    return false;
}

CEventEditableResponse* CEventVehicleOnFire::CloneEditable_Reversed()
{
    return new CEventVehicleOnFire(m_vehicle);
}
