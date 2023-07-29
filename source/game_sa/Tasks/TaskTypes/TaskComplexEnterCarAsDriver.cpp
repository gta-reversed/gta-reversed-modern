#include "StdInc.h"

#include "TaskComplexEnterCarAsDriver.h"

// 0x6402F0
CTaskComplexEnterCarAsDriver::CTaskComplexEnterCarAsDriver(CVehicle* targetVehicle) :
    CTaskComplexEnterCar(targetVehicle, true, false, false, false)
{
}

CTaskComplexEnterCarAsDriver::CTaskComplexEnterCarAsDriver(CVehicle* targetVehicle, eMoveState moveState) : // NOTSA
    CTaskComplexEnterCarAsDriver{ targetVehicle }
{
    m_moveState = moveState;
}

// 0x643780
CTask* CTaskComplexEnterCarAsDriver::Clone() {
    auto task = new CTaskComplexEnterCarAsDriver(m_car);
    task->m_moveState = m_moveState;
    return task;
}
