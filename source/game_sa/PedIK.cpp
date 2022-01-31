/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

RwV3d& CPedIK::XaxisIK = *(RwV3d*)0x8D232C;
RwV3d& CPedIK::YaxisIK = *(RwV3d*)0x8D2338;
RwV3d& CPedIK::ZaxisIK = *(RwV3d*)0x8D2344;

bool& bRotateWithNeck = *(bool*)0x8D2354;

LimbMovementInfo& CPedIK::ms_torsoInfo = *(LimbMovementInfo*)0x8D22E4;

void CPedIK::InjectHooks() {
    ReversibleHooks::Install("CPedIK", "Constructor", 0x5FD8C0, &CPedIK::Constructor);
    ReversibleHooks::Install("CPedIK", "RotateTorso", 0x5FDDB0, &CPedIK::RotateTorso);
    ReversibleHooks::Install("CPedIK", "RotateTorsoForArm", 0x5FDF90, &CPedIK::RotateTorsoForArm);
    ReversibleHooks::Install("CPedIK", "MoveLimb1", 0x5FDA60, (MoveLimbResult(CPedIK::*)(LimbOrientation&, float, float, LimbMovementInfo&))(&CPedIK::MoveLimb));
    ReversibleHooks::Install("CPedIK", "MoveLimb2", 0x5FDB60, (MoveLimbResult(CPedIK::*)(LimbOrientation&, float, float, LimbMovementInfo&, float))(&CPedIK::MoveLimb));
    ReversibleHooks::Install("CPedIK", "PointGunAtPosition", 0x5FDE20, &CPedIK::PointGunAtPosition);
    ReversibleHooks::Install("CPedIK", "PointGunInDirection", 0x5FDC00, &CPedIK::PointGunInDirection);
    ReversibleHooks::Install("CPedIK", "PitchForSlope", 0x5FE0E0, &CPedIK::PitchForSlope);
}

CPedIK* CPedIK::Constructor(CPed* ped) {
    this->CPedIK::CPedIK(ped);
    return this;
}

CPedIK::CPedIK(CPed* ped) {
    m_pPed = ped;
    m_nFlags = 0;
    m_TorsoOrient.m_fYaw = 0.0f;
    m_TorsoOrient.m_fPitch = 0.0f;
    m_fSlopePitch = 0.0f;
    m_fSlopePitchLimitMult = 0.0f;
    m_fSlopeRoll = 0.0f;
    m_fBodyRoll = 0.0f;
}

// 0x5FDDB0
void CPedIK::RotateTorso(AnimBlendFrameData* bone, LimbOrientation& orientation, bool changeRoll) {
    RtQuat* q = &bone->m_pIFrame->orientation;
    RtQuatRotate(q, &XaxisIK, RadiansToDegrees(orientation.m_fYaw), rwCOMBINEREPLACE);
    RtQuatRotate(q, &ZaxisIK, RadiansToDegrees(orientation.m_fPitch), rwCOMBINEPRECONCAT);
    m_pPed->bDontAcceptIKLookAts = true;
}

void CPedIK::RotateTorsoForArm(CVector const& dir) {
    CVector origin = m_pPed->GetPosition();
    float fDestRotation = atan2(-(dir.x - origin.x), dir.y - origin.y);

    if ((m_pPed->m_fCurrentRotation + PI) < fDestRotation) {
        fDestRotation -= TWO_PI;
    } else {
        if ((m_pPed->m_fCurrentRotation - PI) > fDestRotation)
            fDestRotation += TWO_PI;
    }

    float diffAngle = fDestRotation - m_pPed->m_fCurrentRotation;
    float fResultAngle = QUARTER_PI;

    if (diffAngle > QUARTER_PI) {
        if (diffAngle <= HALF_PI)
            fResultAngle = diffAngle - QUARTER_PI;
    } else {
        if (diffAngle >= DegreesToRadians(-60.0f))
            return;

        fResultAngle = diffAngle + DegreesToRadians(60.0f);

        if (diffAngle < DegreesToRadians(-80.0f))
            fResultAngle = DegreesToRadians(-20.0f);
    }

    if (fResultAngle != 0.0f) {
        float fConvertedAngle = RadiansToDegrees(fResultAngle / 2.0f);
        if (bRotateWithNeck) { // android doesn't have this check
            RtQuatRotate(&m_pPed->m_apBones[PED_NODE_NECK]->m_pIFrame->orientation, &XaxisIK, fConvertedAngle, rwCOMBINEPOSTCONCAT);
        }
        RtQuatRotate(&m_pPed->m_apBones[PED_NODE_UPPER_TORSO]->m_pIFrame->orientation, &XaxisIK, fConvertedAngle, rwCOMBINEPOSTCONCAT);
    }
}

