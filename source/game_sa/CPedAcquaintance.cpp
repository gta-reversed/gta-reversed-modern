#include "StdInc.h"

void CAcquaintance::InjectHooks() {
//    ReversibleHooks::Install("CAcquaintance", "GetAcquaintances", 0x608970, &CAcquaintance::GetAcquaintances);
//    ReversibleHooks::Install("CAcquaintance", "SetAcquaintances", 0x608960, &CAcquaintance::SetAcquaintances);
//    ReversibleHooks::Install("CAcquaintance", "ClearAcquaintances", 0x6089A0, &CAcquaintance::ClearAcquaintances);
//    ReversibleHooks::Install("CAcquaintance", "SetAsAcquaintance", 0x608DA0, &CAcquaintance::SetAsAcquaintance);
//    ReversibleHooks::Install("CAcquaintance", "ClearAsAcquaintance", 0x608980, &CAcquaintance::ClearAsAcquaintance);
}

// 0x608970
uint32 CAcquaintance::GetAcquaintances(uint32 acquaintanceID) {
    return plugin::CallMethodAndReturn<uint32, 0x608970, CAcquaintance*, uint32>(this, acquaintanceID);
}

// 0x608960
void CAcquaintance::SetAcquaintances(int32 acquaintanceId, uint32 value) {
    plugin::CallMethod<0x608960, CAcquaintance*, int32, uint32>(this, acquaintanceId, value);
}

// 0x6089A0
void CAcquaintance::ClearAcquaintances(uint32 acquaintanceId) {
    plugin::CallMethod<0x6089A0, CAcquaintance*, uint32>(this, acquaintanceId);
}

// 0x608DA0
void CAcquaintance::SetAsAcquaintance(uint32 acquaintanceId, uint32 pedTypeBitNum) {
    plugin::CallMethod<0x608DA0, CAcquaintance*, uint32, uint32>(this, acquaintanceId, pedTypeBitNum);
}

// 0x608980
void CAcquaintance::ClearAsAcquaintance(uint32 acquaintanceId, uint32 pedTypeBitNum) {
    plugin::CallMethod<0x608980, CAcquaintance*, uint32, int32>(this, acquaintanceId, pedTypeBitNum);
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
