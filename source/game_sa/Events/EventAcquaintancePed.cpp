#include "StdInc.h"

#include "EventAcquaintancePed.h"

void CEventAcquaintancePed::InjectHooks()
{
    RH_ScopedClass(CEventAcquaintancePed);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AF820);
    RH_ScopedVirtualInstall(AffectsPed, 0x4AFA30);
    RH_ScopedVirtualInstall(AffectsPedGroup, 0x4AF970);
    RH_ScopedVirtualInstall(TakesPriorityOver, 0x4AF8F0);
}

void CEventSeenCop::InjectHooks()
{
    RH_ScopedClass(CEventSeenCop);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor1, 0x5FF380);
}

CEventAcquaintancePed::CEventAcquaintancePed(CPed* ped)
{
    m_ped = ped;
    CEntity::SafeRegisterRef(m_ped);
}

CEventAcquaintancePed::~CEventAcquaintancePed()
{
    CEntity::SafeCleanUpRef(m_ped);
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
            && (GetEventType() != EVENT_ACQUAINTANCE_PED_RESPECT && GetEventType() != EVENT_ACQUAINTANCE_PED_LIKE || m_ped != pedGroup->m_pPed))
        {
            if (GetEventType() != EVENT_ACQUAINTANCE_PED_RESPECT && GetEventType() != EVENT_ACQUAINTANCE_PED_LIKE)
                return true;
            CPed* leader = membership.GetLeader();
            if (leader && leader->IsPlayer())
                return false;
            return FindPlayerPed()->GetPlayerGroup().GetMembership().IsMember(m_ped);
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
    RH_ScopedClass(CEventAcquaintancePedHate);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor2, 0x420E70);
}

CEventAcquaintancePedHate* CEventAcquaintancePedHate::Constructor2(CPed* ped)
{
    this->CEventAcquaintancePedHate::CEventAcquaintancePedHate(ped);
    return this;
}


void CEventAcquaintancePedHateBadlyLit::InjectHooks()
{
    RH_ScopedClass(CEventAcquaintancePedHateBadlyLit);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x5FF250);
    RH_ScopedInstall(AffectsPed_Reversed1, 0x4AFA90);
}

CEventAcquaintancePedHateBadlyLit::CEventAcquaintancePedHateBadlyLit(CPed* ped, int32 startTimeInMs, const CVector& point) : CEventAcquaintancePed(ped)
{
    m_startTimeInMs = startTimeInMs;
    m_point = point;
    if (startTimeInMs == -1) {
        m_startTimeInMs = CTimer::GetTimeInMS();
        m_point = ped->GetPosition();
    }
}

CEventAcquaintancePedHateBadlyLit* CEventAcquaintancePedHateBadlyLit::Constructor(CPed* ped, int32 startTimeInMs, const CVector& point)
{
    this->CEventAcquaintancePedHateBadlyLit::CEventAcquaintancePedHateBadlyLit(ped, startTimeInMs, point);
    return this;
}

// 0x4AFA90
bool CEventAcquaintancePedHateBadlyLit::AffectsPed(CPed* ped)
{
    return CEventAcquaintancePedHateBadlyLit::AffectsPed_Reversed(ped);
}

bool CEventAcquaintancePedHateBadlyLit::AffectsPed_Reversed1(CPed* ped)
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

CEventSeenCop* CEventSeenCop::Constructor1(CPed* cop)
{
    this->CEventSeenCop::CEventSeenCop(cop);
    return this;
}
