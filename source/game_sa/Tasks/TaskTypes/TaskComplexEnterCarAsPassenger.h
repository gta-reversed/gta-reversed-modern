/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CTaskComplexEnterCar.h"

class CTaskComplexEnterCarAsPassenger : public CTaskComplexEnterCar {
public:
    CTaskComplexEnterCarAsPassenger(CVehicle* pTargetVehicle, int32 nTargetSeat, bool bCarryOnAfterFallingOff);
    ~CTaskComplexEnterCarAsPassenger() {}

    CTask* Clone() override;
    eTaskType GetTaskType() override { return TASK_COMPLEX_ENTER_CAR_AS_PASSENGER; }
};

VALIDATE_SIZE(CTaskComplexEnterCarAsPassenger, 0x50);
