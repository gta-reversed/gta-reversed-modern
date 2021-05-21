#include "StdInc.h"

void CEntityScanner::InjectHooks() {
//    ReversibleHooks::Install("CEntityScanner", "Clear", 0x5FF9D0, &CEntityScanner::Clear);
//    ReversibleHooks::Install("CEntityScanner", "ScanForEntitiesInRange", 0x5FFA20, &CEntityScanner::ScanForEntitiesInRange);
    ReversibleHooks::Install("CEntityScanner", "GetClosestPedInRange", 0x5FFF20, &CEntityScanner::GetClosestPedInRange);
}

// 0x5FF9D0
void CEntityScanner::Clear()
{
    plugin::CallMethod<0x5FF9D0, CEntityScanner*>(this);
}

// 0x5FFA20
void CEntityScanner::ScanForEntitiesInRange(int arg2, CPed* pPed)
{
    plugin::CallMethod<0x5FFA20, CEntityScanner*, int, CPed*>(this, arg2, pPed);
}

// 0x5FFF20
CEntity* CEntityScanner::GetClosestPedInRange()
{
    return m_pClosestEntityInRange;
}
