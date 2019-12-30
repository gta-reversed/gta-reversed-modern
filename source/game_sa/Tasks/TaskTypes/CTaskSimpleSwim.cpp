#include "StdInc.h"

bool &CTaskSimpleSwim::SWIM_DIVE_UNDER_ANGLE = *reinterpret_cast<bool *>(0x8D2FC4);
float &CTaskSimpleSwim::SWIM_STOP_TIME = *reinterpret_cast<float *>(0x8D2FC0);

CTaskSimpleSwim::CTaskSimpleSwim(CVector const* pPosn, CPed* pPed) : CTaskSimple(plugin::dummy)
{
    plugin::CallMethod<0x688930, CTaskSimpleSwim*, CVector const*, CPed*>(this, pPosn, pPed);
}

bool CTaskSimpleSwim::ProcessPed(CPed *pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x68B1C0, CTaskSimpleSwim*, CPed *>(this, pPed);
#else
    return ProcessPed_Reversed(pPed);
#endif
}

bool CTaskSimpleSwim::ProcessPed_Reversed(CPed* pPed)
{
    if (m_pEntity)
    {
        CAnimManager::BlendAnimation(pPed->m_pRwClump, pPed->m_nAnimGroup, DEFAULT_IDLE_STANCE, 8.0);
        pPed->m_nMoveState = PEDMOVE_STILL;
        pPed->m_nSwimmingMoveState = PEDMOVE_STILL;

        FxSystem_c * pFxSystem = m_pFxSystem;
        if (pFxSystem)
        {
            pFxSystem->Kill();
            m_pFxSystem = 0;
        }
        return true;
    }

    if (m_fSwimStopTime > CTaskSimpleSwim::SWIM_STOP_TIME || pPed->bIsStanding)
    {
        CAnimBlendAssociation * pAnimAssociation = nullptr;
        if (m_AnimID != NO_ANIMATION_SET)
        {
            pAnimAssociation = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, m_AnimID);
        }
        unsigned int animId = DEFAULT_IDLE_STANCE;
        pPed->m_nSwimmingMoveState = PEDMOVE_STILL;
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
                pPed->m_nSwimmingMoveState = PEDMOVE_WALK;
                pPed->m_nMoveState = PEDMOVE_WALK;
            }
            else if (m_AnimID == SWIM_SWIM_CRAWL)
            {
                animId = DEFAULT_RUN_CIVI;
                pPed->m_nSwimmingMoveState = PEDMOVE_RUN;
                pPed->m_nMoveState = PEDMOVE_RUN;
            }
        }
        CAnimManager::BlendAnimation(pPed->m_pRwClump, pPed->m_nAnimGroup, animId, 4.0f);
        pPed->RestoreHeadingRate();
        FxSystem_c * pFxSystem = m_pFxSystem;
        if (pFxSystem)
        {
            pFxSystem->Kill();
            m_pFxSystem = 0;
        }
        return true;
    }
    
    pPed->bIsInTheAir = false;

    if (pPed->IsPlayer())
    {
        if (m_nTimeStep && m_nSwimState != SWIM_UNDERWATER_SPRINTING)
        {
            ProcessControlAI(pPed);
            unsigned int swimmingTimeStep = static_cast<unsigned int>((CTimer::ms_fTimeStep / 50.0f) * 1000.0f);
            if (m_nTimeStep <= swimmingTimeStep)
            {
                m_nTimeStep = 0;
            }
            else
            {
                m_nTimeStep -= swimmingTimeStep;
            }

            CVector vecOut;
            VectorSub(&vecOut, &m_vecPos, &pPed->GetPosition());
            pPed->m_pPlayerData->m_fMoveBlendRatio = vecOut.Magnitude();
            CPlayerData * pPlayerData = pPed->m_pPlayerData;
            if (pPlayerData->m_fMoveBlendRatio < 0.5f)
            {
                pPlayerData->m_fMoveBlendRatio = 0.0f;
                CAnimManager::BlendAnimation(pPed->m_pRwClump, pPed->m_nAnimGroup, DEFAULT_IDLE_STANCE, 4.0f);
                pPed->RestoreHeadingRate();
                DestroyFxSystem();
                return 1;
            }
            if (pPlayerData->m_fMoveBlendRatio > 1.0f)
                pPlayerData->m_fMoveBlendRatio = 1.0f;
        }
        else
        {
            ProcessControlInput(reinterpret_cast<CPlayerPed*>(pPed));
            m_nTimeStep = 0;
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

        if (m_nSwimState == SWIM_UNDERWATER_SPRINTING)
        {
            eWeaponType weaponType = static_cast<eWeaponType>(WEAPON_ARMOUR | WEAPON_BASEBALLBAT);

            CPedDamageResponseCalculator pedDamageResponseCalculator;
            pedDamageResponseCalculator.Constructor1(0, CTimer::ms_fTimeStep, weaponType, PED_PIECE_TORSO, false);

            CEventDamage eventDamage;
            eventDamage.Constructor1(0, CTimer::m_snTimeInMilliseconds, weaponType, PED_PIECE_TORSO, 0, 0, pPed->bInVehicle);
            CPedDamageResponse damageResponseInfo;
            if (eventDamage.AffectsPed(pPed))
            {
                pedDamageResponseCalculator.ComputeDamageResponse(pPed, &damageResponseInfo, true);
            }
            else
            {
                damageResponseInfo.bDamageCalculated = true;
            }
            pPed->m_pIntelligence->m_eventGroup.Add((CEvent*)&eventDamage, false);
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
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x6899F0, CTaskSimpleSwim*, CPed *>(this, pPed);
#else
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
                    pAnimAssociation->m_fSpeed = static_cast < float > (std::max(1.0f, buttonSprintResults));
                }
                else if (m_fAnimSpeed > 1.0)
                {
                    float taskAnimSpeed = static_cast < float > (m_fAnimSpeed - 1.0);
                    pAnimAssociation->m_fSpeed = static_cast < float > (std::min(1.5f, taskAnimSpeed));
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
            if ((animID == SWIM_SWIM_UNDER || animID == SWIM_SWIM_GLIDE) && m_fStateChanger >= 0.0)
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
                        pAnimAssociation->m_fSpeed = static_cast < float > (std::max(0.69999999f, buttonSprintResults));
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
                    if (m_fStateChanger < 0.0 && pAnimAssociation->m_fBlendAmount >= 0.99000001)
                    {
                        if (m_fStateChanger > -2.0)
                        {
                            m_fStateChanger = 0.0f;
                            m_fRotationX = static_cast < float > ((CTaskSimpleSwim::SWIM_DIVE_UNDER_ANGLE * 3.1416) / 180.0); //v28 * 0.017453292;
                        }
                        else
                        {
                            m_fRotationX = static_cast < float > (1.39626f);
                            m_fStateChanger = 0.0f;
                        }
                    }
                }
                else
                {
                    CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_SWIM, SWIM_SWIM_UNDER, 1000.0);
                    int animID = m_AnimID;
                    if (animID == DEFAULT_SWIM_TREAD || animID == NO_ANIMATION_SET)
                    {
                        m_fStateChanger = -2.0f;
                        m_AnimID = SWIM_SWIM_UNDER;
                    }
                    else
                    {
                        m_fStateChanger = -1.0f;
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
#endif
}

void CTaskSimpleSwim::ProcessSwimmingResistance(CPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x68A1D0, CTaskSimpleSwim*, CPed*>(this, pPed);
#else
    float fSubmergeZ = -1.0f;
    CVector vecPedMoveSpeed;

    switch (m_nSwimState)
    {
    case SWIM_TREAD:
    case SWIM_SPRINT:
    case SWIM_SPRINTING:
    {
        CAnimBlendAssociation* pAnimSwimBreast = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, SWIM_SWIM_BREAST);
        CAnimBlendAssociation* pAnimSwimCrawl = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, SWIM_SWIM_CRAWL);

        float fAnimBlendSum = 0.0f;
        float fAnimBlendDifference = 1.0f;
        if (pAnimSwimBreast)
        {
            fAnimBlendSum = 0.40000001f * pAnimSwimBreast->m_fBlendAmount;
            fAnimBlendDifference = 1.0f - pAnimSwimBreast->m_fBlendAmount;
        }

        if (pAnimSwimCrawl)
        {
            fAnimBlendSum += 0.2f * pAnimSwimCrawl->m_fBlendAmount;
            fAnimBlendDifference -= pAnimSwimCrawl->m_fBlendAmount;
        }

        if (fAnimBlendDifference < 0.0f)
        {
            fAnimBlendDifference = 0.0f;
        }

        fSubmergeZ = fAnimBlendDifference * 0.55000001f + fAnimBlendSum;

        vecPedMoveSpeed = pPed->m_vecAnimMovingShiftLocal.x * pPed->m_matrix->right;
        vecPedMoveSpeed += pPed->m_vecAnimMovingShiftLocal.y * pPed->m_matrix->up;
        break;
    }
    case SWIM_DIVE_UNDERWATER:
    {
        vecPedMoveSpeed = pPed->m_vecAnimMovingShiftLocal.x * pPed->m_matrix->right;
        vecPedMoveSpeed += pPed->m_vecAnimMovingShiftLocal.y * pPed->m_matrix->up;

        auto pAnimSwimDiveUnder = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, SWIM_SWIM_DIVE_UNDER);
        if (pAnimSwimDiveUnder)
        {
            vecPedMoveSpeed.z = pAnimSwimDiveUnder->m_fCurrentTime / pAnimSwimDiveUnder->m_pHierarchy->m_fTotalTime * -0.1f;
        }
        break;
    }
    case SWIM_UNDERWATER_SPRINTING:
    {
        vecPedMoveSpeed = pPed->m_vecAnimMovingShiftLocal.x * pPed->m_matrix->right;
        vecPedMoveSpeed += cos(m_fRotationX) * pPed->m_vecAnimMovingShiftLocal.y * pPed->m_matrix->up;
        vecPedMoveSpeed.z += sin(m_fRotationX) * pPed->m_vecAnimMovingShiftLocal.y + 0.0099999998f;
        break;
    }
    case SWIM_BACK_TO_SURFACE:
    {
        auto pAnimAssociation = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, 128);
        if (!pAnimAssociation)
        {
            pAnimAssociation = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, SWIM_SWIM_JUMPOUT);
        }

        if (pAnimAssociation)
        {
            if (pAnimAssociation->m_pHierarchy->m_fTotalTime > pAnimAssociation->m_fCurrentTime
                && (pAnimAssociation->m_fBlendAmount >= 1.0f || pAnimAssociation->m_fBlendDelta > 0.0f))
            {
                float fMoveForceZ = CTimer::ms_fTimeStep * pPed->m_fMass * 0.30000001f * 0.0080000004f;
                pPed->ApplyMoveForce(0.0f, 0.0f, fMoveForceZ);
            }
        }
        return;
    }
    default:
    {
        return;
    }
    }

    float fTheTimeStep = pow(0.89999998f, CTimer::ms_fTimeStep);
    vecPedMoveSpeed *= (1.0f - fTheTimeStep);
    pPed->m_vecMoveSpeed *= fTheTimeStep;
    pPed->m_vecMoveSpeed += vecPedMoveSpeed;

    bool bUpdateRotationX = true;
    const CVector& vecPedPosition = pPed->GetPosition();
    CVector vecCheckWaterLevelPos = CTimer::ms_fTimeStep * pPed->m_vecMoveSpeed + pPed->GetPosition();
    float fWaterLevel = 0.0;
    if (!CWaterLevel::GetWaterLevel(vecCheckWaterLevelPos.x, vecCheckWaterLevelPos.y, vecPedPosition.z, &fWaterLevel, true, 0))
    {
        fSubmergeZ = -1.0f;
        bUpdateRotationX = false;
    }
    else
    {
        if (m_nSwimState != SWIM_UNDERWATER_SPRINTING || m_fStateChanger < 0.0)
        {
            bUpdateRotationX = false;
        }
        else
        {
            if (vecPedPosition.z + 0.64999998f > fWaterLevel && m_fRotationX > 0.78539819f)
            {
                m_nSwimState = SWIM_TREAD;
                m_fStateChanger = 0.0;
                bUpdateRotationX = false;
            }
        }
    }

    if (bUpdateRotationX)
    {
        if (m_fRotationX >= 0.0)
        {
            if (vecPedPosition.z + 0.64999998f <= fWaterLevel)
            {
                if (m_fStateChanger <= 0.001f)
                {
                    m_fStateChanger = 0.0;
                }
                else
                {
                    m_fStateChanger *= 0.94999999f;
                }
            }
            else
            {
                float fMinimumSpeed = 0.050000001f * 0.5f;
                if (m_fStateChanger > fMinimumSpeed)
                {
                    m_fStateChanger *= 0.94999999f;
                }
                if (m_fStateChanger < fMinimumSpeed)
                {
                    m_fStateChanger += CTimer::ms_fTimeStep * 0.0020000001f;
                    m_fStateChanger = std::min(fMinimumSpeed, m_fStateChanger);
                }
                m_fRotationX += CTimer::ms_fTimeStep * m_fStateChanger;
                fSubmergeZ = (0.55000001f - 0.2f) * (m_fRotationX * 1.2732395f) * 0.75f + 0.2f;
            }
        }
        else
        {
            if (vecPedPosition.z - sin(m_fRotationX) + 0.64999998f <= fWaterLevel)
            {
                if (m_fStateChanger > 0.001f)
                {
                    m_fStateChanger *= 0.94999999f;
                }
                else
                {
                    m_fStateChanger = 0.0;
                }
            }
            else
            {
                m_fStateChanger += CTimer::ms_fTimeStep * 0.0020000001f;
                if (m_fStateChanger > 0.050000001f)
                {
                    m_fStateChanger = 0.050000001f;
                }
            }
            m_fRotationX += CTimer::ms_fTimeStep * m_fStateChanger;
        }
    }

    if (fSubmergeZ > 0.0)
    {
        fWaterLevel -= (fSubmergeZ + vecPedPosition.z);
        float fTimeStepMoveSpeedZ = fWaterLevel / CTimer::ms_fTimeStep;
        float fTimeStep = CTimer::ms_fTimeStep * 0.1f;
        if (fTimeStepMoveSpeedZ > fTimeStep)
        {
            fTimeStepMoveSpeedZ = fTimeStep;
        }

        if (-fTimeStep > fTimeStepMoveSpeedZ)
        {
            fTimeStepMoveSpeedZ = -fTimeStep;
        }

        fTimeStepMoveSpeedZ -= pPed->m_vecMoveSpeed.z;

        fTimeStep = CTimer::ms_fTimeStep * 0.02f;
        if (fTimeStepMoveSpeedZ > fTimeStep)
        {
            fTimeStepMoveSpeedZ = fTimeStep;
        }

        if (-fTimeStep > fTimeStepMoveSpeedZ)
        {
            fTimeStepMoveSpeedZ = -fTimeStep;
        }

        pPed->m_vecMoveSpeed.z += fTimeStepMoveSpeedZ;
    }

    CVector* pPedPosition = &pPed->GetPosition();
    if (pPedPosition->z < -69.0f)
    {
        pPedPosition->z = -69.0f;
        if (pPed->m_vecMoveSpeed.z < 0.0f)
        {
            pPed->m_vecMoveSpeed.z = 0.0f;
        }
    }
    return;
