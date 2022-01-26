#include "StdInc.h"

#include "TaskSimpleSetStayInSamePlace.h"

void CTaskSimpleSetStayInSamePlace::InjectHooks()
{
    RH_ScopedInstall(Constructor, 0x62F590);
    //VTABLE
    RH_ScopedInstall(ProcessPed_Reversed, 0x62F5E0);
}

CTaskSimpleSetStayInSamePlace* CTaskSimpleSetStayInSamePlace::Constructor(bool bStayInSamePlace)
{
    this->CTaskSimpleSetStayInSamePlace::CTaskSimpleSetStayInSamePlace(bStayInSamePlace);
    return this;
}

// 0x62F590
CTaskSimpleSetStayInSamePlace::CTaskSimpleSetStayInSamePlace(bool bStayInSamePlace)
{
    m_bStayInSamePlace = bStayInSamePlace;
}

// 0x62F5E0
bool CTaskSimpleSetStayInSamePlace::ProcessPed(CPed* ped)
{
    return ProcessPed_Reversed(ped);
}

bool CTaskSimpleSetStayInSamePlace::ProcessPed_Reversed(CPed* ped)
{
    ped->bStayInSamePlace = m_bStayInSamePlace;
    return true;
}
