#include "StdInc.h"

void CEventGroupEvent::InjectHooks()
{
    RH_ScopedInstall(Constructor, 0x4ADFD0);
    RH_ScopedInstall(Clone_Reversed, 0x4B6EE0);
    RH_ScopedInstall(BaseEventTakesPriorityOverBaseEvent, 0x4AE100);
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

    delete m_event;
}

// 0x4ADFD0
CEventGroupEvent* CEventGroupEvent::Constructor(CPed* ped, CEvent* event)
{
    this->CEventGroupEvent::CEventGroupEvent(ped, event);
    return this;
}

// 0x4B6EE0
CEvent* CEventGroupEvent::Clone()
{
    return CEventGroupEvent::Clone_Reversed();
}

CEvent* CEventGroupEvent::Clone_Reversed()
{
    return new CEventGroupEvent(m_ped, m_event->Clone());
}

// NOTSA, inlined
bool CEventGroupEvent::IsPriorityEvent() const
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

// 0x4AE100
bool CEventGroupEvent::BaseEventTakesPriorityOverBaseEvent(const CEventGroupEvent& other)
{
    if (IsPriorityEvent())
        return true;
    if (other.IsPriorityEvent())
        return false;
    return m_event->TakesPriorityOver(*other.m_event);
}
