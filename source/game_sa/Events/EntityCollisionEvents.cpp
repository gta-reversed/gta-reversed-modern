#include "StdInc.h"

#include "EntityCollisionEvents.h"

#include "TaskComplexAvoidOtherPedWhileWandering.h"
#include "TaskComplexKillPedOnFoot.h"
#include "EventKnockOffBike.h"

void CEventPedCollisionWithPed::InjectHooks()
{
    RH_ScopedClass(CEventPedCollisionWithPed);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AC990);
    RH_ScopedVirtualInstall(TakesPriorityOver, 0x4ACAD0);
    RH_ScopedVirtualInstall(AffectsPed, 0x4ACB10);
}

void CEventPedCollisionWithPlayer::InjectHooks()
{
    RH_ScopedClass(CEventPedCollisionWithPlayer);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x5FED40);
}

void CEventPlayerCollisionWithPed::InjectHooks()
{
    RH_ScopedClass(CEventPlayerCollisionWithPed);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x5FEE40);
}

void CEventObjectCollision::InjectHooks()
{
    RH_ScopedClass(CEventObjectCollision);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4ACCF0);
    RH_ScopedVirtualInstall(AffectsPed, 0x4ACE30);
}

void CEventBuildingCollision::InjectHooks()
{
    RH_ScopedClass(CEventBuildingCollision);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4ACF00);
    RH_ScopedVirtualInstall(AffectsPed, 0x4AD070);
    RH_ScopedInstall(IsHeadOnCollision, 0x4AD1E0);
    RH_ScopedInstall(CanTreatBuildingAsObject, 0x4B3120);
}

CEventPedCollisionWithPed::CEventPedCollisionWithPed(int16 pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState, int16 victimMoveState)
{
    m_pieceType               = pieceType;
    m_damageIntensity         = damageIntensity;
    m_victim                  = victim;
    m_collisionImpactVelocity = *collisionImpactVelocity;
    m_collisionPos            = *collisionPos;
    m_movestate               = moveState;
    m_victimMoveState         = victimMoveState;
    CEntity::SafeRegisterRef(m_victim);
}

CEventPedCollisionWithPed::~CEventPedCollisionWithPed()
{
    CEntity::SafeCleanUpRef(m_victim);
}

CEventPedCollisionWithPed* CEventPedCollisionWithPed::Constructor(int16 pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState, int16 victimMoveState)
{
    this->CEventPedCollisionWithPed::CEventPedCollisionWithPed(pieceType, damageIntensity, victim, collisionImpactVelocity, collisionPos, moveState, victimMoveState);
    return this;
}

// 0x4ACAD0
bool CEventPedCollisionWithPed::TakesPriorityOver(const CEvent& refEvent)
{
    return CEventPedCollisionWithPed::TakesPriorityOver_Reversed(refEvent);
}

// 0x4ACB10
bool CEventPedCollisionWithPed::AffectsPed(CPed* ped)
{
    return CEventPedCollisionWithPed::AffectsPed_Reversed(ped);
}

bool CEventPedCollisionWithPed::TakesPriorityOver_Reversed(const CEvent& refEvent)
{
    if (CEventHandler::IsTemporaryEvent(refEvent))
        return true;
    return CEvent::TakesPriorityOver(refEvent);
}

bool CEventPedCollisionWithPed::AffectsPed_Reversed(CPed* ped) {
    if (!ped->IsAlive() || ped->m_pAttachedTo || ped->bInVehicle) {
        return false;
    }

    if (!m_victim || m_victim->bInVehicle || ped->GetIntelligence()->IsThreatenedBy(*m_victim) || m_victim->GetIntelligence()->m_AnotherStaticCounter > 30) {
        return false;
    }

    switch (m_movestate) {
    case PEDMOVE_NONE:
    case PEDMOVE_STILL:
    case PEDMOVE_TURN_L:
    case PEDMOVE_TURN_R:
        break;
    default:
        return false;
    }

    if (const auto victimsGroup = CPedGroups::GetPedsGroup(m_victim); !victimsGroup || victimsGroup->GetMembership().IsLeader(m_victim)) {
        return false;
    }

    if (DotProduct(m_collisionImpactVelocity, ped->GetForward()) > -0.5f) { // If collision's velocity is not in [-120, 120] - So basically, if coming from behind
        return false;
    }

    if (ped->GetTaskManager().IsFirstFoundTaskMatching<TASK_COMPLEX_PARTNER_DEAL, TASK_COMPLEX_PARTNER_GREET>(m_victim->GetTaskManager())) {
        return false;
    }
                
    if (const auto task = ped->GetTaskManager().GetActiveTaskAs<CTaskComplexAvoidOtherPedWhileWandering>()) {
        if (task->m_PedToAvoid == m_victim) {
            return false;
        }
    }

    if (const auto task = ped->GetTaskManager().Find<CTaskComplexKillPedOnFoot>()) {
        if (task->m_target == m_victim) {
            if (ped->GetTaskManager().Find<TASK_SIMPLE_FIGHT_CTRL>()) {
                return false;
            }
        }
    }

    return true;
}

CEventPedCollisionWithPlayer::CEventPedCollisionWithPlayer(int16 pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState, int16 victimMoveState) :
    CEventPedCollisionWithPed(pieceType, damageIntensity, victim, collisionImpactVelocity, collisionPos, moveState, victimMoveState)
{
}

CEventPedCollisionWithPlayer* CEventPedCollisionWithPlayer::Constructor(int16 pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState, int16 victimMoveState)
{
    this->CEventPedCollisionWithPlayer::CEventPedCollisionWithPlayer(pieceType, damageIntensity, victim, collisionImpactVelocity, collisionPos, moveState, victimMoveState);
    return this;
}

