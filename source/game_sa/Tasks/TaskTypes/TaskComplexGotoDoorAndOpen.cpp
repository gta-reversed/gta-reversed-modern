#include "StdInc.h"
#include "TaskComplexGotoDoorAndOpen.h"

void CTaskComplexGotoDoorAndOpen::InjectHooks() {
    RH_ScopedClass(CTaskComplexGotoDoorAndOpen);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedOverloadedInstall(Constructor, "", 0x66BB20, CTaskComplexGotoDoorAndOpen*(CTaskComplexGotoDoorAndOpen::*)(CObject *));
    RH_ScopedOverloadedInstall(Constructor, "", 0x66BBA0, CTaskComplexGotoDoorAndOpen*(CTaskComplexGotoDoorAndOpen::*)(CVector const&, CVector const&));
    RH_ScopedInstall(Destructor, 0x66BC00);

    // RH_ScopedInstall(Clone, 0x66BCA0);
    RH_ScopedInstall(GetTaskType, 0x66BB90);
    // RH_ScopedInstall(MakeAbortable, 0x66BC80);
    // RH_ScopedInstall(CreateNextSubTask, 0x66C0D0);
    // RH_ScopedInstall(CreateFirstSubTask, 0x66BD40);
    // RH_ScopedInstall(ControlSubTask, 0x66C1F0);
}

// 0x66BB20
CTaskComplexGotoDoorAndOpen::CTaskComplexGotoDoorAndOpen(CObject* door) {}

// 0x66BBA0
CTaskComplexGotoDoorAndOpen::CTaskComplexGotoDoorAndOpen(CVector const& start, CVector const& end) {}

// 0x66BC00
CTaskComplexGotoDoorAndOpen::~CTaskComplexGotoDoorAndOpen() {}

// 0x66BCA0
CTask* CTaskComplexGotoDoorAndOpen::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x66BCA0, CTaskComplexGotoDoorAndOpen*>(this);
}

// 0x66BC80
bool CTaskComplexGotoDoorAndOpen::MakeAbortable(CPed* ped, int32 priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x66BC80, CTaskComplexGotoDoorAndOpen*, CPed*, int32, CEvent const*>(this, ped, priority, event);
}

// 0x66C0D0
CTask* CTaskComplexGotoDoorAndOpen::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x66C0D0, CTaskComplexGotoDoorAndOpen*, CPed*>(this, ped);
}

// 0x66BD40
CTask* CTaskComplexGotoDoorAndOpen::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x66BD40, CTaskComplexGotoDoorAndOpen*, CPed*>(this, ped);
}

// 0x66C1F0
CTask* CTaskComplexGotoDoorAndOpen::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x66C1F0, CTaskComplexGotoDoorAndOpen*, CPed*>(this, ped);
}
