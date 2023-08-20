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
    RH_ScopedVirtualInstall(AffectsPedGroup, 0x4B0EF0);
}

void CEventLeaderExitedCarAsDriver::InjectHooks()
{
    RH_ScopedClass(CEventLeaderExitedCarAsDriver);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B8300);
    RH_ScopedVirtualInstall(AffectsPedGroup, 0x4B0F80);
}

void CEventLeaderQuitEnteringCarAsDriver::InjectHooks()
{
    RH_ScopedClass(CEventLeaderQuitEnteringCarAsDriver);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x63A110);
    RH_ScopedVirtualInstall(AffectsPedGroup, 0x4B1010);
}

void CEventAreaCodes::InjectHooks()
{
    RH_ScopedClass(CEventAreaCodes);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B2190);
    RH_ScopedVirtualInstall(AffectsPed, 0x4B2270);
    RH_ScopedVirtualInstall(TakesPriorityOver, 0x4B2350);
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
    CEntity::SafeRegisterRef(m_vehicle);
}

CEventLeaderEnteredCarAsDriver::~CEventLeaderEnteredCarAsDriver()
{
    CEntity::SafeCleanUpRef(m_vehicle);
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

bool CEventLeaderExitedCarAsDriver::AffectsPedGroup_Reversed(CPedGroup* pg) {
    const auto leader = pg->GetMembership().GetLeader();
    for (auto& m : pg->GetMembership().GetFollowers()) {
        if (m.m_pVehicle && m.bInVehicle && m.m_pVehicle == leader->m_pVehicle) {
            return true;
        }
        if (m.GetTaskManager().HasAnyOf<TASK_COMPLEX_ENTER_CAR_AS_PASSENGER, TASK_COMPLEX_ENTER_CAR_AS_PASSENGER_WAIT>(false)) {
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

bool CEventLeaderQuitEnteringCarAsDriver::AffectsPedGroup_Reversed(CPedGroup* pedGroup) {
    const auto oe = pedGroup->GetIntelligence().GetOldEvent();
    return oe && oe->GetEvent().GetEventType() == EVENT_LEADER_ENTERED_CAR_AS_DRIVER;
}

CEventAreaCodes::CEventAreaCodes(CPed* ped)
{
    m_ped = ped;
    CEntity::SafeRegisterRef(m_ped);
}

CEventAreaCodes::~CEventAreaCodes()
{
    CEntity::SafeCleanUpRef(m_ped);
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
                targetPed = arrestPed->m_PedToArrest;
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
