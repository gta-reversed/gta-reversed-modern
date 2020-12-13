/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"


void CBike::InjectHooks()
{
    ReversibleHooks::Install("CBike", "ProcessBuoyancy", 0x6B5FB0, &CBike::ProcessBuoyancy);
}

// Converted from void CBike::ProcessAI(uint &) 0x0
void CBike::ProcessAI(unsigned int& arg0) {
    ((void(__thiscall*)(CBike*, unsigned int&))(*(void***)this)[66])(this, arg0);
}

// Converted from thiscall void CBike::SetupModelNodes(void) 0x6B5960
void CBike::SetupModelNodes() {
    ((void(__thiscall*)(CBike*))0x6B5960)(this);
}

// Converted from thiscall void CBike::dmgDrawCarCollidingParticles(CVector const& position,float power,eWeaponType weaponType) 0x6B5A00
void CBike::dmgDrawCarCollidingParticles(CVector const& position, float power, eWeaponType weaponType) {
    ((void(__thiscall*)(CBike*, CVector const&, float, eWeaponType))0x6B5A00)(this, position, power, weaponType);
}

// Converted from cdecl bool CBike::DamageKnockOffRider(CVehicle *,float,ushort,CEntity *,CVector &,CVector &) 0x6B5A10
bool CBike::DamageKnockOffRider(CVehicle* arg0, float arg1, unsigned short arg2, CEntity* arg3, CVector& arg4, CVector& arg5) {
    return ((bool(__cdecl*)(CVehicle*, float, unsigned short, CEntity*, CVector&, CVector&))0x6B5A10)(arg0, arg1, arg2, arg3, arg4, arg5);
}

// Converted from thiscall CPed* CBike::KnockOffRider(eWeaponType,uchar,CPed *,bool) 0x6B5F40
CPed* CBike::KnockOffRider(eWeaponType arg0, unsigned char arg1, CPed* arg2, bool arg3) {
    return ((CPed * (__thiscall*)(CBike*, eWeaponType, unsigned char, CPed*, bool))0x6B5F40)(this, arg0, arg1, arg2, arg3);
}

// Converted from thiscall void CBike::SetRemoveAnimFlags(CPed *ped) 0x6B5F50
void CBike::SetRemoveAnimFlags(CPed* ped) {
    ((void(__thiscall*)(CBike*, CPed*))0x6B5F50)(this, ped);
}

// Converted from thiscall void CBike::ReduceHornCounter(void) 0x6B5F90
void CBike::ReduceHornCounter() {
    ((void(__thiscall*)(CBike*))0x6B5F90)(this);
}

