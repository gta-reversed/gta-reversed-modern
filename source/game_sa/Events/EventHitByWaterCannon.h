#include "Event.h"

class CEventHitByWaterCannon : public CEvent {
public:
    CVector m_point;
    CVector m_moveSpeed;

    static void InjectHooks();

    CEventHitByWaterCannon(CVector const& point, CVector const& moveSpeed);
    ~CEventHitByWaterCannon() {};
private:
    CEventHitByWaterCannon* Constructor(CVector const& point, CVector const& moveSpeed);
public:
    eEventType GetEventType() const override { return EVENT_WATER_CANNON; }
    int32 GetEventPriority() const override { return 64; }
    int32 GetLifeTime() override { return 0; }
    CEvent* Clone() override { return new CEventHitByWaterCannon(m_point, m_moveSpeed); }
    bool AffectsPed(CPed* ped) override;
    float GetLocalSoundLevel() override { return 55.0f; }

    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventHitByWaterCannon, 0x24);
