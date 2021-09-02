#include "StdInc.h"

void CEventAcquaintancePed::InjectHooks()
{
    CEventAcquaintancePedHate::InjectHooks();
    CEventAcquaintancePedHateBadlyLit::InjectHooks();
    ReversibleHooks::Install("CEventAcquaintancePed", "Constructor", 0x4AF820, &CEventAcquaintancePed::Constructor);
    ReversibleHooks::Install("CEventAcquaintancePed", "AffectsPed_Reversed", 0x4AFA30, &CEventAcquaintancePed::AffectsPed_Reversed);
    ReversibleHooks::Install("CEventAcquaintancePed", "AffectsPedGroup_Reversed", 0x4AF970, &CEventAcquaintancePed::AffectsPedGroup_Reversed);
    ReversibleHooks::Install("CEventAcquaintancePed", "TakesPriorityOver_Reversed", 0x4AF8F0, &CEventAcquaintancePed::TakesPriorityOver_Reversed);
}

void CEventSeenCop::InjectHooks()
{
    ReversibleHooks::Install("CEventSeenCop", "CEventSeenCop", 0x5FF380, &CEventSeenCop::Constructor);
}

CEventAcquaintancePed::CEventAcquaintancePed(CPed* ped)
{
    m_ped = ped;
    if (m_ped)
        m_ped->RegisterReference(reinterpret_cast<CEntity**>(&m_ped));
}

CEventAcquaintancePed::~CEventAcquaintancePed()
{
    if (m_ped)
        m_ped->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_ped));
}

CEventAcquaintancePed* CEventAcquaintancePed::Constructor(CPed* ped)
{
    this->CEventAcquaintancePed::CEventAcquaintancePed(ped);
    return this;
}

// 0x4AFA30
bool CEventAcquaintancePed::AffectsPed(CPed* ped)
{
    return CEventAcquaintancePed::AffectsPed_Reversed(ped);
}

// 0x4AF970
bool CEventAcquaintancePed::AffectsPedGroup(CPedGroup* pedGroup)
{
    return CEventAcquaintancePed::AffectsPedGroup_Reversed(pedGroup);
}

// 0x4AF8F0
bool CEventAcquaintancePed::TakesPriorityOver(const CEvent& refEvent)
{
    return CEventAcquaintancePed::TakesPriorityOver_Reversed(refEvent);
}

bool CEventAcquaintancePed::AffectsPed_Reversed(CPed* ped)
{
    if (m_ped && !ped->m_pFire && ped->IsAlive() && m_ped->IsAlive())
        return !CPedGroups::AreInSameGroup(ped, m_ped);
    return false;
}

bool CEventAcquaintancePed::AffectsPedGroup_Reversed(CPedGroup* pedGroup)
{
    if (m_ped) {
        CPedGroupMembership& membership = pedGroup->GetMembership();
        if (!membership.IsMember(m_ped)
            && (GetEventType() != EVENT_ACQUAINTANCE_PED_RESPECT && GetEventType() != EVENT_ACQUAINTANCE_PED_LIKE || m_ped != pedGroup->field_0))
        {
            if (GetEventType() != EVENT_ACQUAINTANCE_PED_RESPECT && GetEventType() != EVENT_ACQUAINTANCE_PED_LIKE)
                return true;
            CPed* leader = membership.GetLeader();
            if (leader && leader->IsPlayer()) 
                return false;
            return FindPlayerPed()->GetGroup().GetMembership().IsMember(m_ped);
        }
    }
    return false;
}

bool CEventAcquaintancePed::TakesPriorityOver_Reversed(const CEvent& refEvent)
{
    if (refEvent.GetEventType() == GetEventType()) {
        const auto theRefEvent = static_cast<const CEventAcquaintancePed*>(&refEvent);
        if (m_ped && m_ped->IsPlayer()) 
            return theRefEvent->m_ped && !theRefEvent->m_ped->IsPlayer();
        return false;
    }
    return CEvent::TakesPriorityOver(refEvent);
}


void CEventAcquaintancePedHate::InjectHooks()
{
    ReversibleHooks::Install("CEventAcquaintancePedHate", "CEventAcquaintancePedHate", 0x420E70, &CEventAcquaintancePedHate::Constructor);
}

CEventAcquaintancePedHate* CEventAcquaintancePedHate::Constructor(CPed* ped)
{
    this->CEventAcquaintancePedHate::CEventAcquaintancePedHate(ped);
    return this;
}


void CEventAcquaintancePedHateBadlyLit::InjectHooks()
{
    ReversibleHooks::Install("CEventAcquaintancePedHateBadlyLit", "CEventAcquaintancePedHateBadlyLit", 0x5FF250, &CEventAcquaintancePedHateBadlyLit::Constructor);
    ReversibleHooks::Install("CEventAcquaintancePedHateBadlyLit", "AffectsPed", 0x4AFA90, &CEventAcquaintancePedHateBadlyLit::AffectsPed_Reversed);
}

CEventAcquaintancePedHateBadlyLit::CEventAcquaintancePedHateBadlyLit(CPed* ped, std::int32_t startTimeInMs, const CVector& point) : CEventAcquaintancePed(ped)
{
    m_startTimeInMs = startTimeInMs;
    m_point = point;
    if (startTimeInMs == -1) {
        m_startTimeInMs = CTimer::m_snTimeInMilliseconds;
        m_point = ped->GetPosition();
    }
}

CEventAcquaintancePedHateBadlyLit* CEventAcquaintancePedHateBadlyLit::Constructor(CPed* ped, std::int32_t startTimeInMs, const CVector& point)
{
    this->CEventAcquaintancePedHateBadlyLit::CEventAcquaintancePedHateBadlyLit(ped, startTimeInMs, point);
    return this;
}

// 0x4AFA90
bool CEventAcquaintancePedHateBadlyLit::AffectsPed(CPed* ped)
{
    return CEventAcquaintancePedHateBadlyLit::AffectsPed_Reversed(ped);
}

bool CEventAcquaintancePedHateBadlyLit::AffectsPed_Reversed(CPed* ped)
{
    if (CEventAcquaintancePed::AffectsPed(ped)) {
        CEvent* currentEvent = ped->GetEventHandlerHistory().GetCurrentEvent();
        if (!currentEvent || currentEvent->GetEventType() != EVENT_ACQUAINTANCE_PED_HATE_BADLY_LIT
            || currentEvent->GetSourceEntity() != GetSourceEntity())
        {
            return true;
        }
        auto theCurrentEvent = static_cast<CEventAcquaintancePedHateBadlyLit*>(currentEvent);
        if (m_startTimeInMs - theCurrentEvent->m_startTimeInMs >= 2000) {
            CVector distance = m_point - theCurrentEvent->m_point;
            return distance.SquaredMagnitude() >= 1.0f;
        }
    }
    return false;
}

CEventSeenCop* CEventSeenCop::Constructor(CPed* cop)
{
    this->CEventSeenCop::CEventSeenCop(cop);
    return this;
}
