/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskComplexEnterCar.h"

class CTaskComplexEnterCarAsDriver : public CTaskComplexEnterCar {
public:
    CTaskComplexEnterCarAsDriver(CVehicle* targetVehicle);
    ~CTaskComplexEnterCarAsDriver() {}

    CTask* Clone() override;
    eTaskType GetTaskType() override { return TASK_COMPLEX_ENTER_CAR_AS_DRIVER; }

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTask* Clone_Reversed();
};

VALIDATE_SIZE(CTaskComplexEnterCarAsDriver, 0x50);
