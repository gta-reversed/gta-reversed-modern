#include "StdInc.h"

CBoat** CBoat::apFrameWakeGeneratingBoats; // static CBoat *apFrameWakeGeneratingBoats[4]
float& CBoat::MAX_WAKE_LENGTH = *(float*)0x8D3938; // 50.0
float& CBoat::MIN_WAKE_INTERVAL = *(float*)0x8D393C; // 2.0
float& CBoat::WAKE_LIFETIME = *(float*)0x8D3940; // 150.0
float& CBoat::fShapeLength = *(float*)0x8D3944; // 0.4
float& CBoat::fShapeTime = *(float*)0x8D3948; // 0.05
float& CBoat::fRangeMult = *(float*)0x8D394C; // 0.6

void CBoat::InjectHooks()
{
    //Virtual
    ReversibleHooks::Install("CBoat", "SetModelIndex", 0x6F1140, &CBoat::SetModelIndex_Reversed);
    ReversibleHooks::Install("CBoat", "ProcessControl", 0x6F1770, &CBoat::ProcessControl_Reversed);
    ReversibleHooks::Install("CBoat", "Teleport", 0x6F20E0, &CBoat::Teleport_Reversed);
    ReversibleHooks::Install("CBoat", "GetComponentWorldPosition", 0x6F01D0, &CBoat::GetComponentWorldPosition_Reversed);
    ReversibleHooks::Install("CBoat", "ProcessOpenDoor", 0x6F0190, &CBoat::ProcessOpenDoor_Reversed);
    ReversibleHooks::Install("CBoat", "BlowUpCar", 0x6F21B0, &CBoat::BlowUpCar_Reversed);

    //Class methods
    ReversibleHooks::Install("CBoat", "PruneWakeTrail", 0x6F0E20, &CBoat::PruneWakeTrail);
    ReversibleHooks::Install("CBoat", "AddWakePoint", 0x6F2550, &CBoat::AddWakePoint);

    //Other
    ReversibleHooks::Install("CBoat", "GetBoatAtomicObjectCB", 0x6F00D0, &GetBoatAtomicObjectCB);
}

void CBoat::SetModelIndex(unsigned int index)
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

void CBoat::GetComponentWorldPosition(int componentId, CVector& posnOut)
{
    return CBoat::GetComponentWorldPosition_Reversed(componentId, posnOut);
}

void CBoat::ProcessOpenDoor(CPed* ped, unsigned int doorComponentId, unsigned int arg2, unsigned int arg3, float arg4)
{
    return CBoat::ProcessOpenDoor_Reversed(ped, doorComponentId, arg2, arg3, arg4);
}

void CBoat::BlowUpCar(CEntity* damager, unsigned char bHideExplosion)
{
    return CBoat::BlowUpCar_Reversed(damager, bHideExplosion);
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
    auto fIntensity = m_vecMoveSpeed.Magnitude() * 100.0F;

    // No wake points exisiting, early out
    if (m_afWakePointLifeTime[0] < 0.0F) {
        m_anWakePointIntensity[0] = fIntensity;
        m_avecWakePoints[0].Set(posn.x, posn.y);
        m_afWakePointLifeTime[0] = CBoat::WAKE_LIFETIME;

        m_nNumWaterTrailPoints = 1;
        return;
    }

    if (DistanceBetweenPoints(posn, m_avecWakePoints[0]) <= CBoat::MIN_WAKE_INTERVAL)
        return;

    short uiMaxWakePoints = 31;
    if (!m_nStatus == eEntityStatus::STATUS_PLAYER) {
        if (m_nCreatedBy == eVehicleCreatedBy::MISSION_VEHICLE)
            uiMaxWakePoints = 20;
        else
            uiMaxWakePoints = 15;
    }
    short uiCurWaterPoints = std::min(m_nNumWaterTrailPoints, uiMaxWakePoints);

    // Shift wake points
    if (m_nNumWaterTrailPoints >= uiMaxWakePoints || uiCurWaterPoints > 0) {
        for (unsigned int iInd = uiCurWaterPoints; iInd > 0; --iInd) {
            m_avecWakePoints[iInd] = m_avecWakePoints[iInd - 1];
            m_anWakePointIntensity[iInd] = m_anWakePointIntensity[iInd - 1];
            m_afWakePointLifeTime[iInd] = m_afWakePointLifeTime[iInd - 1];
        }
    }

    m_anWakePointIntensity[0] = fIntensity;
    m_avecWakePoints[0].Set(posn.x, posn.y);
    m_afWakePointLifeTime[0] = CBoat::WAKE_LIFETIME;
    if (m_nNumWaterTrailPoints < 32)
        ++m_nNumWaterTrailPoints;
}

