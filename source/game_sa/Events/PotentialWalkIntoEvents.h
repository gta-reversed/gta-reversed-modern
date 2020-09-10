#pragma once
#include "CEventEditableResponse.h"

class CVehicle;
class CEventPotentialWalkIntoVehicle : public CEventEditableResponse {
public:
    CVehicle* m_vehicle;
    std::int32_t m_moveState;

    static void InjectHooks();

    CEventPotentialWalkIntoVehicle(CVehicle* vehicle, std::int32_t moveState);
    ~CEventPotentialWalkIntoVehicle();
private:
    CEventPotentialWalkIntoVehicle* Constructor(CVehicle* vehicle, std::int32_t moveState);
public:
    eEventType GetEventType() override { return EVENT_POTENTIAL_WALK_INTO_VEHICLE; }
    bool TakesPriorityOver(CEvent* refEvent) override { return true; }
    CEventPotentialWalkIntoVehicle* CloneEditable() override { return new CEventPotentialWalkIntoVehicle(m_vehicle, m_moveState); }
    std::int32_t GetEventPriority() override { return 29; }
    std::int32_t GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
private:
    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventPotentialWalkIntoVehicle, 0x1C);

class CObject;
class CEventPotentialWalkIntoObject : public CEventEditableResponse {
public:
    CObject* m_object;
    std::int32_t m_moveState;

    static void InjectHooks();

    CEventPotentialWalkIntoObject(CObject* object, std::int32_t moveState);
    ~CEventPotentialWalkIntoObject();
private:
    CEventPotentialWalkIntoObject* Constructor(CObject* object, std::int32_t moveState);
public:
    eEventType GetEventType() override { return EVENT_POTENTIAL_WALK_INTO_OBJECT; }
    bool TakesPriorityOver(CEvent* refEvent) override { return true; }
    CEventPotentialWalkIntoObject* CloneEditable() override { return new CEventPotentialWalkIntoObject(m_object, m_moveState); }
    std::int32_t GetEventPriority() override { return 27; }
    std::int32_t GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
private:
    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventPotentialWalkIntoObject, 0x1C);
