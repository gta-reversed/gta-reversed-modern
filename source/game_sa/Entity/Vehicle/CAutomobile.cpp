/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

bool& CAutomobile::m_sAllTaxiLights = *(bool*)0xC1BFD0;
CVector& CAutomobile::vecHunterGunPos = *(CVector*)0x8D3394;
CMatrix* CAutomobile::matW2B = (CMatrix*)0xC1C220;
CColPoint* aAutomobileColPoints = (CColPoint*)0xC1BFF8;

void CAutomobile::InjectHooks()
{
    ReversibleHooks::Install("CAutomobile", "ProcessControl", 0x6B1880, &CAutomobile::ProcessControl_Reversed);
    ReversibleHooks::Install("CAutomobile", "ProcessSuspension", 0x6AFB10, &CAutomobile::ProcessSuspension_Reversed);
    ReversibleHooks::Install("CAutomobile", "HydraulicControl", 0x6A07A0, &CAutomobile::HydraulicControl);
    ReversibleHooks::Install("CAutomobile", "ProcessBuoyancy", 0x6A8C00, &CAutomobile::ProcessBuoyancy);
    ReversibleHooks::Install("CAutomobile", "PlaceOnRoadProperly", 0x6AF420, &CAutomobile::PlaceOnRoadProperly);
    ReversibleHooks::Install("CAutomobile", "ProcessCarWheelPair", 0x6A4EC0, &CAutomobile::ProcessCarWheelPair);
}

CAutomobile::CAutomobile(int modelIndex, unsigned char createdBy, bool setupSuspensionLines) : CVehicle(plugin::dummy) {
    ((void(__thiscall*)(CAutomobile*, int, unsigned char, bool))0x6B0A90)(this, modelIndex, createdBy, setupSuspensionLines);
}

