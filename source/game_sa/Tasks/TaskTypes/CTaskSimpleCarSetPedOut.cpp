#include "StdInc.h"

CTaskSimpleCarSetPedOut::CTaskSimpleCarSetPedOut(CVehicle* pTargetVehicle, int nTargetDoor, bool bSwitchOffEngine)
{
    m_nTargetDoor = nTargetDoor;
    m_pTargetVehicle = pTargetVehicle;
    m_bSwitchOffEngine = bSwitchOffEngine;
    m_bWarpingOutOfCar = 0;
    m_bFallingOutOfCar = 0;
    m_bKnockedOffBike = 0;
    m_nDoorFlagsToClear = 0;
    m_nNumGettingInToClear = 0;
    if (pTargetVehicle)
        pTargetVehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_pTargetVehicle));
}

CTaskSimpleCarSetPedOut::~CTaskSimpleCarSetPedOut()
{
    if (m_pTargetVehicle)
        m_pTargetVehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_pTargetVehicle));
}

CTask* CTaskSimpleCarSetPedOut::Clone()
{
    return plugin::CallMethodAndReturn<CTask*, 0x649F50, CTask*>(this);
}

bool CTaskSimpleCarSetPedOut::ProcessPed(CPed* ped)
{
    return plugin::CallMethodAndReturn<bool, 0x647D10, CTask*, CPed*>(this, ped);
}
