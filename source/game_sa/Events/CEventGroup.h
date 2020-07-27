/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CEvent.h"

enum eTaskType;
class CPed;

const std::int32_t TOTAL_EVENTS_PER_EVENTGROUP = 16;

class CEventGroup {
public:
    CPed *m_pPed;
    std::int32_t m_count;
    CEvent *m_events[TOTAL_EVENTS_PER_EVENTGROUP];

    static void InjectHooks();

    CEventGroup(CPed* ped);
    virtual ~CEventGroup();
private:
    CEventGroup* Constructor(CPed* ped);
public:
    CEvent * Add(CEvent* event, bool bValid);
    bool HasScriptCommandOfTaskType(eTaskType taskId);
    bool HasEventOfType(CEvent* event);
    bool HasEvent(CEvent* event);
    CEvent* GetHighestPriorityEvent();
    void TickEvents();
    void Remove(CEvent* event);
    void RemoveInvalidEvents(bool bRemoveNonScriptCommandEvents);
    void Reorganise();
    void Flush(bool bAvoidFlushingTaskComplexBeInGroup);
};

VALIDATE_SIZE(CEventGroup, 0x4C);
