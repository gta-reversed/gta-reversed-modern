#include "StdInc.h"

CTaskSimpleCarDriveTimed* CTaskSimpleCarDriveTimed::Constructor(CVehicle* pVehicle, int arg2)
{
    return plugin::CallMethodAndReturn< CTaskSimpleCarDriveTimed*, 0x5FF940, CTaskSimpleCarDriveTimed*, CVehicle*, int>(this, pVehicle, arg2);
}