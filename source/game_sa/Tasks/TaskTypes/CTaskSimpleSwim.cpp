#include "StdInc.h"

bool &CTaskSimpleSwim::SWIM_DIVE_UNDER_ANGLE = *reinterpret_cast<bool *>(0x8D2FC4);
float &CTaskSimpleSwim::SWIM_STOP_TIME = *reinterpret_cast<float *>(0x8D2FC0);

CTaskSimpleSwim::CTaskSimpleSwim(CVector const* pPosn, CPed* pPed) : CTaskSimple(plugin::dummy)
{
    plugin::CallMethod<0x688930, CTaskSimpleSwim*, CVector const*, CPed*>(this, pPosn, pPed);
}

bool CTaskSimpleSwim::ProcessPed(CPed *pPed)
{
    if (m_pEntity)
    {
        CAnimManager::BlendAnimation(pPed->m_pRwClump, pPed->m_nAnimGroup, DEFAULT_IDLE_STANCE, 8.0);
        pPed->m_nMoveState = PEDMOVE_STILL;
        pPed->field_538 = PEDMOVE_STILL;

        FxSystem_c * pFxSystem = m_pFxSystem;
        if (pFxSystem)
        {
            pFxSystem->Kill();
            m_pFxSystem = 0;
        }
        return true;
    }

    if (m_vecMoveBlendRatio.z > CTaskSimpleSwim::SWIM_STOP_TIME || (pPed->m_nPedFlags & 1))
    {
        CAnimBlendAssociation * pAnimAssociation = nullptr;
        // I still haven't figured out what the hell is animation ID 191
        if (m_AnimID != 191)
        {
            pAnimAssociation = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, m_AnimID);
        }
        unsigned int animId = DEFAULT_IDLE_STANCE;
        pPed->field_538 = PEDMOVE_STILL;
        pPed->m_nMoveState = PEDMOVE_STILL;
        if (pAnimAssociation)
        {
            if (pAnimAssociation->m_nAnimId == DEFAULT_CLIMB_JUMP)
                pAnimAssociation->m_nFlags |= 8u;
            else
                pAnimAssociation->m_fBlendDelta = -4.0;
            if (m_AnimID == SWIM_SWIM_BREAST)
            {
                animId = DEFAULT_WALK_CIVI;
                pPed->field_538 = PEDMOVE_WALK;
                pPed->m_nMoveState = PEDMOVE_WALK;
            }
            else if (m_AnimID == SWIM_SWIM_CRAWL)
            {
                animId = DEFAULT_RUN_CIVI;
                pPed->field_538 = PEDMOVE_RUN;
                pPed->m_nMoveState = PEDMOVE_RUN;
            }
        }
        CAnimManager::BlendAnimation(pPed->m_pRwClump, pPed->m_nAnimGroup, animId, 4.0);
        pPed->RestoreHeadingRate();
        FxSystem_c * pFxSystem = m_pFxSystem;
        if (pFxSystem)
        {
            pFxSystem->Kill();
            m_pFxSystem = 0;
        }
        return true;
    }

    pPed->m_nPedFlags &= 0xFFFFFDFF;

    if (pPed->IsPlayer())
    {
        // m_vecMoveBlendRatio.z seems to remain 0.0f for some reason, so this code seems not to run at all
        // or it might be for cutscenes or mission? but which one? :D
        if (m_vecMoveBlendRatio.z && m_nSwimState != SWIM_UNDERWATER_SPRINTING)
        {
            ProcessControlAI(pPed);
            float fSwimmingTimeStep = static_cast <float>((CTimer::ms_fTimeStep / 50.0) * 1000.0);
            if (m_vecMoveBlendRatio.z <= fSwimmingTimeStep)
            {
                m_vecMoveBlendRatio.z = 0.0f;
            }
            else
            {
                m_vecMoveBlendRatio.z -= fSwimmingTimeStep;
            }

            CVector *pVecPosition = &pPed->m_placement.m_vPosn;
            if (pPed->m_matrix)
            {
                pVecPosition = &pPed->m_matrix->pos;
            }
            CVector pVecOut;
            VectorSub(&pVecOut, &m_vecMoveBlendRatio, pVecPosition);
            pPed->m_pPlayerData->m_fMoveBlendRatio = sqrt(pVecOut.x * pVecOut.x + pVecOut.y * pVecOut.y);
            CPlayerData * pPlayerData = pPed->m_pPlayerData;
            if (pPlayerData->m_fMoveBlendRatio < 0.5)
            {
                pPlayerData->m_fMoveBlendRatio = 0.0;
                CAnimManager::BlendAnimation(pPed->m_pRwClump, pPed->m_nAnimGroup, DEFAULT_IDLE_STANCE, 4.0);
                pPed->RestoreHeadingRate();
                DestroyFxSystem();
                return 1;
            }
            if (pPlayerData->m_fMoveBlendRatio > 1.0)
                pPlayerData->m_fMoveBlendRatio = 1.0;
        }
        else
        {
            ProcessControlInput(reinterpret_cast<CPlayerPed*>(pPed));
            m_vecMoveBlendRatio.z = 0.0f;
        }
        bool bDecreaseAir = false;
        float fDecreaseAirMultiplicator = 1.0;
        if (m_nSwimState == SWIM_UNDERWATER_SPRINTING)
        {
            bDecreaseAir = true;
            CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, SWIM_SWIM_UNDER);
            if (pAnimAssociation)
            {
                fDecreaseAirMultiplicator = pAnimAssociation->m_fSpeed * pAnimAssociation->m_fBlendAmount + 1.0f;
            }
        }

        CPlayerPed * pPlayerPed = reinterpret_cast<CPlayerPed *> (pPed);
        pPlayerPed->HandlePlayerBreath(bDecreaseAir, fDecreaseAirMultiplicator);
        if (m_pPed)
        {
            if (m_nSwimState != SWIM_UNDERWATER_SPRINTING)
            {
                CPlayerData * pPlayerData = pPed->m_pPlayerData;
                if (CStats::GetFatAndMuscleModifier(STAT_MOD_AIR_IN_LUNG) * 0.5f > pPlayerData->m_fBreath)
                    pPed->Say(356, 0, 1.0, 0, 0, 0);
            }
        }
        pPed->SetMoveState(PEDMOVE_NONE);
    }
    else
    {
        ProcessControlAI(pPed);

        // I didn't really get a chance to this this part of code, if someone knows how to make 
        // other peds swim, then let me know because this code will be needed. I did try spawning peds in the
        // sea but they die lol. Looks like this code will run on some missions.
        if (m_nSwimState == SWIM_UNDERWATER_SPRINTING)
        {
            eWeaponType weaponType = static_cast<eWeaponType>(WEAPON_ARMOUR | WEAPON_BASEBALLBAT);

            CPedDamageResponseCalculator pedDamageResponseCalculator;
            pedDamageResponseCalculator.Constructor1(0, CTimer::ms_fTimeStep, weaponType, PED_PIECE_TORSO, false);

            unsigned char pedFlags = (pPed->m_nPedFlags >> 8) & 1;

            CEventDamage eventDamage;
            eventDamage.Constructor1(0, CTimer::m_snTimeInMilliseconds, weaponType, PED_PIECE_TORSO, 0, 0, pedFlags);
            CPedDamageResponse damageResponseInfo;
            if (eventDamage.AffectsPed(pPed))
            {
                pedDamageResponseCalculator.ComputeDamageResponse(pPed, &damageResponseInfo, true);
            }
            else
            {
                damageResponseInfo.bDamageCalculated = true;
            }
            pPed->m_pIntelligence->m_eventGroup.Add(reinterpret_cast <CEvent&>(eventDamage), false);
            eventDamage.Destructor1();
            pedDamageResponseCalculator.Destructor1();
        }
    }
    ProcessSwimAnims(pPed);
    ProcessSwimmingResistance(pPed);
    ProcessEffects(pPed);
    return false;
}

