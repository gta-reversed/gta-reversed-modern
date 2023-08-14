#include "StdInc.h"

#include "GroupEventHandler.h"

#include "Tasks/TaskTypes/TaskComplexStareAtPed.h"
#include "Tasks/TaskTypes/TaskSimpleNone.h"

#include "Tasks/Allocators/TaskAllocatorPlayerCommandAttack.h"

#include "Events/EventVehicleDamage.h"
#include "Events/EventGunShot.h"
#include "Events/EventSexyPed.h"
#include "Events/EventAcquaintancePed.h"
#include "Events/GroupEvents.h"

#include "TaskAllocator.h"

void CGroupEventHandler::InjectHooks() {
    RH_ScopedClass(CGroupEventHandler);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(IsKillTaskAppropriate, 0x5F7A60);
    RH_ScopedInstall(ComputeWalkAlongsideResponse, 0x5FA910);
    RH_ScopedInstall(ComputeStareResponse, 0x5F9BD0);
    RH_ScopedInstall(ComputeResponseVehicleDamage, 0x5FC070);
    RH_ScopedInstall(ComputeResponseShotFired, 0x5FBDF0);
    RH_ScopedInstall(ComputeResponseSexyPed, 0x5FB390);
    RH_ScopedInstall(ComputeResponseSeenCop, 0x5FBCB0);
    RH_ScopedInstall(ComputeResponsePlayerCommand, 0x5FB470);
    RH_ScopedInstall(ComputeResponsePedThreat, 0x5FBB90);
    RH_ScopedInstall(ComputeResponsePedFriend, 0x5FB2D0);
    RH_ScopedInstall(ComputeResponseNewGangMember, 0x5F9840, { .reversed = false });
    RH_ScopedInstall(ComputeResponseLeaderExitedCar, 0x5F90A0, { .reversed = false });
    RH_ScopedInstall(ComputeResponsLeaderQuitEnteringCar, 0x5F9530, { .reversed = false });
    RH_ScopedInstall(ComputeResponseLeaderEnteredCar, 0x5F8900, { .reversed = false });
    RH_ScopedInstall(ComputeResponseLeaderEnterExit, 0x5F9710, { .reversed = false });
    RH_ScopedInstall(ComputeResponseGunAimedAt, 0x5FBD10, { .reversed = false });
    RH_ScopedInstall(ComputeResponseGather, 0x5F99F0, { .reversed = false });
    RH_ScopedInstall(ComputeResponseDraggedOutCar, 0x5FBE70, { .reversed = false });
    RH_ScopedInstall(ComputeResponseDanger, 0x5FB540, { .reversed = false });
    RH_ScopedInstall(ComputeResponseDamage, 0x5FBF50, { .reversed = false });
    RH_ScopedInstall(ComputeMemberResponses, 0x5FAA50, { .reversed = false });
    RH_ScopedInstall(ComputeLeanOnVehicleResponse, 0x5F9B20, { .reversed = false });
    RH_ScopedInstall(ComputeKillThreatsBasicResponse, 0x5FB590, { .reversed = false });
    RH_ScopedInstall(ComputeKillPlayerBasicResponse, 0x5FB670, { .reversed = false });
    RH_ScopedInstall(ComputeHassleThreatResponse, 0x5F9D50, { .reversed = false });
    RH_ScopedInstall(ComputeHassleSexyPedResponse, 0x5FA020, { .reversed = false });
    RH_ScopedInstall(ComputeHandSignalResponse, 0x5FA820, { .reversed = false });
    RH_ScopedInstall(ComputeGreetResponse, 0x5FA550, { .reversed = false });
    RH_ScopedInstall(ComputeFleePedResponse, 0x5FA130, { .reversed = false });
    RH_ScopedInstall(ComputeEventResponseTasks, 0x5FC200);
    RH_ScopedInstall(ComputeDrivebyResponse, 0x5F7A00, { .reversed = false });
    RH_ScopedInstall(ComputeDoDealResponse, 0x5FA290, { .reversed = false });
}

bool IsPedInPlayersGroup(CPedGroup* pg, CPed* p) {
    const auto playerGrp = &FindPlayerPed(-1)->GetPlayerGroup();
    if (pg == playerGrp) {
        return true;
    }
    if (playerGrp->GetMembership().IsMember(p)) {
        return true;
    }
    return false;
}

