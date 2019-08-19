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
}

// Converted from thiscall void CTaskManager::CTaskManager(CPed *ped) 0x6816A0
CTaskManager::CTaskManager(CPed* ped) {
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CTaskManager*, CPed*))0x6816A0)(this, ped);
#else
    m_pPed = ped;
    m_aPrimaryTasks[0] = 0;
    m_aPrimaryTasks[1] = 0;
    m_aPrimaryTasks[2] = 0;
    m_aPrimaryTasks[3] = 0;
    m_aPrimaryTasks[4] = 0;
    memset(m_aSecondaryTasks, 0, sizeof(m_aSecondaryTasks));
#endif
}

// Converted from thiscall void CTaskManager::~CTaskManager() 0x6816D0
CTaskManager::~CTaskManager() {
    ((void(__thiscall *)(CTaskManager*))0x6816D0)(this);
}

// Converted from thiscall CTask* CTaskManager::GetActiveTask(void) 0x681720
CTask* CTaskManager::GetActiveTask() {
    return ((CTask* (__thiscall *)(CTaskManager*))0x681720)(this);
}

// Converted from thiscall CTask* CTaskManager::FindActiveTaskByType(int taskType) 0x681740
CTask* CTaskManager::FindActiveTaskByType(int taskType) {
    return ((CTask* (__thiscall *)(CTaskManager*, int))0x681740)(this, taskType);
}

// Converted from thiscall CTask* CTaskManager::FindTaskByType(int taskIndex,int taskType) 0x6817D0
CTask* CTaskManager::FindTaskByType(int taskIndex, int taskType) {
    return ((CTask* (__thiscall *)(CTaskManager*, int, int))0x6817D0)(this, taskIndex, taskType);
}

// Converted from thiscall CTask* CTaskManager::GetTaskSecondary(int taskIndex) 0x681810
CTask* CTaskManager::GetTaskSecondary(int taskIndex) {
    return ((CTask* (__thiscall *)(CTaskManager*, int))0x681810)(this, taskIndex);
}

// Converted from thiscall bool CTaskManager::HasTaskSecondary(CTask const*task) 0x681820
bool CTaskManager::HasTaskSecondary(CTask const* task) {
    return ((bool(__thiscall *)(CTaskManager*, CTask const*))0x681820)(this, task);
}

// Converted from thiscall void CTaskManager::Flush(void) 0x681850
void CTaskManager::Flush() {
    ((void(__thiscall *)(CTaskManager*))0x681850)(this);
}

// Converted from thiscall void CTaskManager::FlushImmediately(void) 0x6818A0
void CTaskManager::FlushImmediately() {
    ((void(__thiscall *)(CTaskManager*))0x6818A0)(this);
}

// Converted from thiscall void CTaskManager::SetNextSubTask(CTask *task) 0x681920
void CTaskManager::SetNextSubTask(CTask* task) {
    ((void(__thiscall *)(CTaskManager*, CTask*))0x681920)(this, task);
}

// Converted from thiscall CTask* CTaskManager::GetSimplestTask(CTask *task) 0x681970
CTask* CTaskManager::GetSimplestTask(CTask* task) {
    return ((CTask* (__cdecl *)(CTask*))0x681970)(task);
}

// Converted from thiscall void CTaskManager::StopTimers(CEvent const*_event) 0x6819A0
void CTaskManager::StopTimers(CEvent const* _event) {
    ((void(__thiscall *)(CTaskManager*, CEvent const*))0x6819A0)(this, _event);
}

// Converted from thiscall CTask* CTaskManager::GetSimplestActiveTask(void) 0x6819D0
CTask* CTaskManager::GetSimplestActiveTask() {
    return ((CTask* (__thiscall *)(CTaskManager*))0x6819D0)(this);
}

// Converted from thiscall CTask* CTaskManager::GetSimplestTask(int taskIndex) 0x681A00
CTask* CTaskManager::GetSimplestTask(int taskIndex) {
    return ((CTask* (__thiscall *)(CTaskManager*, int))0x681A00)(this, taskIndex);
}

// Converted from thiscall void CTaskManager::AddSubTasks(CTask *task) 0x681A30
void CTaskManager::AddSubTasks(CTask* task) {
    ((void(__thiscall *)(CTaskManager*, CTask*))0x681A30)(this, task);
}

// Converted from thiscall void CTaskManager::ParentsControlChildren(CTask *task) 0x681A80
void CTaskManager::ParentsControlChildren(CTask* task) {
    ((void(__thiscall *)(CTaskManager*, CTask*))0x681A80)(this, task);
}

// Converted from thiscall void CTaskManager::SetTask(CTask *task,int taskIndex,bool) 0x681AF0
void CTaskManager::SetTask(CTask* task, int taskIndex, bool arg2) {
    ((void(__thiscall *)(CTaskManager*, CTask*, int, bool))0x681AF0)(this, task, taskIndex, arg2);
}

// Converted from thiscall void CTaskManager::SetTaskSecondary(CTask *task,int taskIndex) 0x681B60
void CTaskManager::SetTaskSecondary(CTask* task, int taskIndex) {
    ((void(__thiscall *)(CTaskManager*, CTask*, int))0x681B60)(this, task, taskIndex);
}

