#include "StdInc.h"
#include "TaskSimpleAffectSecondaryBehaviour.h"


void CTaskSimpleAffectSecondaryBehaviour::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleAffectSecondaryBehaviour, 0x870b08, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

RH_ScopedInstall(Constructor, 0x691270);




RH_ScopedVMTInstall(Clone, 0x692910, { .reversed = false });
    RH_ScopedVMTInstall(GetTaskType, 0x6912A0, { .reversed = false });
    RH_ScopedVMTInstall(MakeAbortable, 0x6912B0, { .reversed = false });
    RH_ScopedVMTInstall(ProcessPed, 0x691320, { .reversed = false });

}

// 0x691270
CTaskSimpleAffectSecondaryBehaviour::CTaskSimpleAffectSecondaryBehaviour(bool add, int32 secondaryTaskType, CTask * a4) {
    assert(false && "Constructor not reversed"); // TODO: Reverse constructor}
}




// 0x692910
 CTask * CTaskSimpleAffectSecondaryBehaviour::Clone() {
    return plugin::CallMethodAndReturn< CTask *, 0x692910, CTaskSimpleAffectSecondaryBehaviour*>(this);
}

// 0x6912A0
int32 CTaskSimpleAffectSecondaryBehaviour::GetTaskType() {
    return plugin::CallMethodAndReturn<int32, 0x6912A0, CTaskSimpleAffectSecondaryBehaviour*>(this);
}

// 0x6912B0
bool CTaskSimpleAffectSecondaryBehaviour::MakeAbortable(CPed * ped, int32 priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x6912B0, CTaskSimpleAffectSecondaryBehaviour*, CPed *, int32, CEvent const*>(this, ped, priority, event);
}

// 0x691320
bool CTaskSimpleAffectSecondaryBehaviour::ProcessPed(CPed * ped) {
    return plugin::CallMethodAndReturn<bool, 0x691320, CTaskSimpleAffectSecondaryBehaviour*, CPed *>(this, ped);
}

