#include "StdInc.h"

#include "TaskSimpleWaitUntilPedIsInCar.h"

void CTaskSimpleWaitUntilPedIsInCar::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleWaitUntilPedIsInCar, 0x86f0b8, 9);
    RH_ScopedCategory("Tasks/TaskTypes");
    RH_ScopedVMTInstall(ProcessPed, 0x649700);
}

// 0x649620
CTaskSimpleWaitUntilPedIsInCar::CTaskSimpleWaitUntilPedIsInCar(CPed* targetPed) :
    CTaskSimple(),
    m_TargetPed{ targetPed }
{
    CEntity::SafeRegisterRef(m_TargetPed);
}

// 0x6496A0
CTaskSimpleWaitUntilPedIsInCar::~CTaskSimpleWaitUntilPedIsInCar() {
    CEntity::SafeCleanUpRef(m_TargetPed);
}

// 0x649700
bool CTaskSimpleWaitUntilPedIsInCar::ProcessPed(CPed* ped) {
    ped->SetMoveState(PEDMOVE_STILL);

    if (!m_TargetPed) {
        return true;
    }

    if (m_TargetPed->GetTaskManager().Find<TASK_COMPLEX_GO_TO_CAR_DOOR_AND_STAND_STILL>()) {
        m_bIsWalkingToDoor = true;
        return m_TargetPed->bInVehicle;
    }

    if (m_bIsWalkingToDoor) {
        return true;
    }
    if (m_TargetPed->GetTaskManager().Find<TASK_SIMPLE_CAR_GET_IN>()) {
        return true;
    }
    if (!m_TargetPed->IsPlayer() && m_TargetPed->bStuckUnderCar) {
        return true;
    }

    return m_TargetPed->bInVehicle;
}
