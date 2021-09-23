#include "StdInc.h"

#include "CTaskSimpleSwim.h"

float& CTaskSimpleSwim::SWIM_DIVE_UNDER_ANGLE = *reinterpret_cast<float*>(0x8D2FC4);
float& CTaskSimpleSwim::SWIM_STOP_TIME = *reinterpret_cast<float*>(0x8D2FC0);

void CTaskSimpleSwim::InjectHooks() {
    ReversibleHooks::Install("CTaskSimpleSwim", "CTaskSimpleSwim", 0x688930, &CTaskSimpleSwim::Constructor);
    ReversibleHooks::Install("CTaskSimpleSwim", "Clone", 0x68B050, &CTaskSimpleSwim::Clone_Reversed);
    ReversibleHooks::Install("CTaskSimpleSwim", "GetTaskType", 0x6889F0, &CTaskSimpleSwim::GetId_Reversed);
    ReversibleHooks::Install("CTaskSimpleSwim", "ProcessPed", 0x68B1C0, &CTaskSimpleSwim::ProcessPed_Reversed);
    ReversibleHooks::Install("CTaskSimpleSwim", "MakeAbortable", 0x68B100, &CTaskSimpleSwim::MakeAbortable_Reversed);
    ReversibleHooks::Install("CTaskSimpleSwim", "ApplyRollAndPitch", 0x68A8E0, &CTaskSimpleSwim::ApplyRollAndPitch);
    ReversibleHooks::Install("CTaskSimpleSwim", "ProcessSwimAnims", 0x6899F0, &CTaskSimpleSwim::ProcessSwimAnims);
    ReversibleHooks::Install("CTaskSimpleSwim", "ProcessSwimmingResistance", 0x68A1D0, &CTaskSimpleSwim::ProcessSwimmingResistance);
    ReversibleHooks::Install("CTaskSimpleSwim", "ProcessEffects", 0x68AA70, &CTaskSimpleSwim::ProcessEffects);
    ReversibleHooks::Install("CTaskSimpleSwim", "ProcessControlAI", 0x689640, &CTaskSimpleSwim::ProcessControlAI);
    ReversibleHooks::Install("CTaskSimpleSwim", "ProcessControlInput", 0x688A90, &CTaskSimpleSwim::ProcessControlInput);
    ReversibleHooks::Install("CTaskSimpleSwim", "CreateFxSystem", 0x68A9F0, &CTaskSimpleSwim::CreateFxSystem);
    ReversibleHooks::Install("CTaskSimpleSwim", "DestroyFxSystem", 0x68AA50, &CTaskSimpleSwim::DestroyFxSystem);
}

CTaskSimpleSwim::CTaskSimpleSwim(CVector* pPosition, CPed* pPed) : CTaskSimple() {
    m_bFinishedBlending = false;
    m_bAnimBlockRefAdded = false;
    m_fAnimSpeed = -1.0f;
    m_vecPos = CVector(0.0f, 0.0f, 0.0f);
    m_pPed = pPed;
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

    if (pPosition)
        m_vecPos = *pPosition;

    if (pPed)
        pPed->RegisterReference(reinterpret_cast<CEntity**>(&m_pPed));

    m_pFxSystem = nullptr;
    m_bTriggerWaterSplash = false;
    m_fRandomMoveBlendRatio = 0.0f;
}


CTaskSimpleSwim::~CTaskSimpleSwim() {
    if (m_bAnimBlockRefAdded) {
        CAnimBlock* pAnimBlock = CAnimManager::ms_aAnimAssocGroups[ANIM_GROUP_SWIM].m_pAnimBlock;
        CAnimManager::RemoveAnimBlockRef(pAnimBlock - CAnimManager::ms_aAnimBlocks);
    }

    if (m_pEntity)
        m_pEntity->CleanUpOldReference(&m_pEntity);

    if (m_pPed)
        m_pPed->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_pPed));
}

// 0x688930
CTaskSimpleSwim* CTaskSimpleSwim::Constructor(CVector* pPosition, CPed* pPed) {
    this->CTaskSimpleSwim::CTaskSimpleSwim(pPosition, pPed);
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
bool CTaskSimpleSwim::MakeAbortable(class CPed* ped, eAbortPriority priority, const CEvent* event)
{
    return MakeAbortable_Reversed(ped, priority, event);
}

// 0x68B1C0
bool CTaskSimpleSwim::ProcessPed(CPed* pPed)
{
    return ProcessPed_Reversed(pPed);
}

CTask* CTaskSimpleSwim::Clone_Reversed() {
    return new CTaskSimpleSwim(&m_vecPos, m_pPed);
}

bool CTaskSimpleSwim::MakeAbortable_Reversed(class CPed* ped, eAbortPriority priority, const CEvent* event)
{
    const auto* damageEvent = static_cast<const CEventDamage*>(event);

    if (priority == ABORT_PRIORITY_IMMEDIATE)
    {
        CAnimManager::BlendAnimation(ped->m_pRwClump, ped->m_nAnimGroup, ANIM_ID_IDLE, 1000.0f);
        ped->m_nMoveState = PEDMOVE_STILL;
        ped->m_nSwimmingMoveState = PEDMOVE_STILL;

        if (m_AnimID != ANIM_ID_NO_ANIMATION_SET)
        {
            auto pAnimAssociation = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, m_AnimID);
            if (pAnimAssociation)
            {
                pAnimAssociation->m_fBlendDelta = -1000.0f;
            }
        }

        ped->RestoreHeadingRate();
    }
    else if (!event || event->GetEventPriority() < 71
        && (event->GetEventType() != EVENT_DAMAGE || !damageEvent->m_damageResponse.m_bHealthZero || !damageEvent->m_bAddToEventGroup))
    {
        return false;
    }

    if (m_pFxSystem)
    {
        m_pFxSystem->Kill();
        m_pFxSystem = nullptr;
    }
    return true;
}

