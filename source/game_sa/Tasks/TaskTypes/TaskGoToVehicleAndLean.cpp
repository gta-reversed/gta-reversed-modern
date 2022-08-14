#include "StdInc.h"
#include "TaskGoToVehicleAndLean.h"

void CTaskGoToVehicleAndLean::InjectHooks() {
    RH_ScopedClass(CTaskGoToVehicleAndLean);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x660E60);
    RH_ScopedInstall(Destructor, 0x660EE0);

    //RH_ScopedInstall(Clone, 0x6621B0);
    RH_ScopedInstall(GetTaskType, 0x660ED0);
    //RH_ScopedInstall(MakeAbortable, 0x664500);
    //RH_ScopedInstall(CreateNextSubTask, 0x664590);
    //RH_ScopedInstall(CreateFirstSubTask, 0x664D40);
    //RH_ScopedInstall(ControlSubTask, 0x664E60);
}

// 0x660E60
CTaskGoToVehicleAndLean::CTaskGoToVehicleAndLean(CVehicle* vehicle, int32 leanAnimDurationInMs) {}

// 0x660EE0
CTaskGoToVehicleAndLean::~CTaskGoToVehicleAndLean() {}

// 0x6621B0
CTask* CTaskGoToVehicleAndLean::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x6621B0, CTaskGoToVehicleAndLean*>(this);
}

// 0x664500
bool CTaskGoToVehicleAndLean::MakeAbortable(CPed* ped, int32 priority, const CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x664500, CTaskGoToVehicleAndLean*, CPed*, int32, const CEvent*>(this, ped, priority, event);
}

// 0x664590
CTask* CTaskGoToVehicleAndLean::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x664590, CTaskGoToVehicleAndLean*, CPed*>(this, ped);
}

// 0x664D40
CTask* CTaskGoToVehicleAndLean::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x664D40, CTaskGoToVehicleAndLean*, CPed*>(this, ped);
}

// 0x664E60
CTask* CTaskGoToVehicleAndLean::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x664E60, CTaskGoToVehicleAndLean*, CPed*>(this, ped);
}