void CBoat::SetModelIndex_Reversed(unsigned int index)
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
        if (pPlayerVeh && pPlayerVeh->GetVehicleAppearance() == eVehicleApperance::VEHICLE_APPEARANCE_BOAT) {
            auto iCarMission = m_autoPilot.m_nCarMission;
            if (iCarMission == eCarMission::MISSION_ATTACKPLAYER
                || (iCarMission >= eCarMission::MISSION_RAMPLAYER_FARAWAY && iCarMission <= eCarMission::MISSION_BLOCKPLAYER_CLOSE)) {

                if (CTimer::m_snTimeInMilliseconds > m_nAttackPlayerTime)
                    m_nAttackPlayerTime = (rand() && 0xFFF) + CTimer::m_snTimeInMilliseconds + 4500;
            }
        }
    }

    CVehicle::UpdateClumpAlpha();
    CVehicle::ProcessCarAlarm();
    switch (m_nStatus) {
    case eEntityStatus::STATUS_PLAYER:
        m_nBoatFlags.bAnchored = false;
        m_fAnchoredAngle = -9999.99F;
        if (m_pDriver)
            CVehicle::ProcessControlInputs(m_pDriver->m_nPedType);

        if (m_nModelIndex == eModelID::MODEL_PREDATOR)
            CVehicle::DoFixedMachineGuns();

        CVehicle::DoDriveByShooting();
        break;
    case eEntityStatus::STATUS_SIMPLE:
        m_nBoatFlags.bAnchored = false;
        m_fAnchoredAngle = -9999.99F;
        CCarAI::UpdateCarAI(this);
        CPhysical::ProcessControl();
        physicalFlags.bSubmergedInWater = true;
        m_nBoatFlags.bOnWater = true;
        m_nBoatFlags.bMovingOnWater = true;
        return;
    case eEntityStatus::STATUS_PHYSICS:
        m_nBoatFlags.bAnchored = false;
        m_fAnchoredAngle = -9999.99F;
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
                    BlowUpCar(m_pWhoDestroyedMe, false);
            }
        }
    }

    auto bPostCollision = m_fDamageIntensity > 0.0F && m_vecLastCollisionImpactVelocity.z > 0.1F;
    CPhysical::ProcessControl();
    CVehicle::ProcessBoatControl(m_pBoatHandling, &m_fLastWaterImmersionDepth, m_bHasHitWall, bPostCollision);

    if (m_nModelIndex == eModelID::MODEL_SKIMMER
        && (m_fPropSpeed > CPlane::PLANE_MIN_PROP_SPEED || m_vecMoveSpeed.SquaredMagnitude() > CPlane::PLANE_MIN_PROP_SPEED)) {
        CVehicle::FlyingControl(3, -9999.99F, -9999.99F, -9999.99F, -9999.99F);
    }
    else if (CCheat::m_aCheatsActive[eCheats::CHEAT_BOATS_FLY])
        CVehicle::FlyingControl(5, -9999.99F, -9999.99F, -9999.99F, -9999.99F);

    if (m_nBoatFlags.bAnchored) {
        m_vecMoveSpeed.x = 0.0F;
        m_vecMoveSpeed.y = 0.0F;

        auto bNoAnchorAngle = m_fAnchoredAngle == -9999.99F;
        if (bNoAnchorAngle)
            m_fAnchoredAngle = GetHeading();
        else {
            CVector vecPos = GetMatrix()->GetPosition();
            GetMatrix()->RotateZ(m_fAnchoredAngle - GetHeading());
            GetMatrix()->SetTranslateOnly(vecPos);
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

void CBoat::GetComponentWorldPosition_Reversed(int componentId, CVector& posnOut)
{
    posnOut = RwFrameGetLTM(m_aBoatNodes[componentId])->pos;
}

void CBoat::ProcessOpenDoor_Reversed(CPed* ped, unsigned int doorComponentId, unsigned int arg2, unsigned int arg3, float arg4)
{
    return;
}

void CBoat::BlowUpCar_Reversed(CEntity* damager, unsigned char bHideExplosion)
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

    auto pObject = reinterpret_cast<CObject*>(CObject::operator new(sizeof(CObject)));
    if (!pObject)
        return;

    pObject->Constructor();
    pObject->SetModelIndexNoCreate(379);
    pObject->RefModelInfo(m_nModelIndex);

    auto pMovingCompMatrix = RwFrameGetLTM(pMovingComponent);
    auto pNewRwFrame = RwFrameCreate();
    auto pMovingCompAtomicClone = RpAtomicClone(pMovingCompAtomic);
    memcpy(RwFrameGetMatrix(pNewRwFrame), pMovingCompMatrix, sizeof(RwMatrix));
    RpAtomicSetFrame(pMovingCompAtomicClone, pNewRwFrame);
    CVisibilityPlugins::SetAtomicRenderCallback(pMovingCompAtomicClone, nullptr);
    pObject->AttachToRwObject(&pMovingCompAtomicClone->object.object, true);

    ++CObject::nNoTempObjects;
    pObject->m_bDontStream = true;
    pObject->m_fMass = 10.0F;
    pObject->m_fTurnMass = 25.0F;
    pObject->m_fAirResistance = 0.99F;
    pObject->m_fElasticity = 0.1F;
    pObject->m_fBuoyancyConstant = 8.0F / 75.0F;
    pObject->m_nObjectType = eObjectCreatedBy::OBJECT_TEMPORARY;
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
        *reinterpret_cast<RpAtomic**>(data) = reinterpret_cast<RpAtomic*>(object);

    return object;
}
