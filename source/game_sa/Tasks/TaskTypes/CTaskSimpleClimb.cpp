/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

bool& CTaskSimpleClimb::tempMatrix_Initialized = *reinterpret_cast<bool*>(0xC19630);
CMatrix& CTaskSimpleClimb::tempMatrix = *reinterpret_cast<CMatrix*>(0xC195E8);
CColModel& CTaskSimpleClimb::ms_ClimbColModel = *reinterpret_cast<CColModel*>(0xC19518);
CColModel& CTaskSimpleClimb::ms_StandUpColModel = *reinterpret_cast<CColModel*>(0xC19548);
CColModel& CTaskSimpleClimb::ms_VaultColModel = *reinterpret_cast<CColModel*>(0xC19578);
CColModel& CTaskSimpleClimb::ms_FindEdgeColModel = *reinterpret_cast<CColModel*>(0xC195A8);
float& CTaskSimpleClimb::ms_fHangingOffsetHorz = *reinterpret_cast<float*>(0x8D2F1C); // -0.4F
float& CTaskSimpleClimb::ms_fHangingOffsetVert = *reinterpret_cast<float*>(0x8D2F20); // -1.1F
float& CTaskSimpleClimb::ms_fAtEdgeOffsetHorz = *reinterpret_cast<float*>(0x8D2F24); // -0.4F
float& CTaskSimpleClimb::ms_fAtEdgeOffsetVert = *reinterpret_cast<float*>(0xC18F78); // 0.0F
float& CTaskSimpleClimb::ms_fStandUpOffsetHorz = *reinterpret_cast<float*>(0x8D2F28); // 0.15F
float& CTaskSimpleClimb::ms_fStandUpOffsetVert = *reinterpret_cast<float*>(0x8D2F2C); // 1.0F
float& CTaskSimpleClimb::ms_fVaultOffsetHorz = *reinterpret_cast<float*>(0x8D2F30); // 0.5F
float& CTaskSimpleClimb::ms_fVaultOffsetVert = *reinterpret_cast<float*>(0xC18F7C); // 0.0F
float& CTaskSimpleClimb::ms_fMinForStretchGrab = *reinterpret_cast<float*>(0x8D2F34); // 1.4F

void CTaskSimpleClimb::InjectHooks()
{
    ReversibleHooks::Install("CTaskSimpleClimb", "ScanToGrabSectorList", 0x67DE10, &CTaskSimpleClimb::ScanToGrabSectorList);
    ReversibleHooks::Install("CTaskSimpleClimb", "ScanToGrab", 0x67FD30, &CTaskSimpleClimb::ScanToGrab);
    ReversibleHooks::Install("CTaskSimpleClimb", "CreateColModel", 0x67A890, &CTaskSimpleClimb::CreateColModel);
    ReversibleHooks::Install("CTaskSimpleClimb", "TestForStandUp", 0x680570, &CTaskSimpleClimb::TestForStandUp);
    ReversibleHooks::Install("CTaskSimpleClimb", "TestForVault", 0x6804D0, &CTaskSimpleClimb::TestForVault);
    ReversibleHooks::Install("CTaskSimpleClimb", "TestForClimb", 0x6803A0, &CTaskSimpleClimb::TestForClimb);
    //ReversibleHooks::Install("CTaskSimpleClimb", "StartAnim", 0x67DBE0, &CTaskSimpleClimb::StartAnim);
    ReversibleHooks::Install("CTaskSimpleClimb", "StartSpeech", 0x67A320, &CTaskSimpleClimb::StartSpeech);
    ReversibleHooks::Install("CTaskSimpleClimb", "DeleteAnimCB", 0x67A380, &CTaskSimpleClimb::DeleteAnimCB);
    ReversibleHooks::Install("CTaskSimpleClimb", "Shutdown", 0x67A250, &CTaskSimpleClimb::Shutdown);
    ReversibleHooks::Install("CTaskSimpleClimb", "Constructor", 0x67A110, &CTaskSimpleClimb::Constructor);
    ReversibleHooks::Install("CTaskSimpleClimb", "GetCameraStickModifier", 0x67A5D0, &CTaskSimpleClimb::GetCameraStickModifier);
    ReversibleHooks::Install("CTaskSimpleClimb", "GetCameraTargetPos", 0x67A390, &CTaskSimpleClimb::GetCameraTargetPos);
    //VTABLE
    //ReversibleHooks::Install("CTaskSimpleClimb", "ProcessPed", 0x680DC0, &CTaskSimpleClimb::ProcessPed_Reversed);
    ReversibleHooks::Install("CTaskSimpleClimb", "MakeAbortable", 0x67A280, &CTaskSimpleClimb::MakeAbortable_Reversed);
}

CTaskSimpleClimb* CTaskSimpleClimb::Constructor(CEntity* pClimbEnt, const CVector& vecTarget, float fHeading, unsigned char nSurfaceType, eClimbHeights nHeight, bool bForceClimb)
{
    this->CTaskSimpleClimb::CTaskSimpleClimb(pClimbEnt, vecTarget, fHeading, nSurfaceType, nHeight, bForceClimb);
    return this;
}

// 0x67A110
CTaskSimpleClimb::CTaskSimpleClimb(CEntity* pClimbEnt, const CVector& vecTarget, float fHeading, unsigned char nSurfaceType, eClimbHeights nHeight, bool bForceClimb)
{
    m_bIsFinished = false;
    m_bChangeAnimation = false;
    m_bChangePosition = false;
    m_bInvalidClimb = false;
    m_pClimbEnt = pClimbEnt;
    m_pAnim = nullptr;
    m_vecHandholdPos = vecTarget;
    m_fHandholdHeading = fHeading;
    m_nSurfaceType = nSurfaceType;
    m_nHeightForAnim = nHeight;
    m_nHeightForPos = CLIMB_NOT_READY;
    m_nGetToPosCounter = 0;
    m_bForceClimb = bForceClimb;
    m_nFallAfterVault = -1;

    if (m_pClimbEnt)
        m_pClimbEnt->RegisterReference(&m_pClimbEnt);
}

