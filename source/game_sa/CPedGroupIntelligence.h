/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CPedTaskPair.h"
#include "CPed.h"
#include "CTask.h"

class CGroupEventHandler;
class CPedGroupDefaultTaskAllocator;
class CTaskAllocator;
class CEvent;
class CPedGroup;
class CEventGroupEvent;

class  CPedGroupIntelligence {
    PLUGIN_NO_DEFAULT_CONSTRUCTION(CPedGroupIntelligence)

public:
    CPedGroup *m_pPedGroup;
    CEventGroupEvent*m_pGroupEventHandler; // TODO: member name is incorrect. It needs to be fixed.
    CEventGroupEvent* m_pEventGroupEvent;
    CPedTaskPair m_groupTasks[32];
    CPedGroupDefaultTaskAllocator *m_pPedGroupDefaultTaskAllocator;
    CTaskAllocator *m_pPrimaryTaskAllocator;
    CTaskAllocator *m_pEventResponseTaskAllocator;
    int m_dwDecisionMakerType;
    char field_29C;

     bool AddEvent(CEvent *event);
     void ComputeDefaultTasks(CPed *ped);
     void *ComputeEventResponseTasks();
     void ComputeScriptCommandTasks();
     void FlushTasks(CPedTaskPair *taskpair, CPed *ped);
     CTask *GetTask(CPed *ped, CPedTaskPair const *taskpair);
     CTask *GetTaskDefault(CPed *ped);
     CTask *GetTaskScriptCommand(CPed *ped);
     CTask *GetTaskSecondary(CPed *ped);
     signed int GetTaskSecondarySlot(CPed *ped);
     bool IsCurrentEventValid();
     bool IsGroupResponding();
     void Process();
     void ProcessIgnorePlayerGroup();
     void ReportAllBarScriptTasksFinished();
     void ReportAllTasksFinished(CPedTaskPair *taskpair);
     void ReportAllTasksFinished();
     bool ReportFinishedTask(CPed const *ped, CTask const *task, CPedTaskPair *taskpair);
     bool ReportFinishedTask(CPed const *ped, CTask const *task);
     void SetDefaultTask(CPed *ped, CTask const *task);
     void SetDefaultTaskAllocator(CPedGroupDefaultTaskAllocator const *PedGroupDefaultTaskAllocator);
    //! see ePedGroupTaskAllocator
     void SetDefaultTaskAllocatorType(int nPedGroupTaskAllocator);
    //! arg3 always true
    //! arg5 always false
    //! arg7 always  -1
     void SetEventResponseTask(CPed *ped, bool arg3, CTask const *task1, bool arg5, CTask const *task2, int arg7);
     int SetEventResponseTaskAllocator(int a2);
     int SetGroupDecisionMakerType(int a2);
     void SetPrimaryTaskAllocator(CTaskAllocator *taskAllocator);
     void SetScriptCommandTask(CPed *ped, CTask const *task);
     void SetTask(CPed *ped, CTask const *task, CPedTaskPair *taskpair, int arg5, bool arg6);
};

VALIDATE_SIZE(CPedGroupIntelligence, 0x2A0);

//#include "meta/meta.CPedGroupIntelligence.h"
