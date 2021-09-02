#include "StdInc.h"

CBoat* (&CBoat::apFrameWakeGeneratingBoats)[NUM_WAKE_GEN_BOATS] = *(CBoat*(*)[NUM_WAKE_GEN_BOATS])0xC27994;
float& CBoat::MAX_WAKE_LENGTH = *(float*)0x8D3938; // 50.0
float& CBoat::MIN_WAKE_INTERVAL = *(float*)0x8D393C; // 2.0
float& CBoat::WAKE_LIFETIME = *(float*)0x8D3940; // 150.0
float& CBoat::fShapeLength = *(float*)0x8D3944; // 0.4
float& CBoat::fShapeTime = *(float*)0x8D3948; // 0.05
float& CBoat::fRangeMult = *(float*)0x8D394C; // 0.6

int16* CBoat::waUnknArr = (int16*)0xC279A4;
int16* CBoat::waUnknArr2 = (int16*)0xC279AC;

RxObjSpace3DVertex* CBoat::aRenderVertices = (RxObjSpace3DVertex*)0xC278F8;
RxVertexIndex* CBoat::auRenderIndices = (RxVertexIndex*)0xC27988;

void CBoat::InjectHooks()
{
    //Virtual
    ReversibleHooks::Install("CBoat", "SetModelIndex", 0x6F1140, &CBoat::SetModelIndex_Reversed);
    ReversibleHooks::Install("CBoat", "ProcessControl", 0x6F1770, &CBoat::ProcessControl_Reversed);
    ReversibleHooks::Install("CBoat", "Teleport", 0x6F20E0, &CBoat::Teleport_Reversed);
    ReversibleHooks::Install("CBoat", "PreRender", 0x6F1180, &CBoat::PreRender_Reversed);
    ReversibleHooks::Install("CBoat", "Render", 0x6F0210, &CBoat::Render_Reversed);
    ReversibleHooks::Install("CBoat", "ProcessControlInputs", 0x6F0A10, &CBoat::ProcessControlInputs_Reversed);
    ReversibleHooks::Install("CBoat", "GetComponentWorldPosition", 0x6F01D0, &CBoat::GetComponentWorldPosition_Reversed);
    ReversibleHooks::Install("CBoat", "ProcessOpenDoor", 0x6F0190, &CBoat::ProcessOpenDoor_Reversed);
    ReversibleHooks::Install("CBoat", "BlowUpCar", 0x6F21B0, &CBoat::BlowUpCar_Reversed);

    //Class methods
    ReversibleHooks::Install("CBoat", "PruneWakeTrail", 0x6F0E20, &CBoat::PruneWakeTrail);
    ReversibleHooks::Install("CBoat", "AddWakePoint", 0x6F2550, &CBoat::AddWakePoint);
    ReversibleHooks::Install("CBoat", "SetupModelNodes", 0x6F01A0, &CBoat::SetupModelNodes);
    ReversibleHooks::Install("CBoat", "DebugCode", 0x6F0D00, &CBoat::DebugCode);
    ReversibleHooks::Install("CBoat", "ModifyHandlingValue", 0x6F0DE0, &CBoat::ModifyHandlingValue);
    ReversibleHooks::Install("CBoat", "PrintThrustAndRudderInfo", 0x6F0D90, &CBoat::PrintThrustAndRudderInfo);

    //Other
    ReversibleHooks::Install("CBoat", "FillBoatList", 0x6F2710, &CBoat::FillBoatList);
    ReversibleHooks::Install("CBoat", "IsSectorAffectedByWake", 0x6F0E80, &CBoat::IsSectorAffectedByWake);
    ReversibleHooks::Install("CBoat", "IsVertexAffectedByWake", 0x6F0F50, &CBoat::IsVertexAffectedByWake);
    ReversibleHooks::Install("CBoat", "CheckForSkippingCalculations", 0x6F10C0, &CBoat::CheckForSkippingCalculations);
    ReversibleHooks::Install("CBoat", "GetBoatAtomicObjectCB", 0x6F00D0, &GetBoatAtomicObjectCB);
}

CBoat::CBoat(int32 modelIndex, eVehicleCreatedBy createdBy) : CVehicle(createdBy)
{
    memset(&m_boatFlap, 0, sizeof(m_boatFlap));
    auto pModelInfo = reinterpret_cast<CVehicleModelInfo*>(CModelInfo::GetModelInfo(modelIndex));
    const auto iHandlingId = pModelInfo->m_nHandlingId;
    m_vehicleSubType = eVehicleType::VEHICLE_BOAT;
    m_vehicleType = eVehicleType::VEHICLE_BOAT;
    m_vecBoatMoveForce.Set(0.0F, 0.0F, 0.0F);
    m_vecBoatTurnForce.Set(0.0F, 0.0F, 0.0F);
    m_nPadNumber = 0;
    m_fMovingHiRotation = 0.0;
    m_fPropSpeed = 0.0;
    m_fPropRotation = 0.0;
    m_nAttackPlayerTime = CTimer::m_snTimeInMilliseconds;
    CVehicle::SetModelIndex(modelIndex);
    CBoat::SetupModelNodes();

    m_pHandlingData = &gHandlingDataMgr.m_aVehicleHandling[iHandlingId];
    m_nHandlingFlagsIntValue = m_pHandlingData->m_nHandlingFlags;
    m_pFlyingHandlingData = gHandlingDataMgr.GetFlyingPointer(iHandlingId);
    m_pBoatHandling = gHandlingDataMgr.GetBoatPointer(iHandlingId);

    pModelInfo->ChooseVehicleColour(m_nPrimaryColor, m_nSecondaryColor, m_nTertiaryColor, m_nQuaternaryColor, 1);

    m_fMass = m_pHandlingData->m_fMass;
    m_fTurnMass = m_pHandlingData->m_fTurnMass * 0.5F;
    m_vecCentreOfMass = m_pHandlingData->m_vecCentreOfMass;
    m_fElasticity = 0.1F;
    m_fBuoyancyConstant = m_pHandlingData->m_fBuoyancyConstant;

    if (m_pHandlingData->m_fDragMult <= 0.01F)
        m_fAirResistance = m_pHandlingData->m_fDragMult;
    else
        m_fAirResistance = m_pHandlingData->m_fDragMult / 1000.0F * 0.5F;

    physicalFlags.bTouchingWater = true;
    physicalFlags.bSubmergedInWater = true;
    m_nBoatFlags.bAnchored = true;
    m_nBoatFlags.bMovingOnWater = true;
    m_nBoatFlags.bOnWater = true;

    m_fSteerAngle = 0.0;
    m_fGasPedal = 0.0;
    m_fBreakPedal = 0.0;
    m_fRawSteerAngle = 0.0;
    field_63C = 0;
    m_fLastWaterImmersionDepth = 7.0F;
    field_604 = 0;

    m_fAnchoredAngle = -10000.0f;
    m_fBurningTimer = 0.0;
    m_pWhoDestroyedMe = nullptr;
    m_nNumWaterTrailPoints = 0;
    memset(m_afWakePointLifeTime, 0, sizeof(m_afWakePointLifeTime));

    m_nAmmoInClip = 20;
    m_boatFlap.m_nAxis = eRotationAxis::AXIS_Y;
    if (m_nModelIndex == MODEL_MARQUIS)
    {
        m_boatFlap.m_fOpenAngle = PI / 10.0F;
        m_boatFlap.m_fClosedAngle = -PI / 10.0F;
        m_boatFlap.m_nDirn = 4;
    }
    else
    {
        m_boatFlap.m_fOpenAngle = TWO_PI / 10.0F;
        m_boatFlap.m_fClosedAngle = -TWO_PI / 10.0F;
        m_boatFlap.m_nDirn = 3;
    }

    m_vehicleAudio.Initialise(this);
    for (size_t i = 0; i < 2; ++i)
        m_apPropSplashFx[i] = nullptr;
}

