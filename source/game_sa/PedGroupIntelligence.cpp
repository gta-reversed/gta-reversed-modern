#include "StdInc.h"

#include "PedGroupIntelligence.h"

void CPedGroupIntelligence::InjectHooks() {
    RH_ScopedClass(CPedGroupIntelligence);
    RH_ScopedCategoryGlobal();

    //RH_ScopedInstall(Constructor, 0x5F7250, { .reversed = false });
    
    RH_ScopedOverloadedInstall(AddEvent, "", 0x5F7470, bool(CPedGroupIntelligence::*)(CEvent*), { .reversed = false });
    RH_ScopedInstall(SetScriptCommandTask, 0x5F8560, { .reversed = false });
    RH_ScopedInstall(Flush, 0x5F7350, { .reversed = false });
    RH_ScopedInstall(GetTaskMain, 0x5F85A0, { .reversed = false });
    RH_ScopedInstall(ComputeDefaultTasks, 0x5F88D0, { .reversed = false });
    RH_ScopedInstall(GetTaskScriptCommand, 0x5F8690, { .reversed = false });
    RH_ScopedInstall(GetTaskSecondary, 0x5F8620, { .reversed = false });
    RH_ScopedInstall(GetTaskSecondarySlot, 0x5F8650, { .reversed = false });
    RH_ScopedInstall(SetGroupDecisionMakerType, 0x5F7340, { .reversed = false });
    RH_ScopedInstall(SetPrimaryTaskAllocator, 0x5F7410, { .reversed = false });
    RH_ScopedInstall(SetDefaultTaskAllocatorType, 0x5FBB70, { .reversed = false });

    RH_ScopedOverloadedInstall(ReportFinishedTask, "", 0x5F86F0, bool(CPedGroupIntelligence::*)(const CPed*, const CTask*), { .reversed = false });
}

// 0x5F7250
CPedGroupIntelligence::CPedGroupIntelligence() {
    plugin::CallMethod<0x5F7250, CPedGroupIntelligence*>(this);
}

CPedGroupIntelligence::CPedGroupIntelligence(CPedGroup& owner) :
    m_pPedGroup{ &owner }
{
}

// Unknown address (If any)
CPedGroupIntelligence::~CPedGroupIntelligence() {
    Flush(); // Not sure if it does this at all, but it worked so far, so let's leave it like this for now
}

// 0x5F7350
void CPedGroupIntelligence::Flush() { // Pirulax: For some reason this is called `~CPedGroupIntelligence` in *there*...
    plugin::CallMethod<0x5F7350, CPedGroupIntelligence*>(this);
}

// 0x5F7470
bool CPedGroupIntelligence::AddEvent(CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x5F7470, CPedGroupIntelligence*, CEvent*>(this, event);
}

// 0x5F8560
void CPedGroupIntelligence::SetScriptCommandTask(CPed* ped, const CTask* task) {
    plugin::CallMethod<0x5F8560, CPedGroupIntelligence*, CPed*, const CTask*>(this, ped, task);
}

CTask* CPedGroupIntelligence::GetTask(CPed* ped, const CPedTaskPair* taskPair) {
    const CPedTaskPair* tp;
    auto index = 0;
    while (true) {
        auto taskPed = taskPair[index].m_pPed;
        tp = &taskPair[index++];
        if (taskPed == ped)
            break;
        if (index == 8)
            return nullptr;
    }
    return tp->m_pTask;
}

// 0x5F85A0
CTask* CPedGroupIntelligence::GetTaskMain(CPed* ped) {
    CTask* task = GetTask(ped, &m_groupTasks[16]);
    if (!task) {
        task = GetTask(ped, &m_groupTasks[0]);
        if (!task)
            return GetTask(ped, &m_groupTasks[24]);
    }
    return task;
}

CTask* CPedGroupIntelligence::GetTaskDefault(CPed* ped) {
    return GetTask(ped, &m_groupTasks[24]);
}

// 0x5F8690
CTask* CPedGroupIntelligence::GetTaskScriptCommand(CPed* ped) {
    return GetTask(ped, &m_groupTasks[16]);
}

// 0x5F8620
CTask* CPedGroupIntelligence::GetTaskSecondary(CPed* ped) {
    return GetTask(ped, &m_groupTasks[8]);
}

// 0x5F8650
eSecondaryTask CPedGroupIntelligence::GetTaskSecondarySlot(CPed* ped) {
    return plugin::CallMethodAndReturn<eSecondaryTask, 0x5F8650>(this, ped);
}

void CPedGroupIntelligence::Process() {
    plugin::CallMethod<0x5FC4A0>(this);
}

// 0x5F88D0
void CPedGroupIntelligence::ComputeDefaultTasks(CPed* ped) {
    plugin::CallMethod<0x5F88D0, CPedGroupIntelligence*, CPed*>(this, ped);
}

// 0x5F7340
int32 CPedGroupIntelligence::SetGroupDecisionMakerType(int32 a2) {
    return plugin::CallMethodAndReturn<int32, 0x5F7340, CPedGroupIntelligence*, int32>(this, a2);
}

// 0x5F7410
void CPedGroupIntelligence::SetPrimaryTaskAllocator(CTaskAllocator* taskAllocator) {
    plugin::CallMethod<0x5F7410, CPedGroupIntelligence*, CTaskAllocator*>(this, taskAllocator);
}

// 0x5FBB70
void CPedGroupIntelligence::SetDefaultTaskAllocatorType(ePedGroupDefaultTaskAllocatorType nPedGroupTaskAllocator) {
    plugin::CallMethod<0x5FBB70, CPedGroupIntelligence*, ePedGroupDefaultTaskAllocatorType>(this, nPedGroupTaskAllocator);
}

// 0x5F86F0
bool CPedGroupIntelligence::ReportFinishedTask(const CPed* ped, const CTask* task) {
    return plugin::CallMethodAndReturn<bool, 0x5F86F0>(this, ped, task);
}

// 0x5F7540
void CPedGroupIntelligence::SetTask(CPed* ped, const CTask* task, CPedTaskPair* pair, int32 arg5, bool arg6) {
    plugin::Call<0x5F7540, CPed*, const CTask*, CPedTaskPair*, int32, bool>(ped, task, pair, arg5, arg6);
}
