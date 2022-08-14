#pragma once
#include "TaskComplex.h"

class CTaskComplexGoToBoatSteeringWheel : public CTaskComplex {
public:
    static void InjectHooks();

    CTaskComplexGoToBoatSteeringWheel(CVehicle* veh);
    ~CTaskComplexGoToBoatSteeringWheel();

    static constexpr auto Type = eTaskType::TASK_COMPLEX_GO_TO_BOAT_STEERING_WHEEL;

    virtual CTask* Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual CTask* CreateNextSubTask(CPed* ped);
    virtual CTask* CreateFirstSubTask(CPed* ped);
    virtual CTask* ControlSubTask(CPed* ped);

private: // Wrappers for hooks
    // 0x649090
    CTaskComplexGoToBoatSteeringWheel* Constructor(CVehicle* veh) {
        this->CTaskComplexGoToBoatSteeringWheel::CTaskComplexGoToBoatSteeringWheel(veh);
        return this;
    }

    // 0x649100
    CTaskComplexGoToBoatSteeringWheel* Destructor() {
        this->CTaskComplexGoToBoatSteeringWheel::~CTaskComplexGoToBoatSteeringWheel();
        return this;
    }
};
