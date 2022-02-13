/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "Bike.h"

#include "Buoyancy.h"

void CBike::InjectHooks() {
    RH_ScopedClass(CBike);
    RH_ScopedCategory("Vehicle/Ped");

    // RH_ScopedInstall(Constructor, 0x6BF430);
    RH_ScopedInstall(Destructor, 0x6B57A0);
    RH_ScopedInstall(dmgDrawCarCollidingParticles, 0x6B5A00);
    // RH_ScopedInstall(DamageKnockOffRider, 0x6B5A10);
    RH_ScopedInstall(KnockOffRider, 0x6B5F40);
    // RH_ScopedInstall(SetRemoveAnimFlags, 0x6B5F50);
    RH_ScopedInstall(ReduceHornCounter, 0x6B5F90);
    // RH_ScopedInstall(ProcessAI, 0x6BC930);
    RH_ScopedInstall(ProcessBuoyancy, 0x6B5FB0);
    // RH_ScopedInstall(ResetSuspension, 0x6B6740);
    RH_ScopedInstall(GetAllWheelsOffGround, 0x6B6790);
    RH_ScopedInstall(DebugCode, 0x6B67A0);
    // RH_ScopedInstall(DoSoftGroundResistance, 0x6B6D40);
    RH_ScopedInstall(PlayHornIfNecessary, 0x6B7130);
    RH_ScopedInstall(CalculateLeanMatrix, 0x6B7150);
    // RH_ScopedInstall(ProcessRiderAnims, 0x6B7280);
    // RH_ScopedInstall(FixHandsToBars, 0x6B7F90);
    // RH_ScopedInstall(PlaceOnRoadProperly, 0x6BEEB0);
    // RH_ScopedInstall(GetCorrectedWorldDoorPosition, 0x6BF230);
    RH_ScopedInstall(Fix_Reversed, 0x6B7050);
    // RH_ScopedInstall(BlowUpCar_Reversed, 0x6BEA10);
    RH_ScopedInstall(ProcessDrivingAnims_Reversed, 0x6BF400);
    // RH_ScopedInstall(BurstTyre_Reversed, 0x6BEB20);
    // RH_ScopedInstall(ProcessControlInputs_Reversed, 0x6BE310);
    // RH_ScopedInstall(ProcessEntityCollision_Reversed, 0x6BDEA0);
    RH_ScopedInstall(Render_Reversed, 0x6BDE20);
    // RH_ScopedInstall(PreRender_Reversed, 0x6BD090);
    RH_ScopedInstall(Teleport_Reversed, 0x6BCFC0);
    // RH_ScopedInstall(ProcessControl_Reversed, 0x6B9250);
    // RH_ScopedInstall(VehicleDamage_Reversed, 0x6B8EC0);
    // RH_ScopedInstall(SetupSuspensionLines_Reversed, 0x6B89B0);
    RH_ScopedInstall(SetModelIndex_Reversed, 0x6B8970);
    // RH_ScopedInstall(PlayCarHorn_Reversed, 0x6B7080);
    RH_ScopedInstall(SetupDamageAfterLoad_Reversed, 0x6B7070);
    // RH_ScopedInstall(DoBurstAndSoftGroundRatios_Reversed, 0x6B6950);
    // RH_ScopedInstall(SetUpWheelColModel_Reversed, 0x6B67E0);
    RH_ScopedInstall(RemoveRefsToVehicle_Reversed, 0x6B67B0);
    // RH_ScopedInstall(ProcessControlCollisionCheck_Reversed, 0x6B6620);
    RH_ScopedInstall(GetComponentWorldPosition_Reversed, 0x6B5990);
    RH_ScopedInstall(ProcessOpenDoor_Reversed, 0x6B58D0);
}

// 0x6BF430
CBike::CBike(int32 modelIndex, eVehicleCreatedBy createdBy) : CVehicle(plugin::dummy) {
    plugin::CallMethod<0x6BF430, CBike*, int32, eVehicleCreatedBy>(this, modelIndex, createdBy);
}

// 0x6B57A0
CBike::~CBike() {
    m_vehicleAudio.Terminate();
}

// 0x6B5A00
void CBike::dmgDrawCarCollidingParticles(const CVector& position, float power, eWeaponType weaponType) {
    // NOP
}

