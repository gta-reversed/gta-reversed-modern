/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

void CTaskManager::InjectHooks()
{
    CTaskSimple::InjectHooks();

    ReversibleHooks::Install("CTaskManager", "Constructor", 0x6816A0, &CTaskManager::Constructor);
    ReversibleHooks::Install("CTaskManager", "Destructor", 0x6816D0, &CTaskManager::Destructor);
    ReversibleHooks::Install("CTaskManager", "GetActiveTask", 0x681720, &CTaskManager::GetActiveTask);
    ReversibleHooks::Install("CTaskManager", "FindActiveTaskByType", 0x681740, &CTaskManager::FindActiveTaskByType);
    ReversibleHooks::Install("CTaskManager", "FindTaskByType", 0x6817D0, &CTaskManager::FindTaskByType);
    ReversibleHooks::Install("CTaskManager", "GetTaskSecondary", 0x681810, &CTaskManager::GetTaskSecondary);
    ReversibleHooks::Install("CTaskManager", "HasTaskSecondary", 0x681820, &CTaskManager::HasTaskSecondary);
    ReversibleHooks::Install("CTaskManager", "Flush", 0x681850, &CTaskManager::Flush);
    ReversibleHooks::Install("CTaskManager", "FlushImmediately", 0x6818A0, &CTaskManager::FlushImmediately);
    ReversibleHooks::Install("CTaskManager", "SetNextSubTask", 0x681920, &CTaskManager::SetNextSubTask);
    ReversibleHooks::Install("CTaskManager", "GetSimplestTask_task", 0x681970, (CTaskSimple*(*)(CTask*))&CTaskManager::GetSimplestTask);
    ReversibleHooks::Install("CTaskManager", "GetSimplestTask_tasK_index", 0x681A00, (CTaskSimple*(CTaskManager::*)(int))&CTaskManager::GetSimplestTask);
    ReversibleHooks::Install("CTaskManager", "StopTimers", 0x6819A0, &CTaskManager::StopTimers);
    ReversibleHooks::Install("CTaskManager", "GetSimplestActiveTask", 0x6819D0, &CTaskManager::GetSimplestActiveTask);
    ReversibleHooks::Install("CTaskManager", "AddSubTasks", 0x681A30, &CTaskManager::AddSubTasks);
    ReversibleHooks::Install("CTaskManager", "ParentsControlChildren", 0x681A80, &CTaskManager::ParentsControlChildren);
    ReversibleHooks::Install("CTaskManager", "SetTask", 0x681AF0, &CTaskManager::SetTask);
    ReversibleHooks::Install("CTaskManager", "SetTaskSecondary", 0x681B60, &CTaskManager::SetTaskSecondary);
    ReversibleHooks::Install("CTaskManager", "ClearTaskEventResponse", 0x681BD0, &CTaskManager::ClearTaskEventResponse);
    ReversibleHooks::Install("CTaskManager", "ManageTasks", 0x681C10, &CTaskManager::ManageTasks);
}

// 0x6816A0
CTaskManager* CTaskManager::Constructor(CPed* ped) {
    m_pPed = ped;
    m_aPrimaryTasks[0] = nullptr;
    m_aPrimaryTasks[1] = nullptr;
    m_aPrimaryTasks[2] = nullptr;
    m_aPrimaryTasks[3] = nullptr;
    m_aPrimaryTasks[4] = nullptr;
    memset(m_aSecondaryTasks, 0, sizeof(m_aSecondaryTasks));
    return this;
}

// 0x6816D0
void CTaskManager::Destructor() {
    Flush();
}

// 0x681720
CTask* CTaskManager::GetActiveTask() {
    for (auto& task : m_aPrimaryTasks)
    {
        if (task)
        {
            return task;
        }
    }
    return nullptr;
}

