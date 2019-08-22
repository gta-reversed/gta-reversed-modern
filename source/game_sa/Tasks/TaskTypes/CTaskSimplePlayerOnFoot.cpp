#include "StdInc.h"

int& gLastRandomNumberForIdleAnimationID = *reinterpret_cast<int*>(0x8D2FEC);
unsigned int& gLastTouchTimeDelta = *reinterpret_cast<unsigned int*>(0xC19664);
float& gDuckAnimBlendData = *reinterpret_cast<float*>(0x8D2FF0);

CTaskSimplePlayerOnFoot* CTaskSimplePlayerOnFoot::Constructor()
{
    return plugin::CallMethodAndReturn<CTaskSimplePlayerOnFoot*, 0x685750, CTaskSimplePlayerOnFoot*>(this);
}

CTaskSimplePlayerOnFoot* CTaskSimplePlayerOnFoot::Destructor()
{
    return plugin::CallMethodAndReturn<CTaskSimplePlayerOnFoot*, 0x68B0C0, CTaskSimplePlayerOnFoot*>(this);
}

bool CTaskSimplePlayerOnFoot::ProcessPed(CPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x688810, CTaskSimplePlayerOnFoot*, CPed*>(this, pPed);
#else
    bool result = false;
    CPlayerPed* pPlayerPed = static_cast<CPlayerPed*>(pPed);
    if (pPlayerPed->GetPadFromPlayer())
    {
        CPedIntelligence* pIntelligence = pPlayerPed->m_pIntelligence;
        bool bPedMoving = pPlayerPed->m_nMoveState >= PEDMOVE_WALK;
        if (pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_nType == WEAPON_CHAINSAW
            && pIntelligence->GetTaskFighting()
            && pIntelligence->GetTaskFighting()->m_nCurrentMove == 4)
        {
            bPedMoving = 1;
        }
        pPlayerPed->SetMoveState(PEDMOVE_STILL);
        if (pPlayerPed->bIsDucking)
        {
            PlayerControlDucked(pPlayerPed);
        }
        else if (!pIntelligence->GetTaskFighting() || bPedMoving)
        {
            CTaskSimpleUseGun* pSimpleTaskUseGun = pIntelligence->GetTaskUseGun();
            if (pSimpleTaskUseGun
                && pSimpleTaskUseGun->m_pWeaponInfo
                && !pSimpleTaskUseGun->m_pWeaponInfo->m_nFlags.bAimWithArm)
            {
                PlayerControlZeldaWeapon(pPlayerPed);
            }
            else
            {
                PlayerControlZelda(pPlayerPed, 0);
            }
        }
        else
        {
            PlayerControlFighter(pPlayerPed);
        }
        ProcessPlayerWeapon(pPlayerPed);
        m_nFrameCounter = CTimer::m_FrameCounter;
        result = 0;
    }
    else
    {
        m_nFrameCounter = CTimer::m_FrameCounter;
        result = 0;
    }
    return result;
#endif
}

bool CTaskSimplePlayerOnFoot::ProcessPlayerWeapon(CPlayerPed* pPlayerPed)
{
    return plugin::CallMethodAndReturn<bool, 0x6859A0, CTaskSimplePlayerOnFoot*, CPlayerPed*>(this, pPlayerPed);
}

