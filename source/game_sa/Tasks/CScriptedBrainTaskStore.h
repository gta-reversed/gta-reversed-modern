#pragma once
#include "PluginBase.h"
#include "constants.h"

class CTask;
class CPed;

class CScriptedBrainTaskEntry
{
public:
    CPed* m_ped;
private:
    std::int32_t unused1;
    std::int32_t unused2;
public:
    CTask* m_task;

    static void InjectHooks();

    CScriptedBrainTaskEntry();
    ~CScriptedBrainTaskEntry(){}
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
