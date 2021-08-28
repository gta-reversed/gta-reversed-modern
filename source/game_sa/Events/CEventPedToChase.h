#pragma once
#include "CEvent.h"
#include "CPed.h"

class CEventPedToChase : public CEvent
{
public:
    CPed* m_ped;

    static void InjectHooks();

    CEventPedToChase(CPed* ped);
    ~CEventPedToChase();
private:
    CEventPedToChase* Constructor(CPed* ped);
public:
    eEventType GetEventType() override { return EVENT_PED_TO_CHASE; }
    int GetEventPriority() override { return 1; }
    int GetLifeTime() override { return 0; }
    CEvent* Clone() override;
    bool AffectsPed(CPed* ped) override { return ped->IsAlive(); }
    
    CEvent* Clone_Reversed();
};

VALIDATE_SIZE(CEventPedToChase, 0x10);