// 0x5F7A60
bool CGroupEventHandler::IsKillTaskAppropriate(CPedGroup* g, CPed* ped) {
    if (g->m_bIsMissionGroup || ped->GetActiveWeapon().IsTypeMelee()) { // TODO/NOTE: This `IsTypeMelee()` check should be inverted I think [By following the logic of the code in the loop]
        return true;
    }
    for (auto& m : g->GetMembership().GetMembers()) {
        if (!m.GetActiveWeapon().IsTypeMelee()) {
            return true;
        }
    }
    return false;
}

// 0x5FA910
CTaskAllocator* CGroupEventHandler::ComputeWalkAlongsideResponse(CPedGroup* pg, CPed* ped1, CPed* ped2) {
    NOTSA_UNREACHABLE(); // Unused
}

// 0x5F9BD0
CTaskAllocator* CGroupEventHandler::ComputeStareResponse(CPedGroup* pg, CPed* stareAt, CPed* originatorPed, int32 timeout, int32 timeoutBias) {
    if (!stareAt) {
        return nullptr;
    }
    if (!pg->GetMembership().GetLeader()) {
        return nullptr;
    }
    if ((stareAt->GetPosition() - pg->GetMembership().GetLeader()->GetPosition()).SquaredMagnitude2D() >= sq(8.f)) {
        return nullptr;
    }
    for (auto& m : pg->GetMembership().GetMembers()) {
        pg->GetIntelligence().SetTask(
            &m,
            new CTaskComplexStareAtPed{ pg, stareAt, timeout + CGeneral::GetRandomNumberInRange(-timeoutBias, timeoutBias) },
            pg->GetIntelligence().m_pedTaskPairs
        );
    }
    return nullptr;
}

// 0x5FC070
CTaskAllocator* CGroupEventHandler::ComputeResponseVehicleDamage(const CEventVehicleDamage& e, CPedGroup* pg, CPed* originator) {
    if (!e.m_attacker || !e.m_attacker->IsPed()) {
        return nullptr;
    }
    const auto threat = e.m_attacker->AsPed();
    switch (e.m_taskId) {
    case TASK_GROUP_KILL_THREATS_BASIC:  return ComputeKillThreatsBasicResponse(pg, threat, originator, true);
    case TASK_GROUP_KILL_PLAYER_BASIC:   return ComputeKillPlayerBasicResponse(pg, threat, originator, true); 
    case TASK_GROUP_FLEE_THREAT:         return ComputeFleePedResponse(pg, threat, originator, true);         
    case TASK_GROUP_USE_MEMBER_DECISION: return ComputeMemberResponses(e, pg, originator);                      
    case TASK_GROUP_DRIVEBY:             return ComputeDrivebyResponse(pg, threat, originator);
    default:                             return nullptr;
    }
}

// 0x5FBDF0
CTaskAllocator* CGroupEventHandler::ComputeResponseShotFired(const CEventGunShot& e, CPedGroup* pg, CPed* originator) {
    if (!e.m_firedBy || !e.m_firedBy->IsPed()) {
        return nullptr;
    }
    const auto threat = e.m_firedBy->AsPed();
    switch (e.m_taskId) {
    case TASK_GROUP_KILL_THREATS_BASIC:  return ComputeKillThreatsBasicResponse(pg, threat, originator, false);
    case TASK_GROUP_FLEE_THREAT:         return ComputeFleePedResponse(pg, threat, originator, false);
    case TASK_GROUP_USE_MEMBER_DECISION: return ComputeMemberResponses(e, pg, originator);
    }
    return nullptr;
}

// 0x5FB390
CTaskAllocator* CGroupEventHandler::ComputeResponseSexyPed(const CEventSexyPed& e, CPedGroup* pg, CPed* originator) {
    if (!e.m_SexyPed) {
        return nullptr;
    }
    if (pg->GetMembership().IsMember(e.m_SexyPed)) {
        return nullptr;
    }
    if (IsPedInPlayersGroup(pg, e.m_SexyPed)) {
        return nullptr;
    }
    switch (e.m_taskId) {
    case TASK_GROUP_STARE_AT_PED:    return ComputeStareResponse(pg, e.m_SexyPed, originator, CGeneral::GetRandomNumberInRange(3000, 5000), 1000);
    case TASK_GROUP_HASSLE_SEXY_PED: return ComputeHassleSexyPedResponse(pg, e.m_SexyPed, originator);
    }
    return nullptr;
}

