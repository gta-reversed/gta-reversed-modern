#include "StdInc.h"

int& gLastRandomNumberForIdleAnimationID = *reinterpret_cast<int*>(0x8D2FEC);
unsigned int& gLastTouchTimeDelta = *reinterpret_cast<unsigned int*>(0xC19664);
float& gDuckAnimBlendData = *reinterpret_cast<float*>(0x8D2FF0);
bool& gbUnknown_8D2FE8 = *reinterpret_cast<bool*>(0x8D2FE8);

void CTaskSimplePlayerOnFoot::InjectHooks()
{
    HookInstall(0x688810, &CTaskSimplePlayerOnFoot::ProcessPed_Reversed, 7);
    HookInstall(0x6859A0, &CTaskSimplePlayerOnFoot::ProcessPlayerWeapon, 7);
    HookInstall(0x6872C0, &CTaskSimplePlayerOnFoot::PlayIdleAnimations, 7);
    HookInstall(0x687C20, &CTaskSimplePlayerOnFoot::PlayerControlZeldaWeapon, 7);
    HookInstall(0x687F30, &CTaskSimplePlayerOnFoot::PlayerControlDucked, 7);
    HookInstall(0x6883D0, &CTaskSimplePlayerOnFoot::PlayerControlZelda, 7);
}

bool CTaskSimplePlayerOnFoot::ProcessPed(class CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x688810, CTaskSimplePlayerOnFoot*, CPed*>(this, ped);
#else
    return ProcessPed_Reversed(ped);
#endif
}

bool CTaskSimplePlayerOnFoot::ProcessPed_Reversed(class CPed* ped)
{
    bool result = false;
    CPed* pPed = ped;
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
                PlayerControlZelda(pPlayerPed, false);
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
}

CTaskSimplePlayerOnFoot* CTaskSimplePlayerOnFoot::Constructor()
{
    return plugin::CallMethodAndReturn<CTaskSimplePlayerOnFoot*, 0x685750, CTaskSimplePlayerOnFoot*>(this);
}

CTaskSimplePlayerOnFoot* CTaskSimplePlayerOnFoot::Destructor()
{
    return plugin::CallMethodAndReturn<CTaskSimplePlayerOnFoot*, 0x68B0C0, CTaskSimplePlayerOnFoot*>(this);
}


