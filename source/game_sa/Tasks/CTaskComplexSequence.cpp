#include "StdInc.h"

CTask* CTaskComplexSequence::Clone()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTask*, 0x5F6710, CTask*>(this);
#else
    auto pClonedComplexSequence = (CTaskComplexSequence*)CTask::operator new(0x40);
    if (pClonedComplexSequence)
    {
        pClonedComplexSequence->Constructor();

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
#endif
}

eTaskType CTaskComplexSequence::GetId()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <eTaskType, 0x632C60, CTask*>(this);
#else
    return TASK_COMPLEX_SEQUENCE;
#endif
}

bool CTaskComplexSequence::MakeAbortable(class CPed* ped, eAbortPriority priority, class CEvent* _event)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <bool, 0x632C00, CTask*, class CPed*, eAbortPriority, class CEvent*>(this, ped, priority, _event);
#else
    return m_pSubTask->MakeAbortable(ped, priority, _event);
#endif
}

CTask* CTaskComplexSequence::CreateNextSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <CTask*, 0x638A40, CTask*, CPed*>(this, ped);
#else
    return CreateNextSubTask(ped, &m_nCurrentTaskIndex, &m_nSequenceRepeatedCount);
#endif
}

CTask* CTaskComplexSequence::CreateFirstSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <CTask*, 0x638A60, CTask*, CPed*>(this, ped);
#else
    CTask* pCurrentTask = m_aTasks[m_nCurrentTaskIndex];
    if (pCurrentTask)
    {
        return pCurrentTask->Clone();
    }
    return nullptr;
#endif
}

CTask* CTaskComplexSequence::ControlSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <CTask*, 0x632D00, CTask*, CPed*>(this, ped);
#else
    return m_pSubTask;
#endif
}

CTaskComplexSequence* CTaskComplexSequence::Constructor()
{
    return plugin::CallMethodAndReturn<CTaskComplexSequence*, 0x632BD0, CTaskComplexSequence*>(this);
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
        pTask->DeletingDestructor(1);
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
    plugin::CallMethod<0x632C10, CTask*>(this);
}