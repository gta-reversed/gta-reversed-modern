#pragma once

class CPed;
class CEvent;
class CEventGroupEvent;
class CTaskAllocator;

class CEventVehicleDamage;
class CEventGunShot;
class CEventSexyPed;
class CEventSeenCop;
class CEventPlayerCommandToGroup;

class CGroupEventHandler {
public:
    static void InjectHooks();

    static bool IsKillTaskAppropriate(CPedGroup* pg, CPed* ped);

    static CTaskAllocator* ComputeWalkAlongsideResponse(CPedGroup* pg, CPed* ped1, CPed* ped2);
    static CTaskAllocator* ComputeStareResponse(CPedGroup* pg, CPed* stareAt, CPed* originatorPed, int32 timeout, int32 timeoutBias);

    static CTaskAllocator* ComputeResponseVehicleDamage(const CEventVehicleDamage& event, CPedGroup* group, CPed* ped);
    static CTaskAllocator* ComputeResponseShotFired(const CEventGunShot& event, CPedGroup* group, CPed* ped);
    static CTaskAllocator* ComputeResponseSexyPed(const CEventSexyPed& event, CPedGroup* group, CPed* ped);
    static CTaskAllocator* ComputeResponseSeenCop(const CEventSeenCop& event, CPedGroup* group, CPed* ped);
    static CTaskAllocator* ComputeResponsePlayerCommand(const CEventPlayerCommandToGroup& event, CPedGroup* group, CPed* ped);
    static CTaskAllocator* ComputeResponsePedThreat(const CEvent& event, CPedGroup* group, CPed* ped);
    static CTaskAllocator* ComputeResponsePedFriend(const CEvent& event, CPedGroup* group, CPed* ped);
    static CTaskAllocator* ComputeResponseNewGangMember(const CEvent& event, CPedGroup* group, CPed* ped);
    static CTaskAllocator* ComputeResponseLeaderExitedCar(const CEvent& event, CPedGroup* group, CPed* ped);
    static CTaskAllocator* ComputeResponseLeaderEnteredCar(const CEvent& event, CPedGroup* group, CPed* ped);
    static CTaskAllocator* ComputeResponseLeaderEnterExit(const CEvent& event, CPedGroup* group, CPed* ped);
    static CTaskAllocator* ComputeResponseGunAimedAt(const CEvent& event, CPedGroup* group, CPed* ped);
    static CTaskAllocator* ComputeResponseGather(const CEvent& event, CPedGroup* group, CPed* ped);
    static CTaskAllocator* ComputeResponseDraggedOutCar(const CEvent& event, CPedGroup* group, CPed* ped);
    static CTaskAllocator* ComputeResponseDanger(const CEvent& event, CPedGroup* group, CPed* ped);
    static CTaskAllocator* ComputeResponseDamage(const CEvent& event, CPedGroup* group, CPed* ped);
    static CTaskAllocator* ComputeResponsLeaderQuitEnteringCar(const CEvent&, CPedGroup* group, CPed* ped);
    static CTaskAllocator* ComputeMemberResponses(const CEvent& event, CPedGroup* group, CPed* ped);
    static CTaskAllocator* ComputeLeanOnVehicleResponse(const CEvent& event, CPedGroup* group, CPed* ped);

    static CTaskAllocator* ComputeKillThreatsBasicResponse(CPedGroup* group, CPed* ped1, CPed* ped2, uint8);
    static CTaskAllocator* ComputeKillPlayerBasicResponse(CPedGroup* group, CPed* ped1, CPed* ped2, uint8);
    static CTaskAllocator* ComputeHassleThreatResponse(CPedGroup* group, CPed* ped1, CPed* ped2, bool);
    static CTaskAllocator* ComputeHassleSexyPedResponse(CPedGroup* group, CPed* ped1, CPed* ped2);
    static CTaskAllocator* ComputeHandSignalResponse(CPedGroup* group, CPed* ped1, CPed* ped2);
    static CTaskAllocator* ComputeGreetResponse(CPedGroup* group, CPed* ped1, CPed* ped2);
    static CTaskAllocator* ComputeFleePedResponse(CPedGroup* group, CPed* ped1, CPed* ped2, uint8);
    static CTaskAllocator* ComputeEventResponseTasks(const CEventGroupEvent& groupEvent, CPedGroup* group);
    static CTaskAllocator* ComputeDrivebyResponse(CPedGroup* group, CPed* ped1, CPed* ped2);
    static CTaskAllocator* ComputeDoDealResponse(CPedGroup* group, CPed* ped1, CPed* ped2);
};

