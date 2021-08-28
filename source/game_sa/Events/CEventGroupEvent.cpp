#include "StdInc.h"

void CEventGroupEvent::InjectHooks()
{
    HookInstall(0x4ADFD0, &CEventGroupEvent::Constructor);
    HookInstall(0x4B6EE0, &CEventGroupEvent::Clone_Reversed);
    HookInstall(0x4AE100, &CEventGroupEvent::BaseEventTakesPriorityOverBaseEvent);
}

CEventGroupEvent::CEventGroupEvent(CPed* ped, CEvent* event)
{
    m_ped = ped;
    m_event = event;
    if (m_ped)
        m_ped->RegisterReference(reinterpret_cast<CEntity**>(&m_ped));
}

CEventGroupEvent::~CEventGroupEvent()
{
    if (m_ped)
        m_ped->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_ped));
    if (m_event)
        delete m_event;
}

CEventGroupEvent* CEventGroupEvent::Constructor(CPed* ped, CEvent* event)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventGroupEvent*, 0x4ADFD0, CEventGroupEvent*, CPed*, CEvent* >(this, ped, event);
#else
    this->CEventGroupEvent::CEventGroupEvent(ped, event);
    return this;
#endif
}

CEvent* CEventGroupEvent::Clone()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEvent*, 0x4B6EE0, CEvent*>(this);
#else
    return CEventGroupEvent::Clone_Reversed();
#endif
}

CEvent* CEventGroupEvent::Clone_Reversed()
{
    return new CEventGroupEvent(m_ped, m_event->Clone());
}

bool CEventGroupEvent::IsPriorityEvent()
{
    switch (m_event->GetEventType()) {
    case EVENT_LEADER_ENTERED_CAR_AS_DRIVER:
    case EVENT_LEADER_EXITED_CAR_AS_DRIVER:
    case EVENT_LEADER_QUIT_ENTERING_CAR_AS_DRIVER:
    case EVENT_PLAYER_COMMAND_TO_GROUP:
    case EVENT_PLAYER_COMMAND_TO_GROUP_GATHER:
    case EVENT_DRAGGED_OUT_CAR:
    case EVENT_LEADER_ENTRY_EXIT:
        return true;
    }
    return false;
}

bool CEventGroupEvent::BaseEventTakesPriorityOverBaseEvent(CEventGroupEvent* other)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4AE100, CEvent*, CEvent*>(this, other);
#else
    if (IsPriorityEvent())
        return true;
    if (other->IsPriorityEvent())
        return false;
    return m_event->TakesPriorityOver(other->m_event);
#endif
}
