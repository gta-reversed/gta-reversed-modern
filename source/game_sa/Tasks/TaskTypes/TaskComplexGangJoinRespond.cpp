#include "StdInc.h"
#include "TaskComplexGangJoinRespond.h"

void CTaskComplexGangJoinRespond::InjectHooks() {
    RH_ScopedClass(CTaskComplexGangJoinRespond);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x6616F0);
    RH_ScopedInstall(Destructor, 0x661720);

    // RH_ScopedInstall(Clone, 0x662290);
    RH_ScopedInstall(GetTaskType, 0x661710);
    // RH_ScopedInstall(MakeAbortable, 0x661790);
    // RH_ScopedInstall(CreateNextSubTask, 0x6617A0);
    // RH_ScopedInstall(CreateFirstSubTask, 0x6618D0);
    // RH_ScopedInstall(ControlSubTask, 0x661950);
}

// 0x6616F0
CTaskComplexGangJoinRespond::CTaskComplexGangJoinRespond(uint8) {}

// 0x661720
CTaskComplexGangJoinRespond::~CTaskComplexGangJoinRespond() {}

// 0x662290
CTask* CTaskComplexGangJoinRespond::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x662290, CTaskComplexGangJoinRespond*>(this);
}

// 0x661790
bool CTaskComplexGangJoinRespond::MakeAbortable(CPed* ped, int32 priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x661790, CTaskComplexGangJoinRespond*, CPed*, int32, CEvent const*>(this, ped, priority, event);
}

// 0x6617A0
CTask* CTaskComplexGangJoinRespond::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6617A0, CTaskComplexGangJoinRespond*, CPed*>(this, ped);
}

// 0x6618D0
CTask* CTaskComplexGangJoinRespond::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6618D0, CTaskComplexGangJoinRespond*, CPed*>(this, ped);
}

// 0x661950
CTask* CTaskComplexGangJoinRespond::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x661950, CTaskComplexGangJoinRespond*, CPed*>(this, ped);
}
