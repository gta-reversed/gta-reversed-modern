#include "CEvent.h"

class CEventDeath : public CEvent
{
    bool m_bDrowning;
private:
    char padding[3];
public:
    std::uint32_t m_deathTimeInMs;

    static void InjectHooks();

    CEventDeath(bool bDrowning);
    CEventDeath(bool bDrowning, unsigned int deathTimeInMs);
    ~CEventDeath();
private:
    CEventDeath* Constructor(bool bDrowning);
public:
    eEventType GetEventType() override { return EVENT_DEATH; }
    int GetEventPriority() override { return 73; }
    int GetLifeTime() override { return 0; }
    CEvent* Clone() override;
    bool AffectsPed(CPed* ped) override { return 1; }
    
    CEvent* Clone_Reversed();
};

VALIDATE_SIZE(CEventDeath, 0x14);