CBoat::~CBoat()
{
    if (m_pFireParticle) {
        m_pFireParticle->Kill();
        m_pFireParticle = nullptr;
    }

    for (auto& pSplashPart : m_apPropSplashFx) {
        if (!pSplashPart)
            continue;

        pSplashPart->Kill();
        pSplashPart = nullptr;
    }

    m_vehicleAudio.Terminate();
}

void CBoat::SetModelIndex(uint32 index)
{
    return CBoat::SetModelIndex_Reversed(index);
}

void CBoat::ProcessControl()
{
    return CBoat::ProcessControl_Reversed();
}

void CBoat::Teleport(CVector destination, bool resetRotation)
{
    return CBoat::Teleport_Reversed(destination, resetRotation);
}

void CBoat::PreRender()
{
    return CBoat::PreRender_Reversed();
}

void CBoat::Render()
{
    return CBoat::Render_Reversed();
}

void CBoat::ProcessControlInputs(uint8 playerNum)
{
    return CBoat::ProcessControlInputs_Reversed(playerNum);
}

void CBoat::GetComponentWorldPosition(int32 componentId, CVector& posnOut)
{
    return CBoat::GetComponentWorldPosition_Reversed(componentId, posnOut);
}

void CBoat::ProcessOpenDoor(CPed* ped, uint32 doorComponentId, uint32 animGroup, uint32 arg3, float arg4)
{
    return CBoat::ProcessOpenDoor_Reversed(ped, doorComponentId, animGroup, arg3, arg4);
}

void CBoat::BlowUpCar(CEntity* damager, uint8 bHideExplosion)
{
    return CBoat::BlowUpCar_Reversed(damager, bHideExplosion);
}

inline void CBoat::SetupModelNodes()
{
    memset(m_aBoatNodes, 0, sizeof(m_aBoatNodes));
    CClumpModelInfo::FillFrameArray(m_pRwClump, m_aBoatNodes);
}

void CBoat::DebugCode()
{
    if (FindPlayerVehicle(-1, false) != static_cast<CVehicle*>(this))
        return;

    if (CPad::GetPad(m_nPadNumber)->NewState.Start)
        return;

    auto pPad = CPad::GetPad(0);
    if (!pPad->NewState.DPadLeft || pPad->OldState.DPadLeft)
        return;

    auto uiHandlingId = reinterpret_cast<CVehicleModelInfo*>(CModelInfo::ms_modelInfoPtrs[m_nModelIndex])->m_nHandlingId;
    m_pHandlingData = &gHandlingDataMgr.m_aVehicleHandling[uiHandlingId];
    CBoat::SetupModelNodes();
}

void CBoat::PrintThrustAndRudderInfo()
{
    char cBuffer[64];
    sprintf(cBuffer, "Thrust %3.2f", m_pHandlingData->m_transmissionData.m_fEngineAcceleration * m_pHandlingData->m_fMass);
    sprintf(cBuffer, "Rudder Angle  %3.2f", m_pHandlingData->m_fSteeringLock);
}

void CBoat::ModifyHandlingValue(bool const& bIncrement)
{
    auto fChange = -1.0F;
    if (bIncrement)
        fChange = 1.0F;

    if (field_63C == 4)
        m_pHandlingData->m_fSteeringLock += fChange;
}

void CBoat::PruneWakeTrail()
{
    int16_t iInd;
    for (iInd = 0; iInd < 32; ++iInd) {
        auto fPointLifeTime = m_afWakePointLifeTime[iInd];
        if (fPointLifeTime <= 0.0F)
            break;

        if (fPointLifeTime <= CTimer::ms_fTimeStep) {
            m_afWakePointLifeTime[iInd] = 0.0F;
            break;
        }

        m_afWakePointLifeTime[iInd] -= CTimer::ms_fTimeStep;
    }

    if (iInd >= 32)
        return;

    m_nNumWaterTrailPoints = iInd;
}

void CBoat::AddWakePoint(CVector posn)
{
    auto ucIntensity = static_cast<uint8>(m_vecMoveSpeed.Magnitude() * 100.0F);

    // No wake points exisiting, early out
    if (m_afWakePointLifeTime[0] < 0.0F) {
        m_anWakePointIntensity[0] = ucIntensity;
        m_avecWakePoints[0].Set(posn.x, posn.y);
        m_afWakePointLifeTime[0] = CBoat::WAKE_LIFETIME;

        m_nNumWaterTrailPoints = 1;
        return;
    }

    if (DistanceBetweenPoints2D(posn, m_avecWakePoints[0]) <= CBoat::MIN_WAKE_INTERVAL)
        return;

    int16 uiMaxWakePoints = 31;
    if (!m_nStatus == eEntityStatus::STATUS_PLAYER) {
        if (m_nCreatedBy == eVehicleCreatedBy::MISSION_VEHICLE)
            uiMaxWakePoints = 20;
        else
            uiMaxWakePoints = 15;
    }
    int16 uiCurWaterPoints = std::min(m_nNumWaterTrailPoints, uiMaxWakePoints);

    // Shift wake points
    if (m_nNumWaterTrailPoints >= uiMaxWakePoints || uiCurWaterPoints > 0) {
        for (uint32 iInd = uiCurWaterPoints; iInd > 0; --iInd) {
            m_avecWakePoints[iInd] = m_avecWakePoints[iInd - 1];
            m_anWakePointIntensity[iInd] = m_anWakePointIntensity[iInd - 1];
            m_afWakePointLifeTime[iInd] = m_afWakePointLifeTime[iInd - 1];
        }
    }

    m_anWakePointIntensity[0] = ucIntensity;
    m_avecWakePoints[0].Set(posn.x, posn.y);
    m_afWakePointLifeTime[0] = CBoat::WAKE_LIFETIME;
    if (m_nNumWaterTrailPoints < 32)
        ++m_nNumWaterTrailPoints;
}

