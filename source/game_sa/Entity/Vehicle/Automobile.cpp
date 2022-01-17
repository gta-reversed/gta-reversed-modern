/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "Automobile.h"

#include "WaterCannons.h"
#include "Buoyancy.h"

bool& CAutomobile::m_sAllTaxiLights = *(bool*)0xC1BFD0;
CVector& CAutomobile::vecHunterGunPos = *(CVector*)0x8D3394;
CMatrix* CAutomobile::matW2B = (CMatrix*)0xC1C220;
CColPoint* aAutomobileColPoints = (CColPoint*)0xC1BFF8;

const CVector PACKER_COL_PIVOT = CVector(0.0f, 0.0f, 2.0f);
const float CAR_BALANCE_MULT = 0.08f;

static const CVector TANK_SHOT_DOOM_POS(0.0f, -1.394f, 2.296f);
static const CVector TANK_SHOT_DOOM_DEFAULT_TARGET(0.0f, 2.95f, 2.97f);
static const CVector TANK_SHOT_DOOM_DISTANCE_TO_DEFAULT_TARGET = TANK_SHOT_DOOM_DEFAULT_TARGET - TANK_SHOT_DOOM_POS;

static const uint32 TIGER_GUNFIRE_RATE = 60;
static const CVector TIGER_GUN_POS(0.0f, 0.5f, 0.2f); // 0xC1C208

void CAutomobile::InjectHooks()
{
    ReversibleHooks::Install("CAutomobile", "ProcessControl", 0x6B1880, &CAutomobile::ProcessControl_Reversed);
    ReversibleHooks::Install("CAutomobile", "AddMovingCollisionSpeed", 0x6A1ED0, &CAutomobile::AddMovingCollisionSpeed_Reversed);
    ReversibleHooks::Install("CAutomobile", "ProcessAI", 0x6B4800, &CAutomobile::ProcessAI_Reversed);
    ReversibleHooks::Install("CAutomobile", "ResetSuspension", 0x6A2AE0, &CAutomobile::ResetSuspension_Reversed);
    ReversibleHooks::Install("CAutomobile", "ProcessFlyingCarStuff", 0x6A8500, &CAutomobile::ProcessFlyingCarStuff_Reversed);
    ReversibleHooks::Install("CAutomobile", "DoHoverSuspensionRatios", 0x6A45C0, &CAutomobile::DoHoverSuspensionRatios_Reversed);
    ReversibleHooks::Install("CAutomobile", "ProcessSuspension", 0x6AFB10, &CAutomobile::ProcessSuspension_Reversed);
    ReversibleHooks::Install("CAutomobile", "SetupModelNodes", 0x6A0770, &CAutomobile::SetupModelNodes);
    ReversibleHooks::Install("CAutomobile", "HydraulicControl", 0x6A07A0, &CAutomobile::HydraulicControl);
    ReversibleHooks::Install("CAutomobile", "UpdateMovingCollision", 0x6A1460, &CAutomobile::UpdateMovingCollision);
    ReversibleHooks::Install("CAutomobile", "ProcessBuoyancy", 0x6A8C00, &CAutomobile::ProcessBuoyancy);
    ReversibleHooks::Install("CAutomobile", "ProcessHarvester", 0x6A9680, &CAutomobile::ProcessHarvester);
    ReversibleHooks::Install("CAutomobile", "TankControl", 0x6AE850, &CAutomobile::TankControl);
    ReversibleHooks::Install("CAutomobile", "DoSoftGroundResistance", 0x6A4AF0, &CAutomobile::DoSoftGroundResistance);
    ReversibleHooks::Install("CAutomobile", "ProcessCarWheelPair", 0x6A4EC0, &CAutomobile::ProcessCarWheelPair);
    ReversibleHooks::Install("CAutomobile", "PlaceOnRoadProperly", 0x6AF420, &CAutomobile::PlaceOnRoadProperly);
    ReversibleHooks::Install("CAutomobile", "RcbanditCheck1CarWheels", 0x6B3F70, &CAutomobile::RcbanditCheck1CarWheels);
    ReversibleHooks::Install("CAutomobile", "RcbanditCheckHitWheels", 0x6B45E0, &CAutomobile::RcbanditCheckHitWheels);
    ReversibleHooks::Install("CAutomobile", "FireTruckControl", 0x729B60, &CAutomobile::FireTruckControl);
    ReversibleHooks::Install("CAutomobile", "SetHeliOrientation", 0x6A2450, &CAutomobile::SetHeliOrientation);
    ReversibleHooks::Install("CAutomobile", "ClearHeliOrientation", 0x6A2460, &CAutomobile::ClearHeliOrientation);
}

CAutomobile::CAutomobile(int32 modelIndex, eVehicleCreatedBy createdBy, bool setupSuspensionLines) : CVehicle(plugin::dummy) {
    plugin::CallMethod<0x6B0A90, CAutomobile*, int32, eVehicleCreatedBy, bool>(this, modelIndex, createdBy, setupSuspensionLines);
}

// 0x6B4410
bool CAutomobile::SetTowLink(CVehicle* targetVehicle, bool arg1) {
    return SetTowLink_Reversed(targetVehicle, arg1);
}

bool CAutomobile::SetTowLink_Reversed(CVehicle* targetVehicle, bool arg1) {
    return plugin::CallMethodAndReturn<bool, 0x6B4410, CAutomobile*, CVehicle*, bool>(this, targetVehicle, arg1);
}

