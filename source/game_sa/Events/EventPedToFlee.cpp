#include "StdInc.h"

#include "EventPedToFlee.h"

void CEventPedToFlee::InjectHooks()
{
    RH_ScopedClass(CEventPedToFlee);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AF240);
    RH_ScopedVirtualInstall(Clone, 0x4B73D0);
}

CEventPedToFlee::CEventPedToFlee(CPed* ped)
{
    m_ped = ped;
    CEntity::SafeRegisterRef(m_ped);
}

CEventPedToFlee::~CEventPedToFlee()
{
    CEntity::SafeCleanUpRef(m_ped);
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
