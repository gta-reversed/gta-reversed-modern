/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CPedTaskPair.h"
#include "CPed.h"
#include "CTask.h"

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
    signed int GetTaskSecondarySlot(CPed* ped);
    bool       IsCurrentEventValid();
    bool       IsGroupResponding();
    void       Process();
    void       ProcessIgnorePlayerGroup();
    void       ReportAllBarScriptTasksFinished();
    void       ReportAllTasksFinished(CPedTaskPair* taskpair);
    void       ReportAllTasksFinished();
    bool       ReportFinishedTask(CPed const* ped, CTask const* task, CPedTaskPair* taskpair);
    bool       ReportFinishedTask(CPed const* ped, CTask const* task);
    void       SetDefaultTask(CPed* ped, CTask const* task);
    void       SetDefaultTaskAllocator(CPedGroupDefaultTaskAllocator const* PedGroupDefaultTaskAllocator);
    //! see ePedGroupTaskAllocator
    void SetDefaultTaskAllocatorType(int32 nPedGroupTaskAllocator);
    //! arg3 always true
    //! arg5 always false
    //! arg7 always  -1
    void  SetEventResponseTask(CPed* ped, bool arg3, CTask const* task1, bool arg5, CTask const* task2, int32 arg7);
    int32 SetEventResponseTaskAllocator(int32 a2);
    int32 SetGroupDecisionMakerType(int32 a2);
    void  SetPrimaryTaskAllocator(CTaskAllocator* taskAllocator);
    void  SetScriptCommandTask(CPed* ped, CTask const* task);
    void  SetTask(CPed* ped, CTask const* task, CPedTaskPair* taskpair, int32 arg5, bool arg6);
};

VALIDATE_SIZE(CPedGroupIntelligence, 0x2A0);
