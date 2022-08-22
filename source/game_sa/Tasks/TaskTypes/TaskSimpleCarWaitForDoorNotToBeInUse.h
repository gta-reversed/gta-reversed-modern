#pragma once

#include "TaskSimple.h"

class CVehicle;

/*! Task to wait for a vehicle's door to be opened */
class NOTSA_EXPORT_VTABLE CTaskSimpleCarWaitForDoorNotToBeInUse : public CTaskSimple {
public:
    CVehicle* m_TargetVehicle; // The vehicle whose door we have to wait for
    int32 m_nTargetDoor;
    int32 m_nTargetDoorOpposite;

public:
    constexpr static auto Type = TASK_SIMPLE_CAR_WAIT_FOR_DOOR_NOT_TO_BE_IN_USE;

    CTaskSimpleCarWaitForDoorNotToBeInUse(CVehicle* targetVehicle, int32 targetDoor, int32 targetDoorOpposite);
    ~CTaskSimpleCarWaitForDoorNotToBeInUse() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleCarWaitForDoorNotToBeInUse(m_TargetVehicle, m_nTargetDoor, m_nTargetDoorOpposite); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;
    bool SetPedPosition(CPed* ped) override;

    static void InjectHooks();
    CTaskSimpleCarWaitForDoorNotToBeInUse* Constructor(CVehicle* veh, uint32 doorToWaitFor1, uint32 doorToWaitFor2) { this->CTaskSimpleCarWaitForDoorNotToBeInUse::CTaskSimpleCarWaitForDoorNotToBeInUse(veh, doorToWaitFor1, doorToWaitFor2); return this; }
    CTaskSimpleCarWaitForDoorNotToBeInUse* Destructor() { this->CTaskSimpleCarWaitForDoorNotToBeInUse::~CTaskSimpleCarWaitForDoorNotToBeInUse(); return this; }
};
VALIDATE_SIZE(CTaskSimpleCarWaitForDoorNotToBeInUse, 0x14);
