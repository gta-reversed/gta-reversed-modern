#include "StdInc.h"

#include "TaskLeanOnVehicle.h"

void CTaskLeanOnVehicle::InjectHooks() {
    RH_ScopedClass(CTaskLeanOnVehicle);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x660F90);
    RH_ScopedInstall(Destructor, 0x661030);
    RH_ScopedGlobalInstall(FinishAnimCB, 0x661160);
    // RH_ScopedInstall(MakeAbortable_Reversed, 0x661110);
    // RH_ScopedInstall(ProcessPed, 0x6648C0);
}

// 0x660F90
CTaskLeanOnVehicle::CTaskLeanOnVehicle(CEntity* vehicle, int32 leanAnimDurationInMs, uint8 a4) {
    m_LeanAnimDurationInMs = leanAnimDurationInMs;
    m_Vehicle = vehicle->AsVehicle(); // todo: strange
    field_10 = a4;
    m_LeanAnimAssoc = nullptr;
    m_nAnimId = ANIM_ID_UNDEFINED;
    m_bFinished = 0;
    m_LeanAnimId = 0;
    m_StopLeaning = 0;
    CEntity::SafeRegisterRef(m_Vehicle);
}

// 0x661030
CTaskLeanOnVehicle::~CTaskLeanOnVehicle() {
    CEntity::SafeCleanUpRef(m_Vehicle);
    if (m_LeanAnimAssoc) {
        m_LeanAnimAssoc->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
    }
}

// 0x661160
void CTaskLeanOnVehicle::FinishAnimCB(CAnimBlendAssociation* assoc, void* data) {
    auto task = static_cast<CTaskLeanOnVehicle*>(data);

    task->m_nAnimId = assoc->m_nAnimId;

    if (task->m_nAnimId == ANIM_ID_LEANOUT) {
        assoc->m_fBlendDelta = -1000.0f;
        task->m_bFinished = true;
    }

    if (task->m_LeanAnimId) {
        if (task->m_nAnimId == ANIM_ID_LEANIN) {
            assoc->m_fBlendDelta = -1000.0f;
            task->m_bFinished = true;
        }
    }
    task->m_LeanAnimAssoc = nullptr;
}

// 0x661110
bool CTaskLeanOnVehicle::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    if (priority == ABORT_PRIORITY_IMMEDIATE) {
        if (m_LeanAnimAssoc) {
            m_LeanAnimAssoc->m_fBlendDelta = -1000.0f;
            m_LeanAnimAssoc->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
            m_LeanAnimAssoc = nullptr;
        }
        m_StopLeaning = true;
        ped->m_pEntityIgnoredCollision = nullptr;
        return true;
    }

    m_LeanAnimId = 1;
    return false;
}

// 0x6648C0
bool CTaskLeanOnVehicle::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x6648C0, CTaskLeanOnVehicle*, CPed*>(this, ped);
}
