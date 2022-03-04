#include "StdInc.h"

#include "TaskSimpleGoToPoint.h"

#include "TaskSimpleStandStill.h"
#include "IKChainManager_c.h"
#include "TaskSimpleHoldEntity.h"
#include "TaskSimpleDuck.h"

void CTaskSimpleGoToPoint::InjectHooks()
{
    RH_ScopedClass(CTaskSimpleGoToPoint);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x667CD0);
    RH_ScopedInstall(Clone_Reversed, 0x66CC60);
    RH_ScopedInstall(MakeAbortable_Reversed, 0x667D60);
    RH_ScopedInstall(ProcessPed_Reversed, 0x66D710);
    RH_ScopedInstall(UpdatePoint, 0x645700);
}

// 0x667CD0
CTaskSimpleGoToPoint::CTaskSimpleGoToPoint(int32 moveState, const CVector& targetPoint, float fRadius, bool bMoveTowardsTargetPoint, bool a6) :
    CTaskSimpleGoTo(moveState, targetPoint, fRadius)
{
    m_GoToPointFlags = 0;
    gotoPointFlags.m_bMoveTowardsTargetPoint = bMoveTowardsTargetPoint;
    gotoPointFlags.m_b04 = a6;
}

// 0x667CD0
CTaskSimpleGoToPoint* CTaskSimpleGoToPoint::Constructor(int32 moveState, const CVector& targetPoint, float fRadius, bool bMoveTowardsTargetPoint, bool a6)
{
    this->CTaskSimpleGoToPoint::CTaskSimpleGoToPoint(moveState, targetPoint, fRadius, bMoveTowardsTargetPoint, a6);
    return this;
}

// 0x66CC60
CTask* CTaskSimpleGoToPoint::Clone()
{
    return CTaskSimpleGoToPoint::Clone_Reversed();
}

// 0x667D60
bool CTaskSimpleGoToPoint::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event)
{
    return CTaskSimpleGoToPoint::MakeAbortable_Reversed(ped, priority, event);
}

// 0x66D710
bool CTaskSimpleGoToPoint::ProcessPed(class CPed* ped)
{
    return CTaskSimpleGoToPoint::ProcessPed_Reversed(ped);
}

CTask* CTaskSimpleGoToPoint::Clone_Reversed()
{
    return new CTaskSimpleGoToPoint(
        m_moveState,
        m_vecTargetPoint,
        m_fRadius,
        gotoPointFlags.m_bMoveTowardsTargetPoint,
        gotoPointFlags.m_b04
    );
}

bool CTaskSimpleGoToPoint::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event)
{
    if (gotoFlags.m_bIsIKChainSet) {
        if (g_ikChainMan.IsLooking(ped))
            g_ikChainMan.AbortLookAt(ped, 250);
    }
    if (priority != ABORT_PRIORITY_URGENT) {
        if (priority != ABORT_PRIORITY_IMMEDIATE) {
            gotoPointFlags.m_b02 = true;
            return false;
        }
        CTaskSimpleStandStill standStillTask(0, false, false, 8.0f);
        standStillTask.ProcessPed(ped);
    }
    return true;
}

