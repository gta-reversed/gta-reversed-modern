#pragma once

#include "Event.h"

#include "Event.h"
#include "EventOnFire.h"


class CEventOnFire : public CEvent {
public:
    CEventOnFire() = default;
    ~CEventOnFire() override = default;

    eEventType GetEventType() const override { return EVENT_ON_FIRE; }
    int32 GetEventPriority() const override { return 66; }
    int32 GetLifeTime() override { return 0; }
    CEventOnFire* Clone() override { return new CEventOnFire(); }
    bool AffectsPed(CPed* ped) override;
    float GetLocalSoundLevel() override { return 60.0f; }

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    bool AffectsPed_Reversed(CPed* ped);
};
VALIDATE_SIZE(CEventOnFire, 0xC);
