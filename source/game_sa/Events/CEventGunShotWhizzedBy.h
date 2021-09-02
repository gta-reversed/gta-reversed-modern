#pragma once

#include "CEventGunShot.h"

class CEventGunShotWhizzedBy : public CEventGunShot {
public:
    static void InjectHooks();

    CEventGunShotWhizzedBy(CEntity* entity, CVector const& startPoint, CVector const& endPoint, bool bHasNoSound);
    ~CEventGunShotWhizzedBy() {};
private:
    CEventGunShotWhizzedBy* Constructor(CEntity* entity, CVector const& startPoint, CVector const& endPoint, bool bHasNoSound);
public:
    eEventType GetEventType() const override { return EVENT_SHOT_FIRED_WHIZZED_BY; }
    int32_t GetEventPriority() const override { return 36; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    bool CanBeInterruptedBySameEvent() override { return true; }
    CEventEditableResponse* CloneEditable() override { return new CEventGunShotWhizzedBy(m_entity, m_startPoint, m_endPoint, m_bHasNoSound); }

    bool AffectsPed_Reversed(CPed* ped);
};
