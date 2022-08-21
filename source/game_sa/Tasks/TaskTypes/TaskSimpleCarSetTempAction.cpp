#include "StdInc.h"
#include "TaskSimpleCarSetTempAction.h"


void CTaskSimpleCarSetTempAction::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleCarSetTempAction, 0x86ea6c, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

RH_ScopedInstall(Constructor, 0x63D6F0);

RH_ScopedInstall(Destructor, 0x63D730);



RH_ScopedVMTInstall(Clone, 0x63DF10, { .reversed = false });
    RH_ScopedVMTInstall(GetTaskType, 0x63D720, { .reversed = false });
    RH_ScopedVMTInstall(MakeAbortable, 0x63D740, { .reversed = false });
    RH_ScopedVMTInstall(ProcessPed, 0x645370, { .reversed = false });

}

// 0x63D6F0
CTaskSimpleCarSetTempAction::CTaskSimpleCarSetTempAction(CVehicle * veh, int32 action, int32 timeMs) {
    assert(false && "Constructor not reversed"); // TODO: Reverse constructor}
}

// 0x63D730
CTaskSimpleCarSetTempAction::~CTaskSimpleCarSetTempAction() {
    assert(false && "Destructor not reversed"); // TODO: Reverse destructor}
}



// 0x63DF10
 CTask * CTaskSimpleCarSetTempAction::Clone() {
    return plugin::CallMethodAndReturn< CTask *, 0x63DF10, CTaskSimpleCarSetTempAction*>(this);
}

// 0x63D720
int32 CTaskSimpleCarSetTempAction::GetTaskType() {
    return plugin::CallMethodAndReturn<int32, 0x63D720, CTaskSimpleCarSetTempAction*>(this);
}

// 0x63D740
bool CTaskSimpleCarSetTempAction::MakeAbortable(CPed * ped, int32 priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x63D740, CTaskSimpleCarSetTempAction*, CPed *, int32, CEvent const*>(this, ped, priority, event);
}

// 0x645370
bool CTaskSimpleCarSetTempAction::ProcessPed(CPed * ped) {
    return plugin::CallMethodAndReturn<bool, 0x645370, CTaskSimpleCarSetTempAction*, CPed *>(this, ped);
}

