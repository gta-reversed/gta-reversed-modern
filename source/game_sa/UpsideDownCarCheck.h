/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vehicle.h"

struct UpsideDownCar {
    int32 m_nHandle;
    uint32 m_nTime;
};

class CUpsideDownCarCheck {
public:
    static constexpr auto UPSIDE_DOWN_CAR_CHECK_SIZE{ 6u };
    UpsideDownCar m_aUpsideDownCars[UPSIDE_DOWN_CAR_CHECK_SIZE];

public:
    static void InjectHooks();

    void        Init();
    static bool IsCarUpsideDown(CVehicle* vehicle);
    bool        AreAnyCarsUpsideDown();
    void        UpdateTimers();
    void        AddCarToCheck(int32 car);
    void        RemoveCarFromCheck(int32 carHandle);
    bool        HasCarBeenUpsideDownForAWhile(int32 car);
};

VALIDATE_SIZE(CUpsideDownCarCheck, 0x30);
