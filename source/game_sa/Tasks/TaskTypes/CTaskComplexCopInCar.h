/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskComplex.h"
#include "CVehicle.h"
#include "CPed.h"

class  CTaskComplexCopInCar : public CTaskComplex {
public:
    CVehicle *m_pVehicle;
    CPed *m_pCop1;
    CPed *m_pCop2;
    CTaskTimer m_timer1;
    CTaskTimer m_timer2;
    unsigned char m_nFlags;
    char __flags[3];

    CTaskComplexCopInCar(CVehicle* pVeh, CPed* pCop1, CPed* pCop2, bool arg3);
};

VALIDATE_SIZE(CTaskComplexCopInCar, 0x34);