// 0x5FBCB0
CTaskAllocator* CGroupEventHandler::ComputeResponseSeenCop(const CEventSeenCop& e, CPedGroup* pg, CPed* originator) {
    switch (e.m_taskId) {
    case TASK_GROUP_KILL_THREATS_BASIC: return ComputeKillThreatsBasicResponse(pg, e.m_ped, originator, false);
    case TASK_GROUP_FLEE_THREAT:        return ComputeFleePedResponse(pg, e.m_ped, originator, false);
    case TASK_GROUP_HAND_SIGNAL:        return ComputeHandSignalResponse(pg, e.m_ped, originator);
    }
    return nullptr;
}

// 0x5FB470
CTaskAllocator* CGroupEventHandler::ComputeResponsePlayerCommand(const CEventPlayerCommandToGroup& e, CPedGroup* pg, CPed* originator) {
    switch (e.m_command) {
    case ePlayerGroupCommand::PLAYER_GROUP_COMMAND_GATHER:
        return ComputeResponseGather(e, pg, originator);
    case ePlayerGroupCommand::PLAYER_GROUP_COMMAND_ATTACK:
        return new CTaskAllocatorPlayerCommandAttack{
            e.m_target,
            e.m_target->GetGroupId(),
            e.m_target->m_nPedType
        };
    }
    return nullptr;
}

// 0x5FBB90
CTaskAllocator* CGroupEventHandler::ComputeResponsePedThreat(const CEventAcquaintancePed& e, CPedGroup* pg, CPed* originator) {
    if (!e.m_ped) {
        return nullptr;
    }
    if (pg->GetMembership().IsMember(e.m_ped)) {
        return nullptr;
    }
    switch (e.m_taskId) {
    case TASK_GROUP_KILL_THREATS_BASIC:    return ComputeKillThreatsBasicResponse(pg, e.m_ped, originator, false);
    case TASK_GROUP_STARE_AT_PED:          return ComputeStareResponse(pg, e.m_ped, originator, 99'999'999, false); // 1.15740739583 days
    case TASK_GROUP_FLEE_THREAT:           return ComputeFleePedResponse(pg, e.m_ped, originator, false);
    case TASK_GROUP_HASSLE_THREAT:         return ComputeHassleThreatResponse(pg, e.m_ped, originator, true);
    case TASK_GROUP_USE_MEMBER_DECISION:   return ComputeMemberResponses(e, pg, originator);
    case TASK_GROUP_DRIVEBY:               return ComputeDrivebyResponse(pg, e.m_ped, originator);
    case TASK_GROUP_HASSLE_THREAT_PASSIVE: return ComputeHassleThreatResponse(pg, e.m_ped, originator, false);
    }
    return nullptr;
}

// 0x5FB2D0
CTaskAllocator* CGroupEventHandler::ComputeResponsePedFriend(const CEventAcquaintancePed& e, CPedGroup* pg, CPed* ped) {
    if (!e.m_ped) {
        return nullptr;
    }
    if (IsPedInPlayersGroup(pg, e.m_ped)) {
        return nullptr;
    }
    switch (e.m_taskId) {
    case TASK_GROUP_PARTNER_DEAL:  return ComputeDoDealResponse(pg, e.m_ped, originator);
    case TASK_GROUP_PARTNER_GREET: return ComputeGreetResponse(pg, e.m_ped, originator);
    }
    return nullptr;
}

// 0x5F9840
CTaskAllocator* CGroupEventHandler::ComputeResponseNewGangMember(const CEvent& e, CPedGroup* pg, CPed* ped) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5F9840, const CEvent&, CPedGroup*, CPed*>(e, pg, ped);
}

// 0x5F90A0
CTaskAllocator* CGroupEventHandler::ComputeResponseLeaderExitedCar(const CEvent& e, CPedGroup* pg, CPed* ped) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5F90A0, const CEvent&, CPedGroup*, CPed*>(e, pg, ped);
}

