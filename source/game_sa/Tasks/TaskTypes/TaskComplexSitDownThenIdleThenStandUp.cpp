#include "StdInc.h"
#include "TaskComplexSitDownThenIdleThenStandUp.h"
#include "TaskSimpleSitDown.h"
#include "TaskSimpleSitIdle.h"
#include "TaskSimpleStandUp.h"

void CTaskComplexSitDownThenIdleThenStandUp::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexSitDownThenIdleThenStandUp, 0x86df60, 11);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x631460);

    RH_ScopedInstall(Destructor, 0x6314A0);

    RH_ScopedInstall(CreateSubTask, 0x631550, {.reversed = false});

    RH_ScopedVMTInstall(Clone, 0x636390, {.reversed = false});
    RH_ScopedVMTInstall(GetTaskType, 0x631490, {.reversed = false});
    RH_ScopedVMTInstall(MakeAbortable, 0x631510, {.reversed = false});
    RH_ScopedVMTInstall(CreateNextSubTask, 0x637DB0, {.reversed = false});
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x6316A0, {.reversed = false});
    RH_ScopedVMTInstall(ControlSubTask, 0x631730, {.reversed = false});
}

// 0x631460
CTaskComplexSitDownThenIdleThenStandUp::CTaskComplexSitDownThenIdleThenStandUp(int32 durationMs, bool bSitOnStep, bool bInstant) :
    m_durationMs{durationMs},
    m_doInstantly{bInstant},
    m_sitOnStep{bSitOnStep}
{
}

// 0x6314A0
CTaskComplexSitDownThenIdleThenStandUp::~CTaskComplexSitDownThenIdleThenStandUp() {
    if (m_animBlockRefAdded) {
        CAnimManager::RemoveAnimBlockRef(CAnimManager::GetAnimationBlockIndex("attractors"));
        m_animBlockRefAdded = false;
    }
}

// 0x631550
CTask* CTaskComplexSitDownThenIdleThenStandUp::CreateSubTask(eTaskType taskType) {
    switch (taskType) {
    case TASK_FINISHED:
        return nullptr;
    case TASK_SIMPLE_SIT_DOWN:
        //return new CTaskSimpleSitDown{}; // TODO
    case TASK_SIMPLE_SIT_IDLE:
        return // TODO
    case TASK_SIMPLE_STAND_UP:
        return 
    default:
        NOTSA_UNREACHABLE();
    }
}

// 0x631510
bool CTaskComplexSitDownThenIdleThenStandUp::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x631510, CTaskComplexSitDownThenIdleThenStandUp*, CPed*, int32, CEvent const*>(this, ped, priority, event);
}

// 0x637DB0
CTask* CTaskComplexSitDownThenIdleThenStandUp::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x637DB0, CTaskComplexSitDownThenIdleThenStandUp*, CPed*>(this, ped);
}

// 0x6316A0
CTask* CTaskComplexSitDownThenIdleThenStandUp::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6316A0, CTaskComplexSitDownThenIdleThenStandUp*, CPed*>(this, ped);
}

// 0x631730
CTask* CTaskComplexSitDownThenIdleThenStandUp::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x631730, CTaskComplexSitDownThenIdleThenStandUp*, CPed*>(this, ped);
}
