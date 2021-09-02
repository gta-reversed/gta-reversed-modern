#include "CEvent.h"

class CEventInWater : public CEvent {
public:
    float m_acceleration;

    static void InjectHooks();

    CEventInWater(float acceleration);
    ~CEventInWater() {};
private:
    CEventInWater* Constructor(float acceleration);
public:
    eEventType GetEventType() const override { return EVENT_IN_WATER; }
    int32_t GetEventPriority() const override { return 62; }
    int32 GetLifeTime() override { return 0; }
    CEvent* Clone() override { return new CEventInWater(m_acceleration); }
    bool AffectsPed(CPed* ped) override;
    bool TakesPriorityOver(const CEvent& refEvent) override;

    bool AffectsPed_Reversed(CPed* ped);
    bool TakesPriorityOver_Reversed(const CEvent& refEvent);
};

VALIDATE_SIZE(CEventInWater, 0x10);
