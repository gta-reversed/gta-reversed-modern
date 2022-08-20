#include "StdInc.h"

#include "TaskSimpleCarDriveTimed.h"

CTaskSimpleCarDriveTimed* CTaskSimpleCarDriveTimed::Constructor(CVehicle* vehicle, int32 nTime) {
    this->CTaskSimpleCarDriveTimed::CTaskSimpleCarDriveTimed(vehicle, nTime);
    return this;
}

// 0x5FF940
CTaskSimpleCarDriveTimed::CTaskSimpleCarDriveTimed(CVehicle* vehicle, int32 nTime) : CTaskSimpleCarDrive(vehicle, nullptr, false), m_nTimer() {
    m_nTime = nTime;
}

bool CTaskSimpleCarDriveTimed::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x46F610, CTaskSimpleCarDriveTimed*, CPed*>(this, ped);
}
