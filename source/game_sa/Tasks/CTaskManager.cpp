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

    HookInstall(0x6816A0, &CTaskManager::Constructor, 7);
    HookInstall(0x6816D0, &CTaskManager::Destructor, 7);
    HookInstall(0x681720, &CTaskManager::GetActiveTask, 7);
    HookInstall(0x681740, &CTaskManager::FindActiveTaskByType, 7);
    HookInstall(0x6817D0, &CTaskManager::FindTaskByType, 7);
    HookInstall(0x681810, &CTaskManager::GetTaskSecondary, 7);
    HookInstall(0x681820, &CTaskManager::HasTaskSecondary, 7);
    HookInstall(0x681850, &CTaskManager::Flush, 7);
    HookInstall(0x6818A0, &CTaskManager::FlushImmediately, 7);
    HookInstall(0x681920, &CTaskManager::SetNextSubTask, 7);
    HookInstall(0x681970, (CTaskSimple*(*)(CTask*))&CTaskManager::GetSimplestTask, 7);
    HookInstall(0x6819A0, &CTaskManager::StopTimers, 7);
    HookInstall(0x6819D0, &CTaskManager::GetSimplestActiveTask, 7);
    HookInstall(0x681A00, (CTaskSimple*(CTaskManager::*)(int taskIndex))&CTaskManager::GetSimplestTask, 7);
    HookInstall(0x681A30, &CTaskManager::AddSubTasks, 7);
    HookInstall(0x681A80, &CTaskManager::ParentsControlChildren, 7);
    HookInstall(0x681AF0, &CTaskManager::SetTask, 7);
    HookInstall(0x681B60, &CTaskManager::SetTaskSecondary, 7);
    HookInstall(0x681BD0, &CTaskManager::ClearTaskEventResponse, 7);
    HookInstall(0x681C10, &CTaskManager::ManageTasks, 7);
}

// Converted from thiscall void CTaskManager::CTaskManager(CPed *ped) 0x6816A0
CTaskManager* CTaskManager::Constructor(CPed* ped) {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((CTaskManager * (__thiscall *)(CTaskManager*, CPed*))0x6816A0)(this, ped);
#else
    m_pPed = ped;
    m_aPrimaryTasks[0] = 0;
    m_aPrimaryTasks[1] = 0;
    m_aPrimaryTasks[2] = 0;
    m_aPrimaryTasks[3] = 0;
    m_aPrimaryTasks[4] = 0;
    memset(m_aSecondaryTasks, 0, sizeof(m_aSecondaryTasks));
    return this;
#endif
}

// Converted from thiscall void CTaskManager::~CTaskManager() 0x6816D0
void CTaskManager::Destructor() {
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CTaskManager*))0x6816D0)(this);
#else
    for (int primaryTaskIndex = 0; primaryTaskIndex < 5; primaryTaskIndex++)
    {
        CTask* task = m_aPrimaryTasks[primaryTaskIndex];
        if (task)
        {
            task->DeletingDestructor(1);
        }
        m_aPrimaryTasks[primaryTaskIndex] = 0;
    }


    for (int secondaryTaskIndex = 0; secondaryTaskIndex < 6; secondaryTaskIndex++)
    {
        CTask* pSecondaryTask = m_aSecondaryTasks[secondaryTaskIndex];
        if (pSecondaryTask)
        {
            pSecondaryTask->DeletingDestructor(1);
        }
        m_aSecondaryTasks[secondaryTaskIndex] = 0;
    }
#endif
}

// Converted from thiscall CTask* CTaskManager::GetActiveTask(void) 0x681720
CTask* CTaskManager::GetActiveTask() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((CTask* (__thiscall *)(CTaskManager*))0x681720)(this);
#else
    for (int primaryTaskIndex = 0; primaryTaskIndex < 5; primaryTaskIndex++)
    {
        CTask* task = m_aPrimaryTasks[primaryTaskIndex];
        if (task)
        {
            return task;
        }
    }
    return nullptr;