// Converted from thiscall void CTaskManager::ClearTaskEventResponse(void) 0x681BD0
void CTaskManager::ClearTaskEventResponse() {
    ((void(__thiscall *)(CTaskManager*))0x681BD0)(this);
}

// Converted from thiscall void CTaskManager::ManageTasks(void) 0x681C10
void CTaskManager::ManageTasks()
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall*)(CTaskManager*))0x681C10)(this);
#else
    int iTaskIndex = 0;

    while (!pThis->m_aPrimaryTasks[iTaskIndex])
    {
        iTaskIndex = iTaskIndex + 1;
        if (iTaskIndex >= 5)
        {
            goto PROCESS_SECONDARY_TASKS;
        }
    }

    if (iTaskIndex > -1)
    {
        CTask* pTask = pThis->m_aPrimaryTasks[iTaskIndex];
        CTask* i = nullptr;
        for (i = 0; pTask; pTask = pTask->GetSubTask())
        {
            i = pTask;
        }

        if (!i->IsSimple())
        {
            CTask* pPrimaryTask = pThis->m_aPrimaryTasks[iTaskIndex];
            if (pPrimaryTask)
            {
                pPrimaryTask->DeletingDestructor(1);
            }
            pThis->m_aPrimaryTasks[iTaskIndex] = 0;
            return;
        }
        int loopCounter = 0;
        while (1)
        {
            pThis->ParentsControlChildren(pThis->m_aPrimaryTasks[iTaskIndex]);
            CTask* pTask2 = (CTask*)pThis->m_aPrimaryTasks[iTaskIndex];
            CTask* j = nullptr;
            for (j = 0; pTask2; pTask2 = pTask2->GetSubTask())
            {
                j = pTask2;
            }
            if (!j->IsSimple())
            {
                pThis->SetNextSubTask(j->m_pParentTask);
                CTask* pTask3 = pThis->m_aPrimaryTasks[iTaskIndex];
                CTask* k = nullptr;
                for (k = 0; pTask3; pTask3 = pTask3->GetSubTask())
                {
                    k = pTask3;
                }
                if (!k->IsSimple())
                {
                    break;
                }
            }
            CTask* v13 = pThis->m_aPrimaryTasks[iTaskIndex];
            CTaskSimple* pSimpleTask = nullptr;
            for (pSimpleTask = 0; v13; v13 = v13->GetSubTask())
            {
                pSimpleTask = static_cast<CTaskSimple*>(v13);
            }
            if (!pSimpleTask->ProcessPed(pThis->m_pPed))
            {
                goto PROCESS_SECONDARY_TASKS;
            }
            pThis->SetNextSubTask(pSimpleTask->m_pParentTask);
            if (!pThis->m_aPrimaryTasks[iTaskIndex]->GetSubTask())
            {
                CTask* pTheTask = pThis->m_aPrimaryTasks[iTaskIndex];
                if (pTheTask)
                {
                    pTheTask->DeletingDestructor(1);
                }
                goto LABEL_32;
            }

            loopCounter++;
            if (loopCounter > 10)
            {
                goto PROCESS_SECONDARY_TASKS;
            }
        }

        CTask* pTheTask = pThis->m_aPrimaryTasks[iTaskIndex];
        if (pTheTask)
        {
            pTheTask->DeletingDestructor(1);
        }
    LABEL_32:
        pThis->m_aPrimaryTasks[iTaskIndex] = 0;
    }

PROCESS_SECONDARY_TASKS:
    // process secondary tasks
    CTask** pSecondaryTasks = (CTask * *)pThis->m_aSecondaryTasks;
    int totalSecondaryTasks = 6;
    do
    {
        CTask* pTheSecondaryTask = *pSecondaryTasks;
        if (*pSecondaryTasks)
        {
            while (1)
            {
                pThis->ParentsControlChildren(pTheSecondaryTask);
                CTask* pTheSecondaryTask3 = nullptr;
                CTask* pTheSecondaryTask2 = pTheSecondaryTask;
                do
                {
                    pTheSecondaryTask3 = pTheSecondaryTask2;
                    pTheSecondaryTask2 = (CTask*)pTheSecondaryTask2->GetSubTask();
                } while (pTheSecondaryTask2);

                if (!pTheSecondaryTask3->IsSimple())
                {
                    break;
                }
                CTaskSimple* pTheSecondaryTask5 = nullptr;
                CTask* pTheSecondaryTask4 = pTheSecondaryTask;
                do
                {
                    pTheSecondaryTask5 = static_cast<CTaskSimple*>(pTheSecondaryTask4);
                    pTheSecondaryTask4 = (CTask*)pTheSecondaryTask4->GetSubTask();
                } while (pTheSecondaryTask4);


                if (!pTheSecondaryTask5->ProcessPed(pThis->m_pPed))
                {
                    goto LABEL_44;
                }
                pThis->SetNextSubTask(pTheSecondaryTask5->m_pParentTask);
                if (!pTheSecondaryTask->GetSubTask())
                {
                    pTheSecondaryTask->DeletingDestructor(1);
                    goto LABEL_43;
                }
            }
            pTheSecondaryTask->DeletingDestructor(1);
        LABEL_43:
            *pSecondaryTasks = 0;
        }
    LABEL_44:
        ++pSecondaryTasks;
        totalSecondaryTasks--;
    } while (totalSecondaryTasks);

#endif
}
