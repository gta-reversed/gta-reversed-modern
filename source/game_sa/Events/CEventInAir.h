#pragma once
#include "CEvent.h"

class CEventInAir : public CEvent
{
public:

    static void InjectHooks();

    CEventInAir() {};
    ~CEventInAir() {};
private:
    CEventInAir* Constructor();
public:
    eEventType GetEventType() override { return EVENT_IN_AIR; }
    int GetEventPriority() override { return 61; }
    int GetLifeTime() override { return 0; }
    CEvent* Clone() override { return new CEventInAir(); }
    bool AffectsPed(CPed* ped) override;

    bool AffectsPed_Reversed(CPed* ped);
};

class CEventStuckInAir : public CEvent
{
public:
    CPed* m_ped;

    static void InjectHooks();

    CEventStuckInAir(CPed* ped);
    ~CEventStuckInAir();
private:
    CEventStuckInAir* Constructor(CPed* ped);
public:

    eEventType GetEventType() override { return EVENT_STUCK_IN_AIR; }
    int GetEventPriority() override;
    int GetLifeTime() override { return 0; }
    CEvent* Clone() override { return new CEventStuckInAir(m_ped); }
    bool AffectsPed(CPed* ped) override;
    bool TakesPriorityOver(CEvent* refEvent) override;
    bool CanBeInterruptedBySameEvent() override { return true; }

    int GetEventPriority_Reversed();
    bool AffectsPed_Reversed(CPed* ped);
    bool TakesPriorityOver_Reversed(CEvent* refEvent);
};

VALIDATE_SIZE(CEventInAir, 0xC);
VALIDATE_SIZE(CEventStuckInAir, 0x10);
