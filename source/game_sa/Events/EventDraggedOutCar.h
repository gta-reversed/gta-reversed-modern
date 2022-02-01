#pragma once

#include "EventEditableResponse.h"

class CVehicle;
class CEntity;
class CPed;

class CEventDraggedOutCar : public CEventEditableResponse {
public:
    CPed*     m_carjacker;
    CVehicle* m_vehicle;
    bool      m_IsDriverSeat;

public:
    CEventDraggedOutCar(CVehicle* vehicle, CPed* carjacker, bool IsDriverSeat);
    ~CEventDraggedOutCar();

    eEventType GetEventType() const override { return EVENT_DRAGGED_OUT_CAR; }
    int32 GetEventPriority() const override { return 40; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    bool AffectsPedGroup(CPedGroup* pedGroup) override;
    CEntity* GetSourceEntity() const override { return m_carjacker; }
    float GetLocalSoundLevel() override { return 100.0f; }
    CEventEditableResponse* CloneEditable() override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventDraggedOutCar* Constructor(CVehicle* vehicle, CPed* carjacker, bool IsDriverSeat);
    CEventEditableResponse* CloneEditable_Reversed();
};

VALIDATE_SIZE(CEventDraggedOutCar, 0x20);
