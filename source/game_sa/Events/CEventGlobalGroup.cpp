#include "StdInc.h"

void CEventGlobalGroup::InjectHooks()
{
    ReversibleHooks::Install(0x4AB900, &CEventGlobalGroup::GetSoundLevel);
    ReversibleHooks::Install(0x4AB9C0, &CEventGlobalGroup::AddEventsToPed);
    ReversibleHooks::Install(0x4AB8A0, &CEventGlobalGroup::AddEventsToGroup);
}

float CEventGlobalGroup::GetSoundLevel(CEntity* entity, CVector& position)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<float, 0x4AB900, CEventGlobalGroup*, CEntity*, CVector&>(this, entity, position);
#else
    float soundLevel = 0.0f;
    if (m_count > 0) {
        for (std::int32_t i = 0; i < m_count; i++) {
            CEvent* event = m_events[i];
            if (event->GetSourceEntity() == entity || !entity) {
                float eventSoundLevel = event->GetSoundLevel(entity, position);
                if (eventSoundLevel > 0.0f) 
                    soundLevel += CEvent::CalcSoundLevelIncrement(soundLevel, eventSoundLevel);
            }
        }
    }
    return soundLevel;
#endif
}

void CEventGlobalGroup::AddEventsToPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4AB9C0, CEventGlobalGroup*, CPed*>(this, ped);
#else
    if (m_count > 0) {
        CEventGroup& pedEventGroup = ped->GetEventGroup();
        for (std::int32_t i = 0; i < m_count; i++) {
            CEvent* event = m_events[i];
            CEvent* clonedEvent = event->Clone();
            pedEventGroup.Add(clonedEvent, false);
            delete clonedEvent;
        }
    }
#endif
}

void CEventGlobalGroup::AddEventsToGroup(CPedGroup* pedGroup)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4AB8A0, CEventGlobalGroup*, CPedGroup*>(this, pedGroup);
#else
    if (m_count > 0) {
        CPedGroupIntelligence& groupIntelligence = pedGroup->GetIntelligence();
        for (std::int32_t i = 0; i < m_count; i++) {
            CEvent* event = m_events[i];
            CEvent* clonedEvent = event->Clone();
            groupIntelligence.AddEvent(clonedEvent);
            delete clonedEvent;
        }
    }
#endif
}