CEventPlayerCollisionWithPed::CEventPlayerCollisionWithPed(int16 pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState, int16 victimMoveState) :
    CEventPedCollisionWithPed(pieceType, damageIntensity, victim, collisionImpactVelocity, collisionPos, moveState, victimMoveState)
{
}

CEventPlayerCollisionWithPed* CEventPlayerCollisionWithPed::Constructor(int16 pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState, int16 victimMoveState)
{
    this->CEventPlayerCollisionWithPed::CEventPlayerCollisionWithPed(pieceType, damageIntensity, victim, collisionImpactVelocity, collisionPos, moveState, victimMoveState);
    return this;
}

CEventObjectCollision::CEventObjectCollision(int16 pieceType, float damageIntensity, CObject* object, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState)
{
    m_pieceType = pieceType;
    m_moveState = moveState;
    m_damageIntensity = damageIntensity;
    m_object = object;
    m_impactNormal = *collisionImpactVelocity;
    m_impactPos = *collisionPos;
    CEntity::SafeRegisterRef(m_object);
}

CEventObjectCollision::~CEventObjectCollision()
{
    CEntity::SafeCleanUpRef(m_object);
}

CEventObjectCollision* CEventObjectCollision::Constructor(int16 pieceType, float damageIntensity, CObject* object, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState)
{
    this->CEventObjectCollision::CEventObjectCollision(pieceType, damageIntensity, object, collisionImpactVelocity, collisionPos, moveState);
    return this;
}

// 0x4ACE30
bool CEventObjectCollision::AffectsPed(CPed* ped)
{
    return CEventObjectCollision::AffectsPed_Reversed(ped);
}

bool CEventObjectCollision::AffectsPed_Reversed(CPed* ped)
{
    if (!ped->m_pAttachedTo) {
        if (m_object && !m_object->physicalFlags.bDisableMoveForce) {
            if (!ped->IsPlayer() && ped->IsAlive()) 
                return true;
        }
    }
    return false;
}

CEventBuildingCollision::CEventBuildingCollision(int16 pieceType, float damageIntensity, CBuilding* building, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState)
{
    m_pieceType = pieceType;
    m_moveState = moveState;
    m_damageIntensity = damageIntensity;
    m_building = building;
    m_impactNormal = *collisionImpactVelocity;
    m_impactPos = *collisionPos;
    CEntity::SafeRegisterRef(m_building);
}

CEventBuildingCollision::~CEventBuildingCollision()
{
    CEntity::SafeCleanUpRef(m_building);
}

CEventBuildingCollision* CEventBuildingCollision::Constructor(int16 pieceType, float damageIntensity, CBuilding* building, CVector* collisionImpactVelocity, CVector* collisionPos, int16 moveState)
{
    this->CEventBuildingCollision::CEventBuildingCollision(pieceType, damageIntensity, building, collisionImpactVelocity, collisionPos, moveState);
    return this;
}

// 0x4AD070
bool CEventBuildingCollision::AffectsPed(CPed* ped)
{
    return CEventBuildingCollision::AffectsPed_Reversed(ped);
}

bool CEventBuildingCollision::AffectsPed_Reversed(CPed* ped)
{
    if (!ped->IsPlayer()
        && ped->IsAlive()
        && m_moveState != PEDMOVE_STILL
        && (m_impactNormal.z <= 0.707f || m_building->m_bIsTempBuilding)
        && !ped->m_pAttachedTo)
    {
        CVector direction(m_impactNormal.x, m_impactNormal.y, 0.0f);
        direction.Normalise();
        float dotProduct = DotProduct(direction, ped->GetForward());
        if (dotProduct <= -0.422f) {
            if (ped->GetEventHandler().GetCurrentEventType() == EVENT_BUILDING_COLLISION) {
                auto buildingColEvent = static_cast<CEventBuildingCollision*>(ped->GetEventHandlerHistory().GetCurrentEvent());
                if (buildingColEvent->m_building == m_building && dotProduct > -0.5f) 
                    return false;
            }
            // CEventPotentialWalkIntoBuilding doesn't even exist on PC
            assert (ped->GetEventHandler().GetCurrentEventType() != EVENT_POTENTIAL_WALK_INTO_BUILDING);
            if (dotProduct <= -0.5f && !ped->GetTaskManager().Find<TASK_COMPLEX_CLIMB>())
                return ped->GetEventHandler().GetCurrentEventType() != EVENT_GUN_AIMED_AT;
        }
    }
    return false;
}

// 0x4AD1E0
bool CEventBuildingCollision::IsHeadOnCollision(CPed* ped)
{
    CVector velocity = m_impactNormal;
    velocity.z = 0.0f;
    velocity.Normalise();
    return -DotProduct(velocity, ped->GetForward()) > 0.866f;
}

// 0x4B3120
bool CEventBuildingCollision::CanTreatBuildingAsObject(CBuilding* building)
{
    if (building->m_bIsTempBuilding)
        return true;

    CColModel* colModel = CModelInfo::GetModelInfo(building->m_nModelIndex)->GetColModel();
    CVector& boundMax = colModel->m_boundBox.m_vecMax;
    CVector& boundMin = colModel->m_boundBox.m_vecMin;
    float absoluteLengthX = fabs(boundMax.x - boundMin.x);
    float absoluteLengthY = fabs(boundMax.y - boundMin.y);
    float lengthZ = boundMax.z - boundMin.z;
    if (lengthZ < 2.0f && (absoluteLengthX < 6.0f || absoluteLengthY < 6.0f)
        || absoluteLengthX < 6.0f && absoluteLengthY < 6.0f)
    {
        return true;
    }
    return false;
}
