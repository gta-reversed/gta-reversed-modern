#include "StdInc.h"

#include "TaskSimpleSetStayInSamePlace.h"

void CTaskSimpleSetStayInSamePlace::InjectHooks()
{
    Install("CTaskSimpleSetStayInSamePlace", "Constructor", 0x62F590, &CTaskSimpleSetStayInSamePlace::Constructor);
    //VTABLE
    Install("CTaskSimpleSetStayInSamePlace", "ProcessPed", 0x62F5E0, &CTaskSimpleSetStayInSamePlace::ProcessPed_Reversed);
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