bool CBoat::IsSectorAffectedByWake(CVector2D vecPos, float fOffset, CBoat** ppBoats)
{
    if (!CBoat::apFrameWakeGeneratingBoats[0])
        return false;

    bool bWakeFound = false;
    for (int32_t i = 0; i < NUM_WAKE_GEN_BOATS; ++i) {
        auto pBoat = CBoat::apFrameWakeGeneratingBoats[i];
        if (!pBoat)
            continue;

        if (!pBoat->m_nNumWaterTrailPoints)
            continue;

        for (int32_t iTrail = 0; iTrail < pBoat->m_nNumWaterTrailPoints; ++iTrail) {
            auto fDist = (CBoat::WAKE_LIFETIME - pBoat->m_afWakePointLifeTime[iTrail]) * CBoat::fShapeTime + static_cast<float>(iTrail) * CBoat::fShapeLength + fOffset;
            if (fabs(pBoat->m_avecWakePoints[iTrail].x - vecPos.x) >= fDist
                || fabs(pBoat->m_avecWakePoints[iTrail].y - vecPos.y) >= fDist)
                continue;

            ppBoats[bWakeFound] = pBoat;
            bWakeFound = true;
            break;
        }
    }

    return bWakeFound;
}

float CBoat::IsVertexAffectedByWake(CVector vecPos, CBoat* pBoat, int16 wIndex, bool bUnkn)
{
    if (bUnkn) {
        CBoat::waUnknArr[wIndex] = 0;
        CBoat::waUnknArr2[wIndex] = 8;
    }
    else if (CBoat::waUnknArr[wIndex] > 0)
        return 0.0F;

    if (!pBoat->m_nNumWaterTrailPoints)
        return 0.0F;

    for (int32_t iTrail = 0; iTrail < pBoat->m_nNumWaterTrailPoints; ++iTrail) {
        auto fWakeDistSquared = powf((CBoat::WAKE_LIFETIME - pBoat->m_afWakePointLifeTime[iTrail]) * CBoat::fShapeTime + static_cast<float>(iTrail) * CBoat::fShapeLength, 2);
        auto fTrailDistSquared = (pBoat->m_avecWakePoints[iTrail] - vecPos).SquaredMagnitude();
        if (fTrailDistSquared < fWakeDistSquared)
        {
            CBoat::waUnknArr2[wIndex] = 0;
            float fContrib = sqrtf(fTrailDistSquared / fWakeDistSquared) * CBoat::fRangeMult + (CBoat::WAKE_LIFETIME - pBoat->m_afWakePointLifeTime[iTrail]) * 1.2F / CBoat::WAKE_LIFETIME;
            fContrib = std::min(1.0F, fContrib);
            return 1.0F - fContrib;
        }

        auto fDistDiff = fTrailDistSquared - fWakeDistSquared;
        if (fDistDiff > 20.0F) {
            if (CBoat::waUnknArr2[wIndex] > 3)
                CBoat::waUnknArr2[wIndex] = 3;
        }
        else if (fDistDiff > 10.0F) {
            if (CBoat::waUnknArr2[wIndex] > 2)
                CBoat::waUnknArr2[wIndex] = 2;
        }
    }

    return 0.0F;
}

void CBoat::CheckForSkippingCalculations()
{
    for (size_t ind = 0; ind < 4; ++ind) {
        auto iVal = CBoat::waUnknArr2[ind];
        if (iVal <= 0 || iVal >= 8) {
            if (CBoat::waUnknArr[ind] <= 0) {
                CBoat::waUnknArr2[ind] = 8;
                continue;
            }
            CBoat::waUnknArr[ind] = iVal - 1;
        }
        else if (iVal <= CBoat::waUnknArr[ind] - 1)
            --CBoat::waUnknArr[ind];

        CBoat::waUnknArr2[ind] = 8;
    }
}

void CBoat::FillBoatList()
{
    for (int32_t i = 0; i < NUM_WAKE_GEN_BOATS; i++)
        CBoat::apFrameWakeGeneratingBoats[i] = nullptr;

    auto vecCamPos = CVector2D(TheCamera.GetPosition());
    auto vecCamDir = CVector2D(TheCamera.m_mCameraMatrix.GetForward());
    vecCamDir.Normalise();

    auto iVehNum = CPools::ms_pVehiclePool->GetSize();
    if (!iVehNum)
        return;

    int32_t iCurBoat = 0;

    for (int32_t iInd = 0; iInd < iVehNum; ++iInd) {
        auto pVeh = CPools::ms_pVehiclePool->GetAt(iInd);
        if (!pVeh || !pVeh->IsBoat())
            continue;

        auto pBoat = static_cast<CBoat*>(pVeh);
        if (!pBoat->m_nNumWaterTrailPoints)
            continue;

        auto vecBoatPos = CVector2D(pBoat->GetPosition());
        auto vecBoatCamOffset = vecBoatPos - vecCamPos;
        auto fCamDot = DotProduct2D(vecBoatCamOffset, vecCamDir);
        if (fCamDot > 100.0F || fCamDot < -15.0F)
            continue;

        auto fDistFromCam = DistanceBetweenPoints2D(vecBoatPos, vecCamPos);
        if (fDistFromCam > 80.0F) // Originally squared dist, compared to 6400.0F
            continue;

        // Early out, the list isn't full yet
        if (iCurBoat < 4) {
            CBoat::apFrameWakeGeneratingBoats[iCurBoat] = pBoat;
            ++iCurBoat;
            continue;
        }

        // Insert the new boat into list, based on dist from camera
        auto iNewInd = -1;
        auto fMinDist = 999999.99F;
        for (int32_t iCheckedInd = 0; iCheckedInd < NUM_WAKE_GEN_BOATS; ++iCheckedInd) {
            auto pCheckedBoat = CBoat::apFrameWakeGeneratingBoats[iCheckedInd];
            auto vecCheckedPos = CVector2D(pCheckedBoat->GetPosition());
            auto fCheckedDistFromCam = DistanceBetweenPoints2D(vecCheckedPos, vecCamPos); // Originally squared dist
            if (fCheckedDistFromCam < fMinDist) {
                fMinDist = fCheckedDistFromCam;
                iNewInd = iCheckedInd;
            }
        }

        if (iNewInd != -1 && (fDistFromCam < fMinDist || pBoat->m_nStatus == eEntityStatus::STATUS_PLAYER))
            CBoat::apFrameWakeGeneratingBoats[iNewInd] = pBoat;
    }
}

