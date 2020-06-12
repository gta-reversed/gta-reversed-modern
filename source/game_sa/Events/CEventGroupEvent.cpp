#include "StdInc.h"

void CEventGroupEvent::InjectHooks()
{
    HookInstall(0x4ADFD0, &CEventGroupEvent::Constructor);
    HookInstall(0x4B6EE0, &CEventGroupEvent::Clone_Reversed);
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
