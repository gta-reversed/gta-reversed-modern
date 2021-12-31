/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vehicle.h"

#define UPSIDE_DOWN_CAR_CHECK_SIZE 6

struct UpsideDownCar {
    int32 m_nCarHandle;
    uint32 m_nTime;
};

class CUpsideDownCarCheck {
public:
    UpsideDownCar m_aUpsideDownCars[UPSIDE_DOWN_CAR_CHECK_SIZE];

public:
    static void InjectHooks();

    void        Init();
    static bool IsCarUpsideDown(CVehicle* vehicle);
    bool        AreAnyCarsUpsideDown();
    void        UpdateTimers();
    void        AddCarToCheck(int32 carHandle);
    void        RemoveCarFromCheck(int32 carHandle);
    bool        HasCarBeenUpsideDownForAWhile(int32 carHandle);
};

VALIDATE_SIZE(CUpsideDownCarCheck, 0x30);
