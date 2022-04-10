#include "StdInc.h"

#include "TaskSimpleSwim.h"
#include "TaskSimpleClimb.h"
#include "FxPrtMult.h"

float& CTaskSimpleSwim::SWIM_DIVE_UNDER_ANGLE = *reinterpret_cast<float*>(0x8D2FC4);
float& CTaskSimpleSwim::SWIM_STOP_TIME = *reinterpret_cast<float*>(0x8D2FC0);

void CTaskSimpleSwim::InjectHooks() {
    RH_ScopedClass(CTaskSimpleSwim);
    RH_ScopedCategory("Tasks/TaskTypes");
    RH_ScopedInstall(Constructor, 0x688930);
    RH_ScopedVirtualInstall(Clone, 0x68B050);
    RH_ScopedVirtualInstall(GetId, 0x6889F0);
    RH_ScopedVirtualInstall(ProcessPed, 0x68B1C0);
    RH_ScopedVirtualInstall(MakeAbortable, 0x68B100);
    RH_ScopedInstall(ApplyRollAndPitch, 0x68A8E0);
    RH_ScopedInstall(ProcessSwimAnims, 0x6899F0);
    RH_ScopedInstall(ProcessSwimmingResistance, 0x68A1D0);
    RH_ScopedInstall(ProcessEffects, 0x68AA70);
    RH_ScopedInstall(ProcessControlAI, 0x689640);
    RH_ScopedInstall(ProcessControlInput, 0x688A90);
    RH_ScopedInstall(CreateFxSystem, 0x68A9F0);
    RH_ScopedInstall(DestroyFxSystem, 0x68AA50);
}

CTaskSimpleSwim::CTaskSimpleSwim(CVector* pos, CPed* ped) : CTaskSimple() {
    m_bFinishedBlending = false;
    m_bAnimBlockRefAdded = false;
    m_fAnimSpeed = -1.0f;
    m_vecPos = CVector();
    m_pPed = ped;
    m_fRotationX = 0.0f;
    m_fTurningRotationY = 0.0f;
    m_fUpperTorsoRotationX = 0.0f;
    m_fAimingRotation = 0.0f;
    m_fStateChanger = 0.0f;
    m_pEntity = nullptr;
    m_fSwimStopTime = 0.0f;
    m_nTimeStep = 0;
    m_nSwimState = SWIM_TREAD;
    m_AnimID = ANIM_ID_NO_ANIMATION_SET;

    if (pos)
        m_vecPos = *pos;

    CEntity::SafeRegisterRef(m_pPed);

    m_pFxSystem = nullptr;
    m_bTriggerWaterSplash = false;
    m_fRandomMoveBlendRatio = 0.0f;
}

CTaskSimpleSwim::~CTaskSimpleSwim() {
    if (m_bAnimBlockRefAdded) {
        CAnimBlock* animBlock = CAnimManager::ms_aAnimAssocGroups[ANIM_GROUP_SWIM].m_pAnimBlock;
        CAnimManager::RemoveAnimBlockRef(animBlock - CAnimManager::ms_aAnimBlocks);
    }

    CEntity::SafeCleanUpRef(m_pEntity);
    CEntity::SafeCleanUpRef(m_pPed);
}

// 0x688930
CTaskSimpleSwim* CTaskSimpleSwim::Constructor(CVector* pos, CPed* ped) {
    this->CTaskSimpleSwim::CTaskSimpleSwim(pos, ped);
    return this;
}

// 0x68B050
CTask* CTaskSimpleSwim::Clone() {
    return CTaskSimpleSwim::Clone_Reversed();
}

// 0x6889F0
eTaskType CTaskSimpleSwim::GetTaskType() {
    return CTaskSimpleSwim::GetId_Reversed();
}

// 0x68B100
bool CTaskSimpleSwim::MakeAbortable(class CPed* ped, eAbortPriority priority, const CEvent* event) {
    return MakeAbortable_Reversed(ped, priority, event);
}

// 0x68B1C0
bool CTaskSimpleSwim::ProcessPed(CPed* ped) {
    return ProcessPed_Reversed(ped);
}

CTask* CTaskSimpleSwim::Clone_Reversed() {
    return new CTaskSimpleSwim(&m_vecPos, m_pPed);
}

bool CTaskSimpleSwim::MakeAbortable_Reversed(class CPed* ped, eAbortPriority priority, const CEvent* event) {
    const auto* damageEvent = static_cast<const CEventDamage*>(event);

    if (priority == ABORT_PRIORITY_IMMEDIATE) {
        CAnimManager::BlendAnimation(ped->m_pRwClump, ped->m_nAnimGroup, ANIM_ID_IDLE, 1000.0f);
        ped->m_nMoveState = PEDMOVE_STILL;
        ped->m_nSwimmingMoveState = PEDMOVE_STILL;

        if (m_AnimID != ANIM_ID_NO_ANIMATION_SET) {
            auto animAssociation = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, m_AnimID);
            if (animAssociation) {
                animAssociation->m_fBlendDelta = -1000.0f;
            }
        }

        ped->RestoreHeadingRate();
    }
    else if (!event || event->GetEventPriority() < 71
        && (event->GetEventType() != EVENT_DAMAGE || !damageEvent->m_damageResponse.m_bHealthZero || !damageEvent->m_bAddToEventGroup))
    {
        return false;
    }

    DestroyFxSystem();
    return true;
}