#endif
}

// Converted from thiscall CTask* CTaskManager::FindActiveTaskByType(int taskType) 0x681740
CTask* CTaskManager::FindActiveTaskByType(int taskType) {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((CTask* (__thiscall *)(CTaskManager*, int))0x681740)(this, taskType);
#else
    CTask* result = nullptr;
    int primaryTaskIndex = 0;
    while (!m_aPrimaryTasks[primaryTaskIndex])
    {
        if (++primaryTaskIndex >= 5)
        {
            goto CHECK_IN_SECONDARY_TASKS;
        }
    }
    CTask* pPrimaryTask = (CTask*)m_aPrimaryTasks[primaryTaskIndex];
    if (!pPrimaryTask)
    {
    CHECK_IN_SECONDARY_TASKS:
        for (int secondaryTaskIndex = 0; secondaryTaskIndex < 6; secondaryTaskIndex++)
        {
            CTask* task = m_aSecondaryTasks[secondaryTaskIndex];
            while (task)
            {
                if (result)
                {
                    break;
                }
                if (task->GetId() == taskType)
                {
                    result = task;
                }

                task = task->GetSubTask();
            }
        }
        return result;
    }

    while (!result)
    {
        if (pPrimaryTask->GetId() == taskType)
        {
            result = pPrimaryTask;
        }
        pPrimaryTask = pPrimaryTask->GetSubTask();
        if (!pPrimaryTask)
        {
            if (result)
            {
                return result;
            }
            goto CHECK_IN_SECONDARY_TASKS;
        }
    }
    return result;
#endif
}

// Converted from thiscall CTask* CTaskManager::FindTaskByType(int taskIndex,int taskType) 0x6817D0
CTask* CTaskManager::FindTaskByType(int taskIndex, int taskId) {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((CTask* (__thiscall *)(CTaskManager*, int, int))0x6817D0)(this, taskIndex, taskId);
#else
    CTask* result = nullptr;
    CTask* pTask = m_aPrimaryTasks[taskIndex];
    while (pTask)
    {
        if (result)
        {
            break;
        }
        if (pTask->GetId() == taskId)
        {
            result = pTask;
        }
        pTask = pTask->GetSubTask();
    }
    return result;
#endif
}

// Converted from thiscall CTask* CTaskManager::GetTaskSecondary(int taskIndex) 0x681810
CTask* CTaskManager::GetTaskSecondary(int taskIndex) {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((CTask* (__thiscall *)(CTaskManager*, int))0x681810)(this, taskIndex);
#else
    return m_aSecondaryTasks[taskIndex];
#endif
}

// Converted from thiscall bool CTaskManager::HasTaskSecondary(CTask const*task) 0x681820
bool CTaskManager::HasTaskSecondary(CTask const* task) {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall *)(CTaskManager*, CTask const*))0x681820)(this, task);
#else
    for (int secondaryTaskIndex = 0; secondaryTaskIndex < 6; secondaryTaskIndex++)
    {
        CTask* pSecondaryTask = m_aSecondaryTasks[secondaryTaskIndex];
        if (pSecondaryTask == task)
        {
            return true;
        }
    }
    return false;
#endif
}

// Converted from thiscall void CTaskManager::Flush(void) 0x681850
void CTaskManager::Flush() {
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CTaskManager*))0x681850)(this);
#else
    for (int primaryTaskIndex = 0; primaryTaskIndex < 5; primaryTaskIndex++)
    {
        CTask* task = m_aPrimaryTasks[primaryTaskIndex];
        if (task)
        {
            task->DeletingDestructor(1);
        }

        m_aPrimaryTasks[primaryTaskIndex] = 0;
    }

    for (int secondaryTaskIndex = 0; secondaryTaskIndex < 6; secondaryTaskIndex++)
    {
        CTask* pSecondaryTask = m_aSecondaryTasks[secondaryTaskIndex];
        if (pSecondaryTask)
        {
            pSecondaryTask->DeletingDestructor(1);
        }

        m_aSecondaryTasks[secondaryTaskIndex] = 0;
    }
