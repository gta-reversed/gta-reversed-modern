#include "StdInc.h"

#include "CTaskComplexDriveToPoint.h"

CTaskComplexDriveToPoint::CTaskComplexDriveToPoint(CVehicle* vehicle, CVector& point, float speed, int32 arg4, int32 arg5, float arg6, int32 arg7) : CTaskComplexCarDrive(plugin::dummy)
{
    plugin::CallMethodAndReturn<CTaskComplexDriveToPoint*, 0x63CE00, CTaskComplexDriveToPoint*, CVehicle*, CVector&, float, int32, int32, float, int32>(this, vehicle, point, speed, arg4, arg5, arg6, arg7);
}

CTaskComplexDriveToPoint::~CTaskComplexDriveToPoint()
{
}

