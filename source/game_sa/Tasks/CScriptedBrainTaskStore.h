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

    CScriptedBrainTaskEntry();
    ~CScriptedBrainTaskEntry(){}
};

VALIDATE_SIZE(CScriptedBrainTaskEntry, 0x10);

class CScriptedBrainTaskStore
{
public:
    static CScriptedBrainTaskEntry(&ms_entries)[TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES];

    static CTask* GetTask(CPed* ped);
};
