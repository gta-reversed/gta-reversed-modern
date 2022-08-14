#pragma once

#include "TaskComplex.h"

class CTaskComplexGoToBoatSteeringWheel : public CTaskComplex {
public:
    CVector   m_TargetPos;
    CVehicle* m_Vehicle;
    bool      byte1C;
    uint32    m_FirstSubTaskStartTime;

public:
    static constexpr auto Type = TASK_COMPLEX_GO_TO_BOAT_STEERING_WHEEL;

    explicit CTaskComplexGoToBoatSteeringWheel(CVehicle* vehicle);
    ~CTaskComplexGoToBoatSteeringWheel() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskComplexGoToBoatSteeringWheel(m_Vehicle); } // 0x64A350
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateSubTask(eTaskType taskType);

    void ComputeTargetPos();

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CTaskComplexGoToBoatSteeringWheel* Constructor(CVehicle* veh) { this->CTaskComplexGoToBoatSteeringWheel::CTaskComplexGoToBoatSteeringWheel(veh); return this; }
    CTaskComplexGoToBoatSteeringWheel* Destructor() { this->CTaskComplexGoToBoatSteeringWheel::~CTaskComplexGoToBoatSteeringWheel(); return this; }
};
VALIDATE_SIZE(CTaskComplexGoToBoatSteeringWheel, 0x24);