void CTaskSimplePlayerOnFoot::PlayIdleAnimations(CPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x6872C0, CTaskSimplePlayerOnFoot*, CPed*>(this, pPed);
#else
    CPlayerPed* pPlayerPed = static_cast<CPlayerPed*>(pPed);

    CPad* pPad = pPlayerPed->GetPadFromPlayer();
    if (!CWorld::Players[0].m_pPed || !CWorld::Players[1].m_pPed)
    {
        int animGroupID = 0;
        if (TheCamera.m_bWideScreenOn
            || pPlayerPed->bIsDucking
            || pPlayerPed->bCrouchWhenShooting
            || pPlayerPed->m_pIntelligence->GetTaskHold(0)
            || pPad->DisablePlayerControls
            || pPlayerPed->m_nMoveState > PEDMOVE_STILL
            || (animGroupID = pPlayerPed->m_nAnimGroup, animGroupID != ANIM_GROUP_PLAYER) && animGroupID != ANIM_GROUP_FAT && animGroupID != ANIM_GROUP_MUSCULAR)
        {
            pPad->SetTouched();
        }
        CAnimBlock* pAnimBlock = &CAnimManager::ms_aAnimBlocks[m_nAnimationBlockIndex];
        unsigned int touchTimeDelta = pPad->GetTouchedTimeDelta(); CTimer::m_snTimeInMilliseconds;
        if (touchTimeDelta <= 10000)
        {
            if (pAnimBlock->bLoaded)
            {
                CStreaming::SetModelIsDeletable(m_nAnimationBlockIndex + RESOURCE_FIRST_ID_IFP);
                CAnimBlendAssociation* pAnimAssoc = nullptr;
                for (pAnimAssoc = RpAnimBlendClumpGetFirstAssociation(pPlayerPed->m_pRwClump);
                    pAnimAssoc;
                    pAnimAssoc = RpAnimBlendGetNextAssociation(pAnimAssoc))
                {
                    if (pAnimAssoc->m_bf10)
                    {
                        pAnimAssoc->m_fBlendDelta = -8.0;
                    }
                }
            }
            gLastTouchTimeDelta = 0;
        }
        else
        {
            CStreaming::RequestModel(m_nAnimationBlockIndex + RESOURCE_FIRST_ID_IFP, LOADSTATE_Requested);
            if (pAnimBlock->bLoaded)
            {
                CAnimBlendAssociation* pAnimAssoc1 = RpAnimBlendClumpGetFirstAssociation(pPlayerPed->m_pRwClump);
                if (pAnimAssoc1)
                {
                    while (1)
                    {

                        unsigned int animHierarchyIndex = (uint32_t)pAnimAssoc1->m_pHierarchy - (uint32_t)CAnimManager::ms_aAnimations;
                        animHierarchyIndex = animHierarchyIndex / 6 + (animHierarchyIndex >> 0x1f) >> 2;
                        animHierarchyIndex = animHierarchyIndex + (animHierarchyIndex >> 0x1f);

                        int animBlockFirstAnimIndex = pAnimBlock->startAnimation;
                        if (animHierarchyIndex >= animBlockFirstAnimIndex
                            && animHierarchyIndex < animBlockFirstAnimIndex + pAnimBlock->animationCount)
                        {
                            break;
                        }
                        pAnimAssoc1 = RpAnimBlendGetNextAssociation(pAnimAssoc1);
                        if (!pAnimAssoc1)
                        {
                            goto PLAY_RANDOM_IDLE_ANIM;
                        }
                    }
                }
                else
                {
                PLAY_RANDOM_IDLE_ANIM:
                    if (!(pPlayerPed->bIsLooking && pPlayerPed->bIsRestoringLook) && touchTimeDelta - gLastTouchTimeDelta > 20000)
                    {
                        // Play random idle animation
                        int randomNumber = 0;
                        do
                        {
                            randomNumber = CGeneral::GetRandomNumberInRange(0, 4);
                        } while (gLastRandomNumberForIdleAnimationID == randomNumber);

                        int groupAndAnimIDs[8] = {
                            PLAYIDLES_STRETCH, ANIM_GROUP_PLAYIDLES,
                            PLAYIDLES_TIME, ANIM_GROUP_PLAYIDLES,
                            PLAYIDLES_SHLDR, ANIM_GROUP_PLAYIDLES,
                            PLAYIDLES_STRLEG, ANIM_GROUP_PLAYIDLES };

                        CAnimBlendAssociation* pAnimNewAssoc = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump,
                            groupAndAnimIDs[randomNumber * 2 + 1], groupAndAnimIDs[randomNumber * 2], 8.0);
                        pAnimNewAssoc->m_bf10 = 1;
                        gLastTouchTimeDelta = touchTimeDelta;
                        gLastRandomNumberForIdleAnimationID = randomNumber;
                        if (CStats::GetStatValue(STAT_MANAGEMENT_ISSUES_MISSION_ACCOMPLISHED) != 0.0 && CTimer::m_snTimeInMilliseconds > 1200000)
                        {
                            pPlayerPed->Say(336, 0, 0.2, 0, 0, 0);
                        }
                    }
}
            }
        }
    }
