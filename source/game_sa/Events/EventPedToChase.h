#pragma once

#include "Event.h"
#include "Ped.h"

class CEventPedToChase : public CEvent {
public:
    CPed* m_ped;

public:
    static void InjectHooks();

    CEventPedToChase(CPed* ped);
    ~CEventPedToChase();
private:
    CEventPedToChase* Constructor(CPed* ped);
public:
    eEventType GetEventType() const override { return EVENT_PED_TO_CHASE; }
    int32 GetEventPriority() const override { return 1; }
    int32 GetLifeTime() override { return 0; }
    CEvent* Clone() override;
    bool AffectsPed(CPed* ped) override { return ped->IsAlive(); }
    
    CEvent* Clone_Reversed();
};

VALIDATE_SIZE(CEventPedToChase, 0x10);
