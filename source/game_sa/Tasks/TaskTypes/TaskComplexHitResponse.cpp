#include "StdInc.h"
#include "TaskComplexHitResponse.h"

void CTaskComplexHitResponse::InjectHooks() {
    RH_ScopedClass(CTaskComplexHitResponse);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x631D70);
    RH_ScopedInstall(Destructor, 0x631DA0);

    // RH_ScopedInstall(Clone, 0x6365E0);
    RH_ScopedInstall(GetTaskType, 0x631D90);
    // RH_ScopedInstall(CreateNextSubTask, 0x631DB0);
    // RH_ScopedInstall(CreateFirstSubTask, 0x638040);
    // RH_ScopedInstall(ControlSubTask, 0x631DC0);
}

// 0x631D70
CTaskComplexHitResponse::CTaskComplexHitResponse(int32 a1) {}

// 0x631DA0
CTaskComplexHitResponse::~CTaskComplexHitResponse() {}

// 0x6365E0
CTask* CTaskComplexHitResponse::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x6365E0, CTaskComplexHitResponse*>(this);
}

// 0x631DB0
CTask* CTaskComplexHitResponse::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x631DB0, CTaskComplexHitResponse*, CPed*>(this, ped);
}

// 0x638040
CTask* CTaskComplexHitResponse::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x638040, CTaskComplexHitResponse*, CPed*>(this, ped);
}

// 0x631DC0
CTask* CTaskComplexHitResponse::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x631DC0, CTaskComplexHitResponse*, CPed*>(this, ped);
}
