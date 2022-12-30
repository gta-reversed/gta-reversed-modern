#include "StdInc.h"

#include "TaskComplexHitResponse.h"
// #include "TaskSimpleHitFromFront.h"
// #include "TaskSimpleHitFromLeft.h"
// #include "TaskSimpleHitFromBack.h"
// #include "TaskSimpleHitFromRight.h"

void CTaskComplexHitResponse::InjectHooks() {
    RH_ScopedClass(CTaskComplexHitResponse);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x631D70);
    RH_ScopedInstall(CreateNextSubTask, 0x631DB0, { .reversed = false });
    RH_ScopedInstall(CreateFirstSubTask, 0x638040, { .reversed = false });
    RH_ScopedInstall(ControlSubTask, 0x631DC0, { .reversed = false });
}

// 0x631D70
CTaskComplexHitResponse::CTaskComplexHitResponse(int32 direction) : CTaskComplex() {
    m_Direction = direction;
}

// 0x638040
CTask* CTaskComplexHitResponse::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x638040, CTaskComplexHitResponse*, CPed*>(this, ped);
    /*
    switch (m_Direction) {
    case 0:  return new CTaskSimpleHitFromFront();
    case 1:  return new CTaskSimpleHitFromLeft();
    case 2:  return new CTaskSimpleHitFromBack();
    case 3:  return new CTaskSimpleHitFromRight();
    default: return nullptr;
    }
    */
}
