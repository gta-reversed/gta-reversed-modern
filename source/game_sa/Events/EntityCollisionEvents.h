#pragma once

#include "Event.h"
#include "Vector.h"

class CPed;
class CObject;

class CEventPedCollisionWithPed : public CEvent {
public:
    int16   m_pieceType;
    char    field_E[2];
    float   m_damageIntensity;
    CPed*   m_victim;
    CVector m_collisionImpactVelocity;
    CVector m_collisionPos;
    int16   m_movestate; // see eMoveState
    int16   m_victimMoveState; // see eMoveState

public:
    CEventPedCollisionWithPed(int16 pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState, int16 victimMoveState);
    ~CEventPedCollisionWithPed() override;

    eEventType GetEventType() const override { return EVENT_PED_COLLISION_WITH_PED; };
    bool TakesPriorityOver(const CEvent& refEvent) override;
    int32 GetEventPriority() const override { return 60; };
    int32 GetLifeTime() override { return 0; };
    CEventPedCollisionWithPed* Clone() override { return new CEventPedCollisionWithPed(m_pieceType, m_damageIntensity, m_victim, &m_collisionImpactVelocity, &m_collisionPos, m_movestate, m_victimMoveState); };
    bool AffectsPed(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CEventPedCollisionWithPed* Constructor(int16 pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState, int16 victimMoveState);

    bool TakesPriorityOver_Reversed(const CEvent& refEvent);
    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventPedCollisionWithPed, 0x34);

class CEventPedCollisionWithPlayer : public CEventPedCollisionWithPed {
public:
    CEventPedCollisionWithPlayer(int16 pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState, int16 victimMoveState);
    ~CEventPedCollisionWithPlayer() override = default;

    eEventType GetEventType() const override { return EVENT_PED_COLLISION_WITH_PLAYER; }
    CEventPedCollisionWithPlayer* Clone() override { return new CEventPedCollisionWithPlayer(m_pieceType, m_damageIntensity, m_victim, &m_collisionImpactVelocity, &m_collisionPos, m_movestate, m_victimMoveState); };

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventPedCollisionWithPlayer* Constructor(int16 pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState, int16 victimMoveState);
};

VALIDATE_SIZE(CEventPedCollisionWithPlayer, 0x34);

class CEventPlayerCollisionWithPed : public CEventPedCollisionWithPed {
public:
    CEventPlayerCollisionWithPed(int16 pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState, int16 victimMoveState);
    ~CEventPlayerCollisionWithPed() override = default;

    eEventType GetEventType() const override { return EVENT_PLAYER_COLLISION_WITH_PED; }
    CEventPlayerCollisionWithPed* Clone() override { return new CEventPlayerCollisionWithPed(m_pieceType, m_damageIntensity, m_victim, &m_collisionImpactVelocity, &m_collisionPos, m_movestate, m_victimMoveState); }

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventPlayerCollisionWithPed* Constructor(int16 pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState, int16 victimMoveState);
};

VALIDATE_SIZE(CEventPlayerCollisionWithPed, 0x34);

class CEventObjectCollision : public CEvent {
public:
    int16    m_pieceType;
    int16    m_moveState;
    float    m_damageIntensity;
    CObject* m_object;
    CVector  m_impactNormal;
    CVector  m_impactPos;

public:
    static void InjectHooks();

    CEventObjectCollision(int16 pieceType, float damageIntensity, CObject* object, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState);
    ~CEventObjectCollision() override;

    eEventType GetEventType() const override { return EVENT_OBJECT_COLLISION; }
    bool TakesPriorityOver(const CEvent& refEvent) override { return true; }
    int32 GetEventPriority() const override { return 57; }
    int32 GetLifeTime() override { return 0; }
    CEventObjectCollision* Clone() override { return new CEventObjectCollision(m_pieceType, m_damageIntensity, m_object, &m_impactNormal, &m_impactPos, m_moveState); }
    bool AffectsPed(CPed* ped) override;

private:
    CEventObjectCollision* Constructor(int16 pieceType, float damageIntensity, CObject* object, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState);
    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventObjectCollision, 0x30);

class CBuilding;

class CEventBuildingCollision : public CEvent {
public:
    uint16     m_pieceType;
    int16      m_moveState;
    float      m_damageIntensity;
    CBuilding* m_building;
    CVector    m_impactNormal;
    CVector    m_impactPos;

public:
    CEventBuildingCollision(uint16 pieceType, float damageIntensity, CBuilding* building, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState);
    ~CEventBuildingCollision() override;

    eEventType GetEventType() const override { return EVENT_BUILDING_COLLISION; }
    bool TakesPriorityOver(const CEvent& refEvent) override { return refEvent.GetEventType() != GetEventType(); }
    bool CanBeInterruptedBySameEvent() override { return true; }
    int32 GetEventPriority() const override { return 59; }
    int32 GetLifeTime() override { return 0; }
    CEventBuildingCollision* Clone() override { return new CEventBuildingCollision(m_pieceType, m_damageIntensity, m_building, &m_impactNormal, &m_impactPos, m_moveState); }
    bool AffectsPed(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventBuildingCollision* Constructor(int16 pieceType, float damageIntensity, CBuilding* building, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState);

    bool AffectsPed_Reversed(CPed* ped);
    bool IsHeadOnCollision(CPed* ped);
    static bool CanTreatBuildingAsObject(CBuilding* building);
};

VALIDATE_SIZE(CEventBuildingCollision, 0x30);
