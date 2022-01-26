#include "StdInc.h"

void CEventPedToChase::InjectHooks()
{
    ReversibleHooks::Install("CEventPedToChase", "Constructor", 0x4AF130, &CEventPedToChase::Constructor);
    ReversibleHooks::Install("CEventPedToChase", "Clone_Reversed", 0x4B7360, &CEventPedToChase::Clone_Reversed);
}

// 0x4AF130
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
    this->CEventPedToChase::CEventPedToChase(ped);
    return this;
}

// 0x4B7360
CEvent* CEventPedToChase::Clone()
{
    return CEventPedToChase::Clone_Reversed();
}

CEvent* CEventPedToChase::Clone_Reversed()
{
    return new CEventPedToChase(m_ped);
}
