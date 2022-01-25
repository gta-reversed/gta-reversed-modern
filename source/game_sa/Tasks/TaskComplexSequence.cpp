#include "StdInc.h"

void CTaskComplexSequence::InjectHooks()
{
    Install("CTaskComplexSequence", "CTaskComplexSequence", 0x632BD0, &CTaskComplexSequence::Constructor);
    Install("CTaskComplexSequence", "Clone", 0x5F6710, &CTaskComplexSequence::Clone_Reversed);
    Install("CTaskComplexSequence", "GetTaskType", 0x632C60, &CTaskComplexSequence::GetId_Reversed);
    Install("CTaskComplexSequence", "MakeAbortable", 0x632C00, &CTaskComplexSequence::MakeAbortable_Reversed);
    Install("CTaskComplexSequence", "CreateNextSubTask", 0x638A40, &CTaskComplexSequence::CreateNextSubTask_Reversed);
    Install("CTaskComplexSequence", "CreateNextSubTask_ped", 0x632C70, static_cast<CTask*(CTaskComplexSequence::*)(CPed*, int32&, int32&)>(&CTaskComplexSequence::CreateNextSubTask));
    Install("CTaskComplexSequence", "CreateFirstSubTask", 0x638A60, &CTaskComplexSequence::CreateFirstSubTask_Reversed);
    Install("CTaskComplexSequence", "ControlSubTask", 0x632D00, &CTaskComplexSequence::ControlSubTask_Reversed);
    Install("CTaskComplexSequence", "AddTask", 0x632D10, &CTaskComplexSequence::AddTask);
    Install("CTaskComplexSequence", "Flush", 0x632C10, &CTaskComplexSequence::Flush);
}

// 0x632BD0
CTaskComplexSequence::CTaskComplexSequence() {
    m_nCurrentTaskIndex = 0;
    m_bRepeatSequence = 0;
    m_nSequenceRepeatedCount = 0;
    m_bFlushTasks = false;
    m_nReferenceCount = 0;
    memset(m_aTasks, 0, sizeof(CTaskComplexSequence::m_aTasks));
}

CTaskComplexSequence::~CTaskComplexSequence() {
    Flush();
}

CTaskComplexSequence* CTaskComplexSequence::Constructor()
{
    this->CTaskComplexSequence::CTaskComplexSequence();
    return this;
}

// 0x5F6710
CTask* CTaskComplexSequence::Clone()
{
    return Clone_Reversed();
}

// 0x632C60
eTaskType CTaskComplexSequence::GetTaskType()
{
    return GetId_Reversed();
}

// 0x632C00
bool CTaskComplexSequence::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event)
{
    return MakeAbortable_Reversed(ped, priority, event);
}

// 0x638A40
CTask* CTaskComplexSequence::CreateNextSubTask(CPed* ped)
{
    return CreateNextSubTask_Reversed(ped);
}

// 0x638A60
CTask* CTaskComplexSequence::CreateFirstSubTask(CPed* ped)
{
    return CreateFirstSubTask_Reversed(ped);
}

// 0x632D00
CTask* CTaskComplexSequence::ControlSubTask(CPed* ped)
{
    return ControlSubTask_Reversed(ped);
}

CTask* CTaskComplexSequence::Clone_Reversed()
{
    auto* clonedComplexSequence = new CTaskComplexSequence();
    for (uint32 taskIndex = 0; taskIndex < 8; taskIndex++) {
        CTask* task = m_aTasks[taskIndex];
        if (task) {
            clonedComplexSequence->m_aTasks[taskIndex] = task->Clone();
        } else {
            clonedComplexSequence->m_aTasks[taskIndex] = nullptr;
        }
    }
    clonedComplexSequence->m_bRepeatSequence = m_bRepeatSequence;
    clonedComplexSequence->m_nCurrentTaskIndex = m_nCurrentTaskIndex;
    return clonedComplexSequence;
}

bool CTaskComplexSequence::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event)
{
    return m_pSubTask->MakeAbortable(ped, priority, event);
}

CTask* CTaskComplexSequence::CreateNextSubTask_Reversed(CPed* ped)
{
    return CreateNextSubTask(ped, m_nCurrentTaskIndex, m_nSequenceRepeatedCount);
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

// 0x632D10
void CTaskComplexSequence::AddTask(CTask* pTask)
{
    for (auto& m_aTask : m_aTasks) {
        if (!m_aTask) {
            m_aTask = pTask;
            return;
        }
    }

    delete pTask;
}

// 0x632C70
CTask* CTaskComplexSequence::CreateNextSubTask(CPed* ped, int32& taskIndex, int32& repeatCount)
{
    CTask* nextSubTask = nullptr;
    int32 incrementedTaskIndex = taskIndex + 1;
    taskIndex = incrementedTaskIndex;

    if (m_bRepeatSequence) {
        if (incrementedTaskIndex == 8 || !m_aTasks[incrementedTaskIndex]) {
            taskIndex = 0;
            repeatCount = repeatCount + 1;
        }

        // Value of bRepeatSequence can be 0 or 1, this means that if we are
        // within this code block, then `pNextSubTask = m_aTasks[*pTaskIndex]->Clone()`
        // will always execute.
        int32 bRepeatSequence = m_bRepeatSequence;
        if (bRepeatSequence == 1 || repeatCount != bRepeatSequence) {
            nextSubTask = m_aTasks[taskIndex]->Clone();
        }
    } else if (incrementedTaskIndex != 8) {
        CTask* task = m_aTasks[incrementedTaskIndex];
        if (task) {
            nextSubTask = task->Clone();
        }
    }
    return nextSubTask;
}

// 0x632C10
void CTaskComplexSequence::Flush()
{
    for (auto& m_aTask : m_aTasks) {
        CTask* pTask = m_aTask;
        delete pTask;
        m_aTask = nullptr;
    }

    m_nCurrentTaskIndex = 0;
    m_bRepeatSequence = 0;
    m_nSequenceRepeatedCount = 0;
}
