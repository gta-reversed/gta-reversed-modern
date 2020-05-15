#include "StdInc.h"

CTaskSimpleCarDrive* CTaskSimpleCarDrive::Constructor(CVehicle* pVehicle, CTaskUtilityLineUpPedWithCar* pUtilityTask, bool bUpdateCurrentVehicle)
{
    return plugin::CallMethodAndReturn<CTaskSimpleCarDrive*, 0x63C340, CTaskSimpleCarDrive*, CVehicle*, CTaskUtilityLineUpPedWithCar*, bool>(this, pVehicle, pUtilityTask, bUpdateCurrentVehicle);
}
