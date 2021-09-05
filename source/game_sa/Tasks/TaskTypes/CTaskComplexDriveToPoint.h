#pragma once
#include "CTaskComplexCarDrive.h"
#include "CVehicle.h"

class CTaskComplexDriveToPoint : public CTaskComplexCarDrive
{
public:
    CVector point;
    int32 field_30;
    int32 field_34;
    int32 field_38;

    CTaskComplexDriveToPoint(CVehicle* vehicle, CVector& point, float speed, int32 arg4, int32 arg5, float arg6, int32 arg7);
    ~CTaskComplexDriveToPoint();
};

VALIDATE_SIZE(CTaskComplexDriveToPoint, 0x3C);
