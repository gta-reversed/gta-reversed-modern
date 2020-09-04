#include "CEvent.h"
#include "CVector.h"

class CEventPedCollisionWithPed : public CEvent {
public:
    std::int16_t m_pieceType;
    char field_E[2];
    float m_damageIntensity;
    CPed* m_victim;
    CVector m_collisionImpactVelocity;
    CVector m_collisionPos;
    std::int16_t m_movestate; // see eMoveState
    std::int16_t m_victimMoveState; // see eMoveState

    static void InjectHooks();

    CEventPedCollisionWithPed(std::int16_t pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, std::int16_t moveState, std::int16_t victimMoveState);
    ~CEventPedCollisionWithPed();
private:
    CEventPedCollisionWithPed* Constructor(std::int16_t pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, std::int16_t moveState, std::int16_t victimMoveState);
public:
    eEventType GetEventType() override { return EVENT_PED_COLLISION_WITH_PED; };
    bool TakesPriorityOver(CEvent* refEvent) override;
    std::int32_t GetEventPriority() override { return 60; };
    std::int32_t GetLifeTime() override { return 0; };
    CEventPedCollisionWithPed* Clone() override { return new CEventPedCollisionWithPed(m_pieceType, m_damageIntensity, m_victim, &m_collisionImpactVelocity, &m_collisionPos, m_movestate, m_victimMoveState); };
    bool AffectsPed(CPed* ped) override;
private:
    bool TakesPriorityOver_Reversed(CEvent* refEvent);
    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventPedCollisionWithPed, 0x34);

class CEventPedCollisionWithPlayer : public CEventPedCollisionWithPed {
public:
    static void InjectHooks();

    CEventPedCollisionWithPlayer(std::int16_t pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, std::int16_t moveState, std::int16_t victimMoveState);
    ~CEventPedCollisionWithPlayer() {};
private:
    CEventPedCollisionWithPlayer* Constructor(std::int16_t pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, std::int16_t moveState, std::int16_t victimMoveState);
public:
    eEventType GetEventType() override { return EVENT_PED_COLLISION_WITH_PLAYER; }
    CEventPedCollisionWithPlayer* Clone() override { return new CEventPedCollisionWithPlayer(m_pieceType, m_damageIntensity, m_victim, &m_collisionImpactVelocity, &m_collisionPos, m_movestate, m_victimMoveState); };
};

VALIDATE_SIZE(CEventPedCollisionWithPlayer, 0x34);

class CEventPlayerCollisionWithPed : public CEventPedCollisionWithPed {
public:
    static void InjectHooks();

    CEventPlayerCollisionWithPed(std::int16_t pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, std::int16_t moveState, std::int16_t victimMoveState);
    ~CEventPlayerCollisionWithPed() {}
private:
    CEventPlayerCollisionWithPed* Constructor(std::int16_t pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, std::int16_t moveState, std::int16_t victimMoveState);
public:
    eEventType GetEventType() override { return EVENT_PLAYER_COLLISION_WITH_PED; }
    CEventPlayerCollisionWithPed* Clone() override { return new CEventPlayerCollisionWithPed(m_pieceType, m_damageIntensity, m_victim, &m_collisionImpactVelocity, &m_collisionPos, m_movestate, m_victimMoveState); }
};

VALIDATE_SIZE(CEventPlayerCollisionWithPed, 0x34);