void CAutomobile::ProcessControl()
{
    uint32_t extraHandlingFlags = 0;
    if (vehicleFlags.bUseCarCheats)
        extraHandlingFlags |= EXTRA_HANDLING_PERFECT;
    CCollisionData* colData = GetColModel()->m_pColData;
    m_doingBurnout = 0;
    npcFlags.bLostTraction = false;
    vehicleFlags.bWarnedPeds = false;
    vehicleFlags.bRestingOnPhysical = false;
    m_vehicleAudio.Service();
    bool bExplodeImmediately = false;
    if (IsPlane() || IsHeli()) {
        eCarMission carMission = m_autoPilot.m_nCarMission;
        if ((carMission == MISSION_CRASH_PLANE_AND_BURN
            || carMission == MISSION_CRASH_HELI_AND_BURN
            || m_nStatus == STATUS_PLAYER && m_fHealth < 250.0 && field_981 == 2)
            && m_nStatus != STATUS_WRECKED
            && (m_fDamageIntensity > 0.0f && m_vecLastCollisionImpactVelocity.z > 0.0f || !IsInAir())
            && (m_vecMoveSpeed.z >= 0.0f || physicalFlags.bSubmergedInWater))
        {
            bExplodeImmediately = true;
        }
    }

    if (CCheat::m_aCheatsActive[CHEAT_ALL_TAXIS_NITRO]) {
        if (m_nStatus == STATUS_PLAYER && IsTransportVehicle())
            extraHandlingFlags |= EXTRA_HANDLING_TAXI_BOOST;
    }

    bool bExtraHandlingTaxiBoost = !!(extraHandlingFlags & EXTRA_HANDLING_TAXI_BOOST);
    if (CCheat::m_aCheatsActive[CHEAT_ALL_CARS_HAVE_NITRO] || bExtraHandlingTaxiBoost) {
        handlingFlags.bNosInst = true;
        m_nNitroBoosts = 101;
    }
    if (vehicleFlags.bIsBus)
        ProcessAutoBusDoors();
    ProcessCarAlarm();
    UpdateClumpAlpha();
    UpdatePassengerList();
    if (m_pDriver) {
        if (!vehicleFlags.bDriverLastFrame && m_nBombOnBoard == BOMB_IGNITION_ACTIVATED) {
            m_wBombTimer = 1000;
            m_pWhoDetonatedMe = m_pWhoInstalledBombOnMe;
            if (m_pWhoInstalledBombOnMe)
                CEntity::RegisterReference(reinterpret_cast<CEntity**>(&m_pWhoDetonatedMe));
        }
        vehicleFlags.bDriverLastFrame = true;
    }
    else {
        vehicleFlags.bDriverLastFrame = false;
    }

    if (m_nNumPassengers && IsUpsideDown())
        CanPedEnterCar();

    if (ProcessAI(extraHandlingFlags))
        return;

    bool extraPerfectHandling = !!(extraHandlingFlags & EXTRA_HANDLING_PERFECT);
    bool extraHandlingNitros = !!(extraHandlingFlags & EXTRA_HANDLING_NITROS);
    bool extraHandlingWheelsTouchingPavement = !!(extraHandlingFlags & EXTRA_HANDLING_WHEELS_TOUCHING_PAVEMENT);
    bool extraHandlingTaxiBoost = !!(extraHandlingFlags & EXTRA_HANDLING_TAXI_BOOST);

    bool skipPhysics = false;
    if (m_nStatus == STATUS_ABANDONED || m_nStatus == STATUS_WRECKED) {
        bool isVehicleIdle = false;
        if (!vehicleFlags.bVehicleColProcessed
            && m_vecMoveSpeed == 0.0f
            && m_fWheelsSuspensionCompressionPrev[CARWHEEL_REAR_RIGHT] != 1.0f)
        {
            isVehicleIdle = true;
        }

        float forceLimitRadius = 0.003f;
        float torqueLimitRadius = 0.0009f;
        float movingSpeedLimit = 0.005f;
        if (IsPlane()) {
            if (m_fDamageIntensity > 0.0f && m_pDamageEntity && m_pDamageEntity->IsVehicle())
                forceLimitRadius = 0.003f;
            else
                forceLimitRadius = 0.009f;
            torqueLimitRadius = 0.003f;
            movingSpeedLimit = 0.1f;
        }
        else if (m_nStatus == STATUS_WRECKED) {
            forceLimitRadius = 0.006f;
            torqueLimitRadius = 0.0015f;
            movingSpeedLimit = 0.015f;
        }

        m_vecForce = (m_vecForce + m_vecMoveSpeed) * 0.5f;
        m_vecTorque = (m_vecTorque + m_vecTurnSpeed) * 0.5f;

        bool resetSpeed = true;

        forceLimitRadius *= CTimer::ms_fTimeStep;
        torqueLimitRadius *= CTimer::ms_fTimeStep;
        if (forceLimitRadius * forceLimitRadius < m_vecForce.SquaredMagnitude()
            || torqueLimitRadius * torqueLimitRadius < m_vecTorque.SquaredMagnitude()
            || movingSpeedLimit <= m_fMovingSpeed
            || m_fDamageIntensity > 0.0f && m_pDamageEntity && m_pDamageEntity->IsPed())
        {
            resetSpeed = false;
        }
        else if (physicalFlags.bSubmergedInWater) {
            CVector distance = GetPosition() - TheCamera.GetPosition();
            if (distance.SquaredMagnitude() < 2500.0f)
                resetSpeed = false;
        }
        if (!resetSpeed && !isVehicleIdle) {
            m_nFakePhysics = 0;
        }
        else {
            m_nFakePhysics++;
            if (m_nFakePhysics > 10 || isVehicleIdle) {
                if (!isVehicleIdle || m_nFakePhysics > 10)
                    m_nFakePhysics = 10;
                ResetMoveSpeed();
                ResetTurnSpeed();
                skipPhysics = true;
            }
        }

        if (IsRealHeli()
            && m_wheelSpeed[CARWHEEL_REAR_LEFT] > 0.0f || IsAmphibiousHeli()
            && !m_nNumContactWheels
            && m_fDamageIntensity <= 0.0f
            || m_nModelIndex == MODEL_VORTEX
            || CCheat::m_aCheatsActive[CHEAT_CARS_ON_WATER]
            && IsAnyWheelTouchingShallowWaterGround())
        {
            skipPhysics = false;
            m_nFakePhysics = 0;
        }
    }
    for (int32_t i = 0; i < 4; i++) {
        CEntity* collisionEntity = m_pWheelCollisionEntity[i];
        if (collisionEntity) {
            vehicleFlags.bRestingOnPhysical = true;
            if (!CWorld::bForceProcessControl && collisionEntity->m_bIsInSafePosition) {
                m_bWasPostponed = true;
                return;
            }
        }
    }

    if (vehicleFlags.bRestingOnPhysical) {
        skipPhysics = false;
        m_nFakePhysics = 0;
    }

    VehicleDamage(0.0f, 0, nullptr, nullptr, nullptr, WEAPON_RAMMEDBYCAR);
    if (m_nStatus == STATUS_PLAYER && (m_nModelIndex == MODEL_FIRETRUK || m_nModelIndex == MODEL_SWATVAN)) {
        FireTruckControl(0.0f);
    }
    else {
        switch (m_nModelIndex)
        {
        case MODEL_RHINO:
        case MODEL_RCTIGER:
            TankControl();
            break;
        case MODEL_PACKER:
        case MODEL_DOZER:
        case MODEL_DUMPER:
        case MODEL_CEMENT:
        case MODEL_ANDROM:
        case MODEL_FORKLIFT:
            if (UpdateMovingCollision(-1.0f))
                skipPhysics = false;
            break;
        case MODEL_TOWTRUCK:
        case MODEL_TRACTOR:
            TowTruckControl();
            break;
        default:
            if (handlingFlags.bHydraulicInst)
                HydraulicControl();
            else if ((CCheat::m_aCheatsActive[CHEAT_PERFECT_HANDLING] || (extraHandlingFlags & EXTRA_HANDLING_TAXI_BOOST))
                && m_nStatus == STATUS_PLAYER
                && m_vecMoveSpeed.SquaredMagnitude() > 0.04f)
            {
                BoostJumpControl();
            }
            break;
        }
    }
    if (handlingFlags.bNosInst) {
        NitrousControl(0);
    }
    else {
        for (int32_t i = 0; i < 2; i++) {
            FxSystem_c* fxSys = m_exhaustNitroFxSystem[i];
            if (fxSys) {
                fxSys->Kill();
                m_exhaustNitroFxSystem[i] = nullptr;
            }
        }
    }
    if (FindPlayerVehicle(-1, false) == this && CPad::GetPad(0)->CarGunJustDown())
        ActivateBomb();
    if (skipPhysics) {
        SkipPhysics();
        vehicleFlags.bAudioChangingGear = false;
        vehicleFlags.bVehicleColProcessed = false;
        m_fTireTemperature = 1.0f;
    }
    else {
        if (!vehicleFlags.bVehicleColProcessed)
            ProcessControlCollisionCheck(true);
        bool oldSubmergedInWater = physicalFlags.bSubmergedInWater;
        bool postCollision = false;
        if (m_fDamageIntensity > 0.0f && m_vecLastCollisionImpactVelocity.z > 0.1f)
            postCollision = true;
        CPhysical::ProcessControl();

        if (m_nModelIndex == MODEL_SKIMMER) {
            auto skimmerModelInfo = CModelInfo::GetModelInfo(MODEL_SKIMMER)->AsVehicleModelInfoPtr();
            auto skimmerHandling = gHandlingDataMgr.GetBoatPointer(static_cast<uint8_t>(skimmerModelInfo->m_nHandlingId));
            ProcessBoatControl(skimmerHandling, &m_fDoomVerticalRotation, m_bHasHitWall, postCollision);
            physicalFlags.bTouchingWater = physicalFlags.bSubmergedInWater;
        }
        else {
            ProcessBuoyancy();
        }

        if (!oldSubmergedInWater && physicalFlags.bSubmergedInWater) {
            if (m_pDriver && m_pDriver->IsPlayer()) {
                static_cast<CPlayerPed*>(m_pDriver)->ResetPlayerBreath();
            }
            else {
                for (uint8_t i = 0; i < m_nMaxPassengers; i++) {
                    CPed* passenger = m_apPassengers[i];
                    if (passenger && passenger->IsPlayer())
                        static_cast<CPlayerPed*>(passenger)->ResetPlayerBreath();

                }
            }
        }
        if (m_nModelIndex == MODEL_RCBARON)
            ProcessFlyingCarStuff();
        if (!npcFlags.bSoftSuspension) {
            for (int32_t i = 0; i < 4; i++) {
                float wheelRadius = 1.0f - m_aSuspensionSpringLength[i] / m_aSuspensionLineLength[i];
                m_fWheelsSuspensionCompression[i] = (m_fWheelsSuspensionCompression[i] - wheelRadius) / (1.0f - wheelRadius);
            }
        }

        ProcessSuspension();

        CVector contactPoints[4];
        CVector contactSpeeds[4];

        for (int32_t i = 0; i < 4; i++) {
            if (m_fWheelsSuspensionCompression[i] >= 1.0f) {
                CColLine& colLine = colData->m_pLines[i];
                CColDisk& colDisk = colData->m_pDisks[i];
                if (colData->bUsesDisks) {
                    CVector& point = contactPoints[i];
                    point = colDisk.m_vecStart;
                    point.z -= colDisk.m_fStartRadius;
                    point = Multiply3x3(GetMatrix(), &contactPoints[i]);
                }
                else {
                    contactPoints[i] = Multiply3x3(GetMatrix(), &colLine.m_vecEnd);
                }
            }
            else {
                m_wheelSkidmarkMuddy[i] = false;
                m_wheelSkidmarkType[i] = g_surfaceInfos->GetSkidmarkType(m_wheelColPoint[i].m_nSurfaceTypeB);
                if (m_wheelSkidmarkType[i] == SKIDMARK_MUDDY)
                    m_wheelSkidmarkMuddy[i] = true;
                contactPoints[i] = m_wheelColPoint[i].m_vecPoint - GetPosition();
            }
        }

        for (int32_t i = 0; i < 4; i++) {
            CPhysical* collisionEntity = m_pWheelCollisionEntity[i];
            contactSpeeds[i] = GetSpeed(contactPoints[i]);
            if (collisionEntity) {
                contactSpeeds[i] -= collisionEntity->GetSpeed(m_vWheelCollisionPos[i]);
                m_pWheelCollisionEntity[i] = nullptr;
            }
        }

        float speedForward = DotProduct(m_vecMoveSpeed, GetForward());

        if (vehicleFlags.bAudioChangingGear
            && m_fGasPedal > 0.4f
            && m_fBreakPedal < 0.1f
            && speedForward  > 0.15f
            && this == FindPlayerVehicle(-1, false)
            && TheCamera.GetActiveCamera().m_nMode != MODE_1STPERSON)
        {
            if (m_nStatus == STATUS_PLAYER && !m_pHandlingData->m_bIsBus)
            {
                if (m_dwBusDoorTimerEnd) {
                    uint32_t timeStep = static_cast<uint32_t>(CTimer::ms_fTimeStep * 0.02f * 1000.0f);
                    if (m_dwBusDoorTimerEnd <= timeStep)
                        m_dwBusDoorTimerEnd = 0;
                    else
                        m_dwBusDoorTimerEnd -= timeStep;
                }
                else {
                    m_dwBusDoorTimerEnd = 1000;
                }
            }

            if (IsAnyFrontAndRearWheelTouchingGround()) {
                CVector point = GetForward() * -1.0f;
                CVector force = std::min(m_fTurnMass, 2500.0f) * -0.008f * GetUp();
                ApplyTurnForce(force, point);
            }
        }

        float brake = m_pHandlingData->m_fBrakeDeceleration * m_fBreakPedal * CTimer::ms_fTimeStep;

        m_wheelsOnGrounPrev = m_nWheelsOnGround;
        m_nNumContactWheels = 0;
        m_nWheelsOnGround = 0;

        for (int32_t i = 0; i < 4; i++) {
            if (m_fWheelsSuspensionCompression[i] >= 1.0f) {
                m_aWheelTimer[i] = std::max(m_aWheelTimer[i] - CTimer::ms_fTimeStep, 0.0f);
                if (m_aWheelTimer[i] <= 0.0f)
                    continue;
            }
            else {
                m_aWheelTimer[i] = 4.0f;
            }

            m_nNumContactWheels++;

            switch (m_pHandlingData->GetTransmission().m_nDriveType)
            {
            case '4':
                m_nWheelsOnGround++;
                break;
            case 'F':
                if (i == CARWHEEL_FRONT_LEFT || i == CARWHEEL_FRONT_RIGHT) {
                    m_nWheelsOnGround++;
                    break;
                }
                break;
            case 'R':
                if (i == CARWHEEL_REAR_LEFT || i == CARWHEEL_REAR_RIGHT) {
                    m_nWheelsOnGround++;
                    break;
                }
            }
        }

        uint8_t cheatType = CHEAT_HANDLING_NONE;
        if (handlingFlags.bNosInst && m_fTireTemperature < 0.0f)
            cheatType = CHEAT_HANDLING_NITROS;
        else if (extraPerfectHandling || CCheat::m_aCheatsActive[CHEAT_PERFECT_HANDLING])
            cheatType = CHEAT_HANDLING_PERFECT;

        float acceleration = 0.0f;
        if (vehicleFlags.bEngineOn) {
            cTransmission& transmission = m_pHandlingData->GetTransmission();
            if (!m_pHandlingData->m_bIsPlane && !m_pHandlingData->m_bIsHeli)
                acceleration = transmission.CalculateDriveAcceleration(
                    m_fGasPedal,
                    m_nCurrentGear,
                    m_fGearChangeCount,
                    speedForward,
                    &m_intertiaValue1,
                    &m_intertiaValue2,
                    m_nWheelsOnGround,
                    cheatType)
                / m_fVelocityFrequency;
        }

        float traction = 0.004f * m_pHandlingData->m_fTractionMultiplier;
        if (m_nStatus == STATUS_PHYSICS)
            traction = 0.004f * m_fCarTraction * m_pHandlingData->m_fTractionMultiplier;
        traction *= 0.25f / m_fVelocityFrequency;
        CPlane* vortex = static_cast<CPlane*>(this);
        if (CCheat::m_aCheatsActive[CHEAT_PERFECT_HANDLING] || m_nModelIndex == MODEL_VORTEX && vortex->m_fAccelerationBreakStatus == 0.0f)
            traction *= 4.0f;

        if (this != FindPlayerVehicle(-1, false) && (extraPerfectHandling || CCheat::m_aCheatsActive[CHEAT_PERFECT_HANDLING])) {
            traction *= 1.2f;
            acceleration *= 1.4f;
            if (extraHandlingNitros || CCheat::m_aCheatsActive[CHEAT_PERFECT_HANDLING]) {
                traction *= 1.3f;
                acceleration *= 1.4f;
            }
        }

        float steerAngle = 1.0f;
        if (speedForward <= 0.01f || m_aWheelTimer[CARWHEEL_FRONT_LEFT] <= 0.0f && m_aWheelTimer[CARWHEEL_REAR_LEFT] <= 0.0f)
            steerAngle = 1.0f;
        else if (m_nStatus != STATUS_PLAYER)
            steerAngle = 1.0f;
        else {
            CColPoint colPoint;
            colPoint.m_nSurfaceTypeA = SURFACE_WHEELBASE;
            colPoint.m_nSurfaceTypeB = SURFACE_TARMAC;
            float speedRight = DotProduct(m_vecMoveSpeed, GetRight());
            float adhesive = g_surfaceInfos->GetAdhesiveLimit(&colPoint);
            steerAngle = adhesive * traction * 4.0f * 4.0f / (speedForward * speedForward);
            steerAngle = std::min(steerAngle, 1.0f);
            steerAngle = asin(steerAngle) / DegreesToRadians(m_pHandlingData->m_fSteeringLock);
            if (m_fSteerAngle < 0.0f && speedRight > 0.05f
                || m_fSteerAngle > 0.0f && speedRight < -0.05f
                || vehicleFlags.bIsHandbrakeOn
                || steerAngle > 1.0f)
            {
                steerAngle = 1.0f;
            }
        }
        m_fSteerAngle *= steerAngle;

        if (!handlingFlags.bProcRearwheelFirst) {
            if (handlingFlags.bSteerRearwheels)
                CAutomobile::ProcessCarWheelPair(
                    CARWHEEL_FRONT_LEFT,
                    CARWHEEL_FRONT_RIGHT,
                    -999.0f,
                    contactSpeeds,
                    contactPoints,
                    traction,
                    acceleration,
                    brake,
                    true);
            else
                CAutomobile::ProcessCarWheelPair(
                    CARWHEEL_FRONT_LEFT,
                    CARWHEEL_FRONT_RIGHT,
                    m_fSteerAngle,
                    contactSpeeds,
                    contactPoints,
                    traction,
                    acceleration,
                    brake,
                    true);
        }

        float rearWheelsSteerAngle = -999.0f;
        if (handlingFlags.bSteerRearwheels)
            rearWheelsSteerAngle = -m_fSteerAngle;
        else if (handlingFlags.bHbRearwheelSteer)
            rearWheelsSteerAngle = m_f2ndSteerAngle;

        CAutomobile::ProcessCarWheelPair(
            CARWHEEL_REAR_LEFT,
            CARWHEEL_REAR_RIGHT,
            rearWheelsSteerAngle,
            contactSpeeds,
            contactPoints,
            traction,
            acceleration,
            brake,
            false);
        if (handlingFlags.bProcRearwheelFirst)
        {
            if (handlingFlags.bSteerRearwheels)
                CAutomobile::ProcessCarWheelPair(
                    CARWHEEL_FRONT_LEFT,
                    CARWHEEL_FRONT_RIGHT,
                    -999.0f,
                    contactSpeeds,
                    contactPoints,
                    traction,
                    acceleration,
                    brake,
                    true);
            else
                CAutomobile::ProcessCarWheelPair(
                    CARWHEEL_FRONT_LEFT,
                    CARWHEEL_FRONT_RIGHT,
                    m_fSteerAngle,
                    contactSpeeds,
                    contactPoints,
                    traction,
                    acceleration,
                    brake,
                    true);
        }

        if (m_nStatus != STATUS_PLAYER) {
            if (m_nAlarmState == 0 || m_nAlarmState == -1 || m_nStatus == STATUS_WRECKED) {
                if (m_nHornCounter)
                    m_nHornCounter--;
            }
        }
        else if (handlingFlags.bHydraulicInst || CCheat::m_aCheatsActive[CHEAT_PERFECT_HANDLING] || extraHandlingTaxiBoost)
            ProcessSirenAndHorn(false);
        else
            ProcessSirenAndHorn(true);

        if (m_nModelIndex != MODEL_RCBARON)
            ProcessFlyingCarStuff();
    }
    ProcessCarOnFireAndExplode(bExplodeImmediately);
    if (vehicleFlags.bSirenOrAlarm
        && (CTimer::m_FrameCounter & 7) == 5
        && UsesSiren()
        && m_nModelIndex != MODEL_MRWHOOP
        && FindPlayerVehicle(-1, false) == this)
    {
        CCarAI::MakeWayForCarWithSiren(this);
    }

    float suspensionShake = 0.0f;
    float roughnessShake = 0.0f;
    float wheelSpinRate = 0.0f;
    float speed = m_vecMoveSpeed.SquaredMagnitude();
    for (int32_t i = 0; i < 4; i++) {
        float suspensionChange = m_fWheelsSuspensionCompressionPrev[i] - m_fWheelsSuspensionCompression[i];
        if (suspensionChange > 0.3f && !extraHandlingWheelsTouchingPavement && speed > 0.04f) {
            //m_damageManager.GetWheelStatus(i); // return value is ignored
            if (suspensionChange > suspensionShake)
                suspensionShake = suspensionChange;
        }

        if (m_fWheelsSuspensionCompression[i] < 1.0f && m_nStatus == STATUS_PLAYER) {
            float roughness = g_surfaceInfos->GetRoughness(m_wheelColPoint[i].m_nSurfaceTypeB) * 0.1f;
            roughnessShake = std::max(roughnessShake, roughness);
        }
        uint32_t handlingId = m_pHandlingData->m_nVehicleId;
        cTransmission& transmission = gHandlingDataMgr.GetVehiclePointer(handlingId)->GetTransmission();
        if (m_aWheelTimer[i] <= 0.0f
            && (m_fGasPedal > 0.5f || m_fGasPedal < -0.5f)
            && ((i == CARWHEEL_FRONT_LEFT || i == CARWHEEL_FRONT_RIGHT) && transmission.m_nDriveType != 'R'
                || (i == CARWHEEL_REAR_LEFT || i == CARWHEEL_REAR_RIGHT) && transmission.m_nDriveType != 'F'))
        {
            wheelSpinRate += CVehicle::WHEELSPIN_INAIR_TARGET_RATE;
        }
        else if (m_aWheelState[i] == WHEEL_STATE_SPINNING) {
            wheelSpinRate += CVehicle::WHEELSPIN_TARGET_RATE;
        }

        m_fWheelsSuspensionCompressionPrev[i] = m_fWheelsSuspensionCompression[i];
        m_fWheelsSuspensionCompression[i] = 1.0f;
    }

    if (m_pHandlingData->GetTransmission().m_nDriveType == '4')
        wheelSpinRate *= 0.25f;
    else
        wheelSpinRate *= 0.5f;

    float riseFallWheelSpinRate = CVehicle::WHEELSPIN_FALL_RATE;;
    if (wheelSpinRate >= m_fWheelSpinForAudio)
        riseFallWheelSpinRate = CVehicle::WHEELSPIN_RISE_RATE;

    riseFallWheelSpinRate = pow(riseFallWheelSpinRate, CTimer::ms_fTimeStep);
    m_fWheelSpinForAudio *= riseFallWheelSpinRate;
    m_fWheelSpinForAudio += (1.0f - riseFallWheelSpinRate) * wheelSpinRate;

    if ((CTimer::m_snTimeInMilliseconds & 0x7FF) > 800) {
        if (roughnessShake >= 0.29f)
            suspensionShake = 0.0f;
        roughnessShake = 0.0f;
    }

    if (!extraHandlingWheelsTouchingPavement
        && (suspensionShake > 0.0f || roughnessShake > 0.0f)
        && m_nStatus == STATUS_PLAYER)
    {
        float speed = m_vecMoveSpeed.SquaredMagnitude();
        if (speed > 0.01f) {
            speed = sqrt(speed);
            if (suspensionShake > 0.0f) {
                float frequency = (200.0f * suspensionShake * speed * 2000.0f) / m_fMass + 100.0f;
                frequency = std::min(frequency, 250.0f);
                int16_t time = static_cast<int16_t>(CTimer::ms_fTimeStep * 20000.0f / frequency);
                CPad::GetPad(0)->StartShake(time, static_cast<uint8_t>(frequency), 0);
            }
            else {
                float frequency = (200.0f * roughnessShake * speed * 2000.0f) / m_fMass + 40.0f;
                frequency = std::min(frequency, 150.0f);
                int16_t time = static_cast<int16_t>(CTimer::ms_fTimeStep * 5000.0f / frequency);
                CPad::GetPad(0)->StartShake(time, static_cast<uint8_t>(frequency), 0);
            }
        }
    }

    vehicleFlags.bAudioChangingGear = false;
    vehicleFlags.bVehicleColProcessed = false;

    if (!vehicleFlags.bWarnedPeds)
        CCarCtrl::ScanForPedDanger(this);
    if (handlingFlags.bHydraulicInst && m_vecMoveSpeed.Magnitude() < 0.2f) {
        auto& hydraulicData = CVehicle::m_aSpecialHydraulicData[m_vehicleSpecialColIndex];
        CPlayerPed* driver = static_cast<CPlayerPed*>(m_pDriver);
        if (m_nStatus == STATUS_PHYSICS
            && (hydraulicData.m_wheelSuspension[CARWHEEL_FRONT_LEFT] > 0.5f && hydraulicData.m_wheelSuspension[CARWHEEL_REAR_LEFT] > 0.5f
                || hydraulicData.m_wheelSuspension[CARWHEEL_FRONT_RIGHT] > 0.5f && hydraulicData.m_wheelSuspension[CARWHEEL_REAR_RIGHT] > 0.5f)
            || m_nStatus == STATUS_PLAYER
            && m_pDriver
            && m_pDriver->IsPlayer()
            && fabs(driver->GetPadFromPlayer()->GetCarGunLeftRight()) > 50.0f
            && fabs(driver->GetPadFromPlayer()->GetCarGunUpDown()) < 50.0f)
        {
            float turnSpeedForward = DotProduct(m_vecTurnSpeed, GetForward());
            const float speedSquared = turnSpeedForward * turnSpeedForward;
            float speedTimeStep = pow(0.985f, CTimer::ms_fTimeStep) / (speedSquared * 5.0f + 1.0f);
            float speed = pow(speedTimeStep, CTimer::ms_fTimeStep);
            speed *= turnSpeedForward;
            speed -= turnSpeedForward;

            CVector force = speed * GetUp() * -1.0f * m_fTurnMass;
            CVector point = GetRight() + Multiply3x3(GetMatrix(), &m_vecCentreOfMass);
            ApplyTurnForce(force, point);
        }
    }

    if (m_pTractor) {
        if (m_nStatus == STATUS_REMOTE_CONTROLLED) {
            bool updateTractorLink = false; // TODO: rename this variable later
            if (m_pTractor->m_vecMoveSpeed != 0.0f || m_vecMoveSpeed.SquaredMagnitude() > 0.01f) {
                updateTractorLink = true;
                m_pTractor->UpdateTractorLink(false, false);
            }
            CVehicle::UpdateTrailerLink(false, false);
            if (m_pTractor && m_nStatus == STATUS_REMOTE_CONTROLLED) {
                if (updateTractorLink)
                    m_pTractor->UpdateTractorLink(false, true);
                UpdateTrailerLink(false, true);
            }
        }
        else {
            BreakTowLink();
        }
    }
    else if (m_pTrailer) {
        if (m_pTrailer->m_nStatus == STATUS_REMOTE_CONTROLLED) {
            if (m_pTrailer->m_pTractor == this) {
                RemoveFromMovingList();
                AddToMovingList();
            }
        }
        else {
            m_pTrailer->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_pTrailer));
            m_pTrailer = nullptr;
        }
    }

    if (physicalFlags.bDisableCollisionForce && physicalFlags.bCollidable) {
        ResetMoveSpeed();
        ResetTurnSpeed();
        ResetFrictionMoveSpeed();
        ResetFrictionTurnSpeed();
    }
    else if (!skipPhysics
        && (m_fGasPedal == 0.0f || m_nStatus == STATUS_WRECKED)
        && fabs(m_vecMoveSpeed.x) < 0.0045f
        && fabs(m_vecMoveSpeed.y) < 0.0045f
        && fabs(m_vecMoveSpeed.z) < 0.0045f)
    {
        if (m_fDamageIntensity <= 0.0f || m_pDamageEntity != FindPlayerPed(-1)) {
            if ((!IsPlane() || static_cast<CPlane*>(this)->m_fAccelerationBreakStatus == 0.0f) &&
                (!IsHeli() || static_cast<CHeli*>(this)->m_fAccelerationBreakStatus == 0.0f))
            {
                if ((m_wMiscComponentAngle == 0.0f || m_wMiscComponentAngle == m_wVoodooSuspension)
                    && !physicalFlags.bSubmergedInWater)
                {
                    if ((!m_pTractor || m_pTractor->m_vecMoveSpeed == 0.0f) && DidAnyWheelTouchGroundPrev()) {
                        if (m_nModelIndex == MODEL_VORTEX || CCheat::m_aCheatsActive[CHEAT_CARS_ON_WATER]
                            && DidAnyWheelTouchShallowWaterGroundPrev())
                        {
                            m_nFakePhysics = 0;
                        }
                        else {
                            ResetMoveSpeed();
                            m_vecTurnSpeed.z = 0.0f;
                        }
                    }
                }
            }
        }
    }

    if (CWeather::Earthquake > 0.0f) {
        CVector& position = GetPosition();
        position.z = CGeneral::GetRandomNumberInRange(0.0f, CWeather::Earthquake * 0.5f);
    }
    if (m_nModelIndex == MODEL_COMBINE)
        CAutomobile::ProcessHarvester();
    if (m_nModelIndex == MODEL_RHINO && (m_vecMoveSpeed != 0.0f || m_vecTurnSpeed != 0.0f)) {
        m_doors[DOOR_LEFT_REAR].m_fOpenAngle = 1.0f;
        m_doors[DOOR_LEFT_REAR].m_fClosedAngle = 1.0f;
        m_doors[DOOR_LEFT_REAR].m_fAngle = 1.0f;
        m_doors[DOOR_LEFT_REAR].m_fPrevAngle = 1.0f;
        m_doors[DOOR_RIGHT_REAR].m_fOpenAngle = 1.0f;
        m_doors[DOOR_RIGHT_REAR].m_fClosedAngle = 1.0f;
        m_doors[DOOR_RIGHT_REAR].m_fAngle = 1.0f;
        m_doors[DOOR_RIGHT_REAR].m_fPrevAngle = 1.0f;
    }
}

