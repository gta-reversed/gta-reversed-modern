#include "StdInc.h"

#include "TaskComplexPolicePursuit.h"

// 0x68BA70
CTaskComplexPolicePursuit::CTaskComplexPolicePursuit() : CTaskComplex() {
    plugin::CallMethod<0x68BA70, CTaskComplexPolicePursuit*>(this);
}

// 0x68CDD0
CTaskComplexPolicePursuit::CTaskComplexPolicePursuit(const CTaskComplexPolicePursuit& o) :
    CTaskComplexPolicePursuit{}
{
}

// 0x68D880
CTaskComplexPolicePursuit::~CTaskComplexPolicePursuit() {
    plugin::CallMethod<0x68D880, CTaskComplexPolicePursuit*>(this);
}

// 0x690920
CTask* CTaskComplexPolicePursuit::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x690920, CTaskComplexPolicePursuit*, CPed*>(this, ped);
}

// 0x6908E0
CTask* CTaskComplexPolicePursuit::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6908E0, CTaskComplexPolicePursuit*, CPed*>(this, ped);
}

// 0x68BAC0
CTask* CTaskComplexPolicePursuit::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x68BAC0, CTaskComplexPolicePursuit*, CPed*>(this, ped);
}

// 0x68D910
CTask* CTaskComplexPolicePursuit::CreateSubTask(eTaskType taskType, CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x68D910, CTaskComplexPolicePursuit*, eTaskType, CPed*>(this, taskType, ped);
}

// 0x68BDC0
bool CTaskComplexPolicePursuit::PersistPursuit(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x68BDC0, CTaskComplexPolicePursuit*, CPed*>(this, ped);
}

// 0x68BBD0
bool CTaskComplexPolicePursuit::SetPursuit(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x68BBD0, CTaskComplexPolicePursuit*, CPed*>(this, ped);
}

// 0x68BD90
void CTaskComplexPolicePursuit::ClearPursuit(CPed* ped) {
    plugin::CallMethod<0x68BD90, CTaskComplexPolicePursuit*, CPed*>(this, ped);
}

// 0x68BAD0
void CTaskComplexPolicePursuit::SetWeapon(CPed* ped) {
    return plugin::CallMethod<0x68BAD0, CTaskComplexPolicePursuit*, CPed*>(this, ped);
}

void CTaskComplexPolicePursuit::InjectHooks() {
    RH_ScopedClass(CTaskComplexPolicePursuit);
    RH_ScopedCategory("Tasks/TaskTypes");
    RH_ScopedInstall(Constructor, 0x68BA70, { .reversed = false });
    RH_ScopedInstall(SetWeapon, 0x68BAD0, { .reversed = false });
    RH_ScopedInstall(ClearPursuit, 0x68BD90, { .reversed = false });
    RH_ScopedInstall(SetPursuit, 0x68BBD0, { .reversed = false });
    RH_ScopedInstall(PersistPursuit, 0x68BDC0, { .reversed = false });
    RH_ScopedInstall(CreateSubTask, 0x68D910, { .reversed = false });
    RH_ScopedVirtualInstall(Clone, 0x68CDD0, { .reversed = false });
    RH_ScopedVirtualInstall(MakeAbortable, 0x68BAB0, { .reversed = false });
    RH_ScopedVirtualInstall(CreateNextSubTask, 0x68BAC0, { .reversed = false });
    RH_ScopedVirtualInstall(CreateFirstSubTask, 0x6908E0, { .reversed = false });
    RH_ScopedVirtualInstall(ControlSubTask, 0x690920, { .reversed = false });
}

CTaskComplexPolicePursuit* CTaskComplexPolicePursuit::Constructor() {
    this->CTaskComplexPolicePursuit::CTaskComplexPolicePursuit();
    return this;
}

// 0x68CDD0
CTask* CTaskComplexPolicePursuit::Clone_Reversed() const {
    return CTaskComplexPolicePursuit::Clone();
}

// 0x68BAB0
bool CTaskComplexPolicePursuit::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return CTaskComplexPolicePursuit::MakeAbortable(ped, priority, event);
}

// 0x68BAC0
CTask* CTaskComplexPolicePursuit::CreateNextSubTask_Reversed(CPed* ped) {
    return CTaskComplexPolicePursuit::CreateNextSubTask(ped);
}

// 0x6908E0
CTask* CTaskComplexPolicePursuit::CreateFirstSubTask_Reversed(CPed* ped) {
    return CTaskComplexPolicePursuit::CreateFirstSubTask(ped);
}

// 0x690920
CTask* CTaskComplexPolicePursuit::ControlSubTask_Reversed(CPed* ped) {
    return CTaskComplexPolicePursuit::ControlSubTask(ped);
}
