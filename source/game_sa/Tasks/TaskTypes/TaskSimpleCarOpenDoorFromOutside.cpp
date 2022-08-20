#include "StdInc.h"
#include "TaskSimpleCarOpenDoorFromOutside.h"


void CTaskSimpleCarOpenDoorFromOutside::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleCarOpenDoorFromOutside, 0x86ec9c, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

RH_ScopedInstall(Constructor, 0x645E50);

RH_ScopedInstall(Destructor, 0x645EE0);



RH_ScopedVMTInstall(Clone, 0x6499A0, { .reversed = false });
    RH_ScopedVMTInstall(GetTaskType, 0x645ED0, { .reversed = false });
    RH_ScopedVMTInstall(MakeAbortable, 0x64AD00, { .reversed = false });
    RH_ScopedVMTInstall(ProcessPed, 0x64D710, { .reversed = false });
    RH_ScopedVMTInstall(SetPedPosition, 0x645F80, { .reversed = false });

}

// 0x645E50
CTaskSimpleCarOpenDoorFromOutside::CTaskSimpleCarOpenDoorFromOutside(CVehicle* , int32 , CTaskUtilityLineUpPedWithCar* , bool ) {
    assert(false && "Constructor not reversed"); // TODO: Reverse constructor}
}

// 0x645EE0
CTaskSimpleCarOpenDoorFromOutside::~CTaskSimpleCarOpenDoorFromOutside() {
    assert(false && "Destructor not reversed"); // TODO: Reverse destructor}
}



// 0x6499A0
 CTask * CTaskSimpleCarOpenDoorFromOutside::Clone() {
    return plugin::CallMethodAndReturn< CTask *, 0x6499A0, CTaskSimpleCarOpenDoorFromOutside*>(this);
}

// 0x645ED0
int32 CTaskSimpleCarOpenDoorFromOutside::GetTaskType() {
    return plugin::CallMethodAndReturn<int32, 0x645ED0, CTaskSimpleCarOpenDoorFromOutside*>(this);
}

// 0x64AD00
bool CTaskSimpleCarOpenDoorFromOutside::MakeAbortable(CPed * ped, int32 priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x64AD00, CTaskSimpleCarOpenDoorFromOutside*, CPed *, int32, CEvent const*>(this, ped, priority, event);
}

// 0x64D710
bool CTaskSimpleCarOpenDoorFromOutside::ProcessPed(CPed * ped) {
    return plugin::CallMethodAndReturn<bool, 0x64D710, CTaskSimpleCarOpenDoorFromOutside*, CPed *>(this, ped);
}

// 0x645F80
bool CTaskSimpleCarOpenDoorFromOutside::SetPedPosition(CPed * ped) {
    return plugin::CallMethodAndReturn<bool, 0x645F80, CTaskSimpleCarOpenDoorFromOutside*, CPed *>(this, ped);
}

