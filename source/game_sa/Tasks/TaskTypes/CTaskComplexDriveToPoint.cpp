#include "StdInc.h"

CTaskComplexDriveToPoint::CTaskComplexDriveToPoint(CVehicle* vehicle, CVector& point, float speed, int arg4, int arg5, float arg6, int arg7) : CTaskComplexCarDrive(plugin::dummy)
{
    plugin::CallMethodAndReturn<CTaskComplexDriveToPoint*, 0x63CE00, CTaskComplexDriveToPoint*, CVehicle*, CVector&, float, int, int, float, int>(this, vehicle, point, speed, arg4, arg5, arg6, arg7);
}

CTaskComplexDriveToPoint::~CTaskComplexDriveToPoint()
{
}