bool CTaskSimpleSwim::ProcessPed_Reversed(CPed* ped) {
    if (m_pEntity) {
        CAnimManager::BlendAnimation(ped->m_pRwClump, ped->m_nAnimGroup, ANIM_ID_IDLE, 8.0f);
        ped->m_nMoveState = PEDMOVE_STILL;
        ped->m_nSwimmingMoveState = PEDMOVE_STILL;

        DestroyFxSystem();
        return true;
    }

    if (m_fSwimStopTime > SWIM_STOP_TIME || ped->bIsStanding) {
        CAnimBlendAssociation* assoc = nullptr;
        if (m_AnimID != ANIM_ID_NO_ANIMATION_SET) {
            assoc = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, m_AnimID);
        }
        AnimationId animId = ANIM_ID_IDLE;
        ped->m_nSwimmingMoveState = PEDMOVE_STILL;
        ped->m_nMoveState = PEDMOVE_STILL;
        if (assoc) {
            if (assoc->m_nAnimId == ANIM_ID_CLIMB_JUMP)
                assoc->m_nFlags |= ANIM_FLAG_UNLOCK_LAST_FRAME;
            else
                assoc->m_fBlendDelta = -4.0f;

            if (m_AnimID == ANIM_ID_SWIM_BREAST) {
                animId = ANIM_ID_WALK;
                ped->m_nSwimmingMoveState = PEDMOVE_WALK;
                ped->m_nMoveState = PEDMOVE_WALK;
            } else if (m_AnimID == ANIM_ID_SWIM_CRAWL) {
                animId = ANIM_ID_RUN;
                ped->m_nSwimmingMoveState = PEDMOVE_RUN;
                ped->m_nMoveState = PEDMOVE_RUN;
            }
        }
        CAnimManager::BlendAnimation(ped->m_pRwClump, ped->m_nAnimGroup, animId, 4.0f);
        ped->RestoreHeadingRate();
        DestroyFxSystem();
        return true;
    }

    ped->bIsInTheAir = false;

    if (ped->IsPlayer()) {
        if (m_nTimeStep && m_nSwimState != SWIM_UNDERWATER_SPRINTING) {
            ProcessControlAI(ped);
            auto swimmingTimeStep = static_cast<uint32>((CTimer::GetTimeStepInSeconds()) * 1000.0f);
            if (m_nTimeStep <= swimmingTimeStep)
                m_nTimeStep = 0;
            else
                m_nTimeStep -= swimmingTimeStep;

            CVector vecOut = m_vecPos - ped->GetPosition();
            ped->m_pPlayerData->m_fMoveBlendRatio = vecOut.Magnitude();
            CPlayerPedData* playerData = ped->m_pPlayerData;
            if (playerData->m_fMoveBlendRatio < 0.5f) {
                playerData->m_fMoveBlendRatio = 0.0f;
                CAnimManager::BlendAnimation(ped->m_pRwClump, ped->m_nAnimGroup, ANIM_ID_IDLE, 4.0f);
                ped->RestoreHeadingRate();
                DestroyFxSystem();
                return true;
            }
            if (playerData->m_fMoveBlendRatio > 1.0f)
                playerData->m_fMoveBlendRatio = 1.0f;
        } else {
            ProcessControlInput(reinterpret_cast<CPlayerPed*>(ped));
            m_nTimeStep = 0;
        }
        bool bDecreaseAir = false;
        float fDecreaseAirMult = 1.0f;
        if (m_nSwimState == SWIM_UNDERWATER_SPRINTING) {
            bDecreaseAir = true;
            CAnimBlendAssociation* assocUnder = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_SWIM_UNDER);
            if (assocUnder) {
                fDecreaseAirMult = assocUnder->m_fSpeed * assocUnder->m_fBlendAmount + 1.0f;
            }
        }

        ped->AsPlayer()->HandlePlayerBreath(bDecreaseAir, fDecreaseAirMult);
        if (m_pPed && m_nSwimState != SWIM_UNDERWATER_SPRINTING) {
            if (CStats::GetFatAndMuscleModifier(STAT_MOD_AIR_IN_LUNG) * 0.5f > ped->m_pPlayerData->m_fBreath) {
                ped->Say(356);
            }
        }
        ped->SetMoveState(PEDMOVE_NONE);
    } else {
        ProcessControlAI(ped);

        if (m_nSwimState == SWIM_UNDERWATER_SPRINTING) {
            CPedDamageResponseCalculator damageCalculator(nullptr, CTimer::GetTimeStep(), WEAPON_DROWNING, PED_PIECE_TORSO, false);
            CEventDamage eventDamage(nullptr, CTimer::GetTimeInMS(), WEAPON_DROWNING, PED_PIECE_TORSO, 0, false, ped->bInVehicle);
            if (eventDamage.AffectsPed(ped))
                damageCalculator.ComputeDamageResponse(ped, eventDamage.m_damageResponse, true);
            else
                eventDamage.m_damageResponse.m_bDamageCalculated = true;
            ped->GetEventGroup().Add(&eventDamage, false);
        }
    }

    ProcessSwimAnims(ped);
    ProcessSwimmingResistance(ped);
    ProcessEffects(ped);
    return false;
}

// 0x68A8E0
void CTaskSimpleSwim::ApplyRollAndPitch(CPed* ped) {
    LimbOrientation LimbOrientation(m_fAimingRotation, m_fUpperTorsoRotationX);
    ped->m_pedIK.RotateTorso(ped->m_apBones[PED_NODE_UPPER_TORSO], LimbOrientation, rwCOMBINEREPLACE);
    if (ped->m_pRwObject) {
        CMatrix pedMatrix(ped->GetModellingMatrix(), false);
        CMatrix rotationMatrix;
        rotationMatrix.SetTranslate(CVector(0.0f, 0.0f, 0.0f));
        rotationMatrix.RotateY(m_fTurningRotationY);
        rotationMatrix.RotateX(m_fRotationX);
        pedMatrix *= rotationMatrix;
        pedMatrix.UpdateRW();
        ped->UpdateRwFrame();
    }
}

