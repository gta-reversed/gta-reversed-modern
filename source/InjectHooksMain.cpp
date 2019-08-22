#include "StdInc.h"
#include "detours.h"

#pragma comment(lib, "detours.lib")


//void PlayIdleAnimations(CPed* pPed)
auto OLD_CTaskSimplePlayerOnFoot__PlayerControlZelda = (void(__thiscall*)(CTaskSimplePlayerOnFoot * pThis, CPed * pPed, bool bAvoidJumpingAndDucking))0x6883D0;

void __fastcall CTaskSimplePlayerOnFoot__PlayerControlZelda(CTaskSimplePlayerOnFoot* pThis, void* padding, CPed* pPed, bool bAvoidJumpingAndDucking);

//CTask* __cdecl CTaskManager__GetSimplestTask(CTask* pTask);
void __cdecl HOOK_THEFUNCTION();

void InjectHooksMain(void)
{
    /*CAnimManager::InjectHooks();
    CTaskManager::InjectHooks();
    std::printf("okay, only CAnimManager and CTaskManager hooks\n ");
    CStreaming::InjectHooks();
    CRenderer::InjectHooks();*/


    //InjectHook(0x0681C10, &HOOK_THEFUNCTION, PATCH_JUMP);

   // /*
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    std::printf("GOING TO HOOK FUNC NOW\n");
    DetourAttach(&(PVOID&)OLD_CTaskSimplePlayerOnFoot__PlayerControlZelda, CTaskSimplePlayerOnFoot__PlayerControlZelda);
    DetourTransactionCommit();
    //*/
}

enum eFunctionReturnValue 
{
    FUNCTION_RETURN = 0,
    FUNCTION_INSIDE_IF = 1,
    FUNCTION_OUTSIDE_IF = 2
};
/*
dwReturnLocation:
0 means that the function should return.
1 means continue the function and it is inside of the "if" condition
2 means continue the function and it is outside of the "if" condition
*/


void __fastcall CTaskSimplePlayerOnFoot__PlayerControlZelda(CTaskSimplePlayerOnFoot* pThis, void* padding, CPed* pPed, bool bAvoidJumpingAndDucking)
//CTask* __cdecl CTaskManager__GetSimplestTask(CTask* pTask)
{
    printf(" calling CTaskSimplePlayerOnFoot__PlayerControlZelda\n");

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
        pThis->PlayIdleAnimations(pPlayerPed);
        pPlayerPed->m_pedIK.bSlopePitch = 1;
        return;
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

    pThis->PlayIdleAnimations(pPlayerPed);
    pPlayerPed->m_pedIK.bSlopePitch = 1;
}
