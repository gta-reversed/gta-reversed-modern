#include "StdInc.h"

CScriptedBrainTaskEntry(&CScriptedBrainTaskStore::ms_entries)[TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES] = *(CScriptedBrainTaskEntry(*)[TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES])0xC188F0;

void CScriptedBrainTaskEntry::InjectHooks()
{
    ReversibleHooks::Install(0x62EC40, &CScriptedBrainTaskEntry::Constructor);
}

void CScriptedBrainTaskStore::InjectHooks()
{
    CScriptedBrainTaskEntry::InjectHooks();
    ReversibleHooks::Install(0x635720, &CScriptedBrainTaskStore::SetTask);
    ReversibleHooks::Install(0x6357C0, &CScriptedBrainTaskStore::GetTask);
    ReversibleHooks::Install(0x635850, (void(*)(CPed*)) & CScriptedBrainTaskStore::Clear);
    ReversibleHooks::Install(0x6357F0, (void(*)(CTask*)) & CScriptedBrainTaskStore::Clear);
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
    std::int32_t freeEntryIndex = -1;
    for (std::int32_t i = 0; i < TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES; i++) {
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
    for (std::int32_t i = 0; i < TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES; i++) {
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
    for (std::int32_t i = 0; i < TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES; i++) {
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
    for (std::int32_t i = 0; i < TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES; i++) {
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