void CTaskSimpleSwim::ProcessSwimAnims(CPed *pPed)
{
    CPlayerPed * pPlayerPed = (CPlayerPed *)pPed;
    CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, DEFAULT_SWIM_TREAD);
    if (m_bFinishedBlending)
    {
        if (pAnimAssociation
            && pAnimAssociation->m_fBlendAmount < 1.0
            && pAnimAssociation->m_fBlendDelta <= 0.0)
        {
            CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_DEFAULT, DEFAULT_SWIM_TREAD, 8.0);
        }
    }
    else
    {
        if (pAnimAssociation
            || (pAnimAssociation = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_DEFAULT, DEFAULT_SWIM_TREAD, 8.0)) != 0)
        {
            if (pAnimAssociation->m_fBlendAmount >= 1.0)
                m_bFinishedBlending = true;
        }
        RpAnimBlendClumpSetBlendDeltas(pPlayerPed->m_pRwClump, 0x10, -8.0);
        FxSystem_c * pFixSystem = pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_pFxSystem;
        if (pFixSystem)
        {
            pFixSystem->Kill();
            pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_pFxSystem = 0;
        }

        if (pPlayerPed->IsPlayer() && !m_nSwimState)
        {
            CMatrixLink * pPlayerMatrix = pPlayerPed->m_matrix;
            CVector * pVecPosition = (pPlayerMatrix ? &pPlayerMatrix->pos : &pPlayerPed->m_placement.m_vPosn);
            float waterLevel = 0.0f;
            if (CWaterLevel::GetWaterLevel(pVecPosition->x, pVecPosition->y, pVecPosition->z, &waterLevel, 1, 0))
            {
                if (waterLevel - 2.0 > pVecPosition->z) // *(pSimpleTransform + 8)) //m_placement
                    m_nSwimState = SWIM_UNDERWATER_SPRINTING;
            }
        }
    }

    if (!m_bAnimBlockRefAdded)
    {
        CAnimBlock * pAnimBlock = CAnimManager::ms_aAnimAssocGroups[ANIM_GROUP_SWIM].m_pAnimBlock;
        if (!pAnimBlock)
        {
            char * pBlockName = CAnimManager::GetAnimBlockName(ANIM_GROUP_SWIM);
            pAnimBlock = CAnimManager::GetAnimationBlock(pBlockName);
        }
        if (pAnimBlock->bLoaded)
        {
            CAnimManager::AddAnimBlockRef(pAnimBlock - CAnimManager::ms_aAnimBlocks);
            m_bAnimBlockRefAdded = true;
        }
        else
        {
            CStreaming::RequestModel(pAnimBlock - CAnimManager::ms_aAnimBlocks + 25575, KEEP_IN_MEMORY);
        }
    }

    if (m_bFinishedBlending && m_bAnimBlockRefAdded)
    {
        switch (m_nSwimState)
        {
        case SWIM_TREAD:
        {
            if (m_AnimID != DEFAULT_SWIM_TREAD)
            {
                CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_BREAST);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -1.0;
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_CRAWL);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -1.0;
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_DIVE_UNDER);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -4.0;
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_UNDER);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -2.0;
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_GLIDE);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -2.0;
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_JUMPOUT);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -4.0;
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, DEFAULT_CLIMB_JUMP);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -4.0;
                m_AnimID = DEFAULT_SWIM_TREAD;
            }
            break;
        }
        case SWIM_SPRINT:
        {
            if (m_AnimID == SWIM_SWIM_BREAST)
            {
                CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_BREAST);
                if (!pAnimAssociation)
                {
                    m_nSwimState = SWIM_TREAD;
                    break;
                }
                if (pPlayerPed->IsPlayer())
                {
                    pAnimAssociation->m_fSpeed = pPlayerPed->m_pPlayerData->m_fMoveBlendRatio;
                }
                else if (m_fAnimSpeed > 0.0 && m_fAnimSpeed <= 1.0)
                {
                    pAnimAssociation->m_fSpeed = m_fAnimSpeed;
                }
            }
            else
            {
                CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_SWIM, SWIM_SWIM_BREAST, 2.0);
                m_AnimID = 311;
            }
            break;
        }
        case SWIM_SPRINTING:
        {
            if (m_AnimID == SWIM_SWIM_CRAWL)
            {
                CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_CRAWL);
                if (!pAnimAssociation)
                {
                    m_nSwimState = SWIM_TREAD;
                    break;
                }
                if (pPlayerPed->m_pPlayerData)
                {
                    float buttonSprintResults = pPlayerPed->GetButtonSprintResults((eSprintType)2);
                    pAnimAssociation->m_fSpeed = static_cast < float > (max(1.0, buttonSprintResults));
                }
                else if (m_fAnimSpeed > 1.0)
                {
                    float taskAnimSpeed = static_cast < float > (m_fAnimSpeed - 1.0);
                    pAnimAssociation->m_fSpeed = static_cast < float > (min(1.5, taskAnimSpeed));
                }
            }
            else
            {
                CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_SWIM, SWIM_SWIM_CRAWL, 2.0);
                m_AnimID = SWIM_SWIM_CRAWL;
            }
            break;
        }
        case SWIM_DIVE_UNDERWATER:
        {
            if (m_AnimID == SWIM_SWIM_DIVE_UNDER)
            {
                CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_DIVE_UNDER);
                if (!pAnimAssociation)
                {
                    m_nSwimState = SWIM_TREAD;
                    break;
                }

                if (pAnimAssociation->m_pHierarchy->m_fTotalTime == pAnimAssociation->m_fCurrentTime)
                    m_nSwimState = SWIM_UNDERWATER_SPRINTING;
            }
            else
            {
                CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_SWIM, SWIM_SWIM_DIVE_UNDER, 8.0);
                m_AnimID = SWIM_SWIM_DIVE_UNDER;
            }
            break;
        }
        case SWIM_UNDERWATER_SPRINTING:
        {
            int animID = m_AnimID;
            if ((animID == SWIM_SWIM_UNDER || animID == SWIM_SWIM_GLIDE) && flt_34 >= 0.0)
            {
                if (pPlayerPed->m_pPlayerData && pPlayerPed->GetButtonSprintResults((eSprintType)3) >= 1.0)
                {
                    CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_UNDER);
                    if (!pAnimAssociation
                        || pAnimAssociation->m_fBlendDelta < 0.0
                        || pAnimAssociation->m_fBlendAmount == 0.0)
                    {
                        pAnimAssociation = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_SWIM, SWIM_SWIM_UNDER, 4.0);
                    }
                    if (pAnimAssociation->m_pHierarchy->m_fTotalTime == pAnimAssociation->m_fCurrentTime)
                    {
                        pAnimAssociation->Start(0.0);
                        float buttonSprintResults = pPlayerPed->GetButtonSprintResults((eSprintType)3);
                        pAnimAssociation->m_fSpeed = static_cast < float > (max(0.69999999, buttonSprintResults));
                    }
                    m_AnimID = SWIM_SWIM_UNDER;
                }
                else
                {
                    CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_GLIDE);
                    if (!pAnimAssociation
                        || pAnimAssociation->m_fBlendDelta < 0.0
                        || pAnimAssociation->m_fBlendAmount == 0.0)
                    {
                        CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_SWIM, SWIM_SWIM_GLIDE, 4.0);
                    }
                    m_AnimID = SWIM_SWIM_GLIDE;
                }
            }
            else
            {
                CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_UNDER);
                if (pAnimAssociation)
                {
                    if (flt_34 < 0.0 && pAnimAssociation->m_fBlendAmount >= 0.99000001)
                    {
                        if (flt_34 > -2.0)
                        {
                            //v28 = flt_8D2FC4;
                            flt_34 = 0;
                            flt_24 = static_cast < float > ((CTaskSimpleSwim::SWIM_DIVE_UNDER_ANGLE * 3.1416) / 180.0); //v28 * 0.017453292;
                        }
                        else
                        {
                            flt_24 = static_cast < float > (1068677315);
                            flt_34 = 0;
                        }
                    }
                }
                else
                {
                    CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_SWIM, SWIM_SWIM_UNDER, 1000.0);
                    int animID = m_AnimID;
                    if (animID == DEFAULT_SWIM_TREAD || animID == 191) // 191? Lmao, this animation id does not even exist
                    {
                        flt_34 = -1073741824;
                        m_AnimID = SWIM_SWIM_UNDER;
                    }
                    else
                    {
                        flt_34 = -1082130432;
                        m_AnimID = SWIM_SWIM_UNDER;
                    }
                }
            }
            break;
        }
        case SWIM_BACK_TO_SURFACE:
        {
            int animID = m_AnimID;
            if (animID == SWIM_SWIM_JUMPOUT)
            {
                CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_JUMPOUT);
                if (pAnimAssociation)
                {
                    if (pAnimAssociation->m_pHierarchy->m_fTotalTime * 0.25 <= pAnimAssociation->m_fTimeStep
                        + pAnimAssociation->m_fCurrentTime)
                    {
                        pAnimAssociation = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_DEFAULT, DEFAULT_CLIMB_JUMP, 8.0);
                        pAnimAssociation->m_nFlags |= 8u;
                        m_AnimID = DEFAULT_CLIMB_JUMP;
                    }
                    break;
                }
            }
            else
            {
                if (animID != DEFAULT_CLIMB_JUMP)
                {
                    CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_SWIM, SWIM_SWIM_JUMPOUT, 8.0);
                    m_AnimID = SWIM_SWIM_JUMPOUT;
                    pPlayerPed->m_vecMoveSpeed.z = static_cast < float > (8.0 / pPlayerPed->m_fMass);
                    CEntity * pEntity = CTaskSimpleClimb::TestForClimb(pPlayerPed, m_pClimbPos, (m_fAngle), (m_nSurfaceType), 1);
                    m_pEntity = pEntity;
                    if (pEntity)
                        pEntity->RegisterReference(&m_pEntity);
                    break;
                }
                if (RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, DEFAULT_CLIMB_JUMP))
                {
                    CMatrixLink * pPlayerMatrix = pPlayerPed->m_matrix;
                    CVector * pVecPosition = (pPlayerMatrix ? &pPlayerMatrix->pos : &pPlayerPed->m_placement.m_vPosn);
                    float waterLevel = 0.0f;
                    if (!CWaterLevel::GetWaterLevel(pVecPosition->x, pVecPosition->y, pVecPosition->z, &waterLevel, 1, 0)
                        || pVecPosition->z + 0.5 >= waterLevel)
                    {
                        break;
                    }
                }
            }
            m_nSwimState = SWIM_TREAD;
            break;
        }
        default:
        {
            break;
        }
        }

        CPlayerData * pPlayerData = pPlayerPed->m_pPlayerData;
        if (pPlayerData && (pPlayerData->m_fMoveBlendRatio > 0.5 || m_nSwimState == SWIM_UNDERWATER_SPRINTING))
            CStats::UpdateStatsWhenSwimming(m_nSwimState == SWIM_UNDERWATER_SPRINTING, m_nSwimState == SWIM_SPRINTING);
        return;

    }
}

void CTaskSimpleSwim::ProcessSwimmingResistance(CPed* pPed)
{
    plugin::CallMethod<0x68A1D0, CTaskSimpleSwim*, CPed*>(this, pPed);
}

void CTaskSimpleSwim::ProcessEffects(CPed* pPed)
{
    plugin::CallMethod<0x68AA70, CTaskSimpleSwim*, CPed*>(this, pPed);
}

void CTaskSimpleSwim::ProcessControlAI(CPed*pPed)
{
    plugin::CallMethod<0x689640, CTaskSimpleSwim*, CPed*>(this, pPed);
}

void CTaskSimpleSwim::ProcessControlInput(CPlayerPed* pPlayerPed)
{
    plugin::CallMethod<0x688A90, CTaskSimpleSwim*, CPlayerPed*>(this, pPlayerPed);
}

FxSystemBP_c * CTaskSimpleSwim::DestroyFxSystem()
{
    return plugin::CallMethodAndReturn<FxSystemBP_c *, 0x68AA50, CTaskSimpleSwim*>(this);
}