// todo: shadow var animAssociation
// 0x6899F0
void CTaskSimpleSwim::ProcessSwimAnims(CPed* ped) {
    auto* player = ped->AsPlayer();
    CAnimBlendAssociation* assocTread = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_SWIM_TREAD);
    if (m_bFinishedBlending) {
        if (assocTread && assocTread->m_fBlendAmount < 1.0f && assocTread->m_fBlendDelta <= 0.0f) {
            CAnimManager::BlendAnimation(player->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_SWIM_TREAD, 8.0f);
        }
    } else {
        if (assocTread || (assocTread = CAnimManager::BlendAnimation(player->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_SWIM_TREAD, 8.0f)) != nullptr) {
            if (assocTread->m_fBlendAmount >= 1.0f)
                m_bFinishedBlending = true;
        }
        RpAnimBlendClumpSetBlendDeltas(player->m_pRwClump, 0x10, -8.0f);
        auto& fxSystem = player->GetActiveWeapon().m_pFxSystem; // Removes fire or something in water
        FxSystem_c::SafeKillAndClear(fxSystem);

        if (player->IsPlayer() && !m_nSwimState) {
            CVector& vecPos = player->GetPosition();
            float waterLevel = 0.0f;
            if (CWaterLevel::GetWaterLevel(vecPos, waterLevel, true)) {
                if (waterLevel - 2.0f > vecPos.z)
                    m_nSwimState = SWIM_UNDERWATER_SPRINTING;
            }
        }
    }

    if (!m_bAnimBlockRefAdded) {
        CAnimBlock* animBlock = CAnimManager::ms_aAnimAssocGroups[ANIM_GROUP_SWIM].m_pAnimBlock;
        if (!animBlock) {
            char* blockName = CAnimManager::GetAnimBlockName(ANIM_GROUP_SWIM);
            animBlock = CAnimManager::GetAnimationBlock(blockName);
        }
        if (animBlock->bLoaded) {
            CAnimManager::AddAnimBlockRef(animBlock - CAnimManager::ms_aAnimBlocks); // what?
            m_bAnimBlockRefAdded = true;
        } else {
            CStreaming::RequestModel(IFPToModelId(animBlock - CAnimManager::ms_aAnimBlocks), STREAMING_KEEP_IN_MEMORY);
        }
    }

    if (m_bFinishedBlending && m_bAnimBlockRefAdded) {
        switch (m_nSwimState) {
        case SWIM_TREAD: {
            if (m_AnimID == ANIM_ID_SWIM_TREAD)
                break;

            constexpr struct { AnimationId anim; float delta; } mapping[] = {
                { ANIM_ID_SWIM_BREAST,      -1.0f },
                { ANIM_ID_SWIM_CRAWL,       -1.0f },
                { ANIM_ID_SWIM_DIVE_UNDER,  -4.0f },
                { ANIM_ID_SWIM_UNDER,       -2.0f },
                { ANIM_ID_SWIM_GLIDE,       -2.0f },
                { ANIM_ID_SWIM_JUMPOUT,     -4.0f },
                { ANIM_ID_CLIMB_JUMP,       -4.0f },
            };
            for (auto& [anim, delta] : mapping) {
                if (auto* assoc = RpAnimBlendClumpGetAssociation(player->m_pRwClump, anim)) {
                    assoc->m_fBlendDelta = delta;
                }
            }
            m_AnimID = ANIM_ID_SWIM_TREAD;
            break;
        }
        case SWIM_SPRINT: {
            if (m_AnimID == ANIM_ID_SWIM_BREAST) {
                CAnimBlendAssociation* assoc = RpAnimBlendClumpGetAssociation(player->m_pRwClump, ANIM_ID_SWIM_BREAST);
                if (!assoc) {
                    m_nSwimState = SWIM_TREAD;
                    break;
                }
                if (player->IsPlayer()) {
                    assoc->m_fSpeed = player->m_pPlayerData->m_fMoveBlendRatio;
                } else if (m_fAnimSpeed > 0.0f && m_fAnimSpeed <= 1.0f) {
                    assoc->m_fSpeed = m_fAnimSpeed;
                }
            } else {
                CAnimManager::BlendAnimation(player->m_pRwClump, ANIM_GROUP_SWIM, ANIM_ID_SWIM_BREAST, 2.0f);
                m_AnimID = ANIM_ID_SWIM_BREAST;
            }
            break;
        }
        case SWIM_SPRINTING: {
            if (m_AnimID == ANIM_ID_SWIM_CRAWL) {
                CAnimBlendAssociation* assoc = RpAnimBlendClumpGetAssociation(player->m_pRwClump, ANIM_ID_SWIM_CRAWL);
                if (!assoc) {
                    m_nSwimState = SWIM_TREAD;
                    break;
                }
                if (player->m_pPlayerData) {
                    float buttonSprintResults = player->GetButtonSprintResults(SPRINT_WATER);
                    assoc->m_fSpeed = static_cast<float>(std::max(1.0f, buttonSprintResults));
                } else if (m_fAnimSpeed > 1.0) {
                    auto taskAnimSpeed = static_cast<float>(m_fAnimSpeed - 1.0f);
                    assoc->m_fSpeed    = static_cast<float>(std::min(1.5f, taskAnimSpeed));
                }
            } else {
                CAnimManager::BlendAnimation(player->m_pRwClump, ANIM_GROUP_SWIM, ANIM_ID_SWIM_CRAWL, 2.0f);
                m_AnimID = ANIM_ID_SWIM_CRAWL;
            }
            break;
        }
        case SWIM_DIVE_UNDERWATER: {
            if (m_AnimID == ANIM_ID_SWIM_DIVE_UNDER) {
                CAnimBlendAssociation* assocUnder = RpAnimBlendClumpGetAssociation(player->m_pRwClump, ANIM_ID_SWIM_DIVE_UNDER);
                if (!assocUnder) {
                    m_nSwimState = SWIM_TREAD;
                    break;
                }

                if (assocUnder->m_pHierarchy->m_fTotalTime == assocUnder->m_fCurrentTime) {
                    m_nSwimState = SWIM_UNDERWATER_SPRINTING;
                }
            } else {
                CAnimManager::BlendAnimation(player->m_pRwClump, ANIM_GROUP_SWIM, ANIM_ID_SWIM_DIVE_UNDER, 8.0f);
                m_AnimID = ANIM_ID_SWIM_DIVE_UNDER;
            }
            break;
        }
        case SWIM_UNDERWATER_SPRINTING: {
            if ((m_AnimID == ANIM_ID_SWIM_UNDER || m_AnimID == ANIM_ID_SWIM_GLIDE) && m_fStateChanger >= 0.0f) {
                if (player->m_pPlayerData && player->GetButtonSprintResults(SPRINT_UNDERWATER) >= 1.0f) {
                    CAnimBlendAssociation* assocUnder = RpAnimBlendClumpGetAssociation(player->m_pRwClump, ANIM_ID_SWIM_UNDER);
                    if (!assocUnder || assocUnder->m_fBlendDelta < 0.0f || assocUnder->m_fBlendAmount == 0.0f) {
                        assocUnder = CAnimManager::BlendAnimation(player->m_pRwClump, ANIM_GROUP_SWIM, ANIM_ID_SWIM_UNDER, 4.0f);
                    }
                    if (assocUnder->m_pHierarchy->m_fTotalTime == assocUnder->m_fCurrentTime) {
                        assocUnder->Start(0.0f);
                        float buttonSprintResults = player->GetButtonSprintResults(SPRINT_UNDERWATER);
                        assocUnder->m_fSpeed = static_cast<float>(std::max(0.7f, buttonSprintResults));
                    }
                    m_AnimID = ANIM_ID_SWIM_UNDER;
                } else {
                    CAnimBlendAssociation* assocGlide = RpAnimBlendClumpGetAssociation(player->m_pRwClump, ANIM_ID_SWIM_GLIDE);
                    if (!assocGlide || assocGlide->m_fBlendDelta < 0.0f || assocGlide->m_fBlendAmount == 0.0f) {
                        CAnimManager::BlendAnimation(player->m_pRwClump, ANIM_GROUP_SWIM, ANIM_ID_SWIM_GLIDE, 4.0f);
                    }
                    m_AnimID = ANIM_ID_SWIM_GLIDE;
                }
            } else {
                CAnimBlendAssociation* assocUnder = RpAnimBlendClumpGetAssociation(player->m_pRwClump, ANIM_ID_SWIM_UNDER);
                if (assocUnder) {
                    if (m_fStateChanger < 0.0f && assocUnder->m_fBlendAmount >= 0.99f) {
                        if (m_fStateChanger > -2.0f) {
                            m_fStateChanger = 0.0f;
                            m_fRotationX = DegreesToRadians(CTaskSimpleSwim::SWIM_DIVE_UNDER_ANGLE);
                        } else {
                            m_fRotationX = DegreesToRadians(80.0f);
                            m_fStateChanger = 0.0f;
                        }
                    }
                } else {
                    CAnimManager::BlendAnimation(player->m_pRwClump, ANIM_GROUP_SWIM, ANIM_ID_SWIM_UNDER, 1000.0f);
                    if (m_AnimID == ANIM_ID_SWIM_TREAD || m_AnimID == ANIM_ID_NO_ANIMATION_SET) {
                        m_fStateChanger = -2.0f;
                        m_AnimID = ANIM_ID_SWIM_UNDER;
                    } else {
                        m_fStateChanger = -1.0f;
                        m_AnimID = ANIM_ID_SWIM_UNDER;
                    }
                }
            }
            break;
        }
        case SWIM_BACK_TO_SURFACE: {
            if (m_AnimID == ANIM_ID_SWIM_JUMPOUT) {
                CAnimBlendAssociation* assocJumpOut = RpAnimBlendClumpGetAssociation(player->m_pRwClump, ANIM_ID_SWIM_JUMPOUT);
                if (assocJumpOut) {
                    if (assocJumpOut->m_pHierarchy->m_fTotalTime * 0.25f <= assocJumpOut->m_fTimeStep + assocJumpOut->m_fCurrentTime) {
                        assocJumpOut = CAnimManager::BlendAnimation(player->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_CLIMB_JUMP, 8.0f);
                        assocJumpOut->m_nFlags |= ANIM_FLAG_UNLOCK_LAST_FRAME;
                        m_AnimID = ANIM_ID_CLIMB_JUMP;
                    }
                    break;
                }
            } else {
                if (m_AnimID != ANIM_ID_CLIMB_JUMP) {
                    CAnimManager::BlendAnimation(player->m_pRwClump, ANIM_GROUP_SWIM, ANIM_ID_SWIM_JUMPOUT, 8.0f);
                    m_AnimID = ANIM_ID_SWIM_JUMPOUT;
                    player->m_vecMoveSpeed.z = static_cast<float>(8.0f / player->m_fMass);
                    m_pEntity = CTaskSimpleClimb::TestForClimb(player, m_pClimbPos, m_fAngle, m_nSurfaceType, true);
                    CEntity::SafeRegisterRef(m_pEntity);
                    break;
                }
                if (RpAnimBlendClumpGetAssociation(player->m_pRwClump, ANIM_ID_CLIMB_JUMP)) {
                    const CVector& position = player->GetPosition();
                    float waterLevel = 0.0f;
                    if (!CWaterLevel::GetWaterLevel(position, waterLevel, true) || position.z + 0.5f >= waterLevel)
                        break;
                }
            }
            m_nSwimState = SWIM_TREAD;
            break;
        }
        default: {
            break;
        }
        }

        if (player->m_pPlayerData && (player->m_pPlayerData->m_fMoveBlendRatio > 0.5 || m_nSwimState == SWIM_UNDERWATER_SPRINTING)) {
            CStats::UpdateStatsWhenSwimming(m_nSwimState == SWIM_UNDERWATER_SPRINTING, m_nSwimState == SWIM_SPRINTING);
        }
    }
}

