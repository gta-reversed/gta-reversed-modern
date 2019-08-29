#include "StdInc.h"

CTaskSimpleCarDrive* CTaskSimpleCarDrive::Constructor(CVehicle* pVehicle, int arg2, bool arg3)
{
    return plugin::CallMethodAndReturn<CTaskSimpleCarDrive*, 0x63C340, CTaskSimpleCarDrive*, CVehicle*, int, bool>(this, pVehicle, arg2, arg3);
}