// 0x681740
CTask* CTaskManager::FindActiveTaskByType(int taskType) {
    // First try current active task, and its sub-tasks
    for (CTask* task = GetActiveTask(); task; task = task->GetSubTask()) {
        if (task->GetId() == taskType) {
            return task;
        }
    }

    // Traverse all secondary tasks and their subtasks, and return last match
    CTask* lastFound = nullptr;
    for (int i = 0; i < TASK_SECONDARY_MAX; i++) {
        for (CTask* sub = GetTaskSecondary(i); sub; sub = sub->GetSubTask()) {
            if (sub->GetId() == taskType) {
                lastFound = sub;
                break; /* break inner */
            }
        }
    }
    // TODO, NOTE: This is stupid. Why go begin -> end, and return the last match, when
    // going end -> begin and returning the last matching sub-task would do the same?
    return lastFound;
}

// 0x6817D0
CTask* CTaskManager::FindTaskByType(int taskIndex, int taskId) {
    for (CTask* task = GetPrimaryTask(taskIndex); task; task = task->GetSubTask()) {
        if (task->GetId() == taskId) {
            return task;
        }
    }
    return nullptr;
}

// 0x681810
CTask* CTaskManager::GetTaskSecondary(int taskIndex) {
    return m_aSecondaryTasks[taskIndex];
}

// 0x681820
bool CTaskManager::HasTaskSecondary(CTask const* task) {
    for (auto& secondaryTask : m_aSecondaryTasks) {
        if (secondaryTask && secondaryTask == task)
            return true;
    }
    return false;
}

// 0x681850
void CTaskManager::Flush() {
    for (auto& primaryTask : m_aPrimaryTasks)
    {
        delete primaryTask;
        primaryTask = nullptr;
    }

    for (auto& secondaryTask : m_aSecondaryTasks)
    {
        delete secondaryTask;
        secondaryTask = nullptr;
    }
}

// 0x6818A0
void CTaskManager::FlushImmediately() {
    for (auto& primaryTask : m_aPrimaryTasks)
    {
        if (primaryTask && primaryTask->MakeAbortable(m_pPed, ABORT_PRIORITY_IMMEDIATE, nullptr))
        {
            delete primaryTask;
        }
        primaryTask = nullptr;
    }

    for (auto& secondaryTask : m_aSecondaryTasks)
    {
        if (secondaryTask && secondaryTask->MakeAbortable(m_pPed, ABORT_PRIORITY_IMMEDIATE, nullptr))
        {
            delete secondaryTask;
        }
        secondaryTask = nullptr;
    }
}

// 0x681920
void CTaskManager::SetNextSubTask(CTaskComplex* pTask) {
    CTask* nextSubTask = nullptr;
    if (pTask)
    {
        while (true)
        {
            nextSubTask = pTask->CreateNextSubTask(m_pPed);
            if (nextSubTask)
            {
                break;
            }
            pTask->SetSubTask(nullptr);
            pTask = static_cast<CTaskComplex*>(pTask->m_pParentTask);

            if (!pTask)
            {
                return;
            }
        }
        pTask->SetSubTask(nextSubTask);
        AddSubTasks((CTaskComplex*)nextSubTask);
    }
}

// 0x681970
CTaskSimple* CTaskManager::GetSimplestTask(CTask* pTask) {
    CTaskSimple* result = nullptr;
    while (pTask)
    {
        result = static_cast<CTaskSimple*>(pTask);
        pTask = pTask->GetSubTask();
    }
    return result;
}

// (CEvent const* _event)
// 0x6819A0
void CTaskManager::StopTimers(CEvent* pEvent) {
    for (auto& primaryTask : m_aPrimaryTasks)
    {
        if (primaryTask)
        {
            primaryTask->StopTimer(pEvent);
        }
    }
}

// 0x6819D0
CTask* CTaskManager::GetSimplestActiveTask() {
    CTask* task = nullptr;
    CTask* result = nullptr;
    int primaryTaskIndex = 0;
    while (!m_aPrimaryTasks[primaryTaskIndex])
    {
        if (++primaryTaskIndex >= TASK_PRIMARY_MAX)
        {
            task = nullptr;
            goto GET_SIMPLE_TASK;
        }
    }

    task = m_aPrimaryTasks[primaryTaskIndex];

GET_SIMPLE_TASK:
    while (task)
    {
        result = task;
        task = task->GetSubTask();
    }
    return result;
}

