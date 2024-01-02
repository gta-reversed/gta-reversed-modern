#pragma once

#include "Event.h"

class NOTSA_EXPORT_VTABLE CEventInAir : public CEvent {
public:
    CEventInAir() = default;
    ~CEventInAir() override = default;

    eEventType GetEventType() const override { return EVENT_IN_AIR; }
    int32 GetEventPriority() const override { return 61; }
    int32 GetLifeTime() override { return 0; }
    CEvent* Clone() override { return new CEventInAir(); }
    bool AffectsPed(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventInAir* Constructor();

    bool AffectsPed_Reversed(CPed* ped);
};

class NOTSA_EXPORT_VTABLE CEventStuckInAir : public CEvent {
public:
    CPed* m_ped;

public:
    CEventStuckInAir(CPed* ped);
    ~CEventStuckInAir() override;

    eEventType GetEventType() const override { return EVENT_STUCK_IN_AIR; }
    int32 GetEventPriority() const override;
    int32 GetLifeTime() override { return 0; }
    CEvent* Clone() override { return new CEventStuckInAir(m_ped); }
    bool AffectsPed(CPed* ped) override;
    bool TakesPriorityOver(const CEvent& refEvent) override;
    bool CanBeInterruptedBySameEvent() override { return true; }

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventStuckInAir* Constructor(CPed* ped);

    int32 GetEventPriority_Reversed() const;
    bool AffectsPed_Reversed(CPed* ped);
    bool TakesPriorityOver_Reversed(const CEvent& refEvent);
};

VALIDATE_SIZE(CEventInAir, 0xC);
VALIDATE_SIZE(CEventStuckInAir, 0x10);
