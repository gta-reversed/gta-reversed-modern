#include "StdInc.h"

unsigned int CPedAcquaintance::GetAcquaintances(unsigned int acquaintanceID)
{
    return plugin::CallMethodAndReturn<unsigned int, 0x608970, CPedAcquaintance*, unsigned int>(this, acquaintanceID);
}

void CAcquaintance::SetAsAcquaintance(std::int32_t acquaintanceID, std::int32_t pedFlag)
{
    plugin::CallMethod<0x608DA0, CAcquaintance*, std::int32_t, std::int32_t>(this, acquaintanceID, pedFlag);
}
