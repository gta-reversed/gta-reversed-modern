#pragma once

#include "Event.h"

class NOTSA_EXPORT_VTABLE CEventCreatePartnerTask : public CEvent {
public:
    int32 m_randomNumber;
    CPed* m_partner;
    bool  m_leadSpeaker;
    float m_distanceMultiplier;

public:
    CEventCreatePartnerTask(int32 randomNumber, CPed* partner, bool leadSpeaker, float distanceMultiplier);
    ~CEventCreatePartnerTask() override;

    eEventType GetEventType() const override { return EVENT_CREATE_PARTNER_TASK; }
    int32 GetEventPriority() const override { return 6; }
    int32 GetLifeTime() override { return 0; }
    CEvent* Clone() override { return new CEventCreatePartnerTask(m_randomNumber, m_partner, m_leadSpeaker, m_distanceMultiplier); }
    bool AffectsPed(CPed* ped) override { return true; }
};
VALIDATE_SIZE(CEventCreatePartnerTask, 0x1C);
