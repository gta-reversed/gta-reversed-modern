#include "StdInc.h"
#include "TaskComplexFollowLeaderInFormation.h"

void CTaskComplexFollowLeaderInFormation::InjectHooks() {
    RH_ScopedClass(CTaskComplexFollowLeaderInFormation);
    RH_ScopedCategory("Tasks/TaskTypes");

    // Constructors (1x)
    RH_ScopedInstall(Constructor, 0x6949A0);

    // Destructors (1x)
    RH_ScopedOverloadedInstall(Destructor, "", 0x694A40, CTaskComplexFollowLeaderInFormation * (CTaskComplexFollowLeaderInFormation::*)());

    // Virtual methods (5x)
    RH_ScopedInstall(Clone_Reversed, 0x695740);
    RH_ScopedInstall(GetTaskType_Reversed, 0x694A30);
    RH_ScopedInstall(CreateNextSubTask_Reversed, 0x696820);
    RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x6968E0);
    RH_ScopedInstall(ControlSubTask_Reversed, 0x696940);
}

// 0x6949A0
CTaskComplexFollowLeaderInFormation::CTaskComplexFollowLeaderInFormation(CPedGroup* pedGroup, CPed* ped, CVector const& posn, float a5) {}

// 0x6949A0
CTaskComplexFollowLeaderInFormation* CTaskComplexFollowLeaderInFormation::Constructor(CPedGroup* pedGroup, CPed* ped, CVector const& posn, float a5) {
    this->CTaskComplexFollowLeaderInFormation::CTaskComplexFollowLeaderInFormation(pedGroup, ped, posn, a5);
    return this;
}

// 0x694A40
CTaskComplexFollowLeaderInFormation::~CTaskComplexFollowLeaderInFormation() {}

// 0x694A40
CTaskComplexFollowLeaderInFormation* CTaskComplexFollowLeaderInFormation::Destructor() {
    this->CTaskComplexFollowLeaderInFormation::~CTaskComplexFollowLeaderInFormation();
    return this;
}

// Virtual methods
// 0x695740
CTask* CTaskComplexFollowLeaderInFormation::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x695740, CTaskComplexFollowLeaderInFormation*>(this);
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