#endif
}

void CTaskSimpleSwim::ProcessEffects(CPed* pPed)
{
    plugin::CallMethod<0x68AA70, CTaskSimpleSwim*, CPed*>(this, pPed);
}

void CTaskSimpleSwim::ProcessControlAI(CPed*pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x689640, CTaskSimpleSwim*, CPed*>(this, pPed);
#else
    m_nSwimState = SWIM_TREAD;
    if (m_pPed)
    {
        CVector vecPosition(m_pPed->GetPosition() - pPed->GetPosition());
        vecPosition.Normalise();
        if (m_fRandomMoveBlendRatio == 0.0f)
        {
            m_fRandomMoveBlendRatio = (rand() & 3) * 0.5f + 1.5f;
        }

        vecPosition *= m_fRandomMoveBlendRatio;
        m_vecPos = m_pPed->GetPosition() - vecPosition;
    }

    bool bPedGroupSet = false;
    if (m_vecPos.x != 0.0 || m_vecPos.y != 0.0 || m_vecPos.z != 0.0)
    {
        CVector vecPosition(m_vecPos - pPed->GetPosition());
        pPed->m_fAimingRotation = atan2(-vecPosition.x, vecPosition.y);

        float fMinimum2DDistanceBetweenPeds = 1.0f;
        if (pPed->IsPlayer())
        {
            fMinimum2DDistanceBetweenPeds = 0.5f;
        }

        if (vecPosition.Magnitude2D() > fMinimum2DDistanceBetweenPeds)
        {
            m_nSwimState = SWIM_SPRINT;
            if (m_pPed)
            {
                CPedGroup* pPedGroup = CPedGroups::GetPedsGroup(pPed);
                if (pPedGroup && pPedGroup->m_groupMembership.GetLeader() == m_pPed)
                {
                    bPedGroupSet = true;
                    auto pSwimTask = m_pPed->m_pIntelligence->GetTaskSwim();
                    if (pSwimTask && pSwimTask->m_nSwimState == SWIM_SPRINTING)
                    {
                        CVector out;
                        CVector* pVecSub = VectorSub(&out, &m_vecPos, &pPed->GetPosition());
                        if (pVecSub->Magnitude() > 5.0f)
                        {
                            m_nSwimState = SWIM_SPRINTING;
                        }
                    }
                }
            }
            else if (m_fAnimSpeed > 1.0f)
            {
                if (vecPosition.Magnitude2D() > 2.0f)
                {
                    m_nSwimState = SWIM_SPRINTING;
                }
            }
        }
    }

    CVector vecPosition(m_vecPos - pPed->GetPosition());
    if (m_pPed && m_pPed->bIsStanding && !m_pPed->physicalFlags.bSubmergedInWater
        || pPed->bIsDyingStuck && !m_pPed->physicalFlags.bSubmergedInWater
        && vecPosition.Magnitude2D() < 1.0f)
    {
        if (!((pPed->m_nRandomSeedUpperByte + CTimer::m_FrameCounter - 4) & 0x7F))
        {
            if (CTaskSimpleClimb::TestForClimb(pPed, m_pClimbPos, m_fAngle, m_nSurfaceType, true))
            {
                m_nSwimState = SWIM_BACK_TO_SURFACE;
            }
        }
    }
    m_fAimingRotation = 0.0;
    m_fUpperTorsoRotationX = 0.0;

    if (!bPedGroupSet && !pPed->IsPlayer() && m_fAnimSpeed < 0.0f)
    {
        pPed->m_vecAnimMovingShiftLocal *= 0.5f;
    }
#endif
}

void CTaskSimpleSwim::ProcessControlInput(CPlayerPed* pPlayerPed)
{
    plugin::CallMethod<0x688A90, CTaskSimpleSwim*, CPlayerPed*>(this, pPlayerPed);
}

FxSystemBP_c * CTaskSimpleSwim::DestroyFxSystem()
{
    return plugin::CallMethodAndReturn<FxSystemBP_c *, 0x68AA50, CTaskSimpleSwim*>(this);
}