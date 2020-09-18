#pragma once
#include "PluginBase.h"
#include "CEvent.h"
class CTask;

class CEventScriptCommand : public CEvent
{
public:
    std::int32_t m_primaryTaskIndex;
    CTask* m_task;
    bool m_affectsDeadPeds;

    static void InjectHooks();

    CEventScriptCommand(std::int32_t primaryTaskIndex, CTask* task, bool affectsDeadPeds);
    ~CEventScriptCommand();
private:
    CEventScriptCommand* Constructor(std::int32_t primaryTaskIndex, CTask* task, bool affectsDeadPeds);
public:
    eEventType GetEventType() override { return EVENT_SCRIPT_COMMAND; }
    int GetEventPriority() override;
    int GetLifeTime() override { return 0; }
    CEvent* Clone() override;
    bool AffectsPed(CPed* ped) override;
    bool TakesPriorityOver(CEvent* refEvent) override;
    bool IsValid(CPed* ped) override;
    virtual CTask* CloneScriptTask();

    int GetEventPriority_Reversed();
    CEvent* Clone_Reversed();
    bool AffectsPed_Reversed(CPed* ped);
    bool TakesPriorityOver_Reversed(CEvent* refEvent);
    bool IsValid_Reversed(CPed* ped);
    CTask* CloneScriptTask_Reversed();
};

VALIDATE_SIZE(CEventScriptCommand, 0x18);
