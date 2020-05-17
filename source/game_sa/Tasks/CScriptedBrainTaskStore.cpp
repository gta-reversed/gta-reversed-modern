#include "StdInc.h"

CScriptedBrainTaskEntry(&ms_entries)[TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES] = *(CScriptedBrainTaskEntry(*)[TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES])0xC188F0;

CScriptedBrainTaskEntry::CScriptedBrainTaskEntry()
{
    m_ped = nullptr;
    m_task = nullptr;
}

CTask* CScriptedBrainTaskStore::GetTask(CPed* ped)
{
    return plugin::CallAndReturn<CTask*, 0x6357C0, CPed*>(ped);
}
