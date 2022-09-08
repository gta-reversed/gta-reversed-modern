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
    RH_ScopedOverloadedInstall(GetSimplestTask, "task", 0x681970, CTaskSimple * (*)(CTask*));
    RH_ScopedOverloadedInstall(GetSimplestTask, "index", 0x681A00, CTaskSimple * (CTaskManager::*)(int32));
    RH_ScopedInstall(StopTimers, 0x6819A0);
    RH_ScopedInstall(GetSimplestActiveTask, 0x6819D0);
    RH_ScopedInstall(AddSubTasks, 0x681A30);
    RH_ScopedInstall(ParentsControlChildren, 0x681A80);
    RH_ScopedInstall(SetTask, 0x681AF0);
    RH_ScopedInstall(SetTaskSecondary, 0x681B60);
    RH_ScopedInstall(ClearTaskEventResponse, 0x681BD0);
    RH_ScopedInstall(ManageTasks, 0x681C10);
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
    for (auto& task : m_aPrimaryTasks) {
        if (task) {
            return task;
        }
    }
    return nullptr;
}

// 0x681740
CTask* CTaskManager::FindActiveTaskByType(int32 taskType) {
    // First try current active task, and its sub-tasks
    for (CTask* task = GetActiveTask(); task; task = task->GetSubTask()) {
        if (task->GetTaskType() == taskType) {
            return task;
        }
    }

    // Traverse all secondary tasks and their subtasks, and return last match
    CTask* lastFound = nullptr;
    for (int32 i = 0; i < TASK_SECONDARY_MAX; i++) {
        for (CTask* sub = GetTaskSecondary(i); sub; sub = sub->GetSubTask()) {
            if (sub->GetTaskType() == taskType) {
                lastFound = sub;
                break; /* break inner */
            }
        }
    }
    // TODO, NOTE: This is stupid. Why go begin -> end, and return the last match, when
    // going end -> begin and returning the first matching sub-task would do the same? (Eg.: doing the above loop in reverse)
    // TBH I think they just forgot to put a break, but who knows.
    return lastFound;
}

// 0x6817D0
CTask* CTaskManager::FindTaskByType(ePrimaryTasks taskIndex, eTaskType taskId) {
    for (CTask* task = GetTaskPrimary(taskIndex); task; task = task->GetSubTask()) {
        if (task->GetTaskType() == taskId) {
            return task;
        }
    }
    return nullptr;
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
    ApplyToRootTasks([](CTask*& task) {
        delete task;
        task = nullptr;
    });
}

// 0x6818A0
void CTaskManager::FlushImmediately() {
    ApplyToRootTasks([this](CTask*& task) {
        if (task) {
            if (task->MakeAbortable(m_pPed, ABORT_PRIORITY_IMMEDIATE, nullptr)) {
                delete task;
                task = nullptr;
            }
        }
    });
}

// 0x681920
void CTaskManager::SetNextSubTask(CTaskComplex* ofTask) {
    if (!ofTask) {
        return;
    }

    for (auto task = ofTask; task = static_cast<CTaskComplex*>(task->m_pParentTask); task) {
        if (const auto next = task->CreateNextSubTask(m_pPed)) {
            task->SetSubTask(next);
            AddSubTasks(next);
            break;
        } else {
            task->SetSubTask(nullptr);
        }
    }
}

// 0x681970
CTaskSimple* CTaskManager::GetSimplestTask(CTask* task) {
    CTask* last = nullptr;
    for (; task; task = task->GetSubTask())
        last = task;
    return last->AsSimple();
}

// 0x6819A0
void CTaskManager::StopTimers(const CEvent* event) {
    for (auto& primaryTask : m_aPrimaryTasks) {
        if (primaryTask) {
            primaryTask->StopTimer(event);
        }
    }
}

// 0x6819D0
CTask* CTaskManager::GetSimplestActiveTask() {
    return GetSimplestTask(GetActiveTask());
}

