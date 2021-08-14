#include "StdInc.h"
#include "eCrimeType.h"

int& gLastRandomNumberForIdleAnimationID = *reinterpret_cast<int*>(0x8D2FEC);
unsigned int& gLastTouchTimeDelta = *reinterpret_cast<unsigned int*>(0xC19664);
float& gDuckAnimBlendData = *reinterpret_cast<float*>(0x8D2FF0); // 4.0f
bool& gbUnknown_8D2FE8 = *reinterpret_cast<bool*>(0x8D2FE8); // default value true; also always true

void CTaskSimplePlayerOnFoot::InjectHooks()
{
    ReversibleHooks::Install("CTaskSimplePlayerOnFoot", "ProcessPed_Reversed", 0x688810, &CTaskSimplePlayerOnFoot::ProcessPed_Reversed);
    ReversibleHooks::Install("CTaskSimplePlayerOnFoot", "ProcessPlayerWeapon", 0x6859A0, &CTaskSimplePlayerOnFoot::ProcessPlayerWeapon);
    ReversibleHooks::Install("CTaskSimplePlayerOnFoot", "PlayIdleAnimations", 0x6872C0, &CTaskSimplePlayerOnFoot::PlayIdleAnimations);
    ReversibleHooks::Install("CTaskSimplePlayerOnFoot", "PlayerControlZeldaWeapon", 0x687C20, &CTaskSimplePlayerOnFoot::PlayerControlZeldaWeapon);
    ReversibleHooks::Install("CTaskSimplePlayerOnFoot", "PlayerControlDucked", 0x687F30, &CTaskSimplePlayerOnFoot::PlayerControlDucked);
    ReversibleHooks::Install("CTaskSimplePlayerOnFoot", "PlayerControlZelda", 0x6883D0, &CTaskSimplePlayerOnFoot::PlayerControlZelda);
}

// 0x688810
bool CTaskSimplePlayerOnFoot::ProcessPed(class CPed* ped)
{
    return ProcessPed_Reversed(ped);
}

bool CTaskSimplePlayerOnFoot::ProcessPed_Reversed(class CPed* ped)
{
    CPed* pPed = ped;
    CPlayerPed* pPlayerPed = static_cast<CPlayerPed*>(pPed);

    if (pPlayerPed->GetPadFromPlayer())
    {
        CPedIntelligence* pIntelligence = pPlayerPed->m_pIntelligence;
        bool bPedMoving = pPlayerPed->m_nMoveState >= PEDMOVE_WALK;
        if (pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_nType == WEAPON_CHAINSAW
            && pIntelligence->GetTaskFighting()
            && pIntelligence->GetTaskFighting()->m_nCurrentMove == FIGHT_ATTACK_FIGHTIDLE)
        {
            bPedMoving = true;
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
                && !pSimpleTaskUseGun->m_pWeaponInfo->flags.bAimWithArm)
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
        return false;
    }
    else
    {
        m_nFrameCounter = CTimer::m_FrameCounter;
        return false;
    }
}

// 0x685750
CTaskSimplePlayerOnFoot* CTaskSimplePlayerOnFoot::Constructor()
{
    return plugin::CallMethodAndReturn<CTaskSimplePlayerOnFoot*, 0x685750, CTaskSimplePlayerOnFoot*>(this);
}

// 0x68B0C0
CTaskSimplePlayerOnFoot* CTaskSimplePlayerOnFoot::Destructor()
{
    return plugin::CallMethodAndReturn<CTaskSimplePlayerOnFoot*, 0x68B0C0, CTaskSimplePlayerOnFoot*>(this);
}

