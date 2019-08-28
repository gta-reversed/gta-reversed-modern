#include "StdInc.h"

CEventGunAimedAt* CEventGunAimedAt::Constructor(CPed* pPed)
{
    return plugin::CallMethodAndReturn<CEventGunAimedAt*, 0x4B0700, CEventGunAimedAt*, CPed*>(this, pPed);
}

void CEventGunAimedAt::Destructor()
{
    return plugin::CallMethod<0x4B07B0, CEventGunAimedAt*>(this);
}