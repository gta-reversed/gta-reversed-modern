/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CTask.h"

enum ePrimaryTasks // array indexes
{
    TASK_PRIMARY_PHYSICAL_RESPONSE = 0,
    TASK_PRIMARY_EVENT_RESPONSE_TEMP,
    TASK_PRIMARY_EVENT_RESPONSE_NONTEMP,
    TASK_PRIMARY_PRIMARY,
    TASK_PRIMARY_DEFAULT,
    TASK_PRIMARY_MAX
};

enum eSecondaryTasks // array indexes
{
    TASK_SECONDARY_ATTACK = 0,              // want duck to be after attack
    TASK_SECONDARY_DUCK,                    // because attack controls ducking movement
    TASK_SECONDARY_SAY,
    TASK_SECONDARY_FACIAL_COMPLEX,
    TASK_SECONDARY_PARTIAL_ANIM,
    TASK_SECONDARY_IK,
    TASK_SECONDARY_MAX
};

class CTaskComplex;
class CTaskSimple;
class CPed;

class CTaskManager {
public:
    CTask* m_aPrimaryTasks[TASK_PRIMARY_MAX];
    CTask* m_aSecondaryTasks[TASK_SECONDARY_MAX];
    CPed*  m_pPed;

public:
    static void InjectHooks();

    CTaskManager(CPed* ped);
    ~CTaskManager();

    CTaskManager* Constructor(CPed* ped);
    CTaskManager* Destructor();

    CTask* GetActiveTask();
    CTask* FindActiveTaskByType(int32 taskType);
    CTask* FindTaskByType(int32 taskIndex, int32 taskType);
    CTask* GetTaskSecondary(int32 taskIndex);

    bool HasPrimaryTask(const CTask* task);
    bool HasTaskSecondary(const CTask* task);

    void Flush();
    void FlushImmediately();

    void SetNextSubTask(CTaskComplex* pTask);

    static CTaskSimple* GetSimplestTask(CTask* task);
    void StopTimers(const CEvent* event);
    CTask* GetSimplestActiveTask();
    CTaskSimple* GetSimplestTask(int32 taskIndex);

    void AddSubTasks(CTaskComplex* task);
    void ParentsControlChildren(CTaskComplex* pTask);
    void SetTask(CTask* task, int32 taskIndex, bool unused = false);
    void SetTaskSecondary(CTask* task, int32 taskIndex);
    void ClearTaskEventResponse();
    void ManageTasks();

    CTask* GetPrimaryTask(int32 taskIndex) {
        return m_aPrimaryTasks[taskIndex];
    }
};

VALIDATE_SIZE(CTaskManager, 0x30);
