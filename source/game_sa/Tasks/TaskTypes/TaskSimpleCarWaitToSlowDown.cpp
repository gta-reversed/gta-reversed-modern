#include "StdInc.h"
#include "TaskSimpleCarWaitToSlowDown.h"

void CTaskSimpleCarWaitToSlowDown::InjectHooks() {
    RH_ScopedClass(CTaskSimpleCarWaitToSlowDown);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x646990);

    RH_ScopedInstall(Destructor, 0x646A00);

    RH_ScopedVMTInstall(Clone, 0x649CB0, {.reversed = false});
    RH_ScopedVMTInstall(GetTaskType, 0x6469F0, {.reversed = false});
    RH_ScopedVMTInstall(MakeAbortable, 0x646A60, {.reversed = false});
    RH_ScopedVMTInstall(ProcessPed, 0x646AD0, {.reversed = false});
    RH_ScopedVMTInstall(SetPedPosition, 0x646AB0, {.reversed = false});
}

// 0x646990
CTaskSimpleCarWaitToSlowDown::CTaskSimpleCarWaitToSlowDown(CVehicle* veh, int32 type) {
    assert(false && "Constructor not reversed"); // TODO: Reverse constructor}
}

// 0x646A00
CTaskSimpleCarWaitToSlowDown::~CTaskSimpleCarWaitToSlowDown() {
    assert(false && "Destructor not reversed"); // TODO: Reverse destructor}
}

// 0x649CB0
CTask* CTaskSimpleCarWaitToSlowDown::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x649CB0, CTaskSimpleCarWaitToSlowDown*>(this);
}

// 0x6469F0
int32 CTaskSimpleCarWaitToSlowDown::GetTaskType() {
    return plugin::CallMethodAndReturn<int32, 0x6469F0, CTaskSimpleCarWaitToSlowDown*>(this);
}

// 0x646A60
bool CTaskSimpleCarWaitToSlowDown::MakeAbortable(CPed* ped, int32 priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x646A60, CTaskSimpleCarWaitToSlowDown*, CPed*, int32, CEvent const*>(this, ped, priority, event);
}

// 0x646AD0
bool CTaskSimpleCarWaitToSlowDown::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x646AD0, CTaskSimpleCarWaitToSlowDown*, CPed*>(this, ped);
}

// 0x646AB0
bool CTaskSimpleCarWaitToSlowDown::SetPedPosition(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x646AB0, CTaskSimpleCarWaitToSlowDown*, CPed*>(this, ped);
}
