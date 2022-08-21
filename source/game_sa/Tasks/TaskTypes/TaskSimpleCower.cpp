#include "StdInc.h"
#include "TaskSimpleCower.h"


void CTaskSimpleCower::InjectHooks() {
    RH_ScopedClass(CTaskSimpleCower);
    RH_ScopedCategory("Tasks/TaskTypes");

RH_ScopedInstall(Constructor, 0x48DE70);

RH_ScopedInstall(Destructor, 0x48E900);



RH_ScopedVMTInstall(Clone, 0x48DEB0, { .reversed = false });
    RH_ScopedVMTInstall(IsInterruptable, 0x48DF20, { .reversed = false });

}

// 0x48DE70
CTaskSimpleCower::CTaskSimpleCower() {
    assert(false && "Constructor not reversed"); // TODO: Reverse constructor}
}

// 0x48E900
CTaskSimpleCower::~CTaskSimpleCower() {
    assert(false && "Destructor not reversed"); // TODO: Reverse destructor}
}



// 0x48DEB0
 CTask * CTaskSimpleCower::Clone() {
    return plugin::CallMethodAndReturn< CTask *, 0x48DEB0, CTaskSimpleCower*>(this);
}

// 0x48DF20
bool CTaskSimpleCower::IsInterruptable(CPed const* ped) {
    return plugin::CallMethodAndReturn<bool, 0x48DF20, CTaskSimpleCower*, CPed const*>(this, ped);
}

