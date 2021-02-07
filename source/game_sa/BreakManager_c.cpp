#include "StdInc.h"

BreakManager_c& g_breakMan = *(BreakManager_c*)0xBB4240;

void BreakManager_c::InjectHooks()
{
}

BreakObject_c* BreakManager_c::Add(CObject* pObject, RwV3d* vecPos, float fVelocityRand, bool bSmash)
{
    return plugin::CallMethodAndReturn<BreakObject_c*, 0x59E9B0, BreakManager_c*, CObject*, RwV3d*, float, bool>
        (this, pObject, vecPos, fVelocityRand, bSmash);
}
