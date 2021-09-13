#include "StdInc.h"

#include "CTaskComplexDriveWander.h"

CTaskComplexCarDriveWander::CTaskComplexCarDriveWander(CVehicle* vehicle, int32 arg2, float fSpeed) : CTaskComplexCarDrive(plugin::dummy)
{
    plugin::CallMethodAndReturn< CTaskComplexCarDriveWander*, 0x63CB10, CTaskComplexCarDriveWander*, CVehicle*, int32, float>(this, vehicle, arg2, fSpeed);
}