// 0x6859A0
void CTaskSimplePlayerOnFoot::ProcessPlayerWeapon(CPlayerPed* pPlayerPed)
{
  CPlayerPedData * pPlayerData = pPlayerPed->m_pPlayerData;
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
    pPlayerPed->m_nWeaponAccuracy = pWeaponInfo->flags.bCanAim ? 95 : 100;
    if (pPad->WeaponJustDown(pPlayerPed)
        && (pPlayerPed->m_pTargetedObject || CCamera::m_bUseMouse3rdPerson && pPlayerPed->m_p3rdPersonMouseTarget))
    {
        pPlayerPed->PlayerHasJustAttackedSomeone();
    }
    if (pPlayerPed->m_pFire || !pWeaponInfo->flags.b1stPerson)
    {
        if (!pPad->GetTarget() && weaponType == WEAPON_RLAUNCHER_HS)
        {
            pPlayerData->m_nFireHSMissilePressedTime = 0;
            pPlayerData->m_LastHSMissileTarget = nullptr;
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
                pPlayerData->m_LastHSMissileTarget = nullptr;
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
        int fightCommand = 0;
        gunCommand[0] = 0;

        if (!pPlayerPed->m_pTargetedObject && !pPad->GetTarget() && !pTaskManager->GetTaskSecondary(0))
        {
            if (pPad->MeleeAttackJustDown(false))
            {
                fightCommand = 11;
                gunCommand[0] = 11;
            }

            CAnimBlendAssociation* pAnimAssoc = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, ANIM_ID_KILL_PARTIAL);
            if (pAnimAssoc)
            {
                pAnimAssoc->m_fBlendAmount = -2.0f;
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
                && pPlayerData->m_fMoveBlendRatio < 1.9f
                && pPlayerPed->m_nMoveState != PEDMOVE_SPRINT
                && !pTaskManager->GetTaskSecondary(0)
                && animGroupID != 0
                && CAnimManager::ms_aAnimAssocGroups[animGroupID].m_pAnimBlock
                && CAnimManager::ms_aAnimAssocGroups[animGroupID].m_pAnimBlock->bLoaded
                && pIntelligence->TestForStealthKill(pTargetEntity, false))
            {
                if (pPlayerPed->bIsDucking)
                {
                    CTaskSimpleDuck* pDuckTask = pIntelligence->GetTaskDuck(true);
                    if (pDuckTask && pDuckTask->IsTaskInUseByOtherTasks())
                    {
                        pAnimAssociation = RpAnimBlendClumpGetFirstAssociation(pPlayerPed->m_pRwClump);
                    }
                    else
                    {
                        pAnimAssociation = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, pWeaponInfo->m_dwAnimGroup, ANIM_ID_KILL_PARTIAL, 8.0f);
                    }
                }
                else
                {
                    pAnimAssociation = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, pWeaponInfo->m_dwAnimGroup, ANIM_ID_KILL_PARTIAL, 8.0f);
                }
            }
            else
            {
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, ANIM_ID_KILL_PARTIAL);
                if (pAnimAssociation)
                {
                    pAnimAssociation->m_fBlendAmount = -2.0f;
                }
            }

            bool bCheckButtonCircleStateOnly = false;
            if (pPlayerPed->m_pTargetedObject || pPad->GetTarget())
            {
                bCheckButtonCircleStateOnly = true;
            }
            unsigned char meleeAttackJustDown = pPad->MeleeAttackJustDown(bCheckButtonCircleStateOnly);
            if (meleeAttackJustDown && pAnimAssociation && pAnimAssociation->m_fBlendAmount > 0.5f
                && pTargetEntity && pIntelligence->TestForStealthKill(pTargetEntity, true))
            {
                CTask* pNewTask = static_cast<CTask*>(CTask::operator new(32));
                CTaskSimpleStealthKill* pTaskSimpleStealthKill = nullptr;
                if (pNewTask)
                {
                    pTaskSimpleStealthKill = static_cast<CTaskSimpleStealthKill*>(pNewTask);
                    pTaskSimpleStealthKill->Constructor(true, pTargetEntity, pWeaponInfo->m_dwAnimGroup);
                }

                pTaskManager->SetTask(pTaskSimpleStealthKill, 3, 0);

                eWeaponType activeWeaponType = pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_nType;
                CPedDamageResponseCalculator damageCalculator(pPlayerPed, 0.0, activeWeaponType, PED_PIECE_TORSO, false);
                CEventDamage eventDamage(pPlayerPed, CTimer::m_snTimeInMilliseconds, activeWeaponType, PED_PIECE_TORSO, 0, false, pTargetEntity->bInVehicle);
                if (eventDamage.AffectsPed(pTargetEntity))
                {
                    damageCalculator.ComputeDamageResponse(pTargetEntity, &eventDamage.m_damageResponse, false);
                    pTargetEntity->GetEventGroup().Add(&eventDamage, false);
                    CCrime::ReportCrime(eCrimeType::CRIME_SEALTH_KILL_PED_WITH_KNIFE, pTargetEntity, pPlayerPed);
                    pPlayerPed->m_weaponAudio.AddAudioEvent(AE_WEAPON_STEALTH_KILL);
                }
                pPlayerPed->ClearWeaponTarget();
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
                    if (!CWeaponInfo::GetWeaponInfo(pActiveWeapon->m_nType, 1)->flags.bHeavy)
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
                    if (pPad->GetMeleeAttack(false) && pActiveWeapon->m_nType == WEAPON_CHAINSAW && pTaskManager->GetTaskSecondary(0))
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
    }
    else
    {
        if (pWeaponInfo->m_nWeaponFire == WEAPON_FIRE_USE)
        {
            if (pPad->WeaponJustDown(nullptr))
            {
                unsigned char activeWeaponSlot = pPlayerPed->m_nActiveWeaponSlot;
                weaponType = pPlayerPed->m_aWeapons[activeWeaponSlot].m_nType;
                CWeapon* pPlayerWeapon = &pPlayerPed->m_aWeapons[activeWeaponSlot];
                if (weaponType == WEAPON_DETONATOR)
                {
                    pPlayerWeapon->Fire(pPlayerPed, &pPlayerPed->GetPosition(), &pPlayerPed->GetPosition(), nullptr, nullptr, nullptr);
                }
                else if (weaponType > WEAPON_CAMERA&& weaponType <= WEAPON_INFRARED && !pTaskManager->m_aPrimaryTasks[3])
                {
                    CTaskComplexUseGoggles* pCTaskComplexUseGoggles = nullptr;
                    CTask* pNewTask = static_cast<CTask*>(CTask::operator new(12));
                    if (pNewTask)
                    {
                        pCTaskComplexUseGoggles = static_cast<CTaskComplexUseGoggles*>(pNewTask);
                        pCTaskComplexUseGoggles->Constructor();
                    }

                    pTaskManager->SetTask(pCTaskComplexUseGoggles, 3, 0);
                    pPlayerPed->m_pPlayerData->m_bDontAllowWeaponChange = true;
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
                    pTaskSimpleThrowProjectile->ControlThrow(true, nullptr, nullptr);
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
                                pSecondaryTask->MakeAbortable(pPlayerPed, ABORT_PRIORITY_URGENT, nullptr);
                            }
                        }
                        else
                        {
                            CTask* pNewTask = static_cast<CTask*>(CTask::operator new(60));
                            CTaskSimpleUseGun* pTaskUseGun = nullptr;
                            if (pNewTask)
                            {
                                pTaskUseGun = static_cast<CTaskSimpleUseGun*>(pNewTask);
                                pTaskUseGun->Constructor(pTargetedObject, CVector(0.0f, 0.0f, 0.f), gunCommand[0], 1, false);
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
                                pPlayerData->m_fLookPitch = 0.0f;
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
                                    pTaskSecondary->MakeAbortable(pPlayerPed, ABORT_PRIORITY_URGENT, nullptr);
                                }
                            }
                            else
                            {
                                CTask* pNewTask = static_cast<CTask*>(CTask::operator new(60));
                                CTaskSimpleUseGun* pTaskUseGun = nullptr;
                                if (pNewTask)
                                {
                                    pTaskUseGun = static_cast<CTaskSimpleUseGun*>(pNewTask);
                                    pTaskUseGun->Constructor(pPlayerPed->m_pTargetedObject, CVector(0.0f, 0.0f, 0.0f), gunCommand[0], 1, false);
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
                                    pTaskSecondary->MakeAbortable(pPlayerPed, ABORT_PRIORITY_URGENT, nullptr);
                                }
                                else if (pIntelligence->GetTaskThrow())
                                {
                                    auto pTaskSimpleThrowProjectile = static_cast<CTaskSimpleThrowProjectile*>(pTaskSecondary);
                                    pTaskSimpleThrowProjectile->ControlThrow(pPad->WeaponJustDown(pPlayerPed), nullptr, nullptr);
                                }
                            }
                            else
                            {
                                CTask* pNewTask = static_cast<CTask*>(CTask::operator new(36));
                                CTaskSimpleThrowProjectile* pTaskSimpleThrowProjectile = nullptr;
                                if (pNewTask)
                                {
                                    pTaskSimpleThrowProjectile = static_cast<CTaskSimpleThrowProjectile*>(pNewTask);
                                    pTaskSimpleThrowProjectile->Constructor(nullptr, CVector(0, 0, 0));
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
                            CVector firingPoint(0.0f, 0.0f, 0.6f);
                            CVector outputFiringPoint = *pPlayerPed->m_matrix * firingPoint;
                            pActiveWeapon->Fire(pPlayerPed, &outputFiringPoint, nullptr, nullptr, nullptr, nullptr);
                        }
                        break;
                    }
                    };
                }
            }
        }
    }