bool CPedIK::PointGunInDirection(float Z_angle, float dist, bool flag, float fNormalize) {
    bool bCanReach = true;
    bGunReachedTarget = false;
    bTorsoUsed = true;

    float fAngle = CGeneral::LimitRadianAngle(Z_angle - m_pPed->m_fCurrentRotation);
    auto hier = GetAnimHierarchyFromSkinClump(m_pPed->m_pRwClump);
    auto idx = RpHAnimIDGetIndex(hier, m_pPed->m_apBones[PED_NODE_RIGHT_CLAVICLE]->m_nNodeId);
    RwMatrix* pBone = RwMatrixCreate();
    pBone = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
    RwMatrixDestroy(pBone);

    MoveLimbResult limbRes;
    if (fNormalize < 0.0f) {
        limbRes = MoveLimb(m_TorsoOrient, fAngle, dist, ms_torsoInfo);
    } else {
        limbRes = MoveLimb(m_TorsoOrient, fAngle, dist, ms_torsoInfo, fNormalize);
    }

    if (limbRes == CANT_REACH_TARGET) {
        bCanReach = false;
    } else if (limbRes == REACHED_TARGET) {
        bGunReachedTarget = true;
    }

    auto head = &RpHAnimHierarchyGetMatrixArray(hier)[PED_NODE_HEAD];
    float fHeadAngle = atan2(-head->at.y, -head->at.x) - m_pPed->m_fCurrentRotation;
    fHeadAngle = -CGeneral::LimitRadianAngle(fHeadAngle);

    RwV3d axis(0.0f, 0.0f, 0.0f);
    if (flag) {
        axis.y = cos(fHeadAngle);
        axis.z = sin(fHeadAngle);
    } else {
        axis.y = -sin(fHeadAngle);
        axis.z = cos(fHeadAngle);
    }

    auto Torsoframe = m_pPed->m_apBones[PED_NODE_UPPER_TORSO]->m_pIFrame;
    RtQuatRotate(&Torsoframe->orientation, &axis, RadiansToDegrees(m_TorsoOrient.m_fPitch), rwCOMBINEPOSTCONCAT);
    RtQuatRotate(&Torsoframe->orientation, &XaxisIK, RadiansToDegrees(m_TorsoOrient.m_fYaw), rwCOMBINEPOSTCONCAT);
    m_pPed->bUpdateMatricesRequired = true;

    return bCanReach;
}

