#include "StdInc.h"

void CEventLeaderEnteredCarAsDriver::InjectHooks()
{
    HookInstall(0x48E1C0, &CEventLeaderEnteredCarAsDriver::Constructor);
    HookInstall(0x4B0EF0, &CEventLeaderEnteredCarAsDriver::AffectsPedGroup_Reversed);
}

CEventLeaderEnteredCarAsDriver::CEventLeaderEnteredCarAsDriver(CVehicle* vehicle)
{
    m_vehicle = vehicle;
    if (vehicle)
        vehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventLeaderEnteredCarAsDriver::~CEventLeaderEnteredCarAsDriver()
{
    if (m_vehicle)
        m_vehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventLeaderEnteredCarAsDriver* CEventLeaderEnteredCarAsDriver::Constructor(CVehicle* vehicle)
{
    this->CEventLeaderEnteredCarAsDriver::CEventLeaderEnteredCarAsDriver(vehicle);
    return this;
}

bool CEventLeaderEnteredCarAsDriver::AffectsPedGroup(CPedGroup* pedGroup)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B0EF0, CEventLeaderEnteredCarAsDriver*, CPedGroup*>(this, pedGroup);
#else
    return CEventLeaderEnteredCarAsDriver::AffectsPedGroup_Reversed(pedGroup);
#endif
}

bool CEventLeaderEnteredCarAsDriver::AffectsPedGroup_Reversed(CPedGroup* pedGroup)
{
    if (m_vehicle && pedGroup->m_bMembersEnterLeadersVehicle) {
        for (std::int32_t i = 0; i < 7; i++) {
            CPed* member = pedGroup->GetMembership().GetMember(i);
            if (member) {
                if (member->bInVehicle && member->m_pVehicle == m_vehicle &&
                    !member->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_LEAVE_CAR))
                    return true;
            }
        }
    }
    return false;
}

