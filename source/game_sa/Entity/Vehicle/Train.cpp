/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "Train.h"

#include "Buoyancy.h"
#include "CarCtrl.h"

uint32& CTrain::GenTrain_Track = *(uint32*)0xC37FFC;
uint32& CTrain::GenTrain_TrainConfig = *(uint32*)0xC38000;
uint8& CTrain::GenTrain_Direction = *(uint8*)0xC38004;
uint32& CTrain::GenTrain_GenerationNode = *(uint32*)0xC38008;
uint32& CTrain::GenTrain_Status = *(uint32*)0xC3800C;
bool& CTrain::bDisableRandomTrains = *(bool*)0xC38010;
CVector (&CTrain::aStationCoors)[6] = *(CVector(*)[6])0x8D48F8; /*{ // 0x8D48F8
    CVector{ 1741.0f, -1954.0f, 15.0f },
    CVector{ 1297.0f, -1898.0f, 3.0f  },
    CVector{ -1945.0f, 128.0f,  29.0f },
    CVector{ 1434.0f,  2632.0f, 13.0f },
    CVector{ 2783.0f,  1758.0f, 12.0f },
    CVector{ 2865.0f,  1281.0f, 12.0  }
};*/

uint32 (&NumTrackNodes)[4] = *(uint32(*)[4])0xC38014;
float (&arrTotalTrackLength)[4] = *(float (*)[4])0xC37FEC;
CTrainNode* (&trackNodes)[4] = *(CTrainNode*(*)[4])0xC38024;
float (&StationDist)[6] = *(float (*)[6])0xC38034;

void CTrain::InjectHooks()
{
    RH_ScopedClass(CTrain);
    RH_ScopedCategory("Vehicle");

    RH_ScopedVirtualInstall(ProcessControl, 0x6F86A0);
}

// 0x6F6030
CTrain::CTrain(int32 modelIndex, eVehicleCreatedBy createdBy) : CVehicle(createdBy) {
    plugin::CallMethod<0x6F6030, CTrain*, int32, eVehicleCreatedBy>(this, modelIndex, createdBy);
    return;

    const auto mi = CModelInfo::GetModelInfo(modelIndex)->AsVehicleModelInfoPtr();

    memset(&m_aDoors, 0, sizeof(m_aDoors));
    m_nVehicleSubType = VEHICLE_TYPE_TRAIN;
    m_nVehicleType = VEHICLE_TYPE_TRAIN;
    // m_pHandlingData = &handling.mod_HandlingManager.vehicleHandling[mi->m_nHandlingId];
    // m_nHandlingFlags = m_pHandlingData->m_handlingFlags;
    CVehicle::SetModelIndex(modelIndex);

    // todo: add as NOTSA add SetupModelNodes
    std::ranges::fill(m_aTrainNodes, nullptr);
    CClumpModelInfo::FillFrameArray(m_pRwClump, m_aTrainNodes);
    //

    m_aDoors[2].m_nDirn = 20;
    m_aDoors[2].m_nAxis = 2;
    if (m_nModelIndex == MODEL_STREAKC) {
        m_aDoors[2].m_fOpenAngle = 1.25f;
        m_aDoors[2].m_fClosedAngle = 0.25f;
        m_aDoors[3].m_fOpenAngle = 1.25f;
        m_aDoors[3].m_fClosedAngle = 0.25f;
    } else {
        m_aDoors[2].m_fOpenAngle = -1.2566371;
        m_aDoors[2].m_fClosedAngle = 0.0f;
        m_aDoors[3].m_fOpenAngle = 1.2566371;
        m_aDoors[3].m_fClosedAngle = 0.0f;
    }
    m_aDoors[3].m_nAxis = 2;
    m_aDoors[3].m_nDirn = 20;

    // m_nTrainFlags = m_nTrainFlags & (CLOCKWISE_DIRECTION | IS_LAST_CARRIAGE | IS_FRONT_CARRIAGE) | TF_80 | TF_1;
    // m_nTrainFlags = m_nTrainFlags & 0xF8 | 2;

    m_nPassengersGenerationState = 0;
    // m_nPassengerFlags = m_nPassengerFlags & 0xF0 | rand() & 3;
    // m_nPassengerFlags = m_nPassengerFlags & 0xF | (16 * ((rand() & 3) + 1));
    m_pTemporaryPassenger = nullptr;
    m_nMaxPassengers = 5;
    m_nPhysicalFlags = m_nPhysicalFlags | 0x20000; // b18;
    m_nFlags = m_nFlags | 1;                       // uses collision
    m_nTimeWhenCreated = CTimer::GetTimeInMS();
    field_5C8 = 0;
    m_nTrackId = 0;
    m_fCurrentRailDistance = 0.0f;
    m_fTrainSpeed = 0.0f;
    m_nTimeWhenStoppedAtStation = 0;
    mi->ChooseVehicleColour(m_nPrimaryColor, m_nSecondaryColor, m_nTertiaryColor, m_nQuaternaryColor, 1);
    m_fMass = m_pHandlingData->m_fMass;
    m_fTurnMass = m_pHandlingData->m_fTurnMass;
    m_vecCentreOfMass = (CVector)m_pHandlingData->m_vecCentreOfMass;
    m_fElasticity = 0.05f;
    m_fBuoyancyConstant = m_pHandlingData->m_fBuoyancyConstant;
    if (m_pHandlingData->m_fDragMult <= 0.01f)
        m_fAirResistance = m_pHandlingData->m_fDragMult;
    else
        m_fAirResistance = m_pHandlingData->m_fDragMult / 1000.0f * 0.5f; // pattern: see CPlane::SetGearDown

    m_nPhysicalFlags = m_nPhysicalFlags & 0xFFFFFFF3 | 4; // bDisableCollisionForce
    m_nFlags = m_nFlags | 0x80000000;                     // m_bTunnelTransition
    m_pPrevCarriage = nullptr;
    m_pNextCarriage = nullptr;
    // m_nType = (m_nType & 7) | 0x30;
    m_autoPilot.m_speed = 0.0f;
    m_autoPilot.m_nCruiseSpeed = 0;
    m_vehicleAudio.Initialise(this);
}

