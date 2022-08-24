#include "StdInc.h"

#include "TaskSimpleSetStayInSamePlace.h"

// 0x62F590
CTaskSimpleSetStayInSamePlace::CTaskSimpleSetStayInSamePlace(bool bStayInSamePlace) : CTaskSimple() {
    m_bStayInSamePlace = bStayInSamePlace;
}

// 0x62F5E0
bool CTaskSimpleSetStayInSamePlace::ProcessPed(CPed* ped) {
    ped->bStayInSamePlace = m_bStayInSamePlace;
    return true;
}
