/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "TaskSimple.h"
#include "TaskTimer.h"

enum eFacialExpression
{
    ANIM_FACSURP = 0x0,
    ANIM_FACSURPM = 0x1,
    ANIM_FACURIOS = 0x2, // can be 2 or 4
    ANIM_FACANGER = 0x3, // can be 3 or 5
    ANIM_FACTALK = 0x7,
    ANIM_FACGUM = 0x8,
};

class CTaskSimpleFacial : public CTaskSimple {
public:
    CTaskTimer m_Timer;
    eFacialExpression m_nFacialExpression;
    int32 m_nDuration;

    CTaskSimpleFacial(eFacialExpression nFacialExpress,int32 nDuration);
};

VALIDATE_SIZE(CTaskSimpleFacial, 0x1C);
