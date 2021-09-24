#include "StdInc.h"

void CEventSoundQuiet::InjectHooks()
{
    ReversibleHooks::Install("CEventSoundQuiet", "Constructor", 0x5E05B0, &CEventSoundQuiet::Constructor);
    ReversibleHooks::Install("CEventSoundQuiet", "AffectsPed_Reversed", 0x4B5240, &CEventSoundQuiet::AffectsPed_Reversed);
    ReversibleHooks::Install("CEventSoundQuiet", "CloneEditable_Reversed", 0x5E0670, &CEventSoundQuiet::CloneEditable_Reversed);
}

CEventSoundQuiet::CEventSoundQuiet(CEntity* entity, float fLocalSoundLevel, uint32 startTime, CVector& position)
{
    m_fLocalSoundLevel = fLocalSoundLevel;
    m_startTimeInMs = startTime;
    m_entity = entity;
    m_position = position;
    if (m_entity)
        m_entity->RegisterReference(&m_entity);
    if (m_startTimeInMs != -1)
        return;
    m_startTimeInMs = CTimer::GetTimeInMS();
    m_position = m_entity->GetPosition();
}

CEventSoundQuiet::~CEventSoundQuiet()
{
    if (m_entity)
        m_entity->CleanUpOldReference(&m_entity);
}

CEventSoundQuiet* CEventSoundQuiet::Constructor(CEntity* entity, float fLocalSoundLevel, uint32 startTime, CVector& position)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventSoundQuiet*, 0x5E05B0, CEventSoundQuiet*, CEntity*, float, uint32, CVector&>
        (this, entity, fLocalSoundLevel, startTime, position);
#else
    this->CEventSoundQuiet::CEventSoundQuiet(entity, fLocalSoundLevel, startTime, position);
    return this;
#endif
}

bool CEventSoundQuiet::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B5240, CEvent*, CPed*>(this, ped);
#else
    return CEventSoundQuiet::AffectsPed_Reversed(ped);
#endif
}

CEventEditableResponse* CEventSoundQuiet::CloneEditable()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventEditableResponse*, 0x5E0670, CEvent*>(this);
#else
    return CEventSoundQuiet::CloneEditable_Reversed();
#endif
}

bool CEventSoundQuiet::AffectsPed_Reversed(CPed* ped)
{
    if (ped->IsPlayer() || !ped->IsAlive()|| !GetSourceEntity())
        return false;
    float soundLevel = GetSoundLevel(nullptr, ped->GetPosition());
    if (soundLevel < 30.0f)
        return false;
    auto currentEvent = static_cast<CEventSoundQuiet*>(ped->GetEventHandlerHistory().GetCurrentEvent());
    if (currentEvent &&
        currentEvent->GetEventType() == EVENT_SOUND_QUIET && currentEvent->GetSourceEntity() == GetSourceEntity()) {
        CVector distance = m_position - currentEvent->m_position;
        if (m_startTimeInMs - currentEvent->m_startTimeInMs >= 2000 && distance.SquaredMagnitude() >= 1.0f)
            return true;
        if (soundLevel - currentEvent->GetSoundLevel(nullptr, ped->GetPosition()) < 3.0f)
            return false;
    }
    return true;
}

CEventEditableResponse* CEventSoundQuiet::CloneEditable_Reversed()
{
    return new CEventSoundQuiet(m_entity, m_fLocalSoundLevel, m_startTimeInMs, m_position);
}
