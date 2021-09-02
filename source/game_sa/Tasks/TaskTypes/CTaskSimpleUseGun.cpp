#include "StdInc.h"

CTaskSimpleUseGun* CTaskSimpleUseGun::Constructor(CEntity* pTargetEntity, CVector vecTarget, uint8 nCommand, uint16 nBurstLength, bool bAimImmediate)
{
    return plugin::CallMethodAndReturn<CTaskSimpleUseGun*, 0x61DE60, CTaskSimpleUseGun* , CEntity*, CVector, uint8, uint16, bool>
        (this, pTargetEntity, vecTarget, nCommand, nBurstLength, bAimImmediate);
}

bool CTaskSimpleUseGun::ControlGunMove(CVector2D* moveSpeed)
{
    return plugin::CallMethodAndReturn<bool, 0x61E0C0, CTaskSimpleUseGun*, CVector2D*>(this, moveSpeed);
}

bool CTaskSimpleUseGun::PlayerPassiveControlGun()
{
    return plugin::CallMethodAndReturn<bool, 0x61E0A0, CTaskSimpleUseGun*>(this);
}

bool CTaskSimpleUseGun::RequirePistolWhip(CPed* pPed, CEntity* pTargetEntity)
{
    return plugin::CallAndReturn<bool, 0x61E200, CPed*, CEntity*>(pPed, pTargetEntity);
}

bool CTaskSimpleUseGun::ControlGun(CPed* pPed, CEntity* target, char nCount)
{
    return plugin::CallMethodAndReturn<bool, 0x61E040, CTaskSimpleUseGun*, CPed*, CEntity*, char>(this, pPed, target, nCount);
}

int32 CTaskSimpleUseGun::SkipAim(CPed* pPed)
{
    return plugin::CallMethodAndReturn<int32, 0x61DFA0, CTaskSimpleUseGun*, CPed*>(this, pPed);
}

int32 CTaskSimpleUseGun::ClearAnim(CPed* pPed)
{
    return plugin::CallMethodAndReturn<int32, 0x61E190, CTaskSimpleUseGun*, CPed*>(this, pPed);
}