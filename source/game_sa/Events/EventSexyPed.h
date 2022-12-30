#pragma once

#include "EventEditableResponse.h"

class CEventSexyPed : public CEventEditableResponse {
public:
    CPed* m_Ped;

public:
    CEventSexyPed(CPed* ped);
    ~CEventSexyPed() override;

    eEventType GetEventType() const override { return EVENT_SEXY_PED; }
    int32 GetEventPriority() const override { return 4; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    CEntity* GetSourceEntity() const override { return m_Ped; }
    CEventEditableResponse* CloneEditable() override { return new CEventSexyPed(m_Ped); }
};
VALIDATE_SIZE(CEventSexyPed, 0x18);
