#pragma once
#include "PluginBase.h"
#include "constants.h"

class CEventScriptCommand;
class CTask;
class CPed;

enum class eScriptedTaskStatus : std::int32_t
{
    NONE = -1,
    EVENT_ASSOCIATED = 0,
    TASK_ASSOCIATED,
    PRIMARY,
    FLUSHED,
    GROUP,
    BRAIN, // a.k.a attractor
    SECONDARY
};

class CPedScriptedTaskRecordData
{
public:
    std::int32_t m_opcode;
    CEventScriptCommand* m_event;
    CTask* m_task;
    CPed* m_ped;
    eScriptedTaskStatus m_status;

    static void InjectHooks();

    CPedScriptedTaskRecordData();
    ~CPedScriptedTaskRecordData() {}
private:
    CPedScriptedTaskRecordData* Constructor();
public:
    void AssociateWithTask(CTask* task);
    void AssociateWithEvent(CEventScriptCommand* event);
    void Set(CPed* ped, std::int32_t opcode, CEventScriptCommand* event);
    void Set(CPed* ped, std::int32_t opcode, CTask* task);
    void SetAsGroupTask(CPed* ped, std::int32_t opcode, CTask* task);
    void SetAsAttractorScriptTask(CPed* ped, std::int32_t opcode, CTask* task);
    void Flush();
};

VALIDATE_SIZE(CPedScriptedTaskRecordData, 0x14);

class CPedScriptedTaskRecord
{
public:
    static void InjectHooks();

    static CPedScriptedTaskRecordData(&ms_scriptedTasks)[TOTAL_SCRIPTED_TASKS];

    static CPedScriptedTaskRecordData* GetRecordAssociatedWithEvent(CEvent* event);
    static eScriptedTaskStatus GetStatus(CPed* ped);
    static eScriptedTaskStatus GetStatus(CPed* ped, std::int32_t opcode);
    static std::int32_t GetVacantSlot();
    static void Process();
};
