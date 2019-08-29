#include "StdInc.h"

unsigned int CPedAcquaintance::GetAcquaintances(unsigned int acquaintanceID)
{
    return plugin::CallMethodAndReturn<unsigned int, 0x608970, CPedAcquaintance*, unsigned int>(this, acquaintanceID);
}