void CAutomobile::ProcessControl_Reversed()
{
    return CAutomobile::ProcessControl();
}

void CAutomobile::ProcessSuspension_Reversed()
{
    return CAutomobile::ProcessSuspension();
}

CVector* CAutomobile::AddMovingCollisionSpeed(CVector* out, CVector& vecSpeed)
{
    return ((CVector * (__thiscall*)(CVehicle*, CVector*, CVector&))(*(void***)this)[49])(this, out, vecSpeed);
}

// Converted from void CAutomobile::ProcessAI(uint &) 0x0
bool CAutomobile::ProcessAI(unsigned int& extraHandlingFlags)
{
    return ((bool(__thiscall*)(CAutomobile*, unsigned int&))(*(void***)this)[66])(this, extraHandlingFlags);
}

// Converted from void CAutomobile::ResetSuspension(void) 0x0
void CAutomobile::ResetSuspension()
{
    ((void(__thiscall*)(CAutomobile*))(*(void***)this)[67])(this);
}

// Converted from void CAutomobile::ProcessFlyingCarStuff(void) 0x0
void CAutomobile::ProcessFlyingCarStuff()
{
    ((void(__thiscall*)(CAutomobile*))(*(void***)this)[68])(this);
}

// Converted from void CAutomobile::DoHoverSuspensionRatios(void) 0x0
void CAutomobile::DoHoverSuspensionRatios()
{
    ((void(__thiscall*)(CAutomobile*))(*(void***)this)[69])(this);
}

