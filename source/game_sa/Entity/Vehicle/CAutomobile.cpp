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
    ReversibleHooks::Install("CAutomobile", "ProcessBuoyancy", 0x6A8C00, &CAutomobile::ProcessBuoyancy);
}

CAutomobile::CAutomobile(int modelIndex, unsigned char createdBy, bool setupSuspensionLines) : CVehicle(plugin::dummy) {
    ((void(__thiscall*)(CAutomobile*, int, unsigned char, bool))0x6B0A90)(this, modelIndex, createdBy, setupSuspensionLines);
}


CVector* CAutomobile::AddMovingCollisionSpeed(CVector* out, CVector& vecSpeed)
{
    return ((CVector * (__thiscall*)(CVehicle*, CVector*, CVector&))(*(void***)this)[49])(this, out, vecSpeed);
}

// Converted from void CAutomobile::ProcessAI(uint &) 0x0
bool CAutomobile::ProcessAI(unsigned int& arg0)
{
    return ((bool(__thiscall*)(CAutomobile*, unsigned int&))(*(void***)this)[66])(this, arg0);
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

// Converted from void CAutomobile::ProcessSuspension(void) 0x0
void CAutomobile::ProcessSuspension()
{
    ((void(__thiscall*)(CAutomobile*))(*(void***)this)[70])(this);
}

// Converted from thiscall void CAutomobile::SetupModelNodes(void) 0x6A0770
void CAutomobile::SetupModelNodes()
{
    ((void(__thiscall*)(CAutomobile*))0x6A0770)(this);
}

// Converted from thiscall void CAutomobile::HydraulicControl(void) 0x6A07A0
void CAutomobile::HydraulicControl()
{
    ((void(__thiscall*)(CAutomobile*))0x6A07A0)(this);
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
    RwFrame* frame = reinterpret_cast<RwFrame*>(rwObjectGetParent(m_pRwObject));
    RwMatrix* rwMatrix = RwFrameGetMatrix(frame);
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

// Converted from thiscall void CAutomobile::ProcessCarWheelPair(int, int, float, CVector *, CVector *, float, float, float, bool) 0x6A4EC0
void CAutomobile::ProcessCarWheelPair(int arg0, int arg1, float arg2, CVector* arg3, CVector* arg4, float arg5, float arg6, float arg7, bool arg8)
{
    ((void(__thiscall*)(CAutomobile*, int, int, float, CVector*, CVector*, float, float, float, bool))0x6A4EC0)(this, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
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

// Converted from thiscall void CAutomobile::ProcessCarOnFireAndExplode(uchar) 0x6A7090
void CAutomobile::ProcessCarOnFireAndExplode(unsigned char arg0)
{
    ((void(__thiscall*)(CAutomobile*, unsigned char))0x6A7090)(this, arg0);
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
                CVector vecSpeed;
                GetSpeed(&vecSpeed, vecWaterImpactVelocity);
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
    ((void(__thiscall*)(CAutomobile*))0x6AF420)(this);
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
