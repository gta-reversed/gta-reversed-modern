/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskSimpleAnim.h"
#include "CAnimBlendHierarchy.h"
#include "CTaskTimer.h"
#include "CVector.h"

class  CTaskSimpleRunNamedAnim : public CTaskSimpleAnim {
protected:
    CTaskSimpleRunNamedAnim(plugin::dummy_func_t a) : CTaskSimpleAnim(a), m_timer(a) {}
public:
    char                 m_animName[24];
    char                 m_animGroupName[16];
    float                m_fBlendDelta;
    CAnimBlendHierarchy* m_pAnimHierarchy;
    int                  m_nTime;
    CTaskTimer           m_timer;
    CVector              m_vecOffsetAtEnd;
    unsigned int         m_nFlags;
    short                m_nAnimId;

    CTaskSimpleRunNamedAnim(const char* pAnimName, const char* pAnimGroupName, int flags, float fBlendDelta,
        int nTime, bool bDontInterrupt, bool bRunInSequence, bool bOffsetPed, bool bHoldLastFrame);


};

VALIDATE_SIZE(CTaskSimpleRunNamedAnim, 0x64);
