/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"
#include "RpHAnimBlendInterpFrame.h"

class AnimBlendFrameData {
public:
    union {
        struct {
            uint8 m_bf1 : 1;                                    // doesn't seem to be used
            uint8 m_IsIFrameOrientationToAffectedByNodes : 1;   // m_IFrame orientation will be affected
            uint8 m_IsIFrameTranslationToAffectedByNodes : 1;   // m_IFrame translation will be affected
            uint8 m_bIsInitialized : 1;
            uint8 m_bUpdateSkinnedWith3dVelocityExtraction : 1;
            uint8 m_bCheckBlendNodeClumpKeyFrames : 1;          // key frames of CAnimBlendNode bones will be checked
            uint8 m_bIsCompressed : 1;
            uint8 m_bUpdatingFrame : 1;                         // doesn't seem to be used
        };
        uint8 m_nFlags;
    };
    CVector                  m_vecOffset;
    RpHAnimBlendInterpFrame* m_pIFrame;
    uint32                   m_nNodeId; // In case of peds it's ePedBone (NOTE: I might be wrong, see `IsPedHeadAbovePos`)

    // NOTSA
    CQuaternion& GetFrameOrientation() const { return m_pIFrame->orientation; }
    CVector& GetFrameTranslation() const { return m_pIFrame->translation; }
};
VALIDATE_SIZE(AnimBlendFrameData, 0x18);
