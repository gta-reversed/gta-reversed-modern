/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskComplex.h"
#include "Vehicle.h"
#include "Ped.h"

class CTaskComplexCopInCar : public CTaskComplex {
public:
    CVehicle*  m_pVehicle;
    CPed*      m_pCop1;
    CPed*      m_pCop2;
    CTaskTimer m_timer1;
    CTaskTimer m_timer2;
    uint8      m_nFlags;
    char       _flags[3];

public:
    CTaskComplexCopInCar(CVehicle* vehicle, CPed* cop1, CPed* cop2, bool arg3);
};

VALIDATE_SIZE(CTaskComplexCopInCar, 0x34);