#endif
}

// Converted from thiscall void CTaskManager::FlushImmediately(void) 0x6818A0
void CTaskManager::FlushImmediately() {
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CTaskManager*))0x6818A0)(this);
#else
    for (int primaryTaskIndex = 0; primaryTaskIndex < 5; primaryTaskIndex++)
    {
        CTask* task = m_aPrimaryTasks[primaryTaskIndex];
        if (task && task->MakeAbortable(m_pPed, ABORT_PRIORITY_IMMEDIATE, 0))
        {
            task->DeletingDestructor(1);
        }

        m_aPrimaryTasks[primaryTaskIndex] = 0;
    }

    for (int secondaryTaskIndex = 0; secondaryTaskIndex < 6; secondaryTaskIndex++)
    {
        CTask* pSecondaryTask = m_aSecondaryTasks[secondaryTaskIndex];
        if (pSecondaryTask && pSecondaryTask->MakeAbortable(m_pPed, ABORT_PRIORITY_IMMEDIATE, 0))
        {
            pSecondaryTask->DeletingDestructor(1);
        }

        m_aSecondaryTasks[secondaryTaskIndex] = 0;
    }
#endif
}

// Converted from thiscall void CTaskManager::SetNextSubTask(CTask *task) 0x681920
void CTaskManager::SetNextSubTask(CTaskComplex* pTask) {
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CTaskManager*, CTaskComplex*))0x681920)(this, pTask);
#else
    CTask* nextSubTask = nullptr;
    if (pTask)
    {
        while (1)
        {
            nextSubTask = pTask->CreateNextSubTask(m_pPed);
            if (nextSubTask)
            {
                break;
            }
            pTask->SetSubTask(0);
            pTask = static_cast<CTaskComplex*>(pTask->m_pParentTask);

            if (!pTask)
            {
                return;
            }
        }
        pTask->SetSubTask(nextSubTask);
        AddSubTasks((CTaskComplex*)nextSubTask);
    }
#endif
}

// Converted from thiscall CTask* CTaskManager::GetSimplestTask(CTask *task) 0x681970
CTaskSimple* CTaskManager::GetSimplestTask(CTask* pTask) {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((CTaskSimple * (__cdecl *)(CTask*))0x681970)(pTask);
#else
    CTaskSimple* result = nullptr;
    while (pTask)
    {
        result = static_cast<CTaskSimple*>(pTask);
        pTask = pTask->GetSubTask();
    }
    return result;
#endif
}

// Converted from thiscall void CTaskManager::StopTimers(CEvent const*_event) 0x6819A0
void CTaskManager::StopTimers(CEvent* pEvent) {
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CTaskManager*, CEvent const*))0x6819A0)(this, pEvent);
#else
    for (int primaryTaskIndex = 0; primaryTaskIndex < 5; primaryTaskIndex++)
    {
        CTask* pPrimaryTask = m_aPrimaryTasks[primaryTaskIndex];
        if (pPrimaryTask)
        {
            pPrimaryTask->StopTimer(pEvent);
        }
    }
#endif
}

