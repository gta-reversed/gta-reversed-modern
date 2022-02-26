#include "StdInc.h"
#include "TaskSimpleIKManager.h"

void CTaskSimpleIKManager::InjectHooks() {
    RH_ScopedClass(CTaskSimpleIKManager);
    RH_ScopedCategoryGlobal(); // TODO: Change this to the appropriate category!

    //RH_ScopedInstall(Constructor, 0x6337F0);
    //RH_ScopedOverloadedInstall(Destructor, "", 0x633830, CTaskSimpleIKManager * (CTaskSimpleIKManager::*)());

    //RH_ScopedInstall(AddIKChainTask, 0x633940);
    //RH_ScopedInstall(GetTaskAtSlot, 0x6339B0);
    //RH_ScopedInstall(Clone_Reversed, 0x639350);
    //RH_ScopedInstall(GetTaskType_Reversed, 0x633820);
    //RH_ScopedInstall(MakeAbortable_Reversed, 0x6338A0);
    //RH_ScopedInstall(ProcessPed_Reversed, 0x6338E0);

}

// 0x6337F0
CTaskSimpleIKManager::CTaskSimpleIKManager() {
    // Everything done in header by the compiler
}

// 0x6337F0
CTaskSimpleIKManager* CTaskSimpleIKManager::Constructor() {
    this->CTaskSimpleIKManager::CTaskSimpleIKManager();
    return this;
}

// 0x633830
CTaskSimpleIKManager::~CTaskSimpleIKManager() {
    // Everything done by the compiler
}

// 0x633830
CTaskSimpleIKManager* CTaskSimpleIKManager::Destructor() {
    this->CTaskSimpleIKManager::~CTaskSimpleIKManager();
    return this;
}

// 0x633940
void CTaskSimpleIKManager::AddIKChainTask(CTaskSimpleIKChain* task, int32 a3) {
    plugin::CallMethod<0x633940, CTaskSimpleIKManager*, CTaskSimpleIKChain*, int32>(this, task, a3);
}

// 0x6339B0
CTaskSimpleIKChain* CTaskSimpleIKManager::GetTaskAtSlot(int32 slut) {
    return plugin::CallMethodAndReturn<CTaskSimpleIKChain*, 0x6339B0, CTaskSimpleIKManager*, int32>(this, slut);
}

// 0x639350
CTaskSimpleIKManager* CTaskSimpleIKManager::Clone() {
    return plugin::CallMethodAndReturn<CTaskSimpleIKManager*, 0x639350, CTaskSimpleIKManager*>(this);
}

// 0x633820
eTaskType CTaskSimpleIKManager::GetTaskType() {
    return plugin::CallMethodAndReturn<eTaskType, 0x633820, CTaskSimpleIKManager*>(this);
}

// 0x6338A0
bool CTaskSimpleIKManager::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x6338A0, CTaskSimpleIKManager*, CPed*, eAbortPriority, CEvent const*>(this, ped, priority, event);
}

// 0x6338E0
bool CTaskSimpleIKManager::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x6338E0, CTaskSimpleIKManager*, CPed*>(this, ped);
}