// 0x67A1D0
CTaskSimpleClimb::~CTaskSimpleClimb()
{
    if (m_pClimbEnt)
        m_pClimbEnt->CleanUpOldReference(&m_pClimbEnt);

    if (m_pAnim)
    {
        m_pAnim->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
        m_pAnim = nullptr;
    }
}


// 0x680DC0
bool CTaskSimpleClimb::ProcessPed(CPed* ped)
{
    return ProcessPed_Reversed(ped);
}

// 0x67A280
bool CTaskSimpleClimb::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    return MakeAbortable_Reversed(ped, priority, _event);
}

bool CTaskSimpleClimb::ProcessPed_Reversed(CPed* ped)
{
    if (m_bIsFinished)
    {
        if (ped->m_pEntityIgnoredCollision == m_pClimbEnt)
            ped->m_pEntityIgnoredCollision = nullptr;
        return true;
    }

    if (!m_pClimbEnt
        || m_pClimbEnt->IsObject() && !m_pClimbEnt->IsStatic() && !m_pClimbEnt->AsPhysical()->physicalFlags.bDisableCollisionForce
        || m_pClimbEnt->IsVehicle() && m_pClimbEnt->AsVehicle()->IsBoat() && m_pClimbEnt->AsVehicle()->m_vecMoveSpeed.Magnitude() > 0.1F
        )
    {
        MakeAbortable(ped, ABORT_PRIORITY_URGENT, 0);
        return true;
    }

    if (m_pClimbEnt->IsVehicle())
        ped->m_pEntityIgnoredCollision = m_pClimbEnt;

    if (!m_pAnim || m_bChangeAnimation)
    {
        StartAnim(ped);
        StartSpeech(ped);
    }

    float fAngle = m_fHandholdHeading;
    CVector posn = m_vecHandholdPos;

    if (m_pClimbEnt->IsPhysical())
    {
        posn = m_pClimbEnt->GetMatrix() * posn;
        fAngle += m_pClimbEnt->GetHeading();
    }

    bool bNewHeightForPos = false;
    if (m_bChangePosition && m_pAnim && m_pAnim->m_fBlendAmount == 1.0F)
    {
        bNewHeightForPos = true;
        m_nHeightForPos = m_nHeightForAnim;
        m_bChangePosition = false;
    }

    if (m_nHeightForPos > 0)
    {
        float offsetHorz, offsetVert;

        switch (m_nHeightForPos)
        {
        case CLIMB_GRAB:
        case CLIMB_PULLUP:
            offsetHorz = ms_fHangingOffsetHorz;
            offsetVert = ms_fHangingOffsetVert;
            break;
        case CLIMB_STANDUP:
        case CLIMB_VAULT:
            offsetHorz = ms_fAtEdgeOffsetHorz;
            offsetVert = ms_fAtEdgeOffsetVert;
            break;
        case CLIMB_FINISHED:
            offsetHorz = ms_fStandUpOffsetHorz;
            offsetVert = ms_fStandUpOffsetVert;
            break;
        case CLIMB_FINISHED_V:
            offsetHorz = ms_fVaultOffsetHorz;
            offsetVert = ms_fVaultOffsetVert;
            break;
        default:
            break;
        }

        CVector targetPoint = posn + CVector(-sin(fAngle) * offsetHorz, cos(fAngle) * offsetHorz, offsetVert);
        CVector vecClimbEntSpeed;
        CVector relPosn = targetPoint - ped->GetPosition();

        if (!m_pClimbEnt->IsStatic() && m_pClimbEnt->IsPhysical())
            vecClimbEntSpeed = m_pClimbEnt->AsPhysical()->GetSpeed(targetPoint - m_pClimbEnt->GetPosition());

        if (bNewHeightForPos)
        {
            ped->SetPosn(targetPoint);
            ped->m_vecMoveSpeed = vecClimbEntSpeed;
        }
        else
        {
            if (relPosn.SquaredMagnitude() >= 0.1F)
            {
                ped->bIsStanding = false;
                relPosn *= 0.25F;
                ped->m_vecMoveSpeed = relPosn / CTimer::ms_fTimeStep;

                if (ped->m_vecMoveSpeed.Magnitude() > 0.2F)
                    ped->m_vecMoveSpeed *= 0.2F / ped->m_vecMoveSpeed.Magnitude();

                ped->m_vecMoveSpeed += vecClimbEntSpeed;

                if (!(m_pAnim->m_nFlags & ANIM_FLAG_STARTED) || m_pAnim->m_nAnimId == ANIM_ID_CLIMB_IDLE)
                {
                    m_nGetToPosCounter += CTimer::GetTimeStepInMilliseconds();
                    if (m_nGetToPosCounter > 1000 || m_pAnim->m_nAnimId == ANIM_ID_CLIMB_IDLE && m_nGetToPosCounter > 500)
                    {
                        m_bInvalidClimb = true;
                        MakeAbortable(ped, ABORT_PRIORITY_URGENT, 0);
                        ped->ApplyMoveForce(ped->GetForward() * (ped->m_fMass * -0.1F));
                    }
                }
            }
            else
            {
                ped->bIsStanding = false;
                ped->m_vecMoveSpeed = relPosn / CTimer::ms_fTimeStep;
                ped->m_vecMoveSpeed += vecClimbEntSpeed;

                if (!(m_pAnim->m_nFlags & ANIM_FLAG_STARTED) && m_nHeightForAnim == CLIMB_STANDUP)
                {
                    if (TestForVault(ped, &posn, fAngle))
                    {
                        m_nHeightForAnim = CLIMB_VAULT;
                        m_bChangeAnimation = true;
                    }
                    else
                        m_pAnim->m_nFlags |= ANIM_FLAG_STARTED;
                }
            }
        }
    }

    if (bNewHeightForPos)
    {
        if (m_nHeightForPos == CLIMB_FINISHED || m_nHeightForPos == CLIMB_FINISHED_V)
        {
            m_bIsFinished = true;
            ped->bIsInTheAir = false;
            ped->bIsLanding = false;

            if (m_nHeightForPos == CLIMB_FINISHED_V)
            {
                ped->m_vecMoveSpeed = ped->GetForward() * 0.02F + CVector(0.0F, 0.0F, -0.05F);
                ped->bIsStanding = false;
                ped->bWasStanding = true;
            }
            else
            {
                ped->m_vecMoveSpeed = ped->GetForward() * 0.05F + CVector(0.0F, 0.0F, -0.01F);
                ped->bIsStanding = true;
                ped->bWasStanding = true;
            }

            if (ped->IsPlayer())
            {
                CVector empty{};
                CEventSoundQuiet _event(ped, 50.0F, -1, empty);
                GetEventGlobalGroup()->Add(&_event, false);
            }

            if (m_pAnim)
                m_pAnim->m_fBlendDelta = -8.0F;

            if (ped->m_pEntityIgnoredCollision == m_pClimbEnt)
                ped->m_pEntityIgnoredCollision = nullptr;

            return true;
        }
    }

    CPad* pad = ped->IsPlayer() ? ped->AsPlayerPed()->GetPadFromPlayer() : nullptr;

    if (m_pAnim && m_pAnim->m_fBlendAmount == 1.0F)
    {
        switch (m_pAnim->m_nAnimId)
        {
        case ANIM_ID_CLIMB_JUMP:
            if (m_pAnim->m_pHierarchy->m_fTotalTime <= m_pAnim->m_fTimeStep + m_pAnim->m_fCurrentTime)
            {
                if (m_bForceClimb || pad && pad->GetJump())
                {
                    m_nHeightForAnim++;
                    m_bChangeAnimation = true;
                }

                StartAnim(ped);
            }
            break;
        case ANIM_ID_CLIMB_IDLE:
            if (m_bForceClimb || !pad || pad->GetJump())
            {
                m_nHeightForAnim++;
                m_bChangeAnimation = true;
            }
            break;
        case ANIM_ID_CLIMB_PULL:
        case ANIM_ID_CLIMB_STAND:
            if (m_pAnim->m_pHierarchy->m_fTotalTime == m_pAnim->m_fCurrentTime)
            {
                m_nHeightForAnim++;
                m_bChangeAnimation = true;
            }
            break;
        case ANIM_ID_CLIMB_JUMP_B:
            if (m_pAnim->m_pHierarchy->m_fTotalTime <= m_pAnim->m_fTimeStep + m_pAnim->m_fCurrentTime)
            {
                m_nHeightForAnim++;
                m_bChangeAnimation = true;
            }
            break;
        default:
            if (m_pAnim->m_pHierarchy->m_fTotalTime == m_pAnim->m_fCurrentTime)
                if (m_bForceClimb || pad && pad->JumpJustDown())
                {
                    m_nHeightForAnim++;
                    m_bChangeAnimation = true;
                }
            break;
        }
    }

    if (pad && pad->GetExitVehicle())
    {
        MakeAbortable(ped, ABORT_PRIORITY_URGENT, 0);
    }
    else if (m_nHeightForPos != CLIMB_STANDUP && m_nHeightForPos != CLIMB_VAULT || !m_pAnim || !(m_pAnim->m_nFlags & ANIM_FLAG_STARTED))
    {
        if (m_nHeightForAnim == CLIMB_STANDUP && m_nHeightForPos < CLIMB_STANDUP && TestForVault(ped, &posn, fAngle))
            m_nHeightForAnim = CLIMB_VAULT;
    }
    else if (!TestForStandUp(ped, &posn, fAngle))
    {
        MakeAbortable(ped, ABORT_PRIORITY_URGENT, 0);
    }

    ped->m_fAimingRotation = fAngle;
    ped->m_fCurrentRotation = fAngle;
    ped->SetOrientation(0.0F, 0.0F, fAngle);

    return false;
}