// 0x68A1D0
void CTaskSimpleSwim::ProcessSwimmingResistance(CPed* ped) {
    float fSubmergeZ = -1.0f;
    CVector vecPedMoveSpeed;

    switch (m_nSwimState) {
    case SWIM_TREAD:
    case SWIM_SPRINT:
    case SWIM_SPRINTING: {
        CAnimBlendAssociation* animSwimBreast = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_SWIM_BREAST);
        CAnimBlendAssociation* animSwimCrawl = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_SWIM_CRAWL);

        float fAnimBlendSum = 0.0f;
        float fAnimBlendDifference = 1.0f;
        if (animSwimBreast) {
            fAnimBlendSum = 0.4f * animSwimBreast->m_fBlendAmount;
            fAnimBlendDifference = 1.0f - animSwimBreast->m_fBlendAmount;
        }

        if (animSwimCrawl) {
            fAnimBlendSum += 0.2f * animSwimCrawl->m_fBlendAmount;
            fAnimBlendDifference -= animSwimCrawl->m_fBlendAmount;
        }

        if (fAnimBlendDifference < 0.0f) {
            fAnimBlendDifference = 0.0f;
        }

        fSubmergeZ = fAnimBlendDifference * 0.55f + fAnimBlendSum;

        vecPedMoveSpeed =  ped->m_vecAnimMovingShiftLocal.x * ped->GetRight();
        vecPedMoveSpeed += ped->m_vecAnimMovingShiftLocal.y * ped->GetForward();
        break;
    }
    case SWIM_DIVE_UNDERWATER: {
        vecPedMoveSpeed =  ped->m_vecAnimMovingShiftLocal.x * ped->GetRight();
        vecPedMoveSpeed += ped->m_vecAnimMovingShiftLocal.y * ped->GetForward();

        auto pAnimSwimDiveUnder = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_SWIM_DIVE_UNDER);
        if (pAnimSwimDiveUnder) {
            vecPedMoveSpeed.z = pAnimSwimDiveUnder->m_fCurrentTime / pAnimSwimDiveUnder->m_pHierarchy->m_fTotalTime * -0.1f;
        }
        break;
    }
    case SWIM_UNDERWATER_SPRINTING: {
        vecPedMoveSpeed   =  ped->m_vecAnimMovingShiftLocal.x * ped->GetRight();
        vecPedMoveSpeed   += std::cos(m_fRotationX) * ped->m_vecAnimMovingShiftLocal.y * ped->GetForward();
        vecPedMoveSpeed.z += std::sin(m_fRotationX) * ped->m_vecAnimMovingShiftLocal.y + 0.01f;
        break;
    }
    case SWIM_BACK_TO_SURFACE: {
        auto animClimb = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_CLIMB_JUMP);
        if (!animClimb)
            animClimb = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_SWIM_JUMPOUT);

        if (animClimb) {
            if (animClimb->m_pHierarchy->m_fTotalTime > animClimb->m_fCurrentTime &&
                (animClimb->m_fBlendAmount >= 1.0f || animClimb->m_fBlendDelta > 0.0f)) {
                float fMoveForceZ = CTimer::GetTimeStep() * ped->m_fMass * 0.3f * 0.008f;
                ped->ApplyMoveForce(0.0f, 0.0f, fMoveForceZ);
            }
        }
        return;
    }
    default: {
        return;
    }
    }

    float fTheTimeStep = pow(0.9f, CTimer::GetTimeStep());
    vecPedMoveSpeed *= (1.0f - fTheTimeStep);
    ped->m_vecMoveSpeed *= fTheTimeStep;
    ped->m_vecMoveSpeed += vecPedMoveSpeed;

    bool bUpdateRotationX = true;
    const CVector& vecPedPosition = ped->GetPosition();
    CVector vecCheckWaterLevelPos = CTimer::GetTimeStep() * ped->m_vecMoveSpeed + ped->GetPosition();
    float fWaterLevel = 0.0f;
    if (!CWaterLevel::GetWaterLevel(vecCheckWaterLevelPos, fWaterLevel, true)) {
        fSubmergeZ = -1.0f;
        bUpdateRotationX = false;
    } else {
        if (m_nSwimState != SWIM_UNDERWATER_SPRINTING || m_fStateChanger < 0.0f) {
            bUpdateRotationX = false;
        } else {
            if (vecPedPosition.z + 0.65f > fWaterLevel && m_fRotationX > 0.7854f) { // todo: LEG_SWING_MAX_ANGLE
                m_nSwimState = SWIM_TREAD;
                m_fStateChanger = 0.0f;
                bUpdateRotationX = false;
            }
        }
    }

    if (bUpdateRotationX) {
        if (m_fRotationX >= 0.0f) {
            if (vecPedPosition.z + 0.65f <= fWaterLevel) {
                if (m_fStateChanger <= 0.001f)
                    m_fStateChanger = 0.0f;
                else
                    m_fStateChanger *= 0.95f;
            } else {
                float fMinimumSpeed = 0.05f * 0.5f;
                if (m_fStateChanger > fMinimumSpeed)
                    m_fStateChanger *= 0.95f;
                if (m_fStateChanger < fMinimumSpeed) {
                    m_fStateChanger += CTimer::GetTimeStep() * 0.002f;
                    m_fStateChanger = std::min(fMinimumSpeed, m_fStateChanger);
                }
                m_fRotationX += CTimer::GetTimeStep() * m_fStateChanger;
                fSubmergeZ = (0.55f - 0.2f) * (m_fRotationX * 4.0f / PI) * 0.75f + 0.2f;
            }
        } else {
            if (vecPedPosition.z - sin(m_fRotationX) + 0.65f <= fWaterLevel) {
                if (m_fStateChanger > 0.001f)
                    m_fStateChanger *= 0.95f;
                else
                    m_fStateChanger = 0.0f;
            } else {
                m_fStateChanger += CTimer::GetTimeStep() * 0.002f;
                if (m_fStateChanger > 0.05f)
                    m_fStateChanger = 0.05f;
            }
            m_fRotationX += CTimer::GetTimeStep() * m_fStateChanger;
        }
    }

    if (fSubmergeZ > 0.0f) {
        fWaterLevel -= (fSubmergeZ + vecPedPosition.z);
        float fTimeStepMoveSpeedZ = fWaterLevel / CTimer::GetTimeStep();
        float fTimeStep = CTimer::GetTimeStep() * 0.1f;
        if (fTimeStepMoveSpeedZ > fTimeStep)
            fTimeStepMoveSpeedZ = fTimeStep;
        if (-fTimeStep > fTimeStepMoveSpeedZ)
            fTimeStepMoveSpeedZ = -fTimeStep;

        fTimeStepMoveSpeedZ -= ped->m_vecMoveSpeed.z;

        fTimeStep = CTimer::GetTimeStepInSeconds();
        if (fTimeStepMoveSpeedZ > fTimeStep)
            fTimeStepMoveSpeedZ = fTimeStep;
        if (-fTimeStep > fTimeStepMoveSpeedZ)
            fTimeStepMoveSpeedZ = -fTimeStep;

        ped->m_vecMoveSpeed.z += fTimeStepMoveSpeedZ;
    }

    auto& pedPos = ped->GetPosition();
    if (pedPos.z < -69.0f) {
        pedPos.z = -69.0f;
        if (ped->m_vecMoveSpeed.z < 0.0f)
            ped->m_vecMoveSpeed.z = 0.0f;
    }
}

