#include "StdInc.h"

void CEventPedToChase::InjectHooks()
{
    ReversibleHooks::Install("CEventPedToChase", "Constructor", 0x4AF130, &CEventPedToChase::Constructor);
    ReversibleHooks::Install("CEventPedToChase", "Clone_Reversed", 0x4B7360, &CEventPedToChase::Clone_Reversed);
}

CEventPedToChase::CEventPedToChase(CPed* ped)
{
    m_ped = ped;
    if (m_ped)
        m_ped->RegisterReference(reinterpret_cast<CEntity**>(&m_ped));
}

CEventPedToChase::~CEventPedToChase()
{
    if (m_ped)
        m_ped->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_ped));
}

CEventPedToChase* CEventPedToChase::Constructor(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn< CEventPedToChase*, 0x4AF130, CEventPedToChase*, CPed*>(this, ped);
#else
    this->CEventPedToChase::CEventPedToChase(ped);
    return this;
#endif
}

CEvent* CEventPedToChase::Clone()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEvent*, 0x4B7360, CEvent*>(this);
#else
    return CEventPedToChase::Clone_Reversed();
#endif
}

CEvent* CEventPedToChase::Clone_Reversed()
{
    return new CEventPedToChase(m_ped);
}
