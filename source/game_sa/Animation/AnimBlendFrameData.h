/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

struct RpHAnimBlendInterpFrame;

class AnimBlendFrameData {
public:
    union {
        struct {
            uint8 m_bf1 : 1;                                    // doesn't seem to be used
            uint8 m_IsIFrameOrientationToAffectedByNodes : 1;   // m_IFrame orientation will be affected
            uint8 m_IsIFrameTranslationToAffectedByNodes : 1;   // m_IFrame translation will be affected
            uint8 m_bIsInitialized : 1;
            uint8 m_bUpdateSkinnedWith3dVelocityExtraction : 1;
            uint8 m_bCheckBlendNodeClumpKeyFrames : 1;          // key frames of CAninBlendNode bones will be checked
            uint8 m_bIsCompressed : 1;
            uint8 m_bUpdatingFrame : 1;                         // doesn't seem to be used
        };
        uint8 m_nFlags;
    };
    char                     pad[3];
    CVector                  m_vecOffset;
    RpHAnimBlendInterpFrame* m_pIFrame;
    uint32                   m_nNodeId;
};

VALIDATE_SIZE(AnimBlendFrameData, 0x18);