// 0x5F8900
CTaskAllocator* CGroupEventHandler::ComputeResponseLeaderEnteredCar(const CEvent& e, CPedGroup* pg, CPed* ped) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5F8900, const CEvent&, CPedGroup*, CPed*>(e, pg, ped);
}

// 0x5F9710
CTaskAllocator* CGroupEventHandler::ComputeResponseLeaderEnterExit(const CEvent& e, CPedGroup* pg, CPed* ped) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5F9710, const CEvent&, CPedGroup*, CPed*>(e, pg, ped);
}

// 0x5FBD10
CTaskAllocator* CGroupEventHandler::ComputeResponseGunAimedAt(const CEvent& e, CPedGroup* pg, CPed* ped) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5FBD10, const CEvent&, CPedGroup*, CPed*>(e, pg, ped);
}

// 0x5F99F0
CTaskAllocator* CGroupEventHandler::ComputeResponseGather(const CEvent& e, CPedGroup* pg, CPed* ped) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5F99F0, const CEvent&, CPedGroup*, CPed*>(e, pg, ped);
}

// 0x5FBE70
CTaskAllocator* CGroupEventHandler::ComputeResponseDraggedOutCar(const CEvent& e, CPedGroup* pg, CPed* ped) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5FBE70, const CEvent&, CPedGroup*, CPed*>(e, pg, ped);
}

// 0x5FB540
CTaskAllocator* CGroupEventHandler::ComputeResponseDanger(const CEvent& e, CPedGroup* pg, CPed* ped) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5FB540, const CEvent&, CPedGroup*, CPed*>(e, pg, ped);
}

// 0x5FBF50
CTaskAllocator* CGroupEventHandler::ComputeResponseDamage(const CEvent& e, CPedGroup* pg, CPed* ped) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5FBF50, const CEvent&, CPedGroup*, CPed*>(e, pg, ped);
}

// 0x5F9530
CTaskAllocator* CGroupEventHandler::ComputeResponsLeaderQuitEnteringCar(const CEvent& e, CPedGroup* pg, CPed* ped) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5F9530, const CEvent&, CPedGroup*, CPed*>(e, pg, ped);
}

// 0x5FAA50
CTaskAllocator* CGroupEventHandler::ComputeMemberResponses(const CEvent& e, CPedGroup* pg, CPed* ped) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5FAA50, const CEvent&, CPedGroup*, CPed*>(e, pg, ped);
}

// 0x5F9B20
CTaskAllocator* CGroupEventHandler::ComputeLeanOnVehicleResponse(const CEvent& e, CPedGroup* pg, CPed* ped) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5F9B20, const CEvent&, CPedGroup*, CPed*>(e, pg, ped);
}

// 0x5FB590
CTaskAllocator* CGroupEventHandler::ComputeKillThreatsBasicResponse(CPedGroup* pg, CPed* threat, CPed* originator, uint8 bDamageOriginator) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5FB590, CPedGroup*, CPed*, CPed*, uint8>(pg, threat, originator, bDamageOriginator);
}

// 0x5FB670
CTaskAllocator* CGroupEventHandler::ComputeKillPlayerBasicResponse(CPedGroup* pg, CPed* ped1, CPed* ped2, uint8 a4) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5FB670, CPedGroup*, CPed*, CPed*, uint8>(pg, ped1, ped2, a4);
}

// 0x5F9D50
CTaskAllocator* CGroupEventHandler::ComputeHassleThreatResponse(CPedGroup* pg, CPed* threat, CPed* originator, bool bBeAggressive) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5F9D50, CPedGroup*, CPed*, CPed*, bool>(pg, threat, originator, bBeAggressive);
}

// 0x5FA020
CTaskAllocator* CGroupEventHandler::ComputeHassleSexyPedResponse(CPedGroup* pg, CPed* sexyPed, CPed* originator) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5FA020, CPedGroup*, CPed*, CPed*>(pg, sexyPed, originator);
}

// 0x5FA820
CTaskAllocator* CGroupEventHandler::ComputeHandSignalResponse(CPedGroup* pg, CPed* threat, CPed* originator) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5FA820, CPedGroup*, CPed*, CPed*>(pg, threat, originator);
}

