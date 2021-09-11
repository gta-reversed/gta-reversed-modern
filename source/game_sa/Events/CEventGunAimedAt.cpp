#include "StdInc.h"

void CEventGunAimedAt::InjectHooks()
{
    ReversibleHooks::Install("CEventGunAimedAt", "Constructor", 0x4B0700, &CEventGunAimedAt::Constructor);
    ReversibleHooks::Install("CEventGunAimedAt", "AffectsPed_Reversed", 0x4B4EE0, &CEventGunAimedAt::AffectsPed_Reversed);
    ReversibleHooks::Install("CEventGunAimedAt", "ReportCriminalEvent_Reversed", 0x4B09E0, &CEventGunAimedAt::ReportCriminalEvent_Reversed);
    ReversibleHooks::Install("CEventGunAimedAt", "TakesPriorityOver_Reversed", 0x4B0810, &CEventGunAimedAt::TakesPriorityOver_Reversed);
    ReversibleHooks::Install("CEventGunAimedAt", "CloneEditable_Reversed", 0x4B7630, &CEventGunAimedAt::CloneEditable_Reversed);
}

CEventGunAimedAt::CEventGunAimedAt(CPed* ped)
{
    m_ped = ped;
    if (m_ped)
        m_ped->RegisterReference(reinterpret_cast<CEntity**>(&m_ped));
}

CEventGunAimedAt::~CEventGunAimedAt()
{
    if (m_ped)
        m_ped->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_ped));
}


CEventGunAimedAt* CEventGunAimedAt::Constructor(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventGunAimedAt*, 0x4B0700, CEventGunAimedAt*, CPed*>(this, ped);
#else
    this->CEventGunAimedAt::CEventGunAimedAt(ped);
    return this;
#endif
}

bool CEventGunAimedAt::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B4EE0, CEvent*, CPed*>(this, ped);
#else
    return CEventGunAimedAt::AffectsPed_Reversed(ped);
#endif
}

void CEventGunAimedAt::ReportCriminalEvent(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethod<0x4B09E0, CEvent*, CPed*>(this, ped);
#else
    return CEventGunAimedAt::ReportCriminalEvent_Reversed(ped);
#endif
}

// 0x4B0810
bool CEventGunAimedAt::TakesPriorityOver(const CEvent& refEvent)
{
    return CEventGunAimedAt::TakesPriorityOver_Reversed(refEvent);
}

CEventEditableResponse* CEventGunAimedAt::CloneEditable()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventEditableResponse*, 0x4B7630, CEvent*>(this);
#else
    return CEventGunAimedAt::CloneEditable_Reversed();
#endif
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
                CCrime::ReportCrime(eCrimeType::CRIME_AIM_GUN, ped, FindPlayerPed(-1));
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
