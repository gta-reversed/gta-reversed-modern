/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CVehicle.h"

#define UPSIDE_DOWN_CAR_CHECK_SIZE    6

struct UpsideDownCar {
    int m_nCarHandle;
    int m_nTime;
};

class CUpsideDownCarCheck {
public:
    UpsideDownCar m_aUpsideDownCars[UPSIDE_DOWN_CAR_CHECK_SIZE];

public:
    static void InjectHooks();

    void Init();
    static bool IsCarUpsideDown(CVehicle const* vehicle);
    bool AreAnyCarsUpsideDown();
    void UpdateTimers();
    void AddCarToCheck(int carHandle);
    void RemoveCarFromCheck(int carHandle);
    bool HasCarBeenUpsideDownForAWhile(int carHandle);
};

VALIDATE_SIZE(CUpsideDownCarCheck, 0x30);

//#include "meta/meta.CUpsideDownCarCheck.h"