void CBoat::SetModelIndex_Reversed(uint32 index)
{
    CVehicle::SetModelIndex(index);
    memset(m_aBoatNodes, 0, sizeof(m_aBoatNodes));
    CClumpModelInfo::FillFrameArray(m_pRwClump, m_aBoatNodes);
}

void CBoat::ProcessControl_Reversed() {
    m_vehicleAudio.Service();
    CBoat::PruneWakeTrail();
    CVehicle::ProcessDelayedExplosion();
    auto fMassCheck = (m_fMass * 0.008F * 100.0F) / 125.0F;
    if (physicalFlags.bDestroyed && fMassCheck < m_fBuoyancyConstant)
        m_fBuoyancyConstant -= ((m_fMass * 0.001F) * 0.008F);

    auto pWantedInfo = FindPlayerPed()->m_pPlayerData->m_pWanted;
    if (pWantedInfo->m_nWantedLevel > 0 && m_nModelIndex == eModelID::MODEL_PREDATOR) {
        auto pPlayerVeh = FindPlayerVehicle(-1, false);
        if (pPlayerVeh && pPlayerVeh->GetVehicleAppearance() == eVehicleAppearance::VEHICLE_APPEARANCE_BOAT) {
            auto iCarMission = m_autoPilot.m_nCarMission;
            if (iCarMission == eCarMission::MISSION_ATTACKPLAYER
                || (iCarMission >= eCarMission::MISSION_RAMPLAYER_FARAWAY && iCarMission <= eCarMission::MISSION_BLOCKPLAYER_CLOSE)) {

                if (static_cast<uint32>(CTimer::m_snTimeInMilliseconds) > m_nAttackPlayerTime)
                    m_nAttackPlayerTime = rand() % 4096 + CTimer::m_snTimeInMilliseconds + 4500;
            }
        }
    }

    CVehicle::UpdateClumpAlpha();
    CVehicle::ProcessCarAlarm();
    switch (m_nStatus) {
    case eEntityStatus::STATUS_PLAYER:
        m_nBoatFlags.bAnchored = false;
        m_fAnchoredAngle = -10000.0f;
        if (m_pDriver)
            this->ProcessControlInputs(m_pDriver->m_nPedType);

        if (m_nModelIndex == eModelID::MODEL_PREDATOR)
            CVehicle::DoFixedMachineGuns();

        CVehicle::DoDriveByShootings();
        break;
    case eEntityStatus::STATUS_SIMPLE:
        m_nBoatFlags.bAnchored = false;
        m_fAnchoredAngle = -10000.0f;
        CCarAI::UpdateCarAI(this);
        CPhysical::ProcessControl();
        physicalFlags.bSubmergedInWater = true;
        m_nBoatFlags.bOnWater = true;
        m_nBoatFlags.bMovingOnWater = true;
        return;
    case eEntityStatus::STATUS_PHYSICS:
        m_nBoatFlags.bAnchored = false;
        m_fAnchoredAngle = -10000.0f;
        CCarAI::UpdateCarAI(this);
        CCarCtrl::SteerAICarWithPhysics(this);
        break;
    case eEntityStatus::STATUS_ABANDONED:
    case eEntityStatus::STATUS_WRECKED:
        vehicleFlags.bIsHandbrakeOn = false; //?
        physicalFlags.bSubmergedInWater = true;
        m_nBoatFlags.bOnWater = true;
        m_nBoatFlags.bMovingOnWater = true;

        m_fSteerAngle = 0.0F;
        m_fBreakPedal = 0.5F;
        m_fGasPedal = 0.0F;

        auto fDist = (GetPosition() - FindPlayerCentreOfWorld_NoSniperShift(0)).Magnitude();
        if (fDist > 150.0F) {
            m_vecMoveSpeed.Set(0.0F, 0.0F, 0.0F);
            m_vecTurnSpeed.Set(0.0F, 0.0F, 0.0F);
            return;
        }
        break;
    }

    if (m_nStatus == eEntityStatus::STATUS_PLAYER || m_nStatus == eEntityStatus::STATUS_HELI || m_nStatus == eEntityStatus::STATUS_PHYSICS) {
        auto fSTDPropSpeed = 0.0F;
        auto fROCPropSpeed = CPlane::PLANE_ROC_PROP_SPEED;
        if (m_nModelIndex == eModelID::MODEL_SKIMMER)
            fSTDPropSpeed = CPlane::PLANE_STD_PROP_SPEED;
        else if (m_fGasPedal != 0.0F)
            fROCPropSpeed *= 5.0F;

        if (m_fGasPedal == 0.0F)
            m_fPropSpeed += (fSTDPropSpeed - m_fPropSpeed) * CTimer::ms_fTimeStep * fROCPropSpeed;
        else if (m_fGasPedal < 0.0F) {
            fSTDPropSpeed = (CPlane::PLANE_STD_PROP_SPEED - 0.05F) * m_fGasPedal + CPlane::PLANE_STD_PROP_SPEED;
            m_fPropSpeed += (fSTDPropSpeed - m_fPropSpeed) * CTimer::ms_fTimeStep * fROCPropSpeed;
        }
        else {
            fSTDPropSpeed = (CPlane::PLANE_MAX_PROP_SPEED - CPlane::PLANE_STD_PROP_SPEED) * m_fGasPedal + CPlane::PLANE_STD_PROP_SPEED;
            m_fPropSpeed += (fSTDPropSpeed - m_fPropSpeed) * CTimer::ms_fTimeStep * fROCPropSpeed;
        }
    }
    else if (m_fPropSpeed > 0.0F)
        m_fPropSpeed *= 0.95F;

    auto fDamagePower = m_fDamageIntensity * m_pHandlingData->m_fCollisionDamageMultiplier;
    if (fDamagePower > 25.0F && m_nStatus != eEntityStatus::STATUS_WRECKED && m_fHealth >= 250.0F) {
        auto fSavedHealth = m_fHealth;
        if (m_nStatus == eEntityStatus::STATUS_PLAYER && CStats::GetPercentageProgress() >= 100.0F)
            fDamagePower *= 0.5F;

        auto fGivenDamage = fDamagePower;
        if (this == reinterpret_cast<CBoat*>(FindPlayerVehicle(-1, 0)))
        {
            fGivenDamage -= 25.0F;
            if (vehicleFlags.bTakeLessDamage)
                fGivenDamage /= 6.0F;
            else
                fGivenDamage *= 0.5F;
        }
        else {
            if (fGivenDamage > 60.0F && m_pDriver)
                m_pDriver->Say(0x44U, 0, 1.0F, 0, 0, 0);

            fGivenDamage -= 25.0F;
            if (vehicleFlags.bTakeLessDamage)
                fGivenDamage /= 12.0F;
            else
                fGivenDamage *= 0.25F;
        }

        m_fHealth -= fGivenDamage;
        if (m_fHealth <= 0.0F && fSavedHealth > 0.0F) {
            m_fHealth = 1.0F;
            m_pWhoDestroyedMe = m_pDamageEntity;
        }
    }

    if (m_fHealth > 460.0F || m_nStatus == eEntityStatus::STATUS_WRECKED) {
        m_fBurningTimer = 0.0F;
        if (m_pFireParticle) {
            m_pFireParticle->Kill();
            m_pFireParticle = nullptr;
        }
    }
    else {
        auto vecDist = GetPosition() - TheCamera.GetPosition();
        if (fabs(vecDist.x) < 200.0F && fabs(vecDist.y) < 200.0F) {

            CVector vecFirePos(-1.5F, -0.5F, 1.2F);
            if (m_nModelIndex == eModelID::MODEL_SPEEDER)
                vecFirePos.Set(0.4F, -2.4F, 0.8F);
            else if (m_nModelIndex == eModelID::MODEL_REEFER)
                vecFirePos.Set(2.0F, -1.0F, 0.5F);

            if (m_fHealth < 250.0F) {
                if (!m_pFireParticle) {
                    auto pModellingMat = GetModellingMatrix();
                    if (pModellingMat) {
                        m_pFireParticle = g_fxMan.CreateFxSystem("fire_car", &vecFirePos, pModellingMat, 0);
                        if (m_pFireParticle) {
                            m_pFireParticle->Play();
                            CEventVehicleOnFire vehOnFireEvent(this);
                            GetEventGlobalGroup()->Add(&vehOnFireEvent, false);
                        }
                    }
                }

                m_fBurningTimer += (CTimer::ms_fTimeStep * 20.0F);
                if (m_fBurningTimer > 5000.0F)
                    this->BlowUpCar(m_pWhoDestroyedMe, false);
            }
        }
    }

    auto bPostCollision = m_fDamageIntensity > 0.0F && m_vecLastCollisionImpactVelocity.z > 0.1F;
    CPhysical::ProcessControl();
    ProcessBoatControl(m_pBoatHandling, &m_fLastWaterImmersionDepth, m_bHasHitWall, bPostCollision);

    if (m_nModelIndex == eModelID::MODEL_SKIMMER
        && (m_fPropSpeed > CPlane::PLANE_MIN_PROP_SPEED || m_vecMoveSpeed.SquaredMagnitude() > CPlane::PLANE_MIN_PROP_SPEED)) {
        FlyingControl(FLIGHT_MODEL_PLANE, -10000.0f, -10000.0f, -10000.0f, -10000.0f);
    }
    else if (CCheat::m_aCheatsActive[eCheats::CHEAT_BOATS_FLY])
        FlyingControl(FLIGHT_MODEL_BOAT, -10000.0f, -10000.0f, -10000.0f, -10000.0f);

    if (m_nBoatFlags.bAnchored) {
        m_vecMoveSpeed.x = 0.0F;
        m_vecMoveSpeed.y = 0.0F;

        auto bNoAnchorAngle = m_fAnchoredAngle == -10000.0f;
        if (bNoAnchorAngle)
            m_fAnchoredAngle = GetHeading();
        else {
            CVector vecPos = GetMatrix().GetPosition();
            GetMatrix().RotateZ(m_fAnchoredAngle - GetHeading());
            GetMatrix().SetTranslateOnly(vecPos);
        }
    }
}

