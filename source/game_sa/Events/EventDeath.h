#pragma once

#include "Event.h"

class CEventDeath : public CEvent {
    bool   m_bDrowning;
    char   _pad[3];
public:
    uint32 m_deathTimeInMs;

public:
    static void InjectHooks();

    CEventDeath(bool bDrowning);
    CEventDeath(bool bDrowning, uint32 deathTimeInMs);
    ~CEventDeath();
private:
    CEventDeath* Constructor(bool bDrowning);
public:
    eEventType GetEventType() const override { return EVENT_DEATH; }
    int32 GetEventPriority() const override { return 73; }
    int32 GetLifeTime() override { return 0; }
    CEvent* Clone() override;
    bool AffectsPed(CPed* ped) override { return true; }

    CEvent* Clone_Reversed();
};

VALIDATE_SIZE(CEventDeath, 0x14);