// 0x681A00
CTaskSimple* CTaskManager::GetSimplestTask(int32 taskIndex) {
    return GetSimplestTask(GetTaskPrimary(taskIndex));
}

// 0x681A30
void CTaskManager::AddSubTasks(CTask* task) {
    if (!task)
        return;

    CTask* subTask = nullptr;
    do {
        if (task->IsSimple()) {
            break;
        }

        subTask = task->AsComplex()->CreateFirstSubTask(m_pPed);
        if (subTask) {
            task->AsComplex()->SetSubTask(subTask);
        } else {
            SetNextSubTask(task->m_pParentTask->AsComplex());
        }
        task = subTask->AsComplex();
    } while (subTask);
}

// 0x681A80
void CTaskManager::ParentsControlChildren(CTaskComplex* task) {
    if (!task)
        return;

    for (; !task->IsSimple(); task = task->GetSubTask()->AsComplex()) {
        CTask* subTask = task->GetSubTask();
        auto* controlSubTask = task->ControlSubTask(m_pPed)->AsComplex();
        if (subTask != controlSubTask) {
            subTask->MakeAbortable(m_pPed, ABORT_PRIORITY_URGENT, nullptr);
            task->SetSubTask(controlSubTask);
            AddSubTasks(controlSubTask);
            return;
        }
    }
}

// 0x681AF0
void CTaskManager::SetTask(CTask* task, int32 taskIndex, bool unused) {
    CTask* primaryTask = nullptr;
    if (!task) {
        primaryTask = m_aPrimaryTasks[taskIndex];
        if (primaryTask) {
            delete primaryTask;
            m_aPrimaryTasks[taskIndex] = nullptr;
            return;
        }
    }

    primaryTask = m_aPrimaryTasks[taskIndex];
    if (primaryTask == task)
        return;

    delete primaryTask;

    m_aPrimaryTasks[taskIndex] = task;
    AddSubTasks(task->AsComplex());
    if (GetTaskPrimary(taskIndex)) {
        CTask* simplestTask = GetSimplestTask(m_aPrimaryTasks[taskIndex]);
        if (!simplestTask->IsSimple()) {
            primaryTask = m_aPrimaryTasks[taskIndex];
            if (!primaryTask) {
                m_aPrimaryTasks[taskIndex] = nullptr;
                return;
            }
            delete primaryTask;
            m_aPrimaryTasks[taskIndex] = nullptr;
            return;
        }
    }
}

// 0x681B60
void CTaskManager::SetTaskSecondary(CTask* task, int32 taskIndex) {
    if (const auto current = GetTaskSecondary(taskIndex)) {
        if (current == task) {
            return;
        }
        delete current;
    }

    m_aSecondaryTasks[taskIndex] = task;

    AddSubTasks(task->AsComplex());

    if (auto* simplest = GetSimplestTask(GetTaskSecondary(taskIndex))) {
        if (!simplest->IsSimple()) {
            delete m_aSecondaryTasks[taskIndex];
            m_aSecondaryTasks[taskIndex] = nullptr;
        }
    }
}

// 0x681BD0
void CTaskManager::ClearTaskEventResponse() {
    CTask* task = GetTaskPrimary(TASK_PRIMARY_EVENT_RESPONSE_TEMP);
    if (task) {
        delete task;
        m_aPrimaryTasks[TASK_PRIMARY_EVENT_RESPONSE_TEMP] = nullptr;
    } else {
        task = m_aPrimaryTasks[TASK_PRIMARY_EVENT_RESPONSE_NONTEMP];
        if (task) {
            delete task;
            m_aPrimaryTasks[TASK_PRIMARY_EVENT_RESPONSE_NONTEMP] = nullptr;
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
            CTaskSimple* simplestTask1 = GetSimplestTask(secondaryTask);
            if (!simplestTask1->IsSimple()) {
                break;
            }

            simplestTask1 = GetSimplestTask(secondaryTask);
            if (!simplestTask1->ProcessPed(m_pPed)) {
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