void CBoat::Teleport_Reversed(CVector destination, bool resetRotation)
{
    CWorld::Remove(this);
    SetPosn(destination);
    if (resetRotation)
        SetOrientation(0.0F, 0.0F, 0.0F);

    m_vecMoveSpeed.Set(0.0F, 0.0F, 0.0F);
    m_vecTurnSpeed.Set(0.0F, 0.0F, 0.0F);
    CWorld::Add(this);
}

void CBoat::PreRender_Reversed()
{
    CVehicle::PreRender();

    m_fContactSurfaceBrightness = 0.5F;
    auto fUsedAngle = -m_fSteerAngle;
    CVehicle::SetComponentRotation(m_aBoatNodes[eBoatNodes::BOAT_RUDDER],         eRotationAxis::AXIS_Z, fUsedAngle, true);
    CVehicle::SetComponentRotation(m_aBoatNodes[eBoatNodes::BOAT_REARFLAP_LEFT],  eRotationAxis::AXIS_Z, fUsedAngle, true);
    CVehicle::SetComponentRotation(m_aBoatNodes[eBoatNodes::BOAT_REARFLAP_RIGHT], eRotationAxis::AXIS_Z, fUsedAngle, true);

    auto fPropSpeed = std::min(1.0F, m_fPropSpeed * (32.0F / TWO_PI));
    auto ucTransparency = static_cast<RwUInt8>((1.0F - fPropSpeed) * 255.0F);

    m_fPropRotation += m_fPropSpeed * CTimer::ms_fTimeStep;
    while (m_fPropRotation > TWO_PI)
        m_fPropRotation -= TWO_PI;

    ProcessBoatNodeRendering(eBoatNodes::BOAT_STATIC_PROP,   m_fPropRotation * 2,  ucTransparency);
    ProcessBoatNodeRendering(eBoatNodes::BOAT_STATIC_PROP_2, m_fPropRotation * -2, ucTransparency);

    ucTransparency = (ucTransparency >= 150 ? 0 : 150 - ucTransparency);
    ProcessBoatNodeRendering(eBoatNodes::BOAT_MOVING_PROP,  -m_fPropRotation, ucTransparency);
    ProcessBoatNodeRendering(eBoatNodes::BOAT_MOVING_PROP_2, m_fPropRotation, ucTransparency);

    if (m_nModelIndex == eModelID::MODEL_MARQUIS) {
        auto pFlap = m_aBoatNodes[eBoatNodes::BOAT_FLAP_LEFT];
        if (pFlap) {
            auto tempMat = CMatrix();
            tempMat.Attach(RwFrameGetMatrix(pFlap), false);
            CVector posCopy = tempMat.GetPosition();
            auto vecTransformed = Multiply3x3(GetMatrix(), posCopy);

            m_boatFlap.Process(this, m_vecBoatMoveForce, m_vecBoatTurnForce, vecTransformed);
            CVector vecAxis;
            if (m_boatFlap.m_nAxis == eRotationAxis::AXIS_X)
                vecAxis.Set(m_boatFlap.m_fAngle, 0.0F, 0.0F);
            else if (m_boatFlap.m_nAxis == eRotationAxis::AXIS_Y)
                vecAxis.Set(0.0F, m_boatFlap.m_fAngle, 0.0F);
            else if (m_boatFlap.m_nAxis == eRotationAxis::AXIS_Z)
                vecAxis.Set(0.0F, 0.0F, m_boatFlap.m_fAngle);

            tempMat.SetRotate(vecAxis.x, vecAxis.y, vecAxis.z);
            tempMat.GetPosition() += posCopy;
            tempMat.UpdateRW();
        }
    }

    if (m_nModelIndex == eModelID::MODEL_PREDATOR
        || m_nModelIndex == eModelID::MODEL_REEFER
        || m_nModelIndex == eModelID::MODEL_TROPIC) {

        auto pMoving = m_aBoatNodes[eBoatNodes::BOAT_MOVING];
        if (pMoving) {
            CVehicle::SetComponentRotation(pMoving, eRotationAxis::AXIS_Z, this->m_fMovingHiRotation, 1);
            if (CCheat::m_aCheatsActive[CHEAT_INVISIBLE_CAR])
            {
                auto pFirstObj = reinterpret_cast<RpAtomic*>(GetFirstObject(pMoving));
                RpAtomicRenderMacro(pFirstObj);
            }
        }
        m_fMovingHiRotation += CTimer::ms_fTimeStep / 50.0F;
    }

    m_vecBoatMoveForce = m_vecMoveSpeed + m_vecFrictionMoveSpeed;
    m_vecBoatTurnForce = m_vecTurnSpeed + m_vecFrictionTurnSpeed;
    auto fSpeed = m_vecMoveSpeed.Magnitude();

    int32_t iCounter = 0;
    constexpr eBoatNodes aCheckedNodes[2] = { eBoatNodes::BOAT_STATIC_PROP, eBoatNodes::BOAT_STATIC_PROP_2 };
    for (const auto eNode : aCheckedNodes) {
        auto pProp = m_aBoatNodes[eNode];
        RwMatrix* pSplashMat = CEntity::GetModellingMatrix();

        auto pSplashFx = m_apPropSplashFx[iCounter];
        if (!pSplashFx && pSplashMat && pProp) {
            RwV3dAssign(RwMatrixGetPos(pSplashMat), RwMatrixGetPos(RwFrameGetLTM(pProp)));
            RwMatrixUpdate(pSplashMat);
            auto vecPoint = CVector(0.0F, 0.0F, 0.0F);
            pSplashFx = g_fxMan.CreateFxSystem("boat_prop", &vecPoint, pSplashMat, false);
            if (pSplashFx) {
                m_apPropSplashFx[iCounter] = pSplashFx;
                pSplashFx->Play();
                pSplashFx->SetLocalParticles(true);
                pSplashFx->CopyParentMatrix();
            }
        }

        if (pSplashFx && pSplashMat) {
            if (physicalFlags.bSubmergedInWater) {
                if (pSplashFx->GetPlayStatus() == eFxSystemPlayStatus::FX_STOPPED)
                    pSplashFx->Play();

                RwV3dAssign(RwMatrixGetPos(pSplashMat), RwMatrixGetPos(RwFrameGetLTM(pProp)));
                RwMatrixUpdate(pSplashMat);
                pSplashFx->SetMatrix(pSplashMat);
                auto fTime = std::min(1.0F, fSpeed * 2.0F);
                pSplashFx->SetConstTime(true, fTime);
            }
            else if (pSplashFx->GetPlayStatus() == eFxSystemPlayStatus::FX_PLAYING) {
                pSplashFx->Stop();
            }
        }

        ++iCounter;
    }

    auto fWaterDamping = m_vecWaterDamping.Magnitude();
    CVehicle::DoBoatSplashes(fWaterDamping);
}