PED_WEAPON_AIMING_CODE:

    CVector firingPoint(0.0f, 0.0f, 0.0f);
    CVector upVector(0.0f, 0.0f, 0.0f);


    if (pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_nState == WEAPONSTATE_RELOADING && pWeaponInfo->flags.bReload)
    {
        if (!pIntelligence->GetTaskUseGun())
        {
            int animGroupId = pWeaponInfo->m_dwAnimGroup;
            int crouchReloadAnimID = pWeaponInfo->flags.bReload ? 226 : 0;
            if (!pPlayerPed->bIsDucking)
            {
                if (!RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, crouchReloadAnimID))
                {
                    CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, animGroupId, crouchReloadAnimID, 4.0f);
                }
            }
            else
            {
                auto pDuckTask = (CTaskSimpleDuck*)pIntelligence->GetTaskDuck(true);
                if (pWeaponInfo->GetCrouchReloadAnimationID() && gbUnknown_8D2FE8 && pDuckTask)
                {
                    if (!pDuckTask->IsTaskInUseByOtherTasks())
                    {
                        crouchReloadAnimID = pWeaponInfo->GetCrouchReloadAnimationID();
                        if (!RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, crouchReloadAnimID))
                        {
                            crouchReloadAnimID = pWeaponInfo->GetCrouchReloadAnimationID();
                            CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, animGroupId, crouchReloadAnimID, 4.0f);
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
                pTaskSimpleFight->ControlFight(nullptr, fightCommand);
            }
            if (pIntelligence->GetTaskUseGun())
            {
                if (pPad->GetWeapon(nullptr)
                    || (double)pPad->GetPedWalkUpDown() <= 50.0f
                    && (double)pPad->GetPedWalkUpDown() >= -50.0f
                    && (double)pPad->GetPedWalkLeftRight() <= 50.0f
                    && (double)pPad->GetPedWalkLeftRight() >= -50.0f)
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
                if (!pWeaponInfo->flags.bAimWithArm && pCam->m_nMode == MODE_FOLLOWPED)
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
                firingPoint.Set(0.0f, 0.0f, 0.0f);
                pNewSimpleUseGunTask->Constructor(pPlayerPed->m_pTargetedObject, CVector(0.0, 0.0, 0.0), 1, 1, false);
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
    if (!pWeaponInfo->flags.bCanAim || pPlayerData->m_bFreeAiming)
    {
        if (pPlayerData->m_bFreeAiming && pWeaponInfo->flags.bCanAim
            && (pPad->ShiftTargetLeftJustDown() || pPad->ShiftTargetRightJustDown())
            && !CCamera::m_bUseMouse3rdPerson)
        {
            if (pPlayerPed->m_pTargetedObject)
            {
                if (pPad->ShiftTargetLeftJustDown())
                {
                    pPlayerPed->FindNextWeaponLockOnTarget(pPlayerPed->m_pTargetedObject, true);
                }
                if (pPad->ShiftTargetRightJustDown())
                {
                    pPlayerPed->FindNextWeaponLockOnTarget(pPlayerPed->m_pTargetedObject, false);
                }
            }
            else
            {
                bool shiftTargetLeftJustDown = pPad->ShiftTargetLeftJustDown();
                pPlayerPed->FindNextWeaponLockOnTarget(nullptr, shiftTargetLeftJustDown);
            }
        }
        else if (!pWeaponInfo->flags.bOnlyFreeAim || pPlayerPed->m_pTargetedObject || pPlayerData->m_bFreeAiming)
        {
            if (CCamera::m_bUseMouse3rdPerson && pPlayerData->m_bFreeAiming)
            {
                bool bWeaponIsNotMelee = true;
                if (!pWeaponInfo->m_nWeaponFire)
                {
                    bWeaponIsNotMelee = false;
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
                || pTargetedEntity == (CPed*)nullptr
                || CCamera::m_bUseMouse3rdPerson == 1
                || pTargetedEntity
                && pTargetedEntity->m_nType == ENTITY_TYPE_PED
                && (!CPlayerPed::PedCanBeTargettedVehicleWise(pTargetedEntity)
                    || !CLocalisation::KickingWhenDown()
                    && ((pedState = pTargetedEntity->m_nPedState, pedState == PEDSTATE_DIE) || pedState == PEDSTATE_DEAD))
                || pPlayerPed->DoesTargetHaveToBeBroken(pPlayerPed->m_pTargetedObject, pActiveWeapon)
                || !pPlayerPed->bCanPointGunAtTarget
                && (pActiveWeapon->m_nType, weaponSkill = pPlayerPed->GetWeaponSkill(),
                    !(CWeaponInfo::GetWeaponInfo(pActiveWeapon->m_nType, weaponSkill)->flags.bCanAim))
                )
            {
                pPlayerPed->ClearWeaponTarget();
                pPlayerData->m_bFreeAiming = 1;
            }
            if (pPlayerPed->m_pTargetedObject)
            {
                if (pPad->ShiftTargetLeftJustDown())
                {
                    pPlayerPed->FindNextWeaponLockOnTarget(pPlayerPed->m_pTargetedObject, true);
                }
                if (pPad->ShiftTargetRightJustDown())
                {
                    pPlayerPed->FindNextWeaponLockOnTarget(pPlayerPed->m_pTargetedObject, false);
                }
            }
            if (CWeaponInfo::GetWeaponInfo(pActiveWeapon->m_nType, 1)->m_nWeaponFire == WEAPON_FIRE_INSTANT_HIT)
            {
                pTargetedEntity = (CPed*)pPlayerPed->m_pTargetedObject;
                if (pTargetedEntity && pTargetedEntity->m_nType == ENTITY_TYPE_PED && pIntelligence->IsInSeeingRange(pPlayerPed->GetPosition())) {
                    CTask* pActivePrimaryTask = pIntelligence->GetActivePrimaryTask();
                    if (!pActivePrimaryTask || pActivePrimaryTask->GetId() != TASK_COMPLEX_REACT_TO_GUN_AIMED_AT)
                    {
                        if (pActiveWeapon->m_nType != WEAPON_PISTOL_SILENCED)
                        {
                            pPlayerPed->Say(176, 0, 1.0f, 0, 0, 0);
                        }
                        CPedGroup* pPedGroup = CPedGroups::GetPedsGroup(pTargetedEntity);
                        if (pPedGroup)
                        {
                            if (!CPedGroups::AreInSameGroup(pTargetedEntity, pPlayerPed))
                            {
                                CEventGunAimedAt* pEventGunAimedAt = new CEventGunAimedAt(pPlayerPed);
                                CEventGroupEvent eventGroupEvent(pTargetedEntity, pEventGunAimedAt);
                                pPedGroup->m_groupIntelligence.AddEvent(&eventGroupEvent);
                            }
                        }
                        else
                        {
                            CEventGunAimedAt eventGunAimedAt(pPlayerPed);
                            pIntelligence->m_eventGroup.Add(&eventGunAimedAt, false);
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
    if (pPlayerPed->m_pTargetedObject)
    {
        pTargetedObjectPos = &pPlayerPed->m_pTargetedObject->GetPosition();
    }
    else
    {
        CMatrix* pPlayerMatrix = pPlayerPed->m_matrix;
        firingPoint.x = pPlayerMatrix->GetForward().x;
        firingPoint.y = pPlayerMatrix->GetForward().y;
        firingPoint.z = pPlayerMatrix->GetForward().z;
        firingPoint.x = firingPoint.x * 5.0f;
        firingPoint.y = firingPoint.y * 5.0f;
        firingPoint.z = (sin(pPlayerPed->m_pPlayerData->m_fLookPitch) + firingPoint.z) * 5.0f;
        firingPoint += pPlayerPed->GetPosition();
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
            firingPoint.Set(0.0f, 0.0f, 0.0f);
            pNewSimpleUseGunTask->Constructor(pPlayerPed->m_pTargetedObject, CVector(0.0f, 0.0f, 0.0f), 1, 1, false);
        }
        pTaskManager->SetTaskSecondary(pNewSimpleUseGunTask, 0);
    }

MAKE_PLAYER_LOOK_AT_ENTITY:
    pPlayerData->m_bHaveTargetSelected = pPlayerPed->m_pTargetedObject ? true : false;
    CPed* pTargetedObject = (CPed*)pPlayerPed->m_pTargetedObject;
    bool bTargetedPedDead = false;
    if (!pTargetedObject)
    {
        goto ABORT_LOOKING_IF_POSSIBLE;
    }
    if (pTargetedObject->m_nType == ENTITY_TYPE_PED && (pTargetedObject->bFallenDown || pTargetedObject->m_nPedState == PEDSTATE_DEAD))
    {
        bTargetedPedDead = true;
    }

    CVector distance{};
    if ((pWeaponInfo->m_nWeaponFire || pIntelligence->GetTaskFighting() && !bTargetedPedDead)
        && (pPlayerPed->bIsDucking || !pWeaponInfo->flags.bAimWithArm))
    {
        goto ABORT_LOOKING_IF_POSSIBLE;
    }
    distance = pTargetedObject->GetPosition() - pPlayerPed->GetPosition();
    if (DotProduct(distance, pPlayerPed->GetForwardVector()) <= 0.0f)
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
            nullptr, false, 0.25f, 500, 3, false);
    }

    m_pLookingAtEntity = pTargetedObject;
}

// 0x6872C0
void CTaskSimplePlayerOnFoot::PlayIdleAnimations(CPed* pPed)
{
    CPlayerPed* pPlayerPed = static_cast<CPlayerPed*>(pPed);

    CPad* pPad = pPlayerPed->GetPadFromPlayer();
    if (!CWorld::Players[0].m_pPed || !CWorld::Players[1].m_pPed)
    {
        int animGroupID = 0;
        if (TheCamera.m_bWideScreenOn
            || pPlayerPed->bIsDucking
            || pPlayerPed->bCrouchWhenShooting
            || pPlayerPed->m_pIntelligence->GetTaskHold(false)
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
                CStreaming::SetModelIsDeletable(m_nAnimationBlockIndex + RESOURCE_ID_IFP);
                CAnimBlendAssociation* pAnimAssoc = nullptr;
                for (pAnimAssoc = RpAnimBlendClumpGetFirstAssociation(pPlayerPed->m_pRwClump);
                    pAnimAssoc;
                    pAnimAssoc = RpAnimBlendGetNextAssociation(pAnimAssoc))
                {
                    if (pAnimAssoc->m_nFlags & ANIM_FLAG_200)
                    {
                        pAnimAssoc->m_fBlendDelta = -8.0f;
                    }
                }
            }
            gLastTouchTimeDelta = 0;
        }
        else
        {
            CStreaming::RequestModel(m_nAnimationBlockIndex + RESOURCE_ID_IFP, LOADSTATE_REQUESTED);
            if (pAnimBlock->bLoaded)
            {
                CAnimBlendAssociation* pAnimAssoc1 = RpAnimBlendClumpGetFirstAssociation(pPlayerPed->m_pRwClump);
                if (pAnimAssoc1)
                {
                    while (true)
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
                            ANIM_ID_STRETCH, ANIM_GROUP_PLAYIDLES,
                            ANIM_ID_TIME, ANIM_GROUP_PLAYIDLES,
                            ANIM_ID_SHLDR, ANIM_GROUP_PLAYIDLES,
                            ANIM_ID_STRLEG, ANIM_GROUP_PLAYIDLES
                        };

                        CAnimBlendAssociation* pAnimNewAssoc = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump,
                            groupAndAnimIDs[randomNumber * 2 + 1], groupAndAnimIDs[randomNumber * 2], 8.0f);
                        pAnimNewAssoc->m_nFlags |= ANIM_FLAG_200;
                        gLastTouchTimeDelta = touchTimeDelta;
                        gLastRandomNumberForIdleAnimationID = randomNumber;
                        if (CStats::GetStatValue(STAT_MANAGEMENT_ISSUES_MISSION_ACCOMPLISHED) != 0.0 && CTimer::m_snTimeInMilliseconds > 1200000)
                        {
                            pPlayerPed->Say(336, 0, 0.2f, 0, 0, 0);
                        }
                    }
                }
            }
        }
    }
}

// 0x687530
void CTaskSimplePlayerOnFoot::PlayerControlFighter(CPlayerPed* pPlayerPed)
{
    plugin::CallMethod<0x687530, CTaskSimplePlayerOnFoot*, CPlayerPed*>(this, pPlayerPed);
}

// 0x687C20
void CTaskSimplePlayerOnFoot::PlayerControlZeldaWeapon(CPlayerPed* pPlayerPed)
{
    CTaskSimpleUseGun* pTaskUseGun = pPlayerPed->m_pIntelligence->GetTaskUseGun();
    if (pTaskUseGun)
    {
        if (!pPlayerPed->m_pAttachedTo)
        {
            CVector2D moveSpeed(0.0, 0.0);
            CPad* pPad = pPlayerPed->GetPadFromPlayer();
            float pedWalkUpDown = moveSpeed.y;
            float pedWalkLeftRight = moveSpeed.x;
            if (!pTaskUseGun->m_pWeaponInfo->flags.b1stPerson || CGameLogic::IsPlayerUse2PlayerControls(pPlayerPed))
            {
                pedWalkUpDown = pPad->GetPedWalkUpDown();
                pedWalkLeftRight = pPad->GetPedWalkLeftRight();
            }
            else if (TheCamera.Using1stPersonWeaponMode())
            {
                pedWalkUpDown = pPad->GetPedWalkUpDown(pPlayerPed);
                pedWalkLeftRight = pPad->GetPedWalkLeftRight(pPlayerPed);
            }
            moveSpeed.x = pedWalkLeftRight / 128.0f;
            moveSpeed.y = pedWalkUpDown / 128.0f;
            CEntity* pTargetedObject = pPlayerPed->m_pTargetedObject;
            if (CGameLogic::IsPlayerUse2PlayerControls(pPlayerPed))
            {
                float moveBlendRatio = sqrt(moveSpeed.x * moveSpeed.x + moveSpeed.y * moveSpeed.y);
                if (moveBlendRatio > 0.0f)
                {

                    float radianAngle = CGeneral::GetRadianAngleBetweenPoints(0.0f, 0.0f, -moveSpeed.x, moveSpeed.y)
                        - TheCamera.m_fOrientation;
                    float limitedRadianAngle = CGeneral::LimitRadianAngle(radianAngle);
                    float negativeSinRadian = -sin(limitedRadianAngle);
                    float cosRadian = cos(limitedRadianAngle);
                    if (pTargetedObject)
                    {
                        if (!CGameLogic::IsPlayerAllowedToGoInThisDirection(pPlayerPed, negativeSinRadian, cosRadian, 0.0f, 0.0f))
                        {
                            moveBlendRatio = 0.0f;
                        }
                        CMatrixLink* pPedMatrix = pPlayerPed->m_matrix;
                        moveSpeed.x = (cosRadian * pPedMatrix->GetRight().y + negativeSinRadian * pPedMatrix->GetRight().x + pPedMatrix->GetRight().z * 0.0)
                            * moveBlendRatio;
                        moveSpeed.y = -((cosRadian * pPedMatrix->GetForward().y + negativeSinRadian * pPedMatrix->GetForward().x + pPedMatrix->GetForward().z * 0.0)
                            * moveBlendRatio);
                    }
                    else
                    {
                        pPlayerPed->m_fAimingRotation = limitedRadianAngle;
                        float moveSpeedY = 0.0;
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
                    CVector2D distance = pTargetedObject->GetPosition() - pPlayerPed->GetPosition();
                    pPlayerPed->m_fAimingRotation = atan2(-distance.x, distance.y);
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
}

// 0x687F30
void CTaskSimplePlayerOnFoot::PlayerControlDucked(CPed* pPed)
{
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
            pedMoveBlendRatio = 0.0f;
        }
        else if (pedMoveBlendRatio > 1.0f)
        {
            pedMoveBlendRatio = 1.0f;
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
                    || pPlayerPed->m_pIntelligence->GetTaskUseGun()->m_pWeaponInfo->flags.bAimWithArm)
                {
                    int pedMoveState = PEDMOVE_NONE;
                    if (pPad->GetSprint())
                    {
                        if (pedMoveBlendRatio <= 0.5f)
                        {
                            return;
                        }
                        auto pNewAnimation = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, pPlayerPed->m_nAnimGroup, 1u, gDuckAnimBlendData);
                        pNewAnimation->m_nFlags |= ANIM_FLAG_STARTED;
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
                        pNewAnimation->m_nFlags |= ANIM_FLAG_STARTED;
                        pPlayerPed->m_pPlayerData->m_fMoveBlendRatio = 1.5f;
                        pedMoveState = PEDMOVE_WALK;
                    }
                    pPlayerPed->m_nMoveState = pedMoveState;
                    pPlayerPed->m_nSwimmingMoveState = pedMoveState;
                }
                else if (pedMoveBlendRatio > 0.5f)
                {
                    auto pNewAnimation = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_GUNMOVE_FWD, gDuckAnimBlendData);
                    pNewAnimation->m_nFlags |= ANIM_FLAG_STARTED;
                    pPlayerPed->m_pPlayerData->m_fMoveBlendRatio = 1.0f;
                    moveSpeed.x = 1.0f;
                    moveSpeed.y = 0.0f;
                    CTaskSimpleUseGun* pTaskSimpleUseGun = pPlayerPed->m_pIntelligence->GetTaskUseGun();
                    pTaskSimpleUseGun->ControlGunMove(&moveSpeed);
                }
            }
            else if (!pPad->GetTarget() || pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].IsTypeMelee())
            {
                if (pedMoveBlendRatio > 0.0f)
                {
                    float radianAngle = CGeneral::GetRadianAngleBetweenPoints(0.0f, 0.0f, -moveSpeed.x, moveSpeed.y)
                        - TheCamera.m_fOrientation;
                    float limitedRadianAngle = CGeneral::LimitRadianAngle(radianAngle);
                    pPlayerPed->m_fAimingRotation = limitedRadianAngle;
                    CVector moveDirection(0.0f, -sin(limitedRadianAngle), cos(limitedRadianAngle));
                    if (!CGameLogic::IsPlayerAllowedToGoInThisDirection(pPlayerPed, moveDirection.x, moveDirection.y, 0.0f, 0.0f))
                    {
                        pedMoveBlendRatio = 0.0f;
                    }
                }
                moveSpeed.y = -pedMoveBlendRatio;

                pPlayerPed->m_pPlayerData->m_fMoveBlendRatio = pedMoveBlendRatio;
                moveSpeed.x = 0.0f;
                pSimpleDuckTask->ControlDuckMove(0.0f, moveSpeed.y);
            }
            else
            {
                if (CGameLogic::IsPlayerUse2PlayerControls(pPlayerPed))
                {
                    float radianAngle = CGeneral::GetRadianAngleBetweenPoints(0.0f, 0.0f, -moveSpeed.x, moveSpeed.y) - TheCamera.m_fOrientation;
                    float limitedRadianAngle = CGeneral::LimitRadianAngle(radianAngle);
                    CVector moveDirection(0.0, -sin(limitedRadianAngle), cos(limitedRadianAngle));
                    if (!CGameLogic::IsPlayerAllowedToGoInThisDirection(pPlayerPed, moveDirection.x, moveDirection.y, 0.0f, 0.0f))
                    {
                        pedMoveBlendRatio = 0.0f;
                    }
                    CMatrix* pMatrix = pPlayerPed->m_matrix;
                    CEntity* pTargetedObject = pPlayerPed->m_pTargetedObject;
                    moveSpeed.x = (moveDirection.y * pMatrix->GetRight().y + moveDirection.x * pMatrix->GetRight().x + pMatrix->GetRight().z * 0.0f)
                        * pedMoveBlendRatio;
                    moveSpeed.y = -((moveDirection.y * pMatrix->GetForward().y + pMatrix->GetForward().z * 0.0f + moveDirection.x * pMatrix->GetForward().x)
                        * pedMoveBlendRatio);
                    if (pTargetedObject)
                    {
                        CVector distance = pTargetedObject->GetPosition() - pPlayerPed->GetPosition();
                        pPlayerPed->m_fAimingRotation = atan2(-distance.x, distance.y);
                    }
                    else
                    {
                        pPlayerPed->m_fAimingRotation = limitedRadianAngle;
                    }
                }
                pSimpleDuckTask->ControlDuckMove(moveSpeed.x, moveSpeed.y);
                pPlayerPed->m_pPlayerData->m_fMoveBlendRatio = 0.0f;
            }
        }
    }
}

