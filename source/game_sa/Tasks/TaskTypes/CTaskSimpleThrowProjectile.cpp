#include "StdInc.h"

bool CTaskSimpleThrowProjectile::ControlThrow(bool bUpdateStartTime, CEntity* pEntity, CEntity* pEntity2)
{
    return plugin::CallMethodAndReturn<bool, 0x61F810, CTaskSimpleThrowProjectile*, bool, CEntity*, CEntity*>(this, bUpdateStartTime, pEntity, pEntity2);
}