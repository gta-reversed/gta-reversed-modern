/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "TaskComplex.h"

//typedef int32 AnimationId;

class NOTSA_EXPORT_VTABLE CTaskComplexPlayHandSignalAnim : public CTaskComplex {
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

public:
    static constexpr auto Type = TASK_COMPLEX_HANDSIGNAL_ANIM;

    CTaskComplexPlayHandSignalAnim(AnimationId animationId, float blendFactor);
    CTask* CreateSubTask(int32 taskType);
    int32 GetAnimIdForPed(CPed* ped);
};

VALIDATE_SIZE(CTaskComplexPlayHandSignalAnim, 0x18);
