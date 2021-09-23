#include "StdInc.h"

#include "CTaskSimpleCarDrive.h"

CTaskSimpleCarDrive* CTaskSimpleCarDrive::Constructor(CVehicle* pVehicle, CTaskUtilityLineUpPedWithCar* pUtilityTask, bool bUpdateCurrentVehicle)
{
    return plugin::CallMethodAndReturn<CTaskSimpleCarDrive*, 0x63C340, CTaskSimpleCarDrive*, CVehicle*, CTaskUtilityLineUpPedWithCar*, bool>(this, pVehicle, pUtilityTask, bUpdateCurrentVehicle);
}

CTaskSimpleCarDrive::CTaskSimpleCarDrive(CVehicle* pVehicle, CTaskUtilityLineUpPedWithCar* pUtilityTask, bool bUpdateCurrentVehicle)
{
    plugin::CallMethodAndReturn<CTaskSimpleCarDrive*, 0x63C340, CTaskSimpleCarDrive*, CVehicle*, CTaskUtilityLineUpPedWithCar*, bool>(this, pVehicle, pUtilityTask, bUpdateCurrentVehicle);
}

bool CTaskSimpleCarDrive::ProcessPed(CPed* ped)
{
    return plugin::CallMethodAndReturn<bool, 0x644470, CTaskSimpleCarDrive*, CPed*>(this, ped);
}

CTask* CTaskSimpleCarDrive::Clone()
{
    return plugin::CallMethodAndReturn<CTask*, 0x63DC20, CTaskSimpleCarDrive*>(this);
}

bool CTaskSimpleCarDrive::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event)
{
    return plugin::CallMethodAndReturn<bool, 0x63DC20, CTaskSimpleCarDrive*, CPed*, eAbortPriority, const CEvent*>(this, ped, priority, event);
}