#endif
}

void CTaskSimplePlayerOnFoot::PlayerControlFighter(CPlayerPed* pPlayerPed)
{
    plugin::CallMethod<0x687530, CTaskSimplePlayerOnFoot*, CPlayerPed*>(this, pPlayerPed);
}

bool CTaskSimplePlayerOnFoot::PlayerControlZeldaWeapon(CPed* pPed) 
{
    return plugin::CallMethodAndReturn<bool, 0x687C20, CTaskSimplePlayerOnFoot*, CPed*>(this, pPed);
}

void CTaskSimplePlayerOnFoot::PlayerControlDucked(CPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x687F30, CTaskSimplePlayerOnFoot*, CPed*>(this, pPed);
#else
    CTaskSimpleDuck* pSimpleDuckTask = static_cast<CTaskSimpleDuck*>(pPed->m_pIntelligence->m_TaskMgr.GetTaskSecondary(1));
    if (pSimpleDuckTask)
    {
        CPlayerPed* pPlayerPed = static_cast<CPlayerPed*> (pPed);
        CPad* pPad = pPlayerPed->GetPadFromPlayer();
        CVector2D moveSpeed;
        moveSpeed.x = pPad->GetPedWalkLeftRight() * 0.0078125;
        moveSpeed.y = pPad->GetPedWalkUpDown() * 0.0078125;
        float pedMoveBlendRatio = sqrt(moveSpeed.x * moveSpeed.x + moveSpeed.y * moveSpeed.y);
        if (pPlayerPed->m_pAttachedTo)
        {
            pedMoveBlendRatio = 0.0;
        }
        else if (pedMoveBlendRatio > 1.0)
        {
            pedMoveBlendRatio = 1.0;
        }
        if (!pSimpleDuckTask->m_bIsFinished && !pSimpleDuckTask->m_bIsAborting)
        {
            if (pPad->DuckJustDown()
                || pPad->GetSprint()
                || pPad->JumpJustDown()
                || pPad->ExitVehicleJustDown()
                || !CTaskSimpleDuck::CanPedDuck(pPlayerPed))
            {
                pPlayerPed->m_pIntelligence->ClearTaskDuckSecondary();
                if (!pPlayerPed->m_pIntelligence->GetTaskUseGun()
                    || pPlayerPed->m_pIntelligence->GetTaskUseGun()->m_pWeaponInfo->m_nFlags.bAimWithArm)
                {
                    int pedMoveState = PEDMOVE_NONE;
                    if (pPad->GetSprint())
                    {
                        if (pedMoveBlendRatio <= 0.5)
                        {
                            return;
                        }
                        auto pNewAnimation = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, pPlayerPed->m_nAnimGroup, 1u, gDuckAnimBlendData);
                        pNewAnimation->m_bPlaying = 1;
                        pPlayerPed->m_pPlayerData->m_fMoveBlendRatio = 1.5;
                        pedMoveState = PEDMOVE_RUN;
                    }
                    else
                    {
                        if (pedMoveBlendRatio <= 0.5)
                        {
                            return;
                        }
                        auto pNewAnimation = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, pPlayerPed->m_nAnimGroup, 0, gDuckAnimBlendData);
                        pNewAnimation->m_bPlaying = 1;
                        pPlayerPed->m_pPlayerData->m_fMoveBlendRatio = 1.5;
                        pedMoveState = PEDMOVE_WALK;
                    }
                    pPlayerPed->m_nMoveState = pedMoveState;
                    pPlayerPed->field_538 = pedMoveState;
                }
                else if (pedMoveBlendRatio > 0.5)
                {
                    auto pNewAnimation = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_DEFAULT, DEFAULT_GUNMOVE_FWD, gDuckAnimBlendData);
                    pNewAnimation->m_bPlaying = 1;
                    pPlayerPed->m_pPlayerData->m_fMoveBlendRatio = 1.0;
                    moveSpeed.x = 1.0;
                    moveSpeed.y = 0.0;
                    CTaskSimpleUseGun* pTaskSimpleUseGun = pPlayerPed->m_pIntelligence->GetTaskUseGun();
                    pTaskSimpleUseGun->ControlGunMove(&moveSpeed);
                }
            }
            else if (!pPad->GetTarget() || pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].IsTypeMelee())
            {
                if (pedMoveBlendRatio > 0.0)
                {
                    float radianAngle = CGeneral::GetRadianAngleBetweenPoints(0.0, 0.0, -moveSpeed.x, moveSpeed.y)
                        - TheCamera.m_fOrientation;
                    float limitedRadianAngle = CGeneral::LimitRadianAngle(radianAngle);
                    pPlayerPed->m_fAimingRotation = limitedRadianAngle;
                    CVector moveDirection(0.0, -sin(limitedRadianAngle), cos(limitedRadianAngle));
                    if (!CGameLogic::IsPlayerAllowedToGoInThisDirection(pPlayerPed, moveDirection.x, moveDirection.y, 0.0, 0.0))
                    {
                        pedMoveBlendRatio = 0.0;
                    }
                }
                moveSpeed.y = -pedMoveBlendRatio;

                pPlayerPed->m_pPlayerData->m_fMoveBlendRatio = pedMoveBlendRatio;
                moveSpeed.x = 0.0;
                pSimpleDuckTask->ControlDuckMove(0.0, moveSpeed.y);
            }
            else
            {
                if (CGameLogic::IsPlayerUse2PlayerControls(pPlayerPed))
                {
                    float radianAngle = CGeneral::GetRadianAngleBetweenPoints(0.0, 0.0, -moveSpeed.x, moveSpeed.y) - TheCamera.m_fOrientation;
                    float limitedRadianAngle = CGeneral::LimitRadianAngle(radianAngle);
                    CVector moveDirection(0.0, -sin(limitedRadianAngle), cos(limitedRadianAngle));
                    if (!CGameLogic::IsPlayerAllowedToGoInThisDirection(pPlayerPed, moveDirection.x, moveDirection.y, 0.0, 0.0))
                    {
                        pedMoveBlendRatio = 0.0;
                    }
                    CMatrix* pMatrix = pPlayerPed->m_matrix;
                    CEntity* pTargetedObject = pPlayerPed->m_pTargetedObject;
                    moveSpeed.x = (moveDirection.y * pMatrix->right.y + moveDirection.x * pMatrix->right.x + pMatrix->right.z * 0.0)
                        * pedMoveBlendRatio;
                    moveSpeed.y = -((moveDirection.y * pMatrix->up.y + pMatrix->up.z * 0.0 + moveDirection.x * pMatrix->up.x)
                        * pedMoveBlendRatio);
                    if (pTargetedObject)
                    {
                        CVector* pedPosition = &pMatrix->pos;
                        if (!pMatrix)
                        {
                            pedPosition = &pPlayerPed->m_placement.m_vPosn;
                        }
                        CMatrixLink* targetedObjectMatrix = pTargetedObject->m_matrix;
                        CVector* targetedObjectPos = &pTargetedObject->m_placement.m_vPosn;
                        if (targetedObjectMatrix)
                        {
                            targetedObjectPos = &targetedObjectMatrix->pos;
                        }
                        VectorSub(&moveDirection, targetedObjectPos, pedPosition);
                        pPlayerPed->m_fAimingRotation = atan2(-moveDirection.x, moveDirection.y);
                    }
                    else
                    {
                        pPlayerPed->m_fAimingRotation = limitedRadianAngle;
                    }
                }
                pSimpleDuckTask->ControlDuckMove(moveSpeed.x, moveSpeed.y);
                pPlayerPed->m_pPlayerData->m_fMoveBlendRatio = 0.0;
            }
        }
    }
