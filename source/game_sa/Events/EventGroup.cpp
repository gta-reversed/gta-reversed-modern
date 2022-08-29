#include "StdInc.h"

#include "EventGroup.h"

void CEventGroup::InjectHooks() {
    RH_ScopedClass(CEventGroup);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AB340);
    RH_ScopedOverloadedInstall(Add, "", 0x4AB420, CEvent*(CEventGroup::*)(CEvent*, bool));
    RH_ScopedInstall(HasScriptCommandOfTaskType, 0x4AB840);
    RH_ScopedInstall(HasEventOfType, 0x4AB5E0);
    RH_ScopedInstall(HasEvent, 0x4AB6A0);
    RH_ScopedInstall(GetHighestPriorityEvent, 0x4AB7C0);
    RH_ScopedInstall(TickEvents, 0x4AB6D0);
    RH_ScopedInstall(Remove, 0x4AB5A0);
    RH_ScopedInstall(RemoveInvalidEvents, 0x4AB760);
    RH_ScopedInstall(Reorganise, 0x4AB700);
    RH_ScopedInstall(Flush, 0x4AB370);
    RH_ScopedInstall(GetEventOfType, 0x4AB650);
}

// 0x4AB340
CEventGroup::CEventGroup(CPed* ped) {
    m_pPed = ped;
    m_count = 0;
    std::ranges::fill(m_events, nullptr);
}

CEventGroup::~CEventGroup() {
    Flush(false);
}

CEventGroup* CEventGroup::Constructor(CPed* ped) {
    this->CEventGroup::CEventGroup(ped);
    return this;
}

// 0x4AB420
CEvent* CEventGroup::Add(CEvent* event, bool bValid) {
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
            if (eventEditable->WillRespond() || (eventEditable->GetEventType() == EVENT_DAMAGE && eventEditable->m_bAddToEventGroup)) {
                bAddToEventGroup = true;
            }
        } else {
            bAddToEventGroup = true;
        }
        if (!event->AffectsPed(m_pPed))
            return nullptr;
        if (event->HasEditableResponse()) {
            if (bInformGroup) {
                eventEditable->InformGroup(m_pPed);
            }
            auto* damageEvent = static_cast<CEventDamage*>(event);
            if (bInformRespectedFriends && (eventEditable->GetEventType() != EVENT_DAMAGE || !damageEvent->m_b05)) {
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
bool CEventGroup::HasScriptCommandOfTaskType(eTaskType taskId) {
    for (auto& event : GetEvents()) {
        if (event && event->GetEventType() == EVENT_SCRIPT_COMMAND) {
            auto theEvent = static_cast<CEventScriptCommand*>(event);
            if (theEvent->m_task && theEvent->m_task->GetTaskType() == taskId) {
                return true;
            }
        }
    }
    return false;
}

// 0x4AB5E0
bool CEventGroup::HasEventOfType(CEvent* event) {
    for (auto& tevent : GetEvents()) {
        if (event->GetEventType() == tevent->GetEventType())
            return true;
    }
    return false;
}

// 0x4AB7C0
CEvent* CEventGroup::GetHighestPriorityEvent() {
    CEvent* theEvent = nullptr;
    int32 highestPriority = -1;
    for (auto& event : GetEvents()) {
        int32 eventPriority = event->GetEventPriority();
        bool bIsPriorityGreater = false;
        if (event->GetEventType() == EVENT_SCRIPT_COMMAND) {
            if (eventPriority > highestPriority)
                bIsPriorityGreater = true;
        } else if (eventPriority >= highestPriority) {
            bIsPriorityGreater = true;
        }
        if (bIsPriorityGreater && event->AffectsPed(m_pPed)) {
            highestPriority = eventPriority;
            theEvent = event;
        }
    }
    return theEvent;
}

// 0x4AB6D0
void CEventGroup::TickEvents() {
    for (auto& event : GetEvents()) {
        event->m_nTimeActive++;
    }
}

// 0x4AB6A0
bool CEventGroup::HasEvent(CEvent* event) {
    for (auto& tevent : GetEvents()) {
        if (event == tevent)
            return true;
    }
    return false;
}

// 0x4AB5A0
void CEventGroup::Remove(CEvent* event) {
    for (auto& tevent : GetEvents()) {
        if (event == tevent) {
            tevent = nullptr;
            delete event;
            break;
        }
    }
}

// 0x4AB760
void CEventGroup::RemoveInvalidEvents(bool bRemoveNonScriptCommandEvents) {
    for (auto& event : GetEvents()) {
        if (event) {
            if (!event->IsValid(m_pPed) || bRemoveNonScriptCommandEvents && event->GetEventType() != EVENT_SCRIPT_COMMAND) {
                delete event;
                event = nullptr;
            }
        }
    }
}

// 0x4AB700
void CEventGroup::Reorganise() {
    CEvent* theEvents[TOTAL_EVENTS_PER_EVENTGROUP];
    int32 eventCount = 0;
    for (auto& event : GetEvents()) {
        if (event) {
            theEvents[eventCount++] = event;
            event = nullptr;
        }
    }
    m_count = eventCount;
    for (int32 i = 0; i < m_count; i++) {
        m_events[i] = theEvents[i];
    }
}

// 0x4AB370
void CEventGroup::Flush(bool bAvoidFlushingTaskComplexBeInGroup) {
    CEvent* eventScriptCommand = nullptr;
    if (bAvoidFlushingTaskComplexBeInGroup && m_count > 0) {
        for (auto& event : GetEvents()) {
            if (event->GetEventType() == EVENT_SCRIPT_COMMAND) {
                auto theEvent = static_cast<CEventScriptCommand*>(event);
                if (theEvent->m_task && theEvent->m_task->GetTaskType() == TASK_COMPLEX_BE_IN_GROUP) {
                    eventScriptCommand = event;
                    event = nullptr;
                    break;
                }
            }
        }
    }

    for (auto& event : GetEvents()) {
        if (event) {
            delete event;
            event = nullptr;
        }
    }

    m_count = 0;
    if (eventScriptCommand) {
        m_events[0] = eventScriptCommand;
        m_count = 1;
    }
}

// 0x4AB650
CEvent* CEventGroup::GetEventOfType(eEventType type) const noexcept {
    for (auto& event : GetEvents()) {
        if (event->GetEventType() == type) {
            return event;
        }
    }
    return nullptr;
}