// Converted from thiscall void CPedIK::PointGunAtPosition(CVector const& posn,float arg2)	0x5FDE20
void CPedIK::PointGunAtPosition(CVector const& posn, float fNormalize) {
    auto WeaponInfo = CWeaponInfo::GetWeaponInfo(m_pPed->GetActiveWeapon().m_nType, m_pPed->GetWeaponSkill());
    CVector origin = m_pPed->GetPosition();

    CVector newRight;
    if (m_pPed->bIsDucking) {
        newRight = CWeaponInfo::ms_aWeaponAimOffsets[WeaponInfo->m_nAimOffsetIndex].DuckX * m_pPed->GetRight();
    } else {
        newRight = CWeaponInfo::ms_aWeaponAimOffsets[WeaponInfo->m_nAimOffsetIndex].AimX * m_pPed->GetRight();
    }

    CVector newPos = newRight + origin;

    CVector newUp;
    if (m_pPed->bIsDucking) {
        newUp = CWeaponInfo::ms_aWeaponAimOffsets[WeaponInfo->m_nAimOffsetIndex].DuckZ * m_pPed->GetUp();
    } else {
        newUp = CWeaponInfo::ms_aWeaponAimOffsets[WeaponInfo->m_nAimOffsetIndex].AimZ * m_pPed->GetUp();
    }

    newPos += newUp;

    auto fAngle = CGeneral::GetRadianAngleBetweenPoints(posn.x, posn.y, newPos.x, newPos.y);
    CVector2D diff = (CVector2D)newPos - (CVector2D)posn;
    float dist = diff.Magnitude();

    PointGunInDirection(fAngle, CGeneral::GetRadianAngleBetweenPoints(posn.z, dist, newPos.z, 0.0f), false, fNormalize);
}

