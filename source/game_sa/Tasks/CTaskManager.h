/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTask.h"

enum ePrimaryTasks //array indexes
{
    TASK_PRIMARY_PHYSICAL_RESPONSE = 0,
    TASK_PRIMARY_EVENT_RESPONSE_TEMP,
    TASK_PRIMARY_EVENT_RESPONSE_NONTEMP,
    TASK_PRIMARY_PRIMARY,
    TASK_PRIMARY_DEFAULT,
    TASK_PRIMARY_MAX
};

enum eSecondaryTasks //array indexes
{
    TASK_SECONDARY_ATTACK = 0,                // want duck to be after attack
    TASK_SECONDARY_DUCK,                    // because attack controls ducking movement
    TASK_SECONDARY_SAY,
    TASK_SECONDARY_FACIAL_COMPLEX,
    TASK_SECONDARY_PARTIAL_ANIM,
    TASK_SECONDARY_IK,
    TASK_SECONDARY_MAX
};

class CTaskComplex;

class  CTaskManager {
public:
    CTask *m_aPrimaryTasks[5];
    CTask *m_aSecondaryTasks[6];
    class CPed *m_pPed;
    
    CTaskManager(CPed* ped);
    ~CTaskManager();
    CTask* GetActiveTask();
    CTask* FindActiveTaskByType(int taskType);
    CTask* FindTaskByType(int taskIndex, int taskType);
    CTask* GetTaskSecondary(int taskIndex);
    bool HasTaskSecondary(CTask const* task);
    void Flush();
    void FlushImmediately();
    void SetNextSubTask(CTaskComplex* pTask);
    static CTask* GetSimplestTask(CTask* task);
    void StopTimers(CEvent* _event);
    CTask* GetSimplestActiveTask();
    CTask* GetSimplestTask(int taskIndex);
    void AddSubTasks(CTaskComplex* task);
    void ParentsControlChildren(CTaskComplex* pTask);
    void SetTask(CTask* task, int taskIndex, bool arg2);
    void SetTaskSecondary(CTask* task, int taskIndex);
    void ClearTaskEventResponse();
    void ManageTasks();
    static void InjectHooks();
};

VALIDATE_SIZE(CTaskManager, 0x30);