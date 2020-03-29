#include "StdInc.h"

bool& CTaskSimpleSwim::SWIM_DIVE_UNDER_ANGLE = *reinterpret_cast<bool*>(0x8D2FC4);
float& CTaskSimpleSwim::SWIM_STOP_TIME = *reinterpret_cast<float*>(0x8D2FC0);

void CTaskSimpleSwim::InjectHooks()
{
    HookInstall(0x68B1C0, &CTaskSimpleSwim::ProcessPed_Reversed, 7);
    HookInstall(0x68B100, &CTaskSimpleSwim::MakeAbortable_Reversed, 7);
    HookInstall(0x68A8E0, &CTaskSimpleSwim::ApplyRollAndPitch, 7);
    HookInstall(0x6899F0, &CTaskSimpleSwim::ProcessSwimAnims, 7);
    HookInstall(0x68A1D0, &CTaskSimpleSwim::ProcessSwimmingResistance, 7);
    HookInstall(0x68AA70, &CTaskSimpleSwim::ProcessEffects, 7);
    HookInstall(0x689640, &CTaskSimpleSwim::ProcessControlAI, 7);
    HookInstall(0x688A90, &CTaskSimpleSwim::ProcessControlInput, 7);
    HookInstall(0x68A9F0, &CTaskSimpleSwim::CreateFxSystem, 7);
    HookInstall(0x68AA50, &CTaskSimpleSwim::DestroyFxSystem, 7);
}

CTaskSimpleSwim::CTaskSimpleSwim(CVector const* pPosn, CPed* pPed) : CTaskSimple(plugin::dummy)
{
    plugin::CallMethod<0x688930, CTaskSimpleSwim*, CVector const*, CPed*>(this, pPosn, pPed);
}

bool CTaskSimpleSwim::MakeAbortable(class CPed* ped, eAbortPriority priority, class CEvent* _event)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CTask*, CPed*, int, class CEvent*))plugin::GetVMT(this, 6))(this, ped, priority, _event);
#else
    return MakeAbortable_Reversed(ped, priority, _event);
#endif
}

bool CTaskSimpleSwim::ProcessPed(CPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x68B1C0, CTaskSimpleSwim*, CPed*>(this, pPed);
#else
    return ProcessPed_Reversed(pPed);
#endif
}

bool CTaskSimpleSwim::MakeAbortable_Reversed(class CPed* ped, eAbortPriority priority, class CEvent* _event)
{
    CEventDamage* pDamageEvent = reinterpret_cast<CEventDamage*>(_event);

    if (priority == ABORT_PRIORITY_IMMEDIATE)
    {
        CAnimManager::BlendAnimation(ped->m_pRwClump, ped->m_nAnimGroup, ANIMATION_STARTED | ANIMATION_LOOPED, 1000.0f);
        ped->m_nMoveState = PEDMOVE_STILL;
        ped->m_nSwimmingMoveState = PEDMOVE_STILL;

        if (m_AnimID != NO_ANIMATION_SET)
        {
            auto pAnimAssociation = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, m_AnimID);
            if (pAnimAssociation)
            {
                pAnimAssociation->m_fBlendDelta = -1000.0f;
            }
        }

        ped->RestoreHeadingRate();
    }
    else if (!_event || _event->GetEventPriority() < 71
        && (_event->GetEventType() != EVENT_DAMAGE || !pDamageEvent->damageResponseData.bUnk || !pDamageEvent->unkC))
    {
        return false;
    }

    if (m_pFxSystem)
    {
        m_pFxSystem->Kill();
        m_pFxSystem = 0;
    }
    return true;
}

bool CTaskSimpleSwim::ProcessPed_Reversed(CPed* pPed)
{
    if (m_pEntity)
    {
        CAnimManager::BlendAnimation(pPed->m_pRwClump, pPed->m_nAnimGroup, DEFAULT_IDLE_STANCE, 8.0);
        pPed->m_nMoveState = PEDMOVE_STILL;
        pPed->m_nSwimmingMoveState = PEDMOVE_STILL;

        FxSystem_c* pFxSystem = m_pFxSystem;
        if (pFxSystem)
        {
            pFxSystem->Kill();
            m_pFxSystem = 0;
        }
        return true;
    }

    if (m_fSwimStopTime > CTaskSimpleSwim::SWIM_STOP_TIME || pPed->bIsStanding)
    {
        CAnimBlendAssociation* pAnimAssociation = nullptr;
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
        FxSystem_c* pFxSystem = m_pFxSystem;
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
            CPlayerData* pPlayerData = pPed->m_pPlayerData;
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
            CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, SWIM_SWIM_UNDER);
            if (pAnimAssociation)
            {
                fDecreaseAirMultiplicator = pAnimAssociation->m_fSpeed * pAnimAssociation->m_fBlendAmount + 1.0f;
            }
        }

        CPlayerPed* pPlayerPed = reinterpret_cast<CPlayerPed*> (pPed);
        pPlayerPed->HandlePlayerBreath(bDecreaseAir, fDecreaseAirMultiplicator);
        if (m_pPed)
        {
            if (m_nSwimState != SWIM_UNDERWATER_SPRINTING)
            {
                CPlayerData* pPlayerData = pPed->m_pPlayerData;
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
            pPed->m_pIntelligence->m_eventGroup.Add((CEvent*)& eventDamage, false);
            eventDamage.Destructor1();
            pedDamageResponseCalculator.Destructor1();
        }
    }
    ProcessSwimAnims(pPed);
    ProcessSwimmingResistance(pPed);
    ProcessEffects(pPed);
    return false;
}