bool CTaskSimpleGoToPoint::ProcessPed_Reversed(class CPed* ped)
{
    CPlayerPed* player = ped->AsPlayer();
    ped->m_pedIK.bSlopePitch = true;
    if (HasCircledTarget(ped)) {
        if (!gotoPointFlags.m_b05) {
            gotoPointFlags.m_b03 = true;
            if (gotoFlags.m_bIsIKChainSet) {
                if (g_ikChainMan.IsLooking(ped))
                    g_ikChainMan.AbortLookAt(ped, 250);
            }
            return true;
        }
    }
    if (ped->bHasJustLeftCar) {
        ped->m_pIntelligence->m_eventScanner.ScanForEventsNow(ped, false);
        ped->bHasJustLeftCar = false;
    }
    else if (ped->bHasJustSoughtCover) {
        ped->m_pIntelligence->m_eventScanner.ScanForEventsNow(ped, true);
        ped->bHasJustSoughtCover = false;
    }
    else {
        CTaskSimpleDuck* pDuckTask = ped->m_pIntelligence->GetTaskDuck(false);
        if (pDuckTask) {
            float fMoveSpeedY = 1.1f;
            if (m_moveState == PEDMOVE_WALK)
                fMoveSpeedY = 0.75f;
            pDuckTask->ControlDuckMove(0.0f, -fMoveSpeedY);
        }
        else {
            ped->SetMoveState(static_cast<eMoveState>(m_moveState));
            if (ped->IsPlayer()) {
                if (CPad::GetPad(0)->DisablePlayerControls) {
                    player->SetPlayerMoveBlendRatio(nullptr);
                    player->SetRealMoveAnim();
                }
                else {
                    bool bSprinting = false;
                    CWeaponInfo* pWeaponInfo = CWeaponInfo::GetWeaponInfo(ped->m_aWeapons[ped->m_nActiveWeaponSlot].m_nType, eWeaponSkill::STD);
                    if (!pWeaponInfo->flags.bHeavy) {
                        auto* task = static_cast<CTaskSimpleHoldEntity*>(ped->m_pIntelligence->GetTaskHold(false));
                        if (!task || !task->m_pAnimBlendAssociation) {
                            CAnimBlendAssocGroup* pAnimGroup = &CAnimManager::ms_aAnimAssocGroups[ped->m_nAnimGroup];
                            if (!ped->m_pPlayerData->m_bPlayerSprintDisabled && !g_surfaceInfos->CantSprintOn(ped->m_nContactSurface)) {
                                auto pAnimStaticAssoc1 = pAnimGroup->GetAnimation(ANIM_ID_RUN);
                                auto pAnimStaticAssoc2 = pAnimGroup->GetAnimation(ANIM_ID_SPRINT);
                                if (pAnimStaticAssoc1->m_pHierarchy != pAnimStaticAssoc2->m_pHierarchy &&
                                    player->ControlButtonSprint(SPRINT_GROUND) >= 1.0f) {
                                    ped->SetMoveState(PEDMOVE_SPRINT);
                                    bSprinting = true;
                                }
                            }
                        }
                    }
                    if (!bSprinting && ped->m_nMoveState == PEDMOVE_SPRINT)
                        ped->SetMoveState(PEDMOVE_RUN);
                    if (gotoPointFlags.m_bMoveTowardsTargetPoint)
                        player->SetPlayerMoveBlendRatio(&m_vecTargetPoint);
                    else
                        player->SetPlayerMoveBlendRatio(nullptr);
                    player->SetRealMoveAnim();
                }
            }
            else {
                ped->SetMoveAnim();
            }
        }
        bool bAimingRotationSet = false;
        const CVector& pedPos = ped->GetPosition();
        CVector2D vecDistance = m_vecTargetPoint - pedPos;
        CVector2D vecDirection(vecDistance);
        vecDirection.Normalise();
        CVector2D vecDistanceToTargetFromLastPoint = m_vecTargetPoint - m_vecLastPedPos;
        CVector2D vecDistanceToTargetFromPoint = m_vecTargetPoint - (CTimer::GetTimeStep() * ped->m_vecMoveSpeed + pedPos);
        m_vecLastPedPos = pedPos;
        if ((vecDistance.SquaredMagnitude() >= m_fRadius * m_fRadius
            || gotoPointFlags.m_b05
            || !ped->bIgnoreHeightCheckOnGotoPointTask && fabs(pedPos.z - m_vecTargetPoint.z) >= 2.0f
            || gotoPointFlags.m_b04 && DotProduct2D(vecDistance, vecDistanceToTargetFromLastPoint) >= 0.0f)
            && (gotoPointFlags.m_b04 || DotProduct2D(vecDistance, vecDistanceToTargetFromPoint) > 0.0f || gotoPointFlags.m_b05))
        {
            if (!gotoPointFlags.m_b02) {
                float fAngleInRadians = CGeneral::GetRadianAngleBetweenPoints(vecDirection.x, vecDirection.y, 0.0f, 0.0f);
                ped->m_fAimingRotation = CGeneral::LimitRadianAngle(fAngleInRadians);
                bAimingRotationSet = true;
            }
        }
        else {
            gotoPointFlags.m_b03 = true;
        }
        if (!bAimingRotationSet) {
            QuitIK(ped);
            return true;
        }
    }
    if (gotoFlags.m_bTargetPointUpdated) {
        if (gotoFlags.m_bIsIKChainSet && g_ikChainMan.IsLooking(ped))
            g_ikChainMan.AbortLookAt(ped, 250);
        gotoFlags.m_bTargetPointUpdated = false;
    }
    SetUpIK(ped);
    gotoPointFlags.m_b05 = false;
    return false;
}

// 0x645700
void CTaskSimpleGoToPoint::UpdatePoint(const CVector& targetPosition, float fRadius, bool bDontCheckRadius)
{
    if (bDontCheckRadius || m_vecTargetPoint != targetPosition || m_fRadius != fRadius)
    {
        m_vecTargetPoint = targetPosition;
        gotoFlags.m_b01 = false;
        gotoFlags.m_b02 = false;
        gotoFlags.m_b03 = false;
        gotoFlags.m_b04 = false;
        gotoFlags.m_bTargetPointUpdated = true;
    }
}
