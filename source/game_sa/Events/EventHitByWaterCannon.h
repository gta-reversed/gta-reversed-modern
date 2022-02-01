#pragma once

#include "Event.h"

class CEventHitByWaterCannon : public CEvent {
public:
    CVector m_point;
    CVector m_moveSpeed;

public:
    CEventHitByWaterCannon(CVector const& point, CVector const& moveSpeed);
    ~CEventHitByWaterCannon() override = default;

    eEventType GetEventType() const override { return EVENT_WATER_CANNON; }
    int32 GetEventPriority() const override { return 64; }
    int32 GetLifeTime() override { return 0; }
    CEvent* Clone() override { return new CEventHitByWaterCannon(m_point, m_moveSpeed); }
    bool AffectsPed(CPed* ped) override;
    float GetLocalSoundLevel() override { return 55.0f; }

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventHitByWaterCannon* Constructor(CVector const& point, CVector const& moveSpeed);

    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventHitByWaterCannon, 0x24);