void CAutomobile::ProcessSuspension()
{
    float springLength[4];
    CVector contactPoints[4]; 
    float wheelSpringForceDampingLimits[4]; 
    CVector directions[4];
    CVector contactSpeeds[4];
    int32_t wheelLineIndices[4];

    for (int32_t i = 0; i < 4; i++) {
        springLength[i] = m_fWheelsSuspensionCompression[i];
        wheelSpringForceDampingLimits[i] = 0.0f;
    }

    float forwardSpeed = fabs(DotProduct(m_vecMoveSpeed, GetForward()));

    int32_t numWheelLoops = 1;
    if (ModelIndices::IsRhino(m_nModelIndex) && CReplay::Mode != REPLAY_MODE_1)
        numWheelLoops = 3;
    for (int32_t wheelLoopIndex = 0; wheelLoopIndex < numWheelLoops; wheelLoopIndex++) {
        for (int32_t i = 0; i < 4; i++) {
            directions[i] = GetUp() * -1.0f;
            if (springLength[i] < 1.0f) 
                contactPoints[i] = m_wheelColPoint[i].m_vecPoint - GetPosition();
        }

        for (int32_t i = 0; i < 4; i++) {
            if (springLength[i] >= 1.0f)
                continue;
            float suspensionBias = m_pHandlingData->m_fSuspensionBiasBetweenFrontAndRear;
            if (i == CARWHEEL_REAR_LEFT || i == CARWHEEL_REAR_RIGHT)
                suspensionBias = 1.0f - suspensionBias;

            float fSuspensionForceLevel = m_pHandlingData->m_fSuspensionForceLevel;
            if (handlingFlags.bHydraulicGeom && handlingFlags.bHydraulicInst) {
                if (handlingFlags.bNpcNeutralHandl && m_nStatus == STATUS_SIMPLE)
                    suspensionBias = 0.5f;
                if (fabs(forwardSpeed) < 0.15f)
                        fSuspensionForceLevel *= 1.5f;
            }
            if (ModelIndices::IsVortex(m_nModelIndex))
                fSuspensionForceLevel *= fabs(static_cast<CPlane*>(this)->m_fAccelerationBreakStatus) * 0.25f + 1.0f;
            if (CCheat::m_aCheatsActive[CHEAT_CARS_ON_WATER] || ModelIndices::IsVortex(m_nModelIndex))
                ApplySpringCollision(
                    fSuspensionForceLevel,
                    directions[i],
                    contactPoints[i],
                    springLength[i],
                    suspensionBias,
                    wheelSpringForceDampingLimits[i]);
            else
                ApplySpringCollisionAlt(
                    fSuspensionForceLevel,
                    directions[i],
                    contactPoints[i],
                    springLength[i],
                    suspensionBias,
                    m_wheelColPoint[i].m_vecNormal,
                    wheelSpringForceDampingLimits[i]);
        }

        for (int32_t i = 0; i < 4; ++i) {
            contactSpeeds[i] = CPhysical::GetSpeed(contactPoints[i]);
            if (m_pWheelCollisionEntity[i])
                contactSpeeds[i] -= m_pWheelCollisionEntity[i]->GetSpeed(m_vWheelCollisionPos[i]);
            if (m_fWheelsSuspensionCompression[i] < 1.0f && m_wheelColPoint[i].m_vecNormal.z > 0.35f) {
                directions[i] = -m_wheelColPoint[i].m_vecNormal;
            }
        }

        for (int32_t i = 0; i < 4; ++i) {
            float dampingForce = m_pHandlingData->m_fSuspensionDampingLevel;
            if (handlingFlags.bHydraulicInst && dampingForce > 0.1f && fabs(forwardSpeed) < 0.15f)
                dampingForce = 0.1f;
            if (springLength[i] < 1.0f && !npcFlags.bSoftSuspension)
                ApplySpringDampening(
                    dampingForce,
                    wheelSpringForceDampingLimits[i],
                    directions[i],
                    contactPoints[i],
                    contactSpeeds[i]);
        }
        if (!ModelIndices::IsRhino(m_nModelIndex))
            continue;
        if (numWheelLoops <= 1 || wheelLoopIndex > 1)
            break;
        if (wheelLoopIndex == 0) {
            wheelLineIndices[CARWHEEL_FRONT_LEFT] = 4;
            wheelLineIndices[CARWHEEL_REAR_LEFT] = 7;
            wheelLineIndices[CARWHEEL_FRONT_RIGHT] = 8;
            wheelLineIndices[CARWHEEL_REAR_RIGHT] = 11;

            springLength[CARWHEEL_FRONT_LEFT] = m_doors[DOOR_LEFT_REAR].m_fOpenAngle;
            springLength[CARWHEEL_REAR_LEFT] = m_doors[DOOR_LEFT_REAR].m_fPrevAngle;
            springLength[CARWHEEL_FRONT_RIGHT] = m_doors[DOOR_RIGHT_REAR].m_fOpenAngle;
            springLength[CARWHEEL_REAR_RIGHT] = m_doors[DOOR_RIGHT_REAR].m_fPrevAngle;
        }
        else if (wheelLoopIndex == 1) {
            springLength[CARWHEEL_FRONT_LEFT] = m_doors[DOOR_LEFT_REAR].m_fClosedAngle;
            springLength[CARWHEEL_REAR_LEFT] = m_doors[DOOR_LEFT_REAR].m_fAngle;
            springLength[CARWHEEL_FRONT_RIGHT] = m_doors[DOOR_RIGHT_REAR].m_fClosedAngle;
            springLength[CARWHEEL_REAR_RIGHT] = m_doors[DOOR_RIGHT_REAR].m_fAngle;

            wheelLineIndices[CARWHEEL_FRONT_LEFT] = 5;
            wheelLineIndices[CARWHEEL_REAR_LEFT] = 6;
            wheelLineIndices[CARWHEEL_FRONT_RIGHT] = 9;
            wheelLineIndices[CARWHEEL_REAR_RIGHT] = 10;
        }

        CCollisionData* colData = GetColModel()->m_pColData;
        float wheelsSuspensionCompressionPrev[4];
        for (int32_t i = 0; i < 4; i++) {
            float wheelRadius = 1.0f - m_aSuspensionSpringLength[i] / m_aSuspensionLineLength[i];
            wheelsSuspensionCompressionPrev[i] = (wheelsSuspensionCompressionPrev[i] - wheelRadius) / (1.0f - wheelRadius);
            // yes, wheelsSuspensionCompressionPrev is unused here

            CColLine& colLine = colData->m_pLines[wheelLineIndices[i]];
            contactPoints[i] = colLine.m_vecStart;
            contactPoints[i].z -= m_aSuspensionLineLength[i] * springLength[i];
            contactPoints[i] = Multiply3x3(m_matrix, &contactPoints[i]);
        }
    }

    float speedThreshold = 0.02f;
    float rollOnToWheelsForce = ROLL_ONTO_WHEELS_FORCE;
    if (m_nStatus != STATUS_PLAYER && m_nStatus != STATUS_HELI) {
        speedThreshold *= 2.0f;
        rollOnToWheelsForce *= 2.0f;
    }

    if (forwardSpeed < speedThreshold) {
        float fDir = 0.0f;
        if (m_fWheelsSuspensionCompression[CARWHEEL_FRONT_LEFT] == 1.0f
            && m_fWheelsSuspensionCompression[CARWHEEL_REAR_LEFT] == 1.0f
            && (m_fWheelsSuspensionCompression[CARWHEEL_FRONT_RIGHT] < 1.0f
                || m_fWheelsSuspensionCompression[CARWHEEL_REAR_RIGHT] < 1.0f))
        {
            fDir = 1.0f;
        }
        else if (forwardSpeed < speedThreshold
            && m_fWheelsSuspensionCompression[CARWHEEL_FRONT_RIGHT] == 1.0f
            && m_fWheelsSuspensionCompression[CARWHEEL_REAR_RIGHT] == 1.0f
            && (m_fWheelsSuspensionCompression[CARWHEEL_FRONT_LEFT] < 1.0f
                || m_fWheelsSuspensionCompression[CARWHEEL_REAR_LEFT] < 1.0f))
        {
            fDir = -1.0f;
        }

        if (fDir != 0.0f) {
            CVector right = CrossProduct(GetForward(), CVector(0.0f, 0.0f, 1.0f));
            if (fabs(DotProduct(right, GetRight())) < 0.6f) {
                auto colModel = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel();
                CVector force = GetUp() * fDir * rollOnToWheelsForce * m_fTurnMass;
                CVector point = GetRight() * colModel->GetBoundingBox().m_vecMax.x;
                ApplyTurnForce(force, point);
                ApplyMoveForce(-right * rollOnToWheelsForce * m_fMass * fDir);
            }
        }
    }
}

// Converted from thiscall void CAutomobile::SetupModelNodes(void) 0x6A0770
void CAutomobile::SetupModelNodes()
{
    ((void(__thiscall*)(CAutomobile*))0x6A0770)(this);
}

void CAutomobile::HydraulicControl()
{
    auto modelInfo = CModelInfo::GetModelInfo(m_nModelIndex)->AsVehicleModelInfoPtr();
    float wheelRadius = modelInfo->m_fWheelSizeFront * 0.5f;
    if (m_nStatus == STATUS_PLAYER ||
        m_nStatus == STATUS_PHYSICS
        && IsCreatedBy(MISSION_VEHICLE)
        && m_vehicleSpecialColIndex >= 0
        && !handlingFlags.bHydraulicNone) {
        CPlayerPed* driver = nullptr;
        if (m_nStatus == STATUS_PLAYER) {
            if (m_pDriver && m_pDriver->IsPlayer())
                driver = static_cast<CPlayerPed*>(m_pDriver);
            if (CGameLogic::GameState != GAME_STATE_0)
                return;
        }
        if (!CVehicle::GetSpecialColModel())
            return;

        CCollisionData* colData = CVehicle::m_aSpecialColModel[m_vehicleSpecialColIndex].m_pColData;
        auto& hydraulicData = CVehicle::m_aSpecialHydraulicData[m_vehicleSpecialColIndex];
        float normalUpperLimit = hydraulicData.m_fSuspensionNormalUpperLimit;
        float normalLowerLimit = hydraulicData.m_fSuspensionNormalLowerLimit;
        float extendedUpperLimit = hydraulicData.m_fSuspensionExtendedUpperLimit;
        float extendedLowerLimit = hydraulicData.m_fSuspensionExtendedLowerLimit;
        float normalSpringLength = normalUpperLimit - normalLowerLimit;
        float extendedSpringLength = extendedUpperLimit - extendedLowerLimit;
        if (hydraulicData.m_fSuspensionExtendedUpperLimit >= 100.0f) {
            float minz = 0.0f;
            for (int32_t i = 0; i < colData->m_nNumSpheres; i++) {
                auto& colsphere = colData->m_pSpheres[i];
                float z = colsphere.m_vecCenter.z - colsphere.m_fRadius;
                if (z < minz)
                    minz = z;
            }

            CVector pos;
            modelInfo->GetWheelPosn(CARWHEEL_FRONT_LEFT, pos, false);
            float limitExtend = minz - pos.z;
            normalLowerLimit = m_pHandlingData->m_fSuspensionLowerLimit;
            normalUpperLimit = m_pHandlingData->m_fSuspensionUpperLimit;
            normalSpringLength = normalUpperLimit - normalLowerLimit;
            if (handlingFlags.bHydraulicGeom)
                normalSpringLength *= 1.5f;
            normalUpperLimit = normalSpringLength + normalLowerLimit;
            hydraulicData.m_fSuspensionNormalUpperLimit = normalUpperLimit;
            hydraulicData.m_fSuspensionNormalLowerLimit = normalLowerLimit;
            if (handlingFlags.bHydraulicGeom) {
                extendedUpperLimit = normalUpperLimit - 0.4f;
                extendedLowerLimit = normalLowerLimit - 0.4f;
            }
            else {
                extendedUpperLimit = normalUpperLimit - 0.2f;
                extendedLowerLimit = normalLowerLimit - 0.2f;
            }
            extendedUpperLimit = std::max(extendedUpperLimit, limitExtend);
            extendedSpringLength = extendedUpperLimit - extendedLowerLimit;
            hydraulicData.m_fSuspensionExtendedUpperLimit = extendedUpperLimit;
            hydraulicData.m_fSuspensionExtendedLowerLimit = extendedLowerLimit;

            // or 0.15f * normalSpringLength
            float normalSpringLength_15_Percent = (1.0f - 0.7f) * 0.5f * normalSpringLength;
            hydraulicData.m_fSuspensionNormalIdleUpperLimit = normalUpperLimit - normalSpringLength_15_Percent;
            hydraulicData.m_fSuspensionNormalIdleLowerLimit = normalLowerLimit + normalSpringLength_15_Percent;
            float wheelHeight = limitExtend + wheelRadius - 0.1f;
            if (wheelHeight < hydraulicData.m_fSuspensionNormalIdleLowerLimit) {
                float height = hydraulicData.m_fSuspensionNormalIdleLowerLimit - wheelHeight;
                hydraulicData.m_fSuspensionNormalIdleUpperLimit -= height;
                hydraulicData.m_fSuspensionNormalIdleLowerLimit -= height;
            }
        }

        bool setPrevRatio = false;
        if (m_wMiscComponentAngle >= 20 || m_fMoveDirection <= 0.02f || m_fGasPedal == 0.0f) {
            if (m_wMiscComponentAngle && m_wMiscComponentAngle < 61 && m_fMoveDirection < 0.01f) {
                m_wMiscComponentAngle--;
                if (m_wMiscComponentAngle == 1)
                    m_vehicleAudio.AddAudioEvent(AE_SUSPENSION_OFF, 0.0f);
            }
        }
        else if (m_wMiscComponentAngle) {
            m_wMiscComponentAngle++;
        }
        else {
            m_wMiscComponentAngle = 20;
            m_vehicleAudio.AddAudioEvent(AE_SUSPENSION_ON, 0.0f);
            setPrevRatio = true;
        }

        bool suspensionTriggered = false;
        float wheelPositions[4];
        float suspensionChange[4];

        CVector pos;
        if (driver && driver->GetPadFromPlayer()->HornJustDown()) {
            float lineLength = extendedSpringLength + wheelRadius;
            m_wMiscComponentAngle = m_wMiscComponentAngle < 500 ? 500 : 60;
            if (m_wMiscComponentAngle >= 500) {
                for (int32_t i = 0; i < 4; i++) {
                    CColLine& line = colData->m_pLines[i];
                    wheelPositions[i] = line.m_vecStart.z - m_aSuspensionLineLength[i] * m_fWheelsSuspensionCompression[i];
                    modelInfo->GetWheelPosn(i, pos, false);
                    pos.z += extendedUpperLimit;
                    line.m_vecStart = pos;
                    pos.z -= lineLength;
                    line.m_vecEnd = pos;
                    m_aSuspensionSpringLength[i] = extendedSpringLength;
                    m_aSuspensionLineLength[i] = lineLength;
                    if (m_fWheelsSuspensionCompression[i] < 1.0f) {
                        float compressed = (line.m_vecStart.z - wheelPositions[i]) / lineLength;
                        m_fWheelsSuspensionCompression[i] = std::min(compressed, 1.0f);
                    }
                }
                m_vehicleAudio.AddAudioEvent(AE_SUSPENSION_TRIGGER, 0.0f);
                suspensionTriggered = true;
            }
            else {
                lineLength = normalSpringLength + wheelRadius;
                for (int32_t i = 0; i < 4; i++) {
                    CColLine& line = colData->m_pLines[i];
                    wheelPositions[i] = line.m_vecStart.z - m_fWheelsSuspensionCompression[i] * m_aSuspensionLineLength[i];
                    modelInfo->GetWheelPosn(i, pos, false);
                    pos.z += normalUpperLimit;
                    line.m_vecStart = pos;
                    pos.z -= lineLength;
                    line.m_vecEnd = pos;
                    m_aSuspensionSpringLength[i] = normalSpringLength;
                    m_aSuspensionLineLength[i] = lineLength;
                    if (m_fWheelsSuspensionCompression[i] < 1.0f) {
                        float compressed = (line.m_vecStart.z - wheelPositions[i]) / lineLength;
                        m_fWheelsSuspensionCompression[i] = std::min(compressed, 1.0f);
                    }
                }
                m_vehicleAudio.AddAudioEvent(AE_SUSPENSION_HYDRAULIC, 0.0f);
            }
        }

        if (!suspensionTriggered)
        {
            for (int32_t i = 0; i < 4; i++) {
                suspensionChange[i] = 1.0f;
            }

            if (m_nStatus == STATUS_PHYSICS) {
                for (int32_t i = 0; i < 4; i++) {
                    suspensionChange[i] = hydraulicData.m_wheelSuspension[i];
                }
            }
            else if (driver) {
                if (!driver->GetPadFromPlayer()->GetHydraulicJump()) {
                    float gunLeftRight = driver->GetPadFromPlayer()->GetCarGunLeftRight();
                    float gunUpDown = driver->GetPadFromPlayer()->GetCarGunUpDown();
                    float jumpFactor = (sqrt(gunUpDown * gunUpDown + gunLeftRight * gunLeftRight) * 1.5f) / 128.0f;
                    float angle = atan2(gunLeftRight, gunUpDown) - DegreesToRadians(45.0f);
                    float change_rear_right = cos(angle) * jumpFactor;
                    float change_front_right = sin(angle) * jumpFactor;
                    float change_rear_left = -change_front_right;
                    float change_front_left = -change_rear_right;
                    suspensionChange[CARWHEEL_FRONT_LEFT] = std::max(0.0f, change_front_left);
                    suspensionChange[CARWHEEL_REAR_LEFT] = std::max(0.0f, change_rear_left);
                    suspensionChange[CARWHEEL_FRONT_RIGHT] = std::max(0.0f, change_front_right);
                    suspensionChange[CARWHEEL_REAR_RIGHT] = std::max(0.0f, change_rear_right);
                }
            }

            float maxDelta = 0.0f;
            if (m_wMiscComponentAngle < 500u) {
                if (suspensionChange[CARWHEEL_FRONT_LEFT] == 0.0f
                    && suspensionChange[CARWHEEL_REAR_LEFT] == 0.0f
                    && suspensionChange[CARWHEEL_FRONT_RIGHT] == 0.0f
                    && suspensionChange[CARWHEEL_REAR_RIGHT] == 0.0f)
                {
                    if (m_wMiscComponentAngle == 0) {
                        normalUpperLimit = hydraulicData.m_fSuspensionNormalIdleUpperLimit;
                        normalLowerLimit = hydraulicData.m_fSuspensionNormalIdleLowerLimit;
                        normalSpringLength = normalUpperLimit - normalLowerLimit;
                    }
                }
                else {
                    if (m_wMiscComponentAngle == 0) {
                        for (int32_t i = 0; i < 4; i++) {
                            suspensionChange[i] = 0.0f;
                        }
                    }
                    m_wMiscComponentAngle = 60;
                }

                for (int32_t i = 0; i < 4; i++) {
                    CColLine& line = colData->m_pLines[i];
                    suspensionChange[i] = std::min(suspensionChange[i], 1.0f);
                    float springLength = (extendedSpringLength - normalSpringLength) * suspensionChange[i] + normalSpringLength;
                    float lineLength = springLength + wheelRadius;
                    wheelPositions[i] = line.m_vecStart.z - m_aSuspensionLineLength[i] * m_fWheelsSuspensionCompression[i];
                    modelInfo->GetWheelPosn(i, pos, false);
                    pos.z += (extendedUpperLimit - normalUpperLimit) * suspensionChange[i] + normalUpperLimit;
                    line.m_vecStart = pos;
                    pos.z -= lineLength;
                    maxDelta = std::max(fabs(maxDelta), fabs(pos.z - line.m_vecEnd.z));
                    line.m_vecEnd = pos;
                    m_aSuspensionLineLength[i] = lineLength;
                    m_aSuspensionSpringLength[i] = springLength;
                    if (m_fWheelsSuspensionCompression[i] < 1.0f) {
                        float compressed = (line.m_vecStart.z - wheelPositions[i]) / lineLength;
                        m_fWheelsSuspensionCompression[i] = std::min(compressed, 1.0f);
                    }
                }
            }
            else {
                if (m_wMiscComponentAngle < 504u)
                    m_wMiscComponentAngle++;
                for (int32_t i = 0; i < 4; i++) {
                    CColLine& line = colData->m_pLines[i];
                    suspensionChange[i] = std::min(suspensionChange[i], 1.0f);
                    float springLength = (normalSpringLength - extendedSpringLength) * suspensionChange[i] + extendedSpringLength;
                    wheelPositions[i] = line.m_vecStart.z - m_aSuspensionLineLength[i] * m_fWheelsSuspensionCompression[i];
                    modelInfo->GetWheelPosn(i, pos, false);
                    pos.z += (normalUpperLimit - extendedUpperLimit) * suspensionChange[i] + extendedUpperLimit;
                    float lineLength = springLength + wheelRadius;
                    line.m_vecStart = pos;
                    pos.z -= lineLength;
                    maxDelta = std::max(fabs(maxDelta), fabs(pos.z - line.m_vecEnd.z));
                    line.m_vecEnd = pos;
                    m_aSuspensionLineLength[i] = lineLength;
                    m_aSuspensionSpringLength[i] = springLength;
                    if (m_fWheelsSuspensionCompression[i] < 1.0f) {
                        float compressed = (line.m_vecStart.z - wheelPositions[i]) / lineLength;
                        m_fWheelsSuspensionCompression[i] = std::min(compressed, 1.0f);
                    }
                }
            }
            float limitDiff = extendedLowerLimit - normalLowerLimit;
            if (limitDiff != 0.0f && fabs(maxDelta / limitDiff) > 0.01f) {
                float f = (limitDiff + maxDelta) * 0.5f / limitDiff;
                f = clamp<float>(f, 0.0f, 1.0f);
                if (f < 0.4f || f > 0.6f)
                    setPrevRatio = true;
                if (f < 0.5f - CTimer::ms_fTimeStep * 0.05f)
                    m_vehicleAudio.AddAudioEvent(AE_SUSPENSION_HYDRAULIC, 0.0f);
                else if (f > CTimer::ms_fTimeStep * 0.05f + 0.5f)
                    m_vehicleAudio.AddAudioEvent(AE_SUSPENSION_TRIGGER, 0.0f);
                else if (f > CTimer::ms_fTimeStep * 0.025f + 0.5f)
                    m_vehicleAudio.AddAudioEvent(AE_SUSPENSION_HYDRAULIC, 0.0f);
            }
        }

        if (setPrevRatio || suspensionTriggered) {
            for (int32_t i = 0; i < 4; i++) {
                float wheelRadius = 1.0f - m_aSuspensionSpringLength[i] / m_aSuspensionLineLength[i];
                m_fWheelsSuspensionCompressionPrev[i] = (m_fWheelsSuspensionCompression[i] - wheelRadius) / (1.0f - wheelRadius);
            }
        }
        for (int32_t i = 0; i < 4; i++) {
            hydraulicData.m_wheelSuspension[i] = 0.0f;
        }
    }
}

