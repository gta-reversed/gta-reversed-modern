#pragma once
#include "CTaskComplexCarDrive.h"

class CTaskComplexCarDriveWander : public CTaskComplexCarDrive
{
public:
    CTaskComplexCarDriveWander(CVehicle *vehicle, int arg2, float fSpeed);

};

VALIDATE_SIZE(CTaskComplexCarDrive, 0x24);
