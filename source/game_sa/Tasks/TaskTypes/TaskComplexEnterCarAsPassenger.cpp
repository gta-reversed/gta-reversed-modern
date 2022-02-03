#include "StdInc.h"

#include "TaskComplexEnterCarAsPassenger.h"

// 0x640340
CTaskComplexEnterCarAsPassenger::CTaskComplexEnterCarAsPassenger(CVehicle* targetVehicle, int32 nTargetSeat, bool bCarryOnAfterFallingOff)
    : CTaskComplexEnterCar(targetVehicle, false, false, false, bCarryOnAfterFallingOff)
{
    m_nTargetSeat = nTargetSeat;
}

CTask* CTaskComplexEnterCarAsPassenger::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x6437F0, CTask*>(this);
}
