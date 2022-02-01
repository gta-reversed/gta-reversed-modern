/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "TaskSimpleAnim.h"
#include "AnimBlendHierarchy.h"
#include "TaskTimer.h"
#include "Vector.h"

class CTaskSimpleRunNamedAnim : public CTaskSimpleAnim {
public:
    char                 m_animName[24];
    char                 m_animGroupName[16];
    float                m_fBlendDelta;
    CAnimBlendHierarchy* m_pAnimHierarchy;
    int32                  m_nTime;
    CTaskTimer           m_timer;
    CVector              m_vecOffsetAtEnd;
    uint32         m_nFlags;
    int16                m_nAnimId;

    CTaskSimpleRunNamedAnim(const char* pAnimName, const char* pAnimGroupName, int32 flags, float fBlendDelta,
        int32 nTime, bool bDontInterrupt, bool bRunInSequence, bool bOffsetPed, bool bHoldLastFrame);


};

VALIDATE_SIZE(CTaskSimpleRunNamedAnim, 0x64);
