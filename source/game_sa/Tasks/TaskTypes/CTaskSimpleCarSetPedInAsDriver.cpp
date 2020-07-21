#include "StdInc.h"

CTaskSimpleCarSetPedInAsDriver::CTaskSimpleCarSetPedInAsDriver(CVehicle* pTargetVehicle, CTaskUtilityLineUpPedWithCar* pUtility)
{
    m_bIsFinished = 0;
    m_pAnim = 0;
    m_pTargetVehicle = pTargetVehicle;
    m_pUtility = pUtility;
    m_bWarpingInToCar = 0;
    m_nDoorFlagsToClear = 0;
    m_nNumGettingInToClear = 0;
    if (pTargetVehicle)
        pTargetVehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_pTargetVehicle));
}

CTaskSimpleCarSetPedInAsDriver::~CTaskSimpleCarSetPedInAsDriver()
{
    if (m_pTargetVehicle)
        m_pTargetVehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_pTargetVehicle));
}

CTask* CTaskSimpleCarSetPedInAsDriver::Clone()
{
    return plugin::CallMethodAndReturn<CTask*, 0x649E00, CTask*>(this);
}

bool CTaskSimpleCarSetPedInAsDriver::ProcessPed(CPed* ped)
{
    return plugin::CallMethodAndReturn<bool, 0x64B950, CTask*, CPed*>(this, ped);
}