void CPedIK::PitchForSlope() {
    auto clumpData = RpClumpGetAnimBlendClumpData(m_pPed->m_pRwClump);
    auto hier = GetAnimHierarchyFromSkinClump(m_pPed->m_pRwClump);

    if (abs(m_fBodyRoll) > 0.01f) {
        m_fBodyRoll = clamp(m_fBodyRoll, -PI_6, PI_6);
    }

    if (!m_pPed->IsDyingOrDead()) {
        float offset;
        if (abs(m_fSlopePitch) > 0.01f) {
            offset = 0.1f;
            if (m_pPed->m_nMoveState == 4) { // TODO: find enum
                offset = 0.085f;
            }

            m_fSlopePitchLimitMult = (m_fSlopePitchLimitMult * 0.9f) + offset;

            float lowBound = m_fSlopePitchLimitMult * DegreesToRadians(-35.0f);
            float highBound = m_fSlopePitchLimitMult * PI_6;
            m_fSlopePitch = clamp(m_fSlopePitch, lowBound, highBound);
        }

        if (abs(m_fSlopeRoll) > 0.01f) {
            m_fSlopeRoll = clamp(m_fSlopeRoll, DegreesToRadians(-45.0f), DegreesToRadians(45.0f));
        }

        if (abs(m_fSlopePitch) > 0.01f) {
            auto idx = RpHAnimIDGetIndex(hier, BONE_SPINE);
            auto tmpHier = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
            if (&m_pPed->GetIntelligence()->m_TaskMgr && m_pPed->GetIntelligence()->m_TaskMgr.GetActiveTask()->GetTaskType() == 1027) // TODO: find enum
            {
                RtQuatRotate(&clumpData->frames[idx].m_pIFrame->orientation, &ZaxisIK, RadiansToDegrees(m_fSlopePitch), rwCOMBINEPRECONCAT);
                m_pPed->bUpdateMatricesRequired = true;
            } else {
                float fAngle;
                fAngle = RadiansToDegrees(-m_fSlopePitch) * 0.75f;
                RtQuatRotate(&clumpData->frames[idx].m_pIFrame->orientation, &ZaxisIK, fAngle, rwCOMBINEPRECONCAT);
                m_pPed->bUpdateMatricesRequired = true;

                idx = RpHAnimIDGetIndex(hier, BONE_R_THIGH);
                tmpHier = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
                fAngle = asin(tmpHier->up.z);
                RtQuatRotate(&clumpData->frames[idx].m_pIFrame->orientation, &ZaxisIK, fAngle * 30.0f * m_fSlopePitch, rwCOMBINEPOSTCONCAT);

                idx = RpHAnimIDGetIndex(hier, BONE_R_CALF);
                tmpHier = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
                fAngle = -(fAngle * m_fSlopePitch);
                if (fAngle < 0.0f)
                    fAngle = 0.0f;
                RtQuatRotate(&clumpData->frames[idx].m_pIFrame->orientation, &ZaxisIK, fAngle * -30.0f, rwCOMBINEPOSTCONCAT);

                idx = RpHAnimIDGetIndex(hier, BONE_R_FOOT);
                tmpHier = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
                fAngle = asin(tmpHier->up.z);
                if (fAngle < 0.0f)
                    fAngle = 0.0f;
                fAngle *= m_fSlopePitch;
                RtQuatRotate(&clumpData->frames[idx].m_pIFrame->orientation, &ZaxisIK, fAngle * -30.0f, rwCOMBINEPOSTCONCAT);

                idx = RpHAnimIDGetIndex(hier, BONE_L_THIGH);
                tmpHier = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
                fAngle = asin(tmpHier->up.z);
                RtQuatRotate(&clumpData->frames[idx].m_pIFrame->orientation, &ZaxisIK, fAngle * 30.0f * m_fSlopePitch, rwCOMBINEPOSTCONCAT);

                idx = RpHAnimIDGetIndex(hier, BONE_L_CALF);
                tmpHier = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
                fAngle = -(fAngle * m_fSlopePitch);
                if (fAngle < 0.0f)
                    fAngle = 0.0f;
                RtQuatRotate(&clumpData->frames[idx].m_pIFrame->orientation, &ZaxisIK, fAngle * -30.0f, rwCOMBINEPOSTCONCAT);

                idx = RpHAnimIDGetIndex(hier, BONE_L_FOOT);
                tmpHier = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
                fAngle = asin(tmpHier->up.z);
                if (fAngle < 0.0f)
                    fAngle = 0.0f;
                fAngle *= m_fSlopePitch;
                RtQuatRotate(&clumpData->frames[idx].m_pIFrame->orientation, &ZaxisIK, fAngle * -30.0f, rwCOMBINEPOSTCONCAT);

                RwMatrix* rwMat = m_pPed->GetModellingMatrix();
                CMatrix matResult(rwMat, false);

                CMatrix matTransl;
                matTransl.SetTranslate(CVector(0.0f, 0.0f, 0.0f));
                matTransl.RotateX(-(m_fSlopePitch / 2.0f));
                matResult *= matTransl;

                float fSlopeS = 0.75f * sin(m_fSlopePitch);
                float fSlopeC = (0.3f / cos(m_fSlopeRoll)) - 0.3f;
                auto pedFwd = m_pPed->GetForward();
                matResult.GetPosition() += CVector(pedFwd.x * fSlopeS, pedFwd.y * fSlopeS, pedFwd.z * fSlopeS);
                matResult.GetPosition().z += fSlopeC;
                matResult.UpdateRW();
                m_pPed->UpdateRwFrame();
            }
        } else {
            m_fSlopePitch = 0.0f;
        }

        if (abs(m_fSlopeRoll) > 0.01f) {
            auto idx = RpHAnimIDGetIndex(hier, BONE_L_FOOT);
            auto tmpHier = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
            float fAngle = atan2(tmpHier->at.y, tmpHier->at.x) - m_pPed->m_fCurrentRotation;
            fAngle = CGeneral::LimitRadianAngle(fAngle);
            CVector axis = CVector(0.0f, cos(fAngle), sin(fAngle));
            RtQuatRotate(&clumpData->frames[idx].m_pIFrame->orientation, &axis, RadiansToDegrees(m_fSlopeRoll), rwCOMBINEPRECONCAT);

            idx = RpHAnimIDGetIndex(hier, BONE_R_FOOT);
            tmpHier = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
            fAngle = atan2(tmpHier->at.y, tmpHier->at.x) - m_pPed->m_fCurrentRotation;
            fAngle = CGeneral::LimitRadianAngle(fAngle);
            axis = CVector(0.0f, cos(fAngle), sin(fAngle));
            RtQuatRotate(&clumpData->frames[idx].m_pIFrame->orientation, &axis, RadiansToDegrees(m_fSlopeRoll), rwCOMBINEPRECONCAT);

            m_pPed->bUpdateMatricesRequired = true;
        } else {
            m_fSlopeRoll = 0.0f;
        }

    } else {
        RwMatrix* rwMat = m_pPed->GetModellingMatrix();
        CMatrix matResult(rwMat, false);

        CMatrix matTransl;
        matTransl.SetTranslate(CVector(0.0f, 0.0f, 1.0f));
        matTransl.RotateX(-m_fSlopePitch);
        matTransl.RotateY(m_fSlopeRoll);
        matResult *= matTransl;
        matResult.GetPosition().z -= 1.0f;
        matResult.UpdateRW();
        m_pPed->UpdateRwFrame();
    }

    bSlopePitch = false;
}

