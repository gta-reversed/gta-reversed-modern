#include "StdInc.h"

#include "EventGunAimedAt.h"

#include "PedType.h"

void CEventGunAimedAt::InjectHooks()
{
    RH_ScopedClass(CEventGunAimedAt);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B0700);
    RH_ScopedVirtualInstall(AffectsPed, 0x4B4EE0);
    RH_ScopedVirtualInstall(ReportCriminalEvent, 0x4B09E0);
    RH_ScopedVirtualInstall(TakesPriorityOver, 0x4B0810);
    RH_ScopedVirtualInstall(CloneEditable, 0x4B7630);
}

// 0x4B0700
CEventGunAimedAt::CEventGunAimedAt(CPed* ped)
{
    m_ped = ped;
    CEntity::SafeRegisterRef(m_ped);
}

CEventGunAimedAt::~CEventGunAimedAt()
{
    CEntity::SafeCleanUpRef(m_ped);
}


CEventGunAimedAt* CEventGunAimedAt::Constructor(CPed* ped)
{
    this->CEventGunAimedAt::CEventGunAimedAt(ped);
    return this;
}

// 0x4B4EE0
bool CEventGunAimedAt::AffectsPed(CPed* ped)
{
    return CEventGunAimedAt::AffectsPed_Reversed(ped);
}

// 0x4B09E0
void CEventGunAimedAt::ReportCriminalEvent(CPed* ped)
{
    return CEventGunAimedAt::ReportCriminalEvent_Reversed(ped);
}

// 0x4B0810
bool CEventGunAimedAt::TakesPriorityOver(const CEvent& refEvent)
{
    return CEventGunAimedAt::TakesPriorityOver_Reversed(refEvent);
}

// 0x4B7630
CEventEditableResponse* CEventGunAimedAt::CloneEditable()
{
    return CEventGunAimedAt::CloneEditable_Reversed();
}

bool CEventGunAimedAt::AffectsPed_Reversed(CPed* ped)
{
    if (ped->IsPlayer())
        return false;

    CTask* activeTask = ped->GetTaskManager().GetActiveTask();
    if (activeTask && activeTask->GetTaskType() == TASK_COMPLEX_REACT_TO_GUN_AIMED_AT)
        return false;
    if (m_ped && ped->GetIntelligence()->IsInSeeingRange(m_ped->GetPosition()) && ped->IsAlive()) {
        if (CPedGroups::AreInSameGroup(ped, m_ped))
            return false;
        if (!ped->IsInVehicleThatHasADriver()) {
            if (ped->m_nPedType == PED_TYPE_COP)
                CCrime::ReportCrime(eCrimeType::CRIME_AIM_GUN, ped, FindPlayerPed());
            return true;
        }
    }
    return false;
}

void CEventGunAimedAt::ReportCriminalEvent_Reversed(CPed* ped)
{
    if (IsCriminalEvent())
        CPedType::PoliceDontCareAboutCrimesAgainstPedType(ped->m_nPedType);
}

bool CEventGunAimedAt::TakesPriorityOver_Reversed(const CEvent& refEvent)
{
    if (m_ped && m_ped->IsPlayer()) {
        if (refEvent.GetSourceEntity() == m_ped)
            return GetEventPriority() >= refEvent.GetEventPriority();

        switch (refEvent.GetEventType())
        {
        case EVENT_DAMAGE:
        case EVENT_ACQUAINTANCE_PED_HATE:
        case EVENT_ACQUAINTANCE_PED_RESPECT:
            return true;
        }
        return CEvent::TakesPriorityOver(refEvent);
    }
    return GetEventPriority() >= refEvent.GetEventPriority();
}

CEventEditableResponse* CEventGunAimedAt::CloneEditable_Reversed()
{
    return new CEventGunAimedAt(m_ped);
}
