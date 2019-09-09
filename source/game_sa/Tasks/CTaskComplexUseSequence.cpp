#include "StdInc.h"

CTask* CTaskComplexUseSequence::Clone()
{
//#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTask*, 0x637100, CTask*>(this);
//#else
    /*
    // NOT TESTED. Somebody should find a way to test this.
    auto pClonedComplexUseSequence = (CTaskComplexUseSequence*)CTask::operator new(28);
    if (pClonedComplexUseSequence)
    {
        pClonedComplexUseSequence->CTaskComplex::Constructor();
        pClonedComplexUseSequence->m_nSequenceIndex = m_nSequenceIndex;
        *(unsigned int*)pClonedComplexUseSequence = 0x86e518; //`vtable for'CTaskComplexUseSequence
        pClonedComplexUseSequence->m_nCurrentTaskIndex = 0;
        pClonedComplexUseSequence->m_nEndTaskIndex = -1;
        pClonedComplexUseSequence->m_nSequenceRepeatedCount = 0;

        ++CTaskSequences::ms_taskSequence[m_nSequenceIndex].m_nReferenceCount;

        pClonedComplexUseSequence->m_nCurrentTaskIndex = m_nCurrentTaskIndex;
        pClonedComplexUseSequence->m_nEndTaskIndex = m_nEndTaskIndex;
    }
    return pClonedComplexUseSequence;
    */
//#endif
}

eTaskType CTaskComplexUseSequence::GetId()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <eTaskType, 0x635490, CTask*>(this);
#else
    return TASK_COMPLEX_USE_SEQUENCE;
#endif
}

bool CTaskComplexUseSequence::MakeAbortable(class CPed* ped, eAbortPriority priority, class CEvent* _event)
{
//#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <bool, 0x639730, CTask*, class CPed*, eAbortPriority, class CEvent*>(this, ped, priority, _event);
/*
    // NOT TESTED. Somebody should find a way to test this.
    bool bMakeAbortable = m_pSubTask->MakeAbortable(ped, priority, _event);
    if (bMakeAbortable && _event && _event->GetEventType() == EVENT_DAMAGE)
    {
        CEventDamage* pEventDamage = (CEventDamage*)_event;
        if (pEventDamage->damageResponseData.bUnk && pEventDamage->unkC)
        {
            CTaskComplexSequence* pTaskComplexSequence = &CTaskSequences::ms_taskSequence[m_nSequenceIndex];
            bool bFinalReference = pTaskComplexSequence->m_nReferenceCount == 1;
            pTaskComplexSequence->m_nReferenceCount--;
            if (bFinalReference && pTaskComplexSequence->m_bFlushTasks)
            {
                pTaskComplexSequence->m_bFlushTasks = 0;
                pTaskComplexSequence->Flush();
            }
            m_nSequenceIndex = -1;
        }
    }
    return bMakeAbortable;
*/
//#endif
}

CTask* CTaskComplexUseSequence::CreateNextSubTask(CPed* ped)
{
//#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <CTask*, 0x6354A0, CTask*, CPed*>(this, ped);
    /*
    // NOT TESTED. Somebody should find a way to test this.
    if (m_nSequenceIndex == -1)
    {
        return nullptr;
    }
    else
    {
        auto pTaskComplexSequence = &CTaskSequences::ms_taskSequence[m_nSequenceIndex];
        return pTaskComplexSequence->CreateNextSubTask(ped, &m_nCurrentTaskIndex, &m_nSequenceRepeatedCount);
    }
    */
//#endif
}

CTask* CTaskComplexUseSequence::CreateFirstSubTask(CPed* ped)
{
//#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <CTask*, 0x6354D0, CTask*, CPed*>(this, ped);
    /*
    // NOT TESTED. Somebody should find a way to test this.
    if (m_nSequenceIndex == -1)
    {
        return nullptr;
    }

    CTask* pFirstSubTask = nullptr;
    CTask* pCurrentSequenceTask = CTaskSequences::ms_taskSequence[m_nSequenceIndex].m_aTasks[m_nCurrentTaskIndex];
    if (pCurrentSequenceTask)
    {
        pFirstSubTask = pCurrentSequenceTask->Clone();
    }

    if (m_nEndTaskIndex != -1)
    {
        if (pFirstSubTask && pFirstSubTask->GetId() == TASK_COMPLEX_USE_SEQUENCE)
        {
            auto pTaskComplexUseSequence = (CTaskComplexUseSequence*)pFirstSubTask;
            pTaskComplexUseSequence->m_nCurrentTaskIndex = m_nEndTaskIndex;
            pTaskComplexUseSequence->m_nEndTaskIndex = -1;
        }
    }
    return pFirstSubTask;
    */
//#endif
}

CTask* CTaskComplexUseSequence::ControlSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <CTask*, 0x635530, CTask*, CPed*>(this, ped);
#else
    return m_pSubTask;
#endif
}

CTaskComplexUseSequence* CTaskComplexUseSequence::Constructor(int sequenceIndex)
{
//#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskComplexUseSequence*, 0x635450, CTaskComplexUseSequence*, int>(this, sequenceIndex);

   /*
    // NOT TESTED. Somebody should find a way to test this.
    CTaskComplex::Constructor();
    m_nSequenceIndex = sequenceIndex;
    m_nCurrentTaskIndex = 0;
    m_nSequenceRepeatedCount = 0;
    *(unsigned int*)this = 0x86e518; // `vtable for'CTaskComplexUseSequence;
    m_nEndTaskIndex = -1;
    CTaskSequences::ms_taskSequence[m_nSequenceIndex].m_nReferenceCount++;
    */
//#endif
}

CTaskComplexUseSequence* CTaskComplexUseSequence::Destructor()
{
//#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskComplexUseSequence*, 0x6396C0, CTaskComplexUseSequence*>(this);
    /*
    // NOT TESTED. Somebody should find a way to test this.
    *(unsigned int*)this = 0x86e518; // `vtable for'CTaskComplexUseSequence;

    if (m_nSequenceIndex != -1)
    {
        auto pComplexSequence = &CTaskSequences::ms_taskSequence[m_nSequenceIndex];
        bool bFinalReference = pComplexSequence->m_nReferenceCount == 1;
        pComplexSequence->m_nReferenceCount--;
        if (bFinalReference)
        {
            if (pComplexSequence->m_bFlushTasks)
            {
                pComplexSequence->m_bFlushTasks = 0;
                pComplexSequence->Flush();
            }
        }
    }
    return (CTaskComplexUseSequence*)CTaskComplex::Destructor();
    */
//#endif
}