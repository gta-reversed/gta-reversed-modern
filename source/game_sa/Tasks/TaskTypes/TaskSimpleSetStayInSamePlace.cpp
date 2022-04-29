#include "StdInc.h"

#include "TaskSimpleSetStayInSamePlace.h"

void CTaskSimpleSetStayInSamePlace::InjectHooks()
{
    RH_ScopedClass(CTaskSimpleSetStayInSamePlace);
    RH_ScopedCategory("Tasks/TaskTypes");
    RH_ScopedInstall(Constructor, 0x62F590);
    //VTABLE
    RH_ScopedVirtualInstall(ProcessPed, 0x62F5E0);
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
