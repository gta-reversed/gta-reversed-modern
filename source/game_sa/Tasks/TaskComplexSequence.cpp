#include "StdInc.h"

#include "TaskComplexSequence.h"

void CTaskComplexSequence::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexSequence, 0x86e200, 11);
    RH_ScopedCategory("Tasks");

    RH_ScopedInstall(Constructor, 0x632BD0);
    RH_ScopedVMTInstall(Clone, 0x5F6710);
    RH_ScopedVMTInstall(MakeAbortable, 0x632C00);
    RH_ScopedVMTInstall(CreateNextSubTask, 0x638A40);
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x638A60);
    RH_ScopedVMTInstall(ControlSubTask, 0x632D00);
    RH_ScopedOverloadedInstall(CreateNextSubTask, "ped", 0x632C70, CTask*(CTaskComplexSequence::*)(CPed*, int32&, int32&));
    RH_ScopedOverloadedInstall(AddTask, "0", 0x632D10, void(CTaskComplexSequence::*)(CTask*));
    RH_ScopedOverloadedInstall(AddTask, "1", 0x632D50, void(CTaskComplexSequence::*)(int32, CTask*));
    RH_ScopedInstall(Flush, 0x632C10);
    RH_ScopedInstall(Contains, 0x41BF10);
    RH_ScopedInstall(f0x463610, 0x463610);
    RH_ScopedInstall(f0x636BC0, 0x636BC0);
}

// 0x632BD0
CTaskComplexSequence::CTaskComplexSequence() : CTaskComplex() {
    m_nCurrentTaskIndex = 0;
    m_bRepeatSequence = false;
    m_nSequenceRepeatedCount = 0;
    m_bFlushTasks = false;
    m_nReferenceCount = 0;
    std::ranges::fill(m_aTasks, nullptr);
}

// For 0x5F6710
CTaskComplexSequence::CTaskComplexSequence(const CTaskComplexSequence& o) :
    m_bRepeatSequence{o.m_bRepeatSequence},
    m_nCurrentTaskIndex{o.m_nCurrentTaskIndex}
{
    for (auto&& [i, t] : notsa::enumerate(o.m_aTasks)) {
        m_aTasks[i] = t ? t->Clone() : nullptr;
    }
}

// 0x6389F0
CTaskComplexSequence::~CTaskComplexSequence() {
    Flush();
}

// 0x632C10
void CTaskComplexSequence::Flush() {
    for (auto& task : m_aTasks) {
        delete task;
        task = nullptr;
    }

    m_nCurrentTaskIndex = 0;
    m_bRepeatSequence = false;
    m_nSequenceRepeatedCount = 0;
}

CTaskComplexSequence* CTaskComplexSequence::Constructor() {
    this->CTaskComplexSequence::CTaskComplexSequence();
    return this;
}

// 0x632C00
bool CTaskComplexSequence::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return MakeAbortable_Reversed(ped, priority, event);
}

// 0x638A40
CTask* CTaskComplexSequence::CreateNextSubTask(CPed* ped) {
    return CreateNextSubTask_Reversed(ped);
}

// 0x638A60
CTask* CTaskComplexSequence::CreateFirstSubTask(CPed* ped) {
    return CreateFirstSubTask_Reversed(ped);
}

// 0x632D00
CTask* CTaskComplexSequence::ControlSubTask(CPed* ped) {
    return ControlSubTask_Reversed(ped);
}

bool CTaskComplexSequence::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return m_pSubTask->MakeAbortable(ped, priority, event);
}

CTask* CTaskComplexSequence::CreateNextSubTask_Reversed(CPed* ped) {
    return CreateNextSubTask(ped, m_nCurrentTaskIndex, m_nSequenceRepeatedCount);
}

CTask* CTaskComplexSequence::CreateFirstSubTask_Reversed(CPed* ped) {
    CTask* currentTask = m_aTasks[m_nCurrentTaskIndex];
    return currentTask ? currentTask->Clone() : nullptr;
}

CTask* CTaskComplexSequence::ControlSubTask_Reversed(CPed* ped) {
    return m_pSubTask;
}

// 0x632D10
void CTaskComplexSequence::AddTask(CTask* task) {
    for (auto& t : m_aTasks) {
        if (!t) {
            t = task;
            return;
        }
    }

    delete task;
    DEV_LOG("Failed to add task to sequence");
}

// 0x632D50
void CTaskComplexSequence::AddTask(int32 sequenceIdx, CTask* task) {
    if (sequenceIdx >= (int32)std::size(m_aTasks)) {
        delete task;
        DEV_LOG("Failed to add task to sequence");
    } else {
        delete m_aTasks[sequenceIdx];
        m_aTasks[sequenceIdx] = task;
    }
}

// 0x632C70
CTask* CTaskComplexSequence::CreateNextSubTask(CPed* ped, int32& taskIndex, int32& repeatCount) {
    UNUSED(ped);

    CTask* nextSubTask = nullptr;
    int32 incrementedTaskIndex = taskIndex + 1;
    taskIndex = incrementedTaskIndex;

    if (m_bRepeatSequence) {
        if (incrementedTaskIndex == std::size(m_aTasks) || !m_aTasks[incrementedTaskIndex]) {
            taskIndex = 0;
            repeatCount = repeatCount + 1;
        }

        if (m_bRepeatSequence || (bool)repeatCount != m_bRepeatSequence) {
            nextSubTask = m_aTasks[taskIndex]->Clone();
        }
    } else if (incrementedTaskIndex != std::size(m_aTasks)) {
        if (CTask* task = m_aTasks[incrementedTaskIndex]) {
            nextSubTask = task->Clone();
        }
    }
    return nextSubTask;
}

// 0x41BF10
bool CTaskComplexSequence::Contains(eTaskType taskType) {
    for (auto& task : m_aTasks) {
        if (task->GetTaskType() == taskType) {
            return true;
        }
    }
    return false;
}

// 0x463610
void CTaskComplexSequence::f0x463610(bool flush) {
    if (m_nReferenceCount || !flush) {
        m_bFlushTasks = flush;
    } else {
        m_bFlushTasks = false;
        Flush();
    }
}

// 0x636BC0
void CTaskComplexSequence::f0x636BC0() {
    if (m_nReferenceCount-- == 1 && m_bFlushTasks) {
        m_bFlushTasks = false;
        Flush();
    }
}