/*
    Everything works for this function except stealth kill. It should be
    fixed later.
*/
void CTaskSimplePlayerOnFoot::ProcessPlayerWeapon(CPlayerPed* pPlayerPed)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethod<0x6859A0, CTaskSimplePlayerOnFoot*, CPlayerPed*>(this, pPlayerPed);
#else
    CPlayerData* pPlayerData = pPlayerPed->m_pPlayerData;
    CPedIntelligence* pIntelligence = pPlayerPed->m_pIntelligence;
    CTaskManager* pTaskManager = &pIntelligence->m_TaskMgr;
    CPad* pPad = pPlayerPed->GetPadFromPlayer();

    eWeaponType weaponType = pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_nType;
    unsigned char weaponSkill = pPlayerPed->GetWeaponSkill();
    CWeaponInfo* pWeaponInfo = CWeaponInfo::GetWeaponInfo(weaponType, weaponSkill);

    if (pPlayerData->m_bHaveTargetSelected && !pPlayerPed->m_pTargetedObject)
    {
        TheCamera.ClearPlayerWeaponMode();
        CWeaponEffects::ClearCrossHair(pPlayerPed->m_nPedType);
    }
    pPlayerPed->m_nWeaponAccuracy = pWeaponInfo->m_nFlags.bCanAim ? 95 : 100;
    if (pPad->WeaponJustDown(pPlayerPed)
        && (pPlayerPed->m_pTargetedObject || CCamera::m_bUseMouse3rdPerson && pPlayerPed->m_p3rdPersonMouseTarget))
    {
        pPlayerPed->PlayerHasJustAttackedSomeone();
    }
    if (pPlayerPed->m_pFire || !pWeaponInfo->m_nFlags.b1stPerson)
    {
        if (!pPad->GetTarget() && weaponType == WEAPON_RLAUNCHER_HS)
        {
            pPlayerData->m_nFireHSMissilePressedTime = 0;
            pPlayerData->m_LastHSMissileTarget = 0;
        }
    }
    else
    {
        if (pPad->GetEnterTargeting()
            || TheCamera.m_bJustJumpedOutOf1stPersonBecauseOfTarget
            || pPad->GetTarget() && m_nFrameCounter < (CTimer::m_FrameCounter - 1))
        {
            unsigned int weaponId = 0;
            switch (weaponType)
            {
            case WEAPON_RLAUNCHER:
            {
                weaponId = MODE_ROCKETLAUNCHER;
                break;
            }
            case WEAPON_RLAUNCHER_HS:
            {
                pPlayerData->m_nFireHSMissilePressedTime = CTimer::m_snTimeInMilliseconds;
                pPlayerData->m_LastHSMissileTarget = 0;
                weaponId = MODE_ROCKETLAUNCHER_HS;
                break;
            }
            case WEAPON_SNIPERRIFLE:
            {
                weaponId = MODE_SNIPER;
                break;
            }
            case WEAPON_CAMERA:
            {
                weaponId = MODE_CAMERA;
                break;
            }
            default:
            {
                weaponId = MODE_M16_1STPERSON;
                break;
            }
            }
            TheCamera.SetNewPlayerWeaponMode(weaponId, 0, 0);
            pPlayerPed->SetPedState(PEDSTATE_SNIPER_MODE);
            return;
        }
        if (!TheCamera.Using1stPersonWeaponMode())
        {
            weaponType = pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_nType;
            if (weaponType == WEAPON_RLAUNCHER || weaponType == WEAPON_RLAUNCHER_HS
                || weaponType == WEAPON_SNIPERRIFLE || weaponType == WEAPON_CAMERA)
            {
                CTaskSimpleUseGun* pSimpleTaskUseGun = pIntelligence->GetTaskUseGun();
                if (pSimpleTaskUseGun)
                {
                    pSimpleTaskUseGun->PlayerPassiveControlGun();
                }
                pPlayerPed->m_pPlayerData->m_bHaveTargetSelected = 0;
                return;
            }
        }
    }

    CTaskSimpleUseGun* pNewSimpleUseGunTask = nullptr;
    int gunCommand[4] = { 0 };

    if (pWeaponInfo->m_nWeaponFire == WEAPON_FIRE_MELEE)
    {
        // /*
        int fightCommand = 0;
        gunCommand[0] = 0;

        if (!pPlayerPed->m_pTargetedObject && !pPad->GetTarget() && !pTaskManager->GetTaskSecondary(0))
        {
            if (pPad->MeleeAttackJustDown(0))
            {
                fightCommand = 11;
                gunCommand[0] = 11;
            }

            CAnimBlendAssociation* pAnimAssoc = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, STEALTH_KN_KILL_PARTIAL);
            if (pAnimAssoc)
            {
                pAnimAssoc->m_fBlendAmount = -2.0;
            }

            if (fightCommand == 0)
            {
            HANDLE_FIGHTING_TASK_IF_EXISTS:
                if (pIntelligence->GetTaskFighting())
                {
                    auto pTaskSimpleFight = static_cast<CTaskSimpleFight*>(pTaskManager->GetTaskSecondary(0));
                    if (pPlayerPed->m_nMoveState == PEDMOVE_STILL && pPad->GetSprint())
                    {
                        pTaskSimpleFight->ControlFight(pPlayerPed->m_pTargetedObject, 15);
                    }
                    else
                    {
                        if (pPlayerData->m_nChosenWeapon == pPlayerPed->m_nActiveWeaponSlot)
                        {
                            pTaskSimpleFight->ControlFight(pPlayerPed->m_pTargetedObject, 0);
                        }
                        else
                        {
                            pTaskSimpleFight->ControlFight(pPlayerPed->m_pTargetedObject, 1);
                        }
                    }
                }
                goto PED_WEAPON_AIMING_CODE;
            }

            // fightCommand cannot be 19 here, so we don't need the code here.
            if (fightCommand == 19)
            {
                // Just in case, if this executes somehow, then we probably need to add the code.
                // But It won't.
                assert(fightCommand != 19);
                //LAB_00685c62:
            }

            goto EXECUTE_MELEE_ATTACK;
        }
        else
        {
            CPed* pTargetEntity = nullptr;
            if (!pPlayerPed->m_pTargetedObject)
            {
                if (CCamera::m_bUseMouse3rdPerson && pPlayerPed->m_p3rdPersonMouseTarget)
                {
                    pTargetEntity = pPlayerPed->m_p3rdPersonMouseTarget;
                }
            }
            else
            {
                if (pPlayerPed->m_pTargetedObject->m_nType == ENTITY_TYPE_PED)
                {
                    pTargetEntity = reinterpret_cast<CPed*>(pPlayerPed->m_pTargetedObject);
                }
            }

            CAnimBlendAssociation* pAnimAssociation = nullptr;
            int animGroupID = pWeaponInfo->m_dwAnimGroup;
            if (pTargetEntity && pPad->GetTarget()
                && pPlayerData->m_fMoveBlendRatio < 1.9
                && pPlayerPed->m_nMoveState != PEDMOVE_SPRINT
                && !pTaskManager->GetTaskSecondary(0)
                && animGroupID != 0
                && CAnimManager::ms_aAnimAssocGroups[animGroupID].m_pAnimBlock
                && CAnimManager::ms_aAnimAssocGroups[animGroupID].m_pAnimBlock->bLoaded
                && pIntelligence->TestForStealthKill(pTargetEntity, 0))
            {
                if (pPlayerPed->bIsDucking)
                {
                    CTaskSimpleDuck* pDuckTask = pIntelligence->GetTaskDuck(1);
                    if (pDuckTask && pDuckTask->IsTaskInUseByOtherTasks())
                    {
                        pAnimAssociation = RpAnimBlendClumpGetFirstAssociation(pPlayerPed->m_pRwClump);
                    }
                    else
                    {
                        pAnimAssociation = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, pWeaponInfo->m_dwAnimGroup, STEALTH_KN_KILL_PARTIAL, 8.0);
                    }
                }
                else
                {
                    pAnimAssociation = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, pWeaponInfo->m_dwAnimGroup, STEALTH_KN_KILL_PARTIAL, 8.0);
                }
            }
            else
            {
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, STEALTH_KN_KILL_PARTIAL);
                if (pAnimAssociation)
                {
                    pAnimAssociation->m_fBlendAmount = -2.0;
                }
            }

            bool bCheckButtonCircleStateOnly = 0;
            if (pPlayerPed->m_pTargetedObject || pPad->GetTarget())
            {
                bCheckButtonCircleStateOnly = 1;
            }
            unsigned char meleeAttackJustDown = pPad->MeleeAttackJustDown(bCheckButtonCircleStateOnly);
            if (meleeAttackJustDown && pAnimAssociation && pAnimAssociation->m_fBlendAmount > 0.5
                && pTargetEntity && pIntelligence->TestForStealthKill(pTargetEntity, 1))
            {
                CTask* pNewTask = static_cast<CTask*>(CTask::operator new(32));
                CTaskSimpleStealthKill* pTaskSimpleStealthKill = nullptr;
                if (pNewTask)
                {
                    pTaskSimpleStealthKill = static_cast<CTaskSimpleStealthKill*>(pNewTask);
                    pTaskSimpleStealthKill->Constructor(1, pTargetEntity, pWeaponInfo->m_dwAnimGroup);
                }

                pTaskManager->SetTask(pTaskSimpleStealthKill, 3, 0);

                eWeaponType activeWeaponType = pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_nType;
                CPedDamageResponseCalculator pedDamageResponseCalculator;
                pedDamageResponseCalculator.Constructor1(pPlayerPed, 0.0, activeWeaponType, PED_PIECE_TORSO, 0);


                bool bPedVehicle = pTargetEntity->m_nPedFlags >> 8 & 0xFFFFFF01;

                CEventDamage eventDamage;
                eventDamage.Constructor1(pPlayerPed, CTimer::m_snTimeInMilliseconds, activeWeaponType, PED_PIECE_TORSO, 0, 0, bPedVehicle);
                CPedDamageResponse damageResponseInfo;
                if (eventDamage.AffectsPed(pTargetEntity))
                {
                    pedDamageResponseCalculator.ComputeDamageResponse(pTargetEntity, &damageResponseInfo, 0);
                    pIntelligence->m_eventGroup.Add((CEvent*)& eventDamage, 0);
                    CCrime::ReportCrime(18, pTargetEntity, pPlayerPed);
                    pPlayerPed->m_weaponAudio.AddAudioEvent(156);
                }
                pPlayerPed->ClearWeaponTarget();
                eventDamage.Destructor1();
                pedDamageResponseCalculator.Destructor1();
            }
            else
            {
                CWeapon* pActiveWeapon = &pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot];
                switch (meleeAttackJustDown)
                {
                case 1:
                {
                    fightCommand = 11;
                    gunCommand[0] = fightCommand;
                    break;
                }
                case 4:
                {
                    if (!CWeaponInfo::GetWeaponInfo(pActiveWeapon->m_nType, 1)->m_nFlags.bHeavy)
                    {
                        fightCommand = 12;
                        gunCommand[0] = 12;
                    }
                    else
                    {
                        fightCommand = 11;
                        gunCommand[0] = fightCommand;
                    }
                    break;
                }
                case 3:
                {
                    fightCommand = 2;
                    gunCommand[0] = fightCommand;
                    break;
                }
                default:
                {
                    if (pPad->GetMeleeAttack(0) && pActiveWeapon->m_nType == WEAPON_CHAINSAW && pTaskManager->GetTaskSecondary(0))
                    {
                        fightCommand = 11;
                        gunCommand[0] = fightCommand;
                    }
                    else
                    {
                        goto HANDLE_FIGHTING_TASK_IF_EXISTS;
                    }
                }
                };

            EXECUTE_MELEE_ATTACK:
                if (pTaskManager->GetTaskSecondary(0))
                {
                    if (pIntelligence->GetTaskFighting())
                    {
                        auto pTaskSimpleFight = static_cast<CTaskSimpleFight*>(pTaskManager->GetTaskSecondary(0));
                        pTaskSimpleFight->ControlFight(pPlayerPed->m_pTargetedObject, gunCommand[0]);
                    }
                }
                else
                {
                    CTask* pNewTask = static_cast<CTask*>(CTask::operator new(40));
                    CTaskSimpleFight* pTaskSimpleFight = nullptr;
                    if (pNewTask)
                    {
                        pTaskSimpleFight = static_cast<CTaskSimpleFight*>(pNewTask);
                        pTaskSimpleFight->Constructor(pPlayerPed->m_pTargetedObject, fightCommand, 2000u);
                    }

                    pTaskManager->SetTaskSecondary(pTaskSimpleFight, 0);
                }
            }
        }
        //*/
    }
    else
    {
        if (pWeaponInfo->m_nWeaponFire == WEAPON_FIRE_USE)
        {
            if (pPad->WeaponJustDown(0))
            {
                unsigned char activeWeaponSlot = pPlayerPed->m_nActiveWeaponSlot;
                weaponType = pPlayerPed->m_aWeapons[activeWeaponSlot].m_nType;
                CWeapon* pPlayerWeapon = &pPlayerPed->m_aWeapons[activeWeaponSlot];
                if (weaponType == WEAPON_DETONATOR)
                {
                    CMatrixLink* pPlayerMatrix = pPlayerPed->m_matrix;
                    if (pPlayerMatrix)
                    {
                        pPlayerWeapon->Fire(pPlayerPed, &pPlayerMatrix->pos, &pPlayerMatrix->pos, 0, 0, 0);
                    }
                    else
                    {
                        pPlayerWeapon->Fire(pPlayerPed, &pPlayerPed->m_placement.m_vPosn, &pPlayerPed->m_placement.m_vPosn, 0, 0, 0);
                    }
                }
                else if (weaponType > WEAPON_CAMERA && weaponType <= WEAPON_INFRARED && !pTaskManager->m_aPrimaryTasks[3])
                {
                    CTaskComplexUseGoggles* pCTaskComplexUseGoggles = nullptr;
                    CTask* pNewTask = static_cast<CTask*>(CTask::operator new(12));
                    if (pNewTask)
                    {
                        pCTaskComplexUseGoggles = static_cast<CTaskComplexUseGoggles*>(pNewTask);
                        pCTaskComplexUseGoggles->Constructor();
                    }

                    pTaskManager->SetTask(pCTaskComplexUseGoggles, 3, 0);
                    pPlayerPed->m_pPlayerData->m_bDontAllowWeaponChange = 1;
                }
            }
        }
        else
        {
            if (!pPad->GetWeapon(pPlayerPed))
            {
                if (pIntelligence->GetTaskThrow())
                {
                    auto pTaskSimpleThrowProjectile = static_cast<CTaskSimpleThrowProjectile*>(pTaskManager->GetTaskSecondary(0));
                    pTaskSimpleThrowProjectile->ControlThrow(1, 0, 0);
                }
            }
            else
            {
                unsigned int nWeaponFire = pWeaponInfo->m_nWeaponFire;
                if (pPlayerPed->m_nMoveState != PEDMOVE_SPRINT && pPlayerData->m_nChosenWeapon == pPlayerPed->m_nActiveWeaponSlot && (nWeaponFire - 1) < 4)
                {
                    switch (nWeaponFire)
                    {
                    case WEAPON_FIRE_INSTANT_HIT:
                    case WEAPON_FIRE_AREA_EFFECT:
                    {
                        CEntity* pTargetedObject = pPlayerPed->m_pTargetedObject;
                        gunCommand[0] = 2;
                        if (CTaskSimpleUseGun::RequirePistolWhip(pPlayerPed, pTargetedObject))
                        {
                            gunCommand[0] = 5;
                        }
                        else if (pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_nState == 2)
                        {
                            if (!pPad->GetTarget() && !pTargetedObject && !pPlayerData->m_bFreeAiming)
                            {
                                break;
                            }
                            gunCommand[0] = 1;
                        }
                        CTask* pSecondaryTask = pTaskManager->GetTaskSecondary(0);
                        if (pSecondaryTask)
                        {
                            if (pSecondaryTask->GetId() == TASK_SIMPLE_USE_GUN)
                            {
                                CTaskSimpleUseGun* pTaskUseGun = pIntelligence->GetTaskUseGun();
                                if (pTaskUseGun)
                                {
                                    pTaskUseGun->ControlGun(pPlayerPed, pTargetedObject, gunCommand[0]);
                                }
                            }
                            else
                            {
                                pSecondaryTask->MakeAbortable(pPlayerPed, ABORT_PRIORITY_URGENT, 0);
                            }
                        }
                        else
                        {
                            CTask* pNewTask = static_cast<CTask*>(CTask::operator new(60));
                            CTaskSimpleUseGun* pTaskUseGun = nullptr;
                            if (pNewTask)
                            {
                                pTaskUseGun = static_cast<CTaskSimpleUseGun*>(pNewTask);
                                pTaskUseGun->Constructor(pTargetedObject, CVector(0.0, 0.0, 0.0), gunCommand[0], 1, 0);
                            }

                            pTaskManager->SetTaskSecondary(pTaskUseGun, 0);
                            pPlayerPed->m_pPlayerData->m_fAttackButtonCounter = 0;
                        }
                        if (!pPad->GetTarget())
                        {
                            if (pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_nType == WEAPON_EXTINGUISHER)
                            {
                                pPlayerData->m_fLookPitch = -CWeapon::ms_fExtinguisherAimAngle;
                            }
                            else
                            {
                                pPlayerData->m_fLookPitch = 0.0;
                            }
                        }
                        break;
                    }
                    case WEAPON_FIRE_PROJECTILE:
                    {
                        unsigned char activeWeaponSlot = pPlayerPed->m_nActiveWeaponSlot;
                        CWeapon* pActiveWeapon = &pPlayerPed->m_aWeapons[activeWeaponSlot];
                        if (pActiveWeapon->m_nType == WEAPON_RLAUNCHER || pActiveWeapon->m_nType == WEAPON_RLAUNCHER_HS)
                        {
                            gunCommand[0] = 2;
                            if (pActiveWeapon->m_nState == 2)
                            {
                                gunCommand[0] = 1;
                            }
                            CTask* pTaskSecondary = pTaskManager->GetTaskSecondary(0);
                            if (pTaskSecondary)
                            {
                                if (pTaskSecondary->GetId() == TASK_SIMPLE_USE_GUN)
                                {
                                    if (pIntelligence->GetTaskUseGun())
                                    {
                                        CTaskSimpleUseGun* pTaskUseGun = static_cast<CTaskSimpleUseGun*>(pTaskSecondary);
                                        pTaskUseGun->ControlGun(pPlayerPed, pPlayerPed->m_pTargetedObject, gunCommand[0]);
                                    }
                                }
                                else
                                {
                                    CTask* pTaskSecondary = pTaskManager->GetTaskSecondary(0);
                                    pTaskSecondary->MakeAbortable(pPlayerPed, ABORT_PRIORITY_URGENT, 0);
                                }
                            }
                            else
                            {
                                CTask* pNewTask = static_cast<CTask*>(CTask::operator new(60));
                                CTaskSimpleUseGun* pTaskUseGun = nullptr;
                                if (pNewTask)
                                {
                                    pTaskUseGun = static_cast<CTaskSimpleUseGun*>(pNewTask);
                                    pTaskUseGun->Constructor(pPlayerPed->m_pTargetedObject, CVector(0.0, 0.0, 0.0), gunCommand[0], 1, 0);
                                    pTaskManager->SetTaskSecondary(pTaskUseGun, 0);
                                }
                            }
                        }
                        else
                        {
                            if (pTaskManager->GetTaskSecondary(0) || !pPad->WeaponJustDown(pPlayerPed))
                            {
                                CTask* pTaskSecondary = pTaskManager->GetTaskSecondary(0);
                                if (pTaskSecondary && pTaskSecondary->GetId() != TASK_SIMPLE_THROW)
                                {
                                    pTaskSecondary->MakeAbortable(pPlayerPed, ABORT_PRIORITY_URGENT, 0);
                                }
                                else if (pIntelligence->GetTaskThrow())
                                {
                                    auto pTaskSimpleThrowProjectile = static_cast<CTaskSimpleThrowProjectile*>(pTaskSecondary);
                                    pTaskSimpleThrowProjectile->ControlThrow(pPad->WeaponJustDown(pPlayerPed), 0, 0);
                                }
                            }
                            else
                            {
                                CTask* pNewTask = static_cast<CTask*>(CTask::operator new(36));
                                CTaskSimpleThrowProjectile* pTaskSimpleThrowProjectile = nullptr;
                                if (pNewTask)
                                {
                                    pTaskSimpleThrowProjectile = static_cast<CTaskSimpleThrowProjectile*>(pNewTask);
                                    pTaskSimpleThrowProjectile->Constructor(0, CVector(0, 0, 0));
                                    pTaskManager->SetTaskSecondary(pTaskSimpleThrowProjectile, 0);
                                }
                            }
                        }
                        break;
                    }
                    case WEAPON_FIRE_CAMERA:
                    {
                        unsigned char activeWeaponSlot = pPlayerPed->m_nActiveWeaponSlot;
                        CWeapon* pActiveWeapon = &pPlayerPed->m_aWeapons[activeWeaponSlot];
                        if (TheCamera.m_aCams[TheCamera.m_nActiveCam].m_nMode == MODE_CAMERA && CTimer::m_snTimeInMilliseconds > pActiveWeapon->m_nTimeForNextShot)
                        {
                            CVector firingPoint(0.0, 0.0, 0.60000002);

                            CVector outputFiringPoint(0.0, 0.0, 0.0);
                            MultiplyMatrixWithVector(&outputFiringPoint, pPlayerPed->m_matrix, &firingPoint);
                            pActiveWeapon->Fire(pPlayerPed, &outputFiringPoint, 0, 0, 0, 0);
                        }
                        break;
                    }
                    };
                }
            }
        }
    }