// Converted from thiscall bool CAutomobile::UpdateMovingCollision(float angle) 0x6A1460
bool CAutomobile::UpdateMovingCollision(float angle)
{
    return ((bool(__thiscall*)(CAutomobile*, float))0x6A1460)(this, angle);
}

// Converted from thiscall float CAutomobile::GetMovingCollisionOffset(void) 0x6A2150
float CAutomobile::GetMovingCollisionOffset()
{
    return ((float(__thiscall*)(CAutomobile*))0x6A2150)(this);
}

// Converted from thiscall void CAutomobile::TellHeliToGoToCoors(float x, float y, float z, float altitudeMin, float altitudeMax) 0x6A2390
void CAutomobile::TellHeliToGoToCoors(float x, float y, float z, float altitudeMin, float altitudeMax)
{
    ((void(__thiscall*)(CAutomobile*, float, float, float, float, float))0x6A2390)(this, x, y, z, altitudeMin, altitudeMax);
}

// Converted from thiscall void CAutomobile::SetHeliOrientation(float angle) 0x6A2450
void CAutomobile::SetHeliOrientation(float angle)
{
    ((void(__thiscall*)(CAutomobile*, float))0x6A2450)(this, angle);
}

// Converted from thiscall void CAutomobile::ClearHeliOrientation(void) 0x6A2460
void CAutomobile::ClearHeliOrientation()
{
    ((void(__thiscall*)(CAutomobile*))0x6A2460)(this);
}

// Converted from thiscall void CAutomobile::TellPlaneToGoToCoors(float x, float y, float z, float altitudeMin, float altitudeMax) 0x6A2470
void CAutomobile::TellPlaneToGoToCoors(float x, float y, float z, float altitudeMin, float altitudeMax)
{
    ((void(__thiscall*)(CAutomobile*, float, float, float, float, float))0x6A2470)(this, x, y, z, altitudeMin, altitudeMax);
}

// Converted from thiscall void CAutomobile::HideAllComps(void) 0x6A2510
void CAutomobile::HideAllComps()
{
    ((void(__thiscall*)(CAutomobile*))0x6A2510)(this);
}

// Converted from thiscall void CAutomobile::ShowAllComps(void) 0x6A2520
void CAutomobile::ShowAllComps()
{
    ((void(__thiscall*)(CAutomobile*))0x6A2520)(this);
}

// Converted from thiscall void CAutomobile::SetRandomDamage(bool) 0x6A2530
void CAutomobile::SetRandomDamage(bool arg0)
{
    ((void(__thiscall*)(CAutomobile*, bool))0x6A2530)(this, arg0);
}

// Converted from thiscall void CAutomobile::SetTotalDamage(bool) 0x6A27F0
void CAutomobile::SetTotalDamage(bool arg0)
{
    ((void(__thiscall*)(CAutomobile*, bool))0x6A27F0)(this, arg0);
}

// Converted from cdecl RpMaterial* DisableMatFx(RpMaterial *material, void *data) 0x6A2980
RpMaterial* DisableMatFx(RpMaterial* material, void* data)
{
    return ((RpMaterial * (__cdecl*)(RpMaterial*, void*))0x6A2980)(material, data);
}

// Converted from thiscall void CAutomobile::ReduceHornCounter(void) 0x6A29A0
void CAutomobile::ReduceHornCounter()
{
    ((void(__thiscall*)(CAutomobile*))0x6A29A0)(this);
}

// Converted from thiscall void CAutomobile::CustomCarPlate_BeforeRenderingStart(CVehicleModelInfo *model) 0x6A2F00
void CAutomobile::CustomCarPlate_BeforeRenderingStart(CVehicleModelInfo* model)
{
    ((void(__thiscall*)(CAutomobile*, CVehicleModelInfo*))0x6A2F00)(this, model);
}

// Converted from thiscall void CAutomobile::CustomCarPlate_AfterRenderingStop(CVehicleModelInfo *model) 0x6A2F30
void CAutomobile::CustomCarPlate_AfterRenderingStop(CVehicleModelInfo* model)
{
    ((void(__thiscall*)(CAutomobile*, CVehicleModelInfo*))0x6A2F30)(this, model);
}

// Converted from thiscall bool CAutomobile::GetAllWheelsOffGround(void) 0x6A2F70
bool CAutomobile::GetAllWheelsOffGround()
{
    return ((bool(__thiscall*)(CAutomobile*))0x6A2F70)(this);
}

// Converted from thiscall void CAutomobile::DebugCode(void) 0x6A2F80
void CAutomobile::DebugCode()
{
    ((void(__thiscall*)(CAutomobile*))0x6A2F80)(this);
}

// Converted from thiscall void CAutomobile::FixTyre(eWheels wheel) 0x6A3580
void CAutomobile::FixTyre(eWheelStatus wheel)
{
    ((void(__thiscall*)(CAutomobile*, eWheelStatus))0x6A3580)(this, wheel);
}

// Converted from thiscall void CAutomobile::FixDoor(int nodeIndex, eDoors door) 0x6A35A0
void CAutomobile::FixDoor(int nodeIndex, eDoors door)
{
    ((void(__thiscall*)(CAutomobile*, int, eDoors))0x6A35A0)(this, nodeIndex, door);
}

// Converted from thiscall void CAutomobile::FixPanel(int nodeIndex, ePanels panel) 0x6A3670
void CAutomobile::FixPanel(int nodeIndex, ePanels panel)
{
    ((void(__thiscall*)(CAutomobile*, int, ePanels))0x6A3670)(this, nodeIndex, panel);
}

// Converted from thiscall void CAutomobile::SetTaxiLight(bool enable) 0x6A3740
void CAutomobile::SetTaxiLight(bool enable)
{
    ((void(__thiscall*)(CAutomobile*, bool))0x6A3740)(this, enable);
}

// Converted from cdecl void CAutomobile::SetAllTaxiLights(bool) 0x6A3760
void CAutomobile::SetAllTaxiLights(bool arg0)
{
    ((void(__cdecl*)(bool))0x6A3760)(arg0);
}

