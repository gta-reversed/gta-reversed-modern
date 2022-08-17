#pragma once

#include "TaskComplexEnterCar.h"

class CTaskComplexOpenPassengerDoor : public CTaskComplexEnterCar {
public:
    static constexpr auto Type = TASK_COMPLEX_CAR_OPEN_PASSENGER_DOOR;

    CTaskComplexOpenPassengerDoor(CVehicle* vehicle, int32 targetSeat) : CTaskComplexEnterCar(vehicle, false, true, false, false) {
        m_nTargetSeat = targetSeat;
    } // 0x6403E0
    ~CTaskComplexOpenPassengerDoor() override = default; // 0x640420

    eTaskType GetTaskType() override{ return Type; } // 0x640410
    CTask* Clone() override { return new CTaskComplexOpenPassengerDoor(m_pTargetVehicle, m_nTargetSeat); } // 0x6438E0
};
