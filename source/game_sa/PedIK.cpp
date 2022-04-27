/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

RwV3d& CPedIK::XaxisIK = *(RwV3d*)0x8D232C;
RwV3d& CPedIK::YaxisIK = *(RwV3d*)0x8D2338;
RwV3d& CPedIK::ZaxisIK = *(RwV3d*)0x8D2344;

// 0x5FD8C0
CPedIK::CPedIK(CPed* ped) {
    m_pPed                 = ped;
    m_nFlags               = 0;
    m_fSlopePitch          = 0.0f;
    m_fSlopePitchLimitMult = 0.0f;
    m_fSlopeRoll           = 0.0f;
    m_fBodyRoll            = 0.0f;
}

// 0x5FDDB0 
void CPedIK::RotateTorso(AnimBlendFrameData* bone, LimbOrientation& orientation, bool flag) {
    plugin::CallMethod<0x5FDDB0, CPedIK*, AnimBlendFrameData*, LimbOrientation&, bool>(this, bone, orientation, flag);
}

// 0x5FDC00 
bool CPedIK::PointGunInDirection(float Z_angle, float arg2, bool flag, float arg4) {
    return plugin::CallMethodAndReturn<bool, 0x5FDC00, CPedIK*, float, float, bool, float>(this, Z_angle, arg2, flag, arg4);
}

// 0x5FDE20
void CPedIK::PointGunAtPosition(const CVector& posn, float arg2) {
    plugin::CallMethod<0x5FDE20, CPedIK*, const CVector&, float>(this, posn, arg2);
}

// 0x5FD8F0 
RwMatrix* CPedIK::GetWorldMatrix(RwFrame* frame, RwMatrix* transformMat) {
    return plugin::CallAndReturn<RwMatrix*, 0x5FD8F0, RwFrame*, RwMatrix*>(frame, transformMat);
}

MoveLimbResult CPedIK::MoveLimb(LimbOrientation& TorsoOrien, float yaw, float pitch, LimbMovementInfo& LimbMoveInfo)
{
    return plugin::CallAndReturn<MoveLimbResult, 0x5FDA60, LimbOrientation&, float, float, LimbMovementInfo&>
        (TorsoOrien, yaw, pitch, LimbMoveInfo);
}

MoveLimbResult CPedIK::MoveLimb(LimbOrientation& TorsoOrien, float yaw, float pitch, LimbMovementInfo& LimbMoveInfo,
    float fNormalize)
{
    return plugin::CallAndReturn<MoveLimbResult, 0x5FDB60, LimbOrientation&, float, float, LimbMovementInfo&, float>
        (TorsoOrien, yaw, pitch, LimbMoveInfo, fNormalize);
}
