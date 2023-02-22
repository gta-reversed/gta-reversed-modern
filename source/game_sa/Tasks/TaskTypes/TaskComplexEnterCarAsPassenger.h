/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskComplexEnterCar.h"

class CTaskComplexEnterCarAsPassenger : public CTaskComplexEnterCar {
public:
    static constexpr auto Type = TASK_COMPLEX_ENTER_CAR_AS_PASSENGER;

    CTaskComplexEnterCarAsPassenger(CVehicle* targetVehicle, int32 nTargetSeat = 0, bool bCarryOnAfterFallingOff = false);
    ~CTaskComplexEnterCarAsPassenger() override = default;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override;
};

VALIDATE_SIZE(CTaskComplexEnterCarAsPassenger, 0x50);
