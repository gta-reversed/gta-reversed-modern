#include "StdInc.h"

bool CPedGroupIntelligence::AddEvent(CEvent* event) {
    return plugin::CallMethodAndReturnDynGlobal<bool, CPedGroupIntelligence*, CEvent*>(0x5F7470, this, event);
}

void CPedGroupIntelligence::SetScriptCommandTask(CPed* ped, CTask const* task) {
    plugin::CallMethodDynGlobal<CPedGroupIntelligence*, CPed*, CTask const*>(0x5F8560, this, ped, task);
}

void CPedGroupIntelligence::ComputeDefaultTasks(CPed* ped) {
    plugin::CallMethodDynGlobal<CPedGroupIntelligence*, CPed*>(0x5F88D0, this, ped);
}

CTask* CPedGroupIntelligence::GetTaskScriptCommand(CPed* ped) {
    return plugin::CallMethodAndReturnDynGlobal<CTask*, CPedGroupIntelligence*, CPed*>(0x5F8690, this, ped);
}

int CPedGroupIntelligence::SetGroupDecisionMakerType(int a2) {
    return plugin::CallMethodAndReturnDynGlobal<int, CPedGroupIntelligence*, int>(0x5F7340, this, a2);
}

void CPedGroupIntelligence::SetPrimaryTaskAllocator(CTaskAllocator* taskAllocator) {
    plugin::CallMethodDynGlobal<CPedGroupIntelligence*, CTaskAllocator*>(0x5F7410, this, taskAllocator);
}
