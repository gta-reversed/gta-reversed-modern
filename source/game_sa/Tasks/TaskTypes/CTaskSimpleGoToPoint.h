#pragma once

#include "CTaskSimpleGoTo.h"

class CTaskSimpleGoToPoint : public CTaskSimpleGoTo
{
public:
    CVector field_24;

    CTaskSimpleGoToPoint* Constructor(int moveState, CVector* pTargetPos, float fRadius, char a5, char a6);

    // a4 is always zero 
    void UpdatePoint(CVector* pTargetPosition, float fRadius, bool a4);
};

VALIDATE_SIZE(CTaskSimpleGoToPoint, 0x30);