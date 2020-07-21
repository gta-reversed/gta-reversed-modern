#include "StdInc.h"


CTaskComplexEnterCarAsPassenger::CTaskComplexEnterCarAsPassenger(CVehicle* pTargetVehicle, int nTargetSeat, bool bCarryOnAfterFallingOff) :
    CTaskComplexEnterCar(pTargetVehicle, false, false, false, bCarryOnAfterFallingOff)
{
    m_nTargetSeat = nTargetSeat;
}

CTask* CTaskComplexEnterCarAsPassenger::Clone()
{
    return plugin::CallMethodAndReturn<CTask*, 0x6437F0, CTask*>(this);
}
