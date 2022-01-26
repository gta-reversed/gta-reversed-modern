#include "StdInc.h"

void CEventPedToFlee::InjectHooks()
{
    RH_ScopedInstall(Constructor, 0x4AF240);
    RH_ScopedInstall(Clone_Reversed, 0x4B73D0);
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

// 0x4AF240
CEventPedToFlee* CEventPedToFlee::Constructor(CPed* ped)
{
    this->CEventPedToFlee::CEventPedToFlee(ped);
    return this;
}

// 0x4B73D0
CEvent* CEventPedToFlee::Clone()
{
    return CEventPedToFlee::Clone_Reversed();
}

CEvent* CEventPedToFlee::Clone_Reversed()
{
    return new CEventPedToFlee(m_ped);
}
