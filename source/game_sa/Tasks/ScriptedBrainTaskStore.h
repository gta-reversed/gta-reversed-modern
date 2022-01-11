#pragma once

#include "constants.h"

class CTask;
class CPed;

class CScriptedBrainTaskEntry {
public:
    CPed*  m_ped;
    int32  unused1;
    int32  unused2;
    CTask* m_task;

public:
    static void InjectHooks();

    CScriptedBrainTaskEntry();
    ~CScriptedBrainTaskEntry() {}

private:
    CScriptedBrainTaskEntry* Constructor();
};

VALIDATE_SIZE(CScriptedBrainTaskEntry, 0x10);

class CScriptedBrainTaskStore
{
public:
    static CScriptedBrainTaskEntry(&ms_entries)[TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES];

    static void InjectHooks();

    static CTask* SetTask(CPed* ped, CTask* task);
    static CTask* GetTask(CPed* ped);
    static void Clear(CPed* ped);
    static void Clear(CTask* task);
};
