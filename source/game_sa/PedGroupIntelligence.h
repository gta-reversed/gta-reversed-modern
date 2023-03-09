/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <concepts>

#include "PedTaskPair.h"

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
    CPedTaskPair                   m_groupTasks[32]; // todo: split array
    /* TODO: Split above to below:
    * CPedTaskPair m_pedTaskPairs[8];
    * CPedTaskPair m_secondaryPedTaskPairs[8];
    * CPedTaskPair m_scriptCommandPedTaskPairs[8];
    * CPedTaskPair m_defaultPedTaskPairs[8];
    */
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
    //! arg3 always true
    //! arg5 always false
    //! arg7 always  -1
    void  SetEventResponseTask(CPed* ped, bool arg3, const CTask* task1, bool arg5, const CTask* task2, int32 arg7);
    int32 SetEventResponseTaskAllocator(int32 a2);
    int32 SetGroupDecisionMakerType(int32 a2);
    void  SetPrimaryTaskAllocator(CTaskAllocator* taskAllocator);
    void  SetScriptCommandTask(CPed* ped, const CTask* task);

    /// Helper so events can be directly passed in without having to it into a variable
    template<std::derived_from<CEvent> T>
    auto AddEvent(T event) {
        return AddEvent(&event);
    }

    static void SetTask(CPed* ped, const CTask* task, CPedTaskPair* pair, int32 arg5 = -1, bool arg6 = false);
};

VALIDATE_SIZE(CPedGroupIntelligence, 0x2A0);
