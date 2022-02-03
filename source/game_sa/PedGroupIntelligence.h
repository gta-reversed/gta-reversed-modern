/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PedTaskPair.h"

class CPed;
class CTask;
class CGroupEventHandler;
class CPedGroupDefaultTaskAllocator;
class CTaskAllocator;
class CEvent;
class CPedGroup;
class CEventGroupEvent;

class CPedGroupIntelligence {
    PLUGIN_NO_DEFAULT_CONSTRUCTION(CPedGroupIntelligence)

public:
    CPedGroup*                     m_pPedGroup;
    CEventGroupEvent*              m_oldEventGroupEvent;
    CEventGroupEvent*              m_eventGroupEvent;
    CPedTaskPair                   m_groupTasks[32];
    CPedGroupDefaultTaskAllocator* m_pPedGroupDefaultTaskAllocator;
    CTaskAllocator*                m_pPrimaryTaskAllocator;
    CTaskAllocator*                m_pEventResponseTaskAllocator;
    int32                          m_dwDecisionMakerType;
    int32                          m_taskSequenceId; // Used in CTaskSequences::ms_taskSequence

public:
    bool       AddEvent(CEvent* event);
    void       ComputeDefaultTasks(CPed* ped);
    void*      ComputeEventResponseTasks();
    void       ComputeScriptCommandTasks();
    void       FlushTasks(CPedTaskPair* taskpair, CPed* ped);
    CTask*     GetTask(CPed* ped, CPedTaskPair const* taskpair);
    CTask*     GetTaskDefault(CPed* ped);
    CTask*     GetTaskScriptCommand(CPed* ped);
    CTask*     GetTaskSecondary(CPed* ped);
    int32      GetTaskSecondarySlot(CPed* ped);
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
    //! see ePedGroupTaskAllocator
    void SetDefaultTaskAllocatorType(int32 nPedGroupTaskAllocator);
    //! arg3 always true
    //! arg5 always false
    //! arg7 always  -1
    void  SetEventResponseTask(CPed* ped, bool arg3, const CTask* task1, bool arg5, const CTask* task2, int32 arg7);
    int32 SetEventResponseTaskAllocator(int32 a2);
    int32 SetGroupDecisionMakerType(int32 a2);
    void  SetPrimaryTaskAllocator(CTaskAllocator* taskAllocator);
    void  SetScriptCommandTask(CPed* ped, const CTask* task);
    void  SetTask(CPed* ped, const CTask* task, CPedTaskPair* taskpair, int32 arg5, bool arg6);
};

VALIDATE_SIZE(CPedGroupIntelligence, 0x2A0);