// 0x6B5A10
bool CBike::DamageKnockOffRider(CVehicle* arg0, float arg1, uint16 arg2, CEntity* arg3, CVector& arg4, CVector& arg5) {
    return ((bool(__cdecl*)(CVehicle*, float, uint16, CEntity*, CVector&, CVector&))0x6B5A10)(arg0, arg1, arg2, arg3, arg4, arg5);
}

// dummy function
// 0x6B5F40
CPed* CBike::KnockOffRider(eWeaponType arg0, uint8 arg1, CPed* ped, bool arg3) {
    return ped;
}

// 0x6B5F50
void CBike::SetRemoveAnimFlags(CPed* ped) {
    ((void(__thiscall*)(CBike*, CPed*))0x6B5F50)(this, ped);
}

// 0x6B5F90
void CBike::ReduceHornCounter() {
    if (m_nHornCounter)
        m_nHornCounter -= 1;
}

// 0x6B5FB0
void CBike::ProcessBuoyancy() {
    CVector vecBuoyancyTurnPoint;
    CVector vecBuoyancyForce;
    if (!mod_Buoyancy.ProcessBuoyancy(this, m_fBuoyancyConstant, &vecBuoyancyTurnPoint, &vecBuoyancyForce)) {
        vehicleFlags.bIsDrowning = false;
        physicalFlags.bSubmergedInWater = false;
        physicalFlags.bTouchingWater = false;
        return;
    }

    physicalFlags.bTouchingWater = true;
    ApplyMoveForce(vecBuoyancyForce);
    ApplyTurnForce(vecBuoyancyForce, vecBuoyancyTurnPoint);

    auto fTimeStep = std::max(0.01F, CTimer::GetTimeStep());
    auto fUsedMass = m_fMass / 125.0F;
    auto fBuoyancyForceZ = vecBuoyancyForce.z / (fTimeStep * fUsedMass);

    if (fUsedMass > m_fBuoyancyConstant)
        fBuoyancyForceZ *= 1.05F * fUsedMass / m_fBuoyancyConstant;

    if (physicalFlags.bMakeMassTwiceAsBig)
        fBuoyancyForceZ *= 1.5F;

    auto fBuoyancyForceMult = std::max(0.5F, 1.0F - fBuoyancyForceZ / 20.0F);
    auto fSpeedMult = pow(fBuoyancyForceMult, CTimer::GetTimeStep());
    m_vecMoveSpeed *= fSpeedMult;
    m_vecTurnSpeed *= fSpeedMult;

    if (fBuoyancyForceZ > 0.8F
        || (fBuoyancyForceZ > 0.4F && IsAnyWheelNotMakingContactWithGround())) {

        vehicleFlags.bIsDrowning = true;
        physicalFlags.bSubmergedInWater = true;

        m_vecMoveSpeed.z = std::max(-0.1F, m_vecMoveSpeed.z);

        auto driver = m_pDriver->AsPed();
        if (driver) {
            ProcessPedInVehicleBuoyancy(driver, true);
        }
        else {
            vehicleFlags.bEngineOn = false;
        }

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

inline void CBike::ProcessPedInVehicleBuoyancy(CPed* ped, bool bIsDriver)
{
    if (!ped)
        return;

    ped->physicalFlags.bTouchingWater = true;
    if (!ped->IsPlayer() && bikeFlags.bIgnoreWater)
        return;

    if (ped->IsPlayer())
        ped->AsPlayer()->HandlePlayerBreath(true, 1.0F);

    if (IsAnyWheelMakingContactWithGround()) {
        if (!ped->IsPlayer()) {
            auto pedDamageResponseCalc = CPedDamageResponseCalculator(this, CTimer::GetTimeStep(), eWeaponType::WEAPON_DROWNING, PED_PIECE_TORSO, false);
            auto damageEvent = CEventDamage(this, CTimer::GetTimeInMS(), eWeaponType::WEAPON_DROWNING, PED_PIECE_TORSO, 0, false, true);
            if (damageEvent.AffectsPed(ped))
                pedDamageResponseCalc.ComputeDamageResponse(ped, &damageEvent.m_damageResponse, true);
            else
                damageEvent.m_damageResponse.m_bDamageCalculated = true;

            ped->GetEventGroup().Add(&damageEvent, false);
        }
    }
    else {
        auto knockOffBikeEvent = CEventKnockOffBike(
            this,
            &m_vecMoveSpeed,
            &m_vecLastCollisionImpactVelocity,
            m_fDamageIntensity,
            0.0F,
            KNOCK_OFF_TYPE_FALL,
            0,
            0,
            nullptr,
            bIsDriver,
            false
        );

        ped->GetEventGroup().Add(&knockOffBikeEvent, false);
        if (bIsDriver)
            vehicleFlags.bEngineOn = false;
    }
}

// 0x6BC930
bool CBike::ProcessAI(uint32& extraHandlingFlags) {
    return plugin::CallMethodAndReturn<bool, 0x6BC930, CBike*, uint32&>(this, extraHandlingFlags);
}

// 0x6BF400
void CBike::ProcessDrivingAnims(CPed* driver, uint8 bBlend) {
    if (m_bOffscreen && m_nStatus == STATUS_PLAYER)
        return;

    ProcessRiderAnims(driver, this, &m_rideAnimData, m_pBikeHandlingData, 0);
}

// 0x6B7280
void CBike::ProcessRiderAnims(CPed* rider, CVehicle* vehicle, CRideAnimData* rideData, tBikeHandlingData* handling, int16 a5) {
    plugin::Call<0x6B7280, CPed*, CVehicle*, CRideAnimData*, tBikeHandlingData*, int16>(rider, vehicle, rideData, handling, a5);
}

// 0x6BEB20
bool CBike::BurstTyre(uint8 tyreComponentId, bool bPhysicalEffect) {
    return plugin::CallMethodAndReturn<bool, 0x6BEB20, CBike*, uint8, bool>(this, tyreComponentId, bPhysicalEffect);
}

// 0x6BE310
void CBike::ProcessControlInputs(uint8 playerNum) {
    plugin::CallMethod<0x6BE310, CBike*, uint8>(this, playerNum);
}

// 0x6BDEA0
int32 CBike::ProcessEntityCollision(CEntity* entity, CColPoint* colPoint) {
    return plugin::CallMethodAndReturn<int32, 0x6BDEA0, CBike*, CEntity*, CColPoint*>(this, entity, colPoint);
}

// 0x6B9250
void CBike::ProcessControl() {
    plugin::CallMethod<0x6B9250, CBike*>(this);
}

// 0x6B6740
void CBike::ResetSuspension() {
    ((void(__thiscall*)(CBike*))0x6B6740)(this);
}

// 0x6B6790
bool CBike::GetAllWheelsOffGround() const {
    return m_nNumWheelsOnGround == 0;
}

// 0x6B67A0
void CBike::DebugCode() {
    // NOP
}

// 0x6B6D40
void CBike::DoSoftGroundResistance(uint32& arg0) {
    ((void(__thiscall*)(CBike*, uint32&))0x6B6D40)(this, arg0);
}

// 0x6B7130
void CBike::PlayHornIfNecessary() {
    if (m_autoPilot.carCtrlFlags.bHonkAtCar || m_autoPilot.carCtrlFlags.bHonkAtPed)
        PlayCarHorn();
}

// 0x6B7150
void CBike::CalculateLeanMatrix() {
    if (m_bLeanMatrixCalculated)
        return;

    CMatrix mat;
    mat.SetRotateX(fabs(m_rideAnimData.m_fAnimLean) * -0.05f);
    mat.RotateY(m_rideAnimData.m_fAnimLean);
    m_mLeanMatrix = GetMatrix();
    m_mLeanMatrix = m_mLeanMatrix * mat;
    // place wheel back on ground
    m_mLeanMatrix.GetPosition() += GetUp() * (1.0f - cos(m_rideAnimData.m_fAnimLean)) * GetColModel()->GetBoundingBox().m_vecMin.z;
    m_bLeanMatrixCalculated = true;
}

// 0x6B7F90
void CBike::FixHandsToBars(CPed* rider) {
    ((void(__thiscall*)(CBike*, CPed*))0x6B7F90)(this, rider);
}

// 0x6BEEB0
void CBike::PlaceOnRoadProperly() {
    ((void(__thiscall*)(CBike*))0x6BEEB0)(this);
}

// 0x6BF230
void CBike::GetCorrectedWorldDoorPosition(CVector& out, CVector arg1, CVector arg2) {
    ((void(__thiscall*)(CBike*, CVector&, CVector, CVector))0x6BF230)(this, out, arg1, arg2);
}

// 0x6BEA10
void CBike::BlowUpCar(CEntity* damager, uint8 bHideExplosion) {
    plugin::CallMethod<0x6BEA10, CBike*, CEntity*, uint8>(this, damager, bHideExplosion);
}

// 0x6B7050
void CBike::Fix() {
    vehicleFlags.bIsDamaged = false;
    bikeFlags.bIsOnFire = false;
    m_anWheelDamageState[0] = 0;
    m_anWheelDamageState[1] = 0;
}

// 0x6BD090
void CBike::PreRender() {
    plugin::CallMethod<0x6BD090, CBike*>(this);
}

// 0x6BDE20
void CBike::Render() {
    auto savedRef = 0;
    RwRenderStateGet(rwRENDERSTATEALPHATESTFUNCTIONREF, &savedRef);
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, RWRSTATE(1));

    m_nTimeTillWeNeedThisCar = CTimer::GetTimeInMS() + 3000;
    CVehicle::Render();

    if (m_renderLights.m_bRightFront) {
        CalculateLeanMatrix();
        CVehicle::DoHeadLightBeam(0, m_mLeanMatrix, true);
    }

    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, RWRSTATE(savedRef));
}

