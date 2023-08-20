#include "StdInc.h"

#include "TaskComplexEnterCarAsPassenger.h"

// 0x640340
CTaskComplexEnterCarAsPassenger::CTaskComplexEnterCarAsPassenger(CVehicle* targetVehicle, int32 nTargetSeat, bool bCarryOnAfterFallingOff)
    : CTaskComplexEnterCar(targetVehicle, false, false, false, bCarryOnAfterFallingOff)
{
    m_targetSeat = nTargetSeat;
}

// For 0x6437F0
CTaskComplexEnterCarAsPassenger::CTaskComplexEnterCarAsPassenger(const CTaskComplexEnterCarAsPassenger& o) :
    CTaskComplexEnterCarAsPassenger{
        o.m_car,
        o.m_targetSeat,
        o.m_bCarryOnAfterFallingOff
    }
{
    m_moveState = o.m_moveState;
}
