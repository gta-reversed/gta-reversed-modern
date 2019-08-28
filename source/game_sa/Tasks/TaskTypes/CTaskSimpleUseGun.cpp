#include "StdInc.h"

CTaskSimpleUseGun* CTaskSimpleUseGun::Constructor(CEntity* pTargetEntity, CVector vecTarget, unsigned char nCommand, unsigned short nBurstLength, bool bAimImmediate)
{
    return plugin::CallMethodAndReturn<CTaskSimpleUseGun*, 0x61DE60, CTaskSimpleUseGun* , CEntity*, CVector, unsigned char, unsigned short, bool>
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

int CTaskSimpleUseGun::SkipAim(CPed* pPed)
{
    return plugin::CallMethodAndReturn<int, 0x61DFA0, CTaskSimpleUseGun*, CPed*>(this, pPed);
}