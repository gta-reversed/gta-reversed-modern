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
    ReversibleHooks::Install("CAutomobile", "HydraulicControl", 0x6A07A0, &CAutomobile::HydraulicControl);
    ReversibleHooks::Install("CAutomobile", "ProcessBuoyancy", 0x6A8C00, &CAutomobile::ProcessBuoyancy);
    ReversibleHooks::Install("CAutomobile", "PlaceOnRoadProperly", 0x6AF420, &CAutomobile::PlaceOnRoadProperly);
    ReversibleHooks::Install("CAutomobile", "ProcessCarWheelPair", 0x6A4EC0, &CAutomobile::ProcessCarWheelPair);
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
            else if (!handlingFlags.bNosInst&& gHandlingDataMgr.HasRearWheelDrive(m_pHandlingData->m_nVehicleId))
            {
                traction *= m_fNitroValue;
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
            brakeBias = neutralHandling ? 1.0f : 2.0f - 2.0f * m_pHandlingData->m_fBrakeBias;
            tractionBias = neutralHandling ? 1.0f : 2.0f - 2.0f * m_pHandlingData->m_fTractionBias;
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
            m_wheelColPoint[leftWheel].m_nSurfaceTypeA =  SURFACE_WHEELBASE;
            float adhesion = g_surfaceInfos->GetAdhesiveLimit(&m_wheelColPoint[leftWheel]) * traction;
            if (m_nStatus != STATUS_PLAYER)
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
            if (m_damageManager.GetWheelStatus(leftWheel) == WHEEL_STATUS_BURST)
            {
                adhesion *= m_damageManager.m_fWheelDamageEffect * tractionBias;
                brake *= brakeBias;
                CVehicle::ProcessWheel(wheelFwd, wheelRight, contactSpeeds[leftWheel], contactPoints[leftWheel], m_nNumContactWheels,
                    thrust, brake, adhesion, leftWheel, &m_wheelRotationUnused[leftWheel], &wheelState, WHEEL_STATUS_BURST);
            }
            else
            {
                adhesion *= tractionBias;
                brake *= brakeBias;
                CVehicle::ProcessWheel(wheelFwd, wheelRight, contactSpeeds[leftWheel], contactPoints[leftWheel], m_nNumContactWheels,
                    thrust, brake, adhesion, leftWheel, &m_wheelRotationUnused[leftWheel], &wheelState, WHEEL_STATUS_OK);
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
            if (m_damageManager.GetWheelStatus(rightWheel) == WHEEL_STATUS_BURST)
            {
                adhesion *= m_damageManager.m_fWheelDamageEffect * tractionBias;
                brake *= brakeBias;
                CVehicle::ProcessWheel(wheelFwd, wheelRight, contactSpeeds[rightWheel], contactPoints[rightWheel], m_nNumContactWheels,
                    thrust, brake, adhesion, rightWheel, &m_wheelRotationUnused[rightWheel], &wheelState, WHEEL_STATUS_BURST);
            }
            else
            {
                adhesion *= tractionBias;
                brake *= brakeBias;
                CVehicle::ProcessWheel(wheelFwd, wheelRight, contactSpeeds[rightWheel], contactPoints[rightWheel], m_nNumContactWheels,
                    thrust, brake, adhesion, rightWheel, &m_wheelRotationUnused[rightWheel], &wheelState, WHEEL_STATUS_OK);
            }
            if (driveWheels && m_fGasPedal < 0.0f && wheelState == WHEEL_STATE_SPINNING)
                m_aWheelState[rightWheel] = WHEEL_STATE_NORMAL;
            else
                m_aWheelState[rightWheel] = wheelState;
        }
    }
    if (!bFront && !handlingFlags.bNosInst && m_doingBurnout && driveWheels) {
        if (m_aWheelState[CARWHEEL_REAR_LEFT] == WHEEL_STATE_SPINNING ||
            m_aWheelState[CARWHEEL_REAR_RIGHT] == WHEEL_STATE_SPINNING)
        {
            m_fNitroValue += CTimer::ms_fTimeStep * 0.001f;
            m_fNitroValue = std::min(m_fNitroValue, 3.0f);
        }
        else if (m_fNitroValue > 1.0f) {
            m_fNitroValue = std::powf(0.995f, CTimer::ms_fTimeStep) * m_fNitroValue - 1.0f + 1.0f;
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
        static_cast<CPlane*>(this)->field_9A4 = CGeneral::GetATanOfXY(GetForward().x, GetForward().y);
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
