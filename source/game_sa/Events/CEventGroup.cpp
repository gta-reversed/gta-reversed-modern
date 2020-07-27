#include "StdInc.h"

void CEventGroup::InjectHooks()
{
    HookInstall(0x4AB340, &CEventGroup::Constructor);
    HookInstall(0x4AB420, &CEventGroup::Add);
    HookInstall(0x4AB840, &CEventGroup::HasScriptCommandOfTaskType);
    HookInstall(0x4AB5E0, &CEventGroup::HasEventOfType);
    HookInstall(0x4AB6A0, &CEventGroup::HasEvent);
    HookInstall(0x4AB7C0, &CEventGroup::GetHighestPriorityEvent);
    HookInstall(0x4AB6D0, &CEventGroup::TickEvents);
    HookInstall(0x4AB5A0, &CEventGroup::Remove);
    HookInstall(0x4AB760, &CEventGroup::RemoveInvalidEvents);
    HookInstall(0x4AB700, &CEventGroup::Reorganise);
    HookInstall(0x4AB370, &CEventGroup::Flush);
}

CEventGroup::CEventGroup(CPed* ped)
{
    m_pPed = ped;
    m_count = 0;
    for (std::int32_t i = 0; i < TOTAL_EVENTS_PER_EVENTGROUP; i++) {
        m_events[i] = nullptr;
    }
}

CEventGroup::~CEventGroup()
{
    Flush(false);
}

CEventGroup* CEventGroup::Constructor(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventGroup*, 0x4AB340, CEventGroup*, CPed*>(this, ped);
#else
    this->CEventGroup::CEventGroup(ped);
    return this;
#endif
}

CEvent* CEventGroup::Add(CEvent* event, bool bValid)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEvent*, 0x4AB420, CEventGroup*, CEvent*, bool>(this, event, bValid);
#else
    if (m_pPed) {
        bool bAddToEventGroup = false;
        bool bInformGroup = false;
        bool bInformRespectedFriends = false;
        bool bTriggerLookAt = false;
        auto eventEditable = static_cast<CEventEditableResponse*>(event);
        if (event->HasEditableResponse()) {
            bInformGroup = eventEditable->ComputeResponseTaskOfType(m_pPed, TASK_SIMPLE_INFORM_GROUP);
            bInformRespectedFriends = eventEditable->ComputeResponseTaskOfType(m_pPed, TASK_SIMPLE_INFORM_RESPECTED_FRIENDS);
            bTriggerLookAt = eventEditable->ComputeResponseTaskOfType(m_pPed, TASK_SIMPLE_LOOK_AT_ENTITY_OR_COORD);
            eventEditable->ComputeResponseTaskType(m_pPed, false);
            if (eventEditable->WillRespond() ||
                (eventEditable->GetEventType() == EVENT_DAMAGE && eventEditable->m_bAddToEventGroup))
            {
                bAddToEventGroup = true;
            }
        }
        else {
            bAddToEventGroup = true;
        }
        if (!event->AffectsPed(m_pPed))
            return nullptr;
        if (event->HasEditableResponse()) {
            if (bInformGroup)
                eventEditable->InformGroup(m_pPed);
            CEventDamage* damageEvent = static_cast<CEventDamage*>(event);
            if (bInformRespectedFriends
                && (eventEditable->GetEventType() != EVENT_DAMAGE || !damageEvent->m_b05))
            {
                eventEditable->InformRespectedFriends(m_pPed);
            }
            if (bTriggerLookAt)
                eventEditable->TriggerLookAt(m_pPed);
            eventEditable->InformVehicleOccupants(m_pPed);
        }
        m_pPed->GetIntelligence()->RecordEventForScript(eventEditable->GetEventType(), eventEditable->GetEventPriority());
        if (!bAddToEventGroup)
            return nullptr;
    }
    if (m_count < TOTAL_EVENTS_PER_EVENTGROUP) {
        CEvent* clonedEvent = event->Clone();
        clonedEvent->m_bValid = bValid;
        if (m_pPed)
            clonedEvent->ReportCriminalEvent(m_pPed);
        m_events[m_count] = clonedEvent;
        m_count++;
        return clonedEvent;
    }
    return nullptr;
#endif
}

bool CEventGroup::HasScriptCommandOfTaskType(eTaskType taskId)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4AB840, CEventGroup*, int>(this, taskId);
#else
    if (m_count > 0) {
        for (std::int32_t i = 0; i < m_count; i++) {
            CEvent* event = m_events[i];
            if (event && event->GetEventType() == EVENT_SCRIPT_COMMAND) {
                auto theEvent = static_cast<CEventScriptCommand*>(event);
                if (theEvent->m_task && theEvent->m_task->GetId() == taskId) {
                    return true;
                }
            }
        }
    }
    return false;
