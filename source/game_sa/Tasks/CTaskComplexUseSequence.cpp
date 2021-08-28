#include "StdInc.h"

void CTaskComplexUseSequence::InjectHooks()
{
    HookInstall(0x635450, &CTaskComplexUseSequence::Constructor);
    HookInstall(0x637100, &CTaskComplexUseSequence::Clone_Reversed);
    HookInstall(0x635490, &CTaskComplexUseSequence::GetId_Reversed);
    HookInstall(0x639730, &CTaskComplexUseSequence::MakeAbortable_Reversed);
    HookInstall(0x6354A0, &CTaskComplexUseSequence::CreateNextSubTask_Reversed);
    HookInstall(0x6354D0, &CTaskComplexUseSequence::CreateFirstSubTask_Reversed);
    HookInstall(0x635530, &CTaskComplexUseSequence::ControlSubTask_Reversed);
}

CTaskComplexUseSequence::CTaskComplexUseSequence(int sequenceIndex) {
    m_nSequenceIndex = sequenceIndex;
    m_nCurrentTaskIndex = 0;
    m_nSequenceRepeatedCount = 0;
    m_nEndTaskIndex = -1;
    CTaskSequences::ms_taskSequence[m_nSequenceIndex].m_nReferenceCount++;
}

CTaskComplexUseSequence::~CTaskComplexUseSequence()
{
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
}

CTaskComplexUseSequence* CTaskComplexUseSequence::Constructor(int sequenceIndex)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskComplexUseSequence*, 0x635450, CTaskComplexUseSequence*, int>(this, sequenceIndex);
#else
    this->CTaskComplexUseSequence::CTaskComplexUseSequence(sequenceIndex);
    return this;
#endif
}

CTask* CTaskComplexUseSequence::Clone()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTask*, 0x637100, CTask*>(this);
#else
    return Clone_Reversed();
#endif
}

eTaskType CTaskComplexUseSequence::GetId()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <eTaskType, 0x635490, CTask*>(this);
#else
    return GetId_Reversed();
#endif
}

// 0x639730
bool CTaskComplexUseSequence::MakeAbortable(class CPed* ped, eAbortPriority priority, const CEvent* event)
{
    return MakeAbortable_Reversed(ped, priority, event);
}

CTask* CTaskComplexUseSequence::CreateNextSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <CTask*, 0x6354A0, CTask*, CPed*>(this, ped);
#else
    return CreateNextSubTask_Reversed(ped);
#endif
}

CTask* CTaskComplexUseSequence::CreateFirstSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <CTask*, 0x6354D0, CTask*, CPed*>(this, ped);
#else
    return CreateFirstSubTask_Reversed(ped);
#endif
}

CTask* CTaskComplexUseSequence::ControlSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn <CTask*, 0x635530, CTask*, CPed*>(this, ped);
#else
    return ControlSubTask_Reversed(ped);
#endif
}

CTask* CTaskComplexUseSequence::Clone_Reversed()
{
    auto pClonedComplexUseSequence = new CTaskComplexUseSequence;
    if (pClonedComplexUseSequence)
    {
        pClonedComplexUseSequence->m_nSequenceIndex = m_nSequenceIndex;
        pClonedComplexUseSequence->m_nCurrentTaskIndex = 0;
        pClonedComplexUseSequence->m_nEndTaskIndex = -1;
        pClonedComplexUseSequence->m_nSequenceRepeatedCount = 0;

        ++CTaskSequences::ms_taskSequence[m_nSequenceIndex].m_nReferenceCount;

        pClonedComplexUseSequence->m_nCurrentTaskIndex = m_nCurrentTaskIndex;
        pClonedComplexUseSequence->m_nEndTaskIndex = m_nEndTaskIndex;
    }
    return pClonedComplexUseSequence;
}

bool CTaskComplexUseSequence::MakeAbortable_Reversed(class CPed* ped, eAbortPriority priority, const CEvent* event)
{
    bool bMakeAbortable = m_pSubTask->MakeAbortable(ped, priority, event);
    if (bMakeAbortable && event && event->GetEventType() == EVENT_DAMAGE)
    {
        CEventDamage* pEventDamage = (CEventDamage*)event;
        if (pEventDamage->m_damageResponse.m_bHealthZero && pEventDamage->m_bAddToEventGroup)
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
}

CTask* CTaskComplexUseSequence::CreateNextSubTask_Reversed(CPed* ped)
{
    if (m_nSequenceIndex == -1)
    {
        return nullptr;
    }
    else
    {
        auto pTaskComplexSequence = &CTaskSequences::ms_taskSequence[m_nSequenceIndex];
        return pTaskComplexSequence->CreateNextSubTask(ped, &m_nCurrentTaskIndex, &m_nSequenceRepeatedCount);
    }
    return nullptr;
}

CTask* CTaskComplexUseSequence::CreateFirstSubTask_Reversed(CPed* ped)
{
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
}

CTask* CTaskComplexUseSequence::ControlSubTask_Reversed(CPed* ped)
{
    return m_pSubTask;
}
