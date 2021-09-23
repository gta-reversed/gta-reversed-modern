#include "StdInc.h"

#include "CTaskComplexLeaveCar.h"

CTaskComplexLeaveCar::CTaskComplexLeaveCar(CVehicle* pTargetVehicle, int32 nTargetDoor, int32 nDelayTime, bool bSensibleLeaveCar, bool bForceGetOut) : CTaskComplex() {
    m_nTargetDoor                  = nTargetDoor;
    m_nDelayTime                   = nDelayTime;
    m_bSensibleLeaveCar            = bSensibleLeaveCar;
    m_pTargetVehicle               = pTargetVehicle;
    m_bForceGetOut                 = bForceGetOut;
    m_bDie                         = false;
    m_pTaskUtilityLineUpPedWithCar = nullptr;
    m_nDoorFlagsSet                = 0;
    m_nNumGettingInSet             = 0;
    m_nDieAnimID                   = ANIM_ID_KO_SHOT_FRONT_0;
    m_fDieAnimBlendDelta           = 4.0f;
    m_fDieAnimSpeed                = 1.0f;
    m_bIsInAir                     = false;

    if (pTargetVehicle)
        pTargetVehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_pTargetVehicle));
}

CTaskComplexLeaveCar::~CTaskComplexLeaveCar() {
    if (m_pTargetVehicle) {
        m_pTargetVehicle->ClearGettingOutFlags(m_nDoorFlagsSet);
        m_pTargetVehicle->m_nNumGettingIn -= m_nNumGettingInSet;
        m_pTargetVehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_pTargetVehicle));
    }

    delete m_pTaskUtilityLineUpPedWithCar;
}

CTaskComplexLeaveCar* CTaskComplexLeaveCar::Constructor(CVehicle* pTargetVehicle, int32 nTargetDoor, int32 nDelayTime, bool bSensibleLeaveCar, bool bForceGetOut) {
    return plugin::CallMethodAndReturn<CTaskComplexLeaveCar*, 0x63B8C0, CTaskComplexLeaveCar*, CVehicle*, int32, int32, bool, bool>(this, pTargetVehicle, nTargetDoor, nDelayTime, bSensibleLeaveCar, bForceGetOut);
}

CTask* CTaskComplexLeaveCar::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x63D9E0, CTask*>(this);
}

bool CTaskComplexLeaveCar::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x641100, CTask*, CPed*, int32, const CEvent*>(this, ped, priority, event);
}

CTask* CTaskComplexLeaveCar::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6419F0, CTask*, CPed*>(this, ped);
}

CTask* CTaskComplexLeaveCar::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x641FC0, CTask*, CPed*>(this, ped);
}

CTask* CTaskComplexLeaveCar::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6421B0, CTask*, CPed*>(this, ped);
}
