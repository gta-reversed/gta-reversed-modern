#pragma once
#include "CTaskComplex.h"
#include "CVector.h"

class CTaskComplexGoToPointAndStandStill : public CTaskComplex 
{
    int m_moveState;
    CVector m_vecTargetPoint;
    float m_fRadius; // ped stops moving after it is within the radius of the point.
    float m_fMoveStateRadius; // The ped will either sprint, run, or walk depending on far it is from the radius
    union {
        struct
        {
            unsigned char m_b01 : 1;
            unsigned char m_b02 : 1;
            unsigned char m_b03 : 1;
            unsigned char m_b04 : 1;
            unsigned char m_b05 : 1;
        };
        unsigned char m_nFlags;
    };
private:
    unsigned char field_25; // padding
};

VALIDATE_SIZE(CTaskComplexGoToPointAndStandStill, 0x28);