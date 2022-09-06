#pragma once

#include "Event.h"

class CTask;

class NOTSA_EXPORT_VTABLE CEventScriptCommand : public CEvent {
public:
    int32  m_primaryTaskIndex;
    CTask* m_task;
    bool   m_affectsDeadPeds;

public:
    CEventScriptCommand(int32 primaryTaskIndex, CTask* task, bool affectsDeadPeds);
    ~CEventScriptCommand() override;

    eEventType GetEventType() const override { return EVENT_SCRIPT_COMMAND; }
    int32 GetEventPriority() const override;
    int32 GetLifeTime() override { return 0; }
    CEvent* Clone() override;
    bool AffectsPed(CPed* ped) override;
    bool TakesPriorityOver(const CEvent& refEvent) override;
    bool IsValid(CPed* ped) override;
    virtual CTask* CloneScriptTask();

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventScriptCommand* Constructor(int32 primaryTaskIndex, CTask* task, bool affectsDeadPeds);

    int32 GetEventPriority_Reversed() const;
    CEvent* Clone_Reversed();
    bool AffectsPed_Reversed(CPed* ped);
    bool TakesPriorityOver_Reversed(const CEvent& refEvent);
    bool IsValid_Reversed(CPed* ped);
    CTask* CloneScriptTask_Reversed();
};

VALIDATE_SIZE(CEventScriptCommand, 0x18);
