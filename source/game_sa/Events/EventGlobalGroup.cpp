#include "StdInc.h"

void CEventGlobalGroup::InjectHooks()
{
    ReversibleHooks::Install("CEventGlobalGroup", "GetSoundLevel", 0x4AB900, &CEventGlobalGroup::GetSoundLevel);
    ReversibleHooks::Install("CEventGlobalGroup", "AddEventsToPed", 0x4AB9C0, &CEventGlobalGroup::AddEventsToPed);
    ReversibleHooks::Install("CEventGlobalGroup", "AddEventsToGroup", 0x4AB8A0, &CEventGlobalGroup::AddEventsToGroup);
}

// 0x4AB900
float CEventGlobalGroup::GetSoundLevel(CEntity* entity, CVector& position)
{
    float soundLevel = 0.0f;
    if (m_count > 0) {
        for (int32 i = 0; i < m_count; i++) {
            CEvent* event = m_events[i];
            if (event->GetSourceEntity() == entity || !entity) {
                float eventSoundLevel = event->GetSoundLevel(entity, position);
                if (eventSoundLevel > 0.0f) 
                    soundLevel += CEvent::CalcSoundLevelIncrement(soundLevel, eventSoundLevel);
            }
        }
    }
    return soundLevel;
}

// 0x4AB9C0
void CEventGlobalGroup::AddEventsToPed(CPed* ped)
{
    if (m_count > 0) {
        CEventGroup& pedEventGroup = ped->GetEventGroup();
        for (int32 i = 0; i < m_count; i++) {
            CEvent* event = m_events[i];
            CEvent* clonedEvent = event->Clone();
            pedEventGroup.Add(clonedEvent, false);
            delete clonedEvent;
        }
    }
}

// 0x4AB8A0
void CEventGlobalGroup::AddEventsToGroup(CPedGroup* pedGroup)
{
    if (m_count > 0) {
        CPedGroupIntelligence& groupIntelligence = pedGroup->GetIntelligence();
        for (int32 i = 0; i < m_count; i++) {
            CEvent* event = m_events[i];
            CEvent* clonedEvent = event->Clone();
            groupIntelligence.AddEvent(clonedEvent);
            delete clonedEvent;
        }
    }
}
