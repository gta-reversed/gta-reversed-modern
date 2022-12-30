#include "StdInc.h"

#include "TaskComplexFallAndGetUp.h"
#include "TaskSimpleFall.h"
#include "TaskSimpleGetUp.h"

void CTaskComplexFallAndGetUp::InjectHooks() {
    RH_ScopedClass(CTaskComplexFallAndGetUp);
    RH_ScopedCategory("Tasks/TaskTypes");
    RH_ScopedInstall(Constructor, 0x6786C0);
    RH_ScopedInstall(Constructor2, 0x678700);
    RH_ScopedInstall(CreateSubTask, 0x678900);
    RH_ScopedInstall(IsFalling, 0x6787D0);
    RH_ScopedInstall(SetDownTime, 0x6787A0);
    // VTABLE
    RH_ScopedVirtualInstall(CreateFirstSubTask, 0x678870);
    RH_ScopedVirtualInstall(CreateNextSubTask, 0x67CB70);
    RH_ScopedVirtualInstall(ControlSubTask, 0x6788F0);
    RH_ScopedVirtualInstall(MakeAbortable, 0x6787F0);
}

CTaskComplexFallAndGetUp* CTaskComplexFallAndGetUp::Constructor(AnimationId nFallAnimId, AssocGroupId nFallAnimGroup, int32 nFallDownTime) {
    this->CTaskComplexFallAndGetUp::CTaskComplexFallAndGetUp(nFallAnimId, nFallAnimGroup, nFallDownTime);
    return this;
}

CTaskComplexFallAndGetUp* CTaskComplexFallAndGetUp::Constructor2(int32 nDir, int32 nFallDownTime) {
    this->CTaskComplexFallAndGetUp::CTaskComplexFallAndGetUp(nDir, nFallDownTime);
    return this;
}

// 0x6786C0
CTaskComplexFallAndGetUp::CTaskComplexFallAndGetUp(AnimationId nFallAnimId, AssocGroupId nFallAnimGroup, int32 nFallDownTime) {
    m_nFallAnimId    = nFallAnimId;
    m_nFallAnimGroup = nFallAnimGroup;
    m_nFallDownTime  = nFallDownTime;
}

// 0x678700
CTaskComplexFallAndGetUp::CTaskComplexFallAndGetUp(int32 nDir, int32 nFallDownTime) {
    m_nFallDownTime = nFallDownTime;
    m_nFallAnimGroup = ANIM_GROUP_DEFAULT;

    switch (nDir) {
    case 0:
        m_nFallAnimId = ANIM_ID_KO_SKID_FRONT;
        break;
    case 1:
        m_nFallAnimId = ANIM_ID_KO_SPIN_R;
        break;
    case 2:
        m_nFallAnimId = ANIM_ID_KO_SKID_BACK;
        break;
    case 3:
        m_nFallAnimId = ANIM_ID_KO_SPIN_L;
        break;
    default:
        break;
    }
}

// 0x678870
CTask* CTaskComplexFallAndGetUp::CreateFirstSubTask(CPed* ped) {
    return CreateFirstSubTask_Reversed(ped);
}

// 0x67CB70
CTask* CTaskComplexFallAndGetUp::CreateNextSubTask(CPed* ped) {
    return CreateNextSubTask_Reversed(ped);
}

// 0x6788F0
CTask* CTaskComplexFallAndGetUp::ControlSubTask(CPed* ped) {
    return ControlSubTask_Reversed(ped);
}

// 0x6787F0
bool CTaskComplexFallAndGetUp::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return MakeAbortable_Reversed(ped, priority, event);
}

CTask* CTaskComplexFallAndGetUp::CreateFirstSubTask_Reversed(CPed* ped) {
    return CreateSubTask(TASK_SIMPLE_FALL);
}

CTask* CTaskComplexFallAndGetUp::CreateNextSubTask_Reversed(CPed* ped) {
    auto subTaskType = m_pSubTask->GetTaskType();

    if (subTaskType == TASK_SIMPLE_FALL)
        return CreateSubTask(TASK_SIMPLE_GET_UP);

    if (subTaskType == TASK_SIMPLE_GET_UP)
        return CreateSubTask(TASK_FINISHED);

    return nullptr;
}

CTask* CTaskComplexFallAndGetUp::ControlSubTask_Reversed(CPed* ped) {
    return m_pSubTask;
}

bool CTaskComplexFallAndGetUp::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event) {
    if (priority == ABORT_PRIORITY_IMMEDIATE)
        return m_pSubTask->MakeAbortable(ped, priority, event);

    if (ped->m_nPedState == PEDSTATE_ARRESTED || ped->bIsBeingArrested)
        return false;

    if (priority == ABORT_PRIORITY_LEISURE) {
        if (IsFalling())
            return false;
        else
            m_nFallDownTime = 0;
    }

    return m_pSubTask->MakeAbortable(ped, priority, event);
}

// 0x678900
CTask* CTaskComplexFallAndGetUp::CreateSubTask(eTaskType taskType) {
    switch (taskType) {
    case TASK_SIMPLE_FALL:
        return new CTaskSimpleFall(m_nFallAnimId, m_nFallAnimGroup, m_nFallDownTime);
    case TASK_SIMPLE_GET_UP:
        return new CTaskSimpleGetUp();
    case TASK_FINISHED:
    default:
        return nullptr;
    }
}

// 0x6787D0
bool CTaskComplexFallAndGetUp::IsFalling() {
    return m_pSubTask->GetTaskType() == TASK_SIMPLE_FALL;
}

// 0x6787A0
void CTaskComplexFallAndGetUp::SetDownTime(int32 nTime) {
    m_nFallDownTime = nTime;
    if (IsFalling()) {
        auto pFallTask = reinterpret_cast<CTaskSimpleFall*>(m_pSubTask);
        pFallTask->m_nTotalDownTime = nTime;
        pFallTask->m_nCurrentDownTime = nTime;
    }
}