inline void CBoat::ProcessBoatNodeRendering(eBoatNodes eNode, float fRotation, RwUInt8 ucAlpha)
{
    auto pFrame = m_aBoatNodes[eNode];
    if (!pFrame)
        return;

    CVehicle::SetComponentRotation(pFrame, eRotationAxis::AXIS_Y, fRotation, true);
    RpAtomic* pAtomic;
    RwFrameForAllObjects(pFrame, GetCurrentAtomicObjectCB, &pAtomic);
    if (pAtomic)
        CVehicle::SetComponentAtomicAlpha(pAtomic, ucAlpha);
}

void CBoat::Render_Reversed()
{
    m_nTimeTillWeNeedThisCar = CTimer::m_snTimeInMilliseconds + 3000;
    if (CCheat::m_aCheatsActive[eCheats::CHEAT_INVISIBLE_CAR])
        return;

    CVehicle::Render();

    if (m_nModelIndex == eModelID::MODEL_SKIMMER)
        return;

    // Code below is used to draw the "no water" zones, so the inside of the boat that is under water surface, doesn't have water visible in it

    RwRGBA rwColor = CRGBA(0xFF, 0xFF, 0xFF, 0xFF).ToRwRGBA();
    RxObjSpace3DVertexSetPreLitColor(&CBoat::aRenderVertices[0], &rwColor);
    RxObjSpace3DVertexSetPreLitColor(&CBoat::aRenderVertices[1], &rwColor);
    RxObjSpace3DVertexSetPreLitColor(&CBoat::aRenderVertices[2], &rwColor);
    RxObjSpace3DVertexSetPreLitColor(&CBoat::aRenderVertices[3], &rwColor);

    CBoat::auRenderIndices[0] = 0;
    CBoat::auRenderIndices[1] = 2;
    CBoat::auRenderIndices[2] = 1;
    CBoat::auRenderIndices[3] = 1;
    CBoat::auRenderIndices[4] = 2;
    CBoat::auRenderIndices[5] = 3;

    RxObjSpace3DVertexSetU(&CBoat::aRenderVertices[0], 0.0F);
    RxObjSpace3DVertexSetV(&CBoat::aRenderVertices[0], 0.0F);
    RxObjSpace3DVertexSetU(&CBoat::aRenderVertices[1], 1.0F);
    RxObjSpace3DVertexSetV(&CBoat::aRenderVertices[1], 0.0F);
    RxObjSpace3DVertexSetU(&CBoat::aRenderVertices[2], 0.0F);
    RxObjSpace3DVertexSetV(&CBoat::aRenderVertices[2], 1.0F);
    RxObjSpace3DVertexSetU(&CBoat::aRenderVertices[3], 1.0F);
    RxObjSpace3DVertexSetV(&CBoat::aRenderVertices[3], 1.0F);

    switch (m_nModelIndex) {
    case eModelID::MODEL_PREDATOR:
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[0], -1.45F,  1.90F, 0.96F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[1],  1.45F,  1.90F, 0.96F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[2], -1.45F, -3.75F, 0.96F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[3],  1.45F, -3.75F, 0.96F);
        break;
    case eModelID::MODEL_SQUALO:
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[0], -1.222F,  2.004F, 1.409F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[1],  1.222F,  2.004F, 1.409F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[2], -1.240F, -1.367F, 0.846F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[3],  1.240F, -1.367F, 0.846F);
        break;
    case eModelID::MODEL_SPEEDER:
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[0], -1.15F,  3.61F, 1.03F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[1],  1.15F,  3.61F, 1.03F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[2], -1.15F, -0.06F, 1.03F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[3],  1.15F, -0.06F, 1.03F);
        break;
    case eModelID::MODEL_REEFER:
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[0], -1.90F,  2.83F, 1.00F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[1],  1.90F,  2.83F, 1.00F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[2], -1.66F, -4.48F, 0.83F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[3],  1.66F, -4.48F, 0.83F);
        break;
    case eModelID::MODEL_TROPIC:
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[0], -1.886F, -2.347F, 0.787F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[1], 1.886F, -2.347F, 0.787F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[2], -1.886F, -4.670F, 0.842F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[3], 1.886F, -4.670F, 0.842F);
        break;
    case eModelID::MODEL_COASTG:
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[0], -0.663F, 3.565F, 0.382F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[1],  0.663F, 3.565F, 0.382F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[2], -1.087F, 0.831F, 0.381F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[3],  1.087F, 0.831F, 0.381F);
        break;
    case eModelID::MODEL_DINGHY:
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[0], -0.797F,  1.641F, 0.573F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[1],  0.797F,  1.641F, 0.573F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[2], -0.865F, -1.444F, 0.509F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[3],  0.865F, -1.444F, 0.509F);
        break;
    case eModelID::MODEL_MARQUIS:
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[0], -1.246F, -1.373F, 0.787F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[1],  1.246F, -1.373F, 0.787F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[2], -1.023F, -5.322F, 0.787F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[3],  1.023F, -5.322F, 0.787F);
        break;
    case eModelID::MODEL_LAUNCH:
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[0], -1.0F,  2.5F, 0.3F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[1],  1.0F,  2.5F, 0.3F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[2], -1.0F, -5.4F, 0.3F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[3],  1.0F, -5.4F, 0.3F);
        break;
    default:
        return;
    }

    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, CWaterLevel::waterclear256Raster);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDZERO);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDONE);

    RwMatrix tempMat;
    GetMatrix().UpdateRwMatrix(&tempMat);
    if (RwIm3DTransform(CBoat::aRenderVertices, CBoat::uiNumVertices, &tempMat, rwMATRIXTYPENORMAL)) {
        RwIm3DRenderIndexedPrimitive(RwPrimitiveType::rwPRIMTYPETRILIST, CBoat::auRenderIndices, CBoat::uiNumIndices);
        RwIm3DEnd();
    }

    // Second tri list for Coastguard
    if (m_nModelIndex == eModelID::MODEL_COASTG) {
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[0], -1.087F,  0.831F, 0.381F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[1],  1.087F,  0.831F, 0.381F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[2], -1.097F, -2.977F, 0.381F);
        RwIm3DVertexSetPos(&CBoat::aRenderVertices[3],  1.097F, -2.977F, 0.381F);

        GetMatrix().UpdateRwMatrix(&tempMat);
        if (RwIm3DTransform(CBoat::aRenderVertices, CBoat::uiNumVertices, &tempMat, rwMATRIXTYPENORMAL)) {
            RwIm3DRenderIndexedPrimitive(RwPrimitiveType::rwPRIMTYPETRILIST, CBoat::auRenderIndices, CBoat::uiNumIndices);
            RwIm3DEnd();
        }
    }

    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
}

