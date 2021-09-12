#include "StdInc.h"

#include "CPedAcquaintance.h"

enum {
    ACQUAINTANCE_RESPECT,
    ACQUAINTANCE_LIKE,
    ACQUAINTANCE_IGNORE,
    ACQUAINTANCE_DISLIKE,
    ACQUAINTANCE_HATE,
};

void CAcquaintance::InjectHooks() {
    using namespace ReversibleHooks;
    // Install("CAcquaintance", "GetAcquaintances", 0x608970, &CAcquaintance::GetAcquaintances);
    // Install("CAcquaintance", "SetAcquaintances", 0x608960, &CAcquaintance::SetAcquaintances);
    // Install("CAcquaintance", "ClearAcquaintances", 0x6089A0, &CAcquaintance::ClearAcquaintances);
    // Install("CAcquaintance", "SetAsAcquaintance", 0x608DA0, &CAcquaintance::SetAsAcquaintance);
    // Install("CAcquaintance", "ClearAsAcquaintance", 0x608980, &CAcquaintance::ClearAsAcquaintance);
}

// 0x608AE0
CAcquaintance::CAcquaintance() {
    m_nRespect = 0;
    m_nLike    = 0;
    m_nIgnore  = 0;
    m_nDislike = 0;
    m_nHate    = 0;
}

// 0x608780
CAcquaintance::~CAcquaintance() {
    // NOP
}

// 0x608970
uint32 CAcquaintance::GetAcquaintances(AcquaintanceId id) {
    return plugin::CallMethodAndReturn<uint32, 0x608970, CAcquaintance*, AcquaintanceId>(this, id);
}

// 0x608960
void CAcquaintance::SetAcquaintances(AcquaintanceId id, uint32 value) {
    plugin::CallMethod<0x608960, CAcquaintance*, AcquaintanceId, uint32>(this, id, value);
}

// 0x6089A0
void CAcquaintance::ClearAcquaintances(AcquaintanceId id) {
    plugin::CallMethod<0x6089A0, CAcquaintance*, AcquaintanceId>(this, id);
}

// 0x608DA0
void CAcquaintance::SetAsAcquaintance(AcquaintanceId id, uint32 pedTypeBitNum) {
    plugin::CallMethod<0x608DA0, CAcquaintance*, AcquaintanceId, uint32>(this, id, pedTypeBitNum);
}


// 0x608980
void CAcquaintance::ClearAsAcquaintance(AcquaintanceId id, uint32 pedTypeBitNum) {
    plugin::CallMethod<0x608980, CAcquaintance*, AcquaintanceId, int32>(this, id, pedTypeBitNum);
}
