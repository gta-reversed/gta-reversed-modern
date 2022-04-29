#include "StdInc.h"
#include "TaskSimpleStandStill.h"
#include "TaskSimpleWaitUntilPedIsOutCar.h"

void CTaskSimpleWaitUntilPedIsOutCar::InjectHooks() {
    RH_ScopedClass(CTaskSimpleWaitUntilPedIsOutCar);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x649450);
    RH_ScopedInstall(Destructor, 0x6494F0);
    RH_ScopedInstall(Clone_Reversed, 0x64A4B0);
    RH_ScopedInstall(GetTaskType_Reversed, 0x6494D0);
    RH_ScopedInstall(MakeAbortable_Reversed, 0x6494E0);
    RH_ScopedInstall(ProcessPed_Reversed, 0x649550);
}

// 0x649450
CTaskSimpleWaitUntilPedIsOutCar::CTaskSimpleWaitUntilPedIsOutCar(CPed* ped, CVector const& pos) : CTaskSimple(),
    m_PedToWaitFor{ ped },
    m_Pos{ pos },
    m_bIsNotGoingTowardsPos{ true }
{
    CEntity::SafeRegisterRef(m_PedToWaitFor);
}

// 0x6494F0
CTaskSimpleWaitUntilPedIsOutCar::~CTaskSimpleWaitUntilPedIsOutCar() {
    CEntity::SafeCleanUpRef(m_PedToWaitFor);
}

// 0x649550
bool CTaskSimpleWaitUntilPedIsOutCar::ProcessPed(CPed* ped) {
    if (!m_PedToWaitFor) {
        return true;
    }

    if (m_bIsNotGoingTowardsPos) {
        m_bIsNotGoingTowardsPos = false;

        CTaskSimpleStandStill standStillTask;
        standStillTask.ProcessPed(ped);

        ped->m_fAimingRotation = CGeneral::LimitRadianAngle(CGeneral::GetAngleBetweenPoints(m_Pos.x, m_Pos.y, 0.f, 0.f));
    }

    return !m_PedToWaitFor->bInVehicle;
}