bool CTaskSimpleClimb::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    if (_event && _event->GetEventPriority() < 71 && ped->m_fHealth > 0.0F)
        return false;

    if (m_pAnim)
    {
        m_pAnim->m_fBlendDelta = -4.0F;
        m_pAnim->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
        m_pAnim = nullptr;
    }

    ped->m_vecMoveSpeed.Set(0.0F, 0.0F, -0.05F);
    m_bIsFinished = true;
    return true;
}

// 0x6803A0
CEntity* CTaskSimpleClimb::TestForClimb(CPed* pPed, CVector& climbPos, float& fAngle, unsigned char& nSurfaceType, bool theBool)
{
    auto pEntity = (CEntity*)ScanToGrab(pPed, climbPos, fAngle, nSurfaceType, theBool, false, false, 0);

    if (pEntity)
    {
        CVector point = climbPos;
        float angle = fAngle;

        if (pEntity->IsPhysical())
        {
            point = pEntity->GetMatrix() * point;
            angle += pEntity->GetHeading();
        }

        point += CVector(-ms_fAtEdgeOffsetHorz * sin(angle), ms_fAtEdgeOffsetHorz * cos(angle), ms_fAtEdgeOffsetVert);

        CVector v;
        unsigned char surfaceType2;
        if (!ScanToGrab(pPed, v, angle, surfaceType2, false, true, false, &point))
        {
            return pEntity;
        }
        fAngle = -9999.9F;
    }

    return nullptr;
}