// 0x6F55D0
void CTrain::ReadAndInterpretTrackFile(char* filename, CTrainNode** nodes, int32* lineCount, float* totalDist, int32 skipStations) {
    ((void(__cdecl*)(char*, CTrainNode * *, int32*, float*, int32))0x6F55D0)(filename, nodes, lineCount, totalDist, skipStations);
}

// 0x6F58D0
void CTrain::Shutdown() {
    ((void(__cdecl*)())0x6F58D0)();
}

// 0x6F5900
void CTrain::UpdateTrains() {
    ((void(__cdecl*)())0x6F5900)();
}

// 0x6F5910
void ProcessTrainAnnouncements() {
    ((void(__cdecl*)())0x6F5910)();
}

// 0x6F5920
void PlayAnnouncement(uint8 arg0, uint8 arg1) {
    ((void(__cdecl*)(uint8, uint8))0x6F5920)(arg0, arg1);
}

// 0x6F59E0
void CTrain::FindCoorsFromPositionOnTrack(float railDistance, int32 trackId, CVector* outCoors) {
    ((void(__cdecl*)(float, int32, CVector*))0x6F59E0)(railDistance, trackId, outCoors);
}

// 0x6F5BA0
bool CTrain::FindMaximumSpeedToStopAtStations(float* speed) {
    return ((bool(__thiscall*)(CTrain*, float*))0x6F5BA0)(this, speed);
}

// 0x6F5CD0
uint32 CTrain::FindNumCarriagesPulled() {
    return ((uint32(__thiscall*)(CTrain*))0x6F5CD0)(this);
}

// 0x6F5CF0
void TrainHitStuff(CPtrList& ptrList, CEntity* entity) {
    ((void(__cdecl*)(CPtrList&, CEntity*))0x6F5CF0)(ptrList, entity);
}

// 0x6F5D80
void CTrain::OpenTrainDoor(float state) {
    // NOP
}

// 0x6F5D90
void CTrain::AddPassenger(CPed* ped) {
    // NOP
}

// 0x6F5DA0
void CTrain::RemovePassenger(CPed* ped) {
    // NOP
}

// 0x6F5DB0
void CTrain::DisableRandomTrains(bool disable) {
    bDisableRandomTrains = disable;
}

// 0x6F5DC0
void CTrain::RemoveOneMissionTrain(CTrain* train) {
    ((void(__cdecl*)(CTrain*))0x6F5DC0)(train);
}

// 0x6F5DF0
void CTrain::ReleaseOneMissionTrain(CTrain* train) {
    ((void(__cdecl*)(CTrain*))0x6F5DF0)(train);
}

// 0x6F5E20
void CTrain::SetTrainSpeed(CTrain* train, float speed) {
    ((void(__cdecl*)(CTrain*, float))0x6F5E20)(train, speed);
}

// 0x6F5E50
void CTrain::SetTrainCruiseSpeed(CTrain* arg0, float cruiseSpeed) {
    ((void(__cdecl*)(CTrain*, float))0x6F5E50)(arg0, cruiseSpeed);
}

// 0x6F5E70
CTrain* CTrain::FindCaboose(CTrain* train) {
    return ((CTrain * (__cdecl*)(CTrain*))0x6F5E70)(train);
}

// 0x6F5E90
CTrain* CTrain::FindEngine(CTrain* train) {
    return ((CTrain * (__cdecl*)(CTrain*))0x6F5E90)(train);
}

// 0x6F5EB0
CTrain* CTrain::FindCarriage(CTrain* train, uint8 carriage) {
    return ((CTrain * (__cdecl*)(CTrain*, uint8))0x6F5EB0)(train, carriage);
}

// 0x6F5EF0
bool CTrain::FindSideStationIsOn() {
    return ((bool(__thiscall*)(CTrain*))0x6F5EF0)(this);
}

// 0x6F5F00
void CTrain::FindNextStationPositionInDirection(bool clockwiseDirection, float distance, float* distanceToStation, int32* numStations) {
    ((void(__cdecl*)(bool, float, float*, int32*))0x6F5F00)(clockwiseDirection, distance, distanceToStation, numStations);
}