void CTaskSimpleSwim::ApplyRollAndPitch(CPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x68A8E0, CTaskSimpleSwim*, CPed*>(this, pPed);
#else
    CMatrix rotationMatrix;
    CMatrix outMatrix;

    LimbOrientation theLimbOrientation;
    theLimbOrientation.m_fYaw = m_fAimingRotation;
    theLimbOrientation.m_fPitch = m_fUpperTorsoRotationX;

    pPed->m_pedIK.RotateTorso(pPed->m_apBones[1], theLimbOrientation, false);

    RwObject* pRwObject = pPed->m_pRwObject;
    if (pRwObject)
    {
        RwMatrix* pRwMatrix = &((RwFrame*)pRwObject->parent)->modelling;
        CMatrix pedMatrix(pRwMatrix, 0);
        rotationMatrix.m_pAttachMatrix = 0;
        rotationMatrix.m_bOwnsAttachedMatrix = 0;

        rotationMatrix.SetTranslate(CVector(0.0f, 0.0f, 0.0f));
        rotationMatrix.RotateY(m_fTurningRotationY);
        rotationMatrix.RotateX(m_fRotationX);

        pedMatrix *= rotationMatrix;
        pedMatrix.UpdateRW();
        pPed->UpdateRwFrame();
    }
#endif
}

