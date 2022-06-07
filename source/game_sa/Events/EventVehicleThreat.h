#pragma once

class CEventEditableResponse;

class CEventVehicleThreat : public CEventEditableResponse {
public:
    CVehicle* m_Vehicle;

public:
    CEventVehicleThreat(CVehicle *vehicle);
    ~CEventVehicleThreat() override;

    eEventType GetEventType() const override { return EVENT_VEHICLE_THREAT; }
    int32 GetEventPriority() const override { return 19; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override { return ped->IsAlive(); }
    CEventEditableResponse* CloneEditable() override { return new CEventVehicleThreat(m_Vehicle); }
};