// 0x6F6320
bool CTrain::IsInTunnel() {
    return ((bool(__thiscall*)(CTrain*))0x6F6320)(this);
}

// 0x6F6640
void MarkSurroundingEntitiesForCollisionWithTrain(CVector arg0, float arg1, CEntity* arg2, bool bOnlyVehicles) {
    ((void(__cdecl*)(CVector, float, CEntity*, bool))0x6F6640)(arg0, arg1, arg2, bOnlyVehicles);
}

// 0x6F6850
void CTrain::RemoveRandomPassenger() {
    ((void(__thiscall*)(CTrain*))0x6F6850)(this);
}

// 0x6F6A20
void CTrain::RemoveMissionTrains() {
    ((void(__cdecl*)())0x6F6A20)();
}

// 0x6F6AA0
void CTrain::RemoveAllTrains() {
    ((void(__cdecl*)())0x6F6AA0)();
}

// 0x6F6B60
void CTrain::ReleaseMissionTrains() {
    ((void(__cdecl*)())0x6F6B60)();
}

// 0x6F6BD0
int32 CTrain::FindClosestTrackNode(CVector posn, int32* outTrackId) {
    return ((int32(__cdecl*)(CVector, int32*))0x6F6BD0)(posn, outTrackId);
}

// 0x6F6CC0
void CTrain::FindPositionOnTrackFromCoors() {
    ((void(__thiscall*)(CTrain*))0x6F6CC0)(this);
}

// 0x6F7090
CTrain* CTrain::FindNearestTrain(CVector posn, bool mustBeMainTrain) {
    return ((CTrain * (__cdecl*)(CVector, bool))0x6F7090)(posn, mustBeMainTrain);
}

// 0x6F7140
void CTrain::SetNewTrainPosition(CTrain* train, CVector posn) {
    ((void(__cdecl*)(CTrain*, CVector))0x6F7140)(train, posn);
}

// 0x6F7260
bool CTrain::IsNextStationAllowed(CTrain* train) {
    return ((bool(__cdecl*)(CTrain*))0x6F7260)(train);
}

// 0x6F72F0
void CTrain::SkipToNextAllowedStation(CTrain* train) {
    ((void(__cdecl*)(CTrain*))0x6F72F0)(train);
}

// 0x6F7440
void CTrain::InitTrains() {
    ((void(__cdecl*)())0x6F7440)();
}

// 0x6F7550
void CTrain::CreateMissionTrain(CVector posn, bool clockwiseDirection, uint32 trainType, CTrain** outFirstCarriage, CTrain** outLastCarriage, int32 nodeIndex, int32 trackId, bool isMissionTrain) {
    ((void(__cdecl*)(CVector, bool, uint32, CTrain * *, CTrain * *, int32, int32, bool))0x6F7550)(posn, clockwiseDirection, trainType, outFirstCarriage, outLastCarriage, nodeIndex, trackId, isMissionTrain);
}

// 0x6F7900
void CTrain::DoTrainGenerationAndRemoval() {
    ((void(__cdecl*)())0x6F7900)();
}

// 0x6F8170
void CTrain::AddNearbyPedAsRandomPassenger() {
    ((void(__thiscall*)(CTrain*))0x6F8170)(this);
}

