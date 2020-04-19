#pragma once
#include "CTaskSimple.h"
#include "CVector.h"

class CTaskSimpleGoTo : public CTaskSimple
{
    CTaskSimpleGoTo() = delete;
public:
    int     m_moveState;
    CVector m_vecTargetPoint;
    float   m_fRadius;
    union {
        struct 
        {
            unsigned char m_b01 : 1;
            unsigned char m_b02 : 1;
            unsigned char m_b03 : 1;
            unsigned char m_b04 : 1;
            unsigned char m_b05 : 1;
            unsigned char m_bTargetPointUpdated : 1;
        } gotoFlags;
        unsigned char m_GoToFlags;
    };
private:
    unsigned char field_1D[3]; // padding
};

VALIDATE_SIZE(CTaskSimpleGoTo, 0x20);