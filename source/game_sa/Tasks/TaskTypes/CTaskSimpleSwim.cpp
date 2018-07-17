/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

bool &CTaskSimpleSwim::SWIM_DIVE_UNDER_ANGLE = *reinterpret_cast<bool *>(0x8D2FC4);

CTaskSimpleSwim::CTaskSimpleSwim(CVector const* pPosn, CPed* pPed) : CTaskSimple(plugin::dummy)
{
    plugin::CallMethod<0x688930, CTaskSimpleSwim*, CVector const*, CPed*>(this, pPosn, pPed);
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
                        pAnimAssociation = CAnimManager::BlendAnimation( pPlayerPed->m_pRwClump, ANIM_GROUP_SWIM, SWIM_SWIM_UNDER, 4.0);
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