// Converted from thiscall CTask* CTaskManager::GetSimplestActiveTask(void) 0x6819D0
CTask* CTaskManager::GetSimplestActiveTask() {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((CTask* (__thiscall *)(CTaskManager*))0x6819D0)(this);
#else
    CTask* task = nullptr;
    CTask* result = nullptr;
    int primaryTaskIndex = 0;
    while (!m_aPrimaryTasks[primaryTaskIndex])
    {
        if (++primaryTaskIndex >= 5)
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
#endif
}

// Converted from thiscall CTask* CTaskManager::GetSimplestTask(int taskIndex) 0x681A00
CTaskSimple* CTaskManager::GetSimplestTask(int taskIndex) {
#ifdef USE_DEFAULT_FUNCTIONS
    return ((CTaskSimple * (__thiscall *)(CTaskManager*, int))0x681A00)(this, taskIndex);
#else
    CTaskSimple* result = nullptr;
    CTask* pTask = m_aPrimaryTasks[taskIndex];
    while (pTask)
    {
        result = static_cast<CTaskSimple*>(pTask);
        pTask = pTask->GetSubTask();
    }
    return result;
#endif
}

// Converted from thiscall void CTaskManager::AddSubTasks(CTask *task) 0x681A30
void CTaskManager::AddSubTasks(CTaskComplex* pTask) {
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CTaskManager*, CTaskComplex*))0x681A30)(this, pTask);
#else
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
#endif
}

// Converted from thiscall void CTaskManager::ParentsControlChildren(CTask *task) 0x681A80
void CTaskManager::ParentsControlChildren(CTaskComplex* pTask) {
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CTaskManager*, CTaskComplex*))0x681A80)(this, pTask);
#else
    if (pTask)
    {
        while (!pTask->IsSimple())
        {
            CTask* pSubTask = pTask->GetSubTask();
            CTaskComplex* pControlSubTask = static_cast<CTaskComplex*>(pTask->ControlSubTask(m_pPed));
            if (pSubTask != pControlSubTask)
            {
                pSubTask->MakeAbortable(m_pPed, ABORT_PRIORITY_URGENT, 0);
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
#endif
}

// Converted from thiscall void CTaskManager::SetTask(CTask *task,int taskIndex,bool) 0x681AF0
void CTaskManager::SetTask(CTask* pTask, int taskIndex, bool arg2) {
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CTaskManager*, CTask*, int, bool))0x681AF0)(this, pTask, taskIndex, arg2);
#else
    CTask* pPrimaryTask = nullptr;
    if (!pTask)
    {
        pPrimaryTask = m_aPrimaryTasks[taskIndex];
        if (pPrimaryTask)
        {
            pPrimaryTask->DeletingDestructor(1);
            m_aPrimaryTasks[taskIndex] = 0;
            return;
        }
    }

    pPrimaryTask = m_aPrimaryTasks[taskIndex];
    if (pPrimaryTask != pTask)
    {
        if (pPrimaryTask)
        {
            pPrimaryTask->DeletingDestructor(1);
        }
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
                    m_aPrimaryTasks[taskIndex] = 0;
                    return;
                }
                pPrimaryTask->DeletingDestructor(1);
                m_aPrimaryTasks[taskIndex] = 0;
                return;
            }
        }
    }
#endif
}

// Converted from thiscall void CTaskManager::SetTaskSecondary(CTask *task,int taskIndex) 0x681B60
void CTaskManager::SetTaskSecondary(CTask* pTask, int taskIndex) {
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CTaskManager*, CTask*, int))0x681B60)(this, pTask, taskIndex);
#else
    CTask* pCurrentSecondaryTask = m_aSecondaryTasks[taskIndex];
    if (pCurrentSecondaryTask != pTask)
    {
        if (pCurrentSecondaryTask)
        {
            pCurrentSecondaryTask->DeletingDestructor(1);
            pCurrentSecondaryTask = nullptr;
        }
        m_aSecondaryTasks[taskIndex] = pTask;
        AddSubTasks(static_cast<CTaskComplex*>(pTask));
        CTask* pTheTask = m_aSecondaryTasks[taskIndex];
        if (pTheTask)
        {
            CTask* pSimpleTask = nullptr;
            while (pTheTask)
            {
                pSimpleTask = pTheTask;
                pTheTask = pTheTask->GetSubTask();
            }
            if (!pSimpleTask->IsSimple())
            {
                pTheTask = m_aSecondaryTasks[taskIndex];
                if (pTheTask)
                {
                    pTheTask->DeletingDestructor(1);
                }
                m_aSecondaryTasks[taskIndex] = 0;
            }
        }
    }