PED_WEAPON_AIMING_CODE:

    CVector firingPoint(0.0, 0.0, 0.0);
    CVector upVector(0.0, 0.0, 0.0);


    if (pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_nState == WEAPONSTATE_RELOADING && pWeaponInfo->m_nFlags.bReload)
    {
        if (!pIntelligence->GetTaskUseGun())
        {
            int animGroupId = pWeaponInfo->m_dwAnimGroup;
            int crouchReloadAnimID = (pWeaponInfo->m_nFlags4Bytes >> 12 & 1) != 0 ? 226 : 0;
            if (!pPlayerPed->bIsDucking)
            {
                if (!RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, crouchReloadAnimID))
                {
                    CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, animGroupId, crouchReloadAnimID, 4.0);
                }
            }
            else
            {
                auto pDuckTask = (CTaskSimpleDuck*)pIntelligence->GetTaskDuck(1);
                if (pWeaponInfo->GetCrouchReloadAnimationID() && gbUnknown_8D2FE8 && pDuckTask)
                {
                    if (!pDuckTask->IsTaskInUseByOtherTasks())
                    {
                        crouchReloadAnimID = pWeaponInfo->GetCrouchReloadAnimationID();
                        if (!RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, crouchReloadAnimID))
                        {
                            crouchReloadAnimID = pWeaponInfo->GetCrouchReloadAnimationID();
                            CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, animGroupId, crouchReloadAnimID, 4.0);
                        }
                    }
                }
            }
        }
        else
        {
            auto pTaskUseGun = (CTaskSimpleUseGun*)pTaskManager->GetTaskSecondary(0);
            pTaskUseGun->ControlGun(pPlayerPed, pPlayerPed->m_pTargetedObject, 4);
        }
    }

    int fightCommand = 0;
    if (!pPad->GetTarget()
        || pPlayerPed->m_pPlayerData->m_nChosenWeapon != pPlayerPed->m_nActiveWeaponSlot
        || pPlayerPed->m_nMoveState == PEDMOVE_SPRINT && pWeaponInfo->m_nWeaponFire
        || TheCamera.Using1stPersonWeaponMode())
    {
        if (!pPad->GetTarget() && !pPlayerPed->m_pAttachedTo
            || pPlayerPed->m_pPlayerData->m_nChosenWeapon != pPlayerPed->m_nActiveWeaponSlot
            || pPlayerPed->m_nMoveState == PEDMOVE_SPRINT
            || !TheCamera.Using1stPersonWeaponMode())
        {
            if ((pPlayerPed->m_pTargetedObject || pPlayerPed->m_pPlayerData->m_bFreeAiming)
                && pIntelligence->GetTaskFighting())
            {
                if (pPlayerData->m_vecFightMovement.y >= -0.5)
                {
                    fightCommand = 15;
                }
                else
                {
                    fightCommand = 16;
                }
                CTaskSimpleFight* pTaskSimpleFight = pIntelligence->GetTaskFighting();
                pTaskSimpleFight->ControlFight(0, fightCommand);
            }
            if (pIntelligence->GetTaskUseGun())
            {
                if (pPad->GetWeapon(0)
                    || (double)pPad->GetPedWalkUpDown() <= 50.0
                    && (double)pPad->GetPedWalkUpDown() >= -50.0
                    && (double)pPad->GetPedWalkLeftRight() <= 50.0
                    && (double)pPad->GetPedWalkLeftRight() >= -50.0)
                {
                    CTaskSimpleUseGun* pTaskUseGun = pIntelligence->GetTaskUseGun();
                    pTaskUseGun->PlayerPassiveControlGun();
                }
                else
                {
                    CTaskSimpleUseGun* pTaskUseGun = pIntelligence->GetTaskUseGun();
                    pTaskUseGun->ControlGun(pPlayerPed, pPlayerPed->m_pTargetedObject, 7);
                }
                CCam* pCam = &TheCamera.m_aCams[TheCamera.m_nActiveCam];
                if (!pWeaponInfo->m_nFlags.bAimWithArm && pCam->m_nMode == MODE_FOLLOWPED)
                {
                    pPlayerPed->m_fAimingRotation = atan2(-pCam->m_vecFront.x, pCam->m_vecFront.y);
                }
                if (pPlayerPed->m_pTargetedObject || pPlayerData->m_bFreeAiming)
                {
                    CTaskSimpleUseGun* pTaskUseGun = pIntelligence->GetTaskUseGun();
                    pTaskUseGun->SkipAim(pPlayerPed);
                }
            }
            if (pPlayerPed->m_pTargetedObject)
            {
                pPlayerPed->ClearWeaponTarget();
            }
            pPlayerPed->Clear3rdPersonMouseTarget();
            pPlayerData->m_bFreeAiming = 0;
            goto MAKE_PLAYER_LOOK_AT_ENTITY;
        }
        if (!pTaskManager->GetTaskSecondary(0))
        {
            pNewSimpleUseGunTask = (CTaskSimpleUseGun*)CTask::operator new(60);
            if (pNewSimpleUseGunTask)
            {
                firingPoint.x = 0.0;
                firingPoint.y = 0.0;
                firingPoint.z = 0.0;
                pNewSimpleUseGunTask->Constructor(pPlayerPed->m_pTargetedObject, CVector(0.0, 0.0, 0.0), 1, 1, 0);
            }

            pTaskManager->SetTaskSecondary(pNewSimpleUseGunTask, 0);
            goto MAKE_PLAYER_LOOK_AT_ENTITY;
        }
        if (pIntelligence->GetTaskUseGun())
        {
            auto pTaskUseGun = (CTaskSimpleUseGun*)pTaskManager->GetTaskSecondary(0);
            pTaskUseGun->ControlGun(pPlayerPed, pPlayerPed->m_pTargetedObject, 1);
        }
        goto MAKE_PLAYER_LOOK_AT_ENTITY;
    }
    if (!pWeaponInfo->m_nFlags.bCanAim || pPlayerData->m_bFreeAiming)
    {
        if (pPlayerData->m_bFreeAiming && pWeaponInfo->m_nFlags.bCanAim
            && (pPad->ShiftTargetLeftJustDown() || pPad->ShiftTargetRightJustDown())
            && !CCamera::m_bUseMouse3rdPerson)
        {
            if (pPlayerPed->m_pTargetedObject)
            {
                if (pPad->ShiftTargetLeftJustDown())
                {
                    pPlayerPed->FindNextWeaponLockOnTarget(pPlayerPed->m_pTargetedObject, 1);
                }
                if (pPad->ShiftTargetRightJustDown())
                {
                    pPlayerPed->FindNextWeaponLockOnTarget(pPlayerPed->m_pTargetedObject, 0);
                }
            }
            else
            {
                bool shiftTargetLeftJustDown = pPad->ShiftTargetLeftJustDown();
                pPlayerPed->FindNextWeaponLockOnTarget(0, shiftTargetLeftJustDown);
            }
        }
        else if (!pWeaponInfo->m_nFlags.bOnlyFreeAim || pPlayerPed->m_pTargetedObject || pPlayerData->m_bFreeAiming)
        {
            if (CCamera::m_bUseMouse3rdPerson && pPlayerData->m_bFreeAiming)
            {
                bool bWeaponIsNotMelee = 1;
                if (!pWeaponInfo->m_nWeaponFire)
                {
                    bWeaponIsNotMelee = 0;
                }
                pPlayerPed->Compute3rdPersonMouseTarget(bWeaponIsNotMelee);
            }
        }
        else
        {
            pPlayerData->m_bFreeAiming = 1;
        }
    }
    else
    {
        if (pPlayerPed->m_pTargetedObject)
        {
            CPed* pTargetedEntity = (CPed*)pPlayerPed->m_pTargetedObject;
            CWeapon* pActiveWeapon = &pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot];
            char weaponSkill = 0;
            int pedState = 0;
            if ((fabs((double)pPad->AimWeaponLeftRight(pPlayerPed)) > 100.0
                || fabs((double)pPad->AimWeaponUpDown(pPlayerPed)) > 100.0)
                && !CGameLogic::IsCoopGameGoingOn()
                || pTargetedEntity == (CPed*)0
                || CCamera::m_bUseMouse3rdPerson == 1
                || pTargetedEntity
                && pTargetedEntity->m_nType == ENTITY_TYPE_PED
                && (!CPlayerPed::PedCanBeTargettedVehicleWise(pTargetedEntity)
                    || !CLocalisation::KickingWhenDown()
                    && ((pedState = pTargetedEntity->m_nPedState, pedState == PEDSTATE_DIE) || pedState == PEDSTATE_DEAD))
                || pPlayerPed->DoesTargetHaveToBeBroken(pPlayerPed->m_pTargetedObject, pActiveWeapon)
                || !pPlayerPed->bCanPointGunAtTarget
                && (pActiveWeapon->m_nType, weaponSkill = pPlayerPed->GetWeaponSkill(),
                    !(CWeaponInfo::GetWeaponInfo(pActiveWeapon->m_nType, weaponSkill)->m_nFlags.bCanAim))
                )
            {
                pPlayerPed->ClearWeaponTarget();
                pPlayerData->m_bFreeAiming = 1;
            }
            if (pPlayerPed->m_pTargetedObject)
            {
                if (pPad->ShiftTargetLeftJustDown())
                {
                    pPlayerPed->FindNextWeaponLockOnTarget(pPlayerPed->m_pTargetedObject, 1);
                }
                if (pPad->ShiftTargetRightJustDown())
                {
                    pPlayerPed->FindNextWeaponLockOnTarget(pPlayerPed->m_pTargetedObject, 0);
                }
            }
            if (CWeaponInfo::GetWeaponInfo(pActiveWeapon->m_nType, 1)->m_nWeaponFire == WEAPON_FIRE_INSTANT_HIT)
            {
                pTargetedEntity = (CPed*)pPlayerPed->m_pTargetedObject;
                if (pTargetedEntity)
                {
                    if (pTargetedEntity->m_nType == ENTITY_TYPE_PED)
                    {
                        CMatrix* pPlayerMatrix = pPlayerPed->m_matrix;
                        CVector* pPlayerPos = pPlayerMatrix ? &pPlayerMatrix->pos : &pPlayerPed->m_placement.m_vPosn;
                        if (pIntelligence->IsInSeeingRange(pPlayerPos))
                        {
                            CTask* pActivePrimaryTask = pIntelligence->GetActivePrimaryTask();
                            if (!pActivePrimaryTask || pActivePrimaryTask->GetId() != TASK_COMPLEX_REACT_TO_GUN_AIMED_AT)
                            {
                                if (pActiveWeapon->m_nType != WEAPON_PISTOL_SILENCED)
                                {
                                    pPlayerPed->Say(176, 0, 1.0, 0, 0, 0);
                                }
                                CPedGroup* pPedGroup = CPedGroups::GetPedsGroup(pTargetedEntity);
                                if (pPedGroup)
                                {
                                    if (!CPedGroups::AreInSameGroup(pTargetedEntity, pPlayerPed))
                                    {
                                        CEvent* pEvent = (CEvent*)CEvent::operator_new();
                                        CEventGunAimedAt* pEventGunAimedAt = (CEventGunAimedAt*)pEvent;
                                        if (pEvent)
                                        {
                                            pEventGunAimedAt->Constructor(pPlayerPed);
                                        }
                                        CEventGroupEvent eventGroupEvent;
                                        eventGroupEvent.Constructor(pTargetedEntity, pEvent);
                                        pPedGroup->m_groupIntelligence.AddEvent((CEvent*)& eventGroupEvent);
                                        eventGroupEvent.Destructor();
                                    }
                                }
                                else
                                {
                                    CEventGunAimedAt eventGunAimedAt;
                                    eventGunAimedAt.Constructor(pPlayerPed);
                                    pIntelligence->m_eventGroup.Add((CEvent*)& eventGunAimedAt, 0);
                                    eventGunAimedAt.Destructor();
                                }
                            }
                        }
                    }
                }
            }
        }
        else if (CCamera::m_bUseMouse3rdPerson)
        {
            pPlayerPed->ClearWeaponTarget();
        }
        else if (pPad->GetEnterTargeting()
            || TheCamera.m_bJustJumpedOutOf1stPersonBecauseOfTarget
            || m_nFrameCounter < (unsigned int)(CTimer::m_FrameCounter - 1))
        {
            pPlayerPed->FindWeaponLockOnTarget();
        }
        if (!pPlayerPed->m_pTargetedObject)
        {
            pPlayerData->m_bFreeAiming = 1;
        }
    }

    if (pPlayerPed->m_pTargetedObject)
    {
        if (pWeaponInfo->m_nWeaponFire || pPlayerPed->bIsDucking)
        {
            pPlayerData->m_bFreeAiming = 0;
        }
    }
    else
    {
        unsigned int nWeaponFire = pWeaponInfo->m_nWeaponFire;
        if (!nWeaponFire || nWeaponFire == WEAPON_FIRE_PROJECTILE || nWeaponFire == WEAPON_FIRE_USE)
        {
            goto MAKE_PLAYER_LOOK_AT_ENTITY;
        }
    }

    TheCamera.SetNewPlayerWeaponMode(MODE_AIMWEAPON, 0, 0);

    CVector* pTargetedObjectPos = nullptr;
    CEntity* pTargetedEntity = pPlayerPed->m_pTargetedObject;
    if (pTargetedEntity)
    {
        CMatrix* pTargetedObjectMatrix = pTargetedEntity->m_matrix;
        if (pTargetedObjectMatrix)
        {
            pTargetedObjectPos = &pTargetedObjectMatrix->pos;
        }
        else
        {
            pTargetedObjectPos = &pTargetedEntity->m_placement.m_vPosn;
        }
    }
    else
    {
        CMatrix* pPlayerMatrix = pPlayerPed->m_matrix;
        firingPoint.x = pPlayerMatrix->up.x;
        firingPoint.y = pPlayerMatrix->up.y;
        firingPoint.z = pPlayerMatrix->up.z;
        firingPoint.x = firingPoint.x * 5.0;
        firingPoint.y = firingPoint.y * 5.0;
        firingPoint.z = (sin(pPlayerPed->m_pPlayerData->m_fLookPitch) + firingPoint.z) * 5.0;
        CVector* pPlayerPos = &pPlayerPed->m_placement.m_vPosn;
        if (pPlayerMatrix)
        {
            pPlayerPos = &pPlayerMatrix->pos;
        }
        firingPoint += *pPlayerPos;
        pTargetedObjectPos = &firingPoint;
    }

    TheCamera.UpdateAimingCoors(pTargetedObjectPos);
    if (pTaskManager->GetTaskSecondary(0))
    {
        if (pIntelligence->GetTaskUseGun())
        {
            auto pTaskUseGun = (CTaskSimpleUseGun*)pTaskManager->GetTaskSecondary(0);
            pTaskUseGun->ControlGun(pPlayerPed, pPlayerPed->m_pTargetedObject, 1);
        }
    }
    else
    {
        pNewSimpleUseGunTask = (CTaskSimpleUseGun*)CTask::operator new(60);
        if (pNewSimpleUseGunTask)
        {
            firingPoint.x = 0.0;
            firingPoint.y = 0.0;
            firingPoint.z = 0.0;
            pNewSimpleUseGunTask->Constructor(pPlayerPed->m_pTargetedObject, CVector(0.0, 0.0, 0.0), 1, 1, 0);
        }
        pTaskManager->SetTaskSecondary(pNewSimpleUseGunTask, 0);
    }

