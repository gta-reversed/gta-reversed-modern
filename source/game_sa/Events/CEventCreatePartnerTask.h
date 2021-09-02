#pragma once

#include "CEvent.h"

class CEventCreatePartnerTask : public CEvent {
public:
    int32 m_randomNumber;
    CPed* m_partner;
    bool  m_leadSpeaker;
    float m_distanceMultiplier;

public:
    static void InjectHooks();

    CEventCreatePartnerTask(int32 randomNumber, CPed* partner, bool leadSpeaker, float distanceMultiplier);
    ~CEventCreatePartnerTask();
private:
    CEventCreatePartnerTask* Constructor(int32 randomNumber, CPed* partner, bool leadSpeaker, float distanceMultiplier);
public:
    eEventType GetEventType() const override { return EVENT_CREATE_PARTNER_TASK; }
    int32_t GetEventPriority() const override { return 6; }
    int32 GetLifeTime() override { return 0; }
    CEvent* Clone() override { return new CEventCreatePartnerTask(m_randomNumber, m_partner, m_leadSpeaker, m_distanceMultiplier); }
    bool AffectsPed(CPed* ped) override { return true; }
};

VALIDATE_SIZE(CEventCreatePartnerTask, 0x1C);
