#include "StdInc.h"

#include "EntityScanner.h"

void CEntityScanner::InjectHooks() {
    RH_ScopedClass(CEntityScanner);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Clear, 0x5FF9D0, { .reversed = false });
    RH_ScopedInstall(ScanForEntitiesInRange, 0x5FFA20, { .reversed = false });
}

// 0x5FF990
CEntityScanner::CEntityScanner() {
    field_4 = 0;
    m_nCount = 0;
    std::ranges::fill(m_apEntities, nullptr);
    m_pClosestEntityInRange = nullptr;
    m_nCount = 16;
}

// 0x603480
CEntityScanner::~CEntityScanner() {
    Clear();
}

// 0x5FF9D0
void CEntityScanner::Clear() {
    plugin::CallMethod<0x5FF9D0, CEntityScanner*>(this);
}

// 0x5FFA20
void CEntityScanner::ScanForEntitiesInRange(eRepeatSectorList sectorList, const CPed& ped) {
    plugin::CallMethod<0x5FFA20, CEntityScanner*, eRepeatSectorList, const CPed&>(this, sectorList, ped);
}