bool CTaskSimpleSwim::ProcessPed_Reversed(CPed* pPed)
{
    if (m_pEntity)
    {
        CAnimManager::BlendAnimation(pPed->m_pRwClump, pPed->m_nAnimGroup, ANIM_ID_IDLE, 8.0f);
        pPed->m_nMoveState = PEDMOVE_STILL;
        pPed->m_nSwimmingMoveState = PEDMOVE_STILL;

        FxSystem_c* pFxSystem = m_pFxSystem;
        if (pFxSystem)
        {
            pFxSystem->Kill();
            m_pFxSystem = nullptr;
        }
        return true;
    }

    if (m_fSwimStopTime > CTaskSimpleSwim::SWIM_STOP_TIME || pPed->bIsStanding)
    {
        CAnimBlendAssociation* pAnimAssociation = nullptr;
        if (m_AnimID != ANIM_ID_NO_ANIMATION_SET)
        {
            pAnimAssociation = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, m_AnimID);
        }
        AnimationId animId = ANIM_ID_IDLE;
        pPed->m_nSwimmingMoveState = PEDMOVE_STILL;
        pPed->m_nMoveState = PEDMOVE_STILL;
        if (pAnimAssociation)
        {
            if (pAnimAssociation->m_nAnimId == ANIM_ID_CLIMB_JUMP)
                pAnimAssociation->m_nFlags |= ANIM_FLAG_UNLOCK_LAST_FRAME;
            else
                pAnimAssociation->m_fBlendDelta = -4.0f;
            if (m_AnimID == ANIM_ID_SWIM_BREAST)
            {
                animId = ANIM_ID_WALK;
                pPed->m_nSwimmingMoveState = PEDMOVE_WALK;
                pPed->m_nMoveState = PEDMOVE_WALK;
            }
            else if (m_AnimID == ANIM_ID_SWIM_CRAWL)
            {
                animId = ANIM_ID_RUN;
                pPed->m_nSwimmingMoveState = PEDMOVE_RUN;
                pPed->m_nMoveState = PEDMOVE_RUN;
            }
        }
        CAnimManager::BlendAnimation(pPed->m_pRwClump, pPed->m_nAnimGroup, animId, 4.0f);
        pPed->RestoreHeadingRate();
        FxSystem_c* pFxSystem = m_pFxSystem;
        if (pFxSystem) {
            pFxSystem->Kill();
            m_pFxSystem = nullptr;
        }
        return true;
    }

    pPed->bIsInTheAir = false;

    if (pPed->IsPlayer())
    {
        if (m_nTimeStep && m_nSwimState != SWIM_UNDERWATER_SPRINTING)
        {
            ProcessControlAI(pPed);
            uint32 swimmingTimeStep = static_cast<uint32>((CTimer::ms_fTimeStep / 50.0f) * 1000.0f);
            if (m_nTimeStep <= swimmingTimeStep)
                m_nTimeStep = 0;
            else
                m_nTimeStep -= swimmingTimeStep;

            CVector vecOut = m_vecPos - pPed->GetPosition();
            pPed->m_pPlayerData->m_fMoveBlendRatio = vecOut.Magnitude();
            CPlayerPedData * pPlayerData = pPed->m_pPlayerData;
            if (pPlayerData->m_fMoveBlendRatio < 0.5f) {
                pPlayerData->m_fMoveBlendRatio = 0.0f;
                CAnimManager::BlendAnimation(pPed->m_pRwClump, pPed->m_nAnimGroup, ANIM_ID_IDLE, 4.0f);
                pPed->RestoreHeadingRate();
                DestroyFxSystem();
                return true;
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
            CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, ANIM_ID_SWIM_UNDER);
            if (pAnimAssociation)
            {
                fDecreaseAirMultiplicator = pAnimAssociation->m_fSpeed * pAnimAssociation->m_fBlendAmount + 1.0f;
            }
        }

        auto* pPlayerPed = reinterpret_cast<CPlayerPed*> (pPed);
        pPlayerPed->HandlePlayerBreath(bDecreaseAir, fDecreaseAirMultiplicator);
        if (m_pPed)
        {
            if (m_nSwimState != SWIM_UNDERWATER_SPRINTING)
            {
              CPlayerPedData * pPlayerData = pPed->m_pPlayerData;
                if (CStats::GetFatAndMuscleModifier(STAT_MOD_AIR_IN_LUNG) * 0.5f > pPlayerData->m_fBreath)
                    pPed->Say(356, 0, 1.0f, 0, 0, 0);
            }
        }
        pPed->SetMoveState(PEDMOVE_NONE);
    }
    else
    {
        ProcessControlAI(pPed);

        if (m_nSwimState == SWIM_UNDERWATER_SPRINTING) {
            CPedDamageResponseCalculator damageCalculator(nullptr, CTimer::ms_fTimeStep, WEAPON_DROWNING, PED_PIECE_TORSO, false);
            CEventDamage eventDamage(nullptr, CTimer::GetTimeInMS(), WEAPON_DROWNING, PED_PIECE_TORSO, 0, false, pPed->bInVehicle);
            if (eventDamage.AffectsPed(pPed))
                damageCalculator.ComputeDamageResponse(pPed, &eventDamage.m_damageResponse, true);
            else
                eventDamage.m_damageResponse.m_bDamageCalculated = true;
            pPed->m_pIntelligence->m_eventGroup.Add(&eventDamage, false);
        }
    }
    ProcessSwimAnims(pPed);
    ProcessSwimmingResistance(pPed);
    ProcessEffects(pPed);
    return false;
}

