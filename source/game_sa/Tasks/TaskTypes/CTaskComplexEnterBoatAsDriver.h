/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "CTaskComplex.h"
#include "CVehicle.h"

class CTaskComplexEnterBoatAsDriver : public CTaskComplex {
public:
    CVehicle* m_pTargetVehicle;

    CTaskComplexEnterBoatAsDriver(CVehicle* pTargetVehicle);

};

VALIDATE_SIZE(CTaskComplexEnterBoatAsDriver, 0x10);

