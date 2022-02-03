#include "StdInc.h"

#include "EventGunShot.h"

float& CEventGunShot::ms_fGunShotSenseRangeForRiot2 = *(float*)0x8A625C;

void CEventGunShot::InjectHooks()
{
    RH_ScopedClass(CEventGunShot);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AC610);
    RH_ScopedInstall(AffectsPed_Reversed, 0x4B2CD0);
    RH_ScopedInstall(IsCriminalEvent_Reversed, 0x4AC810);
    RH_ScopedInstall(TakesPriorityOver_Reversed, 0x4AC780);
    RH_ScopedInstall(CloneEditable_Reversed, 0x4B6B20);
}

// 0x4AC610
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
    this->CEventGunShot::CEventGunShot(entity, startPoint, endPoint, bHasNoSound);
    return this;
}

// 0x4B2CD0
bool CEventGunShot::AffectsPed(CPed* ped)
{
    return CEventGunShot::AffectsPed_Reversed(ped);
}

// 0x4AC810
bool CEventGunShot::IsCriminalEvent()
{
    return CEventGunShot::IsCriminalEvent_Reversed();
}

// 0x4AC780
bool CEventGunShot::TakesPriorityOver(const CEvent& refEvent)
{
    return CEventGunShot::TakesPriorityOver_Reversed(refEvent);
}

// 0x4B6B20
CEventEditableResponse* CEventGunShot::CloneEditable()
{
    return CEventGunShot::CloneEditable_Reversed();
}

bool CEventGunShot::AffectsPed_Reversed(CPed* ped)
{
    if (!m_entity)
        return false;

    if (m_entity->IsPed() && CPedGroups::AreInSameGroup(ped, m_entity->AsPed()))
        return false;

    if (!ped->IsInVehicleThatHasADriver()) {
        CWanted* playerWanted = FindPlayerWanted();
        if (ped->m_nPedType == PED_TYPE_COP && playerWanted->m_nWantedLevel > 0) {
            CCopPed* cop = static_cast<CCopPed*>(ped);
            if (playerWanted->IsInPursuit(cop) || playerWanted->CanCopJoinPursuit(cop)) {
                if (m_entity != FindPlayerPed())
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

                CVector dist = m_startPoint - ped->GetPosition();
                if (DotProduct(dist, ped->GetForward()) > 0.0f) {
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
    return m_entity && m_entity->IsPed() && m_entity->AsPed()->IsPlayer();
}

bool CEventGunShot::TakesPriorityOver_Reversed(const CEvent& refEvent)
{
    if (refEvent.GetEventType() == GetEventType()) {
        bool bIsPlayer = false;
        bool otherPedIsPlayer = false;
        const auto refEventGunShot = static_cast<const CEventGunShot*>(&refEvent);
        CPed* ped = m_entity->AsPed();
        if (m_entity && m_entity->IsPed())
            bIsPlayer = ped->IsPlayer();

        CPed* otherPed = refEventGunShot->m_entity->AsPed();
        if (otherPed && otherPed->IsPed())
            otherPedIsPlayer = otherPed->IsPlayer();

        return bIsPlayer && !otherPedIsPlayer;
    }
    return GetEventPriority() >= refEvent.GetEventPriority();
}

CEventEditableResponse* CEventGunShot::CloneEditable_Reversed()
{
    return new CEventGunShot(m_entity, m_startPoint, m_endPoint, m_bHasNoSound);
}
