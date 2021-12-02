#include "StdInc.h"

#include "TaskSimpleCarDrive.h"

CTaskSimpleCarDrive::CTaskSimpleCarDrive(CVehicle* vehicle, CTaskUtilityLineUpPedWithCar* utilityTask, bool updateCurrentVehicle) {
    plugin::CallMethodAndReturn<CTaskSimpleCarDrive*, 0x63C340, CTaskSimpleCarDrive*, CVehicle*, CTaskUtilityLineUpPedWithCar*, bool>(this, vehicle, utilityTask, updateCurrentVehicle);
}

bool CTaskSimpleCarDrive::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x644470, CTaskSimpleCarDrive*, CPed*>(this, ped);
}

CTask* CTaskSimpleCarDrive::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x63DC20, CTaskSimpleCarDrive*>(this);
}

bool CTaskSimpleCarDrive::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x63DC20, CTaskSimpleCarDrive*, CPed*, eAbortPriority, const CEvent*>(this, ped, priority, event);
}

void CTaskSimpleCarDrive::InjectHooks() {
    
}

CTaskSimpleCarDrive* CTaskSimpleCarDrive::Constructor(CVehicle* vehicle, CTaskUtilityLineUpPedWithCar* utilityTask, bool updateCurrentVehicle) {
    this->CTaskSimpleCarDrive::CTaskSimpleCarDrive(vehicle, utilityTask, updateCurrentVehicle);
    return this;
}
