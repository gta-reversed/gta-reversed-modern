#include "StdInc.h"

#include "CTaskComplexPolicePursuit.h"

CTaskComplexPolicePursuit* CTaskComplexPolicePursuit::Constructor()
{
    return plugin::CallMethodAndReturn <CTaskComplexPolicePursuit*, 0x68BA70, CTaskComplexPolicePursuit*>(this);
}