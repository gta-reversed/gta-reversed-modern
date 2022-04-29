#include "StdInc.h"

#include "TaskComplexEnterCarAsDriver.h"

// 0x6402F0
CTaskComplexEnterCarAsDriver::CTaskComplexEnterCarAsDriver(CVehicle* targetVehicle) : CTaskComplexEnterCar(targetVehicle, true, false, false, false) {
    // empty
}

// 0x643780
CTask* CTaskComplexEnterCarAsDriver::Clone() {
    return CTaskComplexEnterCarAsDriver::Clone_Reversed();
}

CTask* CTaskComplexEnterCarAsDriver::Clone_Reversed() {
    auto clonedTask = new CTaskComplexEnterCarAsDriver(m_pTargetVehicle);
    clonedTask->m_nMoveState = m_nMoveState;
    return clonedTask;
}
