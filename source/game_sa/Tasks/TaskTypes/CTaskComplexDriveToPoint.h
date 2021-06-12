#pragma once
#include "CTaskComplexCarDrive.h"
#include "CVehicle.h"

class CTaskComplexDriveToPoint : public CTaskComplexCarDrive
{
public:
    CVector point;
    int field_30;
    int field_34;
    int field_38;

    CTaskComplexDriveToPoint(CVehicle* vehicle, CVector& point, float speed, int arg4, int arg5, float arg6, int arg7);
    ~CTaskComplexDriveToPoint();
};

VALIDATE_SIZE(CTaskComplexDriveToPoint, 0x3C);
