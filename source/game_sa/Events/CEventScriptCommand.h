#pragma once

#include "CEvent.h"

class CTask;

class CEventScriptCommand : public CEvent {
public:
    int32_t m_primaryTaskIndex;
    CTask*  m_task;
    bool    m_affectsDeadPeds;

public:
    CEventScriptCommand(int32_t primaryTaskIndex, CTask* task, bool affectsDeadPeds);
    ~CEventScriptCommand();

    eEventType GetEventType() const override {
        return EVENT_SCRIPT_COMMAND;
    }
    int32_t GetEventPriority() const override;
    int GetLifeTime() override {
        return 0;
    }
    CEvent* Clone() override;
    bool AffectsPed(CPed* ped) override;
    bool TakesPriorityOver(const CEvent& refEvent) override;
    bool IsValid(CPed* ped) override;
    virtual CTask* CloneScriptTask();

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventScriptCommand* Constructor(int32_t primaryTaskIndex, CTask* task, bool affectsDeadPeds);

    int32_t GetEventPriority_Reversed() const;
    CEvent* Clone_Reversed();
    bool AffectsPed_Reversed(CPed* ped);
    bool TakesPriorityOver_Reversed(const CEvent& refEvent);
    bool IsValid_Reversed(CPed* ped);
    CTask* CloneScriptTask_Reversed();
};

VALIDATE_SIZE(CEventScriptCommand, 0x18);
