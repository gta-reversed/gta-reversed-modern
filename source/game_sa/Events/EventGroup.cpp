#include "StdInc.h"

void CEventGroup::InjectHooks()
{
    using namespace ReversibleHooks;
    Install("CEventGroup", "Constructor", 0x4AB340, &CEventGroup::Constructor);
    Install("CEventGroup", "Add", 0x4AB420, &CEventGroup::Add);
    Install("CEventGroup", "HasScriptCommandOfTaskType", 0x4AB840, &CEventGroup::HasScriptCommandOfTaskType);
    Install("CEventGroup", "HasEventOfType", 0x4AB5E0, &CEventGroup::HasEventOfType);
    Install("CEventGroup", "HasEvent", 0x4AB6A0, &CEventGroup::HasEvent);
    Install("CEventGroup", "GetHighestPriorityEvent", 0x4AB7C0, &CEventGroup::GetHighestPriorityEvent);
    Install("CEventGroup", "TickEvents", 0x4AB6D0, &CEventGroup::TickEvents);
    Install("CEventGroup", "Remove", 0x4AB5A0, &CEventGroup::Remove);
    Install("CEventGroup", "RemoveInvalidEvents", 0x4AB760, &CEventGroup::RemoveInvalidEvents);
    Install("CEventGroup", "Reorganise", 0x4AB700, &CEventGroup::Reorganise);
    Install("CEventGroup", "Flush", 0x4AB370, &CEventGroup::Flush);
    //Install("CEventGroup", "GetEventOfType", 0x4AB650, &CEventGroup::GetEventOfType);
}

// 0x4AB340
CEventGroup::CEventGroup(CPed* ped)
{
    m_pPed = ped;
    m_count = 0;
    std::ranges::fill(m_events, nullptr);
}

CEventGroup::~CEventGroup()
{
    Flush(false);
}

CEventGroup* CEventGroup::Constructor(CPed* ped)
{
    this->CEventGroup::CEventGroup(ped);
    return this;
}

// 0x4AB420
CEvent* CEventGroup::Add(CEvent* event, bool bValid)
{
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
}

// 0x4AB840
bool CEventGroup::HasScriptCommandOfTaskType(eTaskType taskId)
{
    if (m_count > 0) {
        for (int32 i = 0; i < m_count; i++) {
            CEvent* event = m_events[i];
            if (event && event->GetEventType() == EVENT_SCRIPT_COMMAND) {
                auto theEvent = static_cast<CEventScriptCommand*>(event);
                if (theEvent->m_task && theEvent->m_task->GetTaskType() == taskId) {
                    return true;
                }
            }
        }
    }
    return false;
}

// 0x4AB5E0
bool CEventGroup::HasEventOfType(CEvent* event)
{
    if (m_count > 0) {
        for (int32 i = 0; i < m_count; i++) {
            if (event->GetEventType() == m_events[i]->GetEventType())
                return true;
        }
    }
    return false;
}

// 0x4AB7C0
CEvent* CEventGroup::GetHighestPriorityEvent()
{
    CEvent* theEvent = nullptr;
    if (m_count > 0) {
        int32 highestPriority = -1;
        for (int32 i = 0; i < m_count; i++) {
            CEvent* event = m_events[i];
            int32 eventPriority = event->GetEventPriority();
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
}

// 0x4AB6D0
void CEventGroup::TickEvents()
{
    if (m_count > 0) {
        for (int32 i = 0; i < m_count; i++) {
            m_events[i]->m_nTimeActive++;
        }
    }
}

// 0x4AB6A0
bool CEventGroup::HasEvent(CEvent* event)
{
    if (m_count > 0) {
        for (int32 i = 0; i < m_count; i++) {
            if (event == m_events[i])
                return true;
        }
    }
    return false;
}

// 0x4AB5A0
void CEventGroup::Remove(CEvent* event)
{
    if (event && m_count > 0) {
        for (int32 i = 0; i < m_count; i++) {
            if (event == m_events[i]) {
                m_events[i] = nullptr;
                delete event;
                break;
            }
        }
    }
}

// 0x4AB760
void CEventGroup::RemoveInvalidEvents(bool bRemoveNonScriptCommandEvents)
{
    if (m_count > 0) {
        for (int32 i = 0; i < m_count; i++) {
            CEvent* event = m_events[i];
            if (event) {
                if (!event->IsValid(m_pPed) || bRemoveNonScriptCommandEvents && event->GetEventType() != EVENT_SCRIPT_COMMAND) {
                    delete event;
                    m_events[i] = nullptr;
                }
            }
        }
    }
}

// 0x4AB700
void CEventGroup::Reorganise()
{
    CEvent* theEvents[TOTAL_EVENTS_PER_EVENTGROUP];
    int32 eventCount = 0;
    if (m_count > 0) {
        for (int32 i = 0; i < m_count; i++) {
            CEvent* event = m_events[i];
            if (event) {
                theEvents[eventCount++] = event;
                m_events[i] = nullptr;
            }
        }
    }
    m_count = eventCount;
    if (m_count > 0) {
        for (int32 i = 0; i < m_count; i++) {
            m_events[i] = theEvents[i];
        }
    }
}

// 0x4AB370
void CEventGroup::Flush(bool bAvoidFlushingTaskComplexBeInGroup)
{
    CEvent* eventScriptcommand = nullptr;
    if (bAvoidFlushingTaskComplexBeInGroup && m_count > 0) {
        for (int32 i = 0; i < m_count; i++) {
            CEvent* event = m_events[i];
            if (event->GetEventType() == EVENT_SCRIPT_COMMAND) {
                auto theEvent = static_cast<CEventScriptCommand*>(event);
                if (theEvent->m_task && theEvent->m_task->GetTaskType() == TASK_COMPLEX_BE_IN_GROUP) {
                    eventScriptcommand = m_events[i];
                    m_events[i] = nullptr;
                    break;
                }
            }
        }
    }
    if (m_count > 0) {
        for (int32 i = 0; i < m_count; i++) {
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
}

// 0x4AB650
CEvent* CEventGroup::GetEventOfType(eEventType type) const noexcept {
    return plugin::CallMethodAndReturn<CEvent*, 0x4AB650, const CEventGroup*, eEventType>(this, type);
}