// 0x681A00
CTaskSimple* CTaskManager::GetSimplestTask(int taskIndex) {
    CTaskSimple* result = nullptr;
    CTask* pTask = m_aPrimaryTasks[taskIndex];
    while (pTask)
    {
        result = static_cast<CTaskSimple*>(pTask);
        pTask = pTask->GetSubTask();
    }
    return result;
}

// 0x681A30
void CTaskManager::AddSubTasks(CTaskComplex* pTask) {
    if (pTask)
    {
        CTask* pSubTask = nullptr;
        do
        {
            if (pTask->IsSimple())
            {
                break;
            }
            pSubTask = pTask->CreateFirstSubTask(m_pPed);
            if (pSubTask)
            {
                pTask->SetSubTask(pSubTask);
            }
            else
            {
                SetNextSubTask(static_cast<CTaskComplex*>(pTask->m_pParentTask));
            }
            pTask = static_cast<CTaskComplex*>(pSubTask);
        } while (pSubTask);
    }
}

// (CTask *task)
// 0x681A80
void CTaskManager::ParentsControlChildren(CTaskComplex* pTask) {
    if (pTask)
    {
        while (!pTask->IsSimple())
        {
            CTask* pSubTask = pTask->GetSubTask();
            CTaskComplex* pControlSubTask = static_cast<CTaskComplex*>(pTask->ControlSubTask(m_pPed));
            if (pSubTask != pControlSubTask)
            {
                pSubTask->MakeAbortable(m_pPed, ABORT_PRIORITY_URGENT, nullptr);
                pTask->SetSubTask(pControlSubTask);
                AddSubTasks(pControlSubTask);
                return;
            }
            pTask = static_cast<CTaskComplex*>(pTask->GetSubTask());
            if (!pTask)
            {
                return;
            }
        }
    }
}

// (CTask *task, int taskIndex, bool)
// 0x681AF0
void CTaskManager::SetTask(CTask* pTask, int taskIndex, int arg2) {
    CTask* pPrimaryTask = nullptr;
    if (!pTask)
    {
        pPrimaryTask = m_aPrimaryTasks[taskIndex];
        if (pPrimaryTask)
        {
            delete pPrimaryTask;
            m_aPrimaryTasks[taskIndex] = nullptr;
            return;
        }
    }

    pPrimaryTask = m_aPrimaryTasks[taskIndex];
    if (pPrimaryTask != pTask)
    {
        delete pPrimaryTask;

        m_aPrimaryTasks[taskIndex] = pTask;
        AddSubTasks(static_cast<CTaskComplex*>(pTask));
        if (m_aPrimaryTasks[taskIndex])
        {
            CTask* pSimplestTask = GetSimplestTask(m_aPrimaryTasks[taskIndex]);
            if (!pSimplestTask->IsSimple())
            {
                pPrimaryTask = m_aPrimaryTasks[taskIndex];
                if (!pPrimaryTask)
                {
                    m_aPrimaryTasks[taskIndex] = nullptr;
                    return;
                }
                delete pPrimaryTask;
                m_aPrimaryTasks[taskIndex] = nullptr;
                return;
            }
        }
    }
}

// 0x681B60
void CTaskManager::SetTaskSecondary(CTask* pTask, int taskIndex) {
    CTask* pCurrentSecondaryTask = m_aSecondaryTasks[taskIndex];
    if (pCurrentSecondaryTask != pTask)
    {
        if (pCurrentSecondaryTask)
        {
            delete pCurrentSecondaryTask;
            pCurrentSecondaryTask = nullptr;
        }
        m_aSecondaryTasks[taskIndex] = pTask;
        AddSubTasks(static_cast<CTaskComplex*>(pTask));
        CTask* pTheTask = m_aSecondaryTasks[taskIndex];
        if (pTheTask)
        {
            CTask* pSimpleTask = nullptr;
            do
            {
                pSimpleTask = pTheTask;
                pTheTask = pTheTask->GetSubTask();
            } while (pTheTask);

            if (!pSimpleTask->IsSimple())
            {
                delete m_aSecondaryTasks[taskIndex];
                m_aSecondaryTasks[taskIndex] = nullptr;
            }
        }
    }
}