RwMatrixTag* CPedIK::GetWorldMatrix(RwFrame* frame, RwMatrixTag* transformMat) {
    *transformMat = *RwFrameGetMatrix(frame);
    for (frame = RwFrameGetParent(frame); frame; frame = RwFrameGetParent(frame))
        RwMatrixTransform(transformMat, RwFrameGetMatrix(frame), rwCOMBINEPOSTCONCAT);
    return transformMat;
}

MoveLimbResult CPedIK::MoveLimb(LimbOrientation& limb, float targetYaw, float targetPitch, LimbMovementInfo& moveInfo) {

    MoveLimbResult result = HAVENT_REACHED_TARGET;

    // yaw
    if (abs(limb.m_fYaw - targetYaw) < moveInfo.yawD) {
        limb.m_fYaw = targetYaw;
        result = REACHED_TARGET;
    } else {
        if (limb.m_fYaw > targetYaw) {
            limb.m_fYaw -= moveInfo.yawD;
        } else if (limb.m_fYaw < targetYaw) {
            limb.m_fYaw += moveInfo.yawD;
        }
    }

    if (limb.m_fYaw > moveInfo.maxYaw || limb.m_fYaw < moveInfo.minYaw) {
        limb.m_fYaw = clamp(limb.m_fYaw, moveInfo.minYaw, moveInfo.maxYaw);
        result = CANT_REACH_TARGET;
    }

    // pitch
    if (abs(limb.m_fPitch - targetPitch) < moveInfo.pitchD) {
        limb.m_fPitch = targetPitch;
    } else {
        if (limb.m_fPitch > targetPitch) {
            limb.m_fPitch -= moveInfo.pitchD;
        } else if (limb.m_fPitch < targetPitch) {
            limb.m_fPitch += moveInfo.pitchD;
        }
        result = HAVENT_REACHED_TARGET;
    }

    if (limb.m_fPitch > moveInfo.maxPitch || limb.m_fPitch < moveInfo.minPitch) {
        limb.m_fPitch = clamp(limb.m_fPitch, moveInfo.minPitch, moveInfo.maxPitch);
        result = CANT_REACH_TARGET;
    }

    return result;
}

MoveLimbResult CPedIK::MoveLimb(LimbOrientation& limb, float targetYaw, float targetPitch, LimbMovementInfo& moveInfo, float fNormalize) {
    MoveLimbResult result = HAVENT_REACHED_TARGET;

    limb.m_fYaw = fNormalize * targetYaw;
    limb.m_fPitch = fNormalize * targetPitch;

    if ((limb.m_fYaw > moveInfo.maxYaw) || (limb.m_fYaw < moveInfo.minYaw)) {
        limb.m_fYaw = clamp(limb.m_fYaw, moveInfo.minYaw, moveInfo.maxYaw);
        result = CANT_REACH_TARGET;
    }

    if ((limb.m_fPitch > moveInfo.maxPitch) || (limb.m_fPitch < moveInfo.minPitch)) {
        limb.m_fPitch = clamp(limb.m_fPitch, moveInfo.minPitch, moveInfo.maxPitch);
        result = CANT_REACH_TARGET;
    } else {
        if (fNormalize > 0.9f && result == HAVENT_REACHED_TARGET)
            result = REACHED_TARGET;
    }

    return result;
}

