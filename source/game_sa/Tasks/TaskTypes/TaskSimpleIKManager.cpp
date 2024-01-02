#include "StdInc.h"
#include "TaskSimpleIKManager.h"

void CTaskSimpleIKManager::InjectHooks() {
    RH_ScopedClass(CTaskSimpleIKManager);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x6337F0);
    RH_ScopedInstall(Destructor, 0x633830);

    RH_ScopedInstall(AddIKChainTask, 0x633940);
    RH_ScopedInstall(GetTaskAtSlot, 0x6339B0);
    RH_ScopedInstall(Clone_Reversed, 0x639350, { .reversed = false });
    RH_ScopedInstall(GetTaskType_Reversed, 0x633820);
    RH_ScopedInstall(MakeAbortable_Reversed, 0x6338A0);
    RH_ScopedInstall(ProcessPed_Reversed, 0x6338E0);
}

// 0x6337F0
CTaskSimpleIKManager::CTaskSimpleIKManager() {
    rng::fill(m_pIKChainTasks, nullptr);
    m_bAborting = false;
}

// 0x633830
CTaskSimpleIKManager::~CTaskSimpleIKManager() {
    for (auto&& task : m_pIKChainTasks) {
        delete task;
    }
}

/*!
* @addr 0x633940
* @brief Store \a task in \a slot.
* @param slot If < 0 the first unused slot will be used.
*/
void CTaskSimpleIKManager::AddIKChainTask(CTaskSimpleIKChain* task, int32 slot) {
    if (slot < 0) { // Find free slot, and store `task` there.
        const auto it = rng::find(m_pIKChainTasks, nullptr);
        if (it != m_pIKChainTasks.end()) {
            *it = task;
        }
    } else { // Store `task` in the given `slot`
        assert(!m_pIKChainTasks[slot]); // Otherwise memory leak
        m_pIKChainTasks[slot] = task;
    }
}

// 0x639350
CTask* CTaskSimpleIKManager::Clone() const {
    return plugin::CallMethodAndReturn<CTask*, 0x639350, const CTaskSimpleIKManager*>(this);
}

// 0x6338A0
bool CTaskSimpleIKManager::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    if (priority == eAbortPriority::ABORT_PRIORITY_IMMEDIATE) {
        for (auto&& task : m_pIKChainTasks) {
            delete task;
            task = nullptr;
        }
        return true;
    } else {
        m_bAborting = true;
        return false;
    }
}

// 0x6338E0
bool CTaskSimpleIKManager::ProcessPed(CPed* ped) {
    if (m_bAborting) {
        return true;
    }

    bool hasAllProcessedPed{true};
    for (auto&& task : m_pIKChainTasks) {
        if (task) {
            if (task->ProcessPed(ped)) {
                delete task;
                task = nullptr;
            } else {
                hasAllProcessedPed = false;
            }
        }
    }

    return hasAllProcessedPed;
}
