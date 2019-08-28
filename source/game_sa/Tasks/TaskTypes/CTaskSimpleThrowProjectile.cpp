#include "StdInc.h"

CTaskSimpleThrowProjectile* CTaskSimpleThrowProjectile::Constructor(CEntity* pTarget, CVector Posn)
{
    return plugin::CallMethodAndReturn<CTaskSimpleThrowProjectile*, 0x61F660, CTaskSimpleThrowProjectile*, CEntity*, CVector>(this, pTarget, Posn);
}

bool CTaskSimpleThrowProjectile::ControlThrow(bool bUpdateStartTime, CEntity* pEntity, CEntity* pEntity2)
{
    return plugin::CallMethodAndReturn<bool, 0x61F810, CTaskSimpleThrowProjectile*, bool, CEntity*, CEntity*>(this, bUpdateStartTime, pEntity, pEntity2);
}