// 0x5FA550
CTaskAllocator* CGroupEventHandler::ComputeGreetResponse(CPedGroup* pg, CPed* ped1, CPed* ped2) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5FA550, CPedGroup*, CPed*, CPed*>(pg, ped1, ped2);
}

// 0x5FA130
CTaskAllocator* CGroupEventHandler::ComputeFleePedResponse(CPedGroup* pg, CPed* ped1, CPed* ped2, uint8 a4) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5FA130, CPedGroup*, CPed*, CPed*, uint8>(pg, ped1, ped2, a4);
}

// 0x5FC200
CTaskAllocator* CGroupEventHandler::ComputeEventResponseTasks(const CEventGroupEvent& ge, CPedGroup* g) {
    const auto& p = ge.m_ped;
    const auto& e = ge.m_event;
    switch (e->GetEventType()) {
    case EVENT_DRAGGED_OUT_CAR:
        return ComputeResponseDraggedOutCar(*e, g, p);
    case EVENT_DAMAGE:
        return ComputeResponseDamage(*e, g, p);
    case EVENT_SHOT_FIRED:
        return ComputeResponseShotFired(static_cast<const CEventGunShot&>(*e), g, p);
    case EVENT_SEXY_PED:
        return ComputeResponseSexyPed(static_cast<const CEventSexyPed&>(*e), g, p);
    case EVENT_GUN_AIMED_AT:
        return ComputeResponseGunAimedAt(*e, g, p);
    case EVENT_ACQUAINTANCE_PED_HATE:
    case EVENT_ACQUAINTANCE_PED_DISLIKE:
        return ComputeResponsePedThreat(static_cast<const CEventAcquaintancePed&>(*e), g, p);
    case EVENT_ACQUAINTANCE_PED_LIKE:
    case EVENT_ACQUAINTANCE_PED_RESPECT:
        return ComputeResponsePedFriend(static_cast<const CEventAcquaintancePed&>(*e), g, p);
    case EVENT_VEHICLE_DAMAGE_WEAPON:
    case EVENT_VEHICLE_DAMAGE_COLLISION:
        return ComputeResponseVehicleDamage(static_cast<const CEventVehicleDamage&>(*e), g, p);
    case EVENT_LEADER_ENTERED_CAR_AS_DRIVER:
        return ComputeResponseLeaderEnteredCar(*e, g, p);
    case EVENT_LEADER_EXITED_CAR_AS_DRIVER:
        return ComputeResponseLeaderExitedCar(*e, g, p);
    case EVENT_LEADER_QUIT_ENTERING_CAR_AS_DRIVER:
        return ComputeResponsLeaderQuitEnteringCar(*e, g, p);
    case EVENT_PLAYER_COMMAND_TO_GROUP:
    case EVENT_PLAYER_COMMAND_TO_GROUP_GATHER:
        return ComputeResponsePlayerCommand(static_cast<const CEventPlayerCommandToGroup&>(*e), g, p);
    case EVENT_SEEN_COP:
        return ComputeResponseSeenCop(static_cast<const CEventSeenCop&>(*e), g, p);
    case EVENT_DANGER:
        return ComputeResponseDanger(*e, g, p);
    case EVENT_LEADER_ENTRY_EXIT:
        return ComputeResponseLeaderEnterExit(*e, g, p);
    case EVENT_NEW_GANG_MEMBER:
        return ComputeResponseNewGangMember(*e, g, p);
    case EVENT_LEAN_ON_VEHICLE:
        return ComputeLeanOnVehicleResponse(*e, g, p);
    default:
        return nullptr;
    }
}

// 0x5F7A00
CTaskAllocator* CGroupEventHandler::ComputeDrivebyResponse(CPedGroup* pg, CPed* friendp, CPed* originator) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5F7A00, CPedGroup*, CPed*, CPed*>(pg, friendp, originator);
}

// 0x5FA290
CTaskAllocator* CGroupEventHandler::ComputeDoDealResponse(CPedGroup* pg, CPed* friendp, CPed* originator) {
    return plugin::CallAndReturn<CTaskAllocator*, 0x5FA290, CPedGroup*, CPed*, CPed*>(pg, friendp, originator);
}
