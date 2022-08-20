#include "StdInc.h"
#include "TaskSimpleCarWaitToSlowDown.h"

void CTaskSimpleCarWaitToSlowDown::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleCarWaitToSlowDown, 0x86ed98, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x646990);
    RH_ScopedInstall(Destructor, 0x646A00);

    RH_ScopedVMTInstall(Clone, 0x649CB0);
    RH_ScopedVMTInstall(GetTaskType, 0x6469F0);
    RH_ScopedVMTInstall(MakeAbortable, 0x646A60);
    RH_ScopedVMTInstall(ProcessPed, 0x646AD0);
    RH_ScopedVMTInstall(SetPedPosition, 0x646AB0);
}

// 0x646990
CTaskSimpleCarWaitToSlowDown::CTaskSimpleCarWaitToSlowDown(CVehicle* veh, SlowDownType type) :
    m_veh{veh},
    m_type{type}
{
    CEntity::SafeRegisterRef(m_veh);
}

// 0x646A00
CTaskSimpleCarWaitToSlowDown::~CTaskSimpleCarWaitToSlowDown() {
    CEntity::SafeCleanUpRef(m_veh);
}

// 0x646A60
bool CTaskSimpleCarWaitToSlowDown::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    switch (priority) {
    case ABORT_PRIORITY_IMMEDIATE:
        return true;
    case ABORT_PRIORITY_URGENT: {
        if (event && event->GetEventType() == EVENT_DAMAGE) {
            const auto dmg = static_cast<const CEventDamage*>(event);
            if (dmg->m_damageResponse.m_bHealthZero && dmg->m_bAddToEventGroup) {
                return true;
            }
        }
        break;
    }
    }
    m_type = SlowDownType::DONE;
    return false;
}

// 0x646AD0
bool CTaskSimpleCarWaitToSlowDown::ProcessPed(CPed* ped) {
    if (!m_veh || m_type == SlowDownType::DONE) {
        return true;
    }

    if (const auto driver = m_veh->m_pDriver) {
        if (!driver->IsPlayer() && ped == driver) {
            // Start stopping the car completely

            auto& ap = m_veh->m_autoPilot;
            ap.m_nCruiseSpeed = 0;
            ap.m_nCarMission = MISSION_NONE;
        }
    }

    switch (m_type) {
    case SlowDownType::PED_STEP_OUT:
        return m_veh->CanPedStepOutCar(false);
    case SlowDownType::PED_STEP_OUT_OR_JUMP: {
        return m_veh->CanPedStepOutCar(false) || m_veh->CanPedJumpOutCar(ped);
    }
    }

    return false;
}

// 0x646AB0
bool CTaskSimpleCarWaitToSlowDown::SetPedPosition(CPed* ped) {
    if (m_veh) {
        ped->SetPedPositionInCar();
    }
    return true;
}
