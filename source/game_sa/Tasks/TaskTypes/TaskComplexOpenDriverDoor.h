#pragma once

#include "TaskComplexEnterCar.h"
class CVehicle;

class CTaskComplexOpenDriverDoor : public CTaskComplexEnterCar {
public:
    static constexpr auto Type = TASK_COMPLEX_CAR_OPEN_DRIVER_DOOR;

    explicit CTaskComplexOpenDriverDoor(CVehicle* vehicle) : CTaskComplexEnterCar(vehicle, true, true, false, false) {
        m_nTargetSeat = 10;
    } // 0x640390
    ~CTaskComplexOpenDriverDoor() override = default;

    eTaskType GetTaskType() override { return Type; } // 0x6403C0
    CTask* Clone() override {
        auto task = new CTaskComplexOpenDriverDoor(m_pTargetVehicle);
        task->m_nMoveState = m_nMoveState;
        return task;
    } // 0x643870
};
