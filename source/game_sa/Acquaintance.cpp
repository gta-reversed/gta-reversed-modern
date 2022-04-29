#include "StdInc.h"

#include "Acquaintance.h"

void CAcquaintance::InjectHooks() {
    RH_ScopedClass(CAcquaintance);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(GetAcquaintances, 0x608970);
    RH_ScopedInstall(SetAcquaintances, 0x608960);
    RH_ScopedInstall(ClearAcquaintances, 0x6089A0);
    RH_ScopedInstall(SetAsAcquaintance, 0x608DA0);
    RH_ScopedInstall(ClearAsAcquaintance, 0x608980);
}

// 0x608AE0
CAcquaintance::CAcquaintance() {
    m_nRespect = 0;
    m_nLike    = 0;
    m_nIgnore  = 0;
    m_nDislike = 0;
    m_nHate    = 0;
}

// 0x608970
uint32 CAcquaintance::GetAcquaintances(AcquaintanceId id) {
    return m_acquaintances[id];
}

// 0x608960
void CAcquaintance::SetAcquaintances(AcquaintanceId id, uint32 value) {
    m_acquaintances[id] = value;
}

// 0x6089A0
void CAcquaintance::ClearAcquaintances(AcquaintanceId id) {
    m_acquaintances[id] = 0;
}

// 0x608DA0
void CAcquaintance::SetAsAcquaintance(AcquaintanceId id, uint32 pedTypeBitNum) {
    auto acquaintances = GetAcquaintances(id);
    if ((acquaintances & pedTypeBitNum) != 0)
        return;

    SetAcquaintances(id, pedTypeBitNum | acquaintances);

    for (auto i = 0; i < ACQUAINTANCE_NUM; i++) {
        if (id != i) {
            ClearAsAcquaintance(i, pedTypeBitNum);
        }
    }
}

// 0x608980
void CAcquaintance::ClearAsAcquaintance(AcquaintanceId id, uint32 pedTypeBitNum) {
    auto acquaintances = GetAcquaintances(id);
    if ((acquaintances & pedTypeBitNum) != 0) {
        SetAcquaintances(id, acquaintances & ~pedTypeBitNum);
    }
}
