#include "StdInc.h"

CTaskSimpleGoToPoint* CTaskSimpleGoToPoint::Constructor(int moveState, CVector* pTargetPos, float fRadius, char a5, char a6)
{
    return plugin::CallMethodAndReturn<CTaskSimpleGoToPoint*, 0x667CD0, CTaskSimpleGoToPoint*, int, CVector*, float, char, char>
        (this, moveState, pTargetPos, fRadius, a5, a6);
}

// a4 is always zero 
void CTaskSimpleGoToPoint::UpdatePoint(CVector* pTargetPosition, float fRadius, bool a4)
{
    return plugin::CallMethod<0x645700, CTaskSimpleGoToPoint*, CVector*, float, bool> (this, pTargetPosition, fRadius, a4);
}