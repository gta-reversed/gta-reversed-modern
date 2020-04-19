#pragma once

#include "CTaskSimpleGoTo.h"

class CTaskSimpleGoToPoint : public CTaskSimpleGoTo
{
public:
    union {
        struct
        {
            unsigned char m_bMoveTowardsTargetPoint : 1;
            unsigned char m_b02 : 1;
            unsigned char m_b03 : 1;
            unsigned char m_b04 : 1;
            unsigned char m_b05 : 1;
        } gotoPointFlags;
        unsigned char m_GoToPointFlags;
    };
private:
    unsigned char field_21[3]; // padding
public:
    CVector m_vecLastDuckPosition;

    CTaskSimpleGoToPoint* Constructor(int moveState, CVector* pTargetPos, float fRadius, char a5, char a6);

    // a4 is always zero 
    void UpdatePoint(CVector* pTargetPosition, float fRadius, bool a4);
};

VALIDATE_SIZE(CTaskSimpleGoToPoint, 0x30);