#endif
}

bool CEventGroup::HasEventOfType(CEvent* event)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4AB5E0, CEventGroup*, CEvent*>(this, event);
#else
    if (m_count > 0) {
        for (std::int32_t i = 0; i < m_count; i++) {
            if (event->GetEventType() == m_events[i]->GetEventType())
                return true;
        }
    }
    return false;
#endif
}

CEvent* CEventGroup::GetHighestPriorityEvent()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEvent*, 0x4AB7C0, CEventGroup*>(this);
#else
    CEvent* theEvent = nullptr;
    if (m_count > 0) {
        std::int32_t highestPriority = -1;
        for (std::int32_t i = 0; i < m_count; i++) {
            CEvent* event = m_events[i];
            std::int32_t eventPriority = event->GetEventPriority();
            bool bIsPriorityGreater = false;
            if (event->GetEventType() == EVENT_SCRIPT_COMMAND) {
                if (eventPriority > highestPriority)
                    bIsPriorityGreater = true;
            }
            else if (eventPriority >= highestPriority)  {
                bIsPriorityGreater = true;
            }
            if (bIsPriorityGreater && event->AffectsPed(m_pPed)) {
                highestPriority = eventPriority;
                theEvent = event;
            }

        }
    }
    return theEvent;
#endif
}

void CEventGroup::TickEvents()
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4AB6D0, CEventGroup*>(this);
#else
    if (m_count > 0) {
        for (std::int32_t i = 0; i < m_count; i++) {
            m_events[i]->m_nTimeActive++;
        }
    }
#endif
}

bool CEventGroup::HasEvent(CEvent* event)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4AB6A0, CEventGroup*, CEvent*>(this, event);
#else
    if (m_count > 0) {
        for (std::int32_t i = 0; i < m_count; i++) {
            if (event == m_events[i])
                return true;
        }
    }
    return false;
#endif
}

void CEventGroup::Remove(CEvent* event)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4AB5A0, CEventGroup*, CEvent*>(this, event);
#else
    if (event && m_count > 0) {
        for (std::int32_t i = 0; i < m_count; i++) {
            if (event == m_events[i]) {
                m_events[i] = nullptr;
                delete event;
                break;
            }
        }
    }
#endif
}

void CEventGroup::RemoveInvalidEvents(bool bRemoveNonScriptCommandEvents)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4AB760, CEventGroup*, bool>(this, bRemoveNonScriptCommandEvents);
#else
    if (m_count > 0) {
        for (std::int32_t i = 0; i < m_count; i++) {
            CEvent* event = m_events[i];
            if (event) {
                if (!event->IsValid(m_pPed) || bRemoveNonScriptCommandEvents && event->GetEventType() != EVENT_SCRIPT_COMMAND) {
                    delete event;
                    m_events[i] = nullptr;
                }
            }
        }
    }
#endif
}

void CEventGroup::Reorganise()
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4AB700, CEventGroup*>(this);
#else
    CEvent* theEvents[TOTAL_EVENTS_PER_EVENTGROUP];
    std::int32_t eventCount = 0;
    if (m_count > 0) {
        for (std::int32_t i = 0; i < m_count; i++) {
            CEvent* event = m_events[i];
            if (event) {
                theEvents[eventCount++] = event;
                m_events[i] = nullptr;
            }
        }
    }
    m_count = eventCount;
    if (m_count > 0) {
        for (std::int32_t i = 0; i < m_count; i++) {
            m_events[i] = theEvents[i];
        }
    }
#endif
}

void CEventGroup::Flush(bool bAvoidFlushingTaskComplexBeInGroup)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4AB370, CEventGroup*, bool>(this, bAvoidFlushingTaskComplexBeInGroup);
#else
    CEvent* eventScriptcommand = nullptr;
    if (bAvoidFlushingTaskComplexBeInGroup && m_count > 0) {
        for (std::int32_t i = 0; i < m_count; i++) {
            CEvent* event = m_events[i];
            if (event->GetEventType() == EVENT_SCRIPT_COMMAND) {
                auto theEvent = static_cast<CEventScriptCommand*>(event);
                if (theEvent->m_task && theEvent->m_task->GetId() == TASK_COMPLEX_BE_IN_GROUP) {
                    eventScriptcommand = m_events[i];
                    m_events[i] = nullptr;
                    break;
                }
            }
        }
    }
    if (m_count > 0) {
        for (std::int32_t i = 0; i < m_count; i++) {
            CEvent* event = m_events[i];
            if (event) {
                delete event;
                m_events[i] = nullptr;
            }
        }
    }
    m_count = 0;
    if (eventScriptcommand) {
        m_events[0] = eventScriptcommand;
        m_count = 1;
    }
#endif
}
