#include "StdInc.h"

CTaskComplexEnterCarAsDriver::CTaskComplexEnterCarAsDriver(CVehicle* pTargetVehicle)
    : CTaskComplexEnterCar(pTargetVehicle, true, false, false, false)
{
    // empty
}

CTask* CTaskComplexEnterCarAsDriver::Clone()
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x643780, CTask*>(this);
#else
    return CTaskComplexEnterCarAsDriver::Clone_Reversed();
#endif
}

CTask* CTaskComplexEnterCarAsDriver::Clone_Reversed()
{
    auto pClonedTask = new CTaskComplexEnterCarAsDriver(m_pTargetVehicle);
    pClonedTask->m_nMoveState = m_nMoveState;
    return pClonedTask;
}
