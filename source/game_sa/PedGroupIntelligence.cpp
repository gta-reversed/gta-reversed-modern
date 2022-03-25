#include "StdInc.h"

#include "PedGroupIntelligence.h"

// 0x5F7250
CPedGroupIntelligence::CPedGroupIntelligence() {
    plugin::CallMethod<0x5F7250, CPedGroupIntelligence*>(this);
}

// 0x5F7350
CPedGroupIntelligence::~CPedGroupIntelligence() {
    plugin::CallMethod<0x5F7350, CPedGroupIntelligence*>(this);
}

bool CPedGroupIntelligence::AddEvent(CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x5F7470, CPedGroupIntelligence*, CEvent*>(this, event);
}

void CPedGroupIntelligence::SetScriptCommandTask(CPed* ped, const CTask* task) {
    plugin::CallMethod<0x5F8560, CPedGroupIntelligence*, CPed*, const CTask*>(this, ped, task);
}

CTask* CPedGroupIntelligence::GetTaskMain(CPed* ped) {
    return plugin::CallAndReturn<CTask*, 0x5F85A0>(this, ped);
}

void CPedGroupIntelligence::ComputeDefaultTasks(CPed* ped) {
    plugin::CallMethod<0x5F88D0, CPedGroupIntelligence*, CPed*>(this, ped);
}

CTask* CPedGroupIntelligence::GetTaskScriptCommand(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x5F8690, CPedGroupIntelligence*, CPed*>(this, ped);
}

CTask* CPedGroupIntelligence::GetTaskSecondary(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x681810>(this, ped);
}

int32 CPedGroupIntelligence::GetTaskSecondarySlot(CPed* ped) {
    return plugin::CallMethodAndReturn<int32, 0x5F8650>(this, ped);
}

int32 CPedGroupIntelligence::SetGroupDecisionMakerType(int32 a2) {
    return plugin::CallMethodAndReturn<int32, 0x5F7340, CPedGroupIntelligence*, int32>(this, a2);
}

void CPedGroupIntelligence::SetPrimaryTaskAllocator(CTaskAllocator* taskAllocator) {
    plugin::CallMethod<0x5F7410, CPedGroupIntelligence*, CTaskAllocator*>(this, taskAllocator);
}

void CPedGroupIntelligence::SetDefaultTaskAllocatorType(int32 nPedGroupTaskAllocator) {
    plugin::CallMethod<0x5FBB70, CPedGroupIntelligence*, int32>(this, nPedGroupTaskAllocator);
}

bool CPedGroupIntelligence::ReportFinishedTask(const CPed* ped, const CTask* task) {
    return plugin::CallMethodAndReturn<bool, 0x5F86F0>(this, ped, task);
}