// 0x6BCFC0
void CBike::Teleport(CVector destination, bool resetRotation) {
    CWorld::Remove(this);

    GetPosition() = destination;
    if (resetRotation)
        SetOrientation(0.0f, 0.0f, 0.0f);

    ResetMoveSpeed();
    ResetTurnSpeed();
    ResetSuspension();

    CWorld::Add(this);
}

// 0x6B8EC0
void CBike::VehicleDamage(float damageIntensity, uint16 collisionComponent, CEntity* damager, CVector* vecCollisionCoors, CVector* vecCollisionDirection, eWeaponType weapon) {
    plugin::CallMethod<0x6B8EC0, CBike*, float, uint16, CEntity*, CVector*, CVector*, eWeaponType>(this, damageIntensity, collisionComponent, damager, vecCollisionCoors, vecCollisionDirection, weapon);
}

// 0x6B89B0
void CBike::SetupSuspensionLines() {
    plugin::CallMethod<0x6B89B0, CBike*>(this);
}

// 0x6B8970
void CBike::SetModelIndex(uint32 index) {
    CVehicle::SetModelIndex(index);
    SetupModelNodes();
}

// 0x6B5960
void CBike::SetupModelNodes() {
    std::ranges::fill(m_aBikeNodes, nullptr);
    CClumpModelInfo::FillFrameArray(m_pRwClump, m_aBikeNodes);
}

