#pragma once
#include "CEvent.h"
#include "CPed.h"

class CPed;

class CEventGunAimedAt : public CEventEditableResponse
{
public:
    CPed* m_ped;

    static void InjectHooks();

    CEventGunAimedAt(CPed* ped);
    ~CEventGunAimedAt();
private:
    CEventGunAimedAt* Constructor(CPed* ped);
public:
    eEventType GetEventType() const override { return EVENT_GUN_AIMED_AT; }
    int32_t GetEventPriority() const override { return 50; }
    int GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    bool IsCriminalEvent() override { return m_ped && m_ped->IsPlayer(); }
    void ReportCriminalEvent(CPed* ped) override;
    CEntity* GetSourceEntity() const override { return m_ped; }
    bool TakesPriorityOver(const CEvent& refEvent) override;
    CEventEditableResponse* CloneEditable() override;

    bool AffectsPed_Reversed(CPed* ped);
    void ReportCriminalEvent_Reversed(CPed* ped);
    bool TakesPriorityOver_Reversed(const CEvent& refEvent);
    CEventEditableResponse* CloneEditable_Reversed();
};

VALIDATE_SIZE(CEventGunAimedAt, 0x18);