// 0x6F86A0
void CTrain::ProcessControl()
{
    vehicleFlags.bWarnedPeds = 0;
    m_vehicleAudio.Service();
    if (gbModelViewer)
    {
        return;
    }

    CVector vecOldTrainPosition = GetPosition();
    float fOldTrainHeading = GetHeading();

    float fTotalTrackLength = arrTotalTrackLength[m_nTrackId];
    CTrainNode* trainNodes = trackNodes[m_nTrackId];
    int32 numTrackNodes = NumTrackNodes[m_nTrackId];

    if (trainFlags.bNotOnARailRoad == 0)
    {
        if (!trainFlags.bIsFrontCarriage)
        {
            CTrain* pPrevCarriage = m_pPrevCarriage;
            if (pPrevCarriage)
            {
                m_fTrainSpeed = pPrevCarriage->m_fTrainSpeed;
                m_fCurrentRailDistance = pPrevCarriage->m_fCurrentRailDistance + m_fLength;
            }
            else
            {
                m_fTrainSpeed *= pow(0.9900000095367432f, CTimer::GetTimeStep());
                m_fCurrentRailDistance += m_fTrainSpeed * CTimer::GetTimeStep();
            }

            if (trainFlags.b01 && trainFlags.bStoppedAtStation
                && m_nModelIndex == MODEL_STREAKC
                && !trainFlags.bMissionTrain)
            {
                CPlayerPed* localPlayer = FindPlayerPed();
                if (m_nPassengersGenerationState == TRAIN_PASSENGERS_QUERY_NUM_PASSENGERS_TO_LEAVE)
                {
                    if (localPlayer->m_pVehicle == this)
                    {
                        m_nNumPassengersToLeave = 0;
                    }
                    else
                    {
                        m_nNumPassengersToLeave = (rand() & 3) + 1; // rand(1, 4)
                    }
                    m_nPassengersGenerationState = TRAIN_PASSENGERS_TELL_PASSENGERS_TO_LEAVE;
                }

                if (m_nPassengersGenerationState == TRAIN_PASSENGERS_TELL_PASSENGERS_TO_LEAVE)
                {
                    RemoveRandomPassenger();
                    if (m_nNumPassengersToLeave == 0)
                    {
                        m_nPassengersGenerationState = TRAIN_PASSENGERS_QUERY_NUM_PASSENGERS_TO_ENTER;
                    }
                }

                if (m_nPassengersGenerationState == TRAIN_PASSENGERS_QUERY_NUM_PASSENGERS_TO_ENTER)
                {
                    if (localPlayer->m_pVehicle == this)
                    {
                        m_nNumPassengersToEnter = 0;
                    }
                    else
                    {
                        m_nNumPassengersToEnter = rand() % 4 + 1; // rand(1, 4)
                    }
                    m_nPassengersGenerationState = TRAIN_PASSENGERS_TELL_PASSENGERS_TO_ENTER;
                }

                if (m_nPassengersGenerationState == TRAIN_PASSENGERS_TELL_PASSENGERS_TO_ENTER)
                {
                    if (trainFlags.bPassengersCanEnterAndLeave)
                    {
                        AddNearbyPedAsRandomPassenger();
                        if (m_nNumPassengersToLeave == m_nNumPassengersToEnter)
                        {
                            m_nPassengersGenerationState = TRAIN_PASSENGERS_GENERATION_FINISHED;
                        }
                    }
                }
            }
        }
        else
        {
            CPad* pad = CPad::GetPad(0);
            if (m_pDriver && m_pDriver->IsPlayer())
            {
                pad = m_pDriver->AsPlayer()->GetPadFromPlayer();
            }

            uint32 numCarriagesPulled = FindNumCarriagesPulled();
            if (!trainFlags.bClockwiseDirection)
            {
                m_fTrainSpeed = -m_fTrainSpeed;
            }

            ///*
            if (m_nStatus)
            {
                bool bIsStreakModel = trainFlags.bIsStreakModel;
                auto fStopAtStationSpeed = static_cast<float>(m_autoPilot.m_nCruiseSpeed);

                uint32 timeInMilliSeconds = CTimer::GetTimeInMS();
                uint32 timeAtStation = CTimer::GetTimeInMS() - m_nTimeWhenStoppedAtStation;
                if (timeAtStation >= (bIsStreakModel ? 20000u : 10000u))
                {
                    if (timeAtStation >= (bIsStreakModel ? 28000u : 18000u))
                    {
                        if (timeAtStation >= (bIsStreakModel ? 32000u : 22000u))
                        {
                            if (trainFlags.bStopsAtStations)
                            {
                                float maxTrainSpeed = 0.0f;
                                if (FindMaximumSpeedToStopAtStations(&maxTrainSpeed))
                                {
                                    fStopAtStationSpeed = 0.0f;
                                    m_nTimeWhenStoppedAtStation = timeInMilliSeconds;
                                }
                                else
                                {
                                    if (fStopAtStationSpeed >= maxTrainSpeed)
                                    {
                                        fStopAtStationSpeed = maxTrainSpeed;
                                    }
                                }
                            }
                        }
                        else if (trainFlags.bStoppedAtStation)
                        {
                            CTrain* trainCarriage = this;
                            do
                            {
                                trainFlags.bStoppedAtStation = false;
                                trainCarriage->m_nPassengersGenerationState = TRAIN_PASSENGERS_GENERATION_FINISHED;
                                trainCarriage = trainCarriage->m_pNextCarriage;
                            } while (trainCarriage);
                        }
                    }
                    else
                    {
                        fStopAtStationSpeed = 0.0f;
                        if (trainFlags.bStoppedAtStation)
                        {
                            CTrain* trainCarriage = this;
                            do
                            {
                                trainFlags.bPassengersCanEnterAndLeave = false;
                                trainCarriage->m_nPassengersGenerationState = TRAIN_PASSENGERS_GENERATION_FINISHED;
                                trainCarriage = trainCarriage->m_pNextCarriage;
                            } while (trainCarriage);
                        }
                    }
                }
                else
                {
                    fStopAtStationSpeed = 0.0f;
                    if (!trainFlags.bStoppedAtStation)
                    {
                        CTrain* trainCarriage = this;
                        do
                        {
                            trainFlags.bStoppedAtStation = true;
                            trainFlags.bPassengersCanEnterAndLeave = true;
                            trainCarriage->m_nPassengersGenerationState = TRAIN_PASSENGERS_QUERY_NUM_PASSENGERS_TO_LEAVE;
                            trainCarriage = trainCarriage->m_pNextCarriage;
                        } while (trainCarriage);
                    }
                }

                fStopAtStationSpeed = fStopAtStationSpeed * 0.02f - m_fTrainSpeed;
                if (fStopAtStationSpeed > 0.0f)
                {
                    m_fTrainGas = fStopAtStationSpeed * 30.0f;
                    if (m_fTrainGas >= 1.0f)
                    {
                        m_fTrainGas = 1.0f;
                    }

                    m_fTrainGas *= 255.0f;
                    m_fTrainBrake = 0.0f;
                }
                else
                {
                    float fTrainSpeed = fStopAtStationSpeed * -30.0f;
                    m_fTrainGas = 0.0f;
                    if (fTrainSpeed >= 1.0f)
                    {
                        fTrainSpeed = 1.0f;
                    }
                    m_fTrainBrake = fTrainSpeed * 255.0f;
                }
            }
            else
            {
                float fTrainSpeed = m_fTrainSpeed;
                if (fTrainSpeed < 0.0f)
                {
                    fTrainSpeed = -fTrainSpeed;
                }

                if (fTrainSpeed < 0.001f)
                {
                    m_fTrainBrake = 0.0f;
                    m_fTrainGas = static_cast<float>(pad->GetAccelerate() - pad->GetBrake());
                }
                else
                {
                    if (m_fTrainSpeed > 0.0f)
                    {
                        m_fTrainBrake = static_cast<float>(pad->GetBrake());
                        m_fTrainGas = static_cast<float>(pad->GetAccelerate());
                    }
                    else
                    {
                        m_fTrainGas = static_cast<float>(-pad->GetBrake());
                        m_fTrainBrake = static_cast<float>(pad->GetAccelerate());
                    }
                }
            }

            if (trainFlags.bForceSlowDown)
            {
                CVector vecPoint = GetPosition();
                CVector vecDistance;
                if (CGameLogic::CalcDistanceToForbiddenTrainCrossing(vecPoint, m_vecMoveSpeed, true, &vecDistance) < 230.0f)
                {
                    if (DotProduct(GetForwardVector(), vecDistance) <= 0.0f)
                    {
                        m_fTrainGas = std::max(0.0f, m_fTrainGas);
                    }
                    else
                    {
                        m_fTrainGas = std::min(0.0f, m_fTrainGas);
                    }

                    if (CGameLogic::CalcDistanceToForbiddenTrainCrossing(vecPoint, m_vecMoveSpeed, false, &vecDistance) < 230.0f)
                    {
                        m_fTrainBrake = 512.0f;

                    }
                }
            }

            numCarriagesPulled += 3;

            m_fTrainSpeed += m_fTrainGas * 0.00390625f * CTimer::GetTimeStep() * 0.002f / numCarriagesPulled;

            if (m_fTrainBrake != 0.0f)
            {
                float fTrainSpeed = m_fTrainSpeed;
                if (m_fTrainSpeed < 0.0f)
                {
                    fTrainSpeed = -fTrainSpeed;
                }
                float fBreak = m_fTrainBrake * 0.00390625f * CTimer::GetTimeStep() * 0.006f / numCarriagesPulled;
                if (fTrainSpeed >= fBreak)
                {
                    if (m_fTrainSpeed < 0.0f)
                    {
                        m_fTrainSpeed += fBreak;
                    }
                    else
                    {
                        m_fTrainSpeed -= fBreak;
                    }
                }
                else
                {
                    m_fTrainSpeed = 0.0f;
                }
            }

            m_fTrainSpeed *= pow(0.999750018119812f, CTimer::GetTimeStep());
            if (!trainFlags.bClockwiseDirection)
            {
                m_fTrainSpeed = -m_fTrainSpeed;
            }

            m_fCurrentRailDistance += CTimer::GetTimeStep() * m_fTrainSpeed;

            if (m_nStatus == STATUS_PLAYER)
            {

                float fTheTrainSpeed = m_fTrainSpeed;
                if (fTheTrainSpeed < 0.0f)
                {
                    fTheTrainSpeed = -fTheTrainSpeed;
                }
                if (fTheTrainSpeed > 1.0f * 0.95f)
                {
                    CPad::GetPad()->StartShake(300, 70, 0);
                    TheCamera.CamShake(0.1f, GetPosition());
                }

                fTheTrainSpeed = m_fTrainSpeed;
                if (fTheTrainSpeed < 0.0f)
                {
                    fTheTrainSpeed = -fTheTrainSpeed;
                }

                if (fTheTrainSpeed > 1.0f)
                {
                    int32 nNodeIndex = m_nNodeIndex;
                    int32 previousNodeIndex = nNodeIndex - 1;
                    if (previousNodeIndex < 0)
                    {
                        previousNodeIndex = numTrackNodes;
                    }

                    int32 previousNodeIndex2 = previousNodeIndex - 1;
                    if (previousNodeIndex2 < 0)
                    {
                        previousNodeIndex2 = numTrackNodes;
                    }

                    CTrainNode* pCurrentTrainNode = &trainNodes[m_nNodeIndex];
                    CTrainNode* pPreviousTrainNode = &trainNodes[previousNodeIndex];
                    CTrainNode* pPreviousTrainNode2 = &trainNodes[previousNodeIndex2];

                    CVector vecDifference1 = pCurrentTrainNode->GetPosn() - pPreviousTrainNode->GetPosn();
                    CVector vecDifference2 = pPreviousTrainNode->GetPosn() - pPreviousTrainNode2->GetPosn();
                    vecDifference1.Normalise();
                    vecDifference2.Normalise();

                    if (vecDifference1.x * vecDifference2.x +
                        vecDifference1.y * vecDifference2.y +
                        vecDifference1.z * vecDifference2.z < 0.99599999f)
                    {
                        CTrain* carriage = this;
                        bool bIsInTunnel = false;
                        while (!bIsInTunnel)
                        {
                            bIsInTunnel = carriage->IsInTunnel();
                            carriage = carriage->m_pNextCarriage;
                            if (!carriage)
                            {
                                if (!bIsInTunnel)
                                {
                                    CTrain* theTrainCarriage = this;
                                    do
                                    {
                                        trainFlags.bNotOnARailRoad = true;
                                        theTrainCarriage->physicalFlags.bDisableCollisionForce = false;
                                        theTrainCarriage->physicalFlags.bDisableSimpleCollision = false;
                                        theTrainCarriage->SetIsStatic(false);
                                        theTrainCarriage = theTrainCarriage->m_pNextCarriage;
                                    } while (theTrainCarriage);

                                    CPhysical::ProcessControl();
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }

        if (m_fCurrentRailDistance < 0.0f)
        {
            do
            {
                m_fCurrentRailDistance += fTotalTrackLength;
            } while (m_fCurrentRailDistance < 0.0f);
        }

        if (m_fCurrentRailDistance >= fTotalTrackLength)
        {
            do
            {
                m_fCurrentRailDistance -= fTotalTrackLength;
            } while (m_fCurrentRailDistance >= fTotalTrackLength);
        }

        float fNextNodeTrackLength = 0.0f;
        int32 nextNodeIndex = m_nNodeIndex + 1;
        if (nextNodeIndex < numTrackNodes)
        {
            CTrainNode* nextTrainNode = &trainNodes[nextNodeIndex];
            fNextNodeTrackLength = nextTrainNode->m_nDistanceFromStart / 3.0f;
        }
        else
        {
            fNextNodeTrackLength = fTotalTrackLength;
            nextNodeIndex = 0;
        }

        CTrainNode* theTrainNode = &trainNodes[m_nNodeIndex];
        float fCurrentNodeTrackLength = theTrainNode->m_nDistanceFromStart / 3.0f;
        while (m_fCurrentRailDistance < fCurrentNodeTrackLength || fNextNodeTrackLength < m_fCurrentRailDistance)
        {
            int32 newNodeIndex = m_nNodeIndex - 1; // previous node
            if (fCurrentNodeTrackLength <= m_fCurrentRailDistance)
            {
                newNodeIndex = m_nNodeIndex + 1; // next node
            }
            m_nNodeIndex = newNodeIndex % numTrackNodes;
            m_vehicleAudio.AddAudioEvent(AE_TRAIN_CLACK, 0.0f);

            theTrainNode = &trainNodes[m_nNodeIndex];
            fCurrentNodeTrackLength = theTrainNode->m_nDistanceFromStart / 3.0f;

            nextNodeIndex = m_nNodeIndex + 1;
            if (nextNodeIndex < numTrackNodes)
            {
                CTrainNode* nextTrainNode = &trainNodes[nextNodeIndex];
                fNextNodeTrackLength = nextTrainNode->m_nDistanceFromStart / 3.0f;
            }
            else
            {
                fNextNodeTrackLength = fTotalTrackLength;
                nextNodeIndex = 0;
            }
        }

        CTrainNode* nextTrainNode = &trainNodes[nextNodeIndex];
        fNextNodeTrackLength = nextTrainNode->m_nDistanceFromStart / 3.0f;

        float fTrackNodeDifference = fNextNodeTrackLength - fCurrentNodeTrackLength;
        if (fTrackNodeDifference < 0.0f)
        {
            fTrackNodeDifference += fTotalTrackLength;
        }

        float fTheDistance = (m_fCurrentRailDistance - fCurrentNodeTrackLength) / fTrackNodeDifference;
        CVector vecPosition1;
        vecPosition1.x = theTrainNode->x * 0.125f * (1.0f - fTheDistance) + nextTrainNode->x * 0.125f * fTheDistance;
        vecPosition1.y = theTrainNode->y * 0.125f * (1.0f - fTheDistance) + nextTrainNode->y * 0.125f * fTheDistance;
        vecPosition1.z = theTrainNode->z * 0.125f * (1.0f - fTheDistance) + nextTrainNode->z * 0.125f * fTheDistance;


        CColModel* vehicleColModel = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel();
        CBoundingBox* pBoundingBox = &vehicleColModel->GetBoundingBox();
        float fTotalCurrentRailDistance = pBoundingBox->m_vecMax.y - pBoundingBox->m_vecMin.y + m_fCurrentRailDistance;
        if (fTotalCurrentRailDistance > fTotalTrackLength)
        {
            fTotalCurrentRailDistance -= fTotalTrackLength;
        }

        nextNodeIndex = m_nNodeIndex + 1;
        if (nextNodeIndex < numTrackNodes)
        {
            CTrainNode* nextTrainNode = &trainNodes[nextNodeIndex];
            fNextNodeTrackLength = nextTrainNode->m_nDistanceFromStart / 3.0f;
        }
        else
        {
            fNextNodeTrackLength = fTotalTrackLength;
            nextNodeIndex = 0;
        }

        int32 trainNodeIndex = m_nNodeIndex;
        while (fTotalCurrentRailDistance < fCurrentNodeTrackLength || fTotalCurrentRailDistance > fNextNodeTrackLength)
        {
            trainNodeIndex = (trainNodeIndex + 1) % numTrackNodes;

            theTrainNode = &trainNodes[trainNodeIndex];
            fCurrentNodeTrackLength = theTrainNode->m_nDistanceFromStart / 3.0f;

            nextNodeIndex = trainNodeIndex + 1;
            if (nextNodeIndex < numTrackNodes)
            {
                CTrainNode* nextTrainNode = &trainNodes[nextNodeIndex];
                fNextNodeTrackLength = nextTrainNode->m_nDistanceFromStart / 3.0f;
            }
            else
            {
                fNextNodeTrackLength = fTotalTrackLength;
                nextNodeIndex = 0;
            }
        }

        nextTrainNode = &trainNodes[nextNodeIndex];
        fNextNodeTrackLength = nextTrainNode->m_nDistanceFromStart / 3.0f;

        fTrackNodeDifference = fNextNodeTrackLength - fCurrentNodeTrackLength;
        if (fTrackNodeDifference < 0.0f)
        {
            fTrackNodeDifference += fTotalTrackLength;
        }

        fTheDistance = (fTotalCurrentRailDistance - fCurrentNodeTrackLength) / fTrackNodeDifference;
        CVector vecPosition2;
        vecPosition2.x = theTrainNode->x * 0.125f * (1.0f - fTheDistance) + nextTrainNode->x * 0.125f * fTheDistance;
        vecPosition2.y = theTrainNode->y * 0.125f * (1.0f - fTheDistance) + nextTrainNode->y * 0.125f * fTheDistance;
        vecPosition2.z = theTrainNode->z * 0.125f * (1.0f - fTheDistance) + nextTrainNode->z * 0.125f * fTheDistance;

        {
            CVector& vecVehiclePosition = GetPosition();
            vecVehiclePosition = (vecPosition1 + vecPosition2) * 0.5f;
            vecVehiclePosition.z += m_pHandlingData->m_fSuspensionLowerLimit - pBoundingBox->m_vecMin.z;
        }

        GetForward() = vecPosition2 - vecPosition1;
        GetForward().Normalise();
        if (!trainFlags.bClockwiseDirection)
        {
            GetForward() *= -1.0f;
        }

        CVector vecTemp(0.0f, 0.0f, 1.0f);

        CrossProduct(&GetRight(), &GetForward(), &vecTemp);
        GetRight().Normalise();

        CrossProduct(&GetUp(), &GetRight(), &GetForward());

        uint8 trainNodeLighting = theTrainNode->GetLightingFromCollision();
        uint8 trainNextNodeLighting = nextTrainNode->GetLightingFromCollision();

        auto fTrainNodeLighting = static_cast<float>(ScaleLighting(trainNodeLighting, 0.5f));
        auto fTrainNextNodeLighting = static_cast<float>(ScaleLighting(trainNextNodeLighting, 0.5f));

        fTrainNodeLighting += (fTrainNextNodeLighting - fTrainNodeLighting) * fTheDistance;
        m_fContactSurfaceBrightness = fTrainNodeLighting;
        m_vecMoveSpeed = (1.0f / CTimer::GetTimeStep()) * (GetPosition() - vecOldTrainPosition);

        float fNewTrainHeading = GetHeading();
        float fHeading = fNewTrainHeading - fOldTrainHeading;
        if (fHeading <= PI)
        {
            if (fHeading < -PI)
            {
                fHeading += TWO_PI;
            }
        }
        else
        {
            fHeading -= TWO_PI;
        }

        m_vecTurnSpeed = CVector(0.0f, 0.0f, fHeading / CTimer::GetTimeStep());

        if (trainFlags.bNotOnARailRoad)
        {
            m_vecMoveSpeed *= -1.0f;
            m_vecTurnSpeed *= -1.0f;

            ApplyMoveSpeed();

            m_vecMoveSpeed *= -1.0f;
            m_vecTurnSpeed *= -1.0f;

            CPhysical::ProcessControl();
        }
        else
        {
            float fVehicleMoveSpeedX = m_vecMoveSpeed.x;
            if (fVehicleMoveSpeedX <= -2.0f)
            {
                fVehicleMoveSpeedX = -2.0f;
            }

            if (fVehicleMoveSpeedX >= 2.0f)
            {
                fVehicleMoveSpeedX = 2.0f;
            }
            m_vecMoveSpeed.x = fVehicleMoveSpeedX;

            float fVehicleMoveSpeedY = m_vecMoveSpeed.y;
            if (fVehicleMoveSpeedY <= -2.0f)
            {
                fVehicleMoveSpeedY = -2.0f;
            }

            if (fVehicleMoveSpeedY >= 2.0f)
            {
                fVehicleMoveSpeedY = 2.0f;
            }
            m_vecMoveSpeed.y = fVehicleMoveSpeedY;

            float fVehicleMoveSpeedZ = m_vecMoveSpeed.z;
            if (fVehicleMoveSpeedZ <= -2.0f)
            {
                fVehicleMoveSpeedZ = -2.0f;
            }

            if (fVehicleMoveSpeedZ >= 2.0f)
            {
                fVehicleMoveSpeedZ = 2.0f;
            }
            m_vecMoveSpeed.z = fVehicleMoveSpeedZ;

            float fVehicleTurnSpeedX = m_vecTurnSpeed.x;
            if (fVehicleTurnSpeedX <= -0.1f)
            {
                fVehicleTurnSpeedX = -0.1f;
            }

            if (fVehicleTurnSpeedX >= 0.1f)
            {
                fVehicleTurnSpeedX = 0.1f;
            }
            m_vecTurnSpeed.x = fVehicleTurnSpeedX;

            float fVehicleTurnSpeedY = m_vecTurnSpeed.y;
            if (fVehicleTurnSpeedY <= -0.1f)
            {
                fVehicleTurnSpeedY = -0.1f;
            }

            if (fVehicleTurnSpeedY >= 0.1f)
            {
                fVehicleTurnSpeedY = 0.1f;
            }
            m_vecTurnSpeed.y = fVehicleTurnSpeedY;

            float fVehicleTurnSpeedZ = m_vecTurnSpeed.z;
            if (fVehicleTurnSpeedZ <= -0.1f)
            {
                fVehicleTurnSpeedZ = -0.1f;
            }

            if (fVehicleTurnSpeedZ >= 0.1f)
            {
                fVehicleTurnSpeedZ = 0.1f;
            }
            m_vecTurnSpeed.z = fVehicleTurnSpeedZ;
        }

        UpdateRW();
        UpdateRwFrame();
        RemoveAndAdd();

        m_bIsStuck = false;
        m_bWasPostponed = false;
        m_bIsInSafePosition = true;

        m_fMovingSpeed = (vecOldTrainPosition - GetPosition()).Magnitude();

        if (trainFlags.bIsFrontCarriage || trainFlags.bIsLastCarriage)
        {
            CVector vecPoint = pBoundingBox->m_vecMax.y * GetForward();
            vecPoint += GetPosition();
            vecPoint += CTimer::GetTimeStep() * m_vecMoveSpeed;

            MarkSurroundingEntitiesForCollisionWithTrain(vecPoint, 3.0f, this, false);
        }

        if (!vehicleFlags.bWarnedPeds)
        {
            CCarCtrl::ScanForPedDanger(this);
        }
        return;
    }
    else
    {
        if (!m_bIsStuck)
        {
            float fMaxForce = 0.003f;
            float fMaxTorque = 0.00090000004f;
            float fMaxMovingSpeed = 0.005f;

            if (m_nStatus != STATUS_PLAYER)
            {
                fMaxForce = 0.006f;
                fMaxTorque = 0.0015f;
                fMaxMovingSpeed = 0.015f;
            }

            float fMaxForceTimeStep = (fMaxForce * CTimer::GetTimeStep()) * (fMaxForce * CTimer::GetTimeStep());
            float fMaxTorqueTimeStep = (fMaxTorque * CTimer::GetTimeStep()) * (fMaxTorque * CTimer::GetTimeStep());

            m_vecForce = (m_vecForce + m_vecMoveSpeed) * 0.5f;
            m_vecTorque = (m_vecTorque + m_vecTurnSpeed) * 0.5f;

            if (m_vecForce.SquaredMagnitude() > fMaxForceTimeStep
                || m_vecTorque.SquaredMagnitude() > fMaxTorqueTimeStep
                || m_fMovingSpeed >= fMaxMovingSpeed
                || m_fDamageIntensity > 0.0f
                && m_pDamageEntity != nullptr
                && (m_pDamageEntity->IsPed())
                )
            {
                m_nFakePhysics = 0;
            }
            else
            {

                m_nFakePhysics += 1;
                if (m_nFakePhysics > 10)
                {

                    //if (!dummy_424100()) dummy_424100 returns 0, nothing else
                    {
                        if (m_nFakePhysics > 10)
                        {
                            m_nFakePhysics = 10;
                        }

                        m_vecMoveSpeed = CVector();
                        m_vecTurnSpeed = CVector();
                        SkipPhysics();
                        return;
                    }
                }
            }
        }

        CPhysical::ProcessControl();

        CVector vecMoveForce, vecTurnForce;
        if (mod_Buoyancy.ProcessBuoyancy(this, m_fBuoyancyConstant, &vecMoveForce, &vecTurnForce))
        {
            physicalFlags.bTouchingWater = true;

            float fTimeStep = 0.01f;
            if (CTimer::GetTimeStep() >= 0.01f)
            {
                fTimeStep = CTimer::GetTimeStep();
            }

            float fSpeedFactor = 1.0f - vecOldTrainPosition.z / (fTimeStep * m_fMass * 0.008f) * 0.05f;
            fSpeedFactor = pow(fSpeedFactor, CTimer::GetTimeStep());

            m_vecMoveSpeed *= fSpeedFactor;
            m_vecTurnSpeed *= fSpeedFactor;
            ApplyMoveForce(vecOldTrainPosition.x, vecOldTrainPosition.y, vecOldTrainPosition.z);
            ApplyTurnForce(vecTurnForce, vecMoveForce);
        }
    }
}
