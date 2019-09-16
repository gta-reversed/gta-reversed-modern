#include "StdInc.h"

CEventSoundQuiet* CEventSoundQuiet::Constructor(CEntity* pEntity, float a3, int startTime, CVector* position)
{
    return plugin::CallMethodAndReturn<CEventSoundQuiet*, 0x5E05B0, CEventSoundQuiet*, CEntity*, float, int, CVector*>
        (this, pEntity, a3, startTime, position);
}

CEventSoundQuiet* CEventSoundQuiet::Destructor()
{
    return plugin::CallMethodAndReturn<CEventSoundQuiet*, 0x5DEA00, CEventSoundQuiet*>(this);
}