void CTaskSimpleSwim::ProcessSwimAnims(CPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x6899F0, CTaskSimpleSwim*, CPed*>(this, pPed);
#else
    CPlayerPed* pPlayerPed = (CPlayerPed*)pPed;
    CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, DEFAULT_SWIM_TREAD);
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
        FxSystem_c* pFixSystem = pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_pFxSystem;
        if (pFixSystem)
        {
            pFixSystem->Kill();
            pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_pFxSystem = 0;
        }

        if (pPlayerPed->IsPlayer() && !m_nSwimState)
        {
            CMatrixLink* pPlayerMatrix = pPlayerPed->m_matrix;
            CVector* pVecPosition = (pPlayerMatrix ? &pPlayerMatrix->pos : &pPlayerPed->m_placement.m_vPosn);
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
        CAnimBlock* pAnimBlock = CAnimManager::ms_aAnimAssocGroups[ANIM_GROUP_SWIM].m_pAnimBlock;
        if (!pAnimBlock)
        {
            char* pBlockName = CAnimManager::GetAnimBlockName(ANIM_GROUP_SWIM);
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
                CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_BREAST);
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
                CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_BREAST);
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
                CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_CRAWL);
                if (!pAnimAssociation)
                {
                    m_nSwimState = SWIM_TREAD;
                    break;
                }
                if (pPlayerPed->m_pPlayerData)
                {
                    float buttonSprintResults = pPlayerPed->GetButtonSprintResults((eSprintType)2);
                    pAnimAssociation->m_fSpeed = static_cast <float> (std::max(1.0f, buttonSprintResults));
                }
                else if (m_fAnimSpeed > 1.0)
                {
                    float taskAnimSpeed = static_cast <float> (m_fAnimSpeed - 1.0);
                    pAnimAssociation->m_fSpeed = static_cast <float> (std::min(1.5f, taskAnimSpeed));
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
                CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_DIVE_UNDER);
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
                    CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_UNDER);
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
                        pAnimAssociation->m_fSpeed = static_cast <float> (std::max(0.69999999f, buttonSprintResults));
                    }
                    m_AnimID = SWIM_SWIM_UNDER;
                }
                else
                {
                    CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_GLIDE);
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
                CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_UNDER);
                if (pAnimAssociation)
                {
                    if (m_fStateChanger < 0.0 && pAnimAssociation->m_fBlendAmount >= 0.99000001)
                    {
                        if (m_fStateChanger > -2.0)
                        {
                            m_fStateChanger = 0.0f;
                            m_fRotationX = static_cast <float> ((CTaskSimpleSwim::SWIM_DIVE_UNDER_ANGLE * 3.1416) / 180.0); //v28 * 0.017453292;
                        }
                        else
                        {
                            m_fRotationX = static_cast <float> (1.39626f);
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
                CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, SWIM_SWIM_JUMPOUT);
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
                    pPlayerPed->m_vecMoveSpeed.z = static_cast <float> (8.0 / pPlayerPed->m_fMass);
                    CEntity* pEntity = CTaskSimpleClimb::TestForClimb(pPlayerPed, m_pClimbPos, (m_fAngle), (m_nSurfaceType), 1);
                    m_pEntity = pEntity;
                    if (pEntity)
                        pEntity->RegisterReference(&m_pEntity);
                    break;
                }
                if (RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, DEFAULT_CLIMB_JUMP))
                {
                    CMatrixLink* pPlayerMatrix = pPlayerPed->m_matrix;
                    CVector* pVecPosition = (pPlayerMatrix ? &pPlayerMatrix->pos : &pPlayerPed->m_placement.m_vPosn);
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

        CPlayerData* pPlayerData = pPlayerPed->m_pPlayerData;
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
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x68AA70, CTaskSimpleSwim*, CPed*>(this, pPed);
#else
    CVector vecParticlePosition;
    if (pPed->m_matrix)
    {
        vecParticlePosition = pPed->m_matrix->up;
    }
    else
    {
        float fHeading = pPed->m_placement.m_fHeading;
        vecParticlePosition.x = -sin(fHeading);
        vecParticlePosition.y = cos(fHeading);
        vecParticlePosition.z = 0.0f;
    }

    vecParticlePosition *= 0.40000001f;
    vecParticlePosition += pPed->GetPosition();

    CPlayerData* pPlayerData = pPed->m_pPlayerData;

    if (pPlayerData)
    {
        vecParticlePosition.z = pPlayerData->m_fWaterHeight;
    }
    else
    {
        vecParticlePosition.z += 0.5f;
    }

    if (m_nSwimState != SWIM_TREAD)
    {
        if (m_pFxSystem)
        {
            m_pFxSystem->Kill();
            m_pFxSystem = 0;
        }
    }
    else
    {
        RwMatrix* pNewMatrix = RwMatrixCreate();
        pNewMatrix->pos = *((RwV3d*)& vecParticlePosition);
        RwMatrixUpdate(pNewMatrix);
        if (!m_pFxSystem)
        {
            CreateFxSystem(pPed, pNewMatrix);
        }

        if (m_pFxSystem)
        {
            m_pFxSystem->SetMatrix(pNewMatrix);
            m_pFxSystem->SetLocalParticles(1);
        }
        RwMatrixDestroy(pNewMatrix);
    }

    if (m_nSwimState != SWIM_DIVE_UNDERWATER)
    {
        m_bTriggerWaterSplash = false;
    }

    switch (m_nSwimState)
    {
    case SWIM_SPRINT:
    case SWIM_SPRINTING:
    {
        const CVector& vecPedUp = pPed->m_matrix->up;

        float fRadianAngle = CGeneral::GetAngleBetweenPoints(vecPedUp.x, vecPedUp.y, 0.0f, 0.0f);
        float fLimitedRadianAngle = CGeneral::LimitAngle(fRadianAngle) + 180.0f;

        FxPrtMult_c fxPrtMult(1.0f, 1.0f, 1.0f, 0.2f, 0.40000001f, 0.0f, 0.5f);
        CVector vecParticleVelocity;
        g_fx.m_pPrtWake->AddParticle((RwV3d*)& vecParticlePosition, (RwV3d*)& vecParticleVelocity, 0.0f, (FxPrtMult_c*)& fxPrtMult, fLimitedRadianAngle, 1.2f, 0.60000002f, 0);
        pPed->m_pedAudio.AddAudioEvent(76, 0.0, 1.0f, 0, 0, 0, 0);

        if (m_nSwimState == SWIM_SPRINTING)
        {
            RpHAnimHierarchy* pAnimHierarchy = GetAnimHierarchyFromSkinClump(pPed->m_pRwClump);
            int boneRHandIndex = RpHAnimIDGetIndex(pAnimHierarchy, BONE_R_HAND);
            RwV3d* pBoneRHandPos = &RpHAnimHierarchyGetMatrixArray(pAnimHierarchy)[boneRHandIndex].pos;
            int boneLHandIndex = RpHAnimIDGetIndex(pAnimHierarchy, BONE_L_HAND);
            RwV3d* pBoneLHandPos = &RpHAnimHierarchyGetMatrixArray(pAnimHierarchy)[boneLHandIndex].pos;
            int boneRFootIndex = RpHAnimIDGetIndex(pAnimHierarchy, BONE_R_FOOT);
            RwV3d* pBoneRFootPos = &RpHAnimHierarchyGetMatrixArray(pAnimHierarchy)[boneRFootIndex].pos;
            int boneLFootIndex = RpHAnimIDGetIndex(pAnimHierarchy, BONE_L_FOOT);
            RwV3d* pBoneLFootPos = &RpHAnimHierarchyGetMatrixArray(pAnimHierarchy)[boneLFootIndex].pos;

            float fPedPosZ = pPed->GetPosition().z;
            if (fabs(pBoneRHandPos->z - fPedPosZ) < 0.050000001f)
            {
                auto pFxSystem = g_fxMan.CreateFxSystem("water_swim", pBoneRHandPos, 0, 0);
                if (pFxSystem)
                {
                    pFxSystem->PlayAndKill();
                    pPed->m_pedAudio.AddAudioEvent(74, 0.0, 1.0f, 0, 0, 0, 0);
                }
            }

            if (fabs(pBoneLHandPos->z - fPedPosZ) < 0.050000001f)
            {
                auto pFxSystem = g_fxMan.CreateFxSystem("water_swim", pBoneLHandPos, 0, 0);
                if (pFxSystem)
                {
                    pFxSystem->PlayAndKill();
                    pPed->m_pedAudio.AddAudioEvent(74, 0.0, 1.0f, 0, 0, 0, 0);
                }
            }
            if (fabs(pBoneRFootPos->z - fPedPosZ) < 0.050000001f)
            {
                auto pFxSystem = g_fxMan.CreateFxSystem("water_swim", pBoneRFootPos, 0, 0);
                if (pFxSystem)
                {
                    pFxSystem->PlayAndKill();
                    pPed->m_pedAudio.AddAudioEvent(74, 0.0, 1.0f, 0, 0, 0, 0);
                }
            }
            if (fabs(pBoneLFootPos->z - fPedPosZ) < 0.050000001f)
            {
                auto pFxSystem = g_fxMan.CreateFxSystem("water_swim", pBoneLFootPos, 0, 0);
                if (pFxSystem)
                {
                    pFxSystem->PlayAndKill();
                    pPed->m_pedAudio.AddAudioEvent(74, 0.0, 1.0f, 0, 0, 0, 0);
                    return;
                }
            }
        }
        break;
    }
    case SWIM_DIVE_UNDERWATER:
    {
        if (m_bTriggerWaterSplash)
        {
            return;
        }
        g_fx.TriggerWaterSplash(vecParticlePosition);
        m_bTriggerWaterSplash = true;
        pPed->m_pedAudio.AddAudioEvent(75, 0.0, 1.0, 0, 0, 0, 0);
        return;
    }
    case SWIM_UNDERWATER_SPRINTING:
    {
        unsigned int oxygen = 5;
        if (pPed->IsPlayer())
        {
            oxygen = static_cast<unsigned int>(
                ((100.0f - pPlayerData->m_fBreath / CStats::GetFatAndMuscleModifier(STAT_MOD_AIR_IN_LUNG) * 100.0f) * 0.33333334f));
        }
        if (CGeneral::GetRandomNumberInRange(0, 100) < oxygen)
        {
            RpHAnimHierarchy* pRwAnimHierarchy = GetAnimHierarchyFromSkinClump(pPed->m_pRwClump);
            RwV3d* pBoneSpine1Pos = &RpHAnimHierarchyGetMatrixArray(pRwAnimHierarchy)[BONE_SPINE1].pos;
            static FxPrtMult_c fxPrtMult(1.0f, 1.0f, 1.0f, 0.25f, 0.30000001f, 0.0f, 0.5f);
            RwV3d vecParticleVelocity = { 0.0f, 0.0f, 2.0f };
            g_fx.m_pPrtBubble->AddParticle(pBoneSpine1Pos, &vecParticleVelocity, 0.0f, &fxPrtMult, -1.0f, 1.2f, 0.60000002f, 0);
        }
        break;
    }
    }
#endif
}

