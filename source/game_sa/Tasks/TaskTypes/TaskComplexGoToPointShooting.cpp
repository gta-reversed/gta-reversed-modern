#include "StdInc.h"
#include "TaskComplexGoToPointShooting.h"

void CTaskComplexGoToPointShooting::InjectHooks() {
    RH_ScopedClass(CTaskComplexGoToPointShooting);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x668C70);
    RH_ScopedInstall(Destructor, 0x0);

    // RH_ScopedInstall(Clone, 0x66CE10);
    RH_ScopedInstall(GetTaskType, 0x668CC0);
}

// 0x668C70
CTaskComplexGoToPointShooting::CTaskComplexGoToPointShooting(int32 arg0, CVector const& arg1, CEntity* arg2, CVector arg3, float arg4, float arg5) {}

// 0x0
CTaskComplexGoToPointShooting::~CTaskComplexGoToPointShooting() {}

// 0x66CE10
CTask* CTaskComplexGoToPointShooting::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x66CE10, CTaskComplexGoToPointShooting*>(this);
}
