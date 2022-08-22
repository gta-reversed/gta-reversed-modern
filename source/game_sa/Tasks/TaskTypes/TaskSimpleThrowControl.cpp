#include "StdInc.h"

#include "TaskSimpleThrowControl.h"

void CTaskSimpleThrowControl::InjectHooks() {
    RH_ScopedClass(CTaskSimpleThrowControl);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x61F8B0);
    RH_ScopedInstall(Destructor, 0x61F950);
    RH_ScopedVirtualInstall2(Clone, 0x6230B0);
    RH_ScopedVirtualInstall2(GetTaskType, 0x61F940);
    RH_ScopedVirtualInstall2(MakeAbortable, 0x61F9B0);
    RH_ScopedVirtualInstall2(ProcessPed, 0x61F9F0, {.enabled = false, .locked = true});
}

// 0x61F8B0
CTaskSimpleThrowControl::CTaskSimpleThrowControl(CEntity* targetEntity, const CVector* pos) :
    CTaskSimple(),
    m_bIsFinished{ false },
    m_bStartedThrowTask{ false },
    m_TargetEntity{ targetEntity },
    m_TargetPos{ pos ? *pos : CVector{} }
{
    assert(m_TargetEntity);
    CEntity::SafeRegisterRef(m_TargetEntity);
}

// 0x61F950
CTaskSimpleThrowControl::~CTaskSimpleThrowControl() {
    CEntity::SafeCleanUpRef(m_TargetEntity);
}

// 0x61F9B0
bool CTaskSimpleThrowControl::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    if (!ped->GetIntelligence()->GetTaskThrow()) {
        return true;
    }
    return ped->GetTaskManager().GetTaskSecondary(TASK_SECONDARY_ATTACK)->MakeAbortable(ped, priority, event);
}

// 0x61F9F0
bool CTaskSimpleThrowControl::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x61F9F0, CTaskSimpleThrowControl*, CPed*>(this, ped);
}