MAKE_PLAYER_LOOK_AT_ENTITY:
    if (pPlayerPed->m_pTargetedObject)
    {
        pPlayerData->m_bHaveTargetSelected = 1;
    }

    CPed* pTargetedObject = (CPed*)pPlayerPed->m_pTargetedObject;
    bool bTargetedPedDead = 0;
    if (!pTargetedObject)
    {
        goto ABORT_LOOKING_IF_POSSIBLE;
    }
    if (pTargetedObject->m_nType == ENTITY_TYPE_PED && (pTargetedObject->bFallenDown || pTargetedObject->m_nPedState == PEDSTATE_DEAD))
    {
        bTargetedPedDead = 1;
    }

    if ((pWeaponInfo->m_nWeaponFire || pIntelligence->GetTaskFighting() && !bTargetedPedDead)
        && (pPlayerPed->bIsDucking || !pWeaponInfo->m_nFlags.bAimWithArm))
    {
        goto ABORT_LOOKING_IF_POSSIBLE;
    }
    CMatrix* pPlayerMatrix = pPlayerPed->m_matrix;
    CVector* pPlayerPos = &pPlayerMatrix->pos;
    if (!pPlayerMatrix)
    {
        pPlayerPos = &pPlayerPed->m_placement.m_vPosn;
    }
    CMatrix* pTargetedObjectMatrix = pTargetedObject->m_matrix;
    pTargetedObjectPos = pTargetedObjectMatrix ? &pTargetedObjectMatrix->pos : &pTargetedObject->m_placement.m_vPosn;
    firingPoint.x = pTargetedObjectPos->x - pPlayerPos->x;
    firingPoint.y = pTargetedObjectPos->y - pPlayerPos->y;
    firingPoint.z = pTargetedObjectPos->z - pPlayerPos->z;
    CVector* pUpVector = pPlayerPed->GetTopDirection(&upVector);
    if ((firingPoint.z * pUpVector->z + firingPoint.y * pUpVector->y + firingPoint.x * pUpVector->x) <= 0.0)
    {
    ABORT_LOOKING_IF_POSSIBLE:
        if (m_pLookingAtEntity
            && g_ikChainMan->IsLooking(pPlayerPed)
            && g_ikChainMan->GetLookAtEntity(pPlayerPed) == m_pLookingAtEntity)
        {
            g_ikChainMan->AbortLookAt(pPlayerPed, 250);
        }
    }
    else if (!g_ikChainMan->IsLooking(pPlayerPed)
        || (g_ikChainMan->GetLookAtEntity(pPlayerPed) != (CEntity*)pTargetedObject))
    {
        int pedBoneID = BONE_UNKNOWN;
        if (pTargetedObject->m_nType == ENTITY_TYPE_PED)
        {
            pedBoneID = BONE_HEAD;
        }
        g_ikChainMan->LookAt("ProcPlyrWeapon", pPlayerPed, pTargetedObject, gDefaultTaskTime, pedBoneID,
            0, 0, 0.25, 500, 3, 0);
    }

    m_pLookingAtEntity = pTargetedObject;
