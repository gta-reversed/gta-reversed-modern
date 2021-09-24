#pragma once

#include "CEvent.h"
#include "CPed.h"

class CEventPedToFlee : public CEvent {
public:
    CPed* m_ped;

public:
    static void InjectHooks();

    CEventPedToFlee(CPed* ped);
    ~CEventPedToFlee();
private:
    CEventPedToFlee* Constructor(CPed* ped);
public:
    eEventType GetEventType() const override { return EVENT_PED_TO_FLEE; }
    int32 GetEventPriority() const override { return 2; }
    int32 GetLifeTime() override { return 0; }
    CEvent* Clone() override;
    bool AffectsPed(CPed* ped) override { return ped->IsAlive(); }
  
    CEvent* Clone_Reversed();
};

VALIDATE_SIZE(CEventPedToFlee, 0x10);