// 0x68AA70
void CTaskSimpleSwim::ProcessEffects(CPed* ped) {
    CVector vecParticlePosition = ped->GetForwardVector();
    vecParticlePosition *= 0.4f;
    vecParticlePosition += ped->GetPosition();

    CPlayerPedData* playerData = ped->m_pPlayerData;

    if (playerData)
        vecParticlePosition.z = playerData->m_fWaterHeight;
    else
        vecParticlePosition.z += 0.5f;

    if (m_nSwimState != SWIM_TREAD) {
        DestroyFxSystem();
    } else {
        RwMatrix* mat = RwMatrixCreate();
        mat->pos = *((RwV3d*)&vecParticlePosition);
        RwMatrixUpdate(mat);
        if (!m_pFxSystem) {
            CreateFxSystem(ped, mat);
        }

        if (m_pFxSystem) {
            m_pFxSystem->SetMatrix(mat);
            m_pFxSystem->SetLocalParticles(true);
        }
        RwMatrixDestroy(mat);
    }

    if (m_nSwimState != SWIM_DIVE_UNDERWATER)
        m_bTriggerWaterSplash = false;

    switch (m_nSwimState) {
    case SWIM_SPRINT:
    case SWIM_SPRINTING: {
        const CVector& vecPedUp = ped->GetForward();

        float fRadianAngle = CGeneral::GetAngleBetweenPoints(vecPedUp.x, vecPedUp.y, 0.0f, 0.0f);
        float fLimitedRadianAngle = CGeneral::LimitAngle(fRadianAngle) + 180.0f;

        FxPrtMult_c fxPrtMult(1.0f, 1.0f, 1.0f, 0.2f, 0.4f, 0.0f, 0.5f);
        CVector vecParticleVelocity;
        g_fx.m_Wake->AddParticle(&vecParticlePosition, &vecParticleVelocity, 0.0f, &fxPrtMult, fLimitedRadianAngle, 1.2f, 0.6f, 0);
        ped->m_pedAudio.AddAudioEvent(AE_PED_SWIM_WAKE, 0.0f, 1.0f);

        if (m_nSwimState == SWIM_SPRINTING) {
            RpHAnimHierarchy* animHierarchy = GetAnimHierarchyFromSkinClump(ped->m_pRwClump);
            int32  boneRHandIndex = RpHAnimIDGetIndex(animHierarchy, BONE_R_HAND);
            RwV3d* boneRHandPos   = &RpHAnimHierarchyGetMatrixArray(animHierarchy)[boneRHandIndex].pos;

            int32  boneLHandIndex = RpHAnimIDGetIndex(animHierarchy, BONE_L_HAND);
            RwV3d* boneLHandPos   = &RpHAnimHierarchyGetMatrixArray(animHierarchy)[boneLHandIndex].pos;

            int32  boneRFootIndex = RpHAnimIDGetIndex(animHierarchy, BONE_R_FOOT);
            RwV3d* boneRFootPos   = &RpHAnimHierarchyGetMatrixArray(animHierarchy)[boneRFootIndex].pos;

            int32  boneLFootIndex = RpHAnimIDGetIndex(animHierarchy, BONE_L_FOOT);
            RwV3d* boneLFootPos   = &RpHAnimHierarchyGetMatrixArray(animHierarchy)[boneLFootIndex].pos;

            float fPedPosZ = ped->GetPosition().z;
            const auto AddAudioEvent = [=](RwV3d* bonePos) {
                if (std::fabs(bonePos->z - fPedPosZ) < 0.05f) {
                    auto fx = g_fxMan.CreateFxSystem("water_swim", static_cast<CVector*>(bonePos), nullptr, false);
                    if (fx) {
                        fx->PlayAndKill();
                        ped->m_pedAudio.AddAudioEvent(AE_PED_SWIM_STROKE_SPLASH, 0.0f, 1.0f);
                    }
                }
            };

            AddAudioEvent(boneRHandPos);
            AddAudioEvent(boneLHandPos);
            AddAudioEvent(boneRFootPos);
            AddAudioEvent(boneLFootPos);
        }
        break;
    }
    case SWIM_DIVE_UNDERWATER: {
        if (m_bTriggerWaterSplash) {
            return;
        }
        g_fx.TriggerWaterSplash(vecParticlePosition);
        m_bTriggerWaterSplash = true;
        ped->m_pedAudio.AddAudioEvent(75, 0.0f, 1.0f);
        break;
    }
    case SWIM_UNDERWATER_SPRINTING: {
        uint32 oxygen = 5;
        if (ped->IsPlayer()) {
            oxygen = static_cast<uint32>(((100.0f - playerData->m_fBreath / CStats::GetFatAndMuscleModifier(STAT_MOD_AIR_IN_LUNG) * 100.0f) * 1.0f / 3.0f));
        }
        if ((unsigned)CGeneral::GetRandomNumberInRange(0, 100) < oxygen) {
            RpHAnimHierarchy* hier = GetAnimHierarchyFromSkinClump(ped->m_pRwClump);
            auto* boneSpine1Pos = static_cast<CVector*>(&RpHAnimHierarchyGetMatrixArray(hier)[BONE_SPINE1].pos);
            static FxPrtMult_c fxPrtMult(1.0f, 1.0f, 1.0f, 0.25f, 0.3f, 0.0f, 0.5f);
            CVector vecParticleVelocity = {0.0f, 0.0f, 2.0f};
            g_fx.m_Bubble->AddParticle(boneSpine1Pos, &vecParticleVelocity, 0.0f, &fxPrtMult, -1.0f, 1.2f, 0.6f, false);
        }
        break;
    }
    }
}

