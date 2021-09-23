#include "StdInc.h"

#include "CTaskComplexEnterCarAsPassenger.h"

// 0x640340
CTaskComplexEnterCarAsPassenger::CTaskComplexEnterCarAsPassenger(CVehicle* pTargetVehicle, int32 nTargetSeat, bool bCarryOnAfterFallingOff)
    : CTaskComplexEnterCar(pTargetVehicle, false, false, false, bCarryOnAfterFallingOff)
{
    m_nTargetSeat = nTargetSeat;
}

CTask* CTaskComplexEnterCarAsPassenger::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x6437F0, CTask*>(this);
}
