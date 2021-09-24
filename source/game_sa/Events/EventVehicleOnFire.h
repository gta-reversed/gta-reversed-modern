#pragma once

#include "CEventEditableResponse.h"

class CVehicle;

class CEventVehicleOnFire : public CEventEditableResponse {
public:
    CVehicle* m_vehicle;

    static void InjectHooks();

    CEventVehicleOnFire(CVehicle* vehicle);
    ~CEventVehicleOnFire();
private:
    CEventVehicleOnFire* Constructor(CVehicle* vehicle);
public:
    eEventType GetEventType() const override { return EVENT_VEHICLE_ON_FIRE; }
    int32 GetEventPriority() const override { return 54; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    float GetLocalSoundLevel() override { return 60.0f; }
    CEventEditableResponse* CloneEditable() override;

    bool AffectsPed_Reversed(CPed* ped);
    CEventEditableResponse* CloneEditable_Reversed();
};

VALIDATE_SIZE(CEventVehicleOnFire, 0x18);
