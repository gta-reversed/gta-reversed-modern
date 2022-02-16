#include "StdInc.h"

#include "TaskSimpleCarSetPedInAsPassenger.h"

CTaskSimpleCarSetPedInAsPassenger::CTaskSimpleCarSetPedInAsPassenger(CVehicle* targetVehicle, int32 nTargetDoor, CTaskUtilityLineUpPedWithCar* utility)
{
    m_nTargetDoor = nTargetDoor;
    m_bIsFinished = 0;
    m_pAnim = 0;
    m_pTargetVehicle = targetVehicle;
    m_pUtility = utility;
    m_bWarpingInToCar = 0;
    m_nDoorFlagsToClear = 0;
    m_nNumGettingInToClear = 0;
    if (targetVehicle)
        targetVehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_pTargetVehicle));
}

CTaskSimpleCarSetPedInAsPassenger::~CTaskSimpleCarSetPedInAsPassenger()
{
    if (m_pTargetVehicle)
        m_pTargetVehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_pTargetVehicle));
}

CTask* CTaskSimpleCarSetPedInAsPassenger::Clone()
{
    return plugin::CallMethodAndReturn<CTask*, 0x649D90, CTask*>(this);
}

bool CTaskSimpleCarSetPedInAsPassenger::ProcessPed(CPed* ped)
{
    return plugin::CallMethodAndReturn<bool, 0x64B5D0, CTask*, CPed*>(this, ped);
}
