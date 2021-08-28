#include "CEvent.h"

class CEventInWater : public CEvent
{
public:
    float m_acceleration;

    static void InjectHooks();

    CEventInWater(float acceleration);
    ~CEventInWater() {};
private:
    CEventInWater* Constructor(float acceleration);
public:
    eEventType GetEventType() override { return EVENT_IN_WATER; }
    int GetEventPriority() override { return 62; }
    int GetLifeTime() override { return 0; }
    CEvent* Clone() override { return new CEventInWater(m_acceleration); }
    bool AffectsPed(CPed* ped) override;
    bool TakesPriorityOver(CEvent* refEvent) override;

    bool AffectsPed_Reversed(CPed* ped);
    bool TakesPriorityOver_Reversed(CEvent* refEvent);
};

VALIDATE_SIZE(CEventInWater, 0x10);
