#include "StdInc.h"

#include "EventPedToChase.h"

void CEventPedToChase::InjectHooks()
{
    RH_ScopedClass(CEventPedToChase);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AF130);
    RH_ScopedVirtualInstall(Clone, 0x4B7360);
}

// 0x4AF130
CEventPedToChase::CEventPedToChase(CPed* ped)
{
    m_ped = ped;
    CEntity::SafeRegisterRef(m_ped);
}

CEventPedToChase::~CEventPedToChase()
{
    CEntity::SafeCleanUpRef(m_ped);
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
