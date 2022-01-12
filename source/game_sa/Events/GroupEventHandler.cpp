#include "StdInc.h"

#include "GroupEventHandler.h"

void CGroupEventHandler::InjectHooks() {
    using namespace ReversibleHooks;
    // Install("CGroupEventHandler", "IsKillTaskAppropriate", 0x5F7A60, &CGroupEventHandler::IsKillTaskAppropriate);
    // Install("CGroupEventHandler", "ComputeWalkAlongsideResponse", 0x5FA910, &CGroupEventHandler::ComputeWalkAlongsideResponse);
    // Install("CGroupEventHandler", "ComputeStareResponse", 0x5F9BD0, &CGroupEventHandler::ComputeStareResponse);
    // Install("CGroupEventHandler", "ComputeResponseVehicleDamage", 0x5FC070, &CGroupEventHandler::ComputeResponseVehicleDamage);
    // Install("CGroupEventHandler", "ComputeResponseShotFired", 0x5FBDF0, &CGroupEventHandler::ComputeResponseShotFired);
    // Install("CGroupEventHandler", "ComputeResponseSexyPed", 0x5FB390, &CGroupEventHandler::ComputeResponseSexyPed);
    // Install("CGroupEventHandler", "ComputeResponseSeenCop", 0x5FBCB0, &CGroupEventHandler::ComputeResponseSeenCop);
    // Install("CGroupEventHandler", "ComputeResponsePlayerCommand", 0x5FB470, &CGroupEventHandler::ComputeResponsePlayerCommand);
    // Install("CGroupEventHandler", "ComputeResponsePedThreat", 0x5FBB90, &CGroupEventHandler::ComputeResponsePedThreat);
    // Install("CGroupEventHandler", "ComputeResponsePedFriend", 0x5FB2D0, &CGroupEventHandler::ComputeResponsePedFriend);
    // Install("CGroupEventHandler", "ComputeResponseNewGangMember", 0x5F9840, &CGroupEventHandler::ComputeResponseNewGangMember);
    // Install("CGroupEventHandler", "ComputeResponseLeaderExitedCar", 0x5F90A0, &CGroupEventHandler::ComputeResponseLeaderExitedCar);
    // Install("CGroupEventHandler", "ComputeResponsLeaderQuitEnteringCar", 0x5F9530, &CGroupEventHandler::ComputeResponsLeaderQuitEnteringCar);
    // Install("CGroupEventHandler", "ComputeResponseLeaderEnteredCar", 0x5F8900, &CGroupEventHandler::ComputeResponseLeaderEnteredCar);
    // Install("CGroupEventHandler", "ComputeResponseLeaderEnterExit", 0x5F9710, &CGroupEventHandler::ComputeResponseLeaderEnterExit);
    // Install("CGroupEventHandler", "ComputeResponseGunAimedAt", 0x5FBD10, &CGroupEventHandler::ComputeResponseGunAimedAt);
    // Install("CGroupEventHandler", "ComputeResponseGather", 0x5F99F0, &CGroupEventHandler::ComputeResponseGather);
    // Install("CGroupEventHandler", "ComputeResponseDraggedOutCar", 0x5FBE70, &CGroupEventHandler::ComputeResponseDraggedOutCar);
    // Install("CGroupEventHandler", "ComputeResponseDanger", 0x5FB540, &CGroupEventHandler::ComputeResponseDanger);
    // Install("CGroupEventHandler", "ComputeResponseDamage", 0x5FBF50, &CGroupEventHandler::ComputeResponseDamage);
    // Install("CGroupEventHandler", "ComputeMemberResponses", 0x5FAA50, &CGroupEventHandler::ComputeMemberResponses);
    // Install("CGroupEventHandler", "ComputeLeanOnVehicleResponse", 0x5F9B20, &CGroupEventHandler::ComputeLeanOnVehicleResponse);
    // Install("CGroupEventHandler", "ComputeKillThreatsBasicResponse", 0x5FB590, &CGroupEventHandler::ComputeKillThreatsBasicResponse);
    // Install("CGroupEventHandler", "ComputeKillPlayerBasicResponse", 0x5FB670, &CGroupEventHandler::ComputeKillPlayerBasicResponse);
    // Install("CGroupEventHandler", "ComputeHassleThreatResponse", 0x5F9D50, &CGroupEventHandler::ComputeHassleThreatResponse);
    // Install("CGroupEventHandler", "ComputeHassleSexyPedResponse", 0x5FA020, &CGroupEventHandler::ComputeHassleSexyPedResponse);
    // Install("CGroupEventHandler", "ComputeHandSignalResponse", 0x5FA820, &CGroupEventHandler::ComputeHandSignalResponse);
    // Install("CGroupEventHandler", "ComputeGreetResponse", 0x5FA550, &CGroupEventHandler::ComputeGreetResponse);
    // Install("CGroupEventHandler", "ComputeFleePedResponse", 0x5FA130, &CGroupEventHandler::ComputeFleePedResponse);
    Install("CGroupEventHandler", "ComputeEventResponseTasks", 0x5FC200, &CGroupEventHandler::ComputeEventResponseTasks);
    // Install("CGroupEventHandler", "ComputeDrivebyResponse", 0x5F7A00, &CGroupEventHandler::ComputeDrivebyResponse);
    // Install("CGroupEventHandler", "ComputeDoDealResponse", 0x5FA290, &CGroupEventHandler::ComputeDoDealResponse);
}

