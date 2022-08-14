#include "StdInc.h"
#include "TaskComplexHitByGunResponse.h"

void CTaskComplexHitByGunResponse::InjectHooks() {
    RH_ScopedClass(CTaskComplexHitByGunResponse);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x631DD0);
    RH_ScopedInstall(Destructor, 0x631E30);

    // RH_ScopedInstall(Clone, 0x636640);
    RH_ScopedInstall(GetTaskType, 0x631DF0);
    // RH_ScopedInstall(MakeAbortable, 0x631E00);
    // RH_ScopedInstall(CreateNextSubTask, 0x631E40);
    // RH_ScopedInstall(CreateFirstSubTask, 0x631E50);
    // RH_ScopedInstall(ControlSubTask, 0x631F70);
}

// 0x631DD0
CTaskComplexHitByGunResponse::CTaskComplexHitByGunResponse(int32 a1) {}

// 0x631E30
CTaskComplexHitByGunResponse::~CTaskComplexHitByGunResponse() {}

// 0x636640
CTask* CTaskComplexHitByGunResponse::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x636640, CTaskComplexHitByGunResponse*>(this);
}

// 0x631E00
bool CTaskComplexHitByGunResponse::MakeAbortable(CPed* ped, int32 priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x631E00, CTaskComplexHitByGunResponse*, CPed*, int32, CEvent const*>(this, ped, priority, event);
}

// 0x631E40
CTask* CTaskComplexHitByGunResponse::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x631E40, CTaskComplexHitByGunResponse*, CPed*>(this, ped);
}

// 0x631E50
CTask* CTaskComplexHitByGunResponse::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x631E50, CTaskComplexHitByGunResponse*, CPed*>(this, ped);
}

// 0x631F70
CTask* CTaskComplexHitByGunResponse::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x631F70, CTaskComplexHitByGunResponse*, CPed*>(this, ped);
}
