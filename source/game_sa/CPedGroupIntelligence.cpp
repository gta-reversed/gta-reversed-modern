#include "StdInc.h"

bool CPedGroupIntelligence::AddEvent(CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x5F7470, CPedGroupIntelligence*, CEvent*>(this, event);
}

void CPedGroupIntelligence::SetScriptCommandTask(CPed* ped, CTask const* task) {
    plugin::CallMethod<0x5F8560, CPedGroupIntelligence*, CPed*, CTask const*>(this, ped, task);
}

void CPedGroupIntelligence::ComputeDefaultTasks(CPed* ped) {
    plugin::CallMethod<0x5F88D0, CPedGroupIntelligence*, CPed*>(this, ped);
}

CTask* CPedGroupIntelligence::GetTaskScriptCommand(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x5F8690, CPedGroupIntelligence*, CPed*>(this, ped);
}

int CPedGroupIntelligence::SetGroupDecisionMakerType(int a2) {
    return plugin::CallMethodAndReturn<int, 0x5F7340, CPedGroupIntelligence*, int>(this, a2);
}

void CPedGroupIntelligence::SetPrimaryTaskAllocator(CTaskAllocator* taskAllocator) {
    plugin::CallMethod<0x5F7410, CPedGroupIntelligence*, CTaskAllocator*>(this, taskAllocator);
}