// 0x689640
void CTaskSimpleSwim::ProcessControlAI(CPed* ped) {
    m_nSwimState = SWIM_TREAD;
    if (m_pPed) {
        CVector vecPosition(m_pPed->GetPosition() - ped->GetPosition());
        vecPosition.Normalise();
        if (m_fRandomMoveBlendRatio == 0.0f) {
            m_fRandomMoveBlendRatio = (CGeneral::GetRandomNumber() % 4) * 0.5f + 1.5f;
        }

        vecPosition *= m_fRandomMoveBlendRatio;
        m_vecPos = m_pPed->GetPosition() - vecPosition;
    }

    bool bPedGroupSet = false;
    if (m_vecPos != 0.0f) {
        CVector vecPosition(m_vecPos - ped->GetPosition());
        ped->m_fAimingRotation = atan2(-vecPosition.x, vecPosition.y);

        float fMinimum2DDistanceBetweenPeds = 1.0f;
        if (ped->IsPlayer()) {
            fMinimum2DDistanceBetweenPeds = 0.5f;
        }

        if (vecPosition.Magnitude2D() > fMinimum2DDistanceBetweenPeds) {
            m_nSwimState = SWIM_SPRINT;
            if (m_pPed) {
                CPedGroup* pedGroup = CPedGroups::GetPedsGroup(ped);
                if (pedGroup && pedGroup->GetMembership().GetLeader() == m_pPed) {
                    bPedGroupSet = true;
                    auto swimTask = m_pPed->GetIntelligence()->GetTaskSwim();
                    if (swimTask && swimTask->m_nSwimState == SWIM_SPRINTING) {
                        CVector distance = m_vecPos - ped->GetPosition();
                        if (distance.Magnitude() > 5.0f) {
                            m_nSwimState = SWIM_SPRINTING;
                        }
                    }
                }
            } else if (m_fAnimSpeed > 1.0f) {
                if (vecPosition.Magnitude2D() > 2.0f) {
                    m_nSwimState = SWIM_SPRINTING;
                }
            }
        }
    }

    CVector vecPosition(m_vecPos - ped->GetPosition());
    if (m_pPed && m_pPed->bIsStanding && !m_pPed->physicalFlags.bSubmergedInWater ||
        ped->bIsDyingStuck && !m_pPed->physicalFlags.bSubmergedInWater && vecPosition.Magnitude2D() < 1.0f) {
        if (!((ped->m_nRandomSeedUpperByte + CTimer::GetFrameCounter() - 4) & 0x7F)) {
            if (CTaskSimpleClimb::TestForClimb(ped, m_pClimbPos, m_fAngle, m_nSurfaceType, true)) {
                m_nSwimState = SWIM_BACK_TO_SURFACE;
            }
        }
    }
    m_fAimingRotation = 0.0f;
    m_fUpperTorsoRotationX = 0.0f;

    if (!bPedGroupSet && !ped->IsPlayer() && m_fAnimSpeed < 0.0f)
        ped->m_vecAnimMovingShiftLocal *= 0.5f;
}

