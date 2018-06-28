/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskComplexEnterCar.h"

class  CTaskComplexEnterCarAsDriver : public CTaskComplexEnterCar {
protected:
    CTaskComplexEnterCarAsDriver(plugin::dummy_func_t a) : CTaskComplexEnterCar(a) {}
public:

    CTaskComplexEnterCarAsDriver(CVehicle* pTargetVehicle);

};

VALIDATE_SIZE(CTaskComplexEnterCarAsDriver, 0x50);
