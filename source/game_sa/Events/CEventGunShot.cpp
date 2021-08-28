#include "StdInc.h"

float& CEventGunShot::ms_fGunShotSenseRangeForRiot2 = *(float*)0x8A625C;

void CEventGunShot::InjectHooks()
{
    HookInstall(0x4AC610, &CEventGunShot::Constructor);
    HookInstall(0x4B2CD0, &CEventGunShot::AffectsPed_Reversed);
    HookInstall(0x4AC810, &CEventGunShot::IsCriminalEvent_Reversed);
    HookInstall(0x4AC780, &CEventGunShot::TakesPriorityOver_Reversed);
    HookInstall(0x4B6B20, &CEventGunShot::CloneEditable_Reversed);
}

CEventGunShot::CEventGunShot(CEntity* entity, CVector startPoint, CVector endPoint, bool bHasNoSound)
{
    m_startPoint = startPoint;
    m_endPoint = endPoint;
    m_entity = entity;
    m_bHasNoSound = bHasNoSound;
    if (m_entity)
        m_entity->RegisterReference(&m_entity);
}

CEventGunShot::~CEventGunShot()
{
    if (m_entity)
        m_entity->CleanUpOldReference(&m_entity);
}

CEventGunShot* CEventGunShot::Constructor(CEntity* entity, CVector startPoint, CVector endPoint, bool bHasNoSound)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventGunShot*, 0x4AC610, CEvent*, CEntity*, CVector, CVector, bool>
        (this, entity, startPoint, endPoint, bHasNoSound);
#else
    this->CEventGunShot::CEventGunShot(entity, startPoint, endPoint, bHasNoSound);
    return this;
#endif
}

bool CEventGunShot::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B2CD0, CEvent*, CPed*>(this, ped);
#else
    return CEventGunShot::AffectsPed_Reversed(ped);
#endif
}

bool CEventGunShot::IsCriminalEvent()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4AC810, CEvent*>(this);
#else
    return CEventGunShot::IsCriminalEvent_Reversed();
#endif
}

bool CEventGunShot::TakesPriorityOver(CEvent* refEvent)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4AC780, CEvent*, CEvent*>(this, refEvent);
#else
    return CEventGunShot::TakesPriorityOver_Reversed(refEvent);
#endif
}

CEventEditableResponse* CEventGunShot::CloneEditable()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventEditableResponse*, 0x4B6B20, CEvent*>(this);
#else
    return CEventGunShot::CloneEditable_Reversed();
#endif
}


bool CEventGunShot::AffectsPed_Reversed(CPed* ped)
{
    if (!m_entity)
        return false;
    if (m_entity->m_nType == ENTITY_TYPE_PED && CPedGroups::AreInSameGroup(ped, static_cast<CPed*>(m_entity)))
        return false;
    if (!ped->IsInVehicleThatHasADriver()) {
        CWanted* playerWanted = FindPlayerWanted(-1);
        if (ped->m_nPedType == PED_TYPE_COP && playerWanted->m_nWantedLevel > 0) {
            CCopPed* cop = static_cast<CCopPed*>(ped);
            if (playerWanted->IsInPursuit(cop) || playerWanted->CanCopJoinPursuit(cop)) {
                if (m_entity != FindPlayerPed(-1))
                    return false;
            }
        }
        if (ped->IsAlive() && ped != m_entity && !ped->IsPlayer()) {
            float fGunShotRange = 45.0f;
            if (CEventGunShot::ms_fGunShotSenseRangeForRiot2 <= 0.0f) {
                if (ped->m_nCreatedBy == PED_MISSION)
                    fGunShotRange = ped->GetIntelligence()->GetPedFOVRange();
            }
            else if (ped->m_nCreatedBy == PED_MISSION) {
                fGunShotRange = CEventGunShot::ms_fGunShotSenseRangeForRiot2;
            }
            CVector distance = ped->GetPosition() - m_entity->GetPosition();
            if (distance .SquaredMagnitude() <= fGunShotRange * fGunShotRange) {
                if (!m_bHasNoSound)
                    return true;
                CVector distance = m_startPoint - ped->GetPosition();
                if (DotProduct(distance, ped->GetForward()) > 0.0f) {
                    if (CWorld::GetIsLineOfSightClear(m_startPoint, ped->GetPosition(), true, true, true, true, true, false, false))
                        return true;
                }
            }
        }
    }
    return false;
}

bool CEventGunShot::IsCriminalEvent_Reversed()
{
    return m_entity && m_entity->m_nType == ENTITY_TYPE_PED && static_cast<CPed*>(m_entity)->IsPlayer();
}

bool CEventGunShot::TakesPriorityOver_Reversed(CEvent* refEvent)
{
    if (refEvent->GetEventType() == GetEventType()) {
        bool bIsPlayer = false;
        bool otherPedIsPlayer = false;
        auto refEventGunShot = static_cast<CEventGunShot*>(refEvent);
        CPed* ped = static_cast<CPed*>(m_entity);
        if (m_entity && m_entity->m_nType == ENTITY_TYPE_PED)
            bIsPlayer = ped->IsPlayer();
        CPed* otherPed = static_cast<CPed*>(refEventGunShot->m_entity);
        if (otherPed && otherPed->m_nType == ENTITY_TYPE_PED) 
            otherPedIsPlayer = otherPed->IsPlayer();
        return bIsPlayer && !otherPedIsPlayer;
    }
    return GetEventPriority() >= refEvent->GetEventPriority();
}

CEventEditableResponse* CEventGunShot::CloneEditable_Reversed()
{
    return new CEventGunShot(m_entity, m_startPoint, m_endPoint, m_bHasNoSound);
}
