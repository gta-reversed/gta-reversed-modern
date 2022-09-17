#include "StdInc.h"

#include "TaskComplexFollowLeaderInFormation.h"

void CTaskComplexFollowLeaderInFormation::InjectHooks() {
    RH_ScopedClass(CTaskComplexFollowLeaderInFormation);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x6949A0, { .reversed = false });
    // RH_ScopedOverloadedInstall(Destructor, "", 0x694A40, CTaskComplexFollowLeaderInFormation * (CTaskComplexFollowLeaderInFormation::*)());

    RH_ScopedVirtualInstall(Clone, 0x695740, { .reversed = false });
    RH_ScopedVirtualInstall(GetTaskType, 0x694A30, { .reversed = false });
    RH_ScopedVirtualInstall(CreateNextSubTask, 0x696820, { .reversed = false });
    RH_ScopedVirtualInstall(CreateFirstSubTask, 0x6968E0, { .reversed = false });
    RH_ScopedVirtualInstall(ControlSubTask, 0x696940, { .reversed = false });
}

// 0x6949A0
CTaskComplexFollowLeaderInFormation::CTaskComplexFollowLeaderInFormation(CPedGroup* pedGroup, CPed* ped, const CVector& posn, float a5) : CTaskComplex() {
    plugin::CallMethod<0x6949A0, CTaskComplexFollowLeaderInFormation*, CPedGroup*, CPed*, const CVector&, float>(this, pedGroup, ped, posn, a5);
}

// 0x694A40
CTaskComplexFollowLeaderInFormation::~CTaskComplexFollowLeaderInFormation() {
    plugin::CallMethod<0x694A40, CTaskComplexFollowLeaderInFormation*>(this);
}

// 0x696820
CTask* CTaskComplexFollowLeaderInFormation::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x696820, CTaskComplexFollowLeaderInFormation*, CPed*>(this, ped);
}

// 0x6968E0
CTask* CTaskComplexFollowLeaderInFormation::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6968E0, CTaskComplexFollowLeaderInFormation*, CPed*>(this, ped);
}

// 0x696940
CTask* CTaskComplexFollowLeaderInFormation::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x696940, CTaskComplexFollowLeaderInFormation*, CPed*>(this, ped);
}
