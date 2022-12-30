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
    CPed* m_pPed;
    LimbOrientation m_TorsoOrient;
    float m_fSlopePitch;
    float m_fSlopePitchLimitMult;
    float m_fSlopeRoll;
    float m_fBodyRoll;

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

    static inline CVector XaxisIK = CVector(1.0f, 0.0f, 0.0f); // 0x8D232C
    static inline CVector YaxisIK = CVector(0.0f, 1.0f, 0.0f); // 0x8D2338
    static inline CVector ZaxisIK = CVector(0.0f, 0.0f, 1.0f); // 0x8D2344

    static inline LimbMovementInfo& ms_torsoInfo = *(LimbMovementInfo*)0x8D22E4;

    CPedIK() = default;
    explicit CPedIK(CPed* ped);

    CPedIK* Constructor(CPed* ped);

    // funcs
    void RotateTorso(AnimBlendFrameData* bone, LimbOrientation& orientation, bool flag);
    void RotateTorsoForArm(CVector const& vec);
    bool PointGunInDirection(float Z_angle, float arg2, bool flag, float arg4);
    void PointGunAtPosition(CVector const& posn, float arg2);
    void PitchForSlope();
    static RwMatrixTag* GetWorldMatrix(RwFrame* frame, RwMatrixTag* transformMat);

    MoveLimbResult MoveLimb(LimbOrientation& TorsoOrien, float yaw, float pitch, LimbMovementInfo& LimbMoveInfo);
    MoveLimbResult MoveLimb(LimbOrientation& TorsoOrien, float yaw, float pitch, LimbMovementInfo& LimbMoveInfo, float fNormalize);

    static void InjectHooks();
};

VALIDATE_SIZE(CPedIK, 0x20);
