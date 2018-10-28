/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"


class  AnimBlendFrameData {
public:
    union {
        struct {
            unsigned char m_bf1 : 1;                                    // doesn't seem to be used
            unsigned char m_IsIFrameOrientationToAffectedByNodes : 1;   // m_IFrame orientation will be affected
            unsigned char m_IsIFrameTranslationToAffectedByNodes : 1;   // m_IFrame translation will be affected
            unsigned char m_bIsInitialized : 1;
            unsigned char m_bUpdateSkinnedWith3dVelocityExtraction : 1;
            unsigned char m_bCheckBlendNodeClumpKeyFrames : 1;          // key frames of CAninBlendNode bones will be checked
            unsigned char m_bIsCompressed : 1;
            unsigned char m_bUpdatingFrame : 1;                         // doesn't seem to be used
        };
        unsigned char m_nFlags;
    };
    char pad[3];
    CVector        m_vecOffset;
    struct RpHAnimBlendInterpFrame *m_pIFrame;
    unsigned int   m_nNodeId;
};

VALIDATE_SIZE(AnimBlendFrameData, 0x18);
