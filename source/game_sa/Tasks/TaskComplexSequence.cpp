#include "StdInc.h"

void CTaskComplexSequence::InjectHooks()
{
    RH_ScopedClass(CTaskComplexSequence);
    RH_ScopedCategory("Tasks");

    RH_ScopedInstall(Constructor, 0x632BD0);
    RH_ScopedVirtualInstall(Clone, 0x5F6710);
    RH_ScopedVirtualInstall(GetId, 0x632C60);
    RH_ScopedVirtualInstall(MakeAbortable, 0x632C00);
    RH_ScopedVirtualInstall(CreateNextSubTask, 0x638A40);
    RH_ScopedOverloadedInstall(CreateNextSubTask, "ped", 0x632C70, CTask*(CTaskComplexSequence::*)(CPed*, int32&, int32&));
    RH_ScopedVirtualInstall(CreateFirstSubTask, 0x638A60);
    RH_ScopedVirtualInstall(ControlSubTask, 0x632D00);
    RH_ScopedInstall(AddTask, 0x632D10);
    RH_ScopedInstall(Flush, 0x632C10);
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
    CTask* currentTask = m_aTasks[m_nCurrentTaskIndex];
    return currentTask ? currentTask->Clone() : nullptr;
}

CTask* CTaskComplexSequence::ControlSubTask_Reversed(CPed* ped)
{
    return m_pSubTask;
}

// 0x632D10
void CTaskComplexSequence::AddTask(CTask* task)
{
    for (auto& m_aTask : m_aTasks) {
        if (!m_aTask) {
            m_aTask = task;
            return;
        }
    }

    delete task;
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
        CTask* task = m_aTask;
        delete task;
        m_aTask = nullptr;
    }

    m_nCurrentTaskIndex = 0;
    m_bRepeatSequence = 0;
    m_nSequenceRepeatedCount = 0;
}
