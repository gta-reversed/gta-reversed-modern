#include "StdInc.h"

void CEventPedToFlee::InjectHooks()
{
    ReversibleHooks::Install(0x4AF240, &CEventPedToFlee::Constructor);
    ReversibleHooks::Install(0x4B73D0, &CEventPedToFlee::Clone_Reversed);
}

CEventPedToFlee::CEventPedToFlee(CPed* ped)
{
    m_ped = ped;
    if (m_ped)
        m_ped->RegisterReference(reinterpret_cast<CEntity**>(&m_ped));
}

CEventPedToFlee::~CEventPedToFlee()
{
    if (m_ped)
        m_ped->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_ped));
}

CEventPedToFlee* CEventPedToFlee::Constructor(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn< CEventPedToFlee*, 0x4AF240, CEventPedToFlee*, CPed*>(this, ped);
#else
    this->CEventPedToFlee::CEventPedToFlee(ped);
    return this;
#endif
}

CEvent* CEventPedToFlee::Clone()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEvent*, 0x4B73D0, CEvent*>(this);
#else
    return CEventPedToFlee::Clone_Reversed();
#endif
}

CEvent* CEventPedToFlee::Clone_Reversed()
{
    return new CEventPedToFlee(m_ped);
}
