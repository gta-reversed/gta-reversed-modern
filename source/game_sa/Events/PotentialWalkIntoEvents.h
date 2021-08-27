#pragma once
#include "CEventEditableResponse.h"
#include "CVector.h"

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
    eEventType GetEventType() const override { return EVENT_POTENTIAL_WALK_INTO_VEHICLE; }
    bool TakesPriorityOver(const CEvent& refEvent) override { return true; }
    CEventPotentialWalkIntoVehicle* CloneEditable() override { return new CEventPotentialWalkIntoVehicle(m_vehicle, m_moveState); }
    int32_t GetEventPriority() const override { return 29; }
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
    eEventType GetEventType() const override { return EVENT_POTENTIAL_WALK_INTO_OBJECT; }
    bool TakesPriorityOver(const CEvent& refEvent) override { return true; }
    CEventPotentialWalkIntoObject* CloneEditable() override { return new CEventPotentialWalkIntoObject(m_object, m_moveState); }
    int32_t GetEventPriority() const override { return 27; }
    std::int32_t GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
private:
    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventPotentialWalkIntoObject, 0x1C);

class CEventPotentialWalkIntoFire : public CEventEditableResponse {
public:
    CVector m_firePos;
    float m_fireSize;
    float m_radius;
    std::int32_t m_moveState;

    static void InjectHooks();

    CEventPotentialWalkIntoFire(CVector* firePos, float fireSize, std::int32_t moveState);
    ~CEventPotentialWalkIntoFire() {}
private:
    CEventPotentialWalkIntoFire* Constructor(CVector* firePos, float fireSize, std::int32_t moveState);
public:
    eEventType GetEventType() const override { return EVENT_POTENTIAL_WALK_INTO_FIRE; }
    int32_t GetEventPriority() const override { return 31; }
    std::int32_t GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    CEventPotentialWalkIntoFire* CloneEditable() override { return new CEventPotentialWalkIntoFire(&m_firePos, m_fireSize, m_moveState); }
private:
    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventPotentialWalkIntoFire, 0x2C);


class CEventPotentialWalkIntoPed : public CEventEditableResponse {
public:
    CVector m_targetPoint;
    CPed* m_ped;
    std::int32_t m_moveState;

    static void InjectHooks();

    CEventPotentialWalkIntoPed(CPed* ped, CVector* targetPoint, std::int32_t moveState);
    ~CEventPotentialWalkIntoPed();
private:
    CEventPotentialWalkIntoPed* Constructor(CPed* ped, CVector* targetPoint, std::int32_t moveState);
public:
    eEventType GetEventType() const override { return EVENT_POTENTIAL_WALK_INTO_PED; }
    int32_t GetEventPriority() const override { return 28; }
    std::int32_t GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    CEntity* GetSourceEntity() const override { return m_ped; }
    bool TakesPriorityOver(const CEvent& refEvent) override;
    CEventPotentialWalkIntoPed* CloneEditable() override { return new CEventPotentialWalkIntoPed(m_ped, &m_targetPoint, m_moveState); }
private:
    bool AffectsPed_Reversed(CPed* ped);
    bool TakesPriorityOver_Reversed(const CEvent& refEvent);
};

VALIDATE_SIZE(CEventPotentialWalkIntoPed, 0x28);

