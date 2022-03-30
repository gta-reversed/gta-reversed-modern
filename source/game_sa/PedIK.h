/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <RenderWare.h>
#include "Vector.h"

class AnimBlendFrameData;
class CPed;

// Return flags from MoveLimb() function
enum MoveLimbResult { CANT_REACH_TARGET, HAVENT_REACHED_TARGET, REACHED_TARGET };

struct LimbOrientation {
public:
    float m_fYaw;
    float m_fPitch;

    LimbOrientation() {
        m_fYaw    = 0.0f;
        m_fPitch  = 0.0f;
    }

    LimbOrientation(float yaw, float pitch) : m_fYaw(yaw), m_fPitch(pitch) { }
};
VALIDATE_SIZE(LimbOrientation, 0x8);

struct LimbMovementInfo {
    float maxYaw, minYaw;
    float yawD;
    float maxPitch, minPitch;
    float pitchD;
};
VALIDATE_SIZE(LimbMovementInfo, 0x18);

class CPedIK {
public:
    CPed*           m_pPed;
    LimbOrientation m_TorsoOrien;
    float           m_fSlopePitch;
    float           m_fSlopePitchLimitMult;
    float           m_fSlopeRoll;
    float           m_fBodyRoll;

    union {
        uint32 m_nFlags;
        struct {
            uint32 bGunReachedTarget : 1;
            uint32 bTorsoUsed : 1;
            uint32 bUseArm : 1;
            uint32 bSlopePitch : 1;
            uint32 bUnk : 1;
        };
    };

    static RwV3d& XaxisIK;
    static RwV3d& YaxisIK;
    static RwV3d& ZaxisIK;

public:
    explicit CPedIK(CPed* ped);

    void                RotateTorso(AnimBlendFrameData* bone, LimbOrientation& orientation, bool flag);
    bool                PointGunInDirection(float Z_angle, float arg2, bool flag, float arg4);
    void                PointGunAtPosition(const CVector& posn, float arg2);
    static RwMatrix*    GetWorldMatrix(RwFrame* frame, RwMatrix* transformMat);

    static MoveLimbResult MoveLimb(LimbOrientation& TorsoOrien, float yaw, float pitch, LimbMovementInfo& LimbMoveInfo);
    static MoveLimbResult MoveLimb(LimbOrientation& TorsoOrien, float yaw, float pitch, LimbMovementInfo& LimbMoveInfo, float fNormalize);
};

VALIDATE_SIZE(CPedIK, 0x20);
