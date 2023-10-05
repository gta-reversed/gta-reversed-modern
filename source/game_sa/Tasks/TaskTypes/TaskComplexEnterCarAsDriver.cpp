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

// For 0x643780
CTaskComplexEnterCarAsDriver::CTaskComplexEnterCarAsDriver(const CTaskComplexEnterCarAsDriver& o) :
    CTaskComplexEnterCarAsDriver{ m_car }
{
    m_moveState = o.m_moveState;
}