// 0x68A8E0
void CTaskSimpleSwim::ApplyRollAndPitch(CPed* pPed)
{
    LimbOrientation theLimbOrientation;
    theLimbOrientation.m_fYaw = m_fAimingRotation;
    theLimbOrientation.m_fPitch = m_fUpperTorsoRotationX;
    pPed->m_pedIK.RotateTorso(pPed->m_apBones[PED_NODE_UPPER_TORSO], theLimbOrientation, rwCOMBINEREPLACE);
    RwObject* pRwObject = pPed->m_pRwObject;
    if (pRwObject)
    {
        CMatrix pedMatrix(pPed->GetModellingMatrix(), false);
        CMatrix rotationMatrix;
        rotationMatrix.SetTranslate(CVector(0.0f, 0.0f, 0.0f));
        rotationMatrix.RotateY(m_fTurningRotationY);
        rotationMatrix.RotateX(m_fRotationX);
        pedMatrix *= rotationMatrix;
        pedMatrix.UpdateRW();
        pPed->UpdateRwFrame();
    }
}

// 0x6899F0
void CTaskSimpleSwim::ProcessSwimAnims(CPed* pPed)
{
    auto* pPlayerPed = (CPlayerPed*)pPed;
    CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, ANIM_ID_SWIM_TREAD);
    if (m_bFinishedBlending) {
        if (pAnimAssociation
            && pAnimAssociation->m_fBlendAmount < 1.0f
            && pAnimAssociation->m_fBlendDelta <= 0.0f) {
            CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_SWIM_TREAD, 8.0f);
        }
    }
    else {
        if (pAnimAssociation
            || (pAnimAssociation = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_SWIM_TREAD, 8.0f)) != nullptr)
        {
            if (pAnimAssociation->m_fBlendAmount >= 1.0f)
                m_bFinishedBlending = true;
        }
        RpAnimBlendClumpSetBlendDeltas(pPlayerPed->m_pRwClump, 0x10, -8.0f);
        FxSystem_c* pFixSystem = pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_pFxSystem;
        if (pFixSystem)
        {
            pFixSystem->Kill();
            pPlayerPed->m_aWeapons[pPlayerPed->m_nActiveWeaponSlot].m_pFxSystem = nullptr;
        }

        if (pPlayerPed->IsPlayer() && !m_nSwimState)
        {
            CVector& vecPos = pPlayerPed->GetPosition();
            float waterLevel = 0.0f;
            if (CWaterLevel::GetWaterLevel(vecPos.x, vecPos.y, vecPos.z, &waterLevel, 1, nullptr))
            {
                if (waterLevel - 2.0f > vecPos.z)
                    m_nSwimState = SWIM_UNDERWATER_SPRINTING;
            }
        }
    }

    if (!m_bAnimBlockRefAdded) {
        CAnimBlock* pAnimBlock = CAnimManager::ms_aAnimAssocGroups[ANIM_GROUP_SWIM].m_pAnimBlock;
        if (!pAnimBlock) {
            char* pBlockName = CAnimManager::GetAnimBlockName(ANIM_GROUP_SWIM);
            pAnimBlock = CAnimManager::GetAnimationBlock(pBlockName);
        }
        if (pAnimBlock->bLoaded) {
            CAnimManager::AddAnimBlockRef(pAnimBlock - CAnimManager::ms_aAnimBlocks);
            m_bAnimBlockRefAdded = true;
        }
        else {
            CStreaming::RequestModel(pAnimBlock - CAnimManager::ms_aAnimBlocks + RESOURCE_ID_IFP, STREAMING_KEEP_IN_MEMORY);
        }
    }

    if (m_bFinishedBlending && m_bAnimBlockRefAdded) {
        switch (m_nSwimState){
        case SWIM_TREAD: {
            if (m_AnimID != ANIM_ID_SWIM_TREAD)
            {
                CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, ANIM_ID_SWIM_BREAST);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -1.0f;
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, ANIM_ID_SWIM_CRAWL);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -1.0f;
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, ANIM_ID_SWIM_DIVE_UNDER);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -4.0f;
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, ANIM_ID_SWIM_UNDER);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -2.0f;
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, ANIM_ID_SWIM_GLIDE);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -2.0f;
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, ANIM_ID_SWIM_JUMPOUT);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -4.0f;
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, ANIM_ID_CLIMB_JUMP);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -4.0f;
                m_AnimID = ANIM_ID_SWIM_TREAD;
            }
            break;
        }
        case SWIM_SPRINT: {
            if (m_AnimID == ANIM_ID_SWIM_BREAST)
            {
                CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, ANIM_ID_SWIM_BREAST);
                if (!pAnimAssociation)
                {
                    m_nSwimState = SWIM_TREAD;
                    break;
                }
                if (pPlayerPed->IsPlayer())
                {
                    pAnimAssociation->m_fSpeed = pPlayerPed->m_pPlayerData->m_fMoveBlendRatio;
                }
                else if (m_fAnimSpeed > 0.0f && m_fAnimSpeed <= 1.0f)
                {
                    pAnimAssociation->m_fSpeed = m_fAnimSpeed;
                }
            }
            else
            {
                CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_SWIM, ANIM_ID_SWIM_BREAST, 2.0f);
                m_AnimID = ANIM_ID_SWIM_BREAST;
            }
            break;
        }
        case SWIM_SPRINTING:
        {
            if (m_AnimID == ANIM_ID_SWIM_CRAWL)
            {
                CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, ANIM_ID_SWIM_CRAWL);
                if (!pAnimAssociation)
                {
                    m_nSwimState = SWIM_TREAD;
                    break;
                }
                if (pPlayerPed->m_pPlayerData)
                {
                    float buttonSprintResults = pPlayerPed->GetButtonSprintResults(SPRINT_WATER);
                    pAnimAssociation->m_fSpeed = static_cast <float> (std::max(1.0f, buttonSprintResults));
                }
                else if (m_fAnimSpeed > 1.0)
                {
                    float taskAnimSpeed = static_cast <float> (m_fAnimSpeed - 1.0f);
                    pAnimAssociation->m_fSpeed = static_cast <float> (std::min(1.5f, taskAnimSpeed));
                }
            }
            else
            {
                CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_SWIM, ANIM_ID_SWIM_CRAWL, 2.0f);
                m_AnimID = ANIM_ID_SWIM_CRAWL;
            }
            break;
        }
        case SWIM_DIVE_UNDERWATER:
        {
            if (m_AnimID == ANIM_ID_SWIM_DIVE_UNDER)
            {
                CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, ANIM_ID_SWIM_DIVE_UNDER);
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
                CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_SWIM, ANIM_ID_SWIM_DIVE_UNDER, 8.0f);
                m_AnimID = ANIM_ID_SWIM_DIVE_UNDER;
            }
            break;
        }
        case SWIM_UNDERWATER_SPRINTING:
        {
            if ((m_AnimID == ANIM_ID_SWIM_UNDER || m_AnimID == ANIM_ID_SWIM_GLIDE) && m_fStateChanger >= 0.0f)
            {
                if (pPlayerPed->m_pPlayerData && pPlayerPed->GetButtonSprintResults(SPRINT_UNDERWATER) >= 1.0f)
                {
                    CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, ANIM_ID_SWIM_UNDER);
                    if (!pAnimAssociation
                        || pAnimAssociation->m_fBlendDelta < 0.0f
                        || pAnimAssociation->m_fBlendAmount == 0.0f)
                    {
                        pAnimAssociation = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_SWIM, ANIM_ID_SWIM_UNDER, 4.0f);
                    }
                    if (pAnimAssociation->m_pHierarchy->m_fTotalTime == pAnimAssociation->m_fCurrentTime)
                    {
                        pAnimAssociation->Start(0.0f);
                        float buttonSprintResults = pPlayerPed->GetButtonSprintResults(SPRINT_UNDERWATER);
                        pAnimAssociation->m_fSpeed = static_cast <float> (std::max(0.7f, buttonSprintResults));
                    }
                    m_AnimID = ANIM_ID_SWIM_UNDER;
                }
                else
                {
                    CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, ANIM_ID_SWIM_GLIDE);
                    if (!pAnimAssociation
                        || pAnimAssociation->m_fBlendDelta < 0.0f
                        || pAnimAssociation->m_fBlendAmount == 0.0f)
                    {
                        CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_SWIM, ANIM_ID_SWIM_GLIDE, 4.0f);
                    }
                    m_AnimID = ANIM_ID_SWIM_GLIDE;
                }
            }
            else
            {
                CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, ANIM_ID_SWIM_UNDER);
                if (pAnimAssociation)
                {
                    if (m_fStateChanger < 0.0f && pAnimAssociation->m_fBlendAmount >= 0.99f)
                    {
                        if (m_fStateChanger > -2.0f)
                        {
                            m_fStateChanger = 0.0f;
                            m_fRotationX = DegreesToRadians(CTaskSimpleSwim::SWIM_DIVE_UNDER_ANGLE);
                        }
                        else
                        {
                            m_fRotationX = DegreesToRadians(80.0f);
                            m_fStateChanger = 0.0f;
                        }
                    }
                }
                else
                {
                    CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_SWIM, ANIM_ID_SWIM_UNDER, 1000.0f);
                    if (m_AnimID == ANIM_ID_SWIM_TREAD || m_AnimID == ANIM_ID_NO_ANIMATION_SET)
                    {
                        m_fStateChanger = -2.0f;
                        m_AnimID = ANIM_ID_SWIM_UNDER;
                    }
                    else
                    {
                        m_fStateChanger = -1.0f;
                        m_AnimID = ANIM_ID_SWIM_UNDER;
                    }
                }
            }
            break;
        }
        case SWIM_BACK_TO_SURFACE:
        {
            if (m_AnimID == ANIM_ID_SWIM_JUMPOUT)
            {
                CAnimBlendAssociation* pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, ANIM_ID_SWIM_JUMPOUT);
                if (pAnimAssociation)
                {
                    if (pAnimAssociation->m_pHierarchy->m_fTotalTime * 0.25f <= pAnimAssociation->m_fTimeStep
                        + pAnimAssociation->m_fCurrentTime) {
                        pAnimAssociation = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_CLIMB_JUMP, 8.0f);
                        pAnimAssociation->m_nFlags |= ANIM_FLAG_UNLOCK_LAST_FRAME;
                        m_AnimID = ANIM_ID_CLIMB_JUMP;
                    }
                    break;
                }
            }
            else {
                if (m_AnimID != ANIM_ID_CLIMB_JUMP)
                {
                    CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, ANIM_GROUP_SWIM, ANIM_ID_SWIM_JUMPOUT, 8.0f);
                    m_AnimID = ANIM_ID_SWIM_JUMPOUT;
                    pPlayerPed->m_vecMoveSpeed.z = static_cast <float> (8.0f / pPlayerPed->m_fMass);
                    CEntity* pEntity = CTaskSimpleClimb::TestForClimb(pPlayerPed, m_pClimbPos, m_fAngle, m_nSurfaceType, true);
                    m_pEntity = pEntity;
                    if (pEntity)
                        pEntity->RegisterReference(&m_pEntity);
                    break;
                }
                if (RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, ANIM_ID_CLIMB_JUMP)) {
                    CVector& position = pPlayerPed->GetPosition();
                    float waterLevel = 0.0f;
                    if (!CWaterLevel::GetWaterLevel(position.x, position.y, position.z, &waterLevel, 1, nullptr)|| position.z + 0.5f >= waterLevel)
                        break;
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

        CPlayerPedData * pPlayerData = pPlayerPed->m_pPlayerData;
        if (pPlayerData && (pPlayerData->m_fMoveBlendRatio > 0.5 || m_nSwimState == SWIM_UNDERWATER_SPRINTING))
            CStats::UpdateStatsWhenSwimming(m_nSwimState == SWIM_UNDERWATER_SPRINTING, m_nSwimState == SWIM_SPRINTING);
        return;
    }
}

