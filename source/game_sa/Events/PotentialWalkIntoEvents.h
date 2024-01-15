#pragma once

#include "EventEditableResponse.h"
#include "Vector.h"
#include "Enums/eMoveState.h"

class CObject;
class CVehicle;

class CEventPotentialWalkIntoVehicle : public CEventEditableResponse {
public:
    CVehicle* m_vehicle;
    int32     m_moveState;

public:
    CEventPotentialWalkIntoVehicle(CVehicle* vehicle, int32 moveState);
    ~CEventPotentialWalkIntoVehicle() override;

    eEventType GetEventType() const override { return EVENT_POTENTIAL_WALK_INTO_VEHICLE; }
    bool TakesPriorityOver(const CEvent& refEvent) override { return true; }
    CEventPotentialWalkIntoVehicle* CloneEditable() override { return new CEventPotentialWalkIntoVehicle(m_vehicle, m_moveState); }
    int32 GetEventPriority() const override { return 29; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventPotentialWalkIntoVehicle* Constructor(CVehicle* vehicle, int32 moveState);

    bool AffectsPed_Reversed(CPed* ped);
};
VALIDATE_SIZE(CEventPotentialWalkIntoVehicle, 0x1C);

class CEventPotentialWalkIntoObject : public CEventEditableResponse {
public:
    CObject* m_object;
    int32 m_moveState;

public:
    CEventPotentialWalkIntoObject(CObject* object, int32 moveState);
    ~CEventPotentialWalkIntoObject() override;

    eEventType GetEventType() const override { return EVENT_POTENTIAL_WALK_INTO_OBJECT; }
    bool TakesPriorityOver(const CEvent& refEvent) override { return true; }
    CEventPotentialWalkIntoObject* CloneEditable() override { return new CEventPotentialWalkIntoObject(m_object, m_moveState); }
    int32 GetEventPriority() const override { return 27; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventPotentialWalkIntoObject* Constructor(CObject* object, int32 moveState);

    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventPotentialWalkIntoObject, 0x1C);

class CEventPotentialWalkIntoFire : public CEventEditableResponse {
public:
    CVector m_firePos;
    float m_fireSize;
    float m_radius;
    eMoveState m_moveState;

public:
    CEventPotentialWalkIntoFire(const CVector& firePos, float fireSize, eMoveState moveState);
    ~CEventPotentialWalkIntoFire() override = default;

    eEventType GetEventType() const override { return EVENT_POTENTIAL_WALK_INTO_FIRE; }
    int32 GetEventPriority() const override { return 31; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    CEventPotentialWalkIntoFire* CloneEditable() override { return new CEventPotentialWalkIntoFire(&m_firePos, m_fireSize, m_moveState); }

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventPotentialWalkIntoFire* Constructor(const CVector& firePos, float fireSize, eMoveState moveState);

    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventPotentialWalkIntoFire, 0x2C);


class CEventPotentialWalkIntoPed : public CEventEditableResponse {
public:
    CVector    m_targetPoint;
    CPed*      m_ped;
    eMoveState m_moveState;

public:
    CEventPotentialWalkIntoPed(CPed* ped, const CVector& targetPoint, eMoveState moveState);
    ~CEventPotentialWalkIntoPed() override;

    eEventType GetEventType() const override { return EVENT_POTENTIAL_WALK_INTO_PED; }
    int32 GetEventPriority() const override { return 28; }
    int32 GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    CEntity* GetSourceEntity() const override { return m_ped; }
    bool TakesPriorityOver(const CEvent& refEvent) override;
    CEventPotentialWalkIntoPed* CloneEditable() override { return new CEventPotentialWalkIntoPed(m_ped, &m_targetPoint, m_moveState); }

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventPotentialWalkIntoPed* Constructor(CPed* ped, const CVector& targetPoint, eMoveState moveState) {
        this->CEventPotentialWalkIntoPed::CEventPotentialWalkIntoPed(ped, targetPoint, moveState);
        return this;
    }

    bool AffectsPed_Reversed(CPed* ped);
    bool TakesPriorityOver_Reversed(const CEvent& refEvent);
};

VALIDATE_SIZE(CEventPotentialWalkIntoPed, 0x28);
