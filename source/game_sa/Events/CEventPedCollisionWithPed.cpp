#include "StdInc.h"

void CEventPedCollisionWithPed::InjectHooks()
{
    HookInstall(0x4AC990, &CEventPedCollisionWithPed::Constructor);
    HookInstall(0x4ACAD0, &CEventPedCollisionWithPed::TakesPriorityOver_Reversed);
    HookInstall(0x4ACB10, &CEventPedCollisionWithPed::AffectsPed_Reversed);
}

void CEventPedCollisionWithPlayer::InjectHooks()
{
    HookInstall(0x5FED40, &CEventPedCollisionWithPlayer::Constructor);
}

void CEventPlayerCollisionWithPed::InjectHooks()
{
    HookInstall(0x5FEE40, &CEventPlayerCollisionWithPed::Constructor);
}

CEventPedCollisionWithPed::CEventPedCollisionWithPed(std::int16_t pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, std::int16_t moveState, std::int16_t victimMoveState)
{
    m_pieceType = pieceType;
    m_damageIntensity = damageIntensity;
    m_victim = victim;
    m_collisionImpactVelocity = *collisionImpactVelocity;
    m_collisionPos = *collisionPos;
    m_movestate = moveState;
    m_victimMoveState = victimMoveState;
    if (victim)
        victim->RegisterReference(reinterpret_cast<CEntity**>(&m_victim));
}

CEventPedCollisionWithPed::~CEventPedCollisionWithPed()
{
}

CEventPedCollisionWithPed* CEventPedCollisionWithPed::Constructor(std::int16_t pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, std::int16_t moveState, std::int16_t victimMoveState)
{
    this->CEventPedCollisionWithPed::CEventPedCollisionWithPed(pieceType, damageIntensity, victim, collisionImpactVelocity, collisionPos, moveState, victimMoveState);
    return this;
}

bool CEventPedCollisionWithPed::TakesPriorityOver(CEvent* refEvent)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4ACAD0, CEventPedCollisionWithPed*, CEvent*>(this, refEvent);
#else
    return CEventPedCollisionWithPed::TakesPriorityOver_Reversed(refEvent);
#endif
}

bool CEventPedCollisionWithPed::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4ACB10, CEventPedCollisionWithPed*, CPed*>(this, ped);
#else
    return CEventPedCollisionWithPed::AffectsPed_Reversed(ped);
#endif
}

bool CEventPedCollisionWithPed::TakesPriorityOver_Reversed(CEvent* refEvent)
{
    if (CEventHandler::IsTemporaryEvent(refEvent))
        return true;
    return CEvent::TakesPriorityOver(refEvent);
}

bool CEventPedCollisionWithPed::AffectsPed_Reversed(CPed* ped)
{
    if (ped->IsAlive() && !ped->m_pAttachedTo && m_victim && !ped->bInVehicle && !m_victim->bInVehicle &&
        m_victim->GetIntelligence()->m_AnotherStaticCounter <= 30 && !ped->GetIntelligence()->IsThreatenedBy(*m_victim)) {
        if (m_movestate < PEDMOVE_WALK) {
            CPedGroup* victimGroup = CPedGroups::GetPedsGroup(m_victim);
            if (victimGroup && !victimGroup->GetMembership().IsLeader(m_victim)) {
                if (DotProduct(m_collisionImpactVelocity, ped->GetForward()) > -0.5f)
                    return false;
                CTask* pedPartnerTask = ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_PARTNER_DEAL);
                if (!pedPartnerTask)
                    pedPartnerTask = ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_PARTNER_GREET);
                if (pedPartnerTask) {
                    CTask* victimPartnerTask = m_victim->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_PARTNER_DEAL);
                    if (!victimPartnerTask)
                        victimPartnerTask = m_victim->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_PARTNER_GREET);
                    if (victimPartnerTask) {
                        if (pedPartnerTask->GetId() == victimPartnerTask->GetId())
                            return false;
                    }
                }
                CTask* pedActiveTask = ped->GetTaskManager().GetActiveTask();
                if (pedActiveTask && pedActiveTask->GetId() == TASK_COMPLEX_AVOID_OTHER_PED_WHILE_WANDERING
                    && reinterpret_cast<CTaskComplexAvoidOtherPedWhileWandering*>(pedActiveTask)->m_ped == m_victim)
                {
                    return false;
                }
                auto pTaskKillPedOnFoot = reinterpret_cast<CTaskComplexKillPedOnFoot*>(ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_KILL_PED_ON_FOOT));
                if (pTaskKillPedOnFoot && pTaskKillPedOnFoot->m_pTarget == m_victim
                    && ped->GetTaskManager().FindActiveTaskByType(TASK_SIMPLE_FIGHT_CTRL)) {
                    return false;
                }
                else {
                    return true;
                }
            }
        }
    }
    return false;
}

CEventPedCollisionWithPlayer::CEventPedCollisionWithPlayer(std::int16_t pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, std::int16_t moveState, std::int16_t victimMoveState) :
    CEventPedCollisionWithPed(pieceType, damageIntensity, victim, collisionImpactVelocity, collisionPos, moveState, victimMoveState)
{
}

CEventPedCollisionWithPlayer* CEventPedCollisionWithPlayer::Constructor(std::int16_t pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, std::int16_t moveState, std::int16_t victimMoveState)
{
    this->CEventPedCollisionWithPlayer::CEventPedCollisionWithPlayer(pieceType, damageIntensity, victim, collisionImpactVelocity, collisionPos, moveState, victimMoveState);
    return this;
}

CEventPlayerCollisionWithPed::CEventPlayerCollisionWithPed(std::int16_t pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, std::int16_t moveState, std::int16_t victimMoveState) :
    CEventPedCollisionWithPed(pieceType, damageIntensity, victim, collisionImpactVelocity, collisionPos, moveState, victimMoveState)
{
}

CEventPlayerCollisionWithPed* CEventPlayerCollisionWithPed::Constructor(std::int16_t pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, std::int16_t moveState, std::int16_t victimMoveState)
{
    this->CEventPlayerCollisionWithPed::CEventPlayerCollisionWithPed(pieceType, damageIntensity, victim, collisionImpactVelocity, collisionPos, moveState, victimMoveState);
    return this;
}
