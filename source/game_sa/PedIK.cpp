/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

static inline bool& bRotateWithNeck = *(bool*)0x8D2354;

void CPedIK::InjectHooks() {
    RH_ScopedClass(CPedIK);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Constructor, 0x5FD8C0);
    RH_ScopedInstall(RotateTorso, 0x5FDDB0);
    RH_ScopedInstall(RotateTorsoForArm, 0x5FDF90);
    RH_ScopedOverloadedInstall(MoveLimb, "1", 0x5FDA60, MoveLimbResult(CPedIK::*)(LimbOrientation&, float, float, LimbMovementInfo&));
    RH_ScopedOverloadedInstall(MoveLimb, "2", 0x5FDB60, MoveLimbResult(CPedIK::*)(LimbOrientation&, float, float, LimbMovementInfo&, float));
    RH_ScopedInstall(PointGunAtPosition, 0x5FDE20);
    RH_ScopedInstall(PointGunInDirection, 0x5FDC00);
    RH_ScopedInstall(PitchForSlope, 0x5FE0E0);
}

CPedIK* CPedIK::Constructor(CPed* ped) {
    this->CPedIK::CPedIK(ped);
    return this;
}

// 0x5FD8C0
CPedIK::CPedIK(CPed* ped) {
    m_pPed                 = ped;
    m_nFlags               = 0;
    m_TorsoOrient.m_fYaw   = 0.0f;
    m_TorsoOrient.m_fPitch = 0.0f;
    m_fSlopePitch          = 0.0f;
    m_fSlopePitchLimitMult = 0.0f;
    m_fSlopeRoll           = 0.0f;
    m_fBodyRoll            = 0.0f;
}

// 0x5FDDB0
void CPedIK::RotateTorso(AnimBlendFrameData* bone, LimbOrientation& orientation, bool changeRoll) {
    const auto quat = bone->m_pIFrame->orientation.AsRtQuat();
    RtQuatRotate(quat, &XaxisIK, RadiansToDegrees(orientation.m_fYaw), rwCOMBINEREPLACE);
    RtQuatRotate(quat, &ZaxisIK, RadiansToDegrees(orientation.m_fPitch), rwCOMBINEPRECONCAT);
    m_pPed->bDontAcceptIKLookAts = true;
}

void CPedIK::RotateTorsoForArm(CVector const& dir) {
    auto destRotation = CVector2D{dir - m_pPed->GetPosition()}.Heading();

    if (m_pPed->m_fCurrentRotation + PI < destRotation) {
        destRotation -= TWO_PI;
    }
    else if (m_pPed->m_fCurrentRotation - PI > destRotation) {
        destRotation += TWO_PI;
    }

    const auto difAngle = destRotation - m_pPed->m_fCurrentRotation;
    auto resultAngle = QUARTER_PI;

    if (difAngle > QUARTER_PI && difAngle <= HALF_PI) {
        resultAngle = difAngle - QUARTER_PI;
    } else {
        if (difAngle >= DegreesToRadians(-60.0f))
            return;

        resultAngle = difAngle + DegreesToRadians(60.0f);

        if (difAngle < DegreesToRadians(-80.0f)) {
            resultAngle = DegreesToRadians(-20.0f);
        }
    }

    if (resultAngle != 0.0f) {
        float convertedAngle = RadiansToDegrees(resultAngle / 2.0f);
        if (bRotateWithNeck) { // android doesn't have this check
            RtQuatRotate(m_pPed->m_apBones[PED_NODE_NECK]->m_pIFrame->orientation.AsRtQuat(), &XaxisIK, convertedAngle, rwCOMBINEPOSTCONCAT);
        }
        RtQuatRotate(m_pPed->m_apBones[PED_NODE_UPPER_TORSO]->m_pIFrame->orientation.AsRtQuat(), &XaxisIK, convertedAngle, rwCOMBINEPOSTCONCAT);
    }
}

