#include "StdInc.h"

#include "TaskComplexUseSequence.h"

void CTaskComplexUseSequence::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexUseSequence, 0x86e518, 11);
    RH_ScopedCategory("Tasks");

    RH_ScopedInstall(Constructor, 0x635450);
    RH_ScopedVMTInstall(Clone, 0x637100);
    RH_ScopedVMTInstall(MakeAbortable, 0x639730);
    RH_ScopedVMTInstall(CreateNextSubTask, 0x6354A0);
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x6354D0);
    RH_ScopedVMTInstall(ControlSubTask, 0x635530);
}

// 0x635450
CTaskComplexUseSequence::CTaskComplexUseSequence(int32 sequenceIndex) :
    m_nSequenceIndex{sequenceIndex}
{
    CTaskSequences::ms_taskSequence[m_nSequenceIndex].m_nReferenceCount++;
}

CTaskComplexUseSequence::CTaskComplexUseSequence(const CTaskComplexUseSequence& o) :
    CTaskComplexUseSequence{o.m_nCurrentTaskIndex}
{
    m_nCurrentTaskIndex = o.m_nCurrentTaskIndex;
    m_nEndTaskIndex     = o.m_nEndTaskIndex;
}

CTaskComplexUseSequence::~CTaskComplexUseSequence() {
    if (m_nSequenceIndex != -1) {
        auto complexSequence = &CTaskSequences::ms_taskSequence[m_nSequenceIndex];
        bool bFinalReference = complexSequence->m_nReferenceCount == 1;
        complexSequence->m_nReferenceCount--;
        if (bFinalReference && complexSequence->m_bFlushTasks) {
            complexSequence->m_bFlushTasks = false;
            complexSequence->Flush();
        }
    }
}

CTaskComplexUseSequence* CTaskComplexUseSequence::Constructor(int32 sequenceIndex) {
    this->CTaskComplexUseSequence::CTaskComplexUseSequence(sequenceIndex);
    return this;
}

// 0x639730
bool CTaskComplexUseSequence::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return MakeAbortable_Reversed(ped, priority, event);
}

// 0x6354A0
CTask* CTaskComplexUseSequence::CreateNextSubTask(CPed* ped) {
    return CreateNextSubTask_Reversed(ped);
}

// 0x6354D0
CTask* CTaskComplexUseSequence::CreateFirstSubTask(CPed* ped) {
    return CreateFirstSubTask_Reversed(ped);
}

// 0x635530
CTask* CTaskComplexUseSequence::ControlSubTask(CPed* ped) {
    return ControlSubTask_Reversed(ped);
}

bool CTaskComplexUseSequence::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event) {
    bool bMakeAbortable = m_pSubTask->MakeAbortable(ped, priority, event);
    if (bMakeAbortable && event && event->GetEventType() == EVENT_DAMAGE) {
        auto* eventDamage = (CEventDamage*)event;
        if (eventDamage->m_damageResponse.m_bHealthZero && eventDamage->m_bAddToEventGroup) {
            CTaskComplexSequence* sequence = &CTaskSequences::ms_taskSequence[m_nSequenceIndex];
            bool bFinalReference = sequence->m_nReferenceCount == 1;
            sequence->m_nReferenceCount--;
            if (bFinalReference && sequence->m_bFlushTasks) {
                sequence->m_bFlushTasks = false;
                sequence->Flush();
            }
            m_nSequenceIndex = -1;
        }
    }
    return bMakeAbortable;
}

CTask* CTaskComplexUseSequence::CreateNextSubTask_Reversed(CPed* ped) {
    if (m_nSequenceIndex == -1) {
        return nullptr;
    } else {
        auto taskComplexSequence = &CTaskSequences::ms_taskSequence[m_nSequenceIndex];
        return taskComplexSequence->CreateNextSubTask(ped, m_nCurrentTaskIndex, m_nSequenceRepeatedCount);
    }
}

CTask* CTaskComplexUseSequence::CreateFirstSubTask_Reversed(CPed* ped) {
    if (m_nSequenceIndex == -1) {
        return nullptr;
    }

    CTask* firstSubTask = nullptr;
    CTask* currentSequenceTask = CTaskSequences::ms_taskSequence[m_nSequenceIndex].m_aTasks[m_nCurrentTaskIndex];
    if (currentSequenceTask) {
        firstSubTask = currentSequenceTask->Clone();
    }

    if (m_nEndTaskIndex != -1) {
        if (firstSubTask && firstSubTask->GetTaskType() == TASK_COMPLEX_USE_SEQUENCE) {
            auto sequence = reinterpret_cast<CTaskComplexUseSequence*>(firstSubTask);
            sequence->m_nCurrentTaskIndex = m_nEndTaskIndex;
            sequence->m_nEndTaskIndex = -1;
        }
    }
    return firstSubTask;
}

CTask* CTaskComplexUseSequence::ControlSubTask_Reversed(CPed* ped) {
    return m_pSubTask;
}