// 0x68A1D0
void CTaskSimpleSwim::ProcessSwimmingResistance(CPed* pPed)
{
    float fSubmergeZ = -1.0f;
    CVector vecPedMoveSpeed;

    switch (m_nSwimState)
    {
    case SWIM_TREAD:
    case SWIM_SPRINT:
    case SWIM_SPRINTING:
    {
        CAnimBlendAssociation* pAnimSwimBreast = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, ANIM_ID_SWIM_BREAST);
        CAnimBlendAssociation* pAnimSwimCrawl = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, ANIM_ID_SWIM_CRAWL);

        float fAnimBlendSum = 0.0f;
        float fAnimBlendDifference = 1.0f;
        if (pAnimSwimBreast) {
            fAnimBlendSum = 0.4f * pAnimSwimBreast->m_fBlendAmount;
            fAnimBlendDifference = 1.0f - pAnimSwimBreast->m_fBlendAmount;
        }

        if (pAnimSwimCrawl) {
            fAnimBlendSum += 0.2f * pAnimSwimCrawl->m_fBlendAmount;
            fAnimBlendDifference -= pAnimSwimCrawl->m_fBlendAmount;
        }

        if (fAnimBlendDifference < 0.0f) {
            fAnimBlendDifference = 0.0f;
        }

        fSubmergeZ = fAnimBlendDifference * 0.55f + fAnimBlendSum;

        vecPedMoveSpeed = pPed->m_vecAnimMovingShiftLocal.x * pPed->GetRight();
        vecPedMoveSpeed += pPed->m_vecAnimMovingShiftLocal.y * pPed->GetForward();
        break;
    }
    case SWIM_DIVE_UNDERWATER:
    {
        vecPedMoveSpeed = pPed->m_vecAnimMovingShiftLocal.x * pPed->GetRight();
        vecPedMoveSpeed += pPed->m_vecAnimMovingShiftLocal.y * pPed->GetForward();

        auto pAnimSwimDiveUnder = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, ANIM_ID_SWIM_DIVE_UNDER);
        if (pAnimSwimDiveUnder)
        {
            vecPedMoveSpeed.z = pAnimSwimDiveUnder->m_fCurrentTime / pAnimSwimDiveUnder->m_pHierarchy->m_fTotalTime * -0.1f;
        }
        break;
    }
    case SWIM_UNDERWATER_SPRINTING:
    {
        vecPedMoveSpeed = pPed->m_vecAnimMovingShiftLocal.x * pPed->GetRight();
        vecPedMoveSpeed += cos(m_fRotationX) * pPed->m_vecAnimMovingShiftLocal.y * pPed->GetForward();
        vecPedMoveSpeed.z += sin(m_fRotationX) * pPed->m_vecAnimMovingShiftLocal.y + 0.01f;
        break;
    }
    case SWIM_BACK_TO_SURFACE:
    {
        auto pAnimAssociation = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, ANIM_ID_CLIMB_JUMP);
        if (!pAnimAssociation)
            pAnimAssociation = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, ANIM_ID_SWIM_JUMPOUT);

        if (pAnimAssociation) {
            if (pAnimAssociation->m_pHierarchy->m_fTotalTime > pAnimAssociation->m_fCurrentTime
                && (pAnimAssociation->m_fBlendAmount >= 1.0f || pAnimAssociation->m_fBlendDelta > 0.0f)) {
                float fMoveForceZ = CTimer::ms_fTimeStep * pPed->m_fMass * 0.3f * 0.008f;
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
    if (!CWaterLevel::GetWaterLevel(vecCheckWaterLevelPos.x, vecCheckWaterLevelPos.y, vecPedPosition.z, &fWaterLevel, true, nullptr)) {
        fSubmergeZ = -1.0f;
        bUpdateRotationX = false;
    }
    else {
        if (m_nSwimState != SWIM_UNDERWATER_SPRINTING || m_fStateChanger < 0.0f) {
            bUpdateRotationX = false;
        }
        else {
            if (vecPedPosition.z + 0.65f > fWaterLevel && m_fRotationX > 0.7854f) {
                m_nSwimState = SWIM_TREAD;
                m_fStateChanger = 0.0;
                bUpdateRotationX = false;
            }
        }
    }

    if (bUpdateRotationX)
    {
        if (m_fRotationX >= 0.0f) {
            if (vecPedPosition.z + 0.65f <= fWaterLevel) {
                if (m_fStateChanger <= 0.001f)
                    m_fStateChanger = 0.0f;
                else
                    m_fStateChanger *= 0.95f;
            }
            else {
                float fMinimumSpeed = 0.05f * 0.5f;
                if (m_fStateChanger > fMinimumSpeed)
                    m_fStateChanger *= 0.95f;
                if (m_fStateChanger < fMinimumSpeed) {
                    m_fStateChanger += CTimer::ms_fTimeStep * 0.002f;
                    m_fStateChanger = std::min(fMinimumSpeed, m_fStateChanger);
                }
                m_fRotationX += CTimer::ms_fTimeStep * m_fStateChanger;
                fSubmergeZ = (0.55f - 0.2f) * (m_fRotationX * 1.2732395f) * 0.75f + 0.2f;
            }
        }
        else {
            if (vecPedPosition.z - sin(m_fRotationX) + 0.65f <= fWaterLevel) {
                if (m_fStateChanger > 0.001f)
                    m_fStateChanger *= 0.95f;
                else
                    m_fStateChanger = 0.0f;
            }
            else {
                m_fStateChanger += CTimer::ms_fTimeStep * 0.002f;
                if (m_fStateChanger > 0.05f)
                    m_fStateChanger = 0.05f;
            }
            m_fRotationX += CTimer::ms_fTimeStep * m_fStateChanger;
        }
    }

    if (fSubmergeZ > 0.0f) {
        fWaterLevel -= (fSubmergeZ + vecPedPosition.z);
        float fTimeStepMoveSpeedZ = fWaterLevel / CTimer::ms_fTimeStep;
        float fTimeStep = CTimer::ms_fTimeStep * 0.1f;
        if (fTimeStepMoveSpeedZ > fTimeStep)
            fTimeStepMoveSpeedZ = fTimeStep;
        if (-fTimeStep > fTimeStepMoveSpeedZ)
            fTimeStepMoveSpeedZ = -fTimeStep;

        fTimeStepMoveSpeedZ -= pPed->m_vecMoveSpeed.z;

        fTimeStep = CTimer::ms_fTimeStep * 0.02f;
        if (fTimeStepMoveSpeedZ > fTimeStep)
            fTimeStepMoveSpeedZ = fTimeStep;
        if (-fTimeStep > fTimeStepMoveSpeedZ)
            fTimeStepMoveSpeedZ = -fTimeStep;

        pPed->m_vecMoveSpeed.z += fTimeStepMoveSpeedZ;
    }

    CVector* pPedPosition = &pPed->GetPosition();
    if (pPedPosition->z < -69.0f) {
        pPedPosition->z = -69.0f;
        if (pPed->m_vecMoveSpeed.z < 0.0f)
            pPed->m_vecMoveSpeed.z = 0.0f;
    }
}

// 0x68AA70
void CTaskSimpleSwim::ProcessEffects(CPed* pPed)
{
    CVector vecParticlePosition = pPed->GetForwardVector();
    vecParticlePosition *= 0.4f;
    vecParticlePosition += pPed->GetPosition();

    CPlayerPedData * pPlayerData = pPed->m_pPlayerData;

    if (pPlayerData)
        vecParticlePosition.z = pPlayerData->m_fWaterHeight;
    else
        vecParticlePosition.z += 0.5f;

    if (m_nSwimState != SWIM_TREAD) {
        if (m_pFxSystem) {
            m_pFxSystem->Kill();
            m_pFxSystem = nullptr;
        }
    }
    else {
        RwMatrix* pNewMatrix = RwMatrixCreate();
        pNewMatrix->pos = *((RwV3d*)& vecParticlePosition);
        RwMatrixUpdate(pNewMatrix);
        if (!m_pFxSystem)
            CreateFxSystem(pPed, pNewMatrix);

        if (m_pFxSystem) {
            m_pFxSystem->SetMatrix(pNewMatrix);
            m_pFxSystem->SetLocalParticles(1);
        }
        RwMatrixDestroy(pNewMatrix);
    }

    if (m_nSwimState != SWIM_DIVE_UNDERWATER)
        m_bTriggerWaterSplash = false;

    switch (m_nSwimState)
    {
    case SWIM_SPRINT:
    case SWIM_SPRINTING:
    {
        const CVector& vecPedUp = pPed->GetForward();

        float fRadianAngle = CGeneral::GetAngleBetweenPoints(vecPedUp.x, vecPedUp.y, 0.0f, 0.0f);
        float fLimitedRadianAngle = CGeneral::LimitAngle(fRadianAngle) + 180.0f;

        FxPrtMult_c fxPrtMult(1.0f, 1.0f, 1.0f, 0.2f, 0.4f, 0.0f, 0.5f);
        CVector vecParticleVelocity;
        g_fx.m_pPrtWake->AddParticle((RwV3d*)& vecParticlePosition, (RwV3d*)& vecParticleVelocity, 0.0f, (FxPrtMult_c*)& fxPrtMult, fLimitedRadianAngle, 1.2f, 0.6f, 0);
        pPed->m_pedAudio.AddAudioEvent(76, 0.0, 1.0f, nullptr, 0, 0, 0);

        if (m_nSwimState == SWIM_SPRINTING)
        {
            RpHAnimHierarchy* pAnimHierarchy = GetAnimHierarchyFromSkinClump(pPed->m_pRwClump);
            int32 boneRHandIndex = RpHAnimIDGetIndex(pAnimHierarchy, BONE_R_HAND);
            RwV3d* pBoneRHandPos = &RpHAnimHierarchyGetMatrixArray(pAnimHierarchy)[boneRHandIndex].pos;
            int32 boneLHandIndex = RpHAnimIDGetIndex(pAnimHierarchy, BONE_L_HAND);
            RwV3d* pBoneLHandPos = &RpHAnimHierarchyGetMatrixArray(pAnimHierarchy)[boneLHandIndex].pos;
            int32 boneRFootIndex = RpHAnimIDGetIndex(pAnimHierarchy, BONE_R_FOOT);
            RwV3d* pBoneRFootPos = &RpHAnimHierarchyGetMatrixArray(pAnimHierarchy)[boneRFootIndex].pos;
            int32 boneLFootIndex = RpHAnimIDGetIndex(pAnimHierarchy, BONE_L_FOOT);
            RwV3d* pBoneLFootPos = &RpHAnimHierarchyGetMatrixArray(pAnimHierarchy)[boneLFootIndex].pos;

            float fPedPosZ = pPed->GetPosition().z;
            if (fabs(pBoneRHandPos->z - fPedPosZ) < 0.05f)
            {
                auto pFxSystem = g_fxMan.CreateFxSystem("water_swim", pBoneRHandPos, nullptr, false);
                if (pFxSystem)
                {
                    pFxSystem->PlayAndKill();
                    pPed->m_pedAudio.AddAudioEvent(74, 0.0, 1.0f, nullptr, 0, 0, 0);
                }
            }

            if (fabs(pBoneLHandPos->z - fPedPosZ) < 0.05f)
            {
                auto pFxSystem = g_fxMan.CreateFxSystem("water_swim", pBoneLHandPos, nullptr, false);
                if (pFxSystem)
                {
                    pFxSystem->PlayAndKill();
                    pPed->m_pedAudio.AddAudioEvent(74, 0.0, 1.0f, nullptr, 0, 0, 0);
                }
            }
            if (fabs(pBoneRFootPos->z - fPedPosZ) < 0.05f)
            {
                auto pFxSystem = g_fxMan.CreateFxSystem("water_swim", pBoneRFootPos, nullptr, false);
                if (pFxSystem)
                {
                    pFxSystem->PlayAndKill();
                    pPed->m_pedAudio.AddAudioEvent(74, 0.0, 1.0f, nullptr, 0, 0, 0);
                }
            }
            if (fabs(pBoneLFootPos->z - fPedPosZ) < 0.05f)
            {
                auto pFxSystem = g_fxMan.CreateFxSystem("water_swim", pBoneLFootPos, nullptr, false);
                if (pFxSystem)
                {
                    pFxSystem->PlayAndKill();
                    pPed->m_pedAudio.AddAudioEvent(74, 0.0, 1.0f, nullptr, 0, 0, 0);
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
        pPed->m_pedAudio.AddAudioEvent(75, 0.0, 1.0, nullptr, 0, 0, 0);
        return;
    }
    case SWIM_UNDERWATER_SPRINTING:
    {
        uint32 oxygen = 5;
        if (pPed->IsPlayer())
        {
            oxygen = static_cast<uint32>(
                ((100.0f - pPlayerData->m_fBreath / CStats::GetFatAndMuscleModifier(STAT_MOD_AIR_IN_LUNG) * 100.0f) * 0.33333334f));
        }
        if ((unsigned)CGeneral::GetRandomNumberInRange(0, 100) < oxygen)
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
}

// 0x689640
void CTaskSimpleSwim::ProcessControlAI(CPed* pPed)
{
    m_nSwimState = SWIM_TREAD;
    if (m_pPed)
    {
        CVector vecPosition(m_pPed->GetPosition() - pPed->GetPosition());
        vecPosition.Normalise();
        if (m_fRandomMoveBlendRatio == 0.0f)
        {
            m_fRandomMoveBlendRatio = (rand() % 4) * 0.5f + 1.5f;
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
                        CVector distance = m_vecPos - pPed->GetPosition();
                        if (distance.Magnitude() > 5.0f)
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
        if (!((pPed->m_nRandomSeedUpperByte + CTimer::m_FrameCounter - 4) & 0x7F)) {
            if (CTaskSimpleClimb::TestForClimb(pPed, m_pClimbPos, m_fAngle, m_nSurfaceType, true))
                m_nSwimState = SWIM_BACK_TO_SURFACE;
        }
    }
    m_fAimingRotation = 0.0f;
    m_fUpperTorsoRotationX = 0.0f;

    if (!bPedGroupSet && !pPed->IsPlayer() && m_fAnimSpeed < 0.0f)
        pPed->m_vecAnimMovingShiftLocal *= 0.5f;
}

// 0x688A90
void CTaskSimpleSwim::ProcessControlInput(CPlayerPed* pPed)
{
    CVector vecPedWalk;
    CPlayerPedData * pPlayerData = pPed->m_pPlayerData;
    if (!m_bFinishedBlending || !m_bAnimBlockRefAdded)
    {
        pPlayerData->m_fMoveBlendRatio = 0.0f;
        return;
    }

    CPad* pPad = pPed->GetPadFromPlayer();
    int16 pedWalkUpDown = pPad->GetPedWalkUpDown();
    int16 pedWalkLeftRight = pPad->GetPedWalkLeftRight();
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
            pPed->m_pPlayerData->m_fMoveBlendRatio = 0.0f;
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
                if (fLimitedRadianAngle <= pPed->m_fCurrentRotation + DegreesToRadians(180.0f))
                {
                    if (fLimitedRadianAngle < pPed->m_fCurrentRotation - DegreesToRadians(180.0f))
                    {
                        fLimitedRadianAngle += DegreesToRadians(360.0f);
                    }
                }
                else
                {
                    fLimitedRadianAngle -= DegreesToRadians(360.0f);
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
                if (pPed->m_fAimingRotation <= DegreesToRadians(180.0f))
                {
                    if (pPed->m_fAimingRotation < -DegreesToRadians(180.0f))
                    {
                        pPed->m_fAimingRotation += DegreesToRadians(360.0f);
                    }
                }
                else
                {
                    pPed->m_fAimingRotation -= DegreesToRadians(360.0f);
                }
                if (CGameLogic::IsPlayerAllowedToGoInThisDirection(pPed, vecPedWalkDirection.x, vecPedWalkDirection.y, vecPedWalkDirection.z, 0.0f))
                {
                    CMatrixLink* pPedMatrix = pPed->m_matrix;
                    pedWalkX = (vecPedWalkDirection.y * pPedMatrix->GetRight().y
                        + vecPedWalkDirection.x * pPedMatrix->GetRight().x
                        + pPedMatrix->GetRight().z * 0.0f)
                        * fWalkMagnitude;
                    vecPedWalk.y = -((vecPedWalkDirection.y * pPedMatrix->GetForward().y
                        + pPedMatrix->GetForward().z * 0.0f
                        + vecPedWalkDirection.x * pPedMatrix->GetForward().x)
                        * fWalkMagnitude);
                }
                else
                {
                    pedWalkX = 0.0f;
                    fWalkMagnitude = 0.0f;
                    vecPedWalk.y = 0.0f;
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
            if (fWalkMagnitude <= 0.0f)
            {
                if (pPlayerData->m_fMoveBlendRatio > 0.0f)
                {
                    pPlayerData->m_fMoveBlendRatio -= CTimer::ms_fTimeStep * 0.05f;
                    if (pPlayerData->m_fMoveBlendRatio < 0.0f)
                    {
                        pPlayerData->m_fMoveBlendRatio = 0.0f;
                    }
                }
            }
            else
            {
                bool bUpdateMoveBlendRatio = false;
                if (!bPlayerUse2PlayerControls)
                {
                    pPed->m_fAimingRotation += CTimer::ms_fTimeStep * -0.03f * pedWalkX;
                    if (pPed->m_fAimingRotation <= DegreesToRadians(180.0f))
                    {
                        if (pPed->m_fAimingRotation < -DegreesToRadians(180.0f))
                        {
                            pPed->m_fAimingRotation += DegreesToRadians(360.0f);
                        }
                    }
                    else
                    {
                        pPed->m_fAimingRotation -= DegreesToRadians(360.0f);
                    }
                    float pedWalkY = vecPedWalk.y;
                    float negativePedWalkY = 0.0f;
                    if (m_nSwimState)
                    {
                        if (pedWalkY > 0.0f)
                        {
                            fWalkMagnitude -= vecPedWalk.y;
                        }
                    }
                    else
                    {
                        fWalkMagnitude = -pedWalkY;
                    }

                    if (fWalkMagnitude < 0.0f)
                    {
                        fWalkMagnitude = 0.0f;
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
                pPed->m_fAimingRotation += DegreesToRadians(180.0f);
                if (pPed->m_fAimingRotation > DegreesToRadians(180.0f))
                {
                    pPed->m_fAimingRotation -= DegreesToRadians(360.0f);
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
            if (fRotation <= DegreesToRadians(180.0f))
            {
                if (fRotation < -DegreesToRadians(180.0f))
                {
                    fRotation = DegreesToRadians(360.0f) - (pPed->m_fAimingRotation - pPed->m_fCurrentRotation);
                }

            }
            else
            {
                fRotation -= DegreesToRadians(360.0f);
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
            float fWaterLevel1 = 0.0f;
            float fWaterLevel2 = 0.0f;
            CVector distance = pPed->GetPosition() - pPed->GetForward();
            CVector position = pPed->GetPosition() + pPed->GetForward();
            if (CWaterLevel::GetWaterLevel(position.x, position.y, position.z, &fWaterLevel1, 1, nullptr)) {
                if (CWaterLevel::GetWaterLevel(distance.x, distance.y, distance.z, &fWaterLevel2, 1, nullptr))
                    m_fRotationX = atan2(fWaterLevel1 - fWaterLevel2, 2.0f) * 1.0f;
            }
        }
        if (pPed->ControlButtonSprint(SPRINT_WATER) < 1.0f)
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
            if (fRotation <= DegreesToRadians(180.0f))
            {
                if (fRotation < -DegreesToRadians(180.0f))
                    fRotation += DegreesToRadians(360.0f);
            }
            else
            {
                fRotation -= DegreesToRadians(360.0f);
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

                if (pPed->m_fAimingRotation <= DegreesToRadians(180.0f))
                {
                    if (pPed->m_fAimingRotation < -DegreesToRadians(180.0f))
                    {
                        pPed->m_fAimingRotation += DegreesToRadians(360.0f);
                    }
                }
                else
                {
                    pPed->m_fAimingRotation -= DegreesToRadians(360.0f);
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
                    fUpperTorsoRotationX = 1.0f;
                }

                m_fUpperTorsoRotationX += CTimer::ms_fTimeStep * -0.079999998f * fUpperTorsoRotationX;
            }
        }

        m_fRotationX += CTimer::ms_fTimeStep * 0.001f;
        m_fRotationX = clamp<float>(m_fRotationX, -DegreesToRadians(80.0f), DegreesToRadians(80.0f));
        // BUG: it should be m_fTimeCanRun <= 0.1f
        if (pPed->m_pPlayerData->m_fTimeCanRun <= 0.0f)
            pPed->m_pPlayerData->m_fTimeCanRun = 0.1f;
        pPed->ControlButtonSprint(SPRINT_UNDERWATER);
        break;
    }
    }


    float fRotation = 0.95f;
    if (m_nSwimState == SWIM_UNDERWATER_SPRINTING || m_nSwimState == SWIM_SPRINTING)
    {
        fRotation = 0.95f;
    }

    if (m_fTurningRotationY > 0.01f || m_fTurningRotationY < -0.01f)
    {
        m_fTurningRotationY *= pow(fRotation, CTimer::ms_fTimeStep);
    }
    else
    {
        m_fTurningRotationY = 0.0f;
    }
    if (m_nSwimState != SWIM_UNDERWATER_SPRINTING && m_nSwimState != SWIM_SPRINTING)
    {
        if (m_fRotationX > 0.01f || m_fRotationX < -0.01f)
        {
            m_fRotationX *= pow(fRotation, CTimer::ms_fTimeStep);
        }
        else
        {
            m_fRotationX = 0.0f;
        }
    }

    if (m_nSwimState == SWIM_DIVE_UNDERWATER || m_nSwimState == SWIM_BACK_TO_SURFACE)
        fRotation = 0.95f;
    else
        fRotation = 0.92f;

    if (m_fAimingRotation > 0.01f
        || m_fAimingRotation < -0.01f
        || m_fUpperTorsoRotationX > 0.01f
        || m_fUpperTorsoRotationX < -0.01f)
    {
        float fTimeStepRotation = pow(fRotation, CTimer::ms_fTimeStep);
        m_fAimingRotation *= fTimeStepRotation;
        m_fUpperTorsoRotationX *= fTimeStepRotation;
    }
    else {
        m_fAimingRotation = 0.0f;
        m_fUpperTorsoRotationX = 0.0f;
    }
    if (m_nSwimState == SWIM_SPRINT)
        pPed->HandleSprintEnergy(false, 0.5f);
    else if (m_nSwimState != SWIM_SPRINTING)
        pPed->HandleSprintEnergy(false, 1.0f);
}

// 0x68A9F0
void CTaskSimpleSwim::CreateFxSystem(CPed* pPed, RwMatrixTag* pRwMatrix)
{
    RwV3d point = { 0.0f, 0.0f, 0.0f };
    m_pFxSystem = g_fxMan.CreateFxSystem("water_ripples", &point, pRwMatrix, false);
    if (m_pFxSystem)
    {
        m_pFxSystem->CopyParentMatrix();
        m_pFxSystem->Play();
    }
}

// 0x68AA50
void CTaskSimpleSwim::DestroyFxSystem()
{
    if (m_pFxSystem)
    {
        m_pFxSystem->Kill();
        m_pFxSystem = nullptr;
    }
}
