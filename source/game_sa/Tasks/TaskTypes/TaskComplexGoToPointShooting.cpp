#include "StdInc.h"

#include "TaskComplexGoToPointShooting.h"

void CTaskComplexGoToPointShooting::InjectHooks() {
    RH_ScopedClass(CTaskComplexGoToPointShooting);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x668C70);
}

// 0x668C70
CTaskComplexGoToPointShooting::CTaskComplexGoToPointShooting(int32 a2, const CVector& a3, CEntity* a4, CVector a5, float a6, float a7)
    : CTaskComplexGoToPointAiming(a2, a3, a4, a5, a6, a7)
{
    // NOP
}

