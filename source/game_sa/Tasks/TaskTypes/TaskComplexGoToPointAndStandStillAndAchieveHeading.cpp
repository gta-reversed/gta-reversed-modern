#include "StdInc.h"
#include "TaskComplexGoToPointAndStandStillAndAchieveHeading.h"

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
CTaskComplexGoToPointAndStandStillAndAchieveHeading::CTaskComplexGoToPointAndStandStillAndAchieveHeading(int32 a2, CVector const& a3, float a4, float a5, float a6, float a7) {}

// 0x668D40
CTaskComplexGoToPointAndStandStillAndAchieveHeading::~CTaskComplexGoToPointAndStandStillAndAchieveHeading() {}

// 0x66CFD0
CTask* CTaskComplexGoToPointAndStandStillAndAchieveHeading::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x66CFD0, CTaskComplexGoToPointAndStandStillAndAchieveHeading*>(this);
}

// 0x66DFD0
CTask* CTaskComplexGoToPointAndStandStillAndAchieveHeading::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x66DFD0, CTaskComplexGoToPointAndStandStillAndAchieveHeading*, CPed*>(this, ped);
}

// 0x66E030
CTask* CTaskComplexGoToPointAndStandStillAndAchieveHeading::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x66E030, CTaskComplexGoToPointAndStandStillAndAchieveHeading*, CPed*>(this, ped);
}

// 0x668E80
CTask* CTaskComplexGoToPointAndStandStillAndAchieveHeading::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x668E80, CTaskComplexGoToPointAndStandStillAndAchieveHeading*, CPed*>(this, ped);
}