// 0x681BD0
void CTaskManager::ClearTaskEventResponse() {
    CTask* pTask = m_aPrimaryTasks[TASK_PRIMARY_EVENT_RESPONSE_TEMP];
    if (pTask)
    {
        delete pTask;
        m_aPrimaryTasks[TASK_PRIMARY_EVENT_RESPONSE_TEMP] = nullptr;
    }
    else
    {
        pTask = m_aPrimaryTasks[TASK_PRIMARY_EVENT_RESPONSE_NONTEMP];
        if (pTask)
        {
            delete pTask;
            m_aPrimaryTasks[TASK_PRIMARY_EVENT_RESPONSE_NONTEMP] = nullptr;
        }
    }
}

// 0x681C10
void CTaskManager::ManageTasks()
{
    int iTaskIndex = 0;

    while (!m_aPrimaryTasks[iTaskIndex])
    {
        iTaskIndex = iTaskIndex + 1;
        if (iTaskIndex >= TASK_PRIMARY_MAX)
        {
            break;
        }
    }

    if (iTaskIndex > -1 && iTaskIndex < TASK_PRIMARY_MAX)
    {
        CTask* pSimplestTask = GetSimplestTask(m_aPrimaryTasks[iTaskIndex]);
        if (!pSimplestTask->IsSimple())
        {
            delete m_aPrimaryTasks[iTaskIndex];
            m_aPrimaryTasks[iTaskIndex] = nullptr;
            return;
        }

        for (int i = 0; i < 11; i++)
        {
            ParentsControlChildren((CTaskComplex*)m_aPrimaryTasks[iTaskIndex]);
            CTask* pSimplestTask = GetSimplestTask(m_aPrimaryTasks[iTaskIndex]);
            if (!pSimplestTask->IsSimple())
            {
                SetNextSubTask((CTaskComplex*)pSimplestTask->m_pParentTask);
                CTask* pSimplestTask = GetSimplestTask(m_aPrimaryTasks[iTaskIndex]);
                if (!pSimplestTask->IsSimple())
                {
                    delete m_aPrimaryTasks[iTaskIndex];
                    m_aPrimaryTasks[iTaskIndex] = nullptr;
                    break;
                }
            }
            CTaskSimple* pSimpleTask = GetSimplestTask(m_aPrimaryTasks[iTaskIndex]);
            if (!pSimpleTask->ProcessPed(m_pPed))
            {
                break;
            }
            else
            {
                SetNextSubTask((CTaskComplex*)pSimpleTask->m_pParentTask);
                if (!m_aPrimaryTasks[iTaskIndex]->GetSubTask())
                {
                    delete m_aPrimaryTasks[iTaskIndex];
                    m_aPrimaryTasks[iTaskIndex] = nullptr;
                    break;
                }
            }
        }
    }

    for (auto& secondaryTask : m_aSecondaryTasks)
    {
        if (secondaryTask)
        {
            bool bProcessPedFailed = false;
            while (true)
            {
                ParentsControlChildren((CTaskComplex*)secondaryTask);
                CTaskSimple* pSimplestTask = GetSimplestTask(secondaryTask);
                if (!pSimplestTask->IsSimple())
                {
                    break;
                }

                pSimplestTask = GetSimplestTask(secondaryTask);
                if (!pSimplestTask->ProcessPed(m_pPed))
                {
                    bProcessPedFailed =  true;
                    break;
                }

                SetNextSubTask((CTaskComplex*)pSimplestTask->m_pParentTask);
                if (!secondaryTask->GetSubTask())
                {
                    break;
                }
            }

            if (bProcessPedFailed)
            {
                continue;
            }
            delete secondaryTask;
            secondaryTask = nullptr;
        }
    }
}

bool CTaskManager::HasPrimaryTask(CTask const* task)
{
    for (auto& primaryTask : m_aPrimaryTasks) {
        if (primaryTask && primaryTask == task)
            return true;
    }
    return false;
}
