/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "CTaskComplex.h"

//typedef int32 AnimationId;

class CTaskComplexPlayHandSignalAnim : public CTaskComplex {
public:
    int32   m_animationId;
    float m_fBlendFactor;
    union {
        uint8 m_nFlags;
        struct
        {
            uint8 m_bLeftHandLoaded : 1;
            uint8 m_bRightHandLoaded : 1;
            uint8 m_bAnimationLoaded : 1;
            uint8 m_bUseFatHands : 1;
        };
    };
    uint8 _pad[3];

    CTaskComplexPlayHandSignalAnim(AnimationId animationId, float blendFactor);
    CTask* CreateSubTask(int32 taskType);
    int32 GetAnimIdForPed(CPed* ped);
};

VALIDATE_SIZE(CTaskComplexPlayHandSignalAnim, 0x18);
