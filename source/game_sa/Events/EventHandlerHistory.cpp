#include "StdInc.h"

void CEventHandlerHistory::InjectHooks()
{
    RH_ScopedClass(CEventHandlerHistory);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(ClearAllEvents, 0x4BC550);
    RH_ScopedInstall(ClearNonTempEvent, 0x4B8C60);
    RH_ScopedInstall(ClearTempEvent, 0x4B8C40);
    RH_ScopedInstall(GetCurrentEvent, 0x4B8CA0);
    RH_ScopedInstall(GetCurrentEventPriority, 0x4B8C80);
    RH_ScopedInstall(IsRespondingToEvent, 0x4B8B90);
    RH_ScopedInstall(RecordCurrentEvent, 0x4BC4B0);
    RH_ScopedInstall(StoreActiveEvent, 0x4B8BF0);
    RH_ScopedInstall(TakesPriorityOverCurrentEvent, 0x4BC580);
    RH_ScopedInstall(TickStoredEvent, 0x4B8C20);
}

CEventHandlerHistory::~CEventHandlerHistory()
{
    Flush();
}

// 0x4BC550
void CEventHandlerHistory::ClearAllEvents()
{
    ClearTempEvent();
    ClearNonTempEvent();
}

// 0x4B8C60
void CEventHandlerHistory::ClearNonTempEvent()
{
    delete m_nonTempEvent;
    m_nonTempEvent = nullptr;
}

// 0x4B8C40
void CEventHandlerHistory::ClearTempEvent()
{
    delete m_tempEvent;
    m_tempEvent = nullptr;
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

// 0x4B8C80
int32 CEventHandlerHistory::GetCurrentEventPriority()
{
    if (m_tempEvent)
        return m_tempEvent->GetEventPriority();
    if (m_nonTempEvent)
        return m_nonTempEvent->GetEventPriority();
    return -1;
}

// 0x4B8B90
bool CEventHandlerHistory::IsRespondingToEvent(eEventType eventType)
{
    if (eventType == EVENT_NONE)
        return m_nonTempEvent || m_storedActiveEvent;

    bool isNonTempEvent = false;
    if (m_nonTempEvent && m_nonTempEvent->GetEventType() == eventType)
        isNonTempEvent = true;

    if (!m_storedActiveEvent || m_storedActiveEvent->GetEventType() != eventType)
        return isNonTempEvent;

    return true;
}

// 0x4BC4B0
void CEventHandlerHistory::RecordCurrentEvent(CPed* ped, CEvent& event)
{
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
}

// 0x4B8BF0
void CEventHandlerHistory::StoreActiveEvent()
{
    delete m_storedActiveEvent;
    m_storedActiveEvent = m_nonTempEvent;
    m_storedActiveEventTimer.Start(2000);
}

// 0x4BC580
bool CEventHandlerHistory::TakesPriorityOverCurrentEvent(CEvent& event)
{
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
}

// 0x4B8C20
void CEventHandlerHistory::TickStoredEvent(CPed* ped)
{
    if (m_storedActiveEvent && !m_tempEvent) {
        m_nonTempEvent = m_storedActiveEvent;
        m_storedActiveEvent = nullptr;
    }
}

