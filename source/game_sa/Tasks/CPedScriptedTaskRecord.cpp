#include "StdInc.h"

CPedScriptedTaskRecordData(&CPedScriptedTaskRecord::ms_scriptedTasks)[TOTAL_SCRIPTED_TASKS] = *(CPedScriptedTaskRecordData(*)[TOTAL_SCRIPTED_TASKS])0xC0B1E8;

void CPedScriptedTaskRecordData::InjectHooks()
{
    HookInstall(0x608330, &CPedScriptedTaskRecordData::Constructor, 5);
    HookInstall(0x608520, &CPedScriptedTaskRecordData::AssociateWithTask, 5);
    HookInstall(0x608500, &CPedScriptedTaskRecordData::AssociateWithEvent, 5);
    HookInstall(0x608390, (void(CPedScriptedTaskRecordData::*)(CPed*, std::int32_t, CEventScriptCommand*)) & CPedScriptedTaskRecordData::Set, 5);
    HookInstall(0x6083E0, (void(CPedScriptedTaskRecordData::*)(CPed*, std::int32_t, CTask*)) & CPedScriptedTaskRecordData::Set, 5);
    HookInstall(0x6084A0, &CPedScriptedTaskRecordData::SetAsGroupTask, 5);
    HookInstall(0x608440, &CPedScriptedTaskRecordData::SetAsAttractorScriptTask, 5);
    HookInstall(0x608350, &CPedScriptedTaskRecordData::Flush, 5);
}

void CPedScriptedTaskRecord::InjectHooks()
{
    HookInstall(0x608580, &CPedScriptedTaskRecord::GetRecordAssociatedWithEvent, 5);
    HookInstall(0x608750, (eScriptedTaskStatus(*)(CPed*)) & CPedScriptedTaskRecord::GetStatus, 5);
    HookInstall(0x608710, (eScriptedTaskStatus(*)(CPed*, std::int32_t)) & CPedScriptedTaskRecord::GetStatus, 5);
    HookInstall(0x608540, &CPedScriptedTaskRecord::GetVacantSlot, 5);
    HookInstall(0x6085E0, &CPedScriptedTaskRecord::Process, 5);
}

CPedScriptedTaskRecordData::CPedScriptedTaskRecordData()
{
    m_opcode = -1;
    m_event = nullptr;
    m_task = nullptr;
    m_ped = nullptr;
    m_status = eScriptedTaskStatus::FLUSHED;
}

CPedScriptedTaskRecordData* CPedScriptedTaskRecordData::Constructor()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CPedScriptedTaskRecordData*, 0x608330, CPedScriptedTaskRecordData*>(this);
#else
    this->CPedScriptedTaskRecordData::CPedScriptedTaskRecordData();
    return this;
#endif
}

void CPedScriptedTaskRecordData::AssociateWithTask(CTask* task)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x608520, CPedScriptedTaskRecordData*, CTask*>(this, task);
#else
    m_event = nullptr;
    m_task = task;
    m_status = eScriptedTaskStatus::TASK_ASSOCIATED;
#endif
}

void CPedScriptedTaskRecordData::AssociateWithEvent(CEventScriptCommand* event)
{
#ifdef USE_DEFAULT_FUNCTIONS
        plugin::CallMethod<0x608500, CPedScriptedTaskRecordData*, CEventScriptCommand*>(this, event);
#else
    m_event = event;
    m_status = eScriptedTaskStatus::EVENT_ASSOCIATED;
#endif
}

void CPedScriptedTaskRecordData::Set(CPed* ped, std::int32_t opcode, CEventScriptCommand* event)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x608390, CPedScriptedTaskRecordData*, CPed*, std::int32_t, CEventScriptCommand*>(this, ped, opcode, event);
#else
    Flush();
    m_ped = ped;
    ped->RegisterReference(reinterpret_cast<CEntity**>(&m_ped));
    m_task = nullptr;
    m_status = eScriptedTaskStatus::EVENT_ASSOCIATED;
    m_opcode = opcode;
    m_event = event;
#endif
}

void CPedScriptedTaskRecordData::Set(CPed* ped, std::int32_t opcode, CTask* task)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x6083E0, CPedScriptedTaskRecordData*, CPed*, std::int32_t, CTask*>(this, ped, opcode, task);
#else
    Flush();
    m_ped = ped;
    ped->RegisterReference(reinterpret_cast<CEntity**>(&m_ped));
    m_opcode = opcode;
    m_event = nullptr;
    m_task = task;
    m_status = eScriptedTaskStatus::TASK_ASSOCIATED;
#endif
}

void CPedScriptedTaskRecordData::SetAsGroupTask(CPed* ped, std::int32_t opcode, CTask* task)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x6084A0, CPedScriptedTaskRecordData*, CPed*, std::int32_t, CTask*>(this, ped, opcode, task);
#else
    Flush();
    m_ped = ped;
    ped->RegisterReference(reinterpret_cast<CEntity**>(&m_ped));
    m_opcode = opcode;
    m_event = nullptr;
    m_task = task;
    m_status = eScriptedTaskStatus::GROUP;
#endif
}

