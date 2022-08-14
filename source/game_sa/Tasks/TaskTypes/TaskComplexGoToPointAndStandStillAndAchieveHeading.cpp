#include "StdInc.h"

#include "TaskComplexGoToPointAndStandStillAndAchieveHeading.h"
#include "TaskSimpleAchieveHeading.h"
#include "TaskSimpleStandStill.h"
#include "TaskSimpleGoToPoint.h"

void CTaskComplexGoToPointAndStandStillAndAchieveHeading::InjectHooks() {
    RH_ScopedClass(CTaskComplexGoToPointAndStandStillAndAchieveHeading);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x668CD0);
    RH_ScopedInstall(Destructor, 0x668D40);

    // RH_ScopedInstall(Clone, 0x66CFD0);
    RH_ScopedInstall(GetTaskType, 0x668D30);
    // RH_ScopedInstall(CreateNextSubTask, 0x66DFD0);
    // RH_ScopedInstall(CreateFirstSubTask, 0x66E030);
    // RH_ScopedInstall(ControlSubTask, 0x668E80);
}

// 0x668CD0
CTaskComplexGoToPointAndStandStillAndAchieveHeading::CTaskComplexGoToPointAndStandStillAndAchieveHeading(int32 a2, CVector const& a3, float a4, float a5, float a6, float a7)
    : CTaskComplex()
{
    dwordC = a2;
    dword10 = a3;
    float1C = a5;
    float28 = a7;
    m_nFlags = m_nFlags | 1; // todo: flags
    float20 = a4;
    float24 = a6;
}

// 0x66DFD0
CTask* CTaskComplexGoToPointAndStandStillAndAchieveHeading::CreateNextSubTask(CPed* ped) {
    switch (m_pSubTask->GetTaskType()) {
    case TASK_SIMPLE_GO_TO_POINT:
        return CreateSubTask(TASK_SIMPLE_STAND_STILL);
    case TASK_SIMPLE_ACHIEVE_HEADING:
        return CreateSubTask(TASK_FINISHED);
    case TASK_SIMPLE_STAND_STILL:
        return CreateSubTask(TASK_SIMPLE_ACHIEVE_HEADING);
    default:
        return nullptr;
    }
}

// 0x668D50
CTask* CTaskComplexGoToPointAndStandStillAndAchieveHeading::CreateSubTask(eTaskType taskType) {
    switch (taskType) {
    case TASK_SIMPLE_ACHIEVE_HEADING:
        return new CTaskSimpleAchieveHeading(float20, float24, float28);
    case TASK_SIMPLE_STAND_STILL:
        return new CTaskSimpleStandStill();
    case TASK_SIMPLE_GO_TO_POINT:
        return new CTaskSimpleGoToPoint(dwordC, dword10, float1C, false, false);
    default:
        return nullptr;
    }
}

// 0x66E030
CTask* CTaskComplexGoToPointAndStandStillAndAchieveHeading::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x66E030, CTaskComplexGoToPointAndStandStillAndAchieveHeading*, CPed*>(this, ped);
}

// 0x668E80
CTask* CTaskComplexGoToPointAndStandStillAndAchieveHeading::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x668E80, CTaskComplexGoToPointAndStandStillAndAchieveHeading*, CPed*>(this, ped);
}
