#include "StdInc.h"
#include "TaskComplexGoToAttractor.h"

void CTaskComplexGoToAttractor::InjectHooks() {
    RH_ScopedClass(CTaskComplexGoToAttractor);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x66B640);
    RH_ScopedInstall(Destructor, 0x66B6A0);

    // RH_ScopedInstall(Clone, 0x66D130);
    RH_ScopedInstall(GetTaskType, 0x66B690);
    // RH_ScopedInstall(MakeAbortable, 0x66B6B0);
    // RH_ScopedInstall(CreateNextSubTask, 0x66B6C0);
    // RH_ScopedInstall(CreateFirstSubTask, 0x670420);
    // RH_ScopedInstall(ControlSubTask, 0x66B710);
}

// 0x66B640
CTaskComplexGoToAttractor::CTaskComplexGoToAttractor(CPedAttractor* attractor, CVector const& attrPosn, float attrHeading, float attrTime, int32 queueNumber, int32 a7) {}

// 0x66B6A0
CTaskComplexGoToAttractor::~CTaskComplexGoToAttractor() {}

// 0x66D130
CTask* CTaskComplexGoToAttractor::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x66D130, CTaskComplexGoToAttractor*>(this);
}

// 0x66B6B0
bool CTaskComplexGoToAttractor::MakeAbortable(CPed* ped, int32 priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x66B6B0, CTaskComplexGoToAttractor*, CPed*, int32, CEvent const*>(this, ped, priority, event);
}

// 0x66B6C0
CTask* CTaskComplexGoToAttractor::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x66B6C0, CTaskComplexGoToAttractor*, CPed*>(this, ped);
}

// 0x670420
CTask* CTaskComplexGoToAttractor::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x670420, CTaskComplexGoToAttractor*, CPed*>(this, ped);
}

// 0x66B710
CTask* CTaskComplexGoToAttractor::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x66B710, CTaskComplexGoToAttractor*, CPed*>(this, ped);
}
