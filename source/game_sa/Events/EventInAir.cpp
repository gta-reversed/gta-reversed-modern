#include "StdInc.h"

#include "EventInAir.h"

void CEventInAir::InjectHooks()
{
    RH_ScopedClass(CEventInAir);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B0CB0);
    RH_ScopedVirtualInstall(AffectsPed, 0x4B0C00);
}

CEventInAir* CEventInAir::Constructor()
{
    this->CEventInAir::CEventInAir();
    return this;
}

// 0x4B0C00
bool CEventInAir::AffectsPed(CPed* ped)
{
    return CEventInAir::AffectsPed_Reversed(ped);
}

bool CEventInAir::AffectsPed_Reversed(CPed* ped)
{
    CTask* activeTask = ped->GetTaskManager().GetActiveTask();
    if (activeTask
        && (activeTask->GetTaskType() == TASK_COMPLEX_USE_SWAT_ROPE
            || activeTask->GetTaskType() == TASK_COMPLEX_DIVE_FROM_ATTACHED_ENTITY_AND_GET_UP
            ||
                       activeTask->GetTaskType() == TASK_COMPLEX_IN_AIR_AND_LAND))
    {
        return false;
    }
    CTask* simplestActiveTask = ped->GetTaskManager().GetSimplestActiveTask();
    if (simplestActiveTask && simplestActiveTask->GetTaskType() == TASK_SIMPLE_FALL ||
        ped->m_pDamageEntity ||
        !ped->m_bUsesCollision ||
        ped->m_pAttachedTo ||
        !CPedGeometryAnalyser::IsInAir(*ped)
    ) {
        return false;
    }
    return ped->IsAlive();
}

void CEventStuckInAir::InjectHooks()
{
    RH_ScopedClass(CEventStuckInAir);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B1490);
    RH_ScopedVirtualInstall(GetEventPriority, 0x4B1600);
    RH_ScopedVirtualInstall(AffectsPed, 0x4B1580);
    RH_ScopedVirtualInstall(TakesPriorityOver, 0x4B15B0);
}

CEventStuckInAir::CEventStuckInAir(CPed* ped)
{
    m_ped = ped;
    CEntity::SafeRegisterRef(m_ped);
}

CEventStuckInAir::~CEventStuckInAir()
{
    CEntity::SafeCleanUpRef(m_ped);
}

CEventStuckInAir* CEventStuckInAir::Constructor(CPed* ped)
{
    this->CEventStuckInAir::CEventStuckInAir(ped);
    return this;
}

// 0x4B1600
int32 CEventStuckInAir::GetEventPriority() const
{
    return CEventStuckInAir::GetEventPriority_Reversed();
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

int32 CEventStuckInAir::GetEventPriority_Reversed() const
{
    if (m_ped && m_ped->GetEventHandler().GetCurrentEventType() != EVENT_STUCK_IN_AIR && m_ped->GetEventGroup().m_count > 1)
        return 75;

    return 63;
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