void CAutomobile::ProcessControl()
{
    uint32 extraHandlingFlags = 0;
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
    bool extraHandlingWheelsTouchingSand = !!(extraHandlingFlags & EXTRA_HANDLING_WHEELS_TOUCHING_SAND);
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

        forceLimitRadius *= CTimer::GetTimeStep();
        torqueLimitRadius *= CTimer::GetTimeStep();
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
    for (int32 i = 0; i < 4; i++) {
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
    if (m_nStatus == STATUS_PLAYER && ModelIndices::HasWaterCannon(m_nModelIndex)) {
        FireTruckControl(nullptr);
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
        for (int32 i = 0; i < 2; i++) {
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
            auto skimmerHandling = gHandlingDataMgr.GetBoatPointer(static_cast<uint8>(skimmerModelInfo->m_nHandlingId));
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
                for (uint8 i = 0; i < m_nMaxPassengers; i++) {
                    CPed* passenger = m_apPassengers[i];
                    if (passenger && passenger->IsPlayer())
                        static_cast<CPlayerPed*>(passenger)->ResetPlayerBreath();

                }
            }
        }
        if (m_nModelIndex == MODEL_RCBARON)
            ProcessFlyingCarStuff();
        if (!npcFlags.bSoftSuspension) {
            for (int32 i = 0; i < 4; i++) {
                float wheelRadius = 1.0f - m_aSuspensionSpringLength[i] / m_aSuspensionLineLength[i];
                m_fWheelsSuspensionCompression[i] = (m_fWheelsSuspensionCompression[i] - wheelRadius) / (1.0f - wheelRadius);
            }
        }

        ProcessSuspension();

        CVector contactPoints[4];
        CVector contactSpeeds[4];

        for (int32 i = 0; i < 4; i++) {
            if (m_fWheelsSuspensionCompression[i] >= 1.0f) {
                CColLine& colLine = colData->m_pLines[i];
                CColDisk& colDisk = colData->m_pDisks[i];
                if (colData->bUsesDisks) {
                    CVector& point = contactPoints[i];
                    point = colDisk.m_vecStart;
                    point.z -= colDisk.m_fStartRadius;
                    point = Multiply3x3(GetMatrix(), contactPoints[i]);
                }
                else {
                    contactPoints[i] = Multiply3x3(GetMatrix(), colLine.m_vecEnd);
                }
            }
            else {
                m_wheelSkidmarkMuddy[i] = false;
                m_wheelSkidmarkType[i] = (eSkidMarkType)g_surfaceInfos->GetSkidmarkType(m_wheelColPoint[i].m_nSurfaceTypeB);
                if (m_wheelSkidmarkType[i] == SKIDMARK_MUDDY)
                    m_wheelSkidmarkMuddy[i] = true;
                contactPoints[i] = m_wheelColPoint[i].m_vecPoint - GetPosition();
            }
        }

        for (int32 i = 0; i < 4; i++) {
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
                    uint32 timeStep = CTimer::GetTimeStepInMS();
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

        float brake = m_pHandlingData->m_fBrakeDeceleration * m_fBreakPedal * CTimer::GetTimeStep();

        m_wheelsOnGrounPrev = m_nWheelsOnGround;
        m_nNumContactWheels = 0;
        m_nWheelsOnGround = 0;

        for (int32 i = 0; i < 4; i++) {
            if (m_fWheelsSuspensionCompression[i] >= 1.0f) {
                m_aWheelTimer[i] = std::max(m_aWheelTimer[i] - CTimer::GetTimeStep(), 0.0f);
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

        uint8 cheatType = CHEAT_HANDLING_NONE;
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
            if (CanUpdateHornCounter() && m_nHornTimeEndMs)
                m_nHornTimeEndMs--;
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
        && (CTimer::GetFrameCounter() & 7) == 5
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
    for (int32 i = 0; i < 4; i++) {
        float suspensionChange = m_fWheelsSuspensionCompressionPrev[i] - m_fWheelsSuspensionCompression[i];
        if (suspensionChange > 0.3f && !extraHandlingWheelsTouchingSand && speed > 0.04f) {
            //m_damageManager.GetWheelStatus(i); // return value is ignored
            if (suspensionChange > suspensionShake)
                suspensionShake = suspensionChange;
        }

        if (m_fWheelsSuspensionCompression[i] < 1.0f && m_nStatus == STATUS_PLAYER) {
            float roughness = g_surfaceInfos->GetRoughness(m_wheelColPoint[i].m_nSurfaceTypeB) * 0.1f;
            roughnessShake = std::max(roughnessShake, roughness);
        }
        uint32 handlingId = m_pHandlingData->m_nVehicleId;
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

    riseFallWheelSpinRate = pow(riseFallWheelSpinRate, CTimer::GetTimeStep());
    m_fWheelSpinForAudio *= riseFallWheelSpinRate;
    m_fWheelSpinForAudio += (1.0f - riseFallWheelSpinRate) * wheelSpinRate;

    if ((CTimer::GetTimeInMS() & 0x7FF) > 800) {
        if (roughnessShake >= 0.29f)
            suspensionShake = 0.0f;
        roughnessShake = 0.0f;
    }

    if (!extraHandlingWheelsTouchingSand
        && (suspensionShake > 0.0f || roughnessShake > 0.0f)
        && m_nStatus == STATUS_PLAYER)
    {
        float speed = m_vecMoveSpeed.SquaredMagnitude();
        if (speed > 0.01f) {
            speed = sqrt(speed);
            if (suspensionShake > 0.0f) {
                float frequency = (200.0f * suspensionShake * speed * 2000.0f) / m_fMass + 100.0f;
                frequency = std::min(frequency, 250.0f);
                int16 time = static_cast<int16>(CTimer::GetTimeStep() * 20000.0f / frequency);
                CPad::GetPad(0)->StartShake(time, static_cast<uint8>(frequency), 0);
            }
            else {
                float frequency = (200.0f * roughnessShake * speed * 2000.0f) / m_fMass + 40.0f;
                frequency = std::min(frequency, 150.0f);
                int16 time = static_cast<int16>(CTimer::GetTimeStep() * 5000.0f / frequency);
                CPad::GetPad(0)->StartShake(time, static_cast<uint8>(frequency), 0);
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
            float speedTimeStep = pow(0.985f, CTimer::GetTimeStep()) / (speedSquared * 5.0f + 1.0f);
            float speed = pow(speedTimeStep, CTimer::GetTimeStep());
            speed *= turnSpeedForward;
            speed -= turnSpeedForward;

            CVector force = speed * GetUp() * -1.0f * m_fTurnMass;
            CVector point = GetRight() + Multiply3x3(GetMatrix(), m_vecCentreOfMass);
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
                if ((m_wMiscComponentAngle == 0.0f || m_wMiscComponentAngle == m_wMiscComponentAnglePrev)
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
        ProcessHarvester();
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

CVector CAutomobile::AddMovingCollisionSpeed(CVector& point)
{
    if (m_nStatus != STATUS_PLAYER && m_nStatus != STATUS_PLANE) {
        if (m_nCreatedBy != MISSION_VEHICLE || !m_wMiscComponentAngle && !m_wMiscComponentAnglePrev)
            return CVector();
    }
    float colAngleMult = 0.0f;
    uint16 angleDiff = m_wMiscComponentAngle - m_wMiscComponentAnglePrev;
    if (angleDiff <= 100 && angleDiff >= -100) {
        CVector colPivot;
        RwFrame* carNodeMisc = nullptr;
        if (ModelIndices::IsDumper(m_nModelIndex)) {
            carNodeMisc = m_aCarNodes[CAR_MISC_C];
            colAngleMult = CMonsterTruck::DUMPER_COL_ANGLEMULT;
        }
        else if (ModelIndices::IsPacker(m_nModelIndex)) {
            colAngleMult = PACKER_COL_ANGLE_MULT;
            colPivot = PACKER_COL_PIVOT;
        }
        else if (ModelIndices::IsDozer(m_nModelIndex)) {
            carNodeMisc = m_aCarNodes[CAR_MISC_A];
            if (carNodeMisc)
                colAngleMult = DOZER_COL_ANGLE_MULT;
        }
        else if (ModelIndices::IsAndromada(m_nModelIndex)) {
            carNodeMisc = m_aCarNodes[CAR_MISC_E];
            if (carNodeMisc)
                colAngleMult = CPlane::ANDROM_COL_ANGLE_MULT;
        }
        else if (ModelIndices::IsForklift(m_nModelIndex)) {
            float rot = angleDiff / CTimer::GetTimeStep() * FORKLIFT_COL_ANGLE_MULT * 2.0f;
            return rot * GetUp();
        }

        if (colAngleMult != 0.0f) {
            if (carNodeMisc)
                colPivot = RwFrameGetMatrix(carNodeMisc)->pos;
            CVector rotation(angleDiff / CTimer::GetTimeStep() * colAngleMult, 0.0f, 0.0f);
            CVector pos = Multiply3x3(GetMatrix(), rotation);
            CVector pivotPos = Multiply3x3(GetMatrix(), colPivot);
            CVector distance = point - pivotPos;
            return CrossProduct(pos, distance);
        }
    }
    return CVector();
}

bool CAutomobile::ProcessAI(uint32& extraHandlingFlags)
{
    CColModel* colModel = CEntity::GetColModel();
    CCollisionData* colData = colModel->m_pColData;
    int8 recordingId = this->m_autoPilot.m_vehicleRecordingId;
    m_autoPilot.carCtrlFlags.bHonkAtCar = false;
    m_autoPilot.carCtrlFlags.bHonkAtPed = false;
    if (recordingId >= 0 && !CVehicleRecording::bUseCarAI[recordingId])
        return false;

    eCarMission carMission = m_autoPilot.m_nCarMission;
    CVehicle* playerVehicle = FindPlayerVehicle(-1, false);
    if (playerVehicle && playerVehicle != this && FindPlayerWanted()->m_nWantedLevel > 3
        && (carMission == MISSION_RAMPLAYER_FARAWAY
            || carMission == MISSION_BLOCKPLAYER_FARAWAY
            || carMission == MISSION_RAMPLAYER_CLOSE
            || carMission == MISSION_BLOCKPLAYER_CLOSE)
        && FindPlayerSpeed().Magnitude() > 0.3f)
    {
        extraHandlingFlags |= EXTRA_HANDLING_PERFECT;
        if (FindPlayerSpeed().Magnitude() > 0.4f && m_vecMoveSpeed.Magnitude() < 0.3f) {
            extraHandlingFlags |= EXTRA_HANDLING_NITROS;
        }
        else {
            CVector distance = GetPosition() - FindPlayerCoors(-1);
            if (distance.Magnitude() > 50.0f)
                extraHandlingFlags |= EXTRA_HANDLING_NITROS;
        }
    }
    else if (m_nModelIndex == MODEL_RCBANDIT && m_nStatus != STATUS_HELI) {
            extraHandlingFlags |= EXTRA_HANDLING_PERFECT;
    }

    bool extraPerfectHandling = !!(extraHandlingFlags & EXTRA_HANDLING_PERFECT);
    if (extraPerfectHandling || CCheat::m_aCheatsActive[CHEAT_PERFECT_HANDLING]) {
        m_vecCentreOfMass.z = m_aSuspensionSpringLength[CARWHEEL_FRONT_LEFT] * 0.3f - m_fFrontHeightAboveRoad;
    }
    else if (m_nStatus == STATUS_PHYSICS) {
        if (handlingFlags.bHydraulicGeom) {
            if (m_autoPilot.m_nCarMission != MISSION_NONE && colData && colData->m_nNumLines > 0) {
                m_vecCentreOfMass.y = (colData->m_pLines[0].m_vecStart.y + colData->m_pLines[1].m_vecStart.y)  * 0.5f;
                handlingFlags.bNpcNeutralHandl = true;
            }
            else {
                m_vecCentreOfMass = m_pHandlingData->m_vecCentreOfMass;
                handlingFlags.bNpcNeutralHandl = false;
            }
        }

        if (handlingFlags.bNpcAntiRoll) {
            m_pHandlingData->m_vecCentreOfMass.z += (colModel->m_boundBox.m_vecMin.z - m_pHandlingData->m_vecCentreOfMass.z) * 0.4f;
        }
    }
    else {
        m_vecCentreOfMass = m_pHandlingData->m_vecCentreOfMass;
    }

    if (m_nStatus != STATUS_ABANDONED && m_nStatus != STATUS_WRECKED
        && m_nStatus != STATUS_PLAYER && m_nStatus != STATUS_HELI
        && m_nStatus != STATUS_PLANE && vehicleFlags.bIsLawEnforcer)
    {
        ScanForCrimes();
    }

    if (vehicleFlags.bCanPark
        && !vehicleFlags.bParking
        && m_nCreatedBy != MISSION_VEHICLE
        && m_autoPilot.m_nCarMission == MISSION_CRUISE
        && ((CTimer::GetFrameCounter() + static_cast<uint8>(m_nRandomSeed)) & 0xF) == 0)
    {
        if (m_nModelIndex != MODEL_TAXI && m_nModelIndex != MODEL_CABBIE) {
            CVector target = GetPosition();
            target += GetRight() * 3.0f + GetForward() * 10.0f;
            CColPoint outColPoint;
            CEntity* outEntity = nullptr;
            if (!CWorld::ProcessLineOfSight(GetPosition(), target, outColPoint, outEntity, true, true, true,
                false, false, false, false, false)
                || outEntity == this)
            {
                CCarAI::GetCarToParkAtCoors(this, &target);
            }
        }
    }

    bool isRemotelyControlledByPlayer = false;
    const eEntityStatus status = static_cast<eEntityStatus>(m_nStatus);
    switch (status)
    {
    case STATUS_SIMPLE:
    {
        CCarAI::UpdateCarAI(this);
        CPhysical::ProcessControl();
        CCarCtrl::UpdateCarOnRails(this);
        m_nNumContactWheels = 4;
        m_wheelsOnGrounPrev = m_nWheelsOnGround;
        m_nWheelsOnGround = 4;
        float speed = m_autoPilot.m_speed * 0.02f;
        m_pHandlingData->GetTransmission().CalculateGearForSimpleCar(speed, m_nCurrentGear);
        float wheelRot = CVehicle::ProcessWheelRotation(WHEEL_STATE_NORMAL, GetForward(), m_vecMoveSpeed, 0.35f);
        for (int32 i = 0; i < 4; i++) {
            m_wheelRotation[i] += wheelRot;
        }
        PlayHornIfNecessary();
        if (m_nHornTimeEndMs)
            m_nHornTimeEndMs--;
        vehicleFlags.bAudioChangingGear = false;
        vehicleFlags.bVehicleColProcessed = false;
        return true;
    }
    case STATUS_PHYSICS:
    case STATUS_TRAILER:
    {
        CCarAI::UpdateCarAI(this);
        CCarCtrl::SteerAICarWithPhysics(this);
        CCarCtrl::ReconsiderRoute(this);
        PlayHornIfNecessary();
        if (vehicleFlags.bIsBeingCarJacked) {
            m_fGasPedal = 0.0f;
            m_fBreakPedal = 1.0f;
            vehicleFlags.bIsHandbrakeOn = true;
        }
        if (!IsAnyWheelTouchingSand())
            return false;
        if (m_nModelIndex == MODEL_RCBANDIT || m_nModelIndex == MODEL_SANDKING || m_nModelIndex == MODEL_BFINJECT)
            return false;
        npcFlags.bLostTraction = true;
        float force = m_fMass * CTimer::GetTimeStep() * 0.005f;
        if (CWeather::WetRoads > 0.0f)
            force *= 1.0f - CWeather::WetRoads;
        ApplyMoveForce(-force * m_vecMoveSpeed);
        return false;
    }
    case STATUS_ABANDONED:
        for (int32 i = 0; i < 4; i++) {
            if (m_pWheelCollisionEntity[i]) {
                vehicleFlags.bRestingOnPhysical = true;
                break;
            }
        }

        if (IsHeli() || IsPlane() && m_vecMoveSpeed.SquaredMagnitude() < 0.1f)
            m_fBreakPedal = 1.0f;
        if (vehicleFlags.bRestingOnPhysical) 
            m_fBreakPedal = 0.5f;
        else if (m_vecMoveSpeed.SquaredMagnitude() < 0.01f)
            m_fBreakPedal = 0.2f;
        else
            m_fBreakPedal = 0.0f;
        vehicleFlags.bIsHandbrakeOn = false;
        m_fSteerAngle = 0.0f;
        m_fGasPedal = 0.0f;
        if (CanUpdateHornCounter())
            m_nHornTimeEndMs = 0;
        if (!vehicleFlags.bIsBeingCarJacked)
            return false;
        vehicleFlags.bIsHandbrakeOn = true;
        m_fGasPedal = 0.0f;
        m_fBreakPedal = 1.0f;
        return false;
    case STATUS_WRECKED:
        m_fBreakPedal = 0.05f;
        vehicleFlags.bIsHandbrakeOn = true;
        m_fSteerAngle = 0.0f;
        m_fGasPedal = 0.0f;
        if (!CanUpdateHornCounter())
            return false;
        m_nHornTimeEndMs = 0;
        return false;
    case STATUS_HELI:
        if (CPad::GetPad(0)->CarGunJustDown() && !CVehicle::bDisableRemoteDetonation) {
            BlowUpCar(FindPlayerPed(), false);
            CRemote::TakeRemoteControlledCarFromPlayer(true);
        }

        if (m_nModelIndex == MODEL_RCBANDIT && !CVehicle::bDisableRemoteDetonationOnContact) {
            //FindPlayerCoors(); // return value is ignored
            if (RcbanditCheckHitWheels()|| physicalFlags.bSubmergedInWater) {
                CRemote::TakeRemoteControlledCarFromPlayer(true);
                BlowUpCar(FindPlayerPed(), false);
            }
        }
        if (CWorld::GetFocusedPlayerInfo().m_pRemoteVehicle == this)
            isRemotelyControlledByPlayer = true;
        break;
    case STATUS_PLANE:
        if (m_vecMoveSpeed.SquaredMagnitude() < 0.01f
            || m_pDriver
            && m_pDriver->IsPlayer()
            && (m_pDriver->m_nPedState == PEDSTATE_ARRESTED
                || m_pDriver->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_CAR_SLOW_BE_DRAGGED_OUT)
                || m_pDriver->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_CAR_QUICK_BE_DRAGGED_OUT)
                || m_pDriver->GetTaskManager().FindActiveTaskByType(TASK_SIMPLE_CAR_WAIT_TO_SLOW_DOWN)))
        {
            m_fBreakPedal = 1.0f;
            m_fGasPedal = 0.0f;
            vehicleFlags.bIsHandbrakeOn = true;
        }
        else
        {
            m_fBreakPedal = 0.0f;
            vehicleFlags.bIsHandbrakeOn = false;
        }

        m_fSteerAngle = 0.0f;
        m_fGasPedal = 0.0f;
        if (!CanUpdateHornCounter())
            return false;
        m_nHornTimeEndMs = 0;
        return false;
    case STATUS_REMOTE_CONTROLLED:
        vehicleFlags.bIsHandbrakeOn = false;
        m_fBreakPedal = 0.0f;
        m_fSteerAngle = 0.0f;
        m_fGasPedal = 0.0f;
        if (!m_pTractor)
            BreakTowLink();
        return false;
    }

    if (status != STATUS_PLAYER && status != STATUS_HELI)
        return false;

    bool processControlInput = isRemotelyControlledByPlayer;
    if (!processControlInput && m_pDriver)
    {
        ePedState pedState = m_pDriver->m_nPedState;
        if (pedState != PEDSTATE_EXIT_CAR && pedState != PEDSTATE_DRAGGED_FROM_CAR && pedState != PEDSTATE_ARRESTED)
            processControlInput = true;
    }
    if (!processControlInput)
        return false;

    CPad* pad = nullptr;
    if (m_pDriver)
        pad = static_cast<CPlayerPed*>(m_pDriver)->GetPadFromPlayer();
    PruneReferences();
    if (isRemotelyControlledByPlayer) {
        int32 playerSlot = CWorld::FindPlayerSlotWithRemoteVehiclePointer(this);
        if (playerSlot >= 0)
            ProcessControlInputs(playerSlot);
    }
    else if (m_pDriver->IsPlayer())
        ProcessControlInputs(static_cast<uint8>(m_pDriver->m_nPedType));

    if (m_nStatus == STATUS_PLAYER) {
        if (!IsHeli()) {
            if ((m_nModelIndex == MODEL_VORTEX || !IsPlane())
                && m_nModelIndex != MODEL_SWATVAN
                && m_nModelIndex != MODEL_RHINO)
                DoDriveByShootings();
        }
    }

    uint32 carLess3WheelCounter = CWorld::GetFocusedPlayerInfo().m_nCarLess3WheelCounter;
    m_vecCentreOfMass.z = m_pHandlingData->m_vecCentreOfMass.z;
    if (carLess3WheelCounter > 500 && !IsHeli() && !IsPlane()) {
        carLess3WheelCounter = std::min(carLess3WheelCounter - 500u, 1000u);
        float fCarLess3WheelCounter = static_cast<float>(carLess3WheelCounter) * 0.002f;
        const float boundMaxZ = colModel->m_boundBox.m_vecMax.z;
        if (GetUp().z > -0.4f && pad) {
            if (GetRight().z <= 0.0f)
                fCarLess3WheelCounter *= -1.0f;

            float steerLeftRight = pad->GetSteeringLeftRight() / 128.0f;
            m_vecCentreOfMass.z += steerLeftRight * CAR_BALANCE_MULT * boundMaxZ * fCarLess3WheelCounter;
        }
        else {
            m_vecCentreOfMass.z -= CAR_BALANCE_MULT * boundMaxZ * 0.5f;
        }
    }

    if (!pad || m_nNumContactWheels != 0 || IsHeli() || IsPlane()) {
        DoSoftGroundResistance(extraHandlingFlags);
        return false;
    }

    float carWeightMult = 0.0007f;
    if (IsMonsterTruck())
        carWeightMult = 0.0025f;
    else
        carWeightMult *= CStats::GetFatAndMuscleModifier(STAT_MOD_DRIVING_SKILL);
    carWeightMult *= std::min(1.0f, 3000.0f / m_fTurnMass) * m_fTurnMass;
    float steerLeftRight = pad->GetSteeringLeftRight() / 128.0f;
    float steerUpDown = pad->GetSteeringUpDown() / 128.0f;
    if (CCamera::m_bUseMouse3rdPerson && fabs(steerLeftRight) < 0.05f && fabs(steerUpDown) < 0.05f) {
        float mouseSteerLeftRight = CPad::NewMouseControllerState.X * 0.02f;
        steerLeftRight = clamp<float>(mouseSteerLeftRight, -1.5f, 1.5f);
        float mouseSteerUpDown = CPad::NewMouseControllerState.Y * 0.02f;
        steerUpDown = clamp<float>(mouseSteerUpDown, -1.5f, 1.5f);
    }

    if (pad->GetHandBrake()) {
        float dotTurnUp = DotProduct(m_vecTurnSpeed, GetUp());;
        if (dotTurnUp < 0.02f && steerLeftRight < 0.0f || dotTurnUp > -0.02f && steerLeftRight > 0.0f) {
            CVector point = m_vecCentreOfMass + GetForward();
            CVector force = GetRight() * steerLeftRight * carWeightMult * CTimer::GetTimeStep();
            ApplyTurnForce(force, point);
        }
    }
    else if (!pad->GetAccelerate()) {
        float dotTurnForward = DotProduct(m_vecTurnSpeed, GetForward());
        if (dotTurnForward < 0.02f && steerLeftRight < 0.0f
            || dotTurnForward > -0.02f && steerLeftRight > 0.0f)
        {
            CVector point = m_vecCentreOfMass + GetUp();
            CVector force = GetRight() * steerLeftRight * carWeightMult * CTimer::GetTimeStep();
            ApplyTurnForce(force, point);
        }
    }

    if (!pad->GetAccelerate()) {
        float dotTurnRight = DotProduct(m_vecTurnSpeed, GetRight());
        if (dotTurnRight < 0.02f && steerUpDown < 0.0f
            || dotTurnRight > -0.02f && steerUpDown > 0.0f)
        {
            CVector point = m_vecCentreOfMass + GetForward();
            CVector force = GetUp() * steerUpDown * carWeightMult * CTimer::GetTimeStep();
            ApplyTurnForce(force, point);
        }
    }
    DoSoftGroundResistance(extraHandlingFlags);
    return false;
}

void CAutomobile::ResetSuspension()
{
    for (int32 i = 0; i < 4; i++) {
        m_fWheelsSuspensionCompression[i] = 1.0f;
        m_aWheelTimer[i] = 0.0f;
        m_wheelRotation[i] = 0.0f;
        m_aWheelState[i] = WHEEL_STATE_NORMAL;
    }
}

// 0x6A8500
void CAutomobile::ProcessFlyingCarStuff()
{
    if (m_nStatus == STATUS_PLAYER || m_nStatus == STATUS_HELI || m_nStatus == STATUS_PHYSICS) {
        if (CCheat::m_aCheatsActive[CHEAT_CARS_FLY]
            && m_vecMoveSpeed.Magnitude() > 0.0f
            && CTimer::GetTimeStep() > 0.0f
        ) {
            FlyingControl(FLIGHT_MODEL_PLANE, -9999.9902F, -9999.9902F, -9999.9902F, -9999.9902F);
        }
    }
}

void CAutomobile::DoHoverSuspensionRatios()
{
    if (GetUp().z >= 0.3f && !vehicleFlags.bIsDrowning) {
        auto colData = GetColModel()->m_pColData;
        for (int32 i = 0; i < 4; i++)  {
            CColLine& line = colData->m_pLines[i];
            CVector start = *m_matrix * line.m_vecStart;
            CVector end = *m_matrix * line.m_vecEnd;
            float colPointZ = -100.0f;
            if (m_fWheelsSuspensionCompression[i] < 1.0f)
                colPointZ = m_wheelColPoint[i].m_vecPoint.z;
            float waterLevel = 0.0f;
            if (CWaterLevel::GetWaterLevel(end.x, end.y, end.z, &waterLevel, false, nullptr)
                && waterLevel > colPointZ && end.z - 1.0f < waterLevel)
            {
                if (waterLevel <= end.z) 
                    m_fWheelsSuspensionCompression[i] = 1.0f;
                else if (waterLevel <= start.z)
                    m_fWheelsSuspensionCompression[i] = (start.z - waterLevel) / (start.z - end.z);
                else
                    m_fWheelsSuspensionCompression[i] = 0.0f;

                CVector point = (end - start) * m_fWheelsSuspensionCompression[i];
                point += start;
                point.z = waterLevel;
                m_wheelColPoint[i].m_vecPoint = point;
                m_wheelColPoint[i].m_vecNormal = CVector(0.0f, 0.0f, 1.0f);
            }
        }
    }
}

void CAutomobile::ProcessSuspension()
{
    float springLength[4];
    CVector contactPoints[4]; 
    float wheelSpringForceDampingLimits[4]; 
    CVector directions[4];
    CVector contactSpeeds[4];
    int32 wheelLineIndices[4];

    for (int32 i = 0; i < 4; i++) {
        springLength[i] = m_fWheelsSuspensionCompression[i];
        wheelSpringForceDampingLimits[i] = 0.0f;
    }

    float forwardSpeed = fabs(DotProduct(m_vecMoveSpeed, GetForward()));

    int32 numWheelLoops = 1;
    if (ModelIndices::IsRhino(m_nModelIndex) && CReplay::Mode != REPLAY_MODE_1)
        numWheelLoops = 3;
    for (int32 wheelLoopIndex = 0; wheelLoopIndex < numWheelLoops; wheelLoopIndex++) {
        for (int32 i = 0; i < 4; i++) {
            directions[i] = GetUp() * -1.0f;
            if (springLength[i] < 1.0f) 
                contactPoints[i] = m_wheelColPoint[i].m_vecPoint - GetPosition();
        }

        for (int32 i = 0; i < 4; i++) {
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

        for (int32 i = 0; i < 4; ++i) {
            contactSpeeds[i] = CPhysical::GetSpeed(contactPoints[i]);
            if (m_pWheelCollisionEntity[i])
                contactSpeeds[i] -= m_pWheelCollisionEntity[i]->GetSpeed(m_vWheelCollisionPos[i]);
            if (m_fWheelsSuspensionCompression[i] < 1.0f && m_wheelColPoint[i].m_vecNormal.z > 0.35f) {
                directions[i] = -m_wheelColPoint[i].m_vecNormal;
            }
        }

        for (int32 i = 0; i < 4; ++i) {
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
        for (int32 i = 0; i < 4; i++) {
            float wheelRadius = 1.0f - m_aSuspensionSpringLength[i] / m_aSuspensionLineLength[i];
            wheelsSuspensionCompressionPrev[i] = (wheelsSuspensionCompressionPrev[i] - wheelRadius) / (1.0f - wheelRadius);
            // yes, wheelsSuspensionCompressionPrev is unused here

            CColLine& colLine = colData->m_pLines[wheelLineIndices[i]];
            contactPoints[i] = colLine.m_vecStart;
            contactPoints[i].z -= m_aSuspensionLineLength[i] * springLength[i];
            contactPoints[i] = Multiply3x3(GetMatrix(), contactPoints[i]);
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

void CAutomobile::ProcessControl_Reversed()
{
    return CAutomobile::ProcessControl();
}

CVector CAutomobile::AddMovingCollisionSpeed_Reversed(CVector& point)
{
    return CAutomobile::AddMovingCollisionSpeed(point);
}

bool CAutomobile::ProcessAI_Reversed(uint32& extraHandlingFlags)
{
    return CAutomobile::ProcessAI(extraHandlingFlags);
}

void CAutomobile::ResetSuspension_Reversed()
{
    return CAutomobile::ResetSuspension();
}

void CAutomobile::ProcessFlyingCarStuff_Reversed()
{
    return CAutomobile::ProcessFlyingCarStuff();
}

void CAutomobile::DoHoverSuspensionRatios_Reversed()
{
    return CAutomobile::DoHoverSuspensionRatios();
}

void CAutomobile::ProcessSuspension_Reversed()
{
    return CAutomobile::ProcessSuspension();
}

void CAutomobile::SetupModelNodes()
{
    for (int32 i = 0; i < CAR_NUM_NODES; i++) {
        m_aCarNodes[i] = nullptr;
    }
    CClumpModelInfo::FillFrameArray(m_pRwClump, m_aCarNodes);
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
            if (CGameLogic::GameState != GAME_STATE_INITIAL)
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
            for (int32 i = 0; i < colData->m_nNumSpheres; i++) {
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
                for (int32 i = 0; i < 4; i++) {
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
                for (int32 i = 0; i < 4; i++) {
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
            for (int32 i = 0; i < 4; i++) {
                suspensionChange[i] = 1.0f;
            }

            if (m_nStatus == STATUS_PHYSICS) {
                for (int32 i = 0; i < 4; i++) {
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
                        for (int32 i = 0; i < 4; i++) {
                            suspensionChange[i] = 0.0f;
                        }
                    }
                    m_wMiscComponentAngle = 60;
                }

                for (int32 i = 0; i < 4; i++) {
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
                for (int32 i = 0; i < 4; i++) {
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
                if (f < 0.5f - CTimer::GetTimeStep() * 0.05f)
                    m_vehicleAudio.AddAudioEvent(AE_SUSPENSION_HYDRAULIC, 0.0f);
                else if (f > CTimer::GetTimeStep() * 0.05f + 0.5f)
                    m_vehicleAudio.AddAudioEvent(AE_SUSPENSION_TRIGGER, 0.0f);
                else if (f > CTimer::GetTimeStep() * 0.025f + 0.5f)
                    m_vehicleAudio.AddAudioEvent(AE_SUSPENSION_HYDRAULIC, 0.0f);
            }
        }

        if (setPrevRatio || suspensionTriggered) {
            for (int32 i = 0; i < 4; i++) {
                float wheelRadius = 1.0f - m_aSuspensionSpringLength[i] / m_aSuspensionLineLength[i];
                m_fWheelsSuspensionCompressionPrev[i] = (m_fWheelsSuspensionCompression[i] - wheelRadius) / (1.0f - wheelRadius);
            }
        }
        for (int32 i = 0; i < 4; i++) {
            hydraulicData.m_wheelSuspension[i] = 0.0f;
        }
    }
}

const int16 DEFAULT_COLLISION_EXTENDLIMIT = 2500;

bool CAutomobile::UpdateMovingCollision(float angle)
{
    if (ModelIndices::HasMiscComponent(m_nModelIndex))
        m_wMiscComponentAnglePrev = m_wMiscComponentAngle;

    CPad* pad = nullptr;
    if (m_nStatus == STATUS_PLAYER) {
        CPlayerPed* driver = static_cast<CPlayerPed*>(m_pDriver);
        if (!driver || !driver->IsPlayer() || CGameLogic::GameState)
            return false;
        pad = driver->GetPadFromPlayer();
    }
    else if (!IsCreatedBy(MISSION_VEHICLE) || angle < 0.0f
        || !ModelIndices::HasMiscComponent(m_nModelIndex) && !ModelIndices::IsFireTruckLadder(m_nModelIndex))
    {
        return false;
    }

    if (!ModelIndices::IsCementTruck(m_nModelIndex) && !ModelIndices::IsFireTruckLadder(m_nModelIndex)) {
        CColModel* colModel = CModelInfo::GetModelInfo(m_nModelIndex)->m_pColModel;
        CCollisionData* colData = colModel->m_pColData;
        if (!GetSpecialColModel())
            return false;
        CColModel& specialColModel = m_aSpecialColModel[m_vehicleSpecialColIndex];
        CCollisionData* specialColData = specialColModel.m_pColData;
        m_wMiscComponentAnglePrev = m_wMiscComponentAngle;
        if (angle < 0.0f) {
            if (!pad || fabs(pad->GetCarGunUpDown()) <= 10.0f)
                return false;
        }
        if (angle >= 0.0f) {
            m_wMiscComponentAngle = static_cast<uint16>(angle * DEFAULT_COLLISION_EXTENDLIMIT);
        }
        else {
            float colAngleMult = 10.0f;
            if (ModelIndices::IsForklift(m_nModelIndex) ) {
                if (pad->GetCarGunUpDown() >= 0.0f)
                    colAngleMult *= -2;
                else
                    colAngleMult *= -1;
            }

            m_wMiscComponentAngle += static_cast<uint16>((pad->GetCarGunUpDown() / 128.0f) * colAngleMult * CTimer::GetTimeStep());
            m_wMiscComponentAngle = clamp<int16>(m_wMiscComponentAngle, 0, DEFAULT_COLLISION_EXTENDLIMIT);
        }

        CMatrix rotMatrix;

        RwFrame* carNodeMisc = nullptr;
        if (ModelIndices::IsDozer(m_nModelIndex)) {
            carNodeMisc = m_aCarNodes[CAR_MISC_A];
            if (carNodeMisc)
                rotMatrix.SetRotateX(m_wMiscComponentAngle * DOZER_COL_ANGLE_MULT);
        }
        else if (ModelIndices::IsDumper(m_nModelIndex) && IsMonsterTruck()) {
            carNodeMisc = m_aCarNodes[CAR_MISC_C];
            if (carNodeMisc)
                rotMatrix.SetRotateX(m_wMiscComponentAngle * CMonsterTruck::DUMPER_COL_ANGLEMULT);
        }
        else if (ModelIndices::IsAndromada(m_nModelIndex)) {
            carNodeMisc = m_aCarNodes[CAR_MISC_E];
            if (carNodeMisc)
                rotMatrix.SetRotateX(m_wMiscComponentAngle * CPlane::ANDROM_COL_ANGLE_MULT);
        }
        else if (ModelIndices::IsForklift(m_nModelIndex)) {
            carNodeMisc = m_aCarNodes[CAR_MISC_A];
            if (carNodeMisc)
                rotMatrix.SetTranslate(CVector(0.0f, 0.0f, m_wMiscComponentAngle * FORKLIFT_COL_ANGLE_MULT));
        }
        else if (ModelIndices::IsPacker(m_nModelIndex)) {
            carNodeMisc = m_aCarNodes[CAR_MISC_A];
            if (carNodeMisc)
                rotMatrix.SetRotateX(m_wMiscComponentAngle * PACKER_COL_ANGLE_MULT);
        }

        CVector componentPos;
        if (carNodeMisc && !ModelIndices::IsForklift(m_nModelIndex))
            componentPos = RwFrameGetMatrix(carNodeMisc)->pos;
        float maxZ = -1000.0f;
        float minZ = 1000.0f;
        for (uint16 triIndx = 0; triIndx < specialColData->m_nNumTriangles; triIndx++) {
            CColTriangle& specialColTriangle = specialColData->m_pTriangles[triIndx];
            if (specialColTriangle.m_nMaterial == SURFACE_CAR_MOVINGCOMPONENT) {
                const CColTriangle& colTriangle = colData->m_pTriangles[triIndx];
                for (int32 i = 0; i < 3; i++) {
                    CVector vertexPos = UncompressVector(colData->m_pVertices[colTriangle.m_vertIndices[i]]);
                    CVector distance  = vertexPos - componentPos;
                    vertexPos = (rotMatrix * distance) + componentPos;
                    specialColData->m_pVertices[specialColTriangle.m_vertIndices[i]] = CompressVector(vertexPos);
                    if (maxZ < vertexPos.z) 
                        maxZ = vertexPos.z;
                    else if (minZ > vertexPos.z)
                        minZ = vertexPos.z;
                }
            }
        }

        if (specialColData->m_pTrianglePlanes) {
            for (int32 i = 0; i < specialColData->m_nNumTriangles; i++) {
                CColTrianglePlane& trianglePlane = specialColData->m_pTrianglePlanes[i];
                trianglePlane.Set(specialColData->m_pVertices, specialColData->m_pTriangles[i]);
            }
        }

        for (uint16 i = 0; i < specialColData->m_nNumSpheres; i++) {
            CColSphere& specialColSphere = specialColData->m_pSpheres[i];
            if (specialColSphere.m_nMaterial == SURFACE_CAR_MOVINGCOMPONENT) {
                CColSphere& colSphere = colData->m_pSpheres[i];
                CVector distance = colSphere.m_vecCenter - componentPos;
                specialColSphere.m_vecCenter = (rotMatrix * distance) + componentPos;
                const float newMaxZ = specialColSphere.m_fRadius + specialColSphere.m_vecCenter.z;
                const float newMinZ = specialColSphere.m_vecCenter.z - specialColSphere.m_fRadius;;
                if (maxZ < newMaxZ)
                    maxZ = newMaxZ;
                else if (minZ > newMinZ)
                    minZ = newMinZ;
            }
        }
        if (colModel->GetBoundingBox().m_vecMax.z < maxZ)
            specialColModel.GetBoundingBox().m_vecMax.z = maxZ;
        if (colModel->GetBoundingBox().m_vecMin.z > minZ)
            specialColModel.GetBoundingBox().m_vecMin.z = minZ;
        return true;
    }

    m_wMiscComponentAnglePrev = m_wMiscComponentAngle;
    if (angle >= 0.0f) {
        m_wMiscComponentAngle = static_cast<uint16>(angle * DEFAULT_COLLISION_EXTENDLIMIT);
        return false;
    }
    if (!pad)
        return false;
    if (pad->GetCarGunUpDown() < -10.0f) {
        m_wMiscComponentAngle -= static_cast<uint16>(2 * (pad->GetCarGunUpDown() / 128.0f) * 10.0f * CTimer::GetTimeStep());
        m_wMiscComponentAngle = std::min(static_cast<int16>(m_wMiscComponentAngle), DEFAULT_COLLISION_EXTENDLIMIT);
        return false;
    }
    if (!m_wMiscComponentAngle)
        return false;
    m_wMiscComponentAngle -= static_cast<uint16>(((pad->GetCarGunUpDown() + 100) * 10.0f * CTimer::GetTimeStep()) / 128.0f);
    if (static_cast<int16>(m_wMiscComponentAngle) < 0)
        m_wMiscComponentAngle = 0;
    return false;
}

// 0x6A2150
float CAutomobile::GetMovingCollisionOffset()
{
    return ((float(__thiscall*)(CAutomobile*))0x6A2150)(this);
}

// 0x6A2390
void CAutomobile::TellHeliToGoToCoors(float x, float y, float z, float altitudeMin, float altitudeMax)
{
    ((void(__thiscall*)(CAutomobile*, float, float, float, float, float))0x6A2390)(this, x, y, z, altitudeMin, altitudeMax);
}

// 0x6A2450
void CAutomobile::SetHeliOrientation(float angle)
{
    m_fForcedOrientation = angle;
}

// 0x6A2460
void CAutomobile::ClearHeliOrientation()
{
    m_fForcedOrientation = 0.0f;
}

// 0x6A2470
void CAutomobile::TellPlaneToGoToCoors(float x, float y, float z, float altitudeMin, float altitudeMax)
{
    ((void(__thiscall*)(CAutomobile*, float, float, float, float, float))0x6A2470)(this, x, y, z, altitudeMin, altitudeMax);
}

// unused
// 0x6A2510
void CAutomobile::HideAllComps()
{
    // NOP
}

// unused
// 0x6A2520
void CAutomobile::ShowAllComps()
{
    // NOP
}

// 0x6A2530
void CAutomobile::SetRandomDamage(bool arg0)
{
    ((void(__thiscall*)(CAutomobile*, bool))0x6A2530)(this, arg0);
}

// 0x6A27F0
void CAutomobile::SetTotalDamage(bool arg0)
{
    ((void(__thiscall*)(CAutomobile*, bool))0x6A27F0)(this, arg0);
}

// 0x6A2980
RpMaterial* DisableMatFx(RpMaterial* material, void* data)
{
    return ((RpMaterial * (__cdecl*)(RpMaterial*, void*))0x6A2980)(material, data);
}

// 0x6A29A0
void CAutomobile::ReduceHornCounter()
{
    if (m_nHornTimeEndMs) m_nHornTimeEndMs--;
}

// 0x6A2F00
void CAutomobile::CustomCarPlate_BeforeRenderingStart(CVehicleModelInfo* model)
{
    ((void(__thiscall*)(CAutomobile*, CVehicleModelInfo*))0x6A2F00)(this, model);
}

// 0x6A2F30
void CAutomobile::CustomCarPlate_AfterRenderingStop(CVehicleModelInfo* model)
{
    ((void(__thiscall*)(CAutomobile*, CVehicleModelInfo*))0x6A2F30)(this, model);
}

// 0x6A2F70
bool CAutomobile::GetAllWheelsOffGround()
{
    return ((bool(__thiscall*)(CAutomobile*))0x6A2F70)(this);
}

// 0x6A2F80
void CAutomobile::DebugCode()
{
    ((void(__thiscall*)(CAutomobile*))0x6A2F80)(this);
}

// 0x6A3580
void CAutomobile::FixTyre(eWheelStatus wheel)
{
    ((void(__thiscall*)(CAutomobile*, eWheelStatus))0x6A3580)(this, wheel);
}

// 0x6A35A0
void CAutomobile::FixDoor(int32 nodeIndex, eDoors door)
{
    ((void(__thiscall*)(CAutomobile*, int32, eDoors))0x6A35A0)(this, nodeIndex, door);
}

// 0x6A3670
void CAutomobile::FixPanel(int32 nodeIndex, ePanels panel)
{
    ((void(__thiscall*)(CAutomobile*, int32, ePanels))0x6A3670)(this, nodeIndex, panel);
}

// 0x6A3740
void CAutomobile::SetTaxiLight(bool enable)
{
    ((void(__thiscall*)(CAutomobile*, bool))0x6A3740)(this, enable);
}

// 0x6A3760
void CAutomobile::SetAllTaxiLights(bool arg0)
{
    ((void(__cdecl*)(bool))0x6A3760)(arg0);
}

// 0x6A3820
void CAutomobile::PlayHornIfNecessary()
{
    ((void(__thiscall*)(CAutomobile*))0x6A3820)(this);
}

// 0x6A3860
void CAutomobile::SetBusDoorTimer(uint32 time, uint8 arg1)
{
    ((void(__thiscall*)(CAutomobile*, uint32, uint8))0x6A3860)(this, time, arg1);
}

// 0x6A38A0
void CAutomobile::ProcessAutoBusDoors()
{
    ((void(__thiscall*)(CAutomobile*))0x6A38A0)(this);
}

// 0x6A3A60
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

// 0x6A3E60
void CAutomobile::StopNitroEffect()
{
    ((void(__thiscall*)(CAutomobile*))0x6A3E60)(this);
}

// 0x6A3EA0
void CAutomobile::NitrousControl(int8 arg0)
{
    ((void(__thiscall*)(CAutomobile*, int8))0x6A3EA0)(this, arg0);
}

// 0x6A40F0
void CAutomobile::TowTruckControl()
{
    ((void(__thiscall*)(CAutomobile*))0x6A40F0)(this);
}

// 0x6A44C0
CPed* CAutomobile::KnockPedOutCar(eWeaponType arg0, uint16 arg1, CPed* arg2)
{
    return ((CPed * (__thiscall*)(CAutomobile*, eWeaponType, uint16, CPed*))0x6A44C0)(this, arg0, arg1, arg2);
}

// 0x6A44D0
void CAutomobile::PopBootUsingPhysics()
{
    ((void(__thiscall*)(CAutomobile*))0x6A44D0)(this);
}

// 0x6A4520
void CAutomobile::CloseAllDoors()
{
    ((void(__thiscall*)(CAutomobile*))0x6A4520)(this);
}

void CAutomobile::DoSoftGroundResistance(uint32& extraHandlingFlags)
{
    if (IsAnyWheelTouchingSand() && m_nModelIndex != MODEL_RCBANDIT && m_nModelIndex != MODEL_RHINO) {
        CVector speedUp = m_vecMoveSpeed - DotProduct(m_vecMoveSpeed, GetUp()) * GetUp();
        float offroadAbility = 0.005f;
        if (speedUp.SquaredMagnitude() <= 0.3f * 0.3f) {
            npcFlags.bLostTraction = true;
        }
        else {
            float magnitude = speedUp.NormaliseAndMag();
            speedUp *= 0.3f;
            offroadAbility *= std::max(0.2f, 1.0f - (magnitude + magnitude));
        }
        if (handlingFlags.bOffroadAbility2)
            offroadAbility *= 0.3f;
        else if (handlingFlags.bOffroadAbility)
            offroadAbility *= 0.6f;
        if (CWeather::WetRoads > 0.2f)
            offroadAbility *= (1.2f - CWeather::WetRoads);
        float direction = -(offroadAbility * (CTimer::GetTimeStep() * m_fMass));
        ApplyMoveForce(speedUp * direction);
        extraHandlingFlags |= EXTRA_HANDLING_WHEELS_TOUCHING_SAND;
    }
    else if (IsAnyWheelTouchingRailTrack()) {
        if (m_nModelIndex != MODEL_RCBANDIT && m_nModelIndex != MODEL_RHINO) {
            CVector speedUp = m_vecMoveSpeed - DotProduct(m_vecMoveSpeed, GetUp()) * GetUp();
            float direction = -(CTimer::GetTimeStep() * m_fMass * CVehicle::ms_fRailTrackResistance);
            ApplyMoveForce(speedUp * direction);
        }
    }
}

void CAutomobile::ProcessCarWheelPair(int32 leftWheel, int32 rightWheel, float steerAngle, CVector* contactSpeeds, CVector* contactPoints, float traction, float acceleration, float brake, bool bFront)
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
            m_fTireTemperature += CTimer::GetTimeStep() * 0.001f;
            m_fTireTemperature = std::min(m_fTireTemperature, 3.0f);
        }
        else if (m_fTireTemperature > 1.0f) {
            m_fTireTemperature = std::powf(0.995f, CTimer::GetTimeStep()) * (m_fTireTemperature - 1.0f) + 1.0f;
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
            m_wheelRotation[leftWheel] += CTimer::GetTimeStep() * m_wheelSpeed[leftWheel];
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
            m_wheelRotation[rightWheel] += CTimer::GetTimeStep() * m_wheelSpeed[rightWheel];
        }
    }
}

// 0x6A6010
float CAutomobile::GetCarRoll()
{
    return ((float(__thiscall*)(CAutomobile*))0x6A6010)(this);
}

// 0x6A6050
float CAutomobile::GetCarPitch()
{
    return ((float(__thiscall*)(CAutomobile*))0x6A6050)(this);
}

// 0x6A6140
bool CAutomobile::IsInAir()
{
    return ((bool(__thiscall*)(CAutomobile*))0x6A6140)(this);
}

// 0x6A6DC0
void CAutomobile::dmgDrawCarCollidingParticles(CVector const& position, float force, eWeaponType weapon)
{
    ((void(__thiscall*)(CAutomobile*, CVector const&, float, eWeaponType))0x6A6DC0)(this, position, force, weapon);
}

void CAutomobile::ProcessCarOnFireAndExplode(bool bExplodeImmediately)
{
    ((void(__thiscall*)(CAutomobile*, uint8))0x6A7090)(this, bExplodeImmediately);
}

// 0x6A8580
CObject* CAutomobile::SpawnFlyingComponent(int32 nodeIndex, uint32 collisionType)
{
    return ((CObject * (__thiscall*)(CAutomobile*, int32, uint32))0x6A8580)(this, nodeIndex, collisionType);
}

// 0x6A8C00
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
        for (int32 i = 0; i < 4; ++i) {
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
    auto fTimeStep = std::max(0.01F, CTimer::GetTimeStep());
    auto fUsedMass = m_fMass / 125.0F;
    auto fBuoyancyForceZ = vecBuoyancyForce.z / (fTimeStep * fUsedMass);

    if (fUsedMass > m_fBuoyancyConstant)
        fBuoyancyForceZ *= 1.05F * fUsedMass / m_fBuoyancyConstant;

    if (physicalFlags.bMakeMassTwiceAsBig)
        fBuoyancyForceZ *= 1.5F;

    auto fBuoyancyForceMult = std::max(0.5F, 1.0F - fBuoyancyForceZ / 20.0F);
    auto fSpeedMult = pow(fBuoyancyForceMult, CTimer::GetTimeStep());

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

    if (ModelIndices::IsAmphibiousHeli(m_nModelIndex)
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

        for (int32 iPassengerInd = 0; iPassengerInd < m_nMaxPassengers; ++iPassengerInd) {
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
            auto pedDamageResponseCalc = CPedDamageResponseCalculator(this, CTimer::GetTimeStep(), eWeaponType::WEAPON_DROWNING, ePedPieceTypes::PED_PIECE_TORSO, false);
            auto damageEvent = CEventDamage(this, CTimer::GetTimeInMS(), eWeaponType::WEAPON_DROWNING, ePedPieceTypes::PED_PIECE_TORSO, 0, false, true);
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

// 0x6A9680
void CAutomobile::ProcessHarvester()
{
    if (m_nStatus == STATUS_PLAYER) {
        CStreaming::m_bStreamHarvesterModelsThisFrame = true;
        if (m_vecMoveSpeed.Magnitude2D() > 0.01f) {
            if ((CTimer::GetFrameCounter() & 1) != 0)
            {
                for (int32 i = CPools::ms_pPedPool->GetSize() - 1; i >= 0; i--) {
                    CPed* ped = CPools::ms_pPedPool->GetAt(i);
                    if (ped && !ped->IsPlayer()) {
                        CVector distance = ped->GetPosition() - GetPosition();
                        float distanceForward = DotProduct(distance, GetForward());
                        if (distanceForward > 4.0f && distanceForward < 5.0f) {
                            float distanceRight = std::abs(DotProduct(distance, GetRight()));
                            if (distanceRight < 4.0f) {
                                float distanceUp = std::abs(DotProduct(distance, GetUp()));
                                if (distanceUp < 4.0f) {
                                    ped->FlagToDestroyWhenNextProcessed();
                                    m_harvesterParticleCounter = 20;
                                    m_vehicleAudio.AddAudioEvent(AE_BODY_HARVEST, 0.0f);
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                for (int32 i = CPools::ms_pObjectPool->GetSize() - 1; i >= 0; i--) {
                    CObject* object = CPools::ms_pObjectPool->GetAt(i);
                    if (object && (m_nModelIndex == ModelIndices::MI_GRASSHOUSE || m_nModelIndex == ModelIndices::MI_GRASSPLANT)) {
                        CVector distance = object->GetPosition() - GetPosition();
                        float distanceForward = DotProduct(distance, GetForward());
                        if (distanceForward > 4.0f && distanceForward < 5.0f) {
                            float distanceRight = std::abs(DotProduct(distance, GetRight()));
                            if (distanceRight < 4.0f) {
                                float distanceUp = std::abs(DotProduct(distance, GetUp()));
                                if (distanceUp < 4.0f)
                                    object->ObjectDamage(99999.0f, nullptr, nullptr, this, WEAPON_RUNOVERBYCAR);
                            }
                        }
                    }
                }
            }
        }

        if (!m_harvesterParticleCounter)
            return;

        CVector pos = *m_matrix * CVector(-1.2f, -3.8f, 1.5f);
        CVector velocity = GetForward() * -0.1f;
        velocity.x += CGeneral::GetRandomNumberInRange(0.05f, -0.05f);
        velocity.y += CGeneral::GetRandomNumberInRange(0.05f, -0.05f);
        int32 bodyPartModelId = -1;
        switch (m_harvesterParticleCounter - 1)
        {
        case 0:
        case 6:
            bodyPartModelId = ModelIndices::MI_HARVESTERBODYPART1;
            break;
        case 1:
        case 3:
            bodyPartModelId = ModelIndices::MI_HARVESTERBODYPART2;
            break;
        case 2:
            bodyPartModelId = ModelIndices::MI_HARVESTERBODYPART3;
            break;
        case 5:
            bodyPartModelId = ModelIndices::MI_HARVESTERBODYPART4;
            break;
        }

        if (CLocalisation::ShootLimbs() && bodyPartModelId >= 0) {
            CObject* limb = new CObject(bodyPartModelId, true);
            CPlaceable::SetMatrix(*m_matrix);
            limb->SetPosn(pos);
            limb->m_vecMoveSpeed = velocity;
            CVector turnSpeed(
            CGeneral::GetRandomNumberInRange(0.12f, -0.04f),
            CGeneral::GetRandomNumberInRange(0.12f, -0.04f),
            CGeneral::GetRandomNumberInRange(0.12f, -0.04f));
            limb->m_vecTurnSpeed = turnSpeed;
            limb->m_nObjectType = OBJECT_TEMPORARY;
            limb->UpdateRW();
            limb->UpdateRwFrame();
            limb->SetIsStatic(false);
            CObject::nNoTempObjects++;
            CWorld::Add(limb);
        }
        m_harvesterParticleCounter--;
        if (CLocalisation::Blood() && m_harvesterParticleCounter % 3 == 0) {
            FxPrtMult_c fxPrtMult;
            fxPrtMult.SetUp(0.15f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f);
            g_fx.m_pPrtSmokeII3expand->AddParticle(&pos, &velocity, 0.0f, &fxPrtMult, -1.0f, 1.2f, 0.6f, 0);
        }
    }
}

// 0x6A9D70
void CAutomobile::ProcessSwingingDoor(int32 nodeIndex, eDoors door)
{
    ((void(__thiscall*)(CAutomobile*, int32, eDoors))0x6A9D70)(this, nodeIndex, door);
}

// 0x6AA200
CObject* CAutomobile::RemoveBonnetInPedCollision()
{
    return ((CObject * (__thiscall*)(CAutomobile*))0x6AA200)(this);
}

// 0x6AA290
void CAutomobile::UpdateWheelMatrix(int32 nodeIndex, int32 flags)
{
    ((void(__thiscall*)(CAutomobile*, int32, int32))0x6AA290)(this, nodeIndex, flags);
}

// 0x6ADEF0
void CAutomobile::PopDoor(int32 nodeIndex, eDoors door, bool showVisualEffect)
{
    ((void(__thiscall*)(CAutomobile*, int32, eDoors, bool))0x6ADEF0)(this, nodeIndex, door, showVisualEffect);
}

// 0x6ADF80
void CAutomobile::PopPanel(int32 nodeIndex, ePanels panel, bool showVisualEffect)
{
    ((void(__thiscall*)(CAutomobile*, int32, ePanels, bool))0x6ADF80)(this, nodeIndex, panel, showVisualEffect);
}

// 0x6ADFF0
void CAutomobile::ScanForCrimes()
{
    ((void(__thiscall*)(CAutomobile*))0x6ADFF0)(this);
}

void CAutomobile::TankControl()
{
    if (m_nModelIndex == MODEL_RCTIGER && m_nStatus  == STATUS_HELI) {
        if (CPad::GetPad(0)->CarGunJustDown()) {
            if (CTimer::GetTimeInMS() > m_nGunFiringTime + TIGER_GUNFIRE_RATE) {
                CWeapon minigun(WEAPON_MINIGUN, 5000);
                CVector point = *m_matrix * TIGER_GUN_POS + CTimer::GetTimeStep() * m_vecMoveSpeed;
                minigun.FireInstantHit(this, &point, &point, nullptr, nullptr, nullptr, false, true);
                CVector2D direction(0.0f, 0.1f);
                minigun.AddGunshell(this, point, direction, 0.025f);
                AudioEngine.ReportWeaponEvent(AE_WEAPON_FIRE, WEAPON_MINIGUN, this);
                m_nGunFiringTime = CTimer::GetTimeInMS();
            }
        }
        return;
    }

    if (m_nStatus != STATUS_PLAYER || m_nModelIndex != MODEL_RHINO)
        return;

    if (CGameLogic::GameState != GAME_STATE_INITIAL || !m_pDriver || !m_pDriver->IsPlayer())
        return;

    CPad* pad = static_cast<CPlayerPed*>(m_pDriver)->GetPadFromPlayer();
    if (!pad)
        return;

    CCam& activeCam = TheCamera.GetActiveCamera();
    if (activeCam.m_nMode != MODE_CAM_ON_A_STRING) {
        m_fDoomVerticalRotation -= (pad->GetCarGunLeftRight() * CTimer::GetTimeStep() * 0.015f) / 128.0f;
        m_fDoomHorizontalRotation += (pad->GetCarGunUpDown() * CTimer::GetTimeStep() * 0.005f) / 128.0f;
    }
    else {
        CVector frontDot = Multiply3x3(activeCam.m_vecFront, GetMatrix());
        float doomVerticalRotation = atan2(-frontDot.x, frontDot.y);
        float doomHorizontalRotation = atan2(frontDot.z, frontDot.Magnitude2D()) + DegreesToRadians(15);

        if (doomVerticalRotation < m_fDoomVerticalRotation - PI)
            doomVerticalRotation = doomVerticalRotation + TWO_PI;
        else if (doomVerticalRotation > m_fDoomVerticalRotation + PI)
            doomVerticalRotation = doomVerticalRotation - TWO_PI;

        float doomVerticalRotDiff = doomVerticalRotation - m_fDoomVerticalRotation;
        float timeStep = CTimer::GetTimeStep() * 0.015f;
        if (doomVerticalRotDiff < -timeStep)
            m_fDoomVerticalRotation -= timeStep;
        else if (doomVerticalRotDiff > timeStep)
            m_fDoomVerticalRotation += timeStep;

        float doomHorizontalRotDiff = doomHorizontalRotation - m_fDoomHorizontalRotation;
        timeStep = CTimer::GetTimeStep() * 0.005f;
        if (doomHorizontalRotDiff > timeStep)
            m_fDoomHorizontalRotation += timeStep;
        else if (doomHorizontalRotDiff >= -timeStep)
            m_fDoomHorizontalRotation = doomHorizontalRotation;
        else
            m_fDoomHorizontalRotation -= timeStep;
    }

    if (m_fDoomVerticalRotation > PI)
        m_fDoomVerticalRotation -= TWO_PI;
    else if (m_fDoomVerticalRotation < -PI)
        m_fDoomVerticalRotation += TWO_PI;

    constexpr float DOOM_HORIZONTAL_ROT_MAX = DegreesToRadians(35);
    constexpr float DOOM_HORIZONTAL_ROT_MIN = -DegreesToRadians(7);

    if (m_fDoomHorizontalRotation > DOOM_HORIZONTAL_ROT_MAX) {
        m_fDoomHorizontalRotation = DOOM_HORIZONTAL_ROT_MAX;
    }
    else if (m_fDoomVerticalRotation > DegreesToRadians(90) || m_fDoomVerticalRotation < -DegreesToRadians(90)) {
        float cosDoomVerticalRot = cosf(m_fDoomVerticalRotation) * 1.3f;
        float doomHorizontalRot = -DegreesToRadians(3);
        if (cosDoomVerticalRot >= -1.0f) 
            doomHorizontalRot = DOOM_HORIZONTAL_ROT_MIN - cosDoomVerticalRot * (doomHorizontalRot - DOOM_HORIZONTAL_ROT_MIN);
        if (doomHorizontalRot > m_fDoomHorizontalRotation)
            m_fDoomHorizontalRotation = doomHorizontalRot;
    }
    else if (m_fDoomHorizontalRotation < DOOM_HORIZONTAL_ROT_MIN) {
        m_fDoomHorizontalRotation = DOOM_HORIZONTAL_ROT_MIN;
    }
    
    if (pad->CarGunJustDown()) {
        CPlayerInfo& playerInfo = CWorld::GetFocusedPlayerInfo();
        if (CTimer::GetTimeInMS() > playerInfo.m_nLastTimeBigGunFired + 800) {
            playerInfo.m_nLastTimeBigGunFired = CTimer::GetTimeInMS();
            CVector point;
            point.x = sin(-m_fDoomVerticalRotation);
            point.y = cos(m_fDoomVerticalRotation);
            point.z = sin(m_fDoomHorizontalRotation);
            point = Multiply3x3(GetMatrix(), point);

            CVector newTurretPosition;
            if (m_aCarNodes[CAR_MISC_C]) {
                RwMatrix* carNodeMiscMatrix = RwFrameGetLTM(m_aCarNodes[CAR_MISC_C]);
                newTurretPosition = *RwMatrixGetPos(carNodeMiscMatrix);
                newTurretPosition += GetSpeed(newTurretPosition - GetPosition()) * CTimer::GetTimeStep();
            }
            else {
                // unused code
                float sinVerticalDoomRot = sin(m_fDoomVerticalRotation);
                float cosVerticalDoomRot = cos(m_fDoomVerticalRotation);

                CVector doomOffset;

                doomOffset.x = TANK_SHOT_DOOM_POS.x;
                doomOffset.x += cosVerticalDoomRot * TANK_SHOT_DOOM_DISTANCE_TO_DEFAULT_TARGET.x;
                doomOffset.x -= sinVerticalDoomRot * TANK_SHOT_DOOM_DISTANCE_TO_DEFAULT_TARGET.y;

                doomOffset.y = TANK_SHOT_DOOM_POS.y;
                doomOffset.y += cosVerticalDoomRot * TANK_SHOT_DOOM_DISTANCE_TO_DEFAULT_TARGET.y;
                doomOffset.y += sinVerticalDoomRot * TANK_SHOT_DOOM_DISTANCE_TO_DEFAULT_TARGET.x;

                doomOffset.z = TANK_SHOT_DOOM_POS.z;
                doomOffset.z += TANK_SHOT_DOOM_DISTANCE_TO_DEFAULT_TARGET.z - 1.0f;

                // BUG?: This statement is not assigned to any variable.
                // It should be `newTurretPosition =  *m_matrix * doomOffset`
                *m_matrix * doomOffset;
            }

            CVector distance = newTurretPosition - GetPosition();
            CVector force = point * -0.1f * m_fMass;
            ApplyForce(force, distance, true);
            CVector endPoint = newTurretPosition + point * 60.0f;
            CWeapon::DoTankDoomAiming(this, m_pDriver, &newTurretPosition, &endPoint);

            CColPoint colPoint;
            CEntity* entity = nullptr;
            CWorld::pIgnoreEntity = this;
            CWorld::ProcessLineOfSight(
                newTurretPosition,
                endPoint,
                colPoint,
                entity,
                true,
                true,
                true,
                true,
                true,
                true,
                false,
                false
            );
            CWorld::pIgnoreEntity = nullptr;
            CVector explosionPos = endPoint;
            if (entity) 
                explosionPos = colPoint.m_vecPoint - (colPoint.m_vecPoint - newTurretPosition) * 0.04f;
            CExplosion::AddExplosion(nullptr, FindPlayerPed(), EXPLOSION_TANK_FIRE, explosionPos, 0, true, -1.0f, false);
            CVector target = explosionPos - newTurretPosition;
            g_fx.TriggerTankFire(newTurretPosition, target);
        }
    }
}

// 0x6AF110
void CAutomobile::BlowUpCarsInPath()
{
    ((void(__thiscall*)(CAutomobile*))0x6AF110)(this);
}

// 0x6AF420
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

// 0x6AF910
void CAutomobile::PopBoot()
{
    ((void(__thiscall*)(CAutomobile*))0x6AF910)(this);
}

// 0x6AFA20
void CAutomobile::CloseBoot()
{
    ((void(__thiscall*)(CAutomobile*))0x6AFA20)(this);
}

// 0x6B0690
void CAutomobile::DoHeliDustEffect(float arg0, float arg1)
{
    ((void(__thiscall*)(CAutomobile*, float, float))0x6B0690)(this, arg0, arg1);
}

// 0x6B1350
void CAutomobile::SetBumperDamage(ePanels panel, bool withoutVisualEffect)
{
    ((void(__thiscall*)(CAutomobile*, ePanels, bool))0x6B1350)(this, panel, withoutVisualEffect);
}

// 0x6B1480
void CAutomobile::SetPanelDamage(ePanels panel, bool createWindowGlass)
{
    ((void(__thiscall*)(CAutomobile*, ePanels, bool))0x6B1480)(this, panel, createWindowGlass);
}

// 0x6B1600
void CAutomobile::SetDoorDamage(eDoors door, bool withoutVisualEffect)
{
    ((void(__thiscall*)(CAutomobile*, eDoors, bool))0x6B1600)(this, door, withoutVisualEffect);
}

bool CAutomobile::RcbanditCheck1CarWheels(CPtrList& ptrlist)
{
    CColModel* colModel = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel();

    CPtrNode* next = nullptr;
    for (CPtrNode* node = ptrlist.m_node; node; node = next) {
        next = node->m_next;
        CAutomobile* vehicle = (CAutomobile*)node->m_item;
        if (node->m_item != this && vehicle->IsAutomobile()) {
            if (!ModelIndices::IsRCBandit(vehicle->m_nModelIndex) && vehicle->m_nScanCode != CWorld::ms_nCurrentScanCode)
                continue;
            CVector distance = GetPosition() - vehicle->GetPosition();
            if (distance.x < 10.0f && distance.y < 10.0f) {
                auto modelInfo = CModelInfo::GetModelInfo(vehicle->m_nModelIndex)->AsVehicleModelInfoPtr();
                for (int32 i = 0; i < 4; i++) {
                    if (m_fWheelsSuspensionCompressionPrev[i] < 1.0f || m_nStatus == STATUS_SIMPLE) {
                        static CMatrix wheelMatrix;
                        CVector wheelPos;
                        modelInfo->GetWheelPosn(i, wheelPos, false);
                        wheelMatrix = Invert(*m_matrix, wheelMatrix);

                        CColSphere sphere;
                        sphere.m_vecCenter = wheelMatrix * (*vehicle->m_matrix * wheelPos);
                        sphere.m_fRadius = modelInfo->m_fWheelSizeFront * 0.25f;
                        if (CCollision::TestSphereBox(sphere, colModel->m_boundBox))
                            return true;
                    }
                }
            }
        }
    }
    return false;
}

bool CAutomobile::RcbanditCheckHitWheels()
{
    const CVector point = GetPosition();
    float fRadius = 2.0f;
    const float minX = point.x - fRadius;
    const float maxX = point.x + fRadius;
    const float minY = point.y - fRadius;
    const float maxY = point.y + fRadius;
    int32 startSectorX = std::max(CWorld::GetSectorX(minX), 0);
    int32 startSectorY = std::max(CWorld::GetSectorY(minY), 0);
    int32 endSectorX = std::min(CWorld::GetSectorX(maxX), MAX_SECTORS_X - 1);
    int32 endSectorY = std::min(CWorld::GetSectorY(maxY), MAX_SECTORS_Y - 1);
    CWorld::IncrementCurrentScanCode();
    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            CRepeatSector* repeatSector = GetRepeatSector(sectorX, sectorY);
            if (RcbanditCheck1CarWheels(repeatSector->m_lists[REPEATSECTOR_VEHICLES]))
                break;
        }
    }
    return true;
}

void CAutomobile::FireTruckControl(CFire* fire)
{
    if (this != FindPlayerVehicle(-1, false)) {
        if (m_nStatus != STATUS_PHYSICS || !fire)
            return;
        CVector2D distance = fire->m_vecPosition - GetPosition();
        float shootDir = atan2(-distance.x, distance.y);
        float heading = GetHeading();
        if (shootDir > heading + PI)
            shootDir -= TWO_PI;
        else if (shootDir < heading - PI)   
            shootDir += TWO_PI;

        float doomVerticalRotation = shootDir - heading;
        if (doomVerticalRotation > m_fDoomVerticalRotation + PI)
            doomVerticalRotation -= TWO_PI;
        else if (doomVerticalRotation < m_fDoomVerticalRotation - PI)
            doomVerticalRotation += TWO_PI;

        float doomVertialRotDiff = doomVerticalRotation - m_fDoomVerticalRotation;
        float timeStep = CTimer::GetTimeStep() * 0.01f;
        if (fabs(doomVertialRotDiff) >= timeStep) {
            if (doomVertialRotDiff <= 0.0f)
                m_fDoomVerticalRotation -= timeStep;
            else
                m_fDoomVerticalRotation += timeStep;
        }
        m_fDoomHorizontalRotation = sin((CTimer::GetTimeInMS() & 0xFFF) * TWO_PI * 0.00024414f) * 0.15f;
    }
    else {
        CCam& activeCam = TheCamera.GetActiveCamera();
        if (activeCam.m_nMode != MODE_CAM_ON_A_STRING)
        {
            CPad* pad = CPad::GetPad(0);
            m_fDoomVerticalRotation -= (pad->GetCarGunLeftRight() * CTimer::GetTimeStep() * 0.05f) / 128.0f;
            m_fDoomHorizontalRotation += (pad->GetCarGunUpDown() * CTimer::GetTimeStep() * 0.02f) / 128.0f;
        }
        else {
            CVector frontDot = Multiply3x3(activeCam.m_vecFront, GetMatrix());
            float doomVerticalRotation = atan2(-frontDot.x, frontDot.y);
            float doomHorizontalRotation = atan2(frontDot.z, frontDot.Magnitude2D());

            if (ModelIndices::IsSwatVan(m_nModelIndex))
                doomHorizontalRotation += DegreesToRadians(22);
            else
                doomHorizontalRotation += DegreesToRadians(15);

            if (doomVerticalRotation > m_fDoomVerticalRotation + PI)
                doomVerticalRotation -= TWO_PI;
            else if (doomVerticalRotation < m_fDoomVerticalRotation - PI)
                doomVerticalRotation += TWO_PI;

            float doomVerticalRotDiff = doomVerticalRotation - m_fDoomVerticalRotation;
            float timeStep = CTimer::GetTimeStep() * 0.05f;
            if (doomVerticalRotDiff > timeStep)
                m_fDoomVerticalRotation += timeStep;
            else if (doomVerticalRotDiff < -timeStep)
                m_fDoomVerticalRotation -= timeStep;

            float doomHorizontalRotDiff = doomHorizontalRotation - m_fDoomHorizontalRotation;
            timeStep = CTimer::GetTimeStep() * 0.02f;
            if (doomHorizontalRotDiff > timeStep)
                m_fDoomHorizontalRotation += timeStep;
            else if (doomHorizontalRotDiff < -timeStep)
                m_fDoomHorizontalRotation -= timeStep;
        }

        if (m_fDoomVerticalRotation > PI)
            m_fDoomVerticalRotation -= TWO_PI;
        else if (m_fDoomVerticalRotation < -PI)
            m_fDoomVerticalRotation += TWO_PI;

        if (ModelIndices::IsSwatVan(m_nModelIndex))
            m_fDoomHorizontalRotation = clamp<float>(m_fDoomHorizontalRotation, -DegreesToRadians(10), DegreesToRadians(35));
        else
            m_fDoomHorizontalRotation = clamp<float>(m_fDoomHorizontalRotation, -DegreesToRadians(20), DegreesToRadians(20));
        if (!CPad::GetPad(0)->GetCarGunFired())
            return;
    }

    CVector newTurretPosition;
    if (m_aCarNodes[CAR_MISC_A]) {
        RwMatrix* carNodeMiscMatrix = RwFrameGetLTM(m_aCarNodes[CAR_MISC_A]);
        newTurretPosition = *RwMatrixGetPos(carNodeMiscMatrix);
    }
    else {
        newTurretPosition = *m_matrix * CVector(0.0f, 1.5f, 1.8f);
    }

    CVector point;
    float cosHorizontalDoomRot = cos(m_fDoomHorizontalRotation);
    point.x = -(sin(m_fDoomVerticalRotation) * cosHorizontalDoomRot);
    point.y = cos(m_fDoomVerticalRotation) * cosHorizontalDoomRot;
    point.z = sin(m_fDoomHorizontalRotation);
    point = Multiply3x3(GetMatrix(), point);

    if (m_aCarNodes[CAR_MISC_A]) {
        if (ModelIndices::IsSwatVan(m_nModelIndex))
            newTurretPosition += point * 2.0f;
        else
            newTurretPosition += point * 1.2f;

        newTurretPosition += GetSpeed(newTurretPosition - GetPosition()) * CTimer::GetTimeStep();
    }

    point.z += (rand() % 16) * 0.001f;
    CVector endPoint = m_vecMoveSpeed * CVector(1.0f, 1.0f, 0.3f);
    if (ModelIndices::IsSwatVan(m_nModelIndex))
        endPoint += point * 0.4f;
    else
        endPoint += point * 0.5f;
    CWaterCannons::UpdateOne((uint32)this, &newTurretPosition, &endPoint);
}

// 0x44D520
bool CAutomobile::HasCarStoppedBecauseOfLight()
{
    return ((bool(__thiscall*)(CAutomobile*))0x44D520)(this);
}

// 0x6A3440
void CAutomobile::Fix() {
    Fix_Reversed();
}

void CAutomobile::Fix_Reversed() {
    plugin::CallMethod<0x6A3440, CAutomobile*>(this);
}

// 0x6A0750
RwObject* GetCurrentAtomicObjectCB(RwObject* object, void* data)
{
    if (RpAtomicGetFlags(object) & rpATOMICRENDER)
        *reinterpret_cast<RpAtomic**>(data) = reinterpret_cast<RpAtomic*>(object);

    return object;
}
