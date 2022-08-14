#include "StdInc.h"
#include "TaskComplexCarSlowBeDraggedOutAndStandUp.h"

void CTaskComplexCarSlowBeDraggedOutAndStandUp::InjectHooks() {
    RH_ScopedClass(CTaskComplexCarSlowBeDraggedOutAndStandUp);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x648620);
    RH_ScopedInstall(Destructor, 0x648690);

    //RH_ScopedInstall(CreateSubTask, 0x648710);

    //RH_ScopedInstall(Clone, 0x64A190);
    RH_ScopedInstall(GetTaskType, 0x648680);
    //RH_ScopedInstall(MakeAbortable, 0x6486F0);
    //RH_ScopedInstall(CreateNextSubTask, 0x6488F0);
    //RH_ScopedInstall(CreateFirstSubTask, 0x648A10);
    //RH_ScopedInstall(ControlSubTask, 0x648B80);
}

// 0x648620
CTaskComplexCarSlowBeDraggedOutAndStandUp::CTaskComplexCarSlowBeDraggedOutAndStandUp(CVehicle*, int32) {}

// 0x648690
CTaskComplexCarSlowBeDraggedOutAndStandUp::~CTaskComplexCarSlowBeDraggedOutAndStandUp() {}

// 0x648710
void CTaskComplexCarSlowBeDraggedOutAndStandUp::CreateSubTask(int32 a2, CPed* a3) {
    plugin::CallMethod<0x648710, CTaskComplexCarSlowBeDraggedOutAndStandUp*, int32, CPed*>(this, a2, a3);
}

// 0x64A190
CTask* CTaskComplexCarSlowBeDraggedOutAndStandUp::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x64A190, CTaskComplexCarSlowBeDraggedOutAndStandUp*>(this);
}

// 0x6486F0
bool CTaskComplexCarSlowBeDraggedOutAndStandUp::MakeAbortable(CPed* ped, int32 priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x6486F0, CTaskComplexCarSlowBeDraggedOutAndStandUp*, CPed*, int32, CEvent const*>(this, ped, priority, event);
}

// 0x6488F0
CTask* CTaskComplexCarSlowBeDraggedOutAndStandUp::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6488F0, CTaskComplexCarSlowBeDraggedOutAndStandUp*, CPed*>(this, ped);
}

// 0x648A10
CTask* CTaskComplexCarSlowBeDraggedOutAndStandUp::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x648A10, CTaskComplexCarSlowBeDraggedOutAndStandUp*, CPed*>(this, ped);
}

// 0x648B80
CTask* CTaskComplexCarSlowBeDraggedOutAndStandUp::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x648B80, CTaskComplexCarSlowBeDraggedOutAndStandUp*, CPed*>(this, ped);
}