// Converted from thiscall void CAutomobile::PlayHornIfNecessary(void) 0x6A3820
void CAutomobile::PlayHornIfNecessary()
{
    ((void(__thiscall*)(CAutomobile*))0x6A3820)(this);
}

// Converted from thiscall void CAutomobile::SetBusDoorTimer(uint time, uchar) 0x6A3860
void CAutomobile::SetBusDoorTimer(unsigned int time, unsigned char arg1)
{
    ((void(__thiscall*)(CAutomobile*, unsigned int, unsigned char))0x6A3860)(this, time, arg1);
}

// Converted from thiscall void CAutomobile::ProcessAutoBusDoors(void) 0x6A38A0
void CAutomobile::ProcessAutoBusDoors()
{
    ((void(__thiscall*)(CAutomobile*))0x6A38A0)(this);
}

// Converted from thiscall void CAutomobile::BoostJumpControl(void) 0x6A3A60
void CAutomobile::BoostJumpControl()
{
    ((void(__thiscall*)(CAutomobile*))0x6A3A60)(this);
}

void CAutomobile::DoNitroEffect(float power)
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall*)(CAutomobile*, float))0x6A3BD0)(this, power);
#else
    auto modelInfo = CModelInfo::GetModelInfo(m_nModelIndex)->AsVehicleModelInfoPtr();
    CVector exhaustPosition = modelInfo->m_pVehicleStruct->m_avDummyPos[DUMMY_EXHAUST];
    bool firstExhaustSubmergedInWater = false;
    bool secondExhaustSubmergedInWater = false;
    float level = 0.0f;
    if (physicalFlags.bTouchingWater) {
        CVector point = *m_matrix * exhaustPosition;
        if (CWaterLevel::GetWaterLevel(point.x, point.y, point.z, &level, true, nullptr)) {
            if (level >= point.z)
                firstExhaustSubmergedInWater = true;
        }
    }
    CVector secondExhaustPosition;
    if (m_pHandlingData->m_bDoubleExhaust) {
        secondExhaustPosition = exhaustPosition;
        secondExhaustPosition.x *= -1.0f;
        if (!physicalFlags.bTouchingWater) {
            CVector point = *m_matrix * secondExhaustPosition;
            if (CWaterLevel::GetWaterLevel(point.x, point.y, point.z, &level, true, nullptr)) {
                if (level >= point.z)
                    secondExhaustSubmergedInWater = true;
            }
        }
    }

    RwMatrix* rwMatrix = CEntity::GetModellingMatrix();
    FxSystem_c* firstExhaustFxSystem = m_exhaustNitroFxSystem[0];
    if (firstExhaustFxSystem)
    {
        firstExhaustFxSystem->SetConstTime(1, fabs(power));
        eFxSystemPlayStatus playStatus = firstExhaustFxSystem->GetPlayStatus();
        if (playStatus == eFxSystemPlayStatus::FX_PLAYING && firstExhaustSubmergedInWater)
            firstExhaustFxSystem->Stop();
        else if (playStatus == eFxSystemPlayStatus::FX_STOPPED && !firstExhaustSubmergedInWater)
            firstExhaustFxSystem->Play();
    }
    else if (!firstExhaustSubmergedInWater && rwMatrix) {
        firstExhaustFxSystem = g_fxMan.CreateFxSystem("nitro", &exhaustPosition, rwMatrix, true);
        m_exhaustNitroFxSystem[0] = firstExhaustFxSystem;
        if (firstExhaustFxSystem) {
            firstExhaustFxSystem->SetLocalParticles(true);
            firstExhaustFxSystem->Play();
        }
    }
    if (m_pHandlingData->m_bDoubleExhaust) {
        FxSystem_c* secondExhaustFxSystem = m_exhaustNitroFxSystem[1];
        if (secondExhaustFxSystem) {
            secondExhaustFxSystem->SetConstTime(1, fabs(power));
            if (secondExhaustFxSystem->GetPlayStatus() == eFxSystemPlayStatus::FX_PLAYING && secondExhaustSubmergedInWater)
                secondExhaustFxSystem->Stop();
            else if (secondExhaustFxSystem->GetPlayStatus() == eFxSystemPlayStatus::FX_STOPPED && !secondExhaustSubmergedInWater)
                secondExhaustFxSystem->Play();
        }
        else if (!firstExhaustSubmergedInWater && rwMatrix) {
            secondExhaustFxSystem = g_fxMan.CreateFxSystem("nitro", &secondExhaustPosition, rwMatrix, true);
            m_exhaustNitroFxSystem[1] = secondExhaustFxSystem;
            if (secondExhaustFxSystem) {
                secondExhaustFxSystem->SetLocalParticles(1);// enable 'local positions' flag
                secondExhaustFxSystem->Play();
            }
        }
    }
#endif
}

// Converted from thiscall void CAutomobile::StopNitroEffect(void) 0x6A3E60
void CAutomobile::StopNitroEffect()
{
    ((void(__thiscall*)(CAutomobile*))0x6A3E60)(this);
}

// Converted from thiscall void CAutomobile::NitrousControl(signed char) 0x6A3EA0
void CAutomobile::NitrousControl(signed char arg0)
{
    ((void(__thiscall*)(CAutomobile*, signed char))0x6A3EA0)(this, arg0);
}

// Converted from thiscall void CAutomobile::TowTruckControl(void) 0x6A40F0
void CAutomobile::TowTruckControl()
{
    ((void(__thiscall*)(CAutomobile*))0x6A40F0)(this);
}

// Converted from thiscall CPed* CAutomobile::KnockPedOutCar(eWeaponType, ushort, CPed *) 0x6A44C0
CPed* CAutomobile::KnockPedOutCar(eWeaponType arg0, unsigned short arg1, CPed* arg2)
{
    return ((CPed * (__thiscall*)(CAutomobile*, eWeaponType, unsigned short, CPed*))0x6A44C0)(this, arg0, arg1, arg2);
}

// Converted from thiscall void CAutomobile::PopBootUsingPhysics(void) 0x6A44D0
void CAutomobile::PopBootUsingPhysics()
{
    ((void(__thiscall*)(CAutomobile*))0x6A44D0)(this);
}

// Converted from thiscall void CAutomobile::CloseAllDoors(void) 0x6A4520
void CAutomobile::CloseAllDoors()
{
    ((void(__thiscall*)(CAutomobile*))0x6A4520)(this);
}

// Converted from thiscall void CAutomobile::DoSoftGroundResistance(uint &) 0x6A4AF0
void CAutomobile::DoSoftGroundResistance(unsigned int& arg0)
{
    ((void(__thiscall*)(CAutomobile*, unsigned int&))0x6A4AF0)(this, arg0);
}

void CAutomobile::ProcessCarWheelPair(int leftWheel, int rightWheel, float steerAngle, CVector* contactSpeeds, CVector* contactPoints, float traction, float acceleration, float brake, bool bFront)
{
    bool driveWheels = false;
    if (bFront && gHandlingDataMgr.HasFrontWheelDrive(m_pHandlingData->m_nVehicleId))
        driveWheels = true;
    else if (!bFront && gHandlingDataMgr.HasRearWheelDrive(m_pHandlingData->m_nVehicleId))
        driveWheels = true;
    float suspensionBias = 2.0f * m_pHandlingData->m_fSuspensionBiasBetweenFrontAndRear;
    if (!bFront)
        suspensionBias = 2.0f - suspensionBias;
    if (!bFront)
    {
        if (!vehicleFlags.bIsHandbrakeOn || handlingFlags.bHbRearwheelSteer)
        {
            if (driveWheels && m_doingBurnout)
            {
                brake = 0.0f;
                traction = 0.0f;
                CVector point = std::min(1.0f, 3000.0f / m_fTurnMass) * -0.002f * m_fTurnMass * m_fSteerAngle * GetRight();
                ApplyTurnForce(contactPoints[leftWheel], point);
            }
            else if (!handlingFlags.bNosInst && gHandlingDataMgr.HasRearWheelDrive(m_pHandlingData->m_nVehicleId))
            {
                traction *= m_fTireTemperature;
            }
        }
        else
        {
            brake = 20000.0f;
        }
    }
    if (m_aWheelTimer[leftWheel] > 0.0f || m_aWheelTimer[rightWheel] > 0.0f)
    {
        CVector wheelFwd;
        CVector wheelRight;
        CVector tmp;

        float sinSteerAngle = 0.0f;
        float cosSteerAngle = 0.0f;
        bool canSteer = steerAngle > -100.0f;
        if (canSteer) {
            sinSteerAngle = sin(steerAngle);
            cosSteerAngle = cos(steerAngle);
        }

        bool neutralHandling = m_nStatus != STATUS_PLAYER && m_nStatus != STATUS_HELI && handlingFlags.bNpcNeutralHandl;
        float brakeBias = 0.0f;
        float tractionBias = 0.0f;
        if (bFront)
        {
            brakeBias = neutralHandling ? 1.0f : 2.0f * m_pHandlingData->m_fBrakeBias;
            tractionBias = neutralHandling ? 1.0f : 2.0f * m_pHandlingData->m_fTractionBias;
        }
        else
        {
            brakeBias = neutralHandling ? 1.0f : 2.0f - (2.0f * m_pHandlingData->m_fBrakeBias);
            tractionBias = neutralHandling ? 1.0f : 2.0f - (2.0f * m_pHandlingData->m_fTractionBias);
        }
        if (m_aWheelTimer[leftWheel] > 0.0f)
        {
            float thrust = driveWheels ? acceleration : 0.0f;

            wheelFwd = GetForward();
            wheelFwd -= DotProduct(wheelFwd, m_wheelColPoint[leftWheel].m_vecNormal) * m_wheelColPoint[leftWheel].m_vecNormal;
            wheelFwd.Normalise();
            wheelRight = CrossProduct(wheelFwd, m_wheelColPoint[leftWheel].m_vecNormal);
            wheelRight.Normalise();
            if (canSteer && m_nModelIndex != MODEL_HYDRA)
            {
                CVector tmp = cosSteerAngle * wheelFwd - sinSteerAngle * wheelRight;
                wheelRight = sinSteerAngle * wheelFwd + cosSteerAngle * wheelRight;
                wheelFwd = tmp;
            }
            m_wheelColPoint[leftWheel].m_nSurfaceTypeA = SURFACE_WHEELBASE;
            float adhesion = g_surfaceInfos->GetAdhesiveLimit(&m_wheelColPoint[leftWheel]) * traction;
            if (m_nStatus == STATUS_PLAYER)
            {
                adhesion *= g_surfaceInfos->GetWetMultiplier(m_wheelColPoint[leftWheel].m_nSurfaceTypeB);
                adhesion *= std::min(suspensionBias * m_pHandlingData->m_fSuspensionForceLevel * 4.0f * (1.0f - m_fWheelsSuspensionCompression[leftWheel]), 2.0f);
                if (handlingFlags.bOffroadAbility2 && g_surfaceInfos->GetAdhesionGroup(m_wheelColPoint[leftWheel].m_nSurfaceTypeB) > ADHESION_GROUP_ROAD)
                {
                    adhesion *= 1.4f;
                }
                else if (handlingFlags.bOffroadAbility)
                {
                    if (g_surfaceInfos->GetAdhesionGroup(m_wheelColPoint[leftWheel].m_nSurfaceTypeB) > ADHESION_GROUP_ROAD)
                        adhesion *= 1.15f;
                }
            }
            tWheelState wheelState = m_aWheelState[leftWheel];
            if (m_damageManager.GetWheelStatus(leftWheel) == WHEEL_STATUS_BURST) {
                CVehicle::ProcessWheel(wheelFwd, wheelRight, contactSpeeds[leftWheel], contactPoints[leftWheel], m_nNumContactWheels,
                    thrust,
                    brake * brakeBias,
                    adhesion * m_damageManager.m_fWheelDamageEffect * tractionBias,
                    leftWheel, &m_wheelRotationUnused[leftWheel], &wheelState, WHEEL_STATUS_BURST);
            }
            else {
                CVehicle::ProcessWheel(wheelFwd, wheelRight, contactSpeeds[leftWheel], contactPoints[leftWheel], m_nNumContactWheels,
                    thrust,
                    brake * brakeBias,
                    adhesion * tractionBias,
                    leftWheel, &m_wheelRotationUnused[leftWheel], &wheelState, WHEEL_STATUS_OK);
            }
            if (driveWheels && m_fGasPedal < 0.0f && wheelState == WHEEL_STATE_SPINNING)
                m_aWheelState[leftWheel] = WHEEL_STATE_NORMAL;
            else
                m_aWheelState[leftWheel] = wheelState;
        }
        if (m_aWheelTimer[rightWheel] > 0.0f)
        {
            float thrust = driveWheels ? acceleration : 0.0f;
            wheelFwd = GetForward();
            wheelFwd -= DotProduct(wheelFwd, m_wheelColPoint[rightWheel].m_vecNormal) * m_wheelColPoint[rightWheel].m_vecNormal;
            wheelFwd.Normalise();
            wheelRight = CrossProduct(wheelFwd, m_wheelColPoint[rightWheel].m_vecNormal);
            wheelRight.Normalise();
            if (canSteer)
            {
                CVector tmp = cosSteerAngle * wheelFwd - sinSteerAngle * wheelRight;
                wheelRight = sinSteerAngle * wheelFwd + cosSteerAngle * wheelRight;
                wheelFwd = tmp;
            }
            m_wheelColPoint[rightWheel].m_nSurfaceTypeA = SURFACE_WHEELBASE;
            float adhesion = g_surfaceInfos->GetAdhesiveLimit(&m_wheelColPoint[rightWheel]) * traction;
            if (m_nStatus == STATUS_PLAYER)
            {
                adhesion *= g_surfaceInfos->GetWetMultiplier(m_wheelColPoint[rightWheel].m_nSurfaceTypeB);
                adhesion *= std::min(suspensionBias * m_pHandlingData->m_fSuspensionForceLevel * 4.0f * (1.0f - m_fWheelsSuspensionCompression[rightWheel]), 2.0f);
                if (handlingFlags.bOffroadAbility2 && g_surfaceInfos->GetAdhesionGroup(m_wheelColPoint[rightWheel].m_nSurfaceTypeB) > ADHESION_GROUP_ROAD)
                {
                    adhesion *= 1.4f;
                }
                else if (handlingFlags.bOffroadAbility)
                {
                    if (g_surfaceInfos->GetAdhesionGroup(m_wheelColPoint[rightWheel].m_nSurfaceTypeB) > ADHESION_GROUP_ROAD)
                        adhesion *= 1.15f;
                }
            }
            tWheelState wheelState = m_aWheelState[rightWheel];
            if (m_damageManager.GetWheelStatus(rightWheel) == WHEEL_STATUS_BURST) {
                CVehicle::ProcessWheel(wheelFwd, wheelRight, contactSpeeds[rightWheel], contactPoints[rightWheel], m_nNumContactWheels,
                    thrust,
                    brake * brakeBias,
                    adhesion * m_damageManager.m_fWheelDamageEffect * tractionBias,
                    rightWheel, &m_wheelRotationUnused[rightWheel], &wheelState, WHEEL_STATUS_BURST);
            }
            else {
                CVehicle::ProcessWheel(wheelFwd, wheelRight, contactSpeeds[rightWheel], contactPoints[rightWheel], m_nNumContactWheels,
                    thrust,
                    brake * brakeBias,
                    adhesion * tractionBias,
                    rightWheel, &m_wheelRotationUnused[rightWheel], &wheelState, WHEEL_STATUS_OK);
            }
            if (driveWheels && m_fGasPedal < 0.0f && wheelState == WHEEL_STATE_SPINNING)
                m_aWheelState[rightWheel] = WHEEL_STATE_NORMAL;
            else
                m_aWheelState[rightWheel] = wheelState;
        }
    }
    if (!bFront && !handlingFlags.bNosInst) {
        if (m_doingBurnout && driveWheels &&
            (m_aWheelState[CARWHEEL_REAR_LEFT] == WHEEL_STATE_SPINNING ||
            m_aWheelState[CARWHEEL_REAR_RIGHT] == WHEEL_STATE_SPINNING))
        {
            m_fTireTemperature += CTimer::ms_fTimeStep * 0.001f;
            m_fTireTemperature = std::min(m_fTireTemperature, 3.0f);
        }
        else if (m_fTireTemperature > 1.0f) {
            m_fTireTemperature = std::powf(0.995f, CTimer::ms_fTimeStep) * (m_fTireTemperature - 1.0f) + 1.0f;
        }
    }
    if (!IsRealHeli())
    {
        if (m_aWheelTimer[leftWheel] <= 0.0f)
        {
            if (driveWheels && acceleration != 0.0f)
            {
                if (acceleration > 0.0f)
                {
                    if (m_wheelSpeed[leftWheel] < 1.0f)
                        m_wheelSpeed[leftWheel] -= 0.1f;
                }
                else
                {
                    if (m_wheelSpeed[leftWheel] > -1.0f)
                        m_wheelSpeed[leftWheel] += 0.05f;
                }
            }
            else
            {
                m_wheelSpeed[leftWheel] *= 0.95f;
            }
            m_wheelRotation[leftWheel] += CTimer::ms_fTimeStep * m_wheelSpeed[leftWheel];
        }
        if (m_aWheelTimer[rightWheel] <= 0.0f)
        {
            if (driveWheels && acceleration != 0.0f)
            {
                if (acceleration > 0.0f)
                {
                    if (m_wheelSpeed[rightWheel] < 1.0f)
                        m_wheelSpeed[rightWheel] -= 0.1f;
                }
                else
                {
                    if (m_wheelSpeed[rightWheel] > -1.0f)
                        m_wheelSpeed[rightWheel] += 0.05f;
                }
            }
            else
            {
                m_wheelSpeed[rightWheel] *= 0.95f;
            }
            m_wheelRotation[rightWheel] += CTimer::ms_fTimeStep * m_wheelSpeed[rightWheel];
        }
    }
}

