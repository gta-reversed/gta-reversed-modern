#include "StdInc.h"
#include "TaskComplexGoToPointAiming.h"

void CTaskComplexGoToPointAiming::InjectHooks() {
    RH_ScopedClass(CTaskComplexGoToPointAiming);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x668790);
    RH_ScopedInstall(Destructor, 0x668870);

    // RH_ScopedInstall(CreateSubTask, 0x6688D0);

    // RH_ScopedInstall(Clone, 0x66CD80);
    RH_ScopedInstall(GetTaskType, 0x668860);
    // RH_ScopedInstall(CreateNextSubTask, 0x66DD70);
    // RH_ScopedInstall(CreateFirstSubTask, 0x66DDB0);
    // RH_ScopedInstall(ControlSubTask, 0x6689E0);
}

// 0x668790
CTaskComplexGoToPointAiming::CTaskComplexGoToPointAiming(int32 arg0, CVector const& arg1, CEntity* arg2, CVector arg3, float arg4, float arg5) {}

// 0x668870
CTaskComplexGoToPointAiming::~CTaskComplexGoToPointAiming() {}

// 0x6688D0
CTaskComplexGoToPointAndStandStill* CTaskComplexGoToPointAiming::CreateSubTask(int32 a2) {
    return plugin::CallMethodAndReturn<CTaskComplexGoToPointAndStandStill*, 0x6688D0, CTaskComplexGoToPointAiming*, int32>(this, a2);
}

// 0x66CD80
CTask* CTaskComplexGoToPointAiming::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x66CD80, CTaskComplexGoToPointAiming*>(this);
}

// 0x66DD70
CTask* CTaskComplexGoToPointAiming::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x66DD70, CTaskComplexGoToPointAiming*, CPed*>(this, ped);
}

// 0x66DDB0
CTask* CTaskComplexGoToPointAiming::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x66DDB0, CTaskComplexGoToPointAiming*, CPed*>(this, ped);
}

// 0x6689E0
CTask* CTaskComplexGoToPointAiming::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6689E0, CTaskComplexGoToPointAiming*, CPed*>(this, ped);
}
