#pragma once

#include "EventEditableResponse.h"

class CEventPedEnteredMyVehicle : public CEventEditableResponse {
    CPed*     m_Ped;
    CVehicle* m_Vehicle;
    int32     m_nUnk;

public:
    CEventPedEnteredMyVehicle(/*const*/ CPed* ped, /*const*/ CVehicle* vehicle, int32 nUnk); // todo: make const as OG
    ~CEventPedEnteredMyVehicle() override;

    eEventType GetEventType() const override { return EVENT_PED_ENTERED_MY_VEHICLE; }
    int32 GetEventPriority() const override { return 39; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    CEntity* GetSourceEntity() const override { return m_Ped; }
    float GetLocalSoundLevel() override { return 60.0f; }
    CEventEditableResponse* CloneEditable() override { return new CEventPedEnteredMyVehicle(m_Ped, m_Vehicle, m_nUnk); }
};
VALIDATE_SIZE(CEventPedEnteredMyVehicle, 0x20);