// Converted from thiscall void CBike::ProcessBuoyancy(void) 0x6B5FB0
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

    auto fTimeStep = std::max(0.01F, CTimer::ms_fTimeStep);
    auto fUsedMass = m_fMass / 125.0F;
    auto fBuoyancyForceZ = vecBuoyancyForce.z / (fTimeStep * fUsedMass);

    if (fUsedMass > m_fBuoyancyConstant)
        fBuoyancyForceZ *= 1.05F * fUsedMass / m_fBuoyancyConstant;

    if (physicalFlags.bMakeMassTwiceAsBig)
        fBuoyancyForceZ *= 1.5F;

    auto fBuoyancyForceMult = std::max(0.5F, 1.0F - fBuoyancyForceZ / 20.0F);
    auto fSpeedMult = pow(fBuoyancyForceMult, CTimer::ms_fTimeStep);
    m_vecMoveSpeed *= fSpeedMult;
    m_vecTurnSpeed *= fSpeedMult;

    if (fBuoyancyForceZ > 0.8F
        || (fBuoyancyForceZ > 0.4F && IsAnyWheelNotMakingContactWithGround())) {

        vehicleFlags.bIsDrowning = true;
        physicalFlags.bSubmergedInWater = true;

        m_vecMoveSpeed.z = std::max(-0.1F, m_vecMoveSpeed.z);

        auto pDriver = static_cast<CPed*>(m_pDriver);
        if (pDriver) {
            ProcessPedInVehicleBuoyancy(pDriver, true);
        }
        else {
            vehicleFlags.bEngineOn = false;
        }

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

inline void CBike::ProcessPedInVehicleBuoyancy(CPed* pPed, bool bIsDriver)
{
    if (!pPed)
        return;

    pPed->physicalFlags.bTouchingWater = true;
    if (!pPed->IsPlayer() && damageFlags.bIgnoreWater)
        return;

    if (pPed->IsPlayer())
        static_cast<CPlayerPed*>(pPed)->HandlePlayerBreath(true, 1.0F);

    if (IsAnyWheelMakingContactWithGround()) {
        if (!pPed->IsPlayer()) {
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
        auto knockOffBikeEvent = CEventKnockOffBike(this, &m_vecMoveSpeed, &m_vecLastCollisionImpactVelocity, m_fDamageIntensity,
            0.0F, eKnockOffType::KNOCK_OFF_TYPE_FALL, 0, 0, nullptr, bIsDriver, false);

        pPed->GetEventGroup().Add(&knockOffBikeEvent, false);
        if (bIsDriver)
            vehicleFlags.bEngineOn = false;
    }
}

// Converted from thiscall void CBike::ResetSuspension(void) 0x6B6740
void CBike::ResetSuspension() {
    ((void(__thiscall*)(CBike*))0x6B6740)(this);
}

// Converted from thiscall bool CBike::GetAllWheelsOffGround(void) 0x6B6790
bool CBike::GetAllWheelsOffGround() {
    return ((bool(__thiscall*)(CBike*))0x6B6790)(this);
}

// Converted from thiscall void CBike::DebugCode(void) 0x6B67A0
void CBike::DebugCode() {
    ((void(__thiscall*)(CBike*))0x6B67A0)(this);
}

// Converted from thiscall void CBike::DoSoftGroundResistance(uint &) 0x6B6D40
void CBike::DoSoftGroundResistance(unsigned int& arg0) {
    ((void(__thiscall*)(CBike*, unsigned int&))0x6B6D40)(this, arg0);
}

// Converted from thiscall void CBike::PlayHornIfNecessary(void) 0x6B7130
void CBike::PlayHornIfNecessary() {
    ((void(__thiscall*)(CBike*))0x6B7130)(this);
}

// Converted from thiscall void CBike::CalculateLeanMatrix(void) 0x6B7150
void CBike::CalculateLeanMatrix() {
    ((void(__thiscall*)(CBike*))0x6B7150)(this);
}

// Converted from cdecl void CBike::ProcessRiderAnims(CPed *rider,CVehicle *vehicle,CRideAnimData *rideData,tBikeHandlingData *handling) 0x6B7280
void CBike::ProcessRiderAnims(CPed* rider, CVehicle* vehicle, CRideAnimData* rideData, tBikeHandlingData* handling) {
    ((void(__cdecl*)(CPed*, CVehicle*, CRideAnimData*, tBikeHandlingData*))0x6B7280)(rider, vehicle, rideData, handling);
}

// Converted from thiscall void CBike::FixHandsToBars(CPed *rider) 0x6B7F90
void CBike::FixHandsToBars(CPed* rider) {
    ((void(__thiscall*)(CBike*, CPed*))0x6B7F90)(this, rider);
}

// Converted from thiscall void CBike::PlaceOnRoadProperly(void) 0x6BEEB0
void CBike::PlaceOnRoadProperly() {
    ((void(__thiscall*)(CBike*))0x6BEEB0)(this);
}

// Converted from thiscall void CBike::GetCorrectedWorldDoorPosition(CVector &out,CVector,CVector) 0x6BF230
void CBike::GetCorrectedWorldDoorPosition(CVector& out, CVector arg1, CVector arg2) {
    ((void(__thiscall*)(CBike*, CVector&, CVector, CVector))0x6BF230)(this, out, arg1, arg2);
}

// Converted from thiscall void CBike::CBike(int modelIndex,uchar createdBy) 0x6BF430
/*
CBike::CBike(int modelIndex, unsigned char createdBy) : CVehicle(plugin::dummy) {
    ((void(__thiscall*)(CBike*, int, unsigned char))0x6BF430)(this, modelIndex, createdBy);
}
*/
