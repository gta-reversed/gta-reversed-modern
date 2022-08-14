#include "StdInc.h"
#include "TaskComplexCarSlowBeDraggedOut.h"

void CTaskComplexCarSlowBeDraggedOut::InjectHooks() {
    RH_ScopedClass(CTaskComplexCarSlowBeDraggedOut);
    RH_ScopedCategory("Tasks/TaskTypes"); // TODO: Change this to the appropriate category!

    RH_ScopedInstall(Constructor, 0x648490);
    RH_ScopedInstall(Destructor, 0x64C580);

    //RH_ScopedInstall(CreateTaskUtilityLineUpPedWithCar, 0x648520);
    //RH_ScopedInstall(CreateSubTask, 0x64C6A0);

    //RH_ScopedInstall(Clone, 0x64A120);
    RH_ScopedInstall(GetTaskType, 0x648500);
    //RH_ScopedInstall(MakeAbortable, 0x64C600);
    //RH_ScopedInstall(CreateNextSubTask, 0x64C810);
    //RH_ScopedInstall(CreateFirstSubTask, 0x64C8B0);
    //RH_ScopedInstall(ControlSubTask, 0x648510);
}

// 0x648490
CTaskComplexCarSlowBeDraggedOut::CTaskComplexCarSlowBeDraggedOut(CVehicle* car, int32 a3, bool a4) {}

// 0x64C580
CTaskComplexCarSlowBeDraggedOut::~CTaskComplexCarSlowBeDraggedOut() {}

// 0x648520
CTaskUtilityLineUpPedWithCar* CTaskComplexCarSlowBeDraggedOut::CreateTaskUtilityLineUpPedWithCar(int32 a2) {
    return plugin::CallMethodAndReturn<CTaskUtilityLineUpPedWithCar*, 0x648520, CTaskComplexCarSlowBeDraggedOut*, int32>(this, a2);
}

// 0x64C6A0
CTaskSimpleCarFallOut* CTaskComplexCarSlowBeDraggedOut::CreateSubTask(int32 a2) {
    return plugin::CallMethodAndReturn<CTaskSimpleCarFallOut*, 0x64C6A0, CTaskComplexCarSlowBeDraggedOut*, int32>(this, a2);
}

// 0x64A120
CTask* CTaskComplexCarSlowBeDraggedOut::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x64A120, CTaskComplexCarSlowBeDraggedOut*>(this);
}

// 0x64C600
bool CTaskComplexCarSlowBeDraggedOut::MakeAbortable(CPed* ped, int32 priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x64C600, CTaskComplexCarSlowBeDraggedOut*, CPed*, int32, CEvent const*>(this, ped, priority, event);
}

// 0x64C810
CTask* CTaskComplexCarSlowBeDraggedOut::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x64C810, CTaskComplexCarSlowBeDraggedOut*, CPed*>(this, ped);
}

// 0x64C8B0
CTask* CTaskComplexCarSlowBeDraggedOut::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x64C8B0, CTaskComplexCarSlowBeDraggedOut*, CPed*>(this, ped);
}

// 0x648510
CTask* CTaskComplexCarSlowBeDraggedOut::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x648510, CTaskComplexCarSlowBeDraggedOut*, CPed*>(this, ped);
}
