#include "StdInc.h"

void CAcquaintance::InjectHooks() {
//    ReversibleHooks::Install("CAcquaintance", "GetAcquaintances", 0x608970, &CAcquaintance::GetAcquaintances);
//    ReversibleHooks::Install("CAcquaintance", "SetAcquaintances", 0x608960, &CAcquaintance::SetAcquaintances);
//    ReversibleHooks::Install("CAcquaintance", "ClearAcquaintances", 0x6089A0, &CAcquaintance::ClearAcquaintances);
//    ReversibleHooks::Install("CAcquaintance", "SetAsAcquaintance", 0x608DA0, &CAcquaintance::SetAsAcquaintance);
//    ReversibleHooks::Install("CAcquaintance", "ClearAsAcquaintance", 0x608980, &CAcquaintance::ClearAsAcquaintance);
}

// 0x608970
unsigned int CAcquaintance::GetAcquaintances(unsigned int acquaintanceID) {
    return plugin::CallMethodAndReturn<unsigned int, 0x608970, CAcquaintance*, unsigned int>(this, acquaintanceID);
}

// 0x608960
void CAcquaintance::SetAcquaintances(int acquaintanceId, unsigned int value) {
    plugin::CallMethod<0x608960, CAcquaintance*, int, unsigned int>(this, acquaintanceId, value);
}

// 0x6089A0
void CAcquaintance::ClearAcquaintances(unsigned int acquaintanceId) {
    plugin::CallMethod<0x6089A0, CAcquaintance*, unsigned int>(this, acquaintanceId);
}

// 0x608DA0
void CAcquaintance::SetAsAcquaintance(unsigned int acquaintanceId, unsigned int pedTypeBitNum) {
    plugin::CallMethod<0x608DA0, CAcquaintance*, unsigned int, unsigned int>(this, acquaintanceId, pedTypeBitNum);
}

// 0x608980
void CAcquaintance::ClearAsAcquaintance(unsigned int acquaintanceId, unsigned int pedTypeBitNum) {
    plugin::CallMethod<0x608980, CAcquaintance*, unsigned int, int>(this, acquaintanceId, pedTypeBitNum);
}

// 0x608AE0
CPedAcquaintance::CPedAcquaintance() {
    m_nRespect = 0;
    m_nLike = 0;
    m_nIgnore = 0;
    m_nDislike = 0;
    m_nHate = 0;
}

// 0x608780
CPedAcquaintance::~CPedAcquaintance() {
    // NOP
}
