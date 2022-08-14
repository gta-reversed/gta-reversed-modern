#include "StdInc.h"
#include "TaskGangHasslePed.h"

void CTaskGangHasslePed::InjectHooks() {
    RH_ScopedClass(CTaskGangHasslePed);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x65FED0);
    RH_ScopedInstall(Destructor, 0x65FF60);

    //RH_ScopedInstall(Clone, 0x6620D0);
    RH_ScopedInstall(GetTaskType, 0x65FF50);
    //RH_ScopedInstall(CreateNextSubTask, 0x6642C0);
    //RH_ScopedInstall(CreateFirstSubTask, 0x664380);
    //RH_ScopedInstall(ControlSubTask, 0x65FFE0);
}

// 0x65FED0
CTaskGangHasslePed::CTaskGangHasslePed(CPed* ped, int32 a3, int32 a4, int32 a5) {}

// 0x65FF60
CTaskGangHasslePed::~CTaskGangHasslePed() {}

// 0x6620D0
CTask* CTaskGangHasslePed::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x6620D0, CTaskGangHasslePed*>(this);
}

// 0x6642C0
CTask* CTaskGangHasslePed::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6642C0, CTaskGangHasslePed*, CPed*>(this, ped);
}

// 0x664380
CTask* CTaskGangHasslePed::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x664380, CTaskGangHasslePed*, CPed*>(this, ped);
}

// 0x65FFE0
CTask* CTaskGangHasslePed::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x65FFE0, CTaskGangHasslePed*, CPed*>(this, ped);
}

