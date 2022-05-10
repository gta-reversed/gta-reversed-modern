#pragma once

#include "TaskComplexCarDrive.h"

class CTaskComplexCarDriveWander : public CTaskComplexCarDrive {
public:
    static constexpr auto Type = TASK_COMPLEX_CAR_DRIVE_WANDER;

    CTaskComplexCarDriveWander(CVehicle* vehicle, int32 arg2, float fSpeed);
};

VALIDATE_SIZE(CTaskComplexCarDrive, 0x24);