// Converted from thiscall float CAutomobile::GetCarRoll(void) 0x6A6010
float CAutomobile::GetCarRoll()
{
    return ((float(__thiscall*)(CAutomobile*))0x6A6010)(this);
}

// Converted from thiscall float CAutomobile::GetCarPitch(void) 0x6A6050
float CAutomobile::GetCarPitch()
{
    return ((float(__thiscall*)(CAutomobile*))0x6A6050)(this);
}

// Converted from thiscall bool CAutomobile::IsInAir(void) 0x6A6140
bool CAutomobile::IsInAir()
{
    return ((bool(__thiscall*)(CAutomobile*))0x6A6140)(this);
}

// Converted from thiscall void CAutomobile::dmgDrawCarCollidingParticles(CVector const& position, float force, eWeaponType weapon) 0x6A6DC0
void CAutomobile::dmgDrawCarCollidingParticles(CVector const& position, float force, eWeaponType weapon)
{
    ((void(__thiscall*)(CAutomobile*, CVector const&, float, eWeaponType))0x6A6DC0)(this, position, force, weapon);
}

void CAutomobile::ProcessCarOnFireAndExplode(bool bExplodeImmediately)
{
    ((void(__thiscall*)(CAutomobile*, unsigned char))0x6A7090)(this, bExplodeImmediately);
}

// Converted from thiscall CObject* CAutomobile::SpawnFlyingComponent(int nodeIndex, uint collisionType) 0x6A8580
CObject* CAutomobile::SpawnFlyingComponent(int nodeIndex, unsigned int collisionType)
{
    return ((CObject * (__thiscall*)(CAutomobile*, int, unsigned int))0x6A8580)(this, nodeIndex, collisionType);
}

// Converted from thiscall void CAutomobile::ProcessBuoyancy(void) 0x6A8C00
void CAutomobile::ProcessBuoyancy()
{
    /* Unused code in sa function
    CTimeCycle::GetAmbientRed_Obj();
    CTimeCycle::GetAmbientGreen_Obj();
    CTimeCycle::GetAmbientBlue_Obj();
    rand();
    */

    CVector vecBuoyancyTurnPoint;
    CVector vecBuoyancyForce;
    if (!mod_Buoyancy.ProcessBuoyancy(this, m_fBuoyancyConstant, &vecBuoyancyTurnPoint, &vecBuoyancyForce)) {
        vehicleFlags.bIsDrowning = false;
        physicalFlags.bSubmergedInWater = false;
        physicalFlags.bTouchingWater = false;

        m_fBuoyancyConstant = m_pHandlingData->m_fBuoyancyConstant;
        for (int32_t i = 0; i < 4; ++i) {
            auto& pColPoint = m_wheelColPoint[i];
            if (m_fWheelsSuspensionCompression[i] < 1.0F && g_surfaceInfos->IsWater(pColPoint.m_nSurfaceTypeB)) {
                auto vecWaterImpactVelocity = (pColPoint.m_vecPoint + GetUp() * 0.3F) - GetPosition();
                CVector vecSpeed = GetSpeed(vecWaterImpactVelocity);
            }
        }
        return; // The loop above is pretty much an overcomplicated NOP.
    }

    if (IsPlane() && m_vecMoveSpeed.z < -1.0F) {
        BlowUpCar(this, false);
    }

    physicalFlags.bTouchingWater = true;
    auto fTimeStep = std::max(0.01F, CTimer::ms_fTimeStep);
    auto fUsedMass = m_fMass / 125.0F;
    auto fBuoyancyForceZ = vecBuoyancyForce.z / (fTimeStep * fUsedMass);

    if (fUsedMass > m_fBuoyancyConstant)
        fBuoyancyForceZ *= 1.05F * fUsedMass / m_fBuoyancyConstant;

    if (physicalFlags.bMakeMassTwiceAsBig)
        fBuoyancyForceZ *= 1.5F;

    auto fBuoyancyForceMult = std::max(0.5F, 1.0F - fBuoyancyForceZ / 20.0F);
    auto fSpeedMult = pow(fBuoyancyForceMult, CTimer::ms_fTimeStep);

    if (m_nModelIndex != eModelID::MODEL_VORTEX
        || GetUp().z <= 0.3F
        || vehicleFlags.bIsDrowning) {

        m_vecMoveSpeed *= fSpeedMult;
        m_vecTurnSpeed *= fSpeedMult;
    }

    bool bHeliRotorKilled = false;
    if (m_pHandlingData->m_bIsHeli && m_fHeliRotorSpeed > 0.15F) {
        bool bForceKillRotor = false;
        if (m_nModelIndex != eModelID::MODEL_SEASPAR && m_nModelIndex != eModelID::MODEL_LEVIATHN) {
            auto fUsedForce = std::max(1.0F, fBuoyancyForceZ * 8.0F);
            auto vecMoveForceHeli = (vecBuoyancyForce * -2.0F) / fUsedForce;
            ApplyMoveForce(vecMoveForceHeli);
            m_vecTurnSpeed *= fSpeedMult;
            if (fBuoyancyForceZ <= 0.9F)
                return;

            bForceKillRotor = true;
        }

        if (fBuoyancyForceZ > 3.0F || bForceKillRotor) {
            m_fHeliRotorSpeed = 0.0F;
            bHeliRotorKilled = true;
        }
    }

    physicalFlags.bTouchingWater = true;
    ApplyMoveForce(vecBuoyancyForce);
    ApplyTurnForce(vecBuoyancyForce, vecBuoyancyTurnPoint);

    if ((m_nModelIndex == eModelID::MODEL_SEASPAR || m_nModelIndex == eModelID::MODEL_LEVIATHN)
        && fBuoyancyForceZ < 3.0F
        && (GetUp().z > -0.5F || fBuoyancyForceZ < 0.6F)) {

        vehicleFlags.bIsDrowning = false;
        physicalFlags.bSubmergedInWater = false;
        return;
    }

    if ((CCheat::m_aCheatsActive[eCheats::CHEAT_CARS_ON_WATER] || m_nModelIndex == eModelID::MODEL_VORTEX)
        && m_nStatus == eEntityStatus::STATUS_PLAYER
        && GetUp().z > 0.3F) {

        if (!vehicleFlags.bIsDrowning) {
            vehicleFlags.bIsDrowning = false;
            physicalFlags.bSubmergedInWater = false;
            return;
        }
    }

    if (bHeliRotorKilled || fBuoyancyForceZ >= 1.0F
        || (fBuoyancyForceZ > 0.6F && IsAnyWheelNotMakingContactWithGround())) {

        vehicleFlags.bIsDrowning = true;
        physicalFlags.bSubmergedInWater = true;

        m_vecMoveSpeed.z = std::max(-0.1F, m_vecMoveSpeed.z);

        if (m_fMass * 8.0F / 1250.0F < m_fBuoyancyConstant)
            m_fBuoyancyConstant -= (m_fMass * 0.01F / 1250.0F);

        if (m_fBuoyancyConstant < m_fMass / 125.0F)
            vehicleFlags.bEngineOn = false;

        auto pDriver = static_cast<CPed*>(m_pDriver);
        ProcessPedInVehicleBuoyancy(pDriver, true);

        for (int iPassengerInd = 0; iPassengerInd < m_nMaxPassengers; ++iPassengerInd) {
            auto pCurPassenger = m_apPassengers[iPassengerInd];
            ProcessPedInVehicleBuoyancy(pCurPassenger, false);
        }
    }
    else {
        vehicleFlags.bIsDrowning = false;
        physicalFlags.bSubmergedInWater = false;
    }
}

