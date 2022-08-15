#include "StdInc.h"

#include "TaskComplexDriveToPoint.h"
// #include "TaskComplexGoToPointAnyMeans.h"

// 0x63CE00
CTaskComplexDriveToPoint::CTaskComplexDriveToPoint(CVehicle* vehicle, CVector& point, float speed, int32 arg4, int32 arg5, float arg6, int32 arg7) : CTaskComplexCarDrive(vehicle) {
    plugin::CallMethodAndReturn<CTaskComplexDriveToPoint*, 0x63CE00, CTaskComplexDriveToPoint*, CVehicle*, CVector&, float, int32, int32, float, int32>(this, vehicle, point, speed, arg4, arg5, arg6, arg7);
}

// 0x63CE80
CTask* CTaskComplexDriveToPoint::CreateSubTaskCannotGetInCar(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x63CE80, CTaskComplexDriveToPoint*, CPed*>(this, ped);
    // return new CTaskComplexGoToPointAnyMeans(6, m_Point, 0.5f, m_carModelIndexToCreate);
}
