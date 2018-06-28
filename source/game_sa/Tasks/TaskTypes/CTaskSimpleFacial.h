/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskSimple.h"
#include "CTaskTimer.h"

enum eFacialExpression
{
    ANIM_FACSURP = 0x0,
    ANIM_FACSURPM = 0x1,
    ANIM_FACURIOS = 0x2, // can be 2 or 4
    ANIM_FACANGER = 0x3, // can be 3 or 5
    ANIM_FACTALK = 0x7,
    ANIM_FACGUM = 0x8,
};

class  CTaskSimpleFacial : public CTaskSimple {
protected:
    CTaskSimpleFacial(plugin::dummy_func_t a) : CTaskSimple(a), m_Timer(a) {}
public:
    CTaskTimer m_Timer;
    eFacialExpression m_nFacialExpression;
    int m_nDuration;

    CTaskSimpleFacial(eFacialExpression nFacialExpress,int nDuration);
};

VALIDATE_SIZE(CTaskSimpleFacial, 0x1C);