// 0x67DE10
void* CTaskSimpleClimb::ScanToGrabSectorList(CPtrList* sectorList, CPed* ped, CVector& targetPos, float& fAngle, unsigned char& nSurfaceType, bool flag1, bool bStandUp, bool bVault)
{
    if (!tempMatrix_Initialized)
    {
        tempMatrix_Initialized = true;
        tempMatrix = CMatrix();
    }

    CColModel* pColmodel = &ms_ClimbColModel;
    if (bStandUp)
        pColmodel = &ms_StandUpColModel;
    if (bVault)
        pColmodel = &ms_VaultColModel;

    CEntity* pCollidedEntity = nullptr;

    for (auto pNode = sectorList->GetNode(); pNode; pNode = pNode->pNext)
    {
        CEntity* pEntity = reinterpret_cast<CEntity*>(pNode->pItem);

        if (pEntity->m_nScanCode == CWorld::ms_nCurrentScanCode)
            continue;

        pEntity->m_nScanCode = CWorld::ms_nCurrentScanCode;

        if (!pEntity->m_bUsesCollision)
            continue;

        if (pEntity->IsBuilding()
            || (
                pEntity->IsObject()
                && (pEntity->IsStatic() || pEntity->AsObject()->physicalFlags.bDisableCollisionForce)
                && !pEntity->AsObject()->physicalFlags.bInfiniteMass
                )
            || (
                pEntity->IsVehicle()
                && (bStandUp || bVault || (ped->GetIntelligence()->GetTaskSwim() && pEntity->AsVehicle()->IsBoat()) || (pEntity->AsVehicle()->IsTrain() && pEntity->AsVehicle()->m_vecMoveSpeed.Magnitude2D() < 0.1F))
                )
            )
        {
            if (DistanceBetweenPoints(ped->GetMatrix() * pColmodel->GetBoundCenter(), pEntity->GetBoundCentre()) >= CModelInfo::GetModelInfo(pEntity->m_nModelIndex)->GetColModel()->GetBoundRadius() + pColmodel->GetBoundRadius())
                continue;

            int numSpheres = -1;
            if (pEntity->IsVehicle() && pEntity->AsVehicle()->IsBoat())
            {
                numSpheres = pEntity->GetColModel()->m_pColData->m_nNumSpheres;
                pEntity->GetColModel()->m_pColData->m_nNumSpheres = 0;
            }

            if (CCollision::ProcessColModels(*ped->m_matrix, *pColmodel, pEntity->GetMatrix(), *pEntity->GetColModel(), CWorld::m_aTempColPts, 0, 0, false) > 0)
            {
                if (bStandUp || bVault)
                {
                    if (pEntity->IsVehicle() && numSpheres > -1)
                        pEntity->GetColModel()->m_pColData->m_nNumSpheres = numSpheres;

                    return pEntity;
                }
                unsigned char nColSphereIndex = CWorld::m_aTempColPts->m_nPieceTypeA;

                if (nColSphereIndex == 0
                    || nColSphereIndex == 1
                    || nColSphereIndex == 2
                    || nColSphereIndex == 3
                    || nColSphereIndex == 4
                    || nColSphereIndex == 10
                    )
                {
                    if (pEntity->IsVehicle() && numSpheres > -1)
                        pEntity->GetColModel()->m_pColData->m_nNumSpheres = numSpheres;
                    return (void*)1;
                }

                auto relPosn = CWorld::m_aTempColPts->m_vecPoint - targetPos;
                if (nColSphereIndex == 16
                    || CWorld::m_aTempColPts->m_vecPoint.z <= targetPos.z && DotProduct(relPosn, ped->GetForward()) >= 0.0F
                    || !g_surfaceInfos->CanClimb(CWorld::m_aTempColPts->m_nSurfaceTypeB))
                {
                    if (pEntity->IsVehicle() && numSpheres > -1)
                        pEntity->GetColModel()->m_pColData->m_nNumSpheres = numSpheres;
                    continue;
                }

                int fatModifier = ped->m_pPlayerData && !ped->GetIntelligence()->GetTaskSwim() ? (int)CStats::GetFatAndMuscleModifier(STAT_MOD_0) : 0;

                if (!flag1 || fatModifier >= 1)
                {
                    if (nColSphereIndex == 5
                        || nColSphereIndex == 11
                        || nColSphereIndex == 17)
                    {
                        if (pEntity->IsVehicle() && numSpheres > -1)
                            pEntity->GetColModel()->m_pColData->m_nNumSpheres = numSpheres;
                        continue;
                    }

                    if (fatModifier >= 1 && (!flag1 || fatModifier >= 2))
                    {
                        if (nColSphereIndex == 6
                            || nColSphereIndex == 12
                            || nColSphereIndex == 18)
                        {
                            if (pEntity->IsVehicle() && numSpheres > -1)
                                pEntity->GetColModel()->m_pColData->m_nNumSpheres = numSpheres;
                            continue;
                        }
                    }
                }

                if (fabsf(CWorld::m_aTempColPts->m_vecNormal.x) <= 0.05F
                    && fabsf(CWorld::m_aTempColPts->m_vecNormal.y) <= 0.05F)
                {
                    targetPos = CWorld::m_aTempColPts->m_vecPoint;
                    fAngle = ped->m_fCurrentRotation;
                    nSurfaceType = CWorld::m_aTempColPts->m_nSurfaceTypeB;
                    pCollidedEntity = pEntity;
                }
                else
                {
                    CVector vecNormal = CWorld::m_aTempColPts->m_vecNormal;

                    if (DotProduct2D(vecNormal, CWorld::m_aTempColPts->m_vecPoint - ped->GetPosition()) < 0.0F)
                        vecNormal = -vecNormal;

                    if (DotProduct(vecNormal, ped->GetForward()) > 0.3F)
                    {
                        targetPos = CWorld::m_aTempColPts->m_vecPoint;
                        fAngle = atan2f(-vecNormal.x, vecNormal.y);
                        nSurfaceType = CWorld::m_aTempColPts->m_nSurfaceTypeB;
                        pCollidedEntity = pEntity;
                    }
                }

                tempMatrix = *ped->m_matrix;
                tempMatrix.SetTranslateOnly(CWorld::m_aTempColPts->m_vecPoint);

                if (CCollision::ProcessColModels(tempMatrix, ms_FindEdgeColModel, pEntity->GetMatrix(), *pEntity->GetColModel(), CWorld::m_aTempColPts, 0, 0, false) > 0)
                {
                    if (fabsf(CWorld::m_aTempColPts->m_vecNormal.x) <= 0.05F
                        && fabsf(CWorld::m_aTempColPts->m_vecNormal.y) <= 0.05F)
                    {
                        targetPos = CWorld::m_aTempColPts->m_vecPoint;
                        nSurfaceType = CWorld::m_aTempColPts->m_nSurfaceTypeB;
                    }
                    else
                    {
                        CVector vecNormal = CWorld::m_aTempColPts->m_vecNormal;

                        if (DotProduct2D(vecNormal, CWorld::m_aTempColPts->m_vecPoint - ped->GetPosition()) < 0.0F)
                            vecNormal = -vecNormal;

                        if (DotProduct(vecNormal, ped->GetForward()) > 0.3F)
                        {
                            targetPos = CWorld::m_aTempColPts->m_vecPoint;
                            fAngle = atan2f(-vecNormal.x, vecNormal.y);
                            nSurfaceType = CWorld::m_aTempColPts->m_nSurfaceTypeB;
                            pCollidedEntity = pEntity;
                        }
                    }
                }

                if (pEntity->IsVehicle() && numSpheres > -1)
                    pEntity->GetColModel()->m_pColData->m_nNumSpheres = numSpheres;
            }
            else if (pEntity->IsVehicle() && numSpheres > -1)
            {
                pEntity->GetColModel()->m_pColData->m_nNumSpheres = numSpheres;
            }
        }
    }

    return pCollidedEntity;
}

