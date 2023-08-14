#pragma once

class CPed;
class CEvent;
class CEventGroupEvent;
class CEventVehicleDamage;

class CGroupEventHandler {
public:
    static void InjectHooks();

    static bool IsKillTaskAppropriate(CPedGroup* pg, CPed* ped);
    static bool ComputeWalkAlongsideResponse(CPedGroup* pg, CPed* ped1, CPed* ped2);
    static void ComputeStareResponse(CPedGroup* pg, CPed* stareAt, CPed* originatorPed, int32 timeout, int32 timeoutBias);

    static void ComputeResponseVehicleDamage(const CEventVehicleDamage& event, CPedGroup* group, CPed* ped);
    static void ComputeResponseShotFired(const CEvent& event, CPedGroup* group, CPed* ped);
    static void ComputeResponseSexyPed(const CEvent& event, CPedGroup* group, CPed* ped);
    static void ComputeResponseSeenCop(const CEvent& event, CPedGroup* group, CPed* ped);
    static void ComputeResponsePlayerCommand(const CEvent& event, CPedGroup* group, CPed* ped);
    static void ComputeResponsePedThreat(const CEvent& event, CPedGroup* group, CPed* ped);
    static void ComputeResponsePedFriend(const CEvent& event, CPedGroup* group, CPed* ped);
    static void ComputeResponseNewGangMember(const CEvent& event, CPedGroup* group, CPed* ped);
    static void ComputeResponseLeaderExitedCar(const CEvent& event, CPedGroup* group, CPed* ped);
    static void ComputeResponseLeaderEnteredCar(const CEvent& event, CPedGroup* group, CPed* ped);
    static void ComputeResponseLeaderEnterExit(const CEvent& event, CPedGroup* group, CPed* ped);
    static void ComputeResponseGunAimedAt(const CEvent& event, CPedGroup* group, CPed* ped);
    static void ComputeResponseGather(const CEvent& event, CPedGroup* group, CPed* ped);
    static void ComputeResponseDraggedOutCar(const CEvent& event, CPedGroup* group, CPed* ped);
    static void ComputeResponseDanger(const CEvent& event, CPedGroup* group, CPed* ped);
    static void ComputeResponseDamage(const CEvent& event, CPedGroup* group, CPed* ped);
    static void ComputeResponsLeaderQuitEnteringCar(const CEvent&, CPedGroup* group, CPed* ped);
    static void ComputeMemberResponses(const CEvent& event, CPedGroup* group, CPed* ped);
    static void ComputeLeanOnVehicleResponse(const CEvent& event, CPedGroup* group, CPed* ped);
    static void ComputeKillThreatsBasicResponse(CPedGroup* group, CPed* ped1, CPed* ped2, uint8);
    static void ComputeKillPlayerBasicResponse(CPedGroup* group, CPed* ped1, CPed* ped2, uint8);
    static void ComputeHassleThreatResponse(CPedGroup* group, CPed* ped1, CPed* ped2, bool);
    static void ComputeHassleSexyPedResponse(CPedGroup* group, CPed* ped1, CPed* ped2);
    static void ComputeHandSignalResponse(CPedGroup* group, CPed* ped1, CPed* ped2);
    static void ComputeGreetResponse(CPedGroup* group, CPed* ped1, CPed* ped2);
    static void ComputeFleePedResponse(CPedGroup* group, CPed* ped1, CPed* ped2, uint8);
    static void ComputeEventResponseTasks(const CEventGroupEvent& groupEvent, CPedGroup* group);
    static void ComputeDrivebyResponse(CPedGroup* group, CPed* ped1, CPed* ped2);
    static void ComputeDoDealResponse(CPedGroup* group, CPed* ped1, CPed* ped2);
};