#endif
}

int CTaskSimplePlayerOnFoot::PlayerControlZelda(CPed* pPed, bool bAvoidJumpingAndDucking)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<int, 0x6883D0, CTaskSimplePlayerOnFoot*, CPed*, bool>(this, pPed, bAvoidJumpingAndDucking);
#else
    CPlayerPed* pPlayerPed = static_cast<CPlayerPed*>(pPed);
    CPlayerData* pPlayerData = pPed->m_pPlayerData;
    pPlayerData->m_vecFightMovement.x = 0.0; pPlayerData->m_vecFightMovement.y = 0.0;
    CPad* pPad = pPlayerPed->GetPadFromPlayer();
    float pedWalkLeftRight = pPad->GetPedWalkLeftRight();
    float pedWalkUpDown = pPad->GetPedWalkUpDown();
    float pedMoveBlendRatio = sqrt(pedWalkUpDown * pedWalkUpDown + pedWalkLeftRight * pedWalkLeftRight) * 0.016666668;
    if (pPlayerPed->m_pAttachedTo)
    {
        pedMoveBlendRatio = 0.0;
    }
    if (pPad->NewState.m_bPedWalk && pedMoveBlendRatio > 1.0)
    {
        pedMoveBlendRatio = 1.0;
    }
    else if (pedMoveBlendRatio <= 0.0)
    {
        pPlayerPed->m_pPlayerData->m_fMoveBlendRatio = 0.0;
        goto DONT_MODIFY_MOVE_BLEND_RATIO;
    }

    float radianAngle = CGeneral::GetRadianAngleBetweenPoints(0.0, 0.0, -pedWalkLeftRight, pedWalkUpDown) - TheCamera.m_fOrientation;
    float limitedRadianAngle = CGeneral::LimitRadianAngle(radianAngle);
    pPlayerPed->m_fAimingRotation = limitedRadianAngle;

    if (CGameLogic::IsPlayerAllowedToGoInThisDirection(pPlayerPed, -sin(limitedRadianAngle), cos(limitedRadianAngle), 0.0, 0.0))
    {

        float fMaximumMoveBlendRatio = CTimer::ms_fTimeStep * 0.07;
        if (pedMoveBlendRatio - pPlayerData->m_fMoveBlendRatio <= fMaximumMoveBlendRatio)
        {
            if (-fMaximumMoveBlendRatio <= pedMoveBlendRatio - pPlayerData->m_fMoveBlendRatio)
                pPlayerData->m_fMoveBlendRatio = pedMoveBlendRatio;
            else
                pPlayerData->m_fMoveBlendRatio = pPlayerData->m_fMoveBlendRatio - fMaximumMoveBlendRatio;
        }
        else
        {
            pPlayerData->m_fMoveBlendRatio = fMaximumMoveBlendRatio + pPlayerData->m_fMoveBlendRatio;
        }
    }

