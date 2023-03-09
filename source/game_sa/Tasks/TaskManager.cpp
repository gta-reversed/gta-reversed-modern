/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "TaskManager.h"

void CTaskManager::InjectHooks() {
    RH_ScopedClass(CTaskManager);
    RH_ScopedCategory("Tasks");

    RH_ScopedInstall(Constructor, 0x6816A0);
    RH_ScopedInstall(Destructor, 0x6816D0);
    RH_ScopedInstall(GetActiveTask, 0x681720);
    RH_ScopedInstall(FindActiveTaskByType, 0x681740);
    RH_ScopedInstall(FindTaskByType, 0x6817D0);
    RH_ScopedInstall(GetTaskSecondary, 0x681810);
    RH_ScopedInstall(HasTaskSecondary, 0x681820);
    RH_ScopedInstall(Flush, 0x681850);
    RH_ScopedInstall(FlushImmediately, 0x6818A0);
    RH_ScopedInstall(SetNextSubTask, 0x681920);
    RH_ScopedOverloadedInstall(GetSimplestTask, "of-task", 0x681970, CTask*(*)(CTask*));
    RH_ScopedOverloadedInstall(GetSimplestTask, "at-index", 0x681A00, CTask*(CTaskManager::*)(ePrimaryTasks));
    RH_ScopedInstall(StopTimers, 0x6819A0);
    RH_ScopedInstall(GetSimplestActiveTask, 0x6819D0);
    RH_ScopedInstall(AddSubTasks, 0x681A30);
    RH_ScopedInstall(ParentsControlChildren, 0x681A80);
    RH_ScopedInstall(SetTask, 0x681AF0);
    RH_ScopedInstall(SetTaskSecondary, 0x681B60);
    RH_ScopedInstall(ClearTaskEventResponse, 0x681BD0);
    RH_ScopedInstall(ManageTasks, 0x681C10);
}

static void DeleteTaskAndNull(CTask*& task) {
    delete task;
    task = nullptr;
}

/// Find the first task (or subtask) that is of the required type
inline CTask* FindFirstTaskOfType(CTask* task, eTaskType type) {
    for (; task; task = task->GetSubTask()) {
        if (task->GetTaskType() == type) {
            return task;
        }
    }
    return nullptr;
}

// 0x6816A0
CTaskManager::CTaskManager(CPed* ped) :
    m_pPed{ped}
{
}

// 0x6816D0
CTaskManager::~CTaskManager() {
    Flush();
}

// 0x681720
CTask* CTaskManager::GetActiveTask() {
    for (const auto task : m_aPrimaryTasks) {
        if (task) {
            return task;
        }
    }
    return nullptr;
}

// 0x681740
CTask* CTaskManager::FindActiveTaskByType(eTaskType taskType) {
    // First try current active task and it's sub-tasks
    if (const auto task = FindFirstTaskOfType(GetActiveTask(), taskType)) {
        return task;
    }

    // The same as above, but for all secondary tasks
    for (const auto sec : m_aSecondaryTasks) {
        if (const auto task = FindFirstTaskOfType(sec, taskType)) {
            return task;
        }
    }

    // Not found
    return nullptr;
}

// 0x6817D0
CTask* CTaskManager::FindTaskByType(ePrimaryTasks taskIndex, eTaskType taskId) {
    return FindFirstTaskOfType(GetTaskPrimary(taskIndex), taskId);
}

// 0x681810
CTask* CTaskManager::GetTaskSecondary(eSecondaryTask taskIndex) {
    return m_aSecondaryTasks[taskIndex];
}

// NOTSA?
bool CTaskManager::HasTaskPrimary(const CTask* task) {
    for (auto& primaryTask : m_aPrimaryTasks) {
        if (primaryTask && primaryTask == task) {
            return true;
        }
    }
    return false;
}

// 0x681820
bool CTaskManager::HasTaskSecondary(const CTask* task) {
    for (auto& secondaryTask : m_aSecondaryTasks) {
        if (secondaryTask && secondaryTask == task) {
            return true;
        }
    }
    return false;
}

// 0x681850
void CTaskManager::Flush() {
    ApplyToRootTasks(DeleteTaskAndNull);
}

// 0x6818A0
void CTaskManager::FlushImmediately() {
    ApplyToRootTasks([this](CTask*& task) {
        if (task) {
            if (task->MakeAbortable(m_pPed, ABORT_PRIORITY_IMMEDIATE, nullptr)) {
                DeleteTaskAndNull(task);
            }
        }
    });
}

// 0x681920
void CTaskManager::SetNextSubTask(CTaskComplex* ofTask) {
    if (!ofTask) {
        return;
    }

    for (auto task = ofTask; task; task = static_cast<CTaskComplex*>(task->m_pParentTask)) {
        if (const auto next = task->CreateNextSubTask(m_pPed)) {
            task->SetSubTask(next);
            AddSubTasks(next);
            break;
        } else {
            // If no subtask is created, the `task` is considered done,
            // thus we go to it's parent and create it's new subtask
            // which by effect will delete the current `task`, and so on...
            task->SetSubTask(nullptr);
        }
    }
}

// 0x681970
CTask* CTaskManager::GetSimplestTask(CTask* task) {
    auto last{task};
    for (; task; task = task->GetSubTask())
        last = task;
    return last;
}

// 0x6819A0
void CTaskManager::StopTimers(const CEvent* event) {
    for (auto& primaryTask : m_aPrimaryTasks) {
        if (primaryTask) {
            primaryTask->StopTimer(event);
        }
    }
}

