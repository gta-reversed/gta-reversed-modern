#pragma once

#include "EventEditableResponse.h"
#include "Ped.h"

class CEventHealthLow : public CEventEditableResponse {
public:
    CEventHealthLow() = default;
    ~CEventHealthLow() override = default;

    eEventType GetEventType() const override { return EVENT_HEALTH_LOW; }
    int32 GetEventPriority() const override { return 68; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override { return ped->IsAlive(); };
    CEventEditableResponse* CloneEditable() override { return new CEventHealthLow(); }
};

class CEventHealthReallyLow : public CEventEditableResponse {
public:
    CEventHealthReallyLow() = default;
    ~CEventHealthReallyLow() override = default;

    eEventType GetEventType() const override { return EVENT_HEALTH_REALLY_LOW; }
    int32 GetEventPriority() const override { return 69; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override { return ped->IsAlive(); };
    CEventEditableResponse* CloneEditable() override { return new CEventHealthReallyLow(); }
};

class CEventHighAngerAtPlayer : public CEventEditableResponse {
public:
    CEventHighAngerAtPlayer() = default;
    ~CEventHighAngerAtPlayer() override = default;

    eEventType GetEventType() const override { return EVENT_HIGH_ANGER_AT_PLAYER; }
    int32 GetEventPriority() const override { return 34; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override { return ped->IsAlive(); };
    CEventEditableResponse* CloneEditable() override { return new CEventHighAngerAtPlayer(); }
};
