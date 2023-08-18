#pragma once

#include "TaskComplex.h"

class CTask;

class NOTSA_EXPORT_VTABLE CTaskComplexSequence : public CTaskComplex {
public:
    int32    m_nCurrentTaskIndex{};      //!< Used in m_aTasks
    CTask*   m_aTasks[8]{};              //!< The sequenced tasks
    bool     m_bRepeatSequence{};        //!< Sequence will loop if set to 1
    int32    m_nSequenceRepeatedCount{}; //!< m_nSequenceRepeatedCount simply tells us how many times the sequence has been repeated.
                                         //!< If m_bRepeatSequence is true, this can be greater than 1,
                                         //!< otherwise it's set to 1 when the sequence is done executing tasks.
    bool     m_bFlushTasks{};
    uint32   m_nReferenceCount{};        //!< count of how many CTaskComplexUseSequence instances are using this sequence

public:
    static constexpr auto Type = TASK_COMPLEX_SEQUENCE;

    //! Constructor
    CTaskComplexSequence();

    //! Construct using multiple tasks, same as constructing and then calling `AddTask` for every task passed in.
    template<Task... T>
    CTaskComplexSequence(T*... tasks) :
        CTaskComplexSequence{}
    {
        (AddTask(tasks), ...);
    }

    CTaskComplexSequence(const CTaskComplexSequence&);
    ~CTaskComplexSequence() override;

    eTaskType GetTaskType() const override { return Type; } // 0x632C60
    CTask* Clone() const override { return new CTaskComplexSequence{*this}; } // 0x5F6710
    bool MakeAbortable(class CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    void AddTask(CTask* task);
    void AddTask(int32 id, CTask* task);
    CTask* CreateNextSubTask(CPed* ped, int32& taskIndex, int32& repeatCount);
    void Flush();
    bool Contains(eTaskType taskType);
    void f0x463610(bool flush);
    void f0x636BC0();

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskComplexSequence* Constructor();

    bool MakeAbortable_Reversed(class CPed* ped, eAbortPriority priority, const CEvent* event);
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);
};
VALIDATE_SIZE(CTaskComplexSequence, 0x40);
