#include "StdInc.h"

int& gLastRandomNumberForIdleAnimationID = *reinterpret_cast<int*>(0x8D2FEC);
unsigned int& gLastTouchTimeDelta = *reinterpret_cast<unsigned int*>(0xC19664);

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
                        int animHierarchyIndex = pAnimAssoc1->m_pHierarchy - CAnimManager::ms_aAnimations;
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
    plugin::CallMethod<0x687F30, CTaskSimplePlayerOnFoot*, CPed*>(this, pPed);
}

int CTaskSimplePlayerOnFoot::PlayerControlZelda(CPed* pPed, bool a3)
{
    return plugin::CallMethodAndReturn<int, 0x6883D0, CTaskSimplePlayerOnFoot*, CPed*, bool>(this, pPed, a3);
}