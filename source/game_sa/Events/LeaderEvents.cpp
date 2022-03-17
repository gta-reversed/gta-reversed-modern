#include "StdInc.h"

#include "LeaderEvents.h"
// #include "EventLeaderEnteredCarAsDriver.h"
// #include "EventLeaderExitedCarAsDriver.h"
// #include "EventLeaderQuitEnteringCarAsDriver.h"
// #include "EventAreaCodes.h"
// #include "EventLeaderEntryExit.h"

#include "TaskComplexKillPedOnFoot.h"
#include "TaskComplexArrestPed.h"

void CEventLeaderEnteredCarAsDriver::InjectHooks()
{
    RH_ScopedClass(CEventLeaderEnteredCarAsDriver);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x48E1C0);
    RH_ScopedInstall(AffectsPedGroup_Reversed, 0x4B0EF0);
}

void CEventLeaderExitedCarAsDriver::InjectHooks()
{
    RH_ScopedClass(CEventLeaderExitedCarAsDriver);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B8300);
    RH_ScopedInstall(AffectsPedGroup_Reversed, 0x4B0F80);
}

void CEventLeaderQuitEnteringCarAsDriver::InjectHooks()
{
    RH_ScopedClass(CEventLeaderQuitEnteringCarAsDriver);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x63A110);
    RH_ScopedInstall(AffectsPedGroup_Reversed, 0x4B1010);
}

void CEventAreaCodes::InjectHooks()
{
    RH_ScopedClass(CEventAreaCodes);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B2190);
    RH_ScopedInstall(AffectsPed_Reversed, 0x4B2270);
    RH_ScopedInstall(TakesPriorityOver_Reversed, 0x4B2350);
}

void CEventLeaderEntryExit::InjectHooks()
{
    RH_ScopedClass(CEventLeaderEntryExit);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x43E1C0);
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

// 0x4B0EF0
bool CEventLeaderEnteredCarAsDriver::AffectsPedGroup(CPedGroup* pedGroup)
{
    return CEventLeaderEnteredCarAsDriver::AffectsPedGroup_Reversed(pedGroup);
}

bool CEventLeaderEnteredCarAsDriver::AffectsPedGroup_Reversed(CPedGroup* pedGroup)
{
    if (m_vehicle && pedGroup->m_bMembersEnterLeadersVehicle) {
        for (int32 i = 0; i < TOTAL_PED_GROUP_FOLLOWERS; i++) {
            CPed* member = pedGroup->GetMembership().GetMember(i);
            if (!member)
                continue;

            if (!member->bInVehicle
                || member->m_pVehicle != m_vehicle
                || member->GetTaskManager().Find<TASK_COMPLEX_LEAVE_CAR>())
            {
                return true;
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

// 0x4B0F80
bool CEventLeaderExitedCarAsDriver::AffectsPedGroup(CPedGroup* pedGroup)
{
    return CEventLeaderExitedCarAsDriver::AffectsPedGroup_Reversed(pedGroup);
}

bool CEventLeaderExitedCarAsDriver::AffectsPedGroup_Reversed(CPedGroup* pedGroup)
{
    for (int32 i = 0; i < TOTAL_PED_GROUP_FOLLOWERS; i++) {
        CPedGroupMembership& memberShip = pedGroup->GetMembership();
        CPed* member = memberShip.GetMember(i);
        if (!member)
            continue;

        if (member->m_pVehicle && member->bInVehicle && member->m_pVehicle == memberShip.GetLeader()->m_pVehicle)
            return true;

        if (member->GetIntelligence()->FindTaskByType(TASK_COMPLEX_ENTER_CAR_AS_PASSENGER)
            || member->GetIntelligence()->FindTaskByType(TASK_COMPLEX_ENTER_CAR_AS_PASSENGER_WAIT))
        {
            return true;
        }
    }
    return false;
}

CEventLeaderQuitEnteringCarAsDriver* CEventLeaderQuitEnteringCarAsDriver::Constructor()
{
    this->CEventLeaderQuitEnteringCarAsDriver::CEventLeaderQuitEnteringCarAsDriver();
    return this;
}

// 0x4B1010
bool CEventLeaderQuitEnteringCarAsDriver::AffectsPedGroup(CPedGroup* pedGroup)
{
    return CEventLeaderQuitEnteringCarAsDriver::AffectsPedGroup_Reversed(pedGroup);
}

bool CEventLeaderQuitEnteringCarAsDriver::AffectsPedGroup_Reversed(CPedGroup* pedGroup)
{
    auto oldEventGroupEvent = pedGroup->GetIntelligence().m_pOldEventGroupEvent;
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

// 0x4B2270
bool CEventAreaCodes::AffectsPed(CPed* ped)
{
    return CEventAreaCodes::AffectsPed_Reversed(ped);
}

// 0x4B2350
bool CEventAreaCodes::TakesPriorityOver(const CEvent& refEvent)
{
    return CEventAreaCodes::TakesPriorityOver_Reversed(refEvent);
}

bool CEventAreaCodes::AffectsPed_Reversed(CPed* ped)
{
    if (!m_ped)
        return false;

    CPed* targetPed = nullptr;
    if (const auto killPedOnFoot = ped->GetTaskManager().Find<CTaskComplexKillPedOnFoot>()) {
        targetPed = killPedOnFoot->m_target;
        if (targetPed != m_ped) {
            if (const auto arrestPed = ped->GetTaskManager().Find<CTaskComplexArrestPed>()) {
                targetPed = arrestPed->m_pedToArrest;
            }
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
