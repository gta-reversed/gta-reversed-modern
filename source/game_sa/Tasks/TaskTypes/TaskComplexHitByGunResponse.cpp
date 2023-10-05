#include "StdInc.h"

#include "TaskComplexHitByGunResponse.h"
//#include "TaskSimpleHitByGunFromRear.h"
//#include "TaskSimpleHitByGunFromLeft.h"
//#include "TaskSimpleHitByGunFromRear.h"
//#include "TaskSimpleHitByGunFromRight.h"

void CTaskComplexHitByGunResponse::InjectHooks() {
    RH_ScopedClass(CTaskComplexHitByGunResponse);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x631DD0);
    RH_ScopedInstall(Destructor, 0x631E30);
    RH_ScopedInstall(CreateFirstSubTask, 0x631E50, { .reversed = false });
}

// 0x631DD0
CTaskComplexHitByGunResponse::CTaskComplexHitByGunResponse(int32 direction) : CTaskComplex() {
    m_Direction = direction;
}

// 0x631E00
bool CTaskComplexHitByGunResponse::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    switch (priority) {
    case ABORT_PRIORITY_URGENT:
    case ABORT_PRIORITY_IMMEDIATE:
        return m_pSubTask->MakeAbortable(ped, priority, event);
    default:
        return false;
    }
}

// 0x631E50
CTask* CTaskComplexHitByGunResponse::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x631E50, CTaskComplexHitByGunResponse*, CPed*>(this, ped);

    /*
    switch (m_Direction) {
    case 0:  return new CTaskSimpleHitByGunFromRear();
    case 1:  return new CTaskSimpleHitByGunFromLeft();
    case 2:  return new CTaskSimpleHitByGunFromRear();
    case 3:  return new CTaskSimpleHitByGunFromRight();
    default: return nullptr;
    }
     */
}
