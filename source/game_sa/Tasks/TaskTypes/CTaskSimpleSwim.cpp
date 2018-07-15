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
    CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPed->m_pRwClump, 14);
    if (m_bFinishedBlending)
    {
        if (pAnimAssociation
            && pAnimAssociation->m_fBlendAmount < 1.0
            && pAnimAssociation->m_fBlendDelta <= 0.0)
        {
            CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, 0, 0xEu, 8.0);
        }
    }
    else
    {
        if (pAnimAssociation
            || (pAnimAssociation = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, 0, 14u, 8.0)) != 0)
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
        CAnimBlock * pAnimBlock = CAnimManager::ms_aAnimAssocGroups[71].m_pAnimBlock;
        if (!pAnimBlock)
        {
            char * pBlockName = CAnimManager::GetAnimBlockName(71);
            pAnimBlock = CAnimManager::GetAnimationBlock(pBlockName);
        }
        if (pAnimBlock->bLoaded == 1)
        {
            CAnimManager::AddAnimBlockRef(pAnimBlock - CAnimManager::ms_aAnimBlocks);
            m_bAnimBlockRefAdded = true;
        }
        else
        {
            CStreaming::RequestModel(pAnimBlock - CAnimManager::ms_aAnimBlocks + 25575, 8);
        }
    }

    if (m_bFinishedBlending && m_bAnimBlockRefAdded)
    {
        switch (m_nSwimState)
        {
        case SWIM_TREAD:
        {
            if (m_AnimID != 14)
            {
                CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, 311);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -1.0;
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, 312);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -1.0;
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, 313);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -4.0;
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, 314);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -2.0;
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, 315);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -2.0;
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, 316);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -4.0;
                pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, 128);
                if (pAnimAssociation)
                    pAnimAssociation->m_fBlendDelta = -4.0;
                m_AnimID = 14;
            }
            break;
        }
        case SWIM_SPRINT:
        {
            if (m_AnimID == 311)
            {
                CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, 311);
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
                CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, 71, 0x137u, 2.0);
                m_AnimID = 311;
            }
            break;
        }
        case SWIM_SPRINTING:
        {
            if (m_AnimID == 312)
            {
                CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, 312);
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
                CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, 71, 0x138u, 2.0);
                m_AnimID = 312;
            }
            break;
        }
        case SWIM_DIVE_UNDERWATER:
        {
            if (m_AnimID == 313)
            {
                CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, 313);
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
                CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, 71, 0x139u, 8.0);
                m_AnimID = 313;
            }
            break;
        }
        case SWIM_UNDERWATER_SPRINTING:
        {
            int animID = m_AnimID;
            if ((animID == 314 || animID == 315) && flt_34 >= 0.0)
            {
                if (pPlayerPed->m_pPlayerData && pPlayerPed->GetButtonSprintResults((eSprintType)3) >= 1.0)
                {
                    CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, 314);
                    if (!pAnimAssociation
                        || pAnimAssociation->m_fBlendDelta < 0.0
                        || pAnimAssociation->m_fBlendAmount == 0.0)
                    {
                        pAnimAssociation = CAnimManager::BlendAnimation(
                            pPlayerPed->m_pRwClump,
                            71,
                            0x13Au,
                            4.0);
                    }
                    if (pAnimAssociation->m_pHierarchy->m_fTotalTime == pAnimAssociation->m_fCurrentTime)
                    {
                        pAnimAssociation->Start(0.0);
                        float buttonSprintResults = pPlayerPed->GetButtonSprintResults((eSprintType)3);
                        pAnimAssociation->m_fSpeed = static_cast < float > (max(0.69999999, buttonSprintResults));
                    }
                    m_AnimID = 314;
                }
                else
                {
                    CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, 315);
                    if (!pAnimAssociation
                        || pAnimAssociation->m_fBlendDelta < 0.0
                        || pAnimAssociation->m_fBlendAmount == 0.0)
                    {
                        CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, 71, 0x13Bu, 4.0);
                    }
                    m_AnimID = 315;
                }
            }
            else
            {
                CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, 314);
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
                    CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, 71, 0x13Au, 1000.0);
                    int animID = m_AnimID;
                    if (animID == 14 || animID == 191)
                    {
                        flt_34 = -1073741824;
                        m_AnimID = 314;
                    }
                    else
                    {
                        flt_34 = -1082130432;
                        m_AnimID = 314;
                    }
                }
            }
            break;
        }
        case SWIM_BACK_TO_SURFACE:
        {
            int animID = m_AnimID;
            if (animID == 316)
            {
                CAnimBlendAssociation * pAnimAssociation = RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, 316);
                if (pAnimAssociation)
                {
                    if (pAnimAssociation->m_pHierarchy->m_fTotalTime * 0.25 <= pAnimAssociation->m_fTimeStep
                        + pAnimAssociation->m_fCurrentTime)
                    {
                        pAnimAssociation = CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, 0, 0x80u, 8.0);
                        pAnimAssociation->m_nFlags |= 8u;
                        m_AnimID = 128;
                    }
                    break;
                }
            }
            else
            {
                if (animID != 128)
                {
                    CAnimManager::BlendAnimation(pPlayerPed->m_pRwClump, 71, 0x13Cu, 8.0);
                    m_AnimID = 316;
                    pPlayerPed->m_vecMoveSpeed.z = static_cast < float > (8.0 / pPlayerPed->m_fMass);
                    CEntity * pEntity = CTaskSimpleClimb::TestForClimb(pPlayerPed, m_pClimbPos, (m_fAngle), (m_nSurfaceType), 1);
                    m_pEntity = pEntity;
                    if (pEntity)
                        pEntity->RegisterReference(&m_pEntity);
                    break;
                }
                if (RpAnimBlendClumpGetAssociation(pPlayerPed->m_pRwClump, 128))
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