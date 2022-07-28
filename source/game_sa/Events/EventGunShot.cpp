#include "StdInc.h"

#include "EventGunShot.h"

float& CEventGunShot::ms_fGunShotSenseRangeForRiot2 = *(float*)0x8A625C;

void CEventGunShot::InjectHooks() {
    RH_ScopedClass(CEventGunShot);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AC610);
    RH_ScopedVirtualInstall(AffectsPed, 0x4B2CD0);
    RH_ScopedVirtualInstall(IsCriminalEvent, 0x4AC810);
    RH_ScopedVirtualInstall(TakesPriorityOver, 0x4AC780);
    RH_ScopedVirtualInstall(CloneEditable, 0x4B6B20);
}

CEventGunShot* CEventGunShot::Constructor(CEntity* entity, CVector startPoint, CVector endPoint, bool bHasNoSound) { this->CEventGunShot::CEventGunShot(entity, startPoint, endPoint, bHasNoSound); return this; }
bool CEventGunShot::AffectsPed(CPed* ped) { return CEventGunShot::AffectsPed_Reversed(ped); }
bool CEventGunShot::IsCriminalEvent() { return CEventGunShot::IsCriminalEvent_Reversed(); }
bool CEventGunShot::TakesPriorityOver(const CEvent& refEvent) { return CEventGunShot::TakesPriorityOver_Reversed(refEvent); }
CEventEditableResponse* CEventGunShot::CloneEditable() { return CEventGunShot::CloneEditable_Reversed(); }

// 0x4AC610
CEventGunShot::CEventGunShot(CEntity* entity, CVector startPoint, CVector endPoint, bool bHasNoSound) : CEventEditableResponse() {
    m_startPoint = startPoint;
    m_endPoint = endPoint;
    m_entity = entity;
    m_bHasNoSound = bHasNoSound;
    CEntity::SafeRegisterRef(m_entity);
}

CEventGunShot::~CEventGunShot() {
    CEntity::SafeCleanUpRef(m_entity);
}

// 0x4B2CD0
bool CEventGunShot::AffectsPed_Reversed(CPed* ped) {
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
                if (ped->IsCreatedByMission()) {
                    fGunShotRange = ped->GetIntelligence()->GetPedFOVRange();
                }
            } else if (ped->IsCreatedByMission()) {
                fGunShotRange = CEventGunShot::ms_fGunShotSenseRangeForRiot2;
            }

            const auto& pedPos = ped->GetPosition();
            if (DistanceBetweenPointsSquared(m_entity->GetPosition(), pedPos) <= sq(fGunShotRange)) {
                if (!m_bHasNoSound)
                    return true;

                if (DotProduct(m_startPoint - pedPos, ped->GetForward()) > 0.0f) {
                    if (CWorld::GetIsLineOfSightClear(m_startPoint, pedPos, true, true, true, true, true, false, false))
                        return true;
                }
            }
        }
    }
    return false;
}

// 0x4AC810
bool CEventGunShot::IsCriminalEvent_Reversed() {
    return m_entity && m_entity->IsPed() && m_entity->AsPed()->IsPlayer();
}

// 0x4AC780
bool CEventGunShot::TakesPriorityOver_Reversed(const CEvent& refEvent) {
    if (refEvent.GetEventType() == GetEventType()) {
        bool bIsPlayer = false;
        bool otherPedIsPlayer = false;
        const auto refEventGunShot = static_cast<const CEventGunShot*>(&refEvent);
        if (m_entity && m_entity->AsPed()->IsPed()) {
            bIsPlayer = m_entity->AsPed()->IsPlayer();
        }

        CPed* otherPed = refEventGunShot->m_entity->AsPed();
        if (otherPed && otherPed->IsPed())
            otherPedIsPlayer = otherPed->IsPlayer();

        return bIsPlayer && !otherPedIsPlayer;
    }
    return GetEventPriority() >= refEvent.GetEventPriority();
}

// 0x4B6B20
CEventEditableResponse* CEventGunShot::CloneEditable_Reversed() {
    return new CEventGunShot(m_entity, m_startPoint, m_endPoint, m_bHasNoSound);
}
