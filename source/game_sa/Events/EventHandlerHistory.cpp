#include "StdInc.h"

void CEventHandlerHistory::InjectHooks()
{
    Install("CEventHandlerHistory", "ClearAllEvents", 0x4BC550, &CEventHandlerHistory::ClearAllEvents);
    Install("CEventHandlerHistory", "ClearNonTempEvent", 0x4B8C60, &CEventHandlerHistory::ClearNonTempEvent);
    Install("CEventHandlerHistory", "ClearTempEvent", 0x4B8C40, &CEventHandlerHistory::ClearTempEvent);
    Install("CEventHandlerHistory", "GetCurrentEvent", 0x4B8CA0, &CEventHandlerHistory::GetCurrentEvent);
    Install("CEventHandlerHistory", "GetCurrentEventPriority", 0x4B8C80, &CEventHandlerHistory::GetCurrentEventPriority);
    Install("CEventHandlerHistory", "IsRespondingToEvent", 0x4B8B90, &CEventHandlerHistory::IsRespondingToEvent);
    Install("CEventHandlerHistory", "RecordCurrentEvent", 0x4BC4B0, &CEventHandlerHistory::RecordCurrentEvent);
    Install("CEventHandlerHistory", "StoreActiveEvent", 0x4B8BF0, &CEventHandlerHistory::StoreActiveEvent);
    Install("CEventHandlerHistory", "TakesPriorityOverCurrentEvent", 0x4BC580, &CEventHandlerHistory::TakesPriorityOverCurrentEvent);
    Install("CEventHandlerHistory", "TickStoredEvent", 0x4B8C20, &CEventHandlerHistory::TickStoredEvent);
}

CEventHandlerHistory::~CEventHandlerHistory()
{
    Flush();
}

void CEventHandlerHistory::ClearAllEvents()
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4BC550, CEventHandlerHistory*>(this);
#else
    ClearTempEvent();
    ClearNonTempEvent();
#endif
}

void CEventHandlerHistory::ClearNonTempEvent()
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4B8C60, CEventHandlerHistory*>(this);
#else
    delete m_nonTempEvent;
    m_nonTempEvent = nullptr;
#endif
}

void CEventHandlerHistory::ClearTempEvent()
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4B8C40, CEventHandlerHistory*>(this);
#else
    delete m_tempEvent;
    m_tempEvent = nullptr;
#endif
}

void CEventHandlerHistory::ClearStoredActiveEvent()
{
    delete m_storedActiveEvent;
    m_storedActiveEvent = nullptr;
}

void CEventHandlerHistory::Flush()
{
    ClearAllEvents();
    ClearStoredActiveEvent();
}

int32 CEventHandlerHistory::GetCurrentEventPriority()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<int32, 0x4B8C80, CEventHandlerHistory*>(this);
#else
    if (m_tempEvent)
        return m_tempEvent->GetEventPriority();
    if (m_nonTempEvent)
        return m_nonTempEvent->GetEventPriority();
    return -1;
#endif
}

bool CEventHandlerHistory::IsRespondingToEvent(eEventType eventType)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B8B90, CEventHandlerHistory*, eEventType>(this, eventType);
#else
    if (eventType == EVENT_NONE)
        return m_nonTempEvent || m_storedActiveEvent;
    bool isNonTempEvent = false;
    if (m_nonTempEvent && m_nonTempEvent->GetEventType() == eventType)
        isNonTempEvent = true;
    if (!m_storedActiveEvent || m_storedActiveEvent->GetEventType() != eventType)
        return isNonTempEvent;
    return true;
#endif
}

void CEventHandlerHistory::RecordCurrentEvent(CPed* ped, CEvent& event)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4BC4B0, CEventHandlerHistory*, CPed*, CEvent&>(this, ped, event);
#else
    if (event.GetEventType() != EVENT_SCRIPT_COMMAND) {
        if (CEventHandler::IsTemporaryEvent(event)) {
            if (m_nonTempEvent) {
                StoreActiveEvent();
                m_nonTempEvent = nullptr;
            }
            ClearTempEvent();
            m_tempEvent = event.Clone();
        }
        else {
            ClearNonTempEvent();
            m_nonTempEvent = event.Clone();
            ClearStoredActiveEvent();
            ClearTempEvent();
        }
    }
#endif
}

void CEventHandlerHistory::StoreActiveEvent()
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4B8BF0, CEventHandlerHistory*>(this);
#else
    delete m_storedActiveEvent;
    m_storedActiveEvent = m_nonTempEvent;
    m_storedActiveEventTimer.Start(2000);
#endif
}

bool CEventHandlerHistory::TakesPriorityOverCurrentEvent(CEvent& event)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4BC580, CEventHandlerHistory*, CEvent&>(this, event);
#else
    if (m_nonTempEvent)
        return event.TakesPriorityOver(*m_nonTempEvent);
    if (!m_tempEvent)
        return true;
    if (CEventHandler::IsTemporaryEvent(event))
        return event.TakesPriorityOver(*m_tempEvent);
    if (!event.TakesPriorityOver(*m_tempEvent))
        return false;
    if (!m_storedActiveEvent || event.TakesPriorityOver(*m_storedActiveEvent))
        return true;
    return false;
#endif
}

void CEventHandlerHistory::TickStoredEvent(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4B8C20, CEventHandlerHistory*, CPed*>(this, ped);
#else
    if (m_storedActiveEvent && !m_tempEvent) {
        m_nonTempEvent = m_storedActiveEvent;
        m_storedActiveEvent = nullptr;
    }
#endif
}