void CBoat::ProcessControlInputs_Reversed(uint8 ucPadNum)
{
    m_nPadNumber = ucPadNum;
    if (ucPadNum > 3)
        m_nPadNumber = 3;

    auto pPad = CPad::GetPad(ucPadNum);
    float fBrakePower = (static_cast<float>(pPad->GetBrake()) * (1.0F / 255.0F) - m_fBreakPedal) * 0.1F + m_fBreakPedal;
    fBrakePower = clamp(fBrakePower, 0.0F, 1.0F);
    m_fBreakPedal = fBrakePower;

    auto fGasPower = fBrakePower * -0.3F;
    if (fBrakePower < 0.05F) {
        m_fBreakPedal = 0.0F;
        fGasPower = static_cast<float>(pPad->GetAccelerate()) * (1.0F / 255.0F);
    }
    m_fGasPedal = fGasPower;

    // Mouse steering
    if (CCamera::m_bUseMouse3rdPerson && CVehicle::m_bEnableMouseSteering) {
        auto bChangedInput = CVehicle::m_nLastControlInput != eControllerType::CONTROLLER_MOUSE || pPad->GetSteeringLeftRight();
        if (CPad::NewMouseControllerState.X == 0.0F && bChangedInput) { // No longer using mouse controls
            m_fRawSteerAngle += (static_cast<float>(-pPad->GetSteeringLeftRight()) * (1.0F / 128.0F) - m_fRawSteerAngle) * 0.2F * CTimer::ms_fTimeStep;
            CVehicle::m_nLastControlInput = eControllerType::CONTROLLER_KEYBOARD1;
        }
        else if (m_fRawSteerAngle != 0.0F || m_fRawSteerAngle != 0.0F) {
            CVehicle::m_nLastControlInput = eControllerType::CONTROLLER_MOUSE;
            if (!pPad->NewState.m_bVehicleMouseLook)
                m_fRawSteerAngle += CPad::NewMouseControllerState.X * -0.0035F;

            if (fabs(m_fRawSteerAngle) < 0.5 || pPad->NewState.m_bVehicleMouseLook)
                m_fRawSteerAngle *= pow(0.985F, CTimer::ms_fTimeStep);
        }
    }
    else {
        m_fRawSteerAngle += (static_cast<float>(-pPad->GetSteeringLeftRight()) * (1.0F / 128.0F) - m_fRawSteerAngle) * 0.2F * CTimer::ms_fTimeStep;
        CVehicle::m_nLastControlInput = eControllerType::CONTROLLER_KEYBOARD1;
    }

    m_fRawSteerAngle = clamp(m_fRawSteerAngle, -1.0F, 1.0F);
    auto fSignedPow = m_fRawSteerAngle * fabs(m_fRawSteerAngle);
    m_fSteerAngle = DegreesToRadians(m_pHandlingData->m_fSteeringLock * fSignedPow);
}

