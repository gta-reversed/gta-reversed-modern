#include "StdInc.h"

#include "TaskComplexDriveWander.h"

CTaskComplexCarDriveWander::CTaskComplexCarDriveWander(CVehicle* vehicle, int32 arg2, float fSpeed) : CTaskComplexCarDrive(vehicle) {
    plugin::CallMethodAndReturn<CTaskComplexCarDriveWander*, 0x63CB10, CTaskComplexCarDriveWander*, CVehicle*, int32, float>(this, vehicle, arg2, fSpeed);
}
