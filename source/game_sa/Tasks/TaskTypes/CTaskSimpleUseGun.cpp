#include "StdInc.h"

bool CTaskSimpleUseGun::ControlGunMove(CVector2D* moveSpeed)
{
    return plugin::CallMethodAndReturn<bool, 0x61E0C0, CTaskSimpleUseGun*, CVector2D*>(this, moveSpeed);
}