// 0x67FD30
CEntity* CTaskSimpleClimb::ScanToGrab(CPed* ped, CVector& climbPos, float& fAngle, unsigned char& pSurfaceType, bool flag1, bool bStandUp, bool bVault, CVector* pedPosition)
{
    if (!ms_ClimbColModel.m_pColData)
        CreateColModel();

    CEntity* pCollidedEntity = nullptr;

    CVector originalPedPosition = ped->GetPosition();

    if (pedPosition)
        ped->SetPosn(*pedPosition);

    climbPos = ped->GetPosition() + ped->GetForward() * 10.0F;

    auto outPoint = *ped->m_matrix * ms_ClimbColModel.GetBoundCenter();

    int x1 = (int)floorf((outPoint.x - ms_ClimbColModel.GetBoundRadius()) * 0.02F + 60.0F);
    int x2 = (int)floorf((outPoint.x + ms_ClimbColModel.GetBoundRadius()) * 0.02F + 60.0F);
    int y1 = (int)floorf((outPoint.y - ms_ClimbColModel.GetBoundRadius()) * 0.02F + 60.0F);
    int y2 = (int)floorf((outPoint.y + ms_ClimbColModel.GetBoundRadius()) * 0.02F + 60.0F);

    CWorld::IncrementCurrentScanCode();

    for (int y = y1; y <= y2; y++)
        for (int x = x1; x <= x2; x++)
        {
            auto scanResult1 = ScanToGrabSectorList(&GetSector(x, y)->m_buildings, ped, climbPos, fAngle, pSurfaceType, flag1, bStandUp, bVault);
            auto scanResult2 = ScanToGrabSectorList(&GetRepeatSector(x, y)->m_lists[REPEATSECTOR_OBJECTS], ped, climbPos, fAngle, pSurfaceType, flag1, bStandUp, bVault);
            if (!scanResult2)
                scanResult2 = ScanToGrabSectorList(&GetRepeatSector(x, y)->m_lists[REPEATSECTOR_VEHICLES], ped, climbPos, fAngle, pSurfaceType, flag1, bStandUp, bVault);

            if ((int)(scanResult1) == 1 || (int)(scanResult2) == 1)
                return nullptr;

            auto pEntity = (CEntity*)(scanResult2 ? scanResult2 : scanResult1);

            if (pEntity)
            {
                if (bStandUp || bVault)
                {
                    if (pedPosition)
                        ped->SetPosn(originalPedPosition);

                    return pEntity;
                }
                else
                    pCollidedEntity = pEntity;
            }
        }

    if (pedPosition)
        ped->SetPosn(originalPedPosition);

    if (pCollidedEntity)
    {
        if (pCollidedEntity->IsPhysical())
        {
            climbPos = Invert(pCollidedEntity->GetMatrix()) * climbPos;
            fAngle -= pCollidedEntity->GetHeading();
        }
    }

    return pCollidedEntity;
}