// 0x688A90
void CTaskSimpleSwim::ProcessControlInput(CPlayerPed* ped) {
    CVector vecPedWalk;
    CPlayerPedData* playerData = ped->m_pPlayerData;
    if (!m_bFinishedBlending || !m_bAnimBlockRefAdded) {
        playerData->m_fMoveBlendRatio = 0.0f;
        return;
    }

    CPad* pad = ped->GetPadFromPlayer();
    vecPedWalk.x = (float)pad->GetPedWalkLeftRight() / 128.0f;
    vecPedWalk.y = (float)pad->GetPedWalkUpDown() / 128.0f;

    float fWalkMagnitude = vecPedWalk.Magnitude2D();
    if (m_nSwimState < SWIM_SPRINTING) {
        if (pad->JumpJustDown()) {
            m_nSwimState = SWIM_BACK_TO_SURFACE;
        } else if (pad->WeaponJustDown(ped)) {
            m_nSwimState = SWIM_DIVE_UNDERWATER;
            ped->m_pPlayerData->m_fMoveBlendRatio = 0.0f;
        }
    }

    switch (m_nSwimState) {
    case SWIM_TREAD:
    case SWIM_SPRINT:
    case SWIM_SPRINTING: {
        float pedWalkX = 0.0f;
        bool bPlayerUse2PlayerControls = false;
        if (CGameLogic::IsPlayerUse2PlayerControls(ped)) {
            bPlayerUse2PlayerControls = true;
            pedWalkX = vecPedWalk.x;
            if (fWalkMagnitude > 0) {
                float negativePedWalkX = -pedWalkX;
                float fRadianAngle = CGeneral::GetRadianAngleBetweenPoints(0.0f, 0.0f, negativePedWalkX, vecPedWalk.y) - TheCamera.m_fOrientation;
                float fLimitedRadianAngle = CGeneral::LimitRadianAngle(fRadianAngle);

                CVector vecPedWalkDirection(0.0f, -sin(fLimitedRadianAngle), cos(fLimitedRadianAngle));
                if (fLimitedRadianAngle <= ped->m_fCurrentRotation + DegreesToRadians(180.0f)) {
                    if (fLimitedRadianAngle < ped->m_fCurrentRotation - DegreesToRadians(180.0f)) {
                        fLimitedRadianAngle += DegreesToRadians(360.0f);
                    }
                } else {
                    fLimitedRadianAngle -= DegreesToRadians(360.0f);
                }

                float fCurrenRotation = fLimitedRadianAngle - ped->m_fCurrentRotation;
                if (fCurrenRotation <= 1.0f) {
                    if (fCurrenRotation < -1.0f)
                        fCurrenRotation = -1.0f;
                } else {
                    fCurrenRotation = 1.0f;
                }

                ped->m_fAimingRotation = fCurrenRotation * (CTimer::GetTimeStep() * 0.08f) + ped->m_fCurrentRotation;
                if (ped->m_fAimingRotation <= DegreesToRadians(180.0f)) {
                    if (ped->m_fAimingRotation < -DegreesToRadians(180.0f)) {
                        ped->m_fAimingRotation += DegreesToRadians(360.0f);
                    }
                } else {
                    ped->m_fAimingRotation -= DegreesToRadians(360.0f);
                }
                if (CGameLogic::IsPlayerAllowedToGoInThisDirection(ped, vecPedWalkDirection.x, vecPedWalkDirection.y, vecPedWalkDirection.z, 0.0f)) {
                    CMatrixLink* pPedMatrix = ped->m_matrix;
                    pedWalkX =
                        (vecPedWalkDirection.y * pPedMatrix->GetRight().y + vecPedWalkDirection.x * pPedMatrix->GetRight().x + pPedMatrix->GetRight().z * 0.0f) * fWalkMagnitude;
                    vecPedWalk.y = -((vecPedWalkDirection.y * pPedMatrix->GetForward().y + pPedMatrix->GetForward().z * 0.0f + vecPedWalkDirection.x * pPedMatrix->GetForward().x) * fWalkMagnitude);
                } else {
                    pedWalkX = 0.0f;
                    fWalkMagnitude = 0.0f;
                    vecPedWalk.y = 0.0f;
                }
            }
        } else // if CGameLogic::IsPlayerUse2PlayerControls(ped) == false
        {
            pedWalkX = vecPedWalk.x;
        }

        float fRotation = pedWalkX;

        if (!CCamera::m_bUseMouse3rdPerson) {
            if (fWalkMagnitude <= 0.0f) {
                if (playerData->m_fMoveBlendRatio > 0.0f) {
                    playerData->m_fMoveBlendRatio -= CTimer::GetTimeStep() * 0.05f;
                    if (playerData->m_fMoveBlendRatio < 0.0f) {
                        playerData->m_fMoveBlendRatio = 0.0f;
                    }
                }
            } else {
                bool bUpdateMoveBlendRatio = false;
                if (!bPlayerUse2PlayerControls) {
                    ped->m_fAimingRotation += CTimer::GetTimeStep() * -0.03f * pedWalkX;
                    if (ped->m_fAimingRotation <= DegreesToRadians(180.0f)) {
                        if (ped->m_fAimingRotation < -DegreesToRadians(180.0f)) {
                            ped->m_fAimingRotation += DegreesToRadians(360.0f);
                        }
                    } else {
                        ped->m_fAimingRotation -= DegreesToRadians(360.0f);
                    }
                    float pedWalkY = vecPedWalk.y;
                    float negativePedWalkY = 0.0f;
                    if (m_nSwimState) {
                        if (pedWalkY > 0.0f) {
                            fWalkMagnitude -= vecPedWalk.y;
                        }
                    } else {
                        fWalkMagnitude = -pedWalkY;
                    }

                    if (fWalkMagnitude < 0.0f) {
                        fWalkMagnitude = 0.0f;
                    }

                    bUpdateMoveBlendRatio = true;
                }

                if (bPlayerUse2PlayerControls || bUpdateMoveBlendRatio) {
                    float fTimeStep = CTimer::GetTimeStep() * 0.07f;
                    if (fWalkMagnitude - playerData->m_fMoveBlendRatio <= fTimeStep) {
                        playerData->m_fMoveBlendRatio = fWalkMagnitude;
                    } else {
                        playerData->m_fMoveBlendRatio += fTimeStep;
                    }
                }
            }
        } else {
            const auto& camFront = CCamera::GetActiveCamera().m_vecFront;
            ped->m_fAimingRotation = std::atan2(-camFront.x, camFront.y);
            if (TheCamera.GetLookDirection() != 3) {
                ped->m_fAimingRotation += DegreesToRadians(180.0f);
                if (ped->m_fAimingRotation > DegreesToRadians(180.0f)) {
                    ped->m_fAimingRotation -= DegreesToRadians(360.0f);
                }
            }

            float negativePedWalkY = -vecPedWalk.y;
            float fTimeStep = CTimer::GetTimeStep() * 0.07f;
            if (negativePedWalkY - playerData->m_fMoveBlendRatio > fTimeStep) {
                playerData->m_fMoveBlendRatio += fTimeStep;
            } else {
                playerData->m_fMoveBlendRatio = negativePedWalkY;
            }

            fRotation = -(ped->m_fAimingRotation - ped->m_fCurrentRotation);
            if (fRotation <= DegreesToRadians(180.0f)) {
                if (fRotation < -DegreesToRadians(180.0f)) {
                    fRotation = DegreesToRadians(360.0f) - (ped->m_fAimingRotation - ped->m_fCurrentRotation);
                }

            } else {
                fRotation -= DegreesToRadians(360.0f);
            }

            fRotation *= 10.0f;
            fRotation = std::max(-1.0f, fRotation);
            fRotation = std::min(1.0f, fRotation);
        }

        m_fAimingRotation += CTimer::GetTimeStep() * 0.08f * fRotation;

        if (m_nSwimState == SWIM_SPRINTING) {
            m_fTurningRotationY += CTimer::GetTimeStep() * 0.04f * fRotation;
        } else if (m_nSwimState == SWIM_SPRINT) {
            m_fUpperTorsoRotationX += fabs(pedWalkX) * CTimer::GetTimeStep() * 0.04f;
        }

        if (m_nSwimState == SWIM_SPRINTING) {
            float fWaterLevel1 = 0.0f;
            float fWaterLevel2 = 0.0f;
            CVector distance = ped->GetPosition() - ped->GetForward();
            CVector position = ped->GetPosition() + ped->GetForward();
            if (CWaterLevel::GetWaterLevel(position, fWaterLevel1, true)) {
                if (CWaterLevel::GetWaterLevel(distance, fWaterLevel2, true)) {
                    m_fRotationX = std::atan2(fWaterLevel1 - fWaterLevel2, 2.0f) * 1.0f;
                }
            }
        }

        if (ped->ControlButtonSprint(SPRINT_WATER) < 1.0f) {
            m_nSwimState = static_cast<eSwimState>(ped->m_pPlayerData->m_fMoveBlendRatio > 0.5f);
        } else {
            m_nSwimState = SWIM_SPRINTING;
        }
        break;
    }
    case SWIM_DIVE_UNDERWATER: {
        if (m_fStateChanger > 0.0f) {
            m_fStateChanger = 0.0f;
        }
        break;
    }
    case SWIM_UNDERWATER_SPRINTING: {
        float fUpperTorsoRotationX = 0.0f;
        if (CCamera::m_bUseMouse3rdPerson) {
            CVector vecActiveCamFront = CCamera::GetActiveCamera().m_vecFront;
            if (TheCamera.GetLookDirection() != 3) {
                vecActiveCamFront.x *= -1.0f;
                vecActiveCamFront.y *= -1.0f;
                vecActiveCamFront.z = 0.0f;
            }

            ped->m_fAimingRotation = std::atan2(-vecActiveCamFront.x, vecActiveCamFront.y);
            float fRotation = -(ped->m_fAimingRotation - ped->m_fCurrentRotation);
            if (fRotation <= DegreesToRadians(180.0f)) {
                if (fRotation < -DegreesToRadians(180.0f))
                    fRotation += DegreesToRadians(360.0f);
            } else {
                fRotation -= DegreesToRadians(360.0f);
            }

            fRotation *= 10.0f;
            fRotation = std::max(-1.0f, fRotation);
            fRotation = std::min(1.0f, fRotation);

            m_fTurningRotationY += CTimer::GetTimeStep() * 0.04f * fRotation;
            m_fAimingRotation   += CTimer::GetTimeStep() * 0.08f * fRotation;

            float fRotationX = (std::asin(vecActiveCamFront.z) - m_fRotationX) * 10.0f;
            fRotationX = std::max(-1.0f, fRotationX);
            fRotationX = std::min(1.0f, fRotationX);
            if (m_fStateChanger == 0.0f || fRotationX > 0.0f) {
                m_fRotationX += CTimer::GetTimeStepInSeconds() * fRotationX;
            }
            fUpperTorsoRotationX = m_fTurningRotationY / 0.5f;
            if (fUpperTorsoRotationX > 1.0f || fUpperTorsoRotationX >= -1.0f) {
                if (fUpperTorsoRotationX > 1.0f) {
                    fUpperTorsoRotationX = 1.0f;
                }
            } else {
                fUpperTorsoRotationX = -1.0f;
            }

            fUpperTorsoRotationX = fRotationX + fUpperTorsoRotationX * -0.08f * fRotation;
            if (fUpperTorsoRotationX <= 1.0f) {
                if (fUpperTorsoRotationX < -1.0f) {
                    fUpperTorsoRotationX = -1.0f;
                }
            } else {
                fUpperTorsoRotationX = 1.0f;
            }

            m_fUpperTorsoRotationX += CTimer::GetTimeStep() * -0.08f * fUpperTorsoRotationX;
        } else {
            if (fWalkMagnitude > 0.0f) {
                float fNormalizedWalkMagnitude = 1.0f / fWalkMagnitude;
                vecPedWalk.x = vecPedWalk.x * fNormalizedWalkMagnitude;
                float pedWalkY = fNormalizedWalkMagnitude * vecPedWalk.y;
                ped->m_fAimingRotation += CTimer::GetTimeStep() * -0.03f * vecPedWalk.x;

                if (ped->m_fAimingRotation <= DegreesToRadians(180.0f)) {
                    if (ped->m_fAimingRotation < -DegreesToRadians(180.0f)) {
                        ped->m_fAimingRotation += DegreesToRadians(360.0f);
                    }
                } else {
                    ped->m_fAimingRotation -= DegreesToRadians(360.0f);
                }

                m_fTurningRotationY += CTimer::GetTimeStep() * 0.04f * vecPedWalk.x;
                m_fAimingRotation   += CTimer::GetTimeStep() * 0.08f * vecPedWalk.x;
                if (m_fStateChanger == 0.0f || pedWalkY > 0.0f) {
                    m_fRotationX += CTimer::GetTimeStepInSeconds() * pedWalkY;
                }

                fUpperTorsoRotationX = m_fTurningRotationY / 0.5f;
                if (fUpperTorsoRotationX > 1.0f || fUpperTorsoRotationX >= -1.0f) {
                    if (fUpperTorsoRotationX > 1.0f) {
                        fUpperTorsoRotationX = 1.0f;
                    }
                } else {
                    fUpperTorsoRotationX = -1.0f;
                }

                fUpperTorsoRotationX = pedWalkY + fUpperTorsoRotationX * -0.08f * vecPedWalk.x;
                if (fUpperTorsoRotationX <= 1.0f) {
                    if (fUpperTorsoRotationX < -1.0f) {
                        fUpperTorsoRotationX = -1.0f;
                    }
                } else {
                    fUpperTorsoRotationX = 1.0f;
                }

                m_fUpperTorsoRotationX += CTimer::GetTimeStep() * -0.08f * fUpperTorsoRotationX;
            }
        }

        m_fRotationX += CTimer::GetTimeStep() * 0.001f;
        m_fRotationX = clamp<float>(m_fRotationX, -DegreesToRadians(80.0f), DegreesToRadians(80.0f));
        // BUG: it should be m_fTimeCanRun <= 0.1f
        if (ped->m_pPlayerData->m_fTimeCanRun <= 0.0f)
            ped->m_pPlayerData->m_fTimeCanRun = 0.1f;
        ped->ControlButtonSprint(SPRINT_UNDERWATER);
        break;
    }
    }

    float fRotation = 0.95f;
    if (m_nSwimState == SWIM_UNDERWATER_SPRINTING || m_nSwimState == SWIM_SPRINTING) {
        fRotation = 0.95f;
    }

    if (m_fTurningRotationY > 0.01f || m_fTurningRotationY < -0.01f) {
        m_fTurningRotationY *= pow(fRotation, CTimer::GetTimeStep());
    } else {
        m_fTurningRotationY = 0.0f;
    }

    if (m_nSwimState != SWIM_UNDERWATER_SPRINTING && m_nSwimState != SWIM_SPRINTING) {
        if (m_fRotationX > 0.01f || m_fRotationX < -0.01f) {
            m_fRotationX *= pow(fRotation, CTimer::GetTimeStep());
        } else {
            m_fRotationX = 0.0f;
        }
    }

    if (m_nSwimState == SWIM_DIVE_UNDERWATER || m_nSwimState == SWIM_BACK_TO_SURFACE)
        fRotation = 0.95f;
    else
        fRotation = 0.92f;

    if (m_fAimingRotation > 0.01f || m_fAimingRotation < -0.01f || m_fUpperTorsoRotationX > 0.01f || m_fUpperTorsoRotationX < -0.01f) {
        float fTimeStepRotation = pow(fRotation, CTimer::GetTimeStep());
        m_fAimingRotation *= fTimeStepRotation;
        m_fUpperTorsoRotationX *= fTimeStepRotation;
    } else {
        m_fAimingRotation = 0.0f;
        m_fUpperTorsoRotationX = 0.0f;
    }

    if (m_nSwimState == SWIM_SPRINT)
        ped->HandleSprintEnergy(false, 0.5f);
    else if (m_nSwimState != SWIM_SPRINTING)
        ped->HandleSprintEnergy(false, 1.0f);
}

// 0x68A9F0
void CTaskSimpleSwim::CreateFxSystem(CPed* ped, RwMatrix* mat) {
    CVector point = {0.0f, 0.0f, 0.0f};
    m_pFxSystem = g_fxMan.CreateFxSystem("water_ripples", &point, mat, false);
    if (m_pFxSystem) {
        m_pFxSystem->CopyParentMatrix();
        m_pFxSystem->Play();
    }
}

// 0x68AA50
void CTaskSimpleSwim::DestroyFxSystem() {
    FxSystem_c::SafeKillAndClear(m_pFxSystem);
}
