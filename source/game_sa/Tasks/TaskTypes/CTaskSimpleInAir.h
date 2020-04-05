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
#include "CVector.h"
#include "CAnimBlendAssociation.h"
#include "CEntity.h"

class  CTaskSimpleInAir : public CTaskSimple {
public:
    CVector m_vecPosn;
    float m_fAngle;
    unsigned char m_nSurfaceType;
    char _pad[3];
    CAnimBlendAssociation *m_pAnim;
    float m_fHeight;
    union {
        unsigned char m_nFlags;
        struct
        {
            unsigned char bUsingJumpGlide : 1;
            unsigned char bUsingFallGlide : 1;
            unsigned char bUsingClimbJump : 1;
        };
    };
    char _pad2[3];
    int m_nProcessCounter;
    CTaskTimer m_timer;
    CEntity *m_pEntity;
    CTaskSimpleInAir(bool bUsingJumpGlide, bool bUsingFallGlide, bool bUsingClimbJump);

};

VALIDATE_SIZE(CTaskSimpleInAir, 0x3C);