void CPedScriptedTaskRecordData::SetAsAttractorScriptTask(CPed* ped, std::int32_t opcode, CTask* task)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x608440, CPedScriptedTaskRecordData*, CPed*, std::int32_t, CTask*>(this, ped, opcode, task);
#else
    Flush();
    m_ped = ped;
    ped->RegisterReference(reinterpret_cast<CEntity**>(&m_ped));
    m_opcode = opcode;
    m_event = nullptr;
    m_task = task;
    m_status = eScriptedTaskStatus::BRAIN;
#endif
}

void CPedScriptedTaskRecordData::Flush()
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x608350, CPedScriptedTaskRecordData*>(this);
#else
    if (m_ped)
        m_ped->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_ped));
    m_ped = nullptr;
    m_event = nullptr;
    m_task = nullptr;
    m_status = eScriptedTaskStatus::FLUSHED;
    m_opcode = -1;
#endif
}

CPedScriptedTaskRecordData* CPedScriptedTaskRecord::GetRecordAssociatedWithEvent(CEvent* event)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<CPedScriptedTaskRecordData*, 0x608580, CEvent*>(event);
#else
    for (std::int32_t i = 0; i < TOTAL_SCRIPTED_TASKS; i++) {
        CPedScriptedTaskRecordData& taskRecordData = ms_scriptedTasks[i];
        if (taskRecordData.m_event == event)
            return &taskRecordData;
    }
    return nullptr;
#endif
}

eScriptedTaskStatus CPedScriptedTaskRecord::GetStatus(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<eScriptedTaskStatus, 0x608750, CPed*>(ped);
#else
    for (std::int32_t i = 0; i < TOTAL_SCRIPTED_TASKS; i++) {
        CPedScriptedTaskRecordData& taskRecordData = ms_scriptedTasks[i];
        if (taskRecordData.m_ped == ped)
            return eScriptedTaskStatus::TASK_ASSOCIATED;
    }
    return eScriptedTaskStatus::EVENT_ASSOCIATED;
#endif
}

eScriptedTaskStatus CPedScriptedTaskRecord::GetStatus(CPed* ped, std::int32_t opcode)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<eScriptedTaskStatus, 0x608710, CPed*, std::int32_t>(ped, opcode);
#else
    for (std::int32_t i = 0; i < TOTAL_SCRIPTED_TASKS; i++) {
        CPedScriptedTaskRecordData& taskRecordData = ms_scriptedTasks[i];
        if ((opcode == -1 || taskRecordData.m_opcode == opcode) && taskRecordData.m_ped == ped)
            return taskRecordData.m_status;
    }
    return eScriptedTaskStatus::NONE;
#endif
}

std::int32_t CPedScriptedTaskRecord::GetVacantSlot()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<std::int32_t, 0x608540>();
#else
    for (std::int32_t i = 0; i < TOTAL_SCRIPTED_TASKS; i++) {
        CPedScriptedTaskRecordData& taskRecordData = ms_scriptedTasks[i];
        if (!taskRecordData.m_event && !taskRecordData.m_task && !taskRecordData.m_ped)
            return i;
    }
    return -1;
#endif
}

void CPedScriptedTaskRecord::Process()
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x6085E0>();
#else
    for (std::int32_t i = 0; i < TOTAL_SCRIPTED_TASKS; i++) {
        CPedScriptedTaskRecordData& taskRecordData = ms_scriptedTasks[i];
        if (taskRecordData.m_event || taskRecordData.m_task || taskRecordData.m_ped) {
            if (!taskRecordData.m_ped) {
                taskRecordData.Flush();
            }
            else if (taskRecordData.m_event) {
                if (taskRecordData.m_ped->GetEventGroup().HasEvent(taskRecordData.m_event))
                    taskRecordData.m_status = eScriptedTaskStatus::EVENT_ASSOCIATED;
                else
                    taskRecordData.Flush();
            }
            else if (taskRecordData.m_task) {
                eScriptedTaskStatus status = taskRecordData.m_status;
                if (status == eScriptedTaskStatus::GROUP || status == eScriptedTaskStatus::BRAIN) {
                    CTask* pScriptedTask = nullptr;
                    if (status == eScriptedTaskStatus::GROUP) {
                        CPedGroup* pedGroup = CPedGroups::GetPedsGroup(taskRecordData.m_ped);
                        if (pedGroup)
                            pScriptedTask = pedGroup->GetIntelligence().GetTaskScriptCommand(taskRecordData.m_ped);
                    }
                    else if (status == eScriptedTaskStatus::BRAIN) {
                        pScriptedTask = CScriptedBrainTaskStore::GetTask(taskRecordData.m_ped);
                    }
                    if (pScriptedTask != taskRecordData.m_task)
                        taskRecordData.Flush();
                }
                else {
                    CTaskManager& taskManager = taskRecordData.m_ped->GetTaskManager();
                    if (taskManager.GetActiveTask() == taskRecordData.m_task)
                        taskRecordData.m_status = eScriptedTaskStatus::TASK_ASSOCIATED;
                    else if (taskManager.HasPrimaryTask(taskRecordData.m_task))
                        taskRecordData.m_status = eScriptedTaskStatus::PRIMARY;
                    else if (taskManager.HasTaskSecondary(taskRecordData.m_task))
                        taskRecordData.m_status = eScriptedTaskStatus::SECONDARY;
                    else
                        taskRecordData.Flush();
                }
            }
        }
    }
#endif
}
