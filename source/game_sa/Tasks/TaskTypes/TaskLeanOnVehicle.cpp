#include "StdInc.h"
#include "TaskLeanOnVehicle.h"

void CTaskLeanOnVehicle::InjectHooks() {
    RH_ScopedClass(CTaskLeanOnVehicle);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x660F90);
    RH_ScopedInstall(Destructor, 0x661030);

    //RH_ScopedGlobalInstall(FinishAnimCB, 0x661160);

    //RH_ScopedInstall(Clone, 0x6610A0);
    RH_ScopedInstall(GetTaskType, 0x661020);
    //RH_ScopedInstall(MakeAbortable, 0x661110);
    //RH_ScopedInstall(ProcessPed, 0x6648C0);
}

// 0x660F90
CTaskLeanOnVehicle::CTaskLeanOnVehicle(CEntity* vehicle, int32 leanAnimDurationInMs, uint8 a4) {}

// 0x661030
CTaskLeanOnVehicle::~CTaskLeanOnVehicle() {}

// 0x661160
CTaskLeanOnVehicle* CTaskLeanOnVehicle::FinishAnimCB(CAnimBlendAssociation* assoc, void* data) {
    return plugin::CallAndReturn<CTaskLeanOnVehicle*, 0x661160, CAnimBlendAssociation*, void*>(assoc, data);
}

// 0x6610A0
CTask* CTaskLeanOnVehicle::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x6610A0, CTaskLeanOnVehicle*>(this);
}

// 0x661110
bool CTaskLeanOnVehicle::MakeAbortable(CPed* ped, int32 priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x661110, CTaskLeanOnVehicle*, CPed*, int32, CEvent const*>(this, ped, priority, event);
}

// 0x6648C0
bool CTaskLeanOnVehicle::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x6648C0, CTaskLeanOnVehicle*, CPed*>(this, ped);
}
