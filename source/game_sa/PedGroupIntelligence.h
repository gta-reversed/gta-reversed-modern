/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <concepts>

#include "PedTaskPair.h"

#include "Tasks/TaskTypes/TaskSimpleNone.h"

class CPed;
class CTask;
class CGroupEventHandler;
class CPedGroupDefaultTaskAllocator;
class CTaskAllocator;
class CEvent;
class CPedGroup;
class CEventGroupEvent;

enum class ePedGroupDefaultTaskAllocatorType : uint32 {
    FOLLOW_ANY_MEANS,
    FOLLOW_LIMITED,
    STAND_STILL,
    CHAT,
    SIT_IN_LEADER_CAR,
    RANDOM,
};

class CPedGroupIntelligence {
public:
    CPedGroup*                     m_pPedGroup;
    CEventGroupEvent*              m_pOldEventGroupEvent;
    CEventGroupEvent*              m_pEventGroupEvent;
    union {
        CPedTaskPair     m_groupTasks[32]; // todo: split array
        struct {
            CPedTaskPair m_pedTaskPairs[8];
            CPedTaskPair m_secondaryPedTaskPairs[8];
            CPedTaskPair m_scriptCommandPedTaskPairs[8];
            CPedTaskPair m_defaultPedTaskPairs[8];
        };
    };
    CPedGroupDefaultTaskAllocator* m_pPedGroupDefaultTaskAllocator;
    CTaskAllocator*                m_pPrimaryTaskAllocator;
    CTaskAllocator*                m_pEventResponseTaskAllocator;
    int32                          m_nDecisionMakerType;
    int32                          m_nTaskSequenceId; // Used in CTaskSequences::ms_taskSequence

public:
    static void InjectHooks();

    CPedGroupIntelligence();
    CPedGroupIntelligence(CPedGroup& owner); // notsa
    ~CPedGroupIntelligence();

    void Flush();

    bool       AddEvent(CEvent* event);
    void       ComputeDefaultTasks(CPed* ped);
    void*      ComputeEventResponseTasks();
    void       ComputeScriptCommandTasks();
    static void       FlushTasks(CPedTaskPair* taskpair, CPed* ped);

    CTask*         GetTask(CPed* ped, CPedTaskPair const* taskPair);
    CTask*         GetTaskMain(CPed* ped);
    CTask*         GetTaskDefault(CPed* ped);
    CTask*         GetTaskScriptCommand(CPed* ped);
    CTask*         GetTaskSecondary(CPed* ped);
    eSecondaryTask GetTaskSecondarySlot(CPed* ped);

    bool       IsCurrentEventValid();
    bool       IsGroupResponding();
    void       Process();
    void       ProcessIgnorePlayerGroup();
    void       ReportAllBarScriptTasksFinished();
    void       ReportAllTasksFinished(CPedTaskPair* taskpair);
    void       ReportAllTasksFinished();
    bool       ReportFinishedTask(const CPed* ped, const CTask* task, CPedTaskPair* taskpair);
    bool       ReportFinishedTask(const CPed* ped, const CTask* task);
    void       SetDefaultTask(CPed* ped, const CTask* task);
    void       SetDefaultTaskAllocator(CPedGroupDefaultTaskAllocator const* PedGroupDefaultTaskAllocator);
    //! see ePedGroupDefaultTaskAllocatorType
    void SetDefaultTaskAllocatorType(ePedGroupDefaultTaskAllocatorType nPedGroupTaskAllocator);

    /*!
    * @addr 0x5F8510
    * @note The tasks passed to this function **shouldn't** be `new`-d, but rather stack allocated! Also, it's often inlined into an unused `CTaskSimpleNone` and `SetTask` call.
    */
    void SetEventResponseTask(
        CPed*        ped,
        bool         hasMainTask,
        const CTask& mainTask,
        bool         hasSecondaryTask = false,
        const CTask& secondaryTask = CTaskSimpleNone{},
        int32        slot = -1
    );
    //! @notsa
    void SetEventResponseTask(CPed* ped, const CTask& task) { SetEventResponseTask(ped, true, task); }
    int32 SetEventResponseTaskAllocator(int32 a2);
    int32 SetGroupDecisionMakerType(int32 a2);
    void  SetPrimaryTaskAllocator(CTaskAllocator* taskAllocator);
    void  SetScriptCommandTask(CPed* ped, const CTask* task);

    /// Helper so events can be directly passed in without having to it into a variable
    template<std::derived_from<CEvent> T>
    auto AddEvent(T event) {
        return AddEvent(&event);
    }

    auto GetPedTaskPairs() { return m_pedTaskPairs; }

    //! `task` shouldn't be `new`-d, but rather stack allocated!
    static void SetTask(CPed* ped, const CTask& task, CPedTaskPair* pair, int32 slot = -1, bool force = false);
};

VALIDATE_SIZE(CPedGroupIntelligence, 0x2A0);