void CBoat::GetComponentWorldPosition_Reversed(int32 componentId, CVector& posnOut)
{
    posnOut = RwFrameGetLTM(m_aBoatNodes[componentId])->pos;
}

void CBoat::ProcessOpenDoor_Reversed(CPed* ped, uint32 doorComponentId, uint32 arg2, uint32 arg3, float arg4)
{
    return;
}

void CBoat::BlowUpCar_Reversed(CEntity* damager, uint8 bHideExplosion)
{
    if (!vehicleFlags.bCanBeDamaged)
        return;

    physicalFlags.bDestroyed = true;
    m_nStatus = eEntityStatus::STATUS_WRECKED;
    CVisibilityPlugins::SetClumpForAllAtomicsFlag(m_pRwClump, eAtomicComponentFlag::ATOMIC_IS_BLOWN_UP);
    m_vecMoveSpeed.z += 0.13F;
    m_fHealth = 0.0F;
    m_wBombTimer = 0;

    const auto& vecPos = GetPosition();
    TheCamera.CamShake(0.4F, vecPos.x, vecPos.y, vecPos.z);
    CVehicle::KillPedsInVehicle();
    m_nOverrideLights = eVehicleOverrideLightsState::NO_CAR_LIGHT_OVERRIDE;
    vehicleFlags.bEngineOn = false;
    vehicleFlags.bLightsOn = false;
    CVehicle::ChangeLawEnforcerState(false);
    CExplosion::AddExplosion(this, damager, eExplosionType::EXPLOSION_BOAT, vecPos, 0, 1, -1.0F, bHideExplosion);
    CDarkel::RegisterCarBlownUpByPlayer(this, 0);

    auto pMovingComponent = m_aBoatNodes[eBoatNodes::BOAT_MOVING];
    if (!pMovingComponent)
        return;

    RpAtomic* pMovingCompAtomic;
    RwFrameForAllObjects(pMovingComponent, GetBoatAtomicObjectCB, &pMovingCompAtomic);
    if (!pMovingCompAtomic)
        return;

    auto pObject = new CObject();
    if (!pObject)
        return;

    pObject->SetModelIndexNoCreate(379);
    pObject->RefModelInfo(m_nModelIndex);

    auto pMovingCompMatrix = RwFrameGetLTM(pMovingComponent);
    auto pNewRwFrame = RwFrameCreate();
    auto pMovingCompAtomicClone = RpAtomicClone(pMovingCompAtomic);
    memcpy(RwFrameGetMatrix(pNewRwFrame), pMovingCompMatrix, sizeof(RwMatrix));
    RpAtomicSetFrame(pMovingCompAtomicClone, pNewRwFrame);
    CVisibilityPlugins::SetAtomicRenderCallback(pMovingCompAtomicClone, nullptr);
    pObject->AttachToRwObject((RwObject*)pMovingCompAtomicClone, true);

    ++CObject::nNoTempObjects;
    pObject->m_bDontStream = true;
    pObject->m_fMass = 10.0F;
    pObject->m_fTurnMass = 25.0F;
    pObject->m_fAirResistance = 0.99F;
    pObject->m_fElasticity = 0.1F;
    pObject->m_fBuoyancyConstant = 8.0F / 75.0F;
    pObject->m_nObjectType = eObjectType::OBJECT_TEMPORARY;
    pObject->SetIsStatic(false);
    pObject->objectFlags.bIsPickup = false;
    pObject->m_dwRemovalTime = CTimer::m_snTimeInMilliseconds + 20000;

    pObject->m_vecMoveSpeed = m_vecMoveSpeed;
    if (GetUp().z <= 0.0F)
        pObject->m_vecMoveSpeed.z = 0.0F;
    else
        pObject->m_vecMoveSpeed.z = 0.3F;

    pObject->m_vecTurnSpeed.Set(0.5F, m_vecTurnSpeed.y * 2.0F, m_vecTurnSpeed.z * 2.0F);

    auto vecOffset = pObject->GetPosition() - vecPos;
    vecOffset.Normalise();
    if (GetUp().z > 0.0F)
        vecOffset += GetUp();

    auto vecObjPos = pObject->GetPosition() + vecOffset;
    pObject->SetPosn(vecObjPos);

    CWorld::Add(pObject);
    RwFrameForAllObjects(pMovingComponent, GetBoatAtomicObjectCB, &pMovingCompAtomic);
    if (pMovingCompAtomic)
        RpAtomicSetFlags(pMovingCompAtomic, 0x0);
}

RwObject* GetBoatAtomicObjectCB(RwObject* object, void* data)
{
    if (RpAtomicGetFlags(object) & rpATOMICRENDER)
        *static_cast<RpAtomic**>(data) = reinterpret_cast<RpAtomic*>(object);

    return object;
}