// 0x67A890
bool CTaskSimpleClimb::CreateColModel()
{
    ms_ClimbColModel.AllocateData(22, 0, 0, 0, 0, 0);
    ms_ClimbColModel.m_pColData->m_pSpheres[0].Set(0.4F, { 0.0F, -0.06F, 1.2F }, 0, 0, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[1].Set(0.4F, { 0.0F, -0.06F, 1.7F }, 1, 1, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[2].Set(0.4F, { 0.0F, -0.06F, 2.2F }, 2, 2, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[3].Set(0.4F, { 0.0F, -0.06F, 2.5F }, 3, 3, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[4].Set(0.4F, { 0.0F, 0.5F, 2.9F }, 4, 4, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[5].Set(0.4F, { 0.0F, 0.5F, 2.4F }, 5, 5, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[6].Set(0.4F, { 0.0F, 0.5F, 1.9F }, 6, 6, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[7].Set(0.4F, { 0.0F, 0.5F, 1.4F }, 7, 7, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[8].Set(0.4F, { 0.0F, 0.5F, 0.9F }, 8, 8, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[9].Set(0.4F, { 0.0F, 0.5F, 0.4F }, 9, 9, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[10].Set(0.4F, { 0.0F, 1.0F, 2.9F }, 10, 10, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[11].Set(0.4F, { 0.0F, 1.0F, 2.4F }, 11, 11, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[12].Set(0.4F, { 0.0F, 1.0F, 1.9F }, 12, 12, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[13].Set(0.4F, { 0.0F, 1.0F, 1.4F }, 13, 13, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[14].Set(0.4F, { 0.0F, 1.0F, 0.9F }, 14, 14, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[15].Set(0.4F, { 0.0F, 1.0F, 0.4F }, 15, 15, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[16].Set(0.4F, { 0.0F, 1.5F, 2.9F }, 16, 16, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[17].Set(0.4F, { 0.0F, 1.5F, 2.4F }, 17, 17, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[18].Set(0.4F, { 0.0F, 1.5F, 1.9F }, 18, 18, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[19].Set(0.4F, { 0.0F, 1.5F, 1.4F }, 19, 19, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[20].Set(0.4F, { 0.0F, 1.5F, 0.9F }, 20, 20, 255);
    ms_ClimbColModel.m_pColData->m_pSpheres[21].Set(0.4F, { 0.0F, 1.5F, 0.4F }, 21, 21, 255);
    ms_ClimbColModel.m_boundSphere.Set(2.02F, { 0.0F, 0.75F, 1.65F });
    ms_ClimbColModel.GetBoundingBox().Set({ -0.4F, -0.46F, 0.0F }, { 0.4F, 1.9F, 3.3F });
    ms_ClimbColModel.m_boundSphere.m_nMaterial = 0;

    ms_StandUpColModel.AllocateData(7, 0, 0, 0, 0, 0);
    ms_StandUpColModel.m_pColData->m_pSpheres[0].Set(0.35F, { 0.0F, 0.6F, 1.75F }, 0, 0, 255);
    ms_StandUpColModel.m_pColData->m_pSpheres[1].Set(0.35F, { 0.0F, 0.6F, 1.3F }, 1, 1, 255);
    ms_StandUpColModel.m_pColData->m_pSpheres[2].Set(0.35F, { 0.0F, 0.6F, 0.85F }, 2, 2, 255);
    ms_StandUpColModel.m_pColData->m_pSpheres[3].Set(0.35F, { 0.0F, 0.3F, 0.65F }, 3, 3, 255);
    ms_StandUpColModel.m_pColData->m_pSpheres[4].Set(0.35F, { 0.0F, 0.0F, 0.5F }, 4, 4, 255);
    ms_StandUpColModel.m_pColData->m_pSpheres[5].Set(0.35F, { 0.0F, 0.0F, 0.1F }, 5, 5, 255);
    ms_StandUpColModel.m_pColData->m_pSpheres[6].Set(0.35F, { 0.0F, 0.0F, -0.3F }, 6, 6, 255);
    ms_StandUpColModel.m_boundSphere.Set(1.5F, { 0.0F, 0.3F, 0.7F });
    ms_StandUpColModel.GetBoundingBox().Set({ -0.35F, -0.35F, -0.65F }, { 0.35F, 0.95F, 2.1F });
    ms_StandUpColModel.m_boundSphere.m_nMaterial = 0;

    ms_VaultColModel.AllocateData(6, 0, 0, 0, 0, 0);
    ms_VaultColModel.m_pColData->m_pSpheres[0].Set(0.3F, { 0.0F, 1.1F, -0.2F }, 0, 0, 255);
    ms_VaultColModel.m_pColData->m_pSpheres[1].Set(0.3F, { 0.0F, 1.1F, 0.2F }, 1, 1, 255);
    ms_VaultColModel.m_pColData->m_pSpheres[2].Set(0.3F, { 0.0F, 1.1F, 0.6F }, 2, 2, 255);
    ms_VaultColModel.m_pColData->m_pSpheres[3].Set(0.3F, { 0.0F, 0.7F, 0.6F }, 3, 3, 255);
    ms_VaultColModel.m_pColData->m_pSpheres[4].Set(0.3F, { 0.0F, 0.35F, 0.6F }, 4, 4, 255);
    ms_VaultColModel.m_pColData->m_pSpheres[5].Set(0.3F, { 0.0F, 0.0F, 0.6F }, 5, 5, 255);
    ms_VaultColModel.m_boundSphere.Set(1.15F, { 0.0F, 0.5F, 0.1F });
    ms_VaultColModel.GetBoundingBox().Set({ -0.35F, -0.35F, -0.6F }, { 0.35F, 1.3F, 0.85F });
    ms_VaultColModel.m_boundSphere.m_nMaterial = 0;

    ms_FindEdgeColModel.AllocateData(16, 0, 0, 0, 0, 0);
    ms_FindEdgeColModel.m_pColData->m_pSpheres[0].Set(0.3F, { 0.0F, -0.5F, 0.5F }, 0, 0, 255);
    ms_FindEdgeColModel.m_pColData->m_pSpheres[1].Set(0.3F, { 0.0F, -0.5F, 0.3F }, 1, 1, 255);
    ms_FindEdgeColModel.m_pColData->m_pSpheres[2].Set(0.3F, { 0.0F, -0.5F, 0.1F }, 2, 2, 255);
    ms_FindEdgeColModel.m_pColData->m_pSpheres[3].Set(0.3F, { 0.0F, -0.5F, -0.1F }, 3, 3, 255);
    ms_FindEdgeColModel.m_pColData->m_pSpheres[4].Set(0.3F, { 0.0F, -0.3F, 0.5F }, 4, 4, 255);
    ms_FindEdgeColModel.m_pColData->m_pSpheres[5].Set(0.3F, { 0.0F, -0.3F, 0.3F }, 5, 5, 255);
    ms_FindEdgeColModel.m_pColData->m_pSpheres[6].Set(0.3F, { 0.0F, -0.3F, 0.1F }, 6, 6, 255);
    ms_FindEdgeColModel.m_pColData->m_pSpheres[7].Set(0.3F, { 0.0F, -0.3F, -0.1F }, 7, 7, 255);
    ms_FindEdgeColModel.m_pColData->m_pSpheres[8].Set(0.3F, { 0.0F, -0.1F, 0.5F }, 8, 8, 255);
    ms_FindEdgeColModel.m_pColData->m_pSpheres[9].Set(0.3F, { 0.0F, -0.1F, 0.3F }, 9, 9, 255);
    ms_FindEdgeColModel.m_pColData->m_pSpheres[10].Set(0.3F, { 0.0F, -0.1F, 0.1F }, 10, 10, 255);
    ms_FindEdgeColModel.m_pColData->m_pSpheres[11].Set(0.3F, { 0.0F, -0.1F, -0.1F }, 11, 11, 255);
    ms_FindEdgeColModel.m_pColData->m_pSpheres[12].Set(0.3F, { 0.0F, 0.1F, 0.5F }, 12, 12, 255);
    ms_FindEdgeColModel.m_pColData->m_pSpheres[13].Set(0.3F, { 0.0F, 0.1F, 0.3F }, 13, 13, 255);
    ms_FindEdgeColModel.m_pColData->m_pSpheres[14].Set(0.3F, { 0.0F, 0.1F, 0.1F }, 14, 14, 255);
    ms_FindEdgeColModel.m_pColData->m_pSpheres[15].Set(0.3F, { 0.0F, 0.1F, -0.1F }, 15, 15, 255);
    ms_FindEdgeColModel.m_boundSphere.Set(0.9F, { 0.0F, -0.2F, 0.2F });
    ms_FindEdgeColModel.GetBoundingBox().Set({ -0.3F, -0.8F, -0.4F }, { 0.3F, 0.4F, 0.8F });
    ms_FindEdgeColModel.m_boundSphere.m_nMaterial = 0;

    return true;
}

// 0x67A250
void CTaskSimpleClimb::Shutdown()
{
    ms_ClimbColModel.RemoveCollisionVolumes();
    ms_StandUpColModel.RemoveCollisionVolumes();
    ms_VaultColModel.RemoveCollisionVolumes();
    ms_FindEdgeColModel.RemoveCollisionVolumes();
}

// 0x680570
bool CTaskSimpleClimb::TestForStandUp(CPed* ped, CVector* point, float fAngle)
{
    CVector v;
    float angle;
    unsigned char nSurfaceType;
    CVector pedPos = *point + CVector(-ms_fAtEdgeOffsetHorz * sin(fAngle), ms_fAtEdgeOffsetHorz * cos(fAngle), ms_fAtEdgeOffsetVert);
    return !ScanToGrab(ped, v, angle, nSurfaceType, false, true, false, &pedPos);
}

// 0x6804D0
bool CTaskSimpleClimb::TestForVault(CPed* ped, CVector* point, float fAngle)
{
    CVector v;
    float angle;
    unsigned char nSurfaceType;
    CVector pedPos = *point + CVector(-ms_fAtEdgeOffsetHorz * sin(fAngle), ms_fAtEdgeOffsetHorz * cos(fAngle), ms_fAtEdgeOffsetVert);
    return m_pClimbEnt->m_nType != ENTITY_TYPE_VEHICLE && !ScanToGrab(ped, v, angle, nSurfaceType, false, false, true, &pedPos);
}

// 0x67DBE0
void CTaskSimpleClimb::StartAnim(CPed* ped)
{
    switch (m_nHeightForAnim)
    {
    case CLIMB_GRAB:
        if (m_pAnim)
        {
            m_pAnim->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
            m_pAnim = CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_CLIMB_IDLE, 4.0F);
        }
        else
        {
            m_pAnim = CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_CLIMB_JUMP, 8.0F);
        }
        m_nHeightForPos = CLIMB_GRAB;
        m_bChangePosition = false;
        m_bChangeAnimation = false;
        break;
    case CLIMB_PULLUP:
        if (m_nHeightForPos == CLIMB_NOT_READY)
        {
            m_nHeightForAnim = CLIMB_STANDUP;
            m_nHeightForPos = CLIMB_STANDUP;
            m_pAnim = CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_CLIMB_STAND, 4.0F);
            m_pAnim->m_nFlags &= ~ANIM_FLAG_STARTED;
        }
        else
        {
            m_pAnim->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
            m_pAnim = CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_CLIMB_PULL, 1000.0F);
            m_nHeightForPos = CLIMB_PULLUP;
        }
        m_bChangePosition = false;
        m_bChangeAnimation = false;
        break;
    case CLIMB_STANDUP:
        if (m_pAnim)
            m_pAnim->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
        m_pAnim = CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_CLIMB_STAND, 1000.0F);
        m_bChangePosition = true;
        m_bChangeAnimation = false;
        break;
    case CLIMB_FINISHED:
    case CLIMB_FINISHED_V:
        CAnimManager::BlendAnimation(ped->m_pRwClump, ped->m_nAnimGroup, ANIM_ID_IDLE, 1000.0F);
        ped->SetMoveState(PEDMOVE_STILL);
        ped->SetMoveAnim();
        if (ped->m_pPlayerData)
            ped->m_pPlayerData->m_fMoveBlendRatio = 0.0F;
        if (m_pAnim)
            m_pAnim->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
        m_pAnim = CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_DEFAULT, m_nHeightForAnim == CLIMB_FINISHED_V ? ANIM_ID_CLIMB_JUMP2FALL : ANIM_ID_CLIMB_STAND_FINISH, 1000.0F);
        m_bChangePosition = true;
        m_bChangeAnimation = false;
        break;
    case CLIMB_VAULT:
        if (m_pAnim)
            m_pAnim->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
        m_pAnim = CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_CLIMB_JUMP_B, m_pAnim && m_pAnim->m_nAnimId == ANIM_ID_CLIMB_STAND ? 16.0F : 1000.0F);
        m_bChangePosition = true;
        m_bChangeAnimation = false;
        break;
    default:
        break;
    }

    if (m_pAnim)
    {
        m_pAnim->SetDeleteCallback(DeleteAnimCB, this);
        if (ped->m_pPlayerData
            && m_pAnim->m_nFlags & ANIM_FLAG_STARTED
            && (m_pAnim->m_nAnimId == ANIM_ID_CLIMB_PULL || m_pAnim->m_nAnimId == ANIM_ID_CLIMB_STAND || m_pAnim->m_nAnimId == ANIM_ID_CLIMB_JUMP_B))
        {
            m_pAnim->m_fSpeed = CStats::GetFatAndMuscleModifier(STAT_MOD_1);
        }
    }
}


// 0x67A320
void CTaskSimpleClimb::StartSpeech(CPed* ped)
{
    if (ped->IsPlayer())
    {
        if (m_nHeightForAnim == CLIMB_PULLUP)
            ped->Say(354, 0, 1.0F, 0, 0, 0);
        else if (m_nHeightForAnim == CLIMB_STANDUP)
            ped->Say(355, 0, 1.0F, 0, 0, 0);
    }
}

// 0x67A380
void CTaskSimpleClimb::DeleteAnimCB(CAnimBlendAssociation* pAnim, void* data)
{
    reinterpret_cast<CTaskSimpleClimb*>(data)->m_pAnim = nullptr;
}

// 0x67A5D0
void CTaskSimpleClimb::GetCameraStickModifier(CEntity* pEntity, float& fVerticalAngle, float& fHorizontalAngle, float& a5, float& a6)
{
    if (!m_pAnim)
        return;

    if (m_pAnim->m_nAnimId == ANIM_ID_CLIMB_JUMP_B)
    {
        CVector vec = m_vecHandholdPos;
        float fAngle = m_fHandholdHeading;

        if (m_pClimbEnt->IsPhysical())
        {
            vec = *m_pClimbEnt->m_matrix * vec;
            fAngle += m_pClimbEnt->GetHeading();
        }

        vec += CVector(-ms_fVaultOffsetHorz * sin(fAngle), ms_fVaultOffsetHorz * cos(fAngle), ms_fVaultOffsetVert);

        CColPoint colPoint;
        CEntity* pColEntity;
        if (CWorld::ProcessVerticalLine(vec, vec.z - 3.0F, colPoint, pColEntity, true, true, false, true, false, false, 0))
        {
            m_nFallAfterVault = (char)(std::max(vec.z - colPoint.m_vecPoint.z - 1.0F, 0.0F) * 10.0F);
        }
        else
        {
            m_nFallAfterVault = 20;
        }

        float v20 = m_nFallAfterVault > 8 ? -0.6F : -0.1F;
        if (fVerticalAngle > v20)
        {
            a5 = std::max((fVerticalAngle - v20) * -0.05F, -0.05F);
        }
    }
    else if (m_pAnim->m_nAnimId == ANIM_ID_CLIMB_IDLE)
    {
        float fHeading = m_pClimbEnt->GetHeading() - HALF_PI;
        if (fHeading > fHorizontalAngle + PI)
            fHeading -= TWO_PI;
        else if (fHeading < fHorizontalAngle - PI)
            fHeading += TWO_PI;

        if (fHeading > fHorizontalAngle + HALF_PI + 0.2F)
            a6 = 0.02F;
        else if (fHeading > fHorizontalAngle + HALF_PI && a6 < 0.0F)
            a6 = 0.0F;
        else if (fHeading < fHorizontalAngle - HALF_PI - 0.2F)
            a6 = -0.02F;
        else if (fHeading < fHorizontalAngle - HALF_PI && a6 > 0.0F)
            a6 = 0.0F;
    }
}

// 0x67A390
void CTaskSimpleClimb::GetCameraTargetPos(CPed* ped, CVector& vecTarget)
{
    vecTarget = ped->GetPosition();

    if (!m_pAnim)
        return;

    float fProgress = m_pAnim->m_fCurrentTime / m_pAnim->m_pHierarchy->m_fTotalTime;
    float offsetHorz, offsetVert;

    switch (m_pAnim->m_nAnimId)
    {
    case ANIM_ID_FALL_GLIDE:
    case ANIM_ID_CLIMB_JUMP2FALL:
        offsetHorz = ms_fVaultOffsetHorz;
        offsetVert = ms_fVaultOffsetVert;
        break;
    case ANIM_ID_CLIMB_PULL:
        offsetHorz = lerp(ms_fHangingOffsetHorz, ms_fAtEdgeOffsetHorz, fProgress);
        offsetVert = lerp(ms_fHangingOffsetVert, ms_fAtEdgeOffsetVert, fProgress);
        break;
    case ANIM_ID_CLIMB_STAND:
        offsetHorz = lerp(ms_fAtEdgeOffsetHorz, ms_fStandUpOffsetHorz, fProgress);
        offsetVert = lerp(ms_fAtEdgeOffsetVert, ms_fStandUpOffsetVert, fProgress);
        break;
    case ANIM_ID_CLIMB_STAND_FINISH:
        offsetHorz = ms_fStandUpOffsetHorz;
        offsetVert = ms_fStandUpOffsetVert;
        break;
    case ANIM_ID_CLIMB_JUMP_B:
        offsetHorz = lerp(ms_fAtEdgeOffsetHorz, ms_fVaultOffsetHorz, fProgress);
        offsetVert = lerp(ms_fAtEdgeOffsetVert, ms_fVaultOffsetVert, fProgress);
        break;
    default:
        return;
    }

    CVector point = m_vecHandholdPos;
    float fAngle = m_fHandholdHeading;
    if (m_pClimbEnt->IsPhysical())
    {
        point = m_pClimbEnt->GetMatrix() * point;
        fAngle += m_pClimbEnt->GetHeading();
    }

    vecTarget = point + CVector(-offsetHorz * sin(fAngle), offsetHorz * cos(fAngle), offsetVert);
}