// 0x6B7080
void CBike::PlayCarHorn() {
    plugin::CallMethod<0x6B7080, CBike*>(this);
}

// 0x6B7070
void CBike::SetupDamageAfterLoad() {
    // NOP
}

// 0x6B6950
void CBike::DoBurstAndSoftGroundRatios() {
    plugin::CallMethod<0x6B6950, CBike*>(this);
}

// 0x6B67E0
bool CBike::SetUpWheelColModel(CColModel* wheelCol) {
    return plugin::CallMethodAndReturn<bool, 0x6B67E0, CBike*, CColModel*>(this, wheelCol);
}

// 0x6B67B0
void CBike::RemoveRefsToVehicle(CEntity* entityToRemove) {
    for (auto& entity: m_apWheelCollisionEntity) {
        if (entity == entityToRemove)
            entity = nullptr;
    }
}

// 0x6B6620
void CBike::ProcessControlCollisionCheck(bool applySpeed) {
    plugin::CallMethod<0x6B6620, CBike*, bool>(this, applySpeed);
}

// 0x6B5990
void CBike::GetComponentWorldPosition(int32 componentId, CVector& outPos) {
    if (IsComponentPresent(componentId))
        outPos = RwFrameGetLTM(m_aBikeNodes[componentId])->pos;
    else
        printf("BikeNode missing: %d %d\n", m_nModelIndex, componentId);
}

// 0x6B58D0
void CBike::ProcessOpenDoor(CPed* ped, uint32 doorComponentId, uint32 animGroup, uint32 animId, float fTime) {
    // NOP
}
