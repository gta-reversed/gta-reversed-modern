#include "StdInc.h"

void CEventLeaderEnteredCarAsDriver::InjectHooks()
{
    ReversibleHooks::Install(0x48E1C0, &CEventLeaderEnteredCarAsDriver::Constructor);
    ReversibleHooks::Install(0x4B0EF0, &CEventLeaderEnteredCarAsDriver::AffectsPedGroup_Reversed);
}

void CEventLeaderExitedCarAsDriver::InjectHooks()
{
    ReversibleHooks::Install(0x4B8300, &CEventLeaderExitedCarAsDriver::Constructor);
    ReversibleHooks::Install(0x4B0F80, &CEventLeaderExitedCarAsDriver::AffectsPedGroup_Reversed);
}

void CEventLeaderQuitEnteringCarAsDriver::InjectHooks()
{
    ReversibleHooks::Install(0x63A110, &CEventLeaderQuitEnteringCarAsDriver::Constructor);
    ReversibleHooks::Install(0x4B1010, &CEventLeaderQuitEnteringCarAsDriver::AffectsPedGroup_Reversed);
}

void CEventAreaCodes::InjectHooks()
{
    ReversibleHooks::Install(0x4B2190, &CEventAreaCodes::Constructor);
    ReversibleHooks::Install(0x4B2270, &CEventAreaCodes::AffectsPed_Reversed);
    ReversibleHooks::Install(0x4B2350, &CEventAreaCodes::TakesPriorityOver_Reversed);
}

void CEventLeaderEntryExit::InjectHooks()
{
    ReversibleHooks::Install(0x43E1C0, &CEventLeaderEntryExit::Constructor);
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
        for (std::int32_t i = 0; i < TOTAL_PED_GROUP_FOLLOWERS; i++) {
            CPed* member = pedGroup->GetMembership().GetMember(i);
            if (member) {
                if (!member->bInVehicle
                    || member->m_pVehicle != m_vehicle
                    || member->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_LEAVE_CAR))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

CEventLeaderExitedCarAsDriver* CEventLeaderExitedCarAsDriver::Constructor()
{
    this->CEventLeaderExitedCarAsDriver::CEventLeaderExitedCarAsDriver();
    return this;
}

bool CEventLeaderExitedCarAsDriver::AffectsPedGroup(CPedGroup* pedGroup)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B0F80, CEventLeaderExitedCarAsDriver*, CPedGroup*>(this, pedGroup);
#else
    return CEventLeaderExitedCarAsDriver::AffectsPedGroup_Reversed(pedGroup);
#endif
}

bool CEventLeaderExitedCarAsDriver::AffectsPedGroup_Reversed(CPedGroup* pedGroup)
{
    for (std::int32_t i = 0; i < TOTAL_PED_GROUP_FOLLOWERS; i++) {
        CPedGroupMembership& memberShip = pedGroup->GetMembership();
        CPed* member = memberShip.GetMember(i);
        if (member) {
            if (member->m_pVehicle && member->bInVehicle && member->m_pVehicle == memberShip.GetLeader()->m_pVehicle)
                return true;
            if (member->GetIntelligence()->FindTaskByType(TASK_COMPLEX_ENTER_CAR_AS_PASSENGER)
                || member->GetIntelligence()->FindTaskByType(TASK_COMPLEX_ENTER_CAR_AS_PASSENGER_WAIT))
            {
                return true;
            }
        }
    }
    return false;
}

CEventLeaderQuitEnteringCarAsDriver* CEventLeaderQuitEnteringCarAsDriver::Constructor()
{
    this->CEventLeaderQuitEnteringCarAsDriver::CEventLeaderQuitEnteringCarAsDriver();
    return this;
}

bool CEventLeaderQuitEnteringCarAsDriver::AffectsPedGroup(CPedGroup* pedGroup)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B1010, CEventLeaderQuitEnteringCarAsDriver*, CPedGroup*>(this, pedGroup);
#else
    return CEventLeaderQuitEnteringCarAsDriver::AffectsPedGroup_Reversed(pedGroup);
#endif
}

bool CEventLeaderQuitEnteringCarAsDriver::AffectsPedGroup_Reversed(CPedGroup* pedGroup)
{
    auto oldEventGroupEvent = pedGroup->GetIntelligence().m_oldEventGroupEvent;
    if (oldEventGroupEvent) 
        return oldEventGroupEvent->m_event->GetEventType() == EVENT_LEADER_ENTERED_CAR_AS_DRIVER;
    return false;
}

CEventAreaCodes::CEventAreaCodes(CPed* ped)
{
    m_ped = ped;
    if (ped)
        ped->RegisterReference(reinterpret_cast<CEntity**>(&m_ped));
}

CEventAreaCodes::~CEventAreaCodes()
{
    if (m_ped)
        m_ped->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_ped));
}

CEventAreaCodes* CEventAreaCodes::Constructor(CPed* ped)
{
    this->CEventAreaCodes::CEventAreaCodes(ped);
    return this;
}

bool CEventAreaCodes::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B2270, CEventAreaCodes*, CPed*>(this, ped);
#else
    return CEventAreaCodes::AffectsPed_Reversed(ped);
#endif
}

bool CEventAreaCodes::TakesPriorityOver(const CEvent& refEvent)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B2350, CEventAreaCodes*, CEvent*>(this, refEvent);
#else
    return CEventAreaCodes::TakesPriorityOver_Reversed(refEvent);
#endif
}

bool CEventAreaCodes::AffectsPed_Reversed(CPed* ped)
{
    if (m_ped) {
        CPed* targetPed = nullptr;
        auto killPedOnFootTask = reinterpret_cast<CTaskComplexKillPedOnFoot*>(ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_KILL_PED_ON_FOOT));
        if (killPedOnFootTask) {
            targetPed = killPedOnFootTask->m_target;
            if (targetPed != m_ped) {
                auto arrestPedTask = reinterpret_cast<CTaskComplexArrestPed*>(ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_ARREST_PED));
                if (arrestPedTask)
                    targetPed = arrestPedTask->m_pedToArrest;
            }
        }
        if (targetPed == m_ped) {
            if (m_ped->GetIntelligence()->FindTaskByType(TASK_COMPLEX_GOTO_DOOR_AND_OPEN))
                return true;
            if (ped->m_pContactEntity && m_ped->m_pContactEntity) {
                if (ped->m_pContactEntity->m_nAreaCode == m_ped->m_pContactEntity->m_nAreaCode)
                    return false;
            }
            if (m_ped->IsAlive()
                && ped->IsAlive()
                && (!ped->m_pContactEntity || ped->m_pContactEntity->m_nAreaCode != AREA_CODE_13)
                && (!m_ped->m_pContactEntity || m_ped->m_pContactEntity->m_nAreaCode != AREA_CODE_13))
            {
                return true;
            }
        }
    }
    return false;
}

bool CEventAreaCodes::TakesPriorityOver_Reversed(const CEvent& refEvent)
{
    if (CEventHandler::IsTemporaryEvent(refEvent))
        return true;
    return CEvent::TakesPriorityOver(refEvent); 
}

CEventLeaderEntryExit* CEventLeaderEntryExit::Constructor(CPed* ped)
{
    this->CEventLeaderEntryExit::CEventLeaderEntryExit(ped);
    return this;
}