// 0x681A30
void CTaskManager::AddSubTasks(CTask* toTask) {
    if (!toTask) {
        return;
    }

    for (auto task = toTask; !task->IsSimple();) {
        const auto ctask = task->AsComplex();
        assert(GetTaskPool()->IsObjectValid(task)); // Sometimes tasks seem to get deleted which causes pure virtual calls (because of destructcors setting the VMT to their's)
        if (const auto sub = ctask->CreateFirstSubTask(m_pPed)) {
            ctask->SetSubTask(sub);
            task = sub; // Go on creating the subtask of the created task
        } else { // No sub task created, so we can stop here
            if (ctask->m_pParentTask) {
                SetNextSubTask(ctask->m_pParentTask->AsComplex()); // We're a subtask of the parent (if any), thus parent must be complex
            }
            break;
        }
    }
}

// 0x681A80
void CTaskManager::ParentsControlChildren(CTask* parent) {
    for (auto task = parent; task && !task->IsSimple();) {
        const auto ctask = task->AsComplex();
        const auto subTask = ctask->GetSubTask();
        const auto newSubTask = ctask->ControlSubTask(m_pPed); // The function might return a new or the current sub-task or null, the latter indicating that the task is done
        if (newSubTask == subTask) { // [Invered] Subtask hasn't changed, so continue
            task = subTask;
        } else { // Subtask has changed, abort old, set new
            subTask->MakeAbortable(m_pPed, ABORT_PRIORITY_URGENT, nullptr);
            ctask->SetSubTask(newSubTask);
            AddSubTasks(newSubTask);
            break;
        }
    }
}

void CTaskManager::AbortFirstPrimaryTaskIn(std::initializer_list<ePrimaryTasks> slots, CPed* ped, eAbortPriority priority, const CEvent* event) {
    for (const auto slot : slots) {
        if (const auto task = GetTaskPrimary(slot)) {
            task->MakeAbortable(ped, priority, event);
            break;
        }
    }
}

// 0x681BD0
void CTaskManager::ClearTaskEventResponse() {
    // Looking at the code, I think `nontemp` is only present if `temp` is, as it's not deleted otherwise.
    for (const auto idx : { TASK_PRIMARY_EVENT_RESPONSE_TEMP, TASK_PRIMARY_EVENT_RESPONSE_NONTEMP }) {
        if (auto& task = m_aPrimaryTasks[idx]) {
            DeleteTaskAndNull(task);
            break;
        }
    }
}

// 0x681C10
void CTaskManager::ManageTasks() {
    // Get taskIndex of first available primary task
    int32 taskIndex = 0;
    while (!GetTaskPrimary(taskIndex)) {
        taskIndex = taskIndex + 1;
        if (taskIndex >= TASK_PRIMARY_MAX) {
            break;
        }
    }

    if (taskIndex > -1 && taskIndex < TASK_PRIMARY_MAX) {
        CTask* simplestTask = GetSimplestTask(GetTaskPrimary(taskIndex));
        if (!simplestTask->IsSimple()) {
            delete m_aPrimaryTasks[taskIndex];
            m_aPrimaryTasks[taskIndex] = nullptr;
            return;
        }

        for (int32 i = 0; i < TASK_PRIMARY_MAX + TASK_SECONDARY_MAX; i++) {
            ParentsControlChildren((CTaskComplex*)GetTaskPrimary(taskIndex));
            simplestTask = GetSimplestTask(GetTaskPrimary(taskIndex));
            if (!simplestTask->IsSimple()) {
                SetNextSubTask((CTaskComplex*)simplestTask->m_pParentTask);
                simplestTask = GetSimplestTask(GetTaskPrimary(taskIndex));
                if (!simplestTask->IsSimple()) {
                    delete m_aPrimaryTasks[taskIndex];
                    m_aPrimaryTasks[taskIndex] = nullptr;
                    break;
                }
            }

            simplestTask = GetSimplestTask(GetTaskPrimary(taskIndex));
            if (!simplestTask->AsSimple()->ProcessPed(m_pPed)) {
                break;
            } else {
                SetNextSubTask((CTaskComplex*)simplestTask->m_pParentTask);
                if (!GetTaskPrimary(taskIndex)->GetSubTask()) {
                    delete m_aPrimaryTasks[taskIndex];
                    m_aPrimaryTasks[taskIndex] = nullptr;
                    break;
                }
            }
        }
    }

    for (auto& secondaryTask : m_aSecondaryTasks) {
        if (!secondaryTask)
            continue;

        bool bProcessPedFailed = false;
        while (true) {
            ParentsControlChildren((CTaskComplex*)secondaryTask);
            auto simplestTask1 = GetSimplestTask(secondaryTask);
            if (!simplestTask1->IsSimple()) {
                break;
            }

            simplestTask1 = GetSimplestTask(secondaryTask);
            if (!simplestTask1->AsSimple()->ProcessPed(m_pPed)) {
                bProcessPedFailed = true;
                break;
            }

            SetNextSubTask((CTaskComplex*)simplestTask1->m_pParentTask);
            if (!secondaryTask->GetSubTask()) {
                break;
            }
        }

        if (bProcessPedFailed) {
            continue;
        }

        delete secondaryTask;
        secondaryTask = nullptr;
    }
}

void CTaskManager::ChangeTaskInSlot(CTask*& taskInSlot, CTask* changeTo) {
    // Nothing to do in case they're the same
    if (taskInSlot == changeTo) {
        return;
    }

    // Delete current
    delete taskInSlot;

    // Set the task in the slot, and add it's subtasks
    taskInSlot = changeTo;
    AddSubTasks(taskInSlot);

    if (taskInSlot && !GetSimplestTask(taskInSlot)->IsSimple()) {
        DeleteTaskAndNull(taskInSlot); // Delete it (TODO: Why?)
    }
}
