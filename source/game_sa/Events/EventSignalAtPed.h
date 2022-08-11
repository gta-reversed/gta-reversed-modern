#pragma once

#include "Event.h"

class CEventSignalAtPed : public CEvent {
public:
    CPed* m_Ped;
    int32 m_f10;
    int8  m_f14;

public:
    CEventSignalAtPed(CPed* ped, int32 a, int8 b);
   ~CEventSignalAtPed() override;

   eEventType GetEventType() const override { return EVENT_SIGNAL_AT_PED; }
   int32 GetEventPriority() const override { return 10; }
   int32 GetLifeTime() override { return 0; }
   bool AffectsPed(CPed* ped) override;
   CEvent* Clone() override { return new CEventSignalAtPed(m_Ped, m_f10, m_f14); }
   bool IsValid(CPed* ped) override;
};
