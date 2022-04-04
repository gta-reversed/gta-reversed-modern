#pragma once

#include "TaskComplexCarDrive.h"
#include "Vehicle.h"

class CTaskComplexDriveToPoint : public CTaskComplexCarDrive {
public:
    CVector point;
    int32   field_30;
    int32   field_34;
    int32   field_38;

public:
    static constexpr auto Type = TASK_COMPLEX_CAR_DRIVE_TO_POINT;

    CTaskComplexDriveToPoint(CVehicle* vehicle, CVector& point, float speed, int32 arg4, int32 arg5, float arg6, int32 arg7);
    ~CTaskComplexDriveToPoint();
};

VALIDATE_SIZE(CTaskComplexDriveToPoint, 0x3C);
