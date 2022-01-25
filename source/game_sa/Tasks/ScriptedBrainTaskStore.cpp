#include "StdInc.h"

CScriptedBrainTaskEntry(&CScriptedBrainTaskStore::ms_entries)[TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES] = *(CScriptedBrainTaskEntry(*)[TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES])0xC188F0;

void CScriptedBrainTaskEntry::InjectHooks()
{
    Install("CScriptedBrainTaskEntry", "CScriptedBrainTaskEntry", 0x62EC40, &CScriptedBrainTaskEntry::Constructor);
}

void CScriptedBrainTaskStore::InjectHooks()
{
    CScriptedBrainTaskEntry::InjectHooks();
    Install("CScriptedBrainTaskStore", "SetTask", 0x635720, &CScriptedBrainTaskStore::SetTask);
    Install("CScriptedBrainTaskStore", "GetTask", 0x6357C0, &CScriptedBrainTaskStore::GetTask);
    Install("CScriptedBrainTaskStore", "Clear_ped", 0x635850, static_cast<void(*)(CPed*)>(&CScriptedBrainTaskStore::Clear));
    Install("CScriptedBrainTaskStore", "Clear_task", 0x6357F0, static_cast<void(*)(CTask*)>(&CScriptedBrainTaskStore::Clear));
}

CScriptedBrainTaskEntry::CScriptedBrainTaskEntry()
{
    m_ped = nullptr;
    m_task = nullptr;
}

CScriptedBrainTaskEntry* CScriptedBrainTaskEntry::Constructor()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CScriptedBrainTaskEntry*, 0x62EC40, CScriptedBrainTaskEntry*>(this);
#else
    this->CScriptedBrainTaskEntry::CScriptedBrainTaskEntry();
    return this;
#endif
}

CTask* CScriptedBrainTaskStore::SetTask(CPed* ped, CTask* task)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<CTask*, 0x635720, CPed*, CTask*>(ped, task);
#else
    int32 freeEntryIndex = -1;
    for (int32 i = 0; i < TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES; i++) {
        CScriptedBrainTaskEntry& entry = ms_entries[i];
        if (!entry.m_ped && freeEntryIndex == -1)
            freeEntryIndex = i;
        if (entry.m_ped == ped) {
            if (entry.m_task)
                delete entry.m_task;
            entry.m_task = task;
            return task;
        }
    }
    if (freeEntryIndex == -1) {
        if (task)
            delete task;
        return nullptr;
    }
    CScriptedBrainTaskEntry& entry = ms_entries[freeEntryIndex];
    entry.m_ped = ped;
    ped->RegisterReference(reinterpret_cast<CEntity**>(&entry.m_ped));
    if (entry.m_task)
        delete entry.m_task;
    entry.m_task = task;
    return task;
#endif
}

CTask* CScriptedBrainTaskStore::GetTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<CTask*, 0x6357C0, CPed*>(ped);
#else
    for (int32 i = 0; i < TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES; i++) {
        CScriptedBrainTaskEntry& entry = ms_entries[i];
        if (entry.m_ped == ped)
            return entry.m_task;
    }
    return nullptr;
#endif
}

void CScriptedBrainTaskStore::Clear(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x635850, CPed*>(ped);
#else
    for (int32 i = 0; i < TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES; i++) {
        CScriptedBrainTaskEntry& entry = ms_entries[i];
        if (entry.m_ped == ped) {
            if(entry.m_task)
                delete entry.m_task;
            entry.m_task = nullptr;
            if (entry.m_ped)
                entry.m_ped->CleanUpOldReference(reinterpret_cast<CEntity**>(&entry.m_ped));
            entry.m_ped = nullptr;
            return;
        }
    }
#endif
}

void CScriptedBrainTaskStore::Clear(CTask* task)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x6357F0, CTask*>(task);
#else
    for (int32 i = 0; i < TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES; i++) {
        CScriptedBrainTaskEntry& entry = ms_entries[i];
        if (entry.m_task == task) {
            if (entry.m_task)
                delete entry.m_task;
            entry.m_task = nullptr;
            if (entry.m_ped)
                entry.m_ped->CleanUpOldReference(reinterpret_cast<CEntity**>(&entry.m_ped));
            entry.m_ped = nullptr;
            return;
        }
    }
#endif
}
