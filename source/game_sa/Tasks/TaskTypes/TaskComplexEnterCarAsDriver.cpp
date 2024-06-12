#include "StdInc.h"

#include "TaskComplexEnterCarAsDriver.h"

// 0x6402F0
CTaskComplexEnterCarAsDriver::CTaskComplexEnterCarAsDriver(CVehicle* targetVehicle) :
    CTaskComplexEnterCar(targetVehicle, true, false, false, false)
{
}

CTaskComplexEnterCarAsDriver::CTaskComplexEnterCarAsDriver(const CTaskComplexEnterCarAsDriver& o) :
    CTaskComplexEnterCarAsDriver{ o.m_Car }
{
    m_MoveState = o.m_MoveState;
}

// For 0x643780
CTaskComplexEnterCarAsDriver::CTaskComplexEnterCarAsDriver(const CTaskComplexEnterCarAsDriver& o) :
    CTaskComplexEnterCarAsDriver{ m_Car }
{
    m_MoveState = o.m_MoveState;
}
