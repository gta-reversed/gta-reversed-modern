/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Event.h"

class CPed;

const int32 TOTAL_EVENTS_PER_EVENTGROUP = 16;

class CEventGroup {
public:
    CPed*   m_pPed;
    int32   m_count;
    CEvent* m_events[TOTAL_EVENTS_PER_EVENTGROUP];

public:
    static void InjectHooks();
    CEventGroup* Constructor(CPed* ped);

    explicit CEventGroup(CPed* ped);
    virtual ~CEventGroup();

    CEvent* Add(CEvent* event, bool bValid = false);
    bool HasScriptCommandOfTaskType(eTaskType taskId);
    bool HasEventOfType(CEvent* event);
    bool HasEvent(CEvent* event);
    CEvent* GetHighestPriorityEvent();
    void TickEvents();
    void Remove(CEvent* event);
    void RemoveInvalidEvents(bool bRemoveNonScriptCommandEvents);
    void Reorganise();
    void Flush(bool bAvoidFlushingTaskComplexBeInGroup);
    CEvent* GetEventOfType(eEventType type) const noexcept;

    // NOTSA

    auto GetEvents()       { return std::span{ m_events, (size_t)m_count }; }
    auto GetEvents() const { return std::span{ m_events, (size_t)m_count }; }

    //! Helper so events can be directly passed in without having to put them into a variable
    template<std::derived_from<CEvent> T>
    CEvent* Add(T event, bool valid = false) {
        return Add(&event, valid);
    }
};

VALIDATE_SIZE(CEventGroup, 0x4C);