bool CPedIK::PointGunInDirection(float Z_angle, float dist, bool flag, float fNormalize) {
    bool bCanReach = true;
    bGunReachedTarget = false;
    bTorsoUsed = true;

    const auto angle = CGeneral::LimitRadianAngle(Z_angle - m_pPed->m_fCurrentRotation);
    auto hier = GetAnimHierarchyFromSkinClump(m_pPed->m_pRwClump);
    auto idx = RpHAnimIDGetIndex(hier, m_pPed->m_apBones[PED_NODE_RIGHT_CLAVICLE]->m_nNodeId);
    RwMatrix* pBone = RwMatrixCreate();
    pBone = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
    RwMatrixDestroy(pBone);

    MoveLimbResult limbRes;
    if (fNormalize < 0.0f) {
        limbRes = MoveLimb(m_TorsoOrient, angle, dist, ms_torsoInfo);
    } else {
        limbRes = MoveLimb(m_TorsoOrient, angle, dist, ms_torsoInfo, fNormalize);
    }

    switch (limbRes) {
    case CANT_REACH_TARGET:
        bCanReach = false;
        break;
    case REACHED_TARGET:
        bGunReachedTarget = true;
        break;
    }

    const auto head = &RpHAnimHierarchyGetMatrixArray(hier)[PED_NODE_HEAD];
    const auto headAngle = -CGeneral::LimitRadianAngle(atan2(-head->at.y, -head->at.x) - m_pPed->m_fCurrentRotation);

    CVector axis(0.0f, 0.0f, 0.0f);
    if (flag) {
        axis.y = std::cos(headAngle);
        axis.z = std::sin(headAngle);
    } else {
        axis.y = -std::sin(headAngle);
        axis.z = std::cos(headAngle);
    }

    auto Torsoframe = m_pPed->m_apBones[PED_NODE_UPPER_TORSO];
    RtQuatRotate(Torsoframe->GetFrameOrientation().AsRtQuat(), &axis, RadiansToDegrees(m_TorsoOrient.m_fPitch), rwCOMBINEPOSTCONCAT);
    RtQuatRotate(Torsoframe->GetFrameOrientation().AsRtQuat(), &XaxisIK, RadiansToDegrees(m_TorsoOrient.m_fYaw), rwCOMBINEPOSTCONCAT);
    m_pPed->bUpdateMatricesRequired = true;

    return bCanReach;
}

// Converted from thiscall void CPedIK::PointGunAtPosition(CVector const& posn,float arg2)	0x5FDE20
void CPedIK::PointGunAtPosition(CVector const& posn, float fNormalize) {
    const auto weaponInfo = CWeaponInfo::GetWeaponInfo(m_pPed->GetActiveWeapon().m_nType, m_pPed->GetWeaponSkill());

    const CVector newRight = [this, weaponInfo] {
        if (m_pPed->bIsDucking) {
            return g_GunAimingOffsets[weaponInfo->m_nAimOffsetIndex].DuckX * m_pPed->GetRight();
        } else {
            return g_GunAimingOffsets[weaponInfo->m_nAimOffsetIndex].AimX * m_pPed->GetRight();
        }
    }();

    const CVector newUp = [this, weaponInfo] {
        if (m_pPed->bIsDucking) {
            return g_GunAimingOffsets[weaponInfo->m_nAimOffsetIndex].DuckZ * m_pPed->GetUp();
        } else {
            return g_GunAimingOffsets[weaponInfo->m_nAimOffsetIndex].AimZ * m_pPed->GetUp();
        }
    }();

    const CVector newPos = m_pPed->GetPosition() + newRight + newUp;

    const auto angle = CGeneral::GetRadianAngleBetweenPoints(posn, newPos);
    const auto dist = DistanceBetweenPoints2D(newPos, posn);
    PointGunInDirection(angle, CGeneral::GetRadianAngleBetweenPoints(posn.z, dist, newPos.z, 0.0f), false, fNormalize);
}