void CTaskSimpleSwim::ProcessControlAI(CPed* pPed)
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

void CTaskSimpleSwim::ProcessControlInput(CPlayerPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x688A90, CTaskSimpleSwim*, CPlayerPed*>(this, pPed);
#else
    CVector vecPedWalk;

    CPlayerData* pPlayerData = pPed->m_pPlayerData;
    if (!m_bFinishedBlending || !m_bAnimBlockRefAdded)
    {
        pPlayerData->m_fMoveBlendRatio = 0.0;
        return;
    }

    CPad* pPad = pPed->GetPadFromPlayer();
    short pedWalkUpDown = pPad->GetPedWalkUpDown();
    short pedWalkLeftRight = pPad->GetPedWalkLeftRight();
    vecPedWalk.x = pedWalkLeftRight * 0.0078125f;
    vecPedWalk.y = pedWalkUpDown * 0.0078125f;

    float fWalkMagnitude = vecPedWalk.Magnitude2D();
    if (m_nSwimState < SWIM_SPRINTING)
    {
        if (pPad->JumpJustDown())
        {
            m_nSwimState = SWIM_BACK_TO_SURFACE;
        }
        else if (pPad->WeaponJustDown(pPed))
        {
            m_nSwimState = SWIM_DIVE_UNDERWATER;
            pPed->m_pPlayerData->m_fMoveBlendRatio = 0.0;
        }
    }

    switch (m_nSwimState)
    {
    case SWIM_TREAD:
    case SWIM_SPRINT:
    case SWIM_SPRINTING:
    {
        float pedWalkX = 0.0f;
        bool bPlayerUse2PlayerControls = false;
        if (CGameLogic::IsPlayerUse2PlayerControls(pPed))
        {
            bPlayerUse2PlayerControls = true;;
            pedWalkX = vecPedWalk.x;
            if (fWalkMagnitude > 0)
            {
                float negativePedWalkX = -pedWalkX;
                float fRadianAngle = CGeneral::GetRadianAngleBetweenPoints(0.0, 0.0, negativePedWalkX, vecPedWalk.y)
                    - TheCamera.m_fOrientation;
                float fLimitedRadianAngle = CGeneral::LimitRadianAngle(fRadianAngle);

                CVector vecPedWalkDirection(0.0f, -sin(fLimitedRadianAngle), cos(fLimitedRadianAngle));
                if (fLimitedRadianAngle <= pPed->m_fCurrentRotation + 3.1415927f)
                {
                    if (fLimitedRadianAngle < pPed->m_fCurrentRotation - 3.1415927f)
                    {
                        fLimitedRadianAngle += 6.2831855f;
                    }
                }
                else
                {
                    fLimitedRadianAngle -= 6.2831855f;
                }

                float fCurrenRotation = fLimitedRadianAngle - pPed->m_fCurrentRotation;
                if (fCurrenRotation <= 1.0f)
                {
                    if (fCurrenRotation < -1.0f)
                        fCurrenRotation = -1.0f;
                }
                else
                {
                    fCurrenRotation = 1.0f;
                }

                pPed->m_fAimingRotation = fCurrenRotation * (CTimer::ms_fTimeStep * 0.079999998f) + pPed->m_fCurrentRotation;
                if (pPed->m_fAimingRotation <= 3.14159274f)
                {
                    if (pPed->m_fAimingRotation < -3.1415927f)
                    {
                        pPed->m_fAimingRotation += 6.2831855f;
                    }
                }
                else
                {
                    pPed->m_fAimingRotation -= 6.2831855f;
                }
                if (CGameLogic::IsPlayerAllowedToGoInThisDirection(pPed, vecPedWalkDirection.x, vecPedWalkDirection.y, vecPedWalkDirection.z, 0.0))
                {
                    CMatrixLink* pPedMatrix = pPed->m_matrix;
                    pedWalkX = (vecPedWalkDirection.y * pPedMatrix->right.y
                        + vecPedWalkDirection.x * pPedMatrix->right.x
                        + pPedMatrix->right.z * 0.0f)
                        * fWalkMagnitude;
                    vecPedWalk.y = -((vecPedWalkDirection.y * pPedMatrix->up.y
                        + pPedMatrix->up.z * 0.0f
                        + vecPedWalkDirection.x * pPedMatrix->up.x)
                        * fWalkMagnitude);
                }
                else
                {
                    pedWalkX = 0.0;
                    fWalkMagnitude = 0.0;
                    vecPedWalk.y = 0.0;
                }
            }
        }
        else // if CGameLogic::IsPlayerUse2PlayerControls(pPed) == false
        {
            pedWalkX = vecPedWalk.x;
        }

        float fRotation = pedWalkX;

        if (!CCamera::m_bUseMouse3rdPerson)
        {
            if (fWalkMagnitude <= 0.0)
            {
                if (pPlayerData->m_fMoveBlendRatio > 0.0f)
                {
                    pPlayerData->m_fMoveBlendRatio -= CTimer::ms_fTimeStep * 0.050000001f;
                    if (pPlayerData->m_fMoveBlendRatio < 0.0)
                    {
                        pPlayerData->m_fMoveBlendRatio = 0.0;
                    }
                }
            }
            else
            {
                bool bUpdateMoveBlendRatio = false;
                if (!bPlayerUse2PlayerControls)
                {
                    pPed->m_fAimingRotation += CTimer::ms_fTimeStep * -0.029999999f * pedWalkX;
                    if (pPed->m_fAimingRotation <= 3.14159274f)
                    {
                        if (pPed->m_fAimingRotation < -3.1415927f)
                        {
                            pPed->m_fAimingRotation += 6.2831855f;
                        }
                    }
                    else
                    {
                        pPed->m_fAimingRotation -= 6.2831855f;
                    }
                    float pedWalkY = vecPedWalk.y;
                    float negativePedWalkY = 0.0f;
                    if (m_nSwimState)
                    {
                        if (pedWalkY > 0.0)
                        {
                            fWalkMagnitude -= vecPedWalk.y;
                        }
                    }
                    else
                    {
                        fWalkMagnitude = -pedWalkY;
                    }

                    if (fWalkMagnitude < 0.0)
                    {
                        fWalkMagnitude = 0.0;
                    }

                    bUpdateMoveBlendRatio = true;
                }

                if (bPlayerUse2PlayerControls || bUpdateMoveBlendRatio)
                {
                    float fTimeStep = CTimer::ms_fTimeStep * 0.07f;
                    if (fWalkMagnitude - pPlayerData->m_fMoveBlendRatio <= fTimeStep)
                    {
                        pPlayerData->m_fMoveBlendRatio = fWalkMagnitude;
                    }
                    else
                    {
                        pPlayerData->m_fMoveBlendRatio += fTimeStep;
                    }
                }
            }
        }
        else
        {
            pPed->m_fAimingRotation = atan2(
                -TheCamera.m_aCams[TheCamera.m_nActiveCam].m_vecFront.x,
                TheCamera.m_aCams[TheCamera.m_nActiveCam].m_vecFront.y);
            if (TheCamera.GetLookDirection() != 3)
            {
                pPed->m_fAimingRotation += 3.1415927f;
                if (pPed->m_fAimingRotation > 3.14159274f)
                {
                    pPed->m_fAimingRotation -= 6.2831855f;
                }
            }

            float negativePedWalkY = -vecPedWalk.y;
            float fTimeStep = CTimer::ms_fTimeStep * 0.07f;
            if (negativePedWalkY - pPlayerData->m_fMoveBlendRatio > fTimeStep)
            {
                pPlayerData->m_fMoveBlendRatio += fTimeStep;
            }
            else
            {
                pPlayerData->m_fMoveBlendRatio = negativePedWalkY;
            }

            fRotation = -(pPed->m_fAimingRotation - pPed->m_fCurrentRotation);
            if (fRotation <= 3.1415927)
            {
                if (fRotation < -3.1415927f)
                {
                    fRotation = 6.2831855f - (pPed->m_fAimingRotation - pPed->m_fCurrentRotation);
                }

            }
            else
            {
                fRotation -= 6.2831855f;
            }

            fRotation *= 10.0f;
            fRotation = std::max(-1.0f, fRotation);
            fRotation = std::min(1.0f, fRotation);
        }

        m_fAimingRotation += CTimer::ms_fTimeStep * 0.079999998f * fRotation;

        if (m_nSwimState == SWIM_SPRINTING)
        {
            m_fTurningRotationY += CTimer::ms_fTimeStep * 0.039999999f * fRotation;
        }
        else if (m_nSwimState == SWIM_SPRINT)
        {
            m_fUpperTorsoRotationX += fabs(pedWalkX) * CTimer::ms_fTimeStep * 0.039999999f;
        }

        if (m_nSwimState == SWIM_SPRINTING)
        {
            CVector vecPositionSum;
            CVector vecPositionDifference;
            CVector* pPedPosition = &pPed->GetPosition();

            float fSumWaterLevel = 0.0;
            float fDifferenceWaterLevel = 0.0f;
            VectorAdd(&vecPositionSum, pPedPosition, &pPed->m_matrix->up);
            VectorSub(&vecPositionDifference, pPedPosition, &pPed->m_matrix->up);
            if (CWaterLevel::GetWaterLevel(vecPositionSum.x, vecPositionSum.y, vecPositionSum.z, &fSumWaterLevel, 1, 0))
            {
                if (CWaterLevel::GetWaterLevel(vecPositionDifference.x, vecPositionDifference.y, vecPositionDifference.z, &fDifferenceWaterLevel, 1, 0))
                {
                    m_fRotationX = atan2(fSumWaterLevel - fDifferenceWaterLevel, 2.0f) * 1.0f;
                }
            }
        }

        if (pPed->ControlButtonSprint(static_cast<eSprintType>(2)) < 1.0f)
        {
            m_nSwimState = static_cast<eSwimState>(pPed->m_pPlayerData->m_fMoveBlendRatio > 0.5f);
        }
        else
        {
            m_nSwimState = SWIM_SPRINTING;
        }
        break;
    }
    case SWIM_DIVE_UNDERWATER:
    {
        if (m_fStateChanger > 0.0f)
        {
            m_fStateChanger = 0.0f;
        }
        break;
    }
    case SWIM_UNDERWATER_SPRINTING:
    {
        float fUpperTorsoRotationX = 0.0f;
        if (CCamera::m_bUseMouse3rdPerson)
        {
            CVector vecActiveCamFront = TheCamera.m_aCams[TheCamera.m_nActiveCam].m_vecFront;;
            if (TheCamera.GetLookDirection() != 3)
            {
                vecActiveCamFront.x *= -1.0f;
                vecActiveCamFront.y *= -1.0f;
                vecActiveCamFront.z = 0.0f;
            }

            pPed->m_fAimingRotation = atan2(-vecActiveCamFront.x, vecActiveCamFront.y);
            float fRotation = -(pPed->m_fAimingRotation - pPed->m_fCurrentRotation);
            if (fRotation <= 3.1415927f)
            {
                if (fRotation < -3.1415927f)
                    fRotation += 6.2831855f;
            }
            else
            {
                fRotation -= 6.2831855f;
            }

            fRotation *= 10.0f;
            fRotation = std::max(-1.0f, fRotation);
            fRotation = std::min(1.0f, fRotation);

            m_fTurningRotationY += CTimer::ms_fTimeStep * 0.039999999f * fRotation;
            m_fAimingRotation += CTimer::ms_fTimeStep * 0.079999998f * fRotation;

            float fRotationX = (asin(vecActiveCamFront.z) - m_fRotationX) * 10.0f;
            fRotationX = std::max(-1.0f, fRotationX);
            fRotationX = std::min(1.0f, fRotationX);
            if (m_fStateChanger == 0.0f || fRotationX > 0.0f)
            {
                m_fRotationX += CTimer::ms_fTimeStep * 0.02f * fRotationX;
            }
            fUpperTorsoRotationX = m_fTurningRotationY / 0.5f;
            if (fUpperTorsoRotationX > 1.0f || fUpperTorsoRotationX >= -1.0f)
            {
                if (fUpperTorsoRotationX > 1.0f)
                {
                    fUpperTorsoRotationX = 1.0f;
                }
            }
            else
            {
                fUpperTorsoRotationX = -1.0f;
            }

            fUpperTorsoRotationX = fRotationX + fUpperTorsoRotationX * -0.079999998f * fRotation;
            if (fUpperTorsoRotationX <= 1.0f)
            {
                if (fUpperTorsoRotationX < -1.0f)
                {
                    fUpperTorsoRotationX = -1.0f;
                }
            }
            else
            {
                fUpperTorsoRotationX = 1.0;
            }

            m_fUpperTorsoRotationX += CTimer::ms_fTimeStep * -0.079999998f * fUpperTorsoRotationX;
        }
        else
        {
            if (fWalkMagnitude > 0.0f)
            {
                float fNormalizedWalkMagnitude = 1.0f / fWalkMagnitude;
                vecPedWalk.x = vecPedWalk.x * fNormalizedWalkMagnitude;
                float pedWalkY = fNormalizedWalkMagnitude * vecPedWalk.y;
                pPed->m_fAimingRotation += CTimer::ms_fTimeStep * -0.029999999f * vecPedWalk.x;

                if (pPed->m_fAimingRotation <= 3.14159274f)
                {
                    if (pPed->m_fAimingRotation < -3.1415927f)
                    {
                        pPed->m_fAimingRotation += 6.2831855f;
                    }
                }
                else
                {
                    pPed->m_fAimingRotation -= 6.2831855f;
                }

                m_fTurningRotationY += CTimer::ms_fTimeStep * 0.039999999f * vecPedWalk.x;
                m_fAimingRotation += CTimer::ms_fTimeStep * 0.079999998f * vecPedWalk.x;
                if (m_fStateChanger == 0.0f || pedWalkY > 0.0f)
                {
                    m_fRotationX += CTimer::ms_fTimeStep * 0.02f * pedWalkY;
                }

                fUpperTorsoRotationX = m_fTurningRotationY / 0.5f;
                if (fUpperTorsoRotationX > 1.0f || fUpperTorsoRotationX >= -1.0f)
                {
                    if (fUpperTorsoRotationX > 1.0f)
                    {
                        fUpperTorsoRotationX = 1.0f;
                    }
                }
                else
                {
                    fUpperTorsoRotationX = -1.0f;
                }

                fUpperTorsoRotationX = pedWalkY + fUpperTorsoRotationX * -0.079999998f * vecPedWalk.x;
                if (fUpperTorsoRotationX <= 1.0f)
                {
                    if (fUpperTorsoRotationX < -1.0f)
                    {
                        fUpperTorsoRotationX = -1.0f;
                    }
                }
                else
                {
                    fUpperTorsoRotationX = 1.0;
                }

                m_fUpperTorsoRotationX += CTimer::ms_fTimeStep * -0.079999998f * fUpperTorsoRotationX;
            }
        }

        m_fRotationX += CTimer::ms_fTimeStep * 0.001f;

        if (m_fRotationX > 1.3962635f || m_fRotationX >= -1.3962635f)
        {
            if (m_fRotationX > 1.3962635f)
            {
                m_fRotationX = 1.3962635f;
            }
        }
        else
        {
            m_fRotationX = -1.3962635f;
        }

        if (pPed->m_pPlayerData->m_fTimeCanRun <= 0.0f)
        {
            pPed->m_pPlayerData->m_fTimeCanRun = 0.1f;
        }
        pPed->ControlButtonSprint(static_cast<eSprintType>(3));
        break;
    }
    }


    float fRotation = 0.94999999f;
    if (m_nSwimState == SWIM_UNDERWATER_SPRINTING || m_nSwimState == SWIM_SPRINTING)
    {
        fRotation = 0.94999999f;
    }

    if (m_fTurningRotationY > 0.0099999998f || m_fTurningRotationY < -0.0099999998f)
    {
        m_fTurningRotationY *= pow(fRotation, CTimer::ms_fTimeStep);
    }
    else
    {
        m_fTurningRotationY = 0.0f;
    }
    if (m_nSwimState != SWIM_UNDERWATER_SPRINTING && m_nSwimState != SWIM_SPRINTING)
    {
        if (m_fRotationX > 0.0099999998f || m_fRotationX < -0.0099999998f)
        {
            m_fRotationX *= pow(fRotation, CTimer::ms_fTimeStep);
        }
        else
        {
            m_fRotationX = 0.0f;
        }
    }

    if (m_nSwimState == SWIM_DIVE_UNDERWATER || m_nSwimState == SWIM_BACK_TO_SURFACE)
    {
        fRotation = 0.94999999f;
    }
    else
    {
        fRotation = 0.92000002f;
    }

    if (m_fAimingRotation > 0.0099999998f
        || m_fAimingRotation < -0.0099999998f
        || m_fUpperTorsoRotationX > 0.0099999998f
        || m_fUpperTorsoRotationX < -0.0099999998f)
    {
        float fTimeStepRotation = pow(fRotation, CTimer::ms_fTimeStep);
        m_fAimingRotation *= fTimeStepRotation;
        m_fUpperTorsoRotationX *= fTimeStepRotation;
    }
    else
    {
        m_fAimingRotation = 0.0f;
        m_fUpperTorsoRotationX = 0.0f;
    }
    if (m_nSwimState == SWIM_SPRINT)
    {
        pPed->HandleSprintEnergy(0, 0.5f);
    }
    else if (m_nSwimState != SWIM_SPRINTING)
    {
        pPed->HandleSprintEnergy(0, 1.0f);
    }
    return;
#endif
}

void CTaskSimpleSwim::CreateFxSystem(CPed* pPed, RwMatrixTag* pRwMatrix)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethod<0x68A9F0, CTaskSimpleSwim*, CPed*, RwMatrixTag* >(this, pPed, pRwMatrix);
#else
    RwV3d point = { 0.0f, 0.0f, 0.0f };
    m_pFxSystem = g_fxMan.CreateFxSystem("water_ripples", &point, pRwMatrix, 0);
    if (m_pFxSystem)
    {
        m_pFxSystem->CopyParentMatrix();
        m_pFxSystem->Play();
    }
#endif
}

void CTaskSimpleSwim::DestroyFxSystem()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethod<0x68AA50, CTaskSimpleSwim*>(this);
#else
    if (m_pFxSystem)
    {
        m_pFxSystem->Kill();
        m_pFxSystem = 0;
    }
#endif
}