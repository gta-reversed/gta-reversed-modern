#include "StdInc.h"

#include "CTaskComplexCarDrive.h"

// 0x63C9D0
CTaskComplexCarDrive::CTaskComplexCarDrive(CVehicle* vehicle) : CTaskComplex() {
    plugin::CallMethodAndReturn<CTaskComplexCarDrive*, 0x63C9D0, CTaskComplexCarDrive*, CVehicle*>(this, vehicle);
}

CTaskComplexCarDrive::CTaskComplexCarDrive(CVehicle* vehicle, float arg2, int32 arg3, int32 arg4) : CTaskComplex() {
    plugin::CallMethodAndReturn<CTaskComplexCarDrive*, 0x63C940, CTaskComplexCarDrive*, CVehicle*, float, int32, int32>(this, vehicle, arg2, arg3, arg4);
}

CTaskComplexCarDrive::~CTaskComplexCarDrive() {
    plugin::CallMethod<0x63CA40, CTaskComplexCarDrive*>(this);
}

CTask* CTaskComplexCarDrive::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x63DC90, CTaskComplexCarDrive*>(this);
}

CTask* CTaskComplexCarDrive::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x644E20, CTaskComplexCarDrive*, CPed*>(this, ped);
}

CTask* CTaskComplexCarDrive::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x645100, CTaskComplexCarDrive*, CPed*>(this, ped);
}

CTask* CTaskComplexCarDrive::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x645240, CTaskComplexCarDrive*, CPed*>(this, ped);
}

void CTaskComplexCarDrive::SetUpCar() {
    plugin::CallMethod<0x63CAE0, CTaskComplexCarDrive*>(this);
}

CTask* CTaskComplexCarDrive::CreateSubTaskCannotGetInCar(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x643200, CTaskComplexCarDrive*, CPed*>(this, ped);
}

CTask* CTaskComplexCarDrive::Drive(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x63CAD0, CTaskComplexCarDrive*, CPed*>(this, ped);
}
