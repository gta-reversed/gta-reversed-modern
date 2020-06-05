/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "AnimBlendFrameData.h"
#include "CVector.h"

class CPed;

// Return flags from MoveLimb() function
enum MoveLimbResult
{
    CANT_REACH_TARGET,
    HAVENT_REACHED_TARGET,
    REACHED_TARGET
};


struct LimbOrientation
{
public:
    float m_fYaw;
    float m_fPitch;
};
VALIDATE_SIZE(LimbOrientation, 0x8);


struct LimbMovementInfo 
{
    float maxYaw, minYaw;
    float yawD;
    float maxPitch, minPitch;
    float pitchD;
};
VALIDATE_SIZE(LimbMovementInfo, 0x18);

class  CPedIK {
public:
    CPed *m_pPed;
    LimbOrientation m_TorsoOrien;
    float m_fSlopePitch;
    float m_fSlopePitchLimitMult;
    float m_fSlopeRoll;
    float m_fBodyRoll;

    union
    {
        unsigned int m_nFlags;
        struct
        {
            unsigned int bGunReachedTarget : 1;
            unsigned int bTorsoUsed : 1;
            unsigned int bUseArm : 1;
            unsigned int bSlopePitch : 1;
        };
    };

    static RwV3d& XaxisIK;
    static RwV3d& YaxisIK;
    static RwV3d& ZaxisIK;

    //funcs
    void RotateTorso(AnimBlendFrameData* bone, LimbOrientation& orientation, bool flag);
    bool PointGunInDirection(float Z_angle, float arg2, bool flag, float arg4);
    void PointGunAtPosition(CVector const& posn, float arg2);
    static RwMatrixTag* GetWorldMatrix(RwFrame* frame, RwMatrixTag* transformMat);

    static MoveLimbResult MoveLimb(LimbOrientation& TorsoOrien, float yaw, float pitch, LimbMovementInfo &LimbMoveInfo);
    static MoveLimbResult MoveLimb(LimbOrientation& TorsoOrien, float yaw, float pitch, LimbMovementInfo &LimbMoveInfo,
        float fNormalize); 

};

VALIDATE_SIZE(CPedIK, 0x20);
