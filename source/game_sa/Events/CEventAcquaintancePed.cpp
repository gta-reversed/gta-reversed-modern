#include "StdInc.h"

void CEventAcquaintancePed::InjectHooks()
{
    CEventAcquaintancePedHate::InjectHooks();
    CEventAcquaintancePedHateBadlyLit::InjectHooks();
    HookInstall(0x4AF820, &CEventAcquaintancePed::Constructor);
    HookInstall(0x4AFA30, &CEventAcquaintancePed::AffectsPed_Reversed);
    HookInstall(0x4AF970, &CEventAcquaintancePed::AffectsPedGroup_Reversed);
    HookInstall(0x4AF8F0, &CEventAcquaintancePed::TakesPriorityOver_Reversed);
}

void CEventSeenCop::InjectHooks()
{
    HookInstall(0x5FF380, &CEventSeenCop::Constructor);
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

bool CEventAcquaintancePed::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4AFA30, CEvent*, CPed*>(this, ped);
#else
    return CEventAcquaintancePed::AffectsPed_Reversed(ped);
#endif
}

bool CEventAcquaintancePed::AffectsPedGroup(CPedGroup* pedGroup)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4AF970, CEvent*, CPedGroup*>(this, pedGroup);
#else
    return CEventAcquaintancePed::AffectsPedGroup_Reversed(pedGroup);
#endif
}

bool CEventAcquaintancePed::TakesPriorityOver(CEvent* refEvent)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4AF8F0, CEvent*, CEvent*>(this, refEvent);
#else
    return CEventAcquaintancePed::TakesPriorityOver_Reversed(refEvent);
#endif
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

bool CEventAcquaintancePed::TakesPriorityOver_Reversed(CEvent* refEvent)
{
    if (refEvent->GetEventType() == GetEventType()) {
        CEventAcquaintancePed* theRefEvent = static_cast<CEventAcquaintancePed*>(refEvent);
        if (m_ped && m_ped->IsPlayer()) 
            return theRefEvent->m_ped && !theRefEvent->m_ped->IsPlayer();
        return false;
    }
    return CEvent::TakesPriorityOver(refEvent);
}


void CEventAcquaintancePedHate::InjectHooks()
{
    HookInstall(0x420E70, &CEventAcquaintancePedHate::Constructor);
}

CEventAcquaintancePedHate* CEventAcquaintancePedHate::Constructor(CPed* ped)
{
    this->CEventAcquaintancePedHate::CEventAcquaintancePedHate(ped);
    return this;
}


void CEventAcquaintancePedHateBadlyLit::InjectHooks()
{
    HookInstall(0x5FF250, &CEventAcquaintancePedHateBadlyLit::Constructor);
    HookInstall(0x4AFA90, &CEventAcquaintancePedHateBadlyLit::AffectsPed_Reversed);
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

bool CEventAcquaintancePedHateBadlyLit::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4AFA90, CEvent*, CPed*>(this, ped);
#else
    return CEventAcquaintancePedHateBadlyLit::AffectsPed_Reversed(ped);
#endif
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