#endif
}

// Converted from thiscall void CTaskManager::ClearTaskEventResponse(void) 0x681BD0
void CTaskManager::ClearTaskEventResponse() {
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CTaskManager*))0x681BD0)(this);
#else
    CTask* pTask = m_aPrimaryTasks[TASK_PRIMARY_EVENT_RESPONSE_TEMP];
    if (pTask)
    {
        if (pTask)
        {
            pTask = pTask->DeletingDestructor(1);
            m_aPrimaryTasks[TASK_PRIMARY_EVENT_RESPONSE_TEMP] = 0;
        }
    }
    else
    {
        pTask = m_aPrimaryTasks[TASK_PRIMARY_EVENT_RESPONSE_NONTEMP];
        if (pTask)
        {
            pTask = pTask->DeletingDestructor(1);
            m_aPrimaryTasks[TASK_PRIMARY_EVENT_RESPONSE_NONTEMP] = 0;
        }
    }
#endif
}

// Converted from thiscall void CTaskManager::ManageTasks(void) 0x681C10
void CTaskManager::ManageTasks()
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall*)(CTaskManager*))0x681C10)(this);
#else
    int iTaskIndex = 0;

    while (!m_aPrimaryTasks[iTaskIndex])
    {
        iTaskIndex = iTaskIndex + 1;
        if (iTaskIndex >= 5)
        {
            break;
        }
    }

    if (iTaskIndex > -1 && iTaskIndex < 5)
    {
        CTask* pSimplestTask = GetSimplestTask(m_aPrimaryTasks[iTaskIndex]);
        if (!pSimplestTask->IsSimple())
        {
            CTask* pPrimaryTask = m_aPrimaryTasks[iTaskIndex];
            if (pPrimaryTask)
            {
                pPrimaryTask->DeletingDestructor(1);
            }
            m_aPrimaryTasks[iTaskIndex] = 0;
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
                    CTask* pTheTask = m_aPrimaryTasks[iTaskIndex];
                    if (pTheTask)
                    {
                        pTheTask->DeletingDestructor(1);
                    }
                    m_aPrimaryTasks[iTaskIndex] = 0;
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
                    CTask* pTheTask = m_aPrimaryTasks[iTaskIndex];
                    if (pTheTask)
                    {
                        pTheTask->DeletingDestructor(1);
                    }
                    m_aPrimaryTasks[iTaskIndex] = 0;
                    break;
                }
            }
        }
    }

    for (int secondaryTaskIndex = 0; secondaryTaskIndex < 6; secondaryTaskIndex++)
    {
        CTask* pTheSecondaryTask = m_aSecondaryTasks[secondaryTaskIndex];
        if (pTheSecondaryTask)
        {
            bool bProcessPedFailed = false;
            while (1)
            {
                ParentsControlChildren((CTaskComplex*)pTheSecondaryTask);
                CTaskSimple* pSimplestTask = GetSimplestTask(pTheSecondaryTask);
                if (!pSimplestTask->IsSimple())
                {
                    break;
                }

                pSimplestTask = GetSimplestTask(pTheSecondaryTask);
                if (!pSimplestTask->ProcessPed(m_pPed))
                {
                    bProcessPedFailed =  true;
                    break;
                }

                SetNextSubTask((CTaskComplex*)pSimplestTask->m_pParentTask);
                if (!pTheSecondaryTask->GetSubTask())
                {
                    break;
                }
            }

            if (bProcessPedFailed)
            {
                continue;
            }
            pTheSecondaryTask->DeletingDestructor(1);
            m_aSecondaryTasks[secondaryTaskIndex] = 0;
        }
    }

#endif
}