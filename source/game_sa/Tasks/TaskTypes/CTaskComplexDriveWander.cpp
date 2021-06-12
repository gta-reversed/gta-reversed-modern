#include "StdInc.h"

CTaskComplexCarDriveWander::CTaskComplexCarDriveWander(CVehicle* vehicle, int arg2, float fSpeed) : CTaskComplexCarDrive(plugin::dummy)
{
    plugin::CallMethodAndReturn< CTaskComplexCarDriveWander*, 0x63CB10, CTaskComplexCarDriveWander*, CVehicle*, int, float>(this, vehicle, arg2, fSpeed);
}
