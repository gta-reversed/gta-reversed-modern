#include "StdInc.h"
#include "TaskComplexGoToPointAnyMeans.h"

void CTaskComplexGoToPointAnyMeans::InjectHooks() {
    RH_ScopedClass(CTaskComplexGoToPointAnyMeans);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedOverloadedInstall(Constructor, "1", 0x66B720, CTaskComplexGoToPointAnyMeans*(CTaskComplexGoToPointAnyMeans::*)(int32, CVector const&, float, int32));
    RH_ScopedOverloadedInstall(Constructor, "2", 0x66B790, CTaskComplexGoToPointAnyMeans*(CTaskComplexGoToPointAnyMeans::*)(int32, CVector const&, CVehicle*, float, int32));
    RH_ScopedInstall(Destructor, 0x66B830);

    // RH_ScopedInstall(CreateSubTask, 0x6705D0);

    // RH_ScopedInstall(Clone, 0x66D1E0);
    RH_ScopedInstall(GetTaskType, 0x66B780);
    // RH_ScopedInstall(CreateNextSubTask, 0x6728A0);
    // RH_ScopedInstall(CreateFirstSubTask, 0x6729C0);
    // RH_ScopedInstall(ControlSubTask, 0x672A50);
}

// 0x66B720
CTaskComplexGoToPointAnyMeans::CTaskComplexGoToPointAnyMeans(int32 a2, CVector const& posn, float a4, int32 a5) {}

// 0x66B790
CTaskComplexGoToPointAnyMeans::CTaskComplexGoToPointAnyMeans(int32 moveState, CVector const& posn, CVehicle* vehicle, float radius, int32 a6) {}

// 0x66B830
CTaskComplexGoToPointAnyMeans::~CTaskComplexGoToPointAnyMeans() {}

// 0x6705D0
CTask* CTaskComplexGoToPointAnyMeans::CreateSubTask(int32 taskType, CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6705D0, CTaskComplexGoToPointAnyMeans*, int32, CPed*>(this, taskType, ped);
}

// 0x66D1E0
CTask* CTaskComplexGoToPointAnyMeans::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x66D1E0, CTaskComplexGoToPointAnyMeans*>(this);
}

// 0x6728A0
CTask* CTaskComplexGoToPointAnyMeans::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6728A0, CTaskComplexGoToPointAnyMeans*, CPed*>(this, ped);
}

// 0x6729C0
CTask* CTaskComplexGoToPointAnyMeans::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6729C0, CTaskComplexGoToPointAnyMeans*, CPed*>(this, ped);
}

// 0x672A50
CTask* CTaskComplexGoToPointAnyMeans::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x672A50, CTaskComplexGoToPointAnyMeans*, CPed*>(this, ped);
}
