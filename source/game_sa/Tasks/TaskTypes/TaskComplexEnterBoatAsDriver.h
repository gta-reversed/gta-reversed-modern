/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskComplex.h"
#include "Vehicle.h"

class CTaskComplexEnterBoatAsDriver : public CTaskComplex {
public:
    CVehicle* m_pTargetVehicle;

public:
    static constexpr auto Type = TASK_COMPLEX_ENTER_BOAT_AS_DRIVER;

    CTaskComplexEnterBoatAsDriver(CVehicle* targetVehicle);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

};

VALIDATE_SIZE(CTaskComplexEnterBoatAsDriver, 0x10);