#endif
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

void CTaskSimplePlayerOnFoot::PlayerControlZeldaWeapon(CPlayerPed* pPlayerPed)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x687C20, CTaskSimplePlayerOnFoot*, CPlayerPed*>(this, pPlayerPed);
#else
    CTaskSimpleUseGun* pTaskUseGun = pPlayerPed->m_pIntelligence->GetTaskUseGun();
    if (pTaskUseGun)
    {
        if (!pPlayerPed->m_pAttachedTo)
        {
            CVector2D moveSpeed(0.0, 0.0);
            CPad* pPad = pPlayerPed->GetPadFromPlayer();
            double pedWalkUpDown = moveSpeed.y;
            double pedWalkLeftRight = moveSpeed.x;
            if (!pTaskUseGun->m_pWeaponInfo->m_nFlags.b1stPerson || CGameLogic::IsPlayerUse2PlayerControls(pPlayerPed))
            {
                pedWalkUpDown = pPad->GetPedWalkUpDown();
                pedWalkLeftRight = pPad->GetPedWalkLeftRight();
            }
            else if (TheCamera.Using1stPersonWeaponMode())
            {
                pedWalkUpDown = pPad->GetPedWalkUpDown(pPlayerPed);
                pedWalkLeftRight = pPad->GetPedWalkLeftRight(pPlayerPed);
            }
            moveSpeed.x = pedWalkLeftRight * 0.0078125f;
            moveSpeed.y = pedWalkUpDown * 0.0078125f;
            CEntity* pTargetedObject = pPlayerPed->m_pTargetedObject;
            if (CGameLogic::IsPlayerUse2PlayerControls(pPlayerPed))
            {
                float moveBlendRatio = sqrt(moveSpeed.x * moveSpeed.x + moveSpeed.y * moveSpeed.y);
                if (moveBlendRatio > 0.0)
                {

                    float radianAngle = CGeneral::GetRadianAngleBetweenPoints(0.0, 0.0, -moveSpeed.x, moveSpeed.y)
                        - TheCamera.m_fOrientation;
                    float limitedRadianAngle = CGeneral::LimitRadianAngle(radianAngle);
                    double negativeSinRadian = -sin(limitedRadianAngle);
                    double cosRadian = cos(limitedRadianAngle);
                    if (pTargetedObject)
                    {
                        if (!CGameLogic::IsPlayerAllowedToGoInThisDirection(pPlayerPed, negativeSinRadian, cosRadian, 0.0, 0.0))
                        {
                            moveBlendRatio = 0.0;
                        }
                        CMatrixLink* pPedMatrix = pPlayerPed->m_matrix;
                        moveSpeed.x = (cosRadian * pPedMatrix->right.y + negativeSinRadian * pPedMatrix->right.x + pPedMatrix->right.z * 0.0)
                            * moveBlendRatio;
                        moveSpeed.y = -((cosRadian * pPedMatrix->up.y + negativeSinRadian * pPedMatrix->up.x + pPedMatrix->up.z * 0.0)
                            * moveBlendRatio);
                    }
                    else
                    {
                        pPlayerPed->m_fAimingRotation = limitedRadianAngle;
                        double moveSpeedY = 0.0;
                        if (CGameLogic::IsPlayerAllowedToGoInThisDirection(pPlayerPed, negativeSinRadian, cosRadian, 0.0, 0.0))
                        {
                            moveSpeedY = moveBlendRatio;
                        }
                        moveSpeed.x = 0.0;
                        moveSpeed.y = -moveSpeedY;
                    }
                }

                if (pTargetedObject)
                {
                    CMatrixLink* pPedMatrix = pPlayerPed->m_matrix;
                    CVector* pPedPos = &pPedMatrix->pos;
                    if (!pPedMatrix)
                    {
                        pPedPos = &pPlayerPed->m_placement.m_vPosn;
                    }
                    CMatrix* pTargetedObjectMatrix = pTargetedObject->m_matrix;
                    CVector* pTargetedObjectPos = &pTargetedObject->m_placement.m_vPosn;;
                    if (pTargetedObjectMatrix)
                    {
                        pTargetedObjectPos = &pTargetedObjectMatrix->pos;
                    }
                    pPlayerPed->m_fAimingRotation = atan2(-(pTargetedObjectPos->x - pPedPos->x), pTargetedObjectPos->y - pPedPos->y);
                }
            }

            float moveBlendRatio = sqrt(moveSpeed.x * moveSpeed.x + moveSpeed.y * moveSpeed.y);
            if (moveBlendRatio > 1.0)
            {
                float moveSpeedMultiplier = 1.0f / moveBlendRatio;
                moveSpeed.x = moveSpeed.x * moveSpeedMultiplier;
                moveSpeed.y = moveSpeedMultiplier * moveSpeed.y;
            }
            pTaskUseGun->ControlGunMove(&moveSpeed);
            if (pPad->DuckJustDown())
            {
                if (CTaskSimpleDuck::CanPedDuck(pPlayerPed))
                {
                    pPlayerPed->m_pIntelligence->SetTaskDuckSecondary(0);
                }
            }
        }
    }