void CPedIK::PitchForSlope() {
    const auto clumpData = RpClumpGetAnimBlendClumpData(m_pPed->m_pRwClump);
    const auto hier = GetAnimHierarchyFromSkinClump(m_pPed->m_pRwClump);

    if (std::abs(m_fBodyRoll) > 0.01f) {
        m_fBodyRoll = std::clamp(m_fBodyRoll, -PI_6, PI_6);
    }

    if (!m_pPed->IsStateDying()) {
        float offset;
        if (std::abs(m_fSlopePitch) > 0.01f) {
            offset = 0.1f;
            if (m_pPed->m_nMoveState == PEDMOVE_WALK) {
                offset = 0.085f;
            }

            m_fSlopePitchLimitMult = (m_fSlopePitchLimitMult * 0.9f) + offset;

            float lowBound = m_fSlopePitchLimitMult * DegreesToRadians(-35.0f);
            float highBound = m_fSlopePitchLimitMult * PI_6;
            m_fSlopePitch = std::clamp(m_fSlopePitch, lowBound, highBound);
        }

        if (std::abs(m_fSlopeRoll) > 0.01f) {
            m_fSlopeRoll = std::clamp(m_fSlopeRoll, DegreesToRadians(-45.0f), DegreesToRadians(45.0f));
        }

        // TODO: refactor
        if (std::abs(m_fSlopePitch) > 0.01f) {
            auto idx = RpHAnimIDGetIndex(hier, BONE_SPINE);
            auto tmpHier = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
            if (&m_pPed->GetIntelligence()->m_TaskMgr && m_pPed->GetIntelligence()->m_TaskMgr.GetActiveTask()->GetTaskType() == TASK_SIMPLE_STEALTH_KILL) {
                RtQuatRotate(clumpData->m_Frames[idx].GetFrameOrientation().AsRtQuat(), &ZaxisIK, RadiansToDegrees(m_fSlopePitch), rwCOMBINEPRECONCAT);
                m_pPed->bUpdateMatricesRequired = true;
            } else {
                float angle = RadiansToDegrees(-m_fSlopePitch) * 0.75f;
                RtQuatRotate(clumpData->m_Frames[idx].GetFrameOrientation().AsRtQuat(), &ZaxisIK, angle, rwCOMBINEPRECONCAT);
                m_pPed->bUpdateMatricesRequired = true;

                idx = RpHAnimIDGetIndex(hier, BONE_R_THIGH);
                tmpHier = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
                angle = std::asin(tmpHier->up.z);
                RtQuatRotate(clumpData->m_Frames[idx].GetFrameOrientation().AsRtQuat(), &ZaxisIK, angle * 30.0f * m_fSlopePitch, rwCOMBINEPOSTCONCAT);

                idx = RpHAnimIDGetIndex(hier, BONE_R_CALF);
                tmpHier = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
                angle = std::max(-angle * m_fSlopePitch, 0.0f);
                RtQuatRotate(clumpData->m_Frames[idx].GetFrameOrientation().AsRtQuat(), &ZaxisIK, angle * -30.0f, rwCOMBINEPOSTCONCAT);

                idx = RpHAnimIDGetIndex(hier, BONE_R_FOOT);
                tmpHier = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
                angle = std::max(std::asin(tmpHier->up.z), 0.0f) * m_fSlopePitch;
                RtQuatRotate(clumpData->m_Frames[idx].GetFrameOrientation().AsRtQuat(), &ZaxisIK, angle * -30.0f, rwCOMBINEPOSTCONCAT);

                idx = RpHAnimIDGetIndex(hier, BONE_L_THIGH);
                tmpHier = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
                angle = std::asin(tmpHier->up.z);
                RtQuatRotate(clumpData->m_Frames[idx].GetFrameOrientation().AsRtQuat(), &ZaxisIK, angle * 30.0f * m_fSlopePitch, rwCOMBINEPOSTCONCAT);

                idx = RpHAnimIDGetIndex(hier, BONE_L_CALF);
                tmpHier = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
                angle = std::max(-angle * m_fSlopePitch, 0.0f);
                RtQuatRotate(clumpData->m_Frames[idx].GetFrameOrientation().AsRtQuat(), &ZaxisIK, angle * -30.0f, rwCOMBINEPOSTCONCAT);

                idx = RpHAnimIDGetIndex(hier, BONE_L_FOOT);
                tmpHier = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
                angle = std::max(std::asin(tmpHier->up.z), 0.0f) * m_fSlopePitch;
                RtQuatRotate(clumpData->m_Frames[idx].GetFrameOrientation().AsRtQuat(), &ZaxisIK, angle * -30.0f, rwCOMBINEPOSTCONCAT);

                RwMatrix* rwMat = m_pPed->GetModellingMatrix();
                CMatrix matResult(rwMat, false);

                CMatrix matTransl;
                matTransl.SetTranslate(CVector(0.0f, 0.0f, 0.0f));
                matTransl.RotateX(-(m_fSlopePitch / 2.0f));
                matResult *= matTransl;

                matResult.GetPosition() += m_pPed->GetForward() * 0.75f * std::sin(m_fSlopePitch);
                matResult.GetPosition().z += 0.3f / std::cos(m_fSlopeRoll) - 0.3f;
                matResult.UpdateRW();
                m_pPed->UpdateRwFrame();
            }
        } else {
            m_fSlopePitch = 0.0f;
        }

        if (std::abs(m_fSlopeRoll) > 0.01f) {
            auto idx = RpHAnimIDGetIndex(hier, BONE_L_FOOT);
            auto tmpHier = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
            float angle = CGeneral::LimitRadianAngle(atan2(tmpHier->at.y, tmpHier->at.x) - m_pPed->m_fCurrentRotation);
            CVector axis = CVector(0.0f, std::cos(angle), std::sin(angle));
            RtQuatRotate(clumpData->m_Frames[idx].GetFrameOrientation().AsRtQuat(), &axis, RadiansToDegrees(m_fSlopeRoll), rwCOMBINEPRECONCAT);

            idx = RpHAnimIDGetIndex(hier, BONE_R_FOOT);
            tmpHier = &RpHAnimHierarchyGetMatrixArray(hier)[idx];
            angle = CGeneral::LimitRadianAngle(atan2(tmpHier->at.y, tmpHier->at.x) - m_pPed->m_fCurrentRotation);
            axis = CVector(0.0f, std::cos(angle), std::sin(angle));
            RtQuatRotate(clumpData->m_Frames[idx].GetFrameOrientation().AsRtQuat(), &axis, RadiansToDegrees(m_fSlopeRoll), rwCOMBINEPRECONCAT);

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
    for (frame = RwFrameGetParent(frame); frame; frame = RwFrameGetParent(frame)) {
        RwMatrixTransform(transformMat, RwFrameGetMatrix(frame), rwCOMBINEPOSTCONCAT);
    }
    return transformMat;
}

MoveLimbResult CPedIK::MoveLimb(LimbOrientation& limb, float targetYaw, float targetPitch, LimbMovementInfo& moveInfo) {

    MoveLimbResult result = HAVENT_REACHED_TARGET;

    // yaw
    if (std::abs(limb.m_fYaw - targetYaw) < moveInfo.yawD) {
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
        limb.m_fYaw = std::clamp(limb.m_fYaw, moveInfo.minYaw, moveInfo.maxYaw);
        result = CANT_REACH_TARGET;
    }

    // pitch
    if (std::abs(limb.m_fPitch - targetPitch) < moveInfo.pitchD) {
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
        limb.m_fPitch = std::clamp(limb.m_fPitch, moveInfo.minPitch, moveInfo.maxPitch);
        result = CANT_REACH_TARGET;
    }

    return result;
}

MoveLimbResult CPedIK::MoveLimb(LimbOrientation& limb, float targetYaw, float targetPitch, LimbMovementInfo& moveInfo, float fNormalize) {
    auto result = HAVENT_REACHED_TARGET;

    limb.m_fYaw = fNormalize * targetYaw;
    limb.m_fPitch = fNormalize * targetPitch;

    if ((limb.m_fYaw > moveInfo.maxYaw) || (limb.m_fYaw < moveInfo.minYaw)) {
        limb.m_fYaw = std::clamp(limb.m_fYaw, moveInfo.minYaw, moveInfo.maxYaw);
        result = CANT_REACH_TARGET;
    }

    if ((limb.m_fPitch > moveInfo.maxPitch) || (limb.m_fPitch < moveInfo.minPitch)) {
        limb.m_fPitch = std::clamp(limb.m_fPitch, moveInfo.minPitch, moveInfo.maxPitch);
        result = CANT_REACH_TARGET;
    } else {
        if (fNormalize > 0.9f && result == HAVENT_REACHED_TARGET)
            result = REACHED_TARGET;
    }

    return result;
}
