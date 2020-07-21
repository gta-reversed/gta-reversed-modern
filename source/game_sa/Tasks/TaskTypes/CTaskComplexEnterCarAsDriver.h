/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskComplexEnterCar.h"

class CTaskComplexEnterCarAsDriver : public CTaskComplexEnterCar {
public:

    CTaskComplexEnterCarAsDriver(CVehicle* pTargetVehicle);
    ~CTaskComplexEnterCarAsDriver() {}

    CTask* Clone() override;
    eTaskType GetId() override { return TASK_COMPLEX_ENTER_CAR_AS_DRIVER; }

    CTask* Clone_Reversed();

};

VALIDATE_SIZE(CTaskComplexEnterCarAsDriver, 0x50);