// 0x5F7A60
void CGroupEventHandler::IsKillTaskAppropriate(CPedGroup* group, CPed* ped) {
    plugin::Call<0x5F7A60, CPedGroup*, CPed*>(group, ped);
}

// 0x5FA910
void CGroupEventHandler::ComputeWalkAlongsideResponse(CPedGroup* group, CPed* ped1, CPed* ped2) {
    plugin::Call<0x5FA910, CPedGroup*, CPed*, CPed*>(group, ped1, ped2);
}

// 0x5F9BD0
void CGroupEventHandler::ComputeStareResponse(CPedGroup* group, CPed* ped1, CPed* ped2, int32 a4, int32 a5) {
    plugin::Call<0x5F9BD0, CPedGroup*, CPed*, CPed*, int32, int32>(group, ped1, ped2, a4, a5);
}

// 0x5FC070
void CGroupEventHandler::ComputeResponseVehicleDamage(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5FC070, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5FBDF0
void CGroupEventHandler::ComputeResponseShotFired(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5FBDF0, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5FB390
void CGroupEventHandler::ComputeResponseSexyPed(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5FB390, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5FBCB0
void CGroupEventHandler::ComputeResponseSeenCop(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5FBCB0, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5FB470
void CGroupEventHandler::ComputeResponsePlayerCommand(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5FB470, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5FBB90
void CGroupEventHandler::ComputeResponsePedThreat(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5FBB90, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5FB2D0
void CGroupEventHandler::ComputeResponsePedFriend(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5FB2D0, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5F9840
void CGroupEventHandler::ComputeResponseNewGangMember(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5F9840, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5F90A0
void CGroupEventHandler::ComputeResponseLeaderExitedCar(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5F90A0, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5F8900
void CGroupEventHandler::ComputeResponseLeaderEnteredCar(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5F8900, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5F9710
void CGroupEventHandler::ComputeResponseLeaderEnterExit(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5F9710, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5FBD10
void CGroupEventHandler::ComputeResponseGunAimedAt(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5FBD10, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5F99F0
void CGroupEventHandler::ComputeResponseGather(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5F99F0, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5FBE70
void CGroupEventHandler::ComputeResponseDraggedOutCar(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5FBE70, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5FB540
void CGroupEventHandler::ComputeResponseDanger(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5FB540, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5FBF50
void CGroupEventHandler::ComputeResponseDamage(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5FBF50, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5F9530
void CGroupEventHandler::ComputeResponsLeaderQuitEnteringCar(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5F9530, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5FAA50
void CGroupEventHandler::ComputeMemberResponses(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5FAA50, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5F9B20
void CGroupEventHandler::ComputeLeanOnVehicleResponse(const CEvent& event, CPedGroup* group, CPed* ped) {
    plugin::Call<0x5F9B20, const CEvent&, CPedGroup*, CPed*>(event, group, ped);
}

// 0x5FB590
void CGroupEventHandler::ComputeKillThreatsBasicResponse(CPedGroup* group, CPed* ped1, CPed* ped2, uint8 a4) {
    plugin::Call<0x5FB590, CPedGroup*, CPed*, CPed*, uint8>(group, ped1, ped2, a4);
}

// 0x5FB670
void CGroupEventHandler::ComputeKillPlayerBasicResponse(CPedGroup* group, CPed* ped1, CPed* ped2, uint8 a4) {
    plugin::Call<0x5FB670, CPedGroup*, CPed*, CPed*, uint8>(group, ped1, ped2, a4);
}

// 0x5F9D50
void CGroupEventHandler::ComputeHassleThreatResponse(CPedGroup* group, CPed* ped1, CPed* ped2, bool a4) {
    plugin::Call<0x5F9D50, CPedGroup*, CPed*, CPed*, bool>(group, ped1, ped2, a4);
}

// 0x5FA020
void CGroupEventHandler::ComputeHassleSexyPedResponse(CPedGroup* group, CPed* ped1, CPed* ped2) {
    plugin::Call<0x5FA020, CPedGroup*, CPed*, CPed*>(group, ped1, ped2);
}

// 0x5FA820
void CGroupEventHandler::ComputeHandSignalResponse(CPedGroup* group, CPed* ped1, CPed* ped2) {
    plugin::Call<0x5FA820, CPedGroup*, CPed*, CPed*>(group, ped1, ped2);
}

// 0x5FA550
void CGroupEventHandler::ComputeGreetResponse(CPedGroup* group, CPed* ped1, CPed* ped2) {
    plugin::Call<0x5FA550, CPedGroup*, CPed*, CPed*>(group, ped1, ped2);
}

// 0x5FA130
void CGroupEventHandler::ComputeFleePedResponse(CPedGroup* group, CPed* ped1, CPed* ped2, uint8 a4) {
    plugin::Call<0x5FA130, CPedGroup*, CPed*, CPed*, uint8>(group, ped1, ped2, a4);
}

// 0x5FC200
void CGroupEventHandler::ComputeEventResponseTasks(const CEventGroupEvent& groupEvent, CPedGroup* group) {
    const auto& ped = groupEvent.m_ped;
    const auto& m_event = groupEvent.m_event;

    switch (m_event->GetEventType()) {
    case EVENT_DRAGGED_OUT_CAR:
        ComputeResponseDraggedOutCar(*m_event, group, ped);
        break;
    case EVENT_DAMAGE:
        ComputeResponseDamage(*m_event, group, ped);
        break;
    case EVENT_SHOT_FIRED:
        ComputeResponseShotFired(*m_event, group, ped);
        break;
    case EVENT_SEXY_PED:
        ComputeResponseSexyPed(*m_event, group, ped);
        break;
    case EVENT_GUN_AIMED_AT:
        ComputeResponseGunAimedAt(*m_event, group, ped);
        break;
    case EVENT_ACQUAINTANCE_PED_HATE:
    case EVENT_ACQUAINTANCE_PED_DISLIKE:
        ComputeResponsePedThreat(*m_event, group, ped);
        break;
    case EVENT_ACQUAINTANCE_PED_LIKE:
    case EVENT_ACQUAINTANCE_PED_RESPECT:
        ComputeResponsePedFriend(*m_event, group, ped);
        break;
    case EVENT_VEHICLE_DAMAGE_WEAPON:
    case EVENT_VEHICLE_DAMAGE_COLLISION:
        ComputeResponseVehicleDamage(*m_event, group, ped);
        break;
    case EVENT_LEADER_ENTERED_CAR_AS_DRIVER:
        ComputeResponseLeaderEnteredCar(*m_event, group, ped);
        break;
    case EVENT_LEADER_EXITED_CAR_AS_DRIVER:
        ComputeResponseLeaderExitedCar(*m_event, group, ped);
        break;
    case EVENT_LEADER_QUIT_ENTERING_CAR_AS_DRIVER:
        ComputeResponsLeaderQuitEnteringCar(*m_event, group, ped);
        break;
    case EVENT_PLAYER_COMMAND_TO_GROUP:
    case EVENT_PLAYER_COMMAND_TO_GROUP_GATHER:
        ComputeResponsePlayerCommand(*m_event, group, ped);
        break;
    case EVENT_SEEN_COP:
        ComputeResponseSeenCop(*m_event, group, ped);
        break;
    case EVENT_DANGER:
        ComputeResponseDanger(*m_event, group, ped);
        break;
    case EVENT_LEADER_ENTRY_EXIT:
        ComputeResponseLeaderEnterExit(*m_event, group, ped);
        break;
    case EVENT_NEW_GANG_MEMBER:
        ComputeResponseNewGangMember(*m_event, group, ped);
        break;
    case EVENT_LEAN_ON_VEHICLE:
        ComputeLeanOnVehicleResponse(*m_event, group, ped);
        break;
    default:
        return;
    }
}

// 0x5F7A00
void CGroupEventHandler::ComputeDrivebyResponse(CPedGroup* group, CPed* ped1, CPed* ped2) {
    plugin::Call<0x5F7A00, CPedGroup*, CPed*, CPed*>(group, ped1, ped2);
}

// 0x5FA290
void CGroupEventHandler::ComputeDoDealResponse(CPedGroup* group, CPed* ped1, CPed* ped2) {
    plugin::Call<0x5FA290, CPedGroup*, CPed*, CPed*>(group, ped1, ped2);
}
