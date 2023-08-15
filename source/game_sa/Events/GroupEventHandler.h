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
class CEventAcquaintancePed;
class CEventNewGangMember;
class CEventLeaderExitedCarAsDriver;
class CEventLeaderEntryExit;
class CEventGunAimedAt;

class CGroupEventHandler {
public:
    static void InjectHooks();

    static bool IsKillTaskAppropriate(CPedGroup* pg, CPed* ped);

    static CTaskAllocator* ComputeWalkAlongsideResponse(CPedGroup* pg, CPed* ped1, CPed* ped2);
    static CTaskAllocator* ComputeStareResponse(CPedGroup* pg, CPed* stareAt, CPed* originatorPed, int32 timeout, int32 timeoutBias);

    static CTaskAllocator* ComputeResponseVehicleDamage(const CEventVehicleDamage& event, CPedGroup* pg, CPed* ped);
    static CTaskAllocator* ComputeResponseShotFired(const CEventGunShot& event, CPedGroup* pg, CPed* ped);
    static CTaskAllocator* ComputeResponseSexyPed(const CEventSexyPed& event, CPedGroup* pg, CPed* ped);
    static CTaskAllocator* ComputeResponseSeenCop(const CEventSeenCop& event, CPedGroup* pg, CPed* ped);
    static CTaskAllocator* ComputeResponsePlayerCommand(const CEventPlayerCommandToGroup& event, CPedGroup* pg, CPed* ped);
    static CTaskAllocator* ComputeResponsePedThreat(const CEventAcquaintancePed& event, CPedGroup* pg, CPed* ped);
    static CTaskAllocator* ComputeResponsePedFriend(const CEventAcquaintancePed& e, CPedGroup* pg, CPed* ped);
    static CTaskAllocator* ComputeResponseNewGangMember(const CEventNewGangMember& e, CPedGroup* pg, CPed* ped);
    static CTaskAllocator* ComputeResponseLeaderExitedCar(const CEventLeaderExitedCarAsDriver& e, CPedGroup* pg, CPed* ped);
    static CTaskAllocator* ComputeResponseLeaderEnteredCar(const CEvent& e, CPedGroup* pg, CPed* ped);
    static CTaskAllocator* ComputeResponseLeaderEnterExit(const CEventLeaderEntryExit& e, CPedGroup* pg, CPed* ped);
    static CTaskAllocator* ComputeResponseGunAimedAt(const CEventGunAimedAt& e, CPedGroup* pg, CPed* ped);
    static CTaskAllocator* ComputeResponseGather(const CEvent& e, CPedGroup* pg, CPed* ped);
    static CTaskAllocator* ComputeResponseDraggedOutCar(const CEvent& e, CPedGroup* pg, CPed* ped);
    static CTaskAllocator* ComputeResponseDanger(const CEvent& e, CPedGroup* pg, CPed* ped);
    static CTaskAllocator* ComputeResponseDamage(const CEvent& e, CPedGroup* pg, CPed* ped);
    static CTaskAllocator* ComputeResponsLeaderQuitEnteringCar(const CEvent&, CPedGroup* pg, CPed* ped);
    static CTaskAllocator* ComputeMemberResponses(const CEvent& e, CPedGroup* pg, CPed* ped);
    static CTaskAllocator* ComputeLeanOnVehicleResponse(const CEvent& e, CPedGroup* pg, CPed* ped);

    static CTaskAllocator* ComputeKillThreatsBasicResponse(CPedGroup* pg, CPed* ped1, CPed* ped2, uint8);
    static CTaskAllocator* ComputeKillPlayerBasicResponse(CPedGroup* pg, CPed* ped1, CPed* ped2, uint8);
    static CTaskAllocator* ComputeHassleThreatResponse(CPedGroup* pg, CPed* ped1, CPed* ped2, bool);
    static CTaskAllocator* ComputeHassleSexyPedResponse(CPedGroup* pg, CPed* ped1, CPed* ped2);
    static CTaskAllocator* ComputeHandSignalResponse(CPedGroup* pg, CPed* ped1, CPed* ped2);
    static CTaskAllocator* ComputeGreetResponse(CPedGroup* pg, CPed* ped1, CPed* ped2);
    static CTaskAllocator* ComputeFleePedResponse(CPedGroup* pg, CPed* ped1, CPed* ped2, uint8);
    static CTaskAllocator* ComputeEventResponseTasks(const CEventGroupEvent& groupEvent, CPedGroup* pg);
    static CTaskAllocator* ComputeDrivebyResponse(CPedGroup* pg, CPed* ped1, CPed* ped2);
    static CTaskAllocator* ComputeDoDealResponse(CPedGroup* pg, CPed* ped1, CPed* ped2);
};

static inline auto& fEntityPosChangeThreshold = StaticRef<float>(0xC18CF0);
