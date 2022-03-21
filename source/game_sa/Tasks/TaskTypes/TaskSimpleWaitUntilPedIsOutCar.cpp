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
CTaskSimpleWaitUntilPedIsOutCar::CTaskSimpleWaitUntilPedIsOutCar(CPed* ped, CVector const& pos) :
    m_pedToWaitFor{ped},
    m_pos{pos}
{
    if (m_pedToWaitFor) {
        m_pedToWaitFor->RegisterReference(reinterpret_cast<CEntity**>(&m_pedToWaitFor));
    }
}

// 0x6494F0
CTaskSimpleWaitUntilPedIsOutCar::~CTaskSimpleWaitUntilPedIsOutCar() {
    CEntity::ClearReference(m_pedToWaitFor);
}

// 0x64A4B0
CTask* CTaskSimpleWaitUntilPedIsOutCar::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x64A4B0, CTaskSimpleWaitUntilPedIsOutCar*>(this);
}

// 0x649550
bool CTaskSimpleWaitUntilPedIsOutCar::ProcessPed(CPed* ped) {
    if (!m_pedToWaitFor) {
        return true;
    }

    if (m_isNotGoingTowardsPos) {
        m_isNotGoingTowardsPos = false;

        CTaskSimpleStandStill standStillTask{};
        standStillTask.ProcessPed(ped);

        ped->m_fAimingRotation = CGeneral::LimitRadianAngle(CGeneral::GetAngleBetweenPoints(m_pos.x, m_pos.y, 0.f, 0.f));
    }

    return !m_pedToWaitFor->bInVehicle;
}