inline void CAutomobile::ProcessPedInVehicleBuoyancy(CPed* pPed, bool bIsDriver)
{
    if (!pPed)
        return;

    pPed->physicalFlags.bTouchingWater = true;
    if (!pPed->IsPlayer() && npcFlags.bIgnoreWater)
        return;

    if (!IsSubclassQuad() || IsAnyWheelMakingContactWithGround()) {
        if (pPed->IsPlayer())
            static_cast<CPlayerPed*>(pPed)->HandlePlayerBreath(true, 1.0F);
        else {
            auto pedDamageResponseCalc = CPedDamageResponseCalculator(this, CTimer::ms_fTimeStep, eWeaponType::WEAPON_DROWNING, ePedPieceTypes::PED_PIECE_TORSO, false);
            auto damageEvent = CEventDamage(this, CTimer::m_snTimeInMilliseconds, eWeaponType::WEAPON_DROWNING, ePedPieceTypes::PED_PIECE_TORSO, 0, false, true);
            if (damageEvent.AffectsPed(pPed))
                pedDamageResponseCalc.ComputeDamageResponse(pPed, &damageEvent.m_damageResponse, true);
            else
                damageEvent.m_damageResponse.m_bDamageCalculated = true;

            pPed->GetEventGroup().Add(&damageEvent, false);
        }
    }
    else {
        auto vecCollisionImpact = m_vecMoveSpeed * -1.0F;
        vecCollisionImpact.Normalise();
        auto fDamageIntensity = m_vecMoveSpeed.Magnitude() * m_fMass;

        auto knockOffBikeEvent = CEventKnockOffBike(this, &m_vecMoveSpeed, &vecCollisionImpact, fDamageIntensity,
            0.0F, eKnockOffType::KNOCK_OFF_TYPE_FALL, 0, 0, nullptr, false, false);

        pPed->GetEventGroup().Add(&knockOffBikeEvent, false);

        if (pPed->IsPlayer())
            static_cast<CPlayerPed*>(pPed)->HandlePlayerBreath(true, 1.0F);

        if (bIsDriver)
            vehicleFlags.bEngineOn = false;
    }
}

// Converted from thiscall void CAutomobile::ProcessHarvester(void) 0x6A9680
void CAutomobile::ProcessHarvester()
{
    ((void(__thiscall*)(CAutomobile*))0x6A9680)(this);
}

// Converted from thiscall void CAutomobile::ProcessSwingingDoor(int nodeIndex, eDoors door) 0x6A9D70
void CAutomobile::ProcessSwingingDoor(int nodeIndex, eDoors door)
{
    ((void(__thiscall*)(CAutomobile*, int, eDoors))0x6A9D70)(this, nodeIndex, door);
}

// Converted from thiscall CObject* CAutomobile::RemoveBonnetInPedCollision(void) 0x6AA200
CObject* CAutomobile::RemoveBonnetInPedCollision()
{
    return ((CObject * (__thiscall*)(CAutomobile*))0x6AA200)(this);
}

// Converted from thiscall void CAutomobile::UpdateWheelMatrix(int nodeIndex, int flags) 0x6AA290
void CAutomobile::UpdateWheelMatrix(int nodeIndex, int flags)
{
    ((void(__thiscall*)(CAutomobile*, int, int))0x6AA290)(this, nodeIndex, flags);
}

// Converted from thiscall void CAutomobile::PopDoor(int nodeIndex, eDoors door, bool showVisualEffect) 0x6ADEF0
void CAutomobile::PopDoor(int nodeIndex, eDoors door, bool showVisualEffect)
{
    ((void(__thiscall*)(CAutomobile*, int, eDoors, bool))0x6ADEF0)(this, nodeIndex, door, showVisualEffect);
}

// Converted from thiscall void CAutomobile::PopPanel(int nodeIndex, ePanels panel, bool showVisualEffect) 0x6ADF80
void CAutomobile::PopPanel(int nodeIndex, ePanels panel, bool showVisualEffect)
{
    ((void(__thiscall*)(CAutomobile*, int, ePanels, bool))0x6ADF80)(this, nodeIndex, panel, showVisualEffect);
}

// Converted from thiscall void CAutomobile::ScanForCrimes(void) 0x6ADFF0
void CAutomobile::ScanForCrimes()
{
    ((void(__thiscall*)(CAutomobile*))0x6ADFF0)(this);
}

// Converted from thiscall void CAutomobile::TankControl(void) 0x6AE850
void CAutomobile::TankControl()
{
    ((void(__thiscall*)(CAutomobile*))0x6AE850)(this);
}

// Converted from thiscall void CAutomobile::BlowUpCarsInPath(void) 0x6AF110
void CAutomobile::BlowUpCarsInPath()
{
    ((void(__thiscall*)(CAutomobile*))0x6AF110)(this);
}

// Converted from thiscall void CAutomobile::PlaceOnRoadProperly(void) 0x6AF420
void CAutomobile::PlaceOnRoadProperly()
{
    auto pColModel = CEntity::GetColModel();
    auto fStartY = pColModel->m_pColData->m_pLines[0].m_vecStart.y;
    auto fEndY = -pColModel->m_pColData->m_pLines[3].m_vecStart.y;

    const auto& vecPos = GetPosition();

    auto vecRearCheck = vecPos - GetForward() * fEndY;
    vecRearCheck.z = vecPos.z;

    auto vecFrontCheck = vecPos + GetForward() * fStartY;
    vecFrontCheck.z = vecPos.z;

    bool bColFoundFront = false;
    CColPoint colPoint;
    CEntity* colEntity;
    float fColZ;
    if (CWorld::ProcessVerticalLine(vecFrontCheck, vecFrontCheck.z + 5.0F, colPoint, colEntity, true, false, false, false, false, false, nullptr)) {
        m_bTunnel = colEntity->m_bTunnel;
        m_bTunnelTransition = colEntity->m_bTunnelTransition;

        fColZ = colPoint.m_vecPoint.z;
        m_pEntityWeAreOn = colEntity;
        bColFoundFront = true;
    }
    if (CWorld::ProcessVerticalLine(vecFrontCheck, vecFrontCheck.z - 5.0F, colPoint, colEntity, true, false, false, false, false, false, nullptr)) {
        if (!bColFoundFront || fabs(vecFrontCheck.z - colPoint.m_vecPoint.z) < fabs(vecFrontCheck.z - fColZ)) {
            m_bTunnel = colEntity->m_bTunnel;
            m_bTunnelTransition = colEntity->m_bTunnelTransition;

            fColZ = colPoint.m_vecPoint.z;
            m_pEntityWeAreOn = colEntity;

            m_FrontCollPoly.m_nLighting = colPoint.m_nLightingB;
            vecFrontCheck.z = fColZ;
        }
    }
    else if (bColFoundFront) {
        m_FrontCollPoly.m_nLighting = colPoint.m_nLightingB;
        vecFrontCheck.z = fColZ;
    }

    bool bColFoundRear = false;
    colEntity = nullptr;
    if (CWorld::ProcessVerticalLine(vecRearCheck, vecRearCheck.z + 5.0F, colPoint, colEntity, true, false, false, false, false, false, nullptr)) {
        m_bTunnel = colEntity->m_bTunnel;
        m_bTunnelTransition = colEntity->m_bTunnelTransition;

        fColZ = colPoint.m_vecPoint.z;
        m_pEntityWeAreOn = colEntity;
        bColFoundRear = true;
    }
    if (CWorld::ProcessVerticalLine(vecRearCheck, vecRearCheck.z - 5.0F, colPoint, colEntity, true, false, false, false, false, false, nullptr)) {
        if (!bColFoundRear || fabs(vecRearCheck.z - colPoint.m_vecPoint.z) < fabs(vecRearCheck.z - fColZ)) {
            m_bTunnel = colEntity->m_bTunnel;
            m_bTunnelTransition = colEntity->m_bTunnelTransition;

            fColZ = colPoint.m_vecPoint.z;
            m_pEntityWeAreOn = colEntity;

            m_RearCollPoly.m_nLighting = colPoint.m_nLightingB;
            vecRearCheck.z = fColZ;
        }
    }
    else if (bColFoundRear) {
        m_RearCollPoly.m_nLighting = colPoint.m_nLightingB;
        vecRearCheck.z = fColZ;
    }

    //FIXME: Not originally in this function, we can't spawn skimmer from debug menu cause those 2 values aren't initialized,
    //       resulting in garbage results further down, either we have a bug somewhere, or it's like that in original SA too
    if (m_nModelIndex == eModelID::MODEL_SKIMMER) {
        m_fFrontHeightAboveRoad = 0.0F;
        m_fRearHeightAboveRoad = 0.0F;
        vecFrontCheck.z += 4.0F;
        vecRearCheck.z += 4.0F;
    }
    else {
        auto fHeightAboveRoad = GetHeightAboveRoad();
        vecFrontCheck.z += fHeightAboveRoad;
        vecRearCheck.z += m_fRearHeightAboveRoad;
    }

    auto fLength = fEndY + fStartY;
    GetRight().Set((vecFrontCheck.y - vecRearCheck.y) / fLength, -((vecFrontCheck.x - vecRearCheck.x) / fLength), 0.0F);

    auto vecDiff = vecFrontCheck - vecRearCheck;
    vecDiff.Normalise();
    GetForward() = vecDiff;

    auto vecCross = CrossProduct(GetRight(), GetForward());
    GetUp() = vecCross;

    CVector vecNewPos = (vecFrontCheck * fEndY + vecRearCheck * fStartY) / fLength;
    SetPosn(vecNewPos);

    if (IsPlane())
        static_cast<CPlane*>(this)->m_planeCreationHeading = CGeneral::GetATanOfXY(GetForward().x, GetForward().y);
}

// Converted from thiscall void CAutomobile::PopBoot(void) 0x6AF910
void CAutomobile::PopBoot()
{
    ((void(__thiscall*)(CAutomobile*))0x6AF910)(this);
}

// Converted from thiscall void CAutomobile::CloseBoot(void) 0x6AFA20
void CAutomobile::CloseBoot()
{
    ((void(__thiscall*)(CAutomobile*))0x6AFA20)(this);
}

// Converted from thiscall void CAutomobile::DoHeliDustEffect(float, float) 0x6B0690
void CAutomobile::DoHeliDustEffect(float arg0, float arg1)
{
    ((void(__thiscall*)(CAutomobile*, float, float))0x6B0690)(this, arg0, arg1);
}

// Converted from thiscall void CAutomobile::SetBumperDamage(ePanels panel, bool withoutVisualEffect) 0x6B1350
void CAutomobile::SetBumperDamage(ePanels panel, bool withoutVisualEffect)
{
    ((void(__thiscall*)(CAutomobile*, ePanels, bool))0x6B1350)(this, panel, withoutVisualEffect);
}

// Converted from thiscall void CAutomobile::SetPanelDamage(ePanels panel, bool createWindowGlass) 0x6B1480
void CAutomobile::SetPanelDamage(ePanels panel, bool createWindowGlass)
{
    ((void(__thiscall*)(CAutomobile*, ePanels, bool))0x6B1480)(this, panel, createWindowGlass);
}

// Converted from thiscall void CAutomobile::SetDoorDamage(eDoors door, bool withoutVisualEffect) 0x6B1600
void CAutomobile::SetDoorDamage(eDoors door, bool withoutVisualEffect)
{
    ((void(__thiscall*)(CAutomobile*, eDoors, bool))0x6B1600)(this, door, withoutVisualEffect);
}

// Converted from thiscall bool CAutomobile::RcbanditCheck1CarWheels(CPtrList &ptrlist) 0x6B3F70
bool CAutomobile::RcbanditCheck1CarWheels(CPtrList& ptrlist)
{
    return ((bool(__thiscall*)(CAutomobile*, CPtrList&))0x6B3F70)(this, ptrlist);
}

// Converted from thiscall bool CAutomobile::RcbanditCheckHitWheels(void) 0x6B45E0
bool CAutomobile::RcbanditCheckHitWheels()
{
    return ((bool(__thiscall*)(CAutomobile*))0x6B45E0)(this);
}

// Converted from thiscall void CAutomobile::FireTruckControl(float) 0x729B60
void CAutomobile::FireTruckControl(float arg0)
{
    ((void(__thiscall*)(CAutomobile*, float))0x729B60)(this, arg0);
}

// Converted from thiscall bool CAutomobile::HasCarStoppedBecauseOfLight(void) 0x44D520
bool CAutomobile::HasCarStoppedBecauseOfLight()
{
    return ((bool(__thiscall*)(CAutomobile*))0x44D520)(this);
}

// Converted from cdecl RwObject* GetCurrentAtomicObjectCB(RwObject *object, void *data) 0x6A0750
RwObject* GetCurrentAtomicObjectCB(RwObject* object, void* data)
{
    if (RpAtomicGetFlags(object) & rpATOMICRENDER)
        *reinterpret_cast<RpAtomic**>(data) = reinterpret_cast<RpAtomic*>(object);

    return object;
}