// 0x6883D0
int CTaskSimplePlayerOnFoot::PlayerControlZelda(CPed* pPed, bool bAvoidJumpingAndDucking)
{
    CPlayerPed* pPlayerPed = static_cast<CPlayerPed*>(pPed);
    CPlayerPedData * pPlayerData = pPed->m_pPlayerData;
    pPlayerData->m_vecFightMovement.x = 0.0;
    pPlayerData->m_vecFightMovement.y = 0.0f;

    CPad* pPad = pPlayerPed->GetPadFromPlayer();
    float pedWalkLeftRight = pPad->GetPedWalkLeftRight();
    float pedWalkUpDown = pPad->GetPedWalkUpDown();
    float pedMoveBlendRatio = sqrt(pedWalkUpDown * pedWalkUpDown + pedWalkLeftRight * pedWalkLeftRight) * 0.016666668f;
    if (pPlayerPed->m_pAttachedTo)
    {
        pedMoveBlendRatio = 0.0f;
    }
    if (pPad->NewState.m_bPedWalk && pedMoveBlendRatio > 1.0f)
    {
        pedMoveBlendRatio = 1.0f;
    }
    else if (pedMoveBlendRatio <= 0.0f)
    {
        pPlayerPed->m_pPlayerData->m_fMoveBlendRatio = 0.0f;
        goto DONT_MODIFY_MOVE_BLEND_RATIO;
    }

    float radianAngle = CGeneral::GetRadianAngleBetweenPoints(0.0f, 0.0f, -pedWalkLeftRight, pedWalkUpDown) - TheCamera.m_fOrientation;
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
    if (!(CWeaponInfo::GetWeaponInfo(pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_nType, 1)->flags.bHeavy))
    {
        if (!pPed->m_standingOnEntity || !pPed->m_standingOnEntity->m_bIsStatic || pPed->m_standingOnEntity->m_bHasContacted)
        {
            if (!pPlayerPed->m_pIntelligence->GetTaskHold(false)
                || !((CTaskSimpleHoldEntity*)pPlayerPed->m_pIntelligence->GetTaskHold(false))->m_pAnimBlendAssociation)
            {
                CAnimBlendHierarchy* pAnimHierarchy = nullptr;
                CAnimBlendAssocGroup* pAnimGroup = &CAnimManager::ms_aAnimAssocGroups[pPlayerPed->m_nAnimGroup];

                if (pPlayerPed->m_pPlayerData->m_bPlayerSprintDisabled
                    || g_surfaceInfos->CantSprintOn(pPlayerPed->m_nContactSurface)
                    || (pAnimHierarchy = pAnimGroup->GetAnimation(1)->m_pHierarchy,
                        pAnimHierarchy == pAnimGroup->GetAnimation(2)->m_pHierarchy))
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

    if (!pPlayerPed->bIsInTheAir && !(CWeaponInfo::GetWeaponInfo(pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_nType, 1)->flags.bHeavy))
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
                            pPlayerPed->m_pIntelligence->m_TaskMgr.SetTask(new CTaskComplexJump(COMPLEX_JUMP_TYPE_JUMP), 3, 0);
                    }
                }
            }
        }
    }

    PlayIdleAnimations(pPlayerPed);
    pPlayerPed->m_pedIK.bSlopePitch = 1;
    return pPlayerPed->m_pedIK.m_nFlags;
}
