#include "StdInc.h"

CTaskComplexLeaveCar::CTaskComplexLeaveCar(CVehicle* pTargetVehicle, int nTargetDoor, int nDelayTime, bool bSensibleLeaveCar, bool bForceGetOut)
{
    m_nTargetDoor = nTargetDoor;
    m_nDelayTime = nDelayTime;
    m_bSensibleLeaveCar = bSensibleLeaveCar;
    m_pTargetVehicle = pTargetVehicle;
    m_bForceGetOut = bForceGetOut;
    m_bDie = 0;
    m_pTaskUtilityLineUpPedWithCar = 0;
    m_nDoorFlagsSet = 0;
    m_nNumGettingInSet = 0;
    m_nDieAnimID = ANIM_ID_KO_SHOT_FRONT_0;
    m_fDieAnimBlendDelta = 4.0f;
    m_fDieAnimSpeed = 1.0f;
    m_bIsInAir = 0;
    if (pTargetVehicle)
        pTargetVehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_pTargetVehicle));
}

CTaskComplexLeaveCar::~CTaskComplexLeaveCar()
{
    if (m_pTargetVehicle) {
        m_pTargetVehicle->ClearGettingOutFlags(m_nDoorFlagsSet);
        m_pTargetVehicle->m_nNumGettingIn -= m_nNumGettingInSet;
        m_pTargetVehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_pTargetVehicle));
    }
    if (m_pTaskUtilityLineUpPedWithCar)
        delete m_pTaskUtilityLineUpPedWithCar;
}

CTaskComplexLeaveCar* CTaskComplexLeaveCar::Constructor(CVehicle* pTargetVehicle, int nTargetDoor, int nDelayTime, bool bSensibleLeaveCar, bool bForceGetOut)
{
    return plugin::CallMethodAndReturn< CTaskComplexLeaveCar*, 0x63B8C0, CTaskComplexLeaveCar*, CVehicle*, int, int, bool, bool>
        (this, pTargetVehicle, nTargetDoor, nDelayTime, bSensibleLeaveCar, bForceGetOut);
}

CTask* CTaskComplexLeaveCar::Clone()
{
    return plugin::CallMethodAndReturn<CTask*, 0x63D9E0, CTask*>(this);
}

bool CTaskComplexLeaveCar::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    return plugin::CallMethodAndReturn<bool, 0x641100, CTask*, CPed*, int, CEvent*>(this, ped, priority, _event);
}

CTask* CTaskComplexLeaveCar::CreateNextSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x6419F0, CTask*, CPed*>(this, ped);
}

CTask* CTaskComplexLeaveCar::CreateFirstSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x641FC0, CTask*, CPed*>(this, ped);
}

CTask* CTaskComplexLeaveCar::ControlSubTask(CPed* ped)
{ 
    return plugin::CallMethodAndReturn<CTask*, 0x6421B0, CTask*, CPed*>(this, ped);
}
