#pragma once
#include "PluginBase.h"
#include "CTaskTimer.h"

class CEvent;
class CEventHandlerHistory
{
public:
    CTask* m_task = nullptr;
    CEvent* m_nonTempEvent = nullptr;
    CEvent* m_tempEvent = nullptr;
    CEvent* m_storedActiveEvent = nullptr;
    CTaskTimer m_storedActiveEventTimer;

    static void InjectHooks();

    CEventHandlerHistory() {}
    ~CEventHandlerHistory();

    void ClearAllEvents();
    void ClearNonTempEvent();
    void ClearTempEvent();
    void ClearStoredActiveEvent();
    void Flush();
    CEvent* GetCurrentEvent() { return m_tempEvent ? m_tempEvent : m_nonTempEvent; };
    std::int32_t GetCurrentEventPriority();
    CEvent* GetStoredActiveEvent() { return m_storedActiveEvent; }
    bool IsRespondingToEvent(eEventType eventType);
    void RecordCurrentEvent(CPed* ped, CEvent& event);
    void StoreActiveEvent();
    bool TakesPriorityOverCurrentEvent(CEvent& event);
    void TickStoredEvent(CPed* ped);
};

VALIDATE_SIZE(CEventHandlerHistory, 0x1C);
