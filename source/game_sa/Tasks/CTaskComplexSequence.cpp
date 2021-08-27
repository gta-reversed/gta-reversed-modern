#include "StdInc.h"

void CTaskComplexSequence::InjectHooks()
{
    HookInstall(0x632BD0, &CTaskComplexSequence::Constructor);
    HookInstall(0x5F6710, &CTaskComplexSequence::Clone_Reversed);
    HookInstall(0x632C60, &CTaskComplexSequence::GetId_Reversed);
    HookInstall(0x632C00, &CTaskComplexSequence::MakeAbortable_Reversed);
    HookInstall(0x638A40, &CTaskComplexSequence::CreateNextSubTask_Reversed);
    HookInstall(0x638A60, &CTaskComplexSequence::CreateFirstSubTask_Reversed);
    HookInstall(0x632D00, &CTaskComplexSequence::ControlSubTask_Reversed);
    HookInstall(0x632D10, &CTaskComplexSequence::AddTask);
    HookInstall(0x632C70, (CTask*(CTaskComplexSequence::*)(CPed*, int*, int*))&CTaskComplexSequence::CreateNextSubTask);
    HookInstall(0x632C10, &CTaskComplexSequence::Flush);
}

CTaskComplexSequence::CTaskComplexSequence() {
    m_nCurrentTaskIndex = 0;
    m_bRepeatSequence = 0;
    m_nSequenceRepeatedCount = 0;
    m_bFlushTasks = 0;
    m_nReferenceCount = 0;
    memset(m_aTasks, 0, sizeof(CTaskComplexSequence::m_aTasks));
}

CTaskComplexSequence::~CTaskComplexSequence() {
    Flush();
}

CTaskComplexSequence* CTaskComplexSequence::Constructor()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskComplexSequence*, 0x632BD0, CTaskComplexSequence*>(this);
#else
    this->CTaskComplexSequence::CTaskComplexSequence();
    return this;
#endif
}

CTask* CTaskComplexSequence::Clone()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTask*, 0x5F6710, CTask*>(this);
#else
    return Clone_Reversed();
#endif
}

eTaskType CTaskComplexSequence::GetId()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <eTaskType, 0x632C60, CTask*>(this);
#else
    return GetId_Reversed();
#endif
}

// 0x632C00
bool CTaskComplexSequence::MakeAbortable(class CPed* ped, eAbortPriority priority, const CEvent* event)
{
    return MakeAbortable_Reversed(ped, priority, event);
}

CTask* CTaskComplexSequence::CreateNextSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <CTask*, 0x638A40, CTask*, CPed*>(this, ped);
#else
    return CreateNextSubTask_Reversed(ped);
#endif
}

CTask* CTaskComplexSequence::CreateFirstSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <CTask*, 0x638A60, CTask*, CPed*>(this, ped);
#else
    return CreateFirstSubTask_Reversed(ped);
#endif
}

CTask* CTaskComplexSequence::ControlSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <CTask*, 0x632D00, CTask*, CPed*>(this, ped);
#else
    return ControlSubTask_Reversed(ped);
#endif
}

CTask* CTaskComplexSequence::Clone_Reversed()
{
    auto pClonedComplexSequence = new CTaskComplexSequence();
    if (pClonedComplexSequence) {
        for (unsigned int taskIndex = 0; taskIndex < 8; taskIndex++)
        {
            CTask* pTask = m_aTasks[taskIndex];
            if (pTask)
            {
                pClonedComplexSequence->m_aTasks[taskIndex] = pTask->Clone();
            }
            else
            {
                pClonedComplexSequence->m_aTasks[taskIndex] = 0;
            }
        }

        pClonedComplexSequence->m_bRepeatSequence = m_bRepeatSequence;
        pClonedComplexSequence->m_nCurrentTaskIndex = m_nCurrentTaskIndex;
    }
    return pClonedComplexSequence;
}

bool CTaskComplexSequence::MakeAbortable_Reversed(class CPed* ped, eAbortPriority priority, const CEvent* event)
{
    return m_pSubTask->MakeAbortable(ped, priority, event);
}

CTask* CTaskComplexSequence::CreateNextSubTask_Reversed(CPed* ped)
{
    return CreateNextSubTask(ped, &m_nCurrentTaskIndex, &m_nSequenceRepeatedCount);
}

CTask* CTaskComplexSequence::CreateFirstSubTask_Reversed(CPed* ped)
{
    CTask* pCurrentTask = m_aTasks[m_nCurrentTaskIndex];
    if (pCurrentTask)
    {
        return pCurrentTask->Clone();
    }
    return nullptr;
}

CTask* CTaskComplexSequence::ControlSubTask_Reversed(CPed* ped)
{
    return m_pSubTask;
}

void CTaskComplexSequence::AddTask(CTask* pTask)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x632D10, CTaskComplexSequence*, CTask*>(this, pTask);
#else
    for (unsigned int taskIndex = 0; taskIndex < 8; taskIndex++)
    {
        if (!m_aTasks[taskIndex])
        {
            m_aTasks[taskIndex] = pTask;
            return;
        }
    }

    if (pTask)
    {
        delete pTask;
    }
#endif
}

CTask* CTaskComplexSequence::CreateNextSubTask(CPed* pPed, int* pTaskIndex, int* pRepeatCount)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTask*, 0x632C70, CTask*, CPed*, int*, int*>(this, pPed, pTaskIndex, pRepeatCount);
#else
    CTask* pNextSubTask = nullptr;
    int incrementedTaskIndex = *pTaskIndex + 1;
    *pTaskIndex = incrementedTaskIndex;

    if (m_bRepeatSequence)
    {
        if (incrementedTaskIndex == 8 || !m_aTasks[incrementedTaskIndex])
        {
            *pTaskIndex = 0;
            *pRepeatCount = *pRepeatCount + 1;
        }

        // Value of bRepeatSequence can be 0 or 1, this means that if we are 
        // within this code block, then `pNextSubTask = m_aTasks[*pTaskIndex]->Clone()` 
        // will always execute.
        int bRepeatSequence = m_bRepeatSequence;
        if (bRepeatSequence == 1 || *pRepeatCount != bRepeatSequence)
        {
            pNextSubTask = m_aTasks[*pTaskIndex]->Clone();
        }
    }
    else if (incrementedTaskIndex != 8)
    {
        CTask* pTask = m_aTasks[incrementedTaskIndex];
        if (pTask)
        {
            pNextSubTask = pTask->Clone();
        }
    }
    return pNextSubTask;
#endif
}

void CTaskComplexSequence::Flush()
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x632C10, CTask*>(this);
#else
    for (unsigned int taskIndex = 0; taskIndex < 8; taskIndex++)
    {
        CTask* pTask = m_aTasks[taskIndex];
        if (pTask)
        {
            delete pTask;
        }

        m_aTasks[taskIndex] = 0;
    }

    m_nCurrentTaskIndex = 0;
    m_bRepeatSequence = 0;
    m_nSequenceRepeatedCount = 0;
#endif
}
