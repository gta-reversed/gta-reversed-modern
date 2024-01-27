#include "StdInc.h"
#include "EventStuckInAir.h"


void CEventStuckInAir::InjectHooks()
{
    RH_ScopedClass(CEventStuckInAir);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B1490);
    RH_ScopedVirtualInstall2(GetEventPriority, 0x4B1600);
    RH_ScopedVirtualInstall(AffectsPed, 0x4B1580);
    RH_ScopedVirtualInstall(TakesPriorityOver, 0x4B15B0);
}

// 0x4B1490
CEventStuckInAir::CEventStuckInAir(CPed* ped)
{
    m_ped = ped;
    CEntity::SafeRegisterRef(m_ped);
}

CEventStuckInAir::~CEventStuckInAir()
{
    CEntity::SafeCleanUpRef(m_ped);
}

// 0x4B1600
int32 CEventStuckInAir::GetEventPriority() const {
    return m_ped && m_ped->GetIntelligence()->GetEventHandler().GetCurrentEventType() != EVENT_STUCK_IN_AIR && m_ped->GetIntelligence()->GetEventGroup().GetNumEventsInQueue() <= 1
        ? 75
        : 63;
}

// 0x4B1490
CEventStuckInAir* CEventStuckInAir::Constructor(CPed* ped)
{
    this->CEventStuckInAir::CEventStuckInAir(ped);
    return this;
}

// 0x4B1580
bool CEventStuckInAir::AffectsPed(CPed* ped)
{
    return CEventStuckInAir::AffectsPed_Reversed(ped);
}

// 0x4B15B0
bool CEventStuckInAir::TakesPriorityOver(const CEvent& refEvent)
{
    return CEventStuckInAir::TakesPriorityOver_Reversed(refEvent);
}

bool CEventStuckInAir::AffectsPed_Reversed(CPed* ped)
{
    if (ped->bIsStanding)
        return false;

    return ped->GetStuckChecker().m_state != PED_STUCK_STATE_NONE;
}

bool CEventStuckInAir::TakesPriorityOver_Reversed(const CEvent& refEvent)
{
    if (refEvent.GetEventPriority() < 74 && refEvent.GetEventType() != EVENT_STUCK_IN_AIR)
        return true;

    return CEvent::TakesPriorityOver(refEvent);
}