#endif
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
        moveSpeed.x = pPad->GetPedWalkLeftRight() * 0.0078125f;
        moveSpeed.y = pPad->GetPedWalkUpDown() * 0.0078125f;
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
                        pPlayerPed->m_pPlayerData->m_fMoveBlendRatio = 1.5f;
                        pedMoveState = PEDMOVE_RUN;
                    }
                    else
                    {
                        if (pedMoveBlendRatio <= 0.5f)
                        {
                            return;
                        }
                        auto pNewAnimation = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, pPlayerPed->m_nAnimGroup, 0, gDuckAnimBlendData);
                        pNewAnimation->m_bPlaying = 1;
                        pPlayerPed->m_pPlayerData->m_fMoveBlendRatio = 1.5f;
                        pedMoveState = PEDMOVE_WALK;
                    }
                    pPlayerPed->m_nMoveState = pedMoveState;
                    pPlayerPed->m_nSwimmingMoveState = pedMoveState;
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
                    moveSpeed.x = (moveDirection.y * pMatrix->right.y + moveDirection.x * pMatrix->right.x + pMatrix->right.z * 0.0f)
                        * pedMoveBlendRatio;
                    moveSpeed.y = -((moveDirection.y * pMatrix->up.y + pMatrix->up.z * 0.0f + moveDirection.x * pMatrix->up.x)
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
    float pedMoveBlendRatio = sqrt(pedWalkUpDown * pedWalkUpDown + pedWalkLeftRight * pedWalkLeftRight) * 0.016666668f;
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

        float fMaximumMoveBlendRatio = CTimer::ms_fTimeStep * 0.07f;
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
        if (!pPed->somePedStruct || !pPed->somePedStruct->flags.b03 || pPed->somePedStruct->flags.b04)
        {
            if (!pPlayerPed->m_pIntelligence->GetTaskHold(0)
                || !((CTaskSimpleHoldEntity*)pPlayerPed->m_pIntelligence->GetTaskHold(0))->m_pAnimBlendAssociation)
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