DONT_MODIFY_MOVE_BLEND_RATIO:
    if (!(CWeaponInfo::GetWeaponInfo(pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_nType, 1)->m_nFlags.bHeavy))
    {
        unsigned int pedField_568 = pPlayerPed->field_568;
        unsigned int unknownFlags = 0;
        if (!pedField_568 || (unknownFlags = *(unsigned int*)(pedField_568 + 64), (unknownFlags & 4) == 0) || ((unknownFlags & 8) != 0))
        {
            if (!pPlayerPed->m_pIntelligence->GetTaskHold(0)
                || !pPlayerPed->m_pIntelligence->GetTaskHold(0)->m_pAnimBlendAssociation)
            {
                CAnimBlendHierarchy* pAnimHierarchy = nullptr;
                CAnimBlendAssocGroup* pAnimGroup = &CAnimManager::ms_aAnimAssocGroups[pPlayerPed->m_nAnimGroup];

                if (pPlayerPed->m_pPlayerData->m_bPlayerSprintDisabled
                    || g_surfaceInfos->IsSprint(pPlayerPed->m_nContactSurface)
                    || (pAnimHierarchy = pAnimGroup->GetAnimation(1)->m_pHeirarchy,
                        pAnimHierarchy == pAnimGroup->GetAnimation(2)->m_pHeirarchy))
                {
                    if (pPad->GetSprint())
                    {
                        pPlayerPed->m_nMoveState = PEDMOVE_RUN;
                    }
                }
                else if (pPlayerPed->ControlButtonSprint((eSprintType)0) >= 1.0)
                {
                    pPlayerPed->m_nMoveState = PEDMOVE_SPRINT;
                }
            }
        }
    }

    pPlayerPed->SetRealMoveAnim();
    // What is the point of calling RpAnimBlendClumpGetAssociation here? 
    // Nvm, let's keep it.
    RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, 11);
    RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, 12);

    if (bAvoidJumpingAndDucking)
    {
        PlayIdleAnimations(pPlayerPed);
        pPlayerPed->m_pedIK.bSlopePitch = 1;
        return pPlayerPed->m_pedIK.m_nFlags;
    }

    if (pPad->DuckJustDown() && CTaskSimpleDuck::CanPedDuck(pPlayerPed))
    {
        pPlayerPed->m_pIntelligence->SetTaskDuckSecondary(0);
    }

    if (!pPlayerPed->bIsInTheAir && !(CWeaponInfo::GetWeaponInfo(pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_nType, 1)->m_nFlags.bHeavy))
    {
        if (pPad->JumpJustDown())
        {
            if (!pPad->GetTarget() && !pPlayerPed->m_pAttachedTo)
            {
                eCamMode cameraMode = TheCamera.m_aCams[TheCamera.m_nActiveCam].m_nMode;
                if (cameraMode != MODE_SNIPER
                    && cameraMode != MODE_ROCKETLAUNCHER
                    && cameraMode != MODE_ROCKETLAUNCHER_HS
                    && cameraMode != MODE_M16_1STPERSON
                    && cameraMode != MODE_HELICANNON_1STPERSON
                    && cameraMode != MODE_CAMERA)
                {
                    pPlayerPed->ClearWeaponTarget();
                    if (pPlayerPed->m_pIntelligence->m_TaskMgr.GetActiveTask())
                    {
                        CTask* pActiveTask = pPlayerPed->m_pIntelligence->m_TaskMgr.GetActiveTask();
                        if (pActiveTask->GetId() != TASK_COMPLEX_JUMP)
                        {
                            CTaskComplexJump* pComplexTaskJump = nullptr;
                            CTask* pNewTask = static_cast<CTask*>(CTask::operator new(20));
                            if (pNewTask)
                            {
                                pComplexTaskJump = static_cast<CTaskComplexJump*>(pNewTask);
                                pComplexTaskJump = pComplexTaskJump->Constructor(COMPLEX_JUMP_TYPE_JUMP);
                            }
                            pPlayerPed->m_pIntelligence->m_TaskMgr.SetTask(pComplexTaskJump, 3, 0);
                        }
                    }
                }
            }
        }
    }

    PlayIdleAnimations(pPlayerPed);
    pPlayerPed->m_pedIK.bSlopePitch = 1;
    return pPlayerPed->m_pedIK.m_nFlags;
#endif
}