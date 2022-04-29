#include "StdInc.h"

#include "TaskSimpleCarSetPedInAsDriver.h"

CTaskSimpleCarSetPedInAsDriver::CTaskSimpleCarSetPedInAsDriver(CVehicle* targetVehicle, CTaskUtilityLineUpPedWithCar* utility)
{
    m_bIsFinished = 0;
    m_pAnim = 0;
    m_pTargetVehicle = targetVehicle;
    m_pUtility = utility;
    m_bWarpingInToCar = 0;
    m_nDoorFlagsToClear = 0;
    m_nNumGettingInToClear = 0;
    CEntity::SafeRegisterRef(m_pTargetVehicle);
}

CTaskSimpleCarSetPedInAsDriver::~CTaskSimpleCarSetPedInAsDriver()
{
    CEntity::SafeCleanUpRef(m_pTargetVehicle);
}

CTask* CTaskSimpleCarSetPedInAsDriver::Clone()
{
    return plugin::CallMethodAndReturn<CTask*, 0x649E00, CTask*>(this);
}

bool CTaskSimpleCarSetPedInAsDriver::ProcessPed(CPed* ped)
{
    return plugin::CallMethodAndReturn<bool, 0x64B950, CTask*, CPed*>(this, ped);
}
