#include "StdInc.h"

#include "TaskSimpleCarSetPedOut.h"

CTaskSimpleCarSetPedOut::CTaskSimpleCarSetPedOut(CVehicle* targetVehicle, int32 nTargetDoor, bool bSwitchOffEngine)
{
    m_nTargetDoor = nTargetDoor;
    m_pTargetVehicle = targetVehicle;
    m_bSwitchOffEngine = bSwitchOffEngine;
    m_bWarpingOutOfCar = 0;
    m_bFallingOutOfCar = 0;
    m_bKnockedOffBike = 0;
    m_nDoorFlagsToClear = 0;
    m_nNumGettingInToClear = 0;
    CEntity::SafeRegisterRef(m_pTargetVehicle);
}

CTaskSimpleCarSetPedOut::~CTaskSimpleCarSetPedOut()
{
    CEntity::SafeCleanUpRef(m_pTargetVehicle);
}

CTask* CTaskSimpleCarSetPedOut::Clone()
{
    return plugin::CallMethodAndReturn<CTask*, 0x649F50, CTask*>(this);
}

bool CTaskSimpleCarSetPedOut::ProcessPed(CPed* ped)
{
    return plugin::CallMethodAndReturn<bool, 0x647D10, CTask*, CPed*>(this, ped);
}
