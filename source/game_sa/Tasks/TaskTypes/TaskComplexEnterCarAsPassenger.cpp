#include "StdInc.h"

#include "TaskComplexEnterCarAsPassenger.h"

// 0x640340
CTaskComplexEnterCarAsPassenger::CTaskComplexEnterCarAsPassenger(CVehicle* targetVehicle, int32 nTargetSeat, bool bCarryOnAfterFallingOff)
    : CTaskComplexEnterCar(targetVehicle, false, false, false, bCarryOnAfterFallingOff)
{
    m_nTargetSeat = nTargetSeat;
}

// 0x6437F0
CTask* CTaskComplexEnterCarAsPassenger::Clone() {
    auto task = new CTaskComplexEnterCarAsPassenger(m_pTargetVehicle, m_nTargetSeat, m_bCarryOnAfterFallingOff);
    task->m_nMoveState = m_nMoveState;
    return task;
}
