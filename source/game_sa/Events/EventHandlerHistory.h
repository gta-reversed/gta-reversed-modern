#pragma once

#include "TaskTimer.h"

class CEvent;
class CEventHandlerHistory {
public:
    CTask* m_AbortedTask{};
    CEvent* m_CurrentNonTempEvent{};
    CEvent* m_CurrentTempEvent{};
    CEvent* m_StoredEventActive{};
    CTaskTimer m_StoreTimer{};

public:
    static void InjectHooks();

    CEventHandlerHistory() = default;
    ~CEventHandlerHistory();

    void ClearAllEvents();
    void ClearNonTempEvent();
    void ClearTempEvent();
    void ClearStoredActiveEvent();
    void Flush();
    CEvent* GetCurrentEvent() const { return m_CurrentTempEvent ? m_CurrentTempEvent : m_CurrentNonTempEvent; }
    int32 GetCurrentEventPriority() const;
    CEvent* GetStoredActiveEvent() const { return m_StoredEventActive; }
    bool IsRespondingToEvent(eEventType eventType) const;
    void RecordCurrentEvent(CPed* ped, CEvent& event);
    void StoreActiveEvent();
    bool TakesPriorityOverCurrentEvent(CEvent& event) const;
    void TickStoredEvent(CPed*);
};

VALIDATE_SIZE(CEventHandlerHistory, 0x1C);
