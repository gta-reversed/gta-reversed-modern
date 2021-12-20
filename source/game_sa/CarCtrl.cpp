/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

uint32& CCarCtrl::NumLawEnforcerCars = *(uint32*)0x969098;
uint32& CCarCtrl::NumParkedCars = *(uint32*)0x9690A0;
uint32& CCarCtrl::NumAmbulancesOnDuty = *(uint32*)0x9690A8;
uint32& CCarCtrl::NumFireTrucksOnDuty = *(uint32*)0x9690AC;
uint32& CCarCtrl::MaxNumberOfCarsInUse = *(uint32*)0x8A5B24;
bool& CCarCtrl::bCarsGeneratedAroundCamera = *(bool*)0x9690C1;

void CCarCtrl::InjectHooks()
{
    ReversibleHooks::Install("CCarCtrl", "ChooseGangCarModel", 0x421A40, &CCarCtrl::ChooseGangCarModel, false, 7);
    ReversibleHooks::Install("CCarCtrl", "ChoosePoliceCarModel", 0x421980, &CCarCtrl::ChoosePoliceCarModel, false, 7);
    ReversibleHooks::Install("CCarCtrl", "CreateCarForScript", 0x431F80, &CCarCtrl::CreateCarForScript);
}

// 0x421970
int32 CCarCtrl::ChooseBoatModel() {
    return plugin::CallAndReturn<int32, 0x421970>();
}

// 0x421900
int32 CCarCtrl::ChooseCarModelToLoad(int32 arg1) {
    return plugin::CallAndReturn<int32, 0x421900, int32>(arg1);
}

int32 CCarCtrl::ChooseGangCarModel(int32 loadedCarGroupId)
{
    return CPopulation::PickGangCar(loadedCarGroupId);
}

// 0x424CE0
int32 CCarCtrl::ChooseModel(int32* arg1) {
    return plugin::CallAndReturn<int32, 0x424CE0, int32*>(arg1);
}

int32 CCarCtrl::ChoosePoliceCarModel(uint32 ignoreLvpd1Model) {
    CWanted* playerWanted = FindPlayerWanted(-1);
    if (playerWanted->AreSwatRequired() 
        && CStreaming::GetInfo(MODEL_ENFORCER).IsLoaded() 
        && CStreaming::GetInfo(MODEL_SWAT).IsLoaded())
    {
        if (CGeneral::GetRandomNumberInRange(0, 3) == 2)
            return MODEL_ENFORCER; 
    }
    else
    {
        if (playerWanted->AreFbiRequired() 
            && CStreaming::GetInfo(MODEL_FBIRANCH).IsLoaded()
            && CStreaming::GetInfo(MODEL_FBI).IsLoaded())
            return MODEL_FBIRANCH; 
        if (playerWanted->AreArmyRequired() 
            && CStreaming::GetInfo(MODEL_RHINO).IsLoaded()
            && CStreaming::GetInfo(MODEL_BARRACKS).IsLoaded()
            && CStreaming::GetInfo(MODEL_ARMY).IsLoaded())
            return (rand() < 0x3FFF) + MODEL_RHINO;
    }
    return CStreaming::GetDefaultCopCarModel(ignoreLvpd1Model);
}

// 0x423F00
void CCarCtrl::ClearInterestingVehicleList() {
    plugin::Call<0x423F00>();
}

// 0x422760
void CCarCtrl::ClipTargetOrientationToLink(CVehicle* pVehicle, CCarPathLinkAddress arg2, char arg3, float* arg4, float arg5, float arg6) {
    plugin::Call<0x422760, CVehicle*, CCarPathLinkAddress, char, float*, float, float>(pVehicle, arg2, arg3, arg4, arg5, arg6);
}

// 0x431F80
CVehicle* CCarCtrl::CreateCarForScript(int32 modelid, CVector posn, uint8 doMissionCleanup) {
    if (CModelInfo::IsBoatModel(modelid))
    {
        auto* pBoat = new CBoat(modelid, eVehicleCreatedBy::MISSION_VEHICLE);
        if (posn.z <= -100.0F)
            posn.z = CWorld::FindGroundZForCoord(posn.x, posn.y);

        posn.z += pBoat->GetDistanceFromCentreOfMassToBaseOfModel();
        pBoat->SetPosn(posn);

        CTheScripts::ClearSpaceForMissionEntity(posn, pBoat);
        pBoat->vehicleFlags.bEngineOn = false;
        pBoat->vehicleFlags.bIsLocked = true;
        pBoat->m_nStatus = eEntityStatus::STATUS_ABANDONED;
        CCarCtrl::JoinCarWithRoadSystem(pBoat);

        pBoat->m_autoPilot.m_nCarMission = eCarMission::MISSION_NONE;
        pBoat->m_autoPilot.m_nTempAction = 0;
        pBoat->m_autoPilot.m_speed = 20.0F;
        pBoat->m_autoPilot.m_nCruiseSpeed = 20;

        if (doMissionCleanup)
            pBoat->m_bIsStaticWaitingForCollision = true;

        pBoat->m_autoPilot.movementFlags.bIsStopped = true;
        CWorld::Add(pBoat);

        if (doMissionCleanup)
            CTheScripts::MissionCleanUp.AddEntityToList(CPools::ms_pVehiclePool->GetRef(pBoat), MissionCleanUpEntityType::MISSION_CLEANUP_ENTITY_TYPE_VEHICLE);

        return pBoat;
    }

    auto* pVeh = CCarCtrl::GetNewVehicleDependingOnCarModel(modelid, eVehicleCreatedBy::MISSION_VEHICLE);
    if (posn.z <= -100.0F)
        posn.z = CWorld::FindGroundZForCoord(posn.x, posn.y);

    posn.z += pVeh->GetDistanceFromCentreOfMassToBaseOfModel();
    pVeh->SetPosn(posn);

    if (!doMissionCleanup)
    {
        if (pVeh->IsAutomobile())
            pVeh->AsAutomobile()->PlaceOnRoadProperly();
        else if (pVeh->IsBike())
            pVeh->AsBike()->PlaceOnRoadProperly();
    }

    if (pVeh->IsTrain())
        pVeh->AsTrain()->trainFlags.bNotOnARailRoad = true;

    CTheScripts::ClearSpaceForMissionEntity(posn, pVeh);
    pVeh->vehicleFlags.bIsLocked = true;
    pVeh->m_nStatus = eEntityStatus::STATUS_ABANDONED;
    CCarCtrl::JoinCarWithRoadSystem(pVeh);
    pVeh->vehicleFlags.bEngineOn = false;
    pVeh->vehicleFlags.bHasBeenOwnedByPlayer = true;

    pVeh->m_autoPilot.m_nCarMission = eCarMission::MISSION_NONE;
    pVeh->m_autoPilot.m_nTempAction = 0;
    pVeh->m_autoPilot.m_nCarDrivingStyle = eCarDrivingStyle::DRIVINGSTYLE_STOP_FOR_CARS;
    pVeh->m_autoPilot.m_speed = 13.0F;
    pVeh->m_autoPilot.m_nCruiseSpeed = 13;
    pVeh->m_autoPilot.m_nCurrentLane = 0;
    pVeh->m_autoPilot.m_nNextLane = 0;

    if (doMissionCleanup)
        pVeh->m_bIsStaticWaitingForCollision = true;

    CWorld::Add(pVeh);
    if (doMissionCleanup)
        CTheScripts::MissionCleanUp.AddEntityToList(CPools::ms_pVehiclePool->GetRef(pVeh), MissionCleanUpEntityType::MISSION_CLEANUP_ENTITY_TYPE_VEHICLE);

    if (pVeh->IsRoadVehicle())
        pVeh->m_autoPilot.movementFlags.bIsStopped = true;

    return pVeh;
}

// 0x42C740
bool CCarCtrl::CreateConvoy(CVehicle* pVehicle, int32 arg2) {
    return plugin::CallAndReturn<bool, 0x42C740, CVehicle*, int32>(pVehicle, arg2);
}

// 0x42C2B0
bool CCarCtrl::CreatePoliceChase(CVehicle* pVehicle, int32 arg2, CNodeAddress NodeAddress) {
    return plugin::CallAndReturn<bool, 0x42C2B0, CVehicle*, int32, CNodeAddress>(pVehicle, arg2, NodeAddress);
}

// 0x428040
bool CCarCtrl::DealWithBend_Racing(CVehicle* pVehicle, CCarPathLinkAddress LinkAddress1, CCarPathLinkAddress LinkAddress2, CCarPathLinkAddress LinkAddress3, CCarPathLinkAddress LinkAddress4, char arg6, char arg7, char arg8, char arg9, float arg10, float* arg11, float* arg12, float* arg13, float* arg14, CVector* pVector) {
    return plugin::CallAndReturn<bool, 0x428040, CVehicle*, CCarPathLinkAddress, CCarPathLinkAddress, CCarPathLinkAddress, CCarPathLinkAddress, char, char, char, char, float, float*, float*, float*, float*, CVector*>(pVehicle, LinkAddress1, LinkAddress2, LinkAddress3, LinkAddress4, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, pVector);
}

// 0x42EC90
void CCarCtrl::DragCarToPoint(CVehicle* pVehicle, CVector* pVector) {
    plugin::Call<0x42EC90, CVehicle*, CVector*>(pVehicle, pVector);
}

// 0x4325C0
float CCarCtrl::FindAngleToWeaveThroughTraffic(CVehicle* pVehicle, CPhysical* pPhysical, float arg3, float arg4, float arg5) {
    return plugin::CallAndReturn<float, 0x4325C0, CVehicle*, CPhysical*, float, float, float>(pVehicle, pPhysical, arg3, arg4, arg5);
}

// 0x4226F0
void CCarCtrl::FindIntersection2Lines(float arg1, float arg2, float arg3, float arg4, float arg5, float arg6, float arg7, float arg8, float* arg9, float* arg10) {
    plugin::Call<0x4226F0, float, float, float, float, float, float, float, float, float*, float*>(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
}

// 0x42B470
void CCarCtrl::FindLinksToGoWithTheseNodes(CVehicle* pVehicle) {
    plugin::Call<0x42B470, CVehicle*>(pVehicle);
}

// 0x434400
float CCarCtrl::FindMaximumSpeedForThisCarInTraffic(CVehicle* pVehicle) {
    return plugin::CallAndReturn<float, 0x434400, CVehicle*>(pVehicle);
}

// 0x42BD20
void CCarCtrl::FindNodesThisCarIsNearestTo(CVehicle* pVehicle, CNodeAddress& NodeAddress1, CNodeAddress& NodeAddress2) {
    plugin::Call<0x42BD20, CVehicle*, CNodeAddress&, CNodeAddress&>(pVehicle, NodeAddress1, NodeAddress2);
}

// 0x422090
char CCarCtrl::FindPathDirection(CNodeAddress NodeAddress1, CNodeAddress NodeAddress2, CNodeAddress NodeAddress3, bool* arg4) {
    return plugin::CallAndReturn<char, 0x422090, CNodeAddress, CNodeAddress, CNodeAddress, bool*>(NodeAddress1, NodeAddress2, NodeAddress3, arg4);
}

// 0x422620
float CCarCtrl::FindPercDependingOnDistToLink(CVehicle* pVehicle, CCarPathLinkAddress LinkAddress) {
    return plugin::CallAndReturn<float, 0x422620, CVehicle*, CCarPathLinkAddress>(pVehicle, LinkAddress);
}

// 0x421770
int32 CCarCtrl::FindSequenceElement(int32 arg1) {
    return plugin::CallAndReturn<int32, 0x421770, int32>(arg1);
}

// 0x4224E0
float CCarCtrl::FindSpeedMultiplier(float arg1, float arg2, float arg3, float arg4) {
    return plugin::CallAndReturn<float, 0x4224E0, float, float, float, float>(arg1, arg2, arg3, arg4);
}

// 0x424130
float CCarCtrl::FindSpeedMultiplierWithSpeedFromNodes(char arg1) {
    return plugin::CallAndReturn<float, 0x424130, char>(arg1);
}

float CCarCtrl::FindGhostRoadHeight(CVehicle* pVehicle) {
    return plugin::CallAndReturn<float, 0x422370, CVehicle*>(pVehicle);
}

// 0x42B270
void CCarCtrl::FireHeliRocketsAtTarget(CAutomobile* pEntityLauncher, CEntity* pEntity) {
    plugin::Call<0x42B270, CAutomobile*, CEntity*>(pEntityLauncher, pEntity);
}

// 0x429A70
void CCarCtrl::FlyAIHeliInCertainDirection(CHeli* pHeli, float arg2, float arg3, bool arg4) {
    plugin::Call<0x429A70, CHeli*, float, float, bool>(pHeli, arg2, arg3, arg4);
}

// 0x423940
void CCarCtrl::FlyAIHeliToTarget_FixedOrientation(CHeli* pHeli, float Orientation, CVector posn) {
    plugin::Call<0x423940, CHeli*, float, CVector>(pHeli, Orientation, posn);
}

// 0x423000
void CCarCtrl::FlyAIPlaneInCertainDirection(CPlane* pPlane) {
    plugin::Call<0x423000, CPlane*>(pPlane);
}

// 0x424210
bool CCarCtrl::GenerateCarCreationCoors2(CVector posn, float radius, float arg3, float arg4, bool arg5, float arg6, float arg7, CVector* pOrigin, CNodeAddress* pNodeAddress1, CNodeAddress* pNodeAddress12, float* arg11, bool arg12, bool arg13) {
    return plugin::CallAndReturn<bool, 0x424210, CVector, float, float, float, bool, float, float, CVector*, CNodeAddress*, CNodeAddress*, float*, bool, bool>(posn, radius, arg3, arg4, arg5, arg6, arg7, pOrigin, pNodeAddress1, pNodeAddress12, arg11, arg12, arg13);
}

// 0x42F9C0
void CCarCtrl::GenerateEmergencyServicesCar() {
    plugin::Call<0x42F9C0>();
}

// 0x42B7D0
bool CCarCtrl::GenerateOneEmergencyServicesCar(uint32 modelID, CVector posn) {
    return plugin::CallAndReturn<bool, 0x42B7D0, uint32, CVector>(modelID, posn);
}

// 0x430050
void CCarCtrl::GenerateOneRandomCar() {
    plugin::Call<0x430050>();
}

// 0x4341C0
void CCarCtrl::GenerateRandomCars() {
    plugin::Call<0x4341C0>();
}

// 0x42F3C0
void CCarCtrl::GetAIHeliToAttackPlayer(CAutomobile* pAutomobile) {
    plugin::Call<0x42F3C0, CAutomobile*>(pAutomobile);
}

// 0x42A730
void CCarCtrl::GetAIHeliToFlyInDirection(CAutomobile* pAutomobile) {
    plugin::Call<0x42A730, CAutomobile*>(pAutomobile);
}

// 0x429780
void CCarCtrl::GetAIPlaneToAttackPlayer(CAutomobile* pAutomobile) {
    plugin::Call<0x429780, CAutomobile*>(pAutomobile);
}

// 0x429890
void CCarCtrl::GetAIPlaneToDoDogFight(CAutomobile* pAutomobile) {
    plugin::Call<0x429890, CAutomobile*>(pAutomobile);
}

// 0x42F370
void CCarCtrl::GetAIPlaneToDoDogFightAgainstPlayer(CAutomobile* pAutomobile) {
    plugin::Call<0x42F370, CAutomobile*>(pAutomobile);
}

// 0x421440
CVehicle* CCarCtrl::GetNewVehicleDependingOnCarModel(int32 modelID, uint8 createdBy) {
    return plugin::CallAndReturn<CVehicle*, 0x421440, int32, uint8>(modelID, createdBy);
}

// 0x4212E0
void CCarCtrl::Init() {
    plugin::Call<0x4212E0>();
}

// 0x421740
void CCarCtrl::InitSequence(int32 SequenceElements) {
    plugin::Call<0x421740, int32>(SequenceElements);
}

// 0x42C250
bool CCarCtrl::IsAnyoneParking() {
    return plugin::CallAndReturn<bool, 0x42C250>();
}

// 0x42DAB0
bool CCarCtrl::IsThisAnAppropriateNode(CVehicle* pVehicle, CNodeAddress NodeAddress1, CNodeAddress NodeAddress2, CNodeAddress NodeAddress3, bool arg5) {
    return plugin::CallAndReturn<bool, 0x42DAB0, CVehicle*, CNodeAddress, CNodeAddress, CNodeAddress, bool>(pVehicle, NodeAddress1, NodeAddress2, NodeAddress3, arg5);
}

// 0x423EA0
bool CCarCtrl::IsThisVehicleInteresting(CVehicle* pVehicle) {
    return plugin::CallAndReturn<bool, 0x423EA0, CVehicle*>(pVehicle);
}

// 0x432CB0
void CCarCtrl::JoinCarWithRoadAccordingToMission(CVehicle* pVehicle) {
    plugin::Call<0x432CB0, CVehicle*>(pVehicle);
}

// 0x42F5A0
void CCarCtrl::JoinCarWithRoadSystem(CVehicle* pVehicle) {
    plugin::Call<0x42F5A0, CVehicle*>(pVehicle);
}

// 0x42F870
bool CCarCtrl::JoinCarWithRoadSystemGotoCoors(CVehicle* pVehicle, CVector const& posn, bool unused, bool bIsBoat) {
    return plugin::CallAndReturn<bool, 0x42F870, CVehicle*, CVector const&, bool, bool>(pVehicle, posn, unused, bIsBoat);
}

// 0x432B10
bool CCarCtrl::PickNextNodeAccordingStrategy(CVehicle* pVehicle) {
    return plugin::CallAndReturn<bool, 0x432B10, CVehicle*>(pVehicle);
}

// 0x42DE80
void CCarCtrl::PickNextNodeRandomly(CVehicle* pVehicle) {
    plugin::Call<0x42DE80, CVehicle*>(pVehicle);
}

// 0x426EF0
bool CCarCtrl::PickNextNodeToChaseCar(CVehicle* pVehicle, float x_dest, float y_dest, float z_dest) {
    return plugin::CallAndReturn<bool, 0x426EF0, CVehicle*, float, float, float>(pVehicle, x_dest, y_dest, z_dest);
}

// 0x427740
bool CCarCtrl::PickNextNodeToFollowPath(CVehicle* pVehicle) {
    return plugin::CallAndReturn<bool, 0x427740, CVehicle*>(pVehicle);
}

// 0x429600
void CCarCtrl::PossiblyFireHSMissile(CVehicle* pEntityLauncher, CEntity* pTargetEntity) {
    plugin::Call<0x429600, CVehicle*, CEntity*>(pEntityLauncher, pTargetEntity);
}

// 0x424F80
void CCarCtrl::PossiblyRemoveVehicle(CVehicle* pVehicle) {
    plugin::Call<0x424F80, CVehicle*>(pVehicle);
}

// 0x423F10
void CCarCtrl::PruneVehiclesOfInterest() {
    plugin::Call<0x423F10>();
}

// 0x4213B0
void CCarCtrl::ReInit() {
    plugin::Call<0x4213B0>();
}

// 0x42FC40
void CCarCtrl::ReconsiderRoute(CVehicle* pVehicle) {
    plugin::Call<0x42FC40, CVehicle*>(pVehicle);
}

// 0x423DE0
void CCarCtrl::RegisterVehicleOfInterest(CVehicle* pVehicle) {
    plugin::Call<0x423DE0, CVehicle*>(pVehicle);
}

// 0x4322B0
void CCarCtrl::RemoveCarsIfThePoolGetsFull() {
    plugin::Call<0x4322B0>();
}

// 0x42CD10
void CCarCtrl::RemoveDistantCars() {
    plugin::Call<0x42CD10>();
}

// 0x423ED0
void CCarCtrl::RemoveFromInterestingVehicleList(CVehicle* pVehicle) {
    plugin::Call<0x423ED0, CVehicle*>(pVehicle);
}

// 0x42CE40
void CCarCtrl::ScanForPedDanger(CVehicle* pVehicle) {
    plugin::Call<0x42CE40, CVehicle*>(pVehicle);
}

// 0x42FBC0
bool CCarCtrl::ScriptGenerateOneEmergencyServicesCar(uint32 modelID, CVector posn) {
    return plugin::CallAndReturn<bool, 0x42FBC0, uint32, CVector>(modelID, posn);
}

// 0x4342A0
void CCarCtrl::SetCoordsOfScriptCar(CVehicle* pVehicle, float x, float y, float z, uint8 arg5, uint8 arg6) {
    plugin::Call<0x4342A0, CVehicle*, float, float, float, uint8, uint8>(pVehicle, x, y, z, arg5, arg6);
}

// 0x4217C0
void CCarCtrl::SetUpDriverAndPassengersForVehicle(CVehicle* pVehicle, int32 arg2, int32 arg3, bool arg4, bool arg5, int32 passengersNum) {
    plugin::Call<0x4217C0, CVehicle*, int32, int32, bool, bool, int32>(pVehicle, arg2, arg3, arg4, arg5, passengersNum);
}

// 0x432420
void CCarCtrl::SlowCarDownForCarsSectorList(CPtrList& PtrList, CVehicle* pVehicle, float arg3, float arg4, float arg5, float arg6, float* arg7, float arg8) {
    plugin::Call<0x432420, CPtrList&, CVehicle*, float, float, float, float, float*, float>(PtrList, pVehicle, arg3, arg4, arg5, arg6, arg7, arg8);
}

// 0x426220
void CCarCtrl::SlowCarDownForObject(CEntity* pEntity, CVehicle* pVehicle, float* arg3, float arg4) {
    plugin::Call<0x426220, CEntity*, CVehicle*, float*, float>(pEntity, pVehicle, arg3, arg4);
}

// 0x42D4F0
void CCarCtrl::SlowCarDownForObjectsSectorList(CPtrList& PtrList, CVehicle* pVehicle, float arg3, float arg4, float arg5, float arg6, float* arg7, float arg8) {
    plugin::Call<0x42D4F0, CPtrList&, CVehicle*, float, float, float, float, float*, float>(PtrList, pVehicle, arg3, arg4, arg5, arg6, arg7, arg8);
}

// 0x42D0E0
void CCarCtrl::SlowCarDownForOtherCar(CEntity* pCar1, CVehicle* pCar2, float* arg3, float arg4) {
    plugin::Call<0x42D0E0, CEntity*, CVehicle*, float*, float>(pCar1, pCar2, arg3, arg4);
}

// 0x425440
void CCarCtrl::SlowCarDownForPedsSectorList(CPtrList& PtrList, CVehicle* pVehicle, float arg3, float arg4, float arg5, float arg6, float* arg7, float arg8) {
    plugin::Call<0x425440, CPtrList&, CVehicle*, float, float, float, float, float*, float>(PtrList, pVehicle, arg3, arg4, arg5, arg6, arg7, arg8);
}

// 0x434790
void CCarCtrl::SlowCarOnRailsDownForTrafficAndLights(CVehicle* pVehicle) {
    plugin::Call<0x434790, CVehicle*>(pVehicle);
}

// 0x428DE0
void CCarCtrl::SteerAIBoatWithPhysicsAttackingPlayer(CVehicle* pVehicle, float* arg2, float* arg3, float* arg4, bool* arg5) {
    plugin::Call<0x428DE0, CVehicle*, float*, float*, float*, bool*>(pVehicle, arg2, arg3, arg4, arg5);
}

// 0x429090
void CCarCtrl::SteerAIBoatWithPhysicsCirclingPlayer(CVehicle* pVehicle, float* arg2, float* arg3, float* arg4, bool* arg5) {
    plugin::Call<0x429090, CVehicle*, float*, float*, float*, bool*>(pVehicle, arg2, arg3, arg4, arg5);
}

// 0x428BE0
void CCarCtrl::SteerAIBoatWithPhysicsHeadingForTarget(CVehicle* pVehicle, float arg2, float arg3, float* arg4, float* arg5, float* arg6) {
    plugin::Call<0x428BE0, CVehicle*, float, float, float*, float*, float*>(pVehicle, arg2, arg3, arg4, arg5, arg6);
}

// 0x422B20
void CCarCtrl::SteerAICarBlockingPlayerForwardAndBack(CVehicle* pVehicle, float* arg2, float* arg3, float* arg4, bool* arg5) {
    plugin::Call<0x422B20, CVehicle*, float*, float*, float*, bool*>(pVehicle, arg2, arg3, arg4, arg5);
}

// 0x433BA0
void CCarCtrl::SteerAICarParkParallel(CVehicle* pVehicle, float* arg2, float* arg3, float* arg4, bool* arg5) {
    plugin::Call<0x433BA0, CVehicle*, float*, float*, float*, bool*>(pVehicle, arg2, arg3, arg4, arg5);
}

// 0x433EA0
void CCarCtrl::SteerAICarParkPerpendicular(CVehicle* pVehicle, float* arg2, float* arg3, float* arg4, bool* arg5) {
    plugin::Call<0x433EA0, CVehicle*, float*, float*, float*, bool*>(pVehicle, arg2, arg3, arg4, arg5);
}

// 0x4336D0
void CCarCtrl::SteerAICarTowardsPointInEscort(CVehicle* pVehicle1, CVehicle* pVehicle2, float arg3, float arg4, float* arg5, float* arg6, float* arg7, bool* arg8) {
    plugin::Call<0x4336D0, CVehicle*, CVehicle*, float, float, float*, float*, float*, bool*>(pVehicle1, pVehicle2, arg3, arg4, arg5, arg6, arg7, arg8);
}

// 0x437C20
void CCarCtrl::SteerAICarWithPhysics(CVehicle* pVehicle) {
    plugin::Call<0x437C20, CVehicle*>(pVehicle);
}

// 0x434900
void CCarCtrl::SteerAICarWithPhysicsFollowPath(CVehicle* pVehicle, float* arg2, float* arg3, float* arg4, bool* arg5) {
    plugin::Call<0x434900, CVehicle*, float*, float*, float*, bool*>(pVehicle, arg2, arg3, arg4, arg5);
}

// 0x435830
void CCarCtrl::SteerAICarWithPhysicsFollowPath_Racing(CVehicle* pVehicle, float* arg2, float* arg3, float* arg4, bool* arg5) {
    plugin::Call<0x435830, CVehicle*, float*, float*, float*, bool*>(pVehicle, arg2, arg3, arg4, arg5);
}

// 0x432DD0
void CCarCtrl::SteerAICarWithPhysicsFollowPreRecordedPath(CVehicle* pVehicle, float* arg2, float* arg3, float* arg4, bool* arg5) {
    plugin::Call<0x432DD0, CVehicle*, float*, float*, float*, bool*>(pVehicle, arg2, arg3, arg4, arg5);
}

// 0x433280
void CCarCtrl::SteerAICarWithPhysicsHeadingForTarget(CVehicle* pVehicle, CPhysical* pTarget, float arg3, float arg4, float* arg5, float* arg6, float* arg7, bool* arg8) {
    plugin::Call<0x433280, CVehicle*, CPhysical*, float, float, float*, float*, float*, bool*>(pVehicle, pTarget, arg3, arg4, arg5, arg6, arg7, arg8);
}

// 0x4335E0
void CCarCtrl::SteerAICarWithPhysicsTryingToBlockTarget(CVehicle* pVehicle, CEntity* Unusued, float arg3, float arg4, float arg5, float arg6, float* arg7, float* arg8, float* arg9, bool* arg10) {
    plugin::Call<0x4335E0, CVehicle*, CEntity*, float, float, float, float, float*, float*, float*, bool*>(pVehicle, Unusued, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
}

// 0x428990
void CCarCtrl::SteerAICarWithPhysicsTryingToBlockTarget_Stop(CVehicle* pVehicle, float x, float y, float arg4, float arg5, float* arg6, float* arg7, float* arg8, bool* arg9) {
    plugin::Call<0x428990, CVehicle*, float, float, float, float, float*, float*, float*, bool*>(pVehicle, x, y, arg4, arg5, arg6, arg7, arg8, arg9);
}

// 0x436A90
void CCarCtrl::SteerAICarWithPhysics_OnlyMission(CVehicle* pVehicle, float* arg2, float* arg3, float* arg4, bool* arg5) {
    plugin::Call<0x436A90, CVehicle*, float*, float*, float*, bool*>(pVehicle, arg2, arg3, arg4, arg5);
}

// 0x42AAD0
void CCarCtrl::SteerAIHeliAsPoliceHeli(CAutomobile* pAutomobile) {
    plugin::Call<0x42AAD0, CAutomobile*>(pAutomobile);
}

// 0x42ACB0
void CCarCtrl::SteerAIHeliFlyingAwayFromPlayer(CAutomobile* pAutomobile) {
    plugin::Call<0x42ACB0, CAutomobile*>(pAutomobile);
}

// 0x4238E0
void CCarCtrl::SteerAIHeliToCrashAndBurn(CAutomobile* pAutomobile) {
    plugin::Call<0x4238E0, CAutomobile*>(pAutomobile);
}

// 0x42A750
void CCarCtrl::SteerAIHeliToFollowEntity(CAutomobile* pAutomobile) {
    plugin::Call<0x42A750, CAutomobile*>(pAutomobile);
}

// 0x42AEB0
void CCarCtrl::SteerAIHeliToKeepEntityInView(CAutomobile* pAutomobile) {
    plugin::Call<0x42AEB0, CAutomobile*>(pAutomobile);
}

// 0x42AD30
void CCarCtrl::SteerAIHeliToLand(CAutomobile* pAutomobile) {
    plugin::Call<0x42AD30, CAutomobile*>(pAutomobile);
}

// 0x42A630
void CCarCtrl::SteerAIHeliTowardsTargetCoors(CAutomobile* pAutomobile) {
    plugin::Call<0x42A630, CAutomobile*>(pAutomobile);
}

// 0x423880
void CCarCtrl::SteerAIPlaneToCrashAndBurn(CAutomobile* pAutomobile) {
    plugin::Call<0x423880, CAutomobile*>(pAutomobile);
}

// 0x4237F0
void CCarCtrl::SteerAIPlaneToFollowEntity(CAutomobile* pAutomobile) {
    plugin::Call<0x4237F0, CAutomobile*>(pAutomobile);
}

// 0x423790
void CCarCtrl::SteerAIPlaneTowardsTargetCoors(CAutomobile* pAutomobile) {
    plugin::Call<0x423790, CAutomobile*>(pAutomobile);
}

// 0x422590
bool CCarCtrl::StopCarIfNodesAreInvalid(CVehicle* pVehicle) {
    return plugin::CallAndReturn<bool, 0x422590, CVehicle*>(pVehicle);
}

// 0x4222A0
void CCarCtrl::SwitchBetweenPhysicsAndGhost(CVehicle* pVehicle) {
    plugin::Call<0x4222A0, CVehicle*>(pVehicle);
}

// 0x423FC0
void CCarCtrl::SwitchVehicleToRealPhysics(CVehicle* pVehicle) {
    plugin::Call<0x423FC0, CVehicle*>(pVehicle);
}

// 0x425B30
float CCarCtrl::TestCollisionBetween2MovingRects(CVehicle* pVehicle1, CVehicle* pVehicle2, float arg3, float arg4, CVector* pVector1, CVector* pVector2) {
    return plugin::CallAndReturn<float, 0x425B30, CVehicle*, CVehicle*, float, float, CVector*, CVector*>(pVehicle1, pVehicle2, arg3, arg4, pVector1, pVector2);
}

// 0x425F70
float CCarCtrl::TestCollisionBetween2MovingRects_OnlyFrontBumper(CVehicle* pVehicle1, CVehicle* pVehicle2, float arg3, float arg4, CVector* pVector1, CVector* pVector2) {
    return plugin::CallAndReturn<float, 0x425F70, CVehicle*, CVehicle*, float, float, CVector*, CVector*>(pVehicle1, pVehicle2, arg3, arg4, pVector1, pVector2);
}

// 0x429520
void CCarCtrl::TestWhetherToFirePlaneGuns(CVehicle* pVehicle, CEntity* pTarget) {
    plugin::Call<0x429520, CVehicle*, CEntity*>(pVehicle, pTarget);
}

// 0x421FE0
bool CCarCtrl::ThisVehicleShouldTryNotToTurn(CVehicle* pVehicle) {
    return plugin::CallAndReturn<bool, 0x421FE0, CVehicle*>(pVehicle);
}

// 0x429300
void CCarCtrl::TriggerDogFightMoves(CVehicle* pVehicle1, CVehicle* pVehicle2) {
    plugin::Call<0x429300, CVehicle*, CVehicle*>(pVehicle1, pVehicle2);
}

// 0x424000
void CCarCtrl::UpdateCarCount(CVehicle* pVehicle, uint8 bDecrease) {
    plugin::Call<0x424000, CVehicle*, uint8>(pVehicle, bDecrease);
}

// 0x436540
void CCarCtrl::UpdateCarOnRails(CVehicle* pVehicle) {
    plugin::Call<0x436540, CVehicle*>(pVehicle);
}

// 0x426BC0
void CCarCtrl::WeaveForObject(CEntity* pEntity, CVehicle* pVehicle, float* arg3, float* arg4) {
    plugin::Call<0x426BC0, CEntity*, CVehicle*, float*, float*>(pEntity, pVehicle, arg3, arg4);
}

// 0x426350
void CCarCtrl::WeaveForOtherCar(CEntity* pEntity, CVehicle* pVehicle, float* arg3, float* arg4) {
    plugin::Call<0x426350, CEntity*, CVehicle*, float*, float*>(pEntity, pVehicle, arg3, arg4);
}

// 0x42D680
void CCarCtrl::WeaveThroughCarsSectorList(CPtrList& PtrList, CVehicle* pVehicle, CPhysical* pPhysical, float arg4, float arg5, float arg6, float arg7, float* arg8, float* arg9) {
    plugin::Call<0x42D680, CPtrList&, CVehicle*, CPhysical*, float, float, float, float, float*, float*>(PtrList, pVehicle, pPhysical, arg4, arg5, arg6, arg7, arg8, arg9);
}

// 0x42D950
void CCarCtrl::WeaveThroughObjectsSectorList(CPtrList& PtrList, CVehicle* pVehicle, float arg3, float arg4, float arg5, float arg6, float* arg7, float* arg8) {
    plugin::Call<0x42D950, CPtrList&, CVehicle*, float, float, float, float, float*, float*>(PtrList, pVehicle, arg3, arg4, arg5, arg6, arg7, arg8);
}

// 0x42D7E0
void CCarCtrl::WeaveThroughPedsSectorList(CPtrList& PtrList, CVehicle* pVehicle, CPhysical* pPhysical, float arg4, float arg5, float arg6, float arg7, float* arg8, float* arg9) {
    plugin::Call<0x42D7E0, CPtrList&, CVehicle*, CPhysical*, float, float, float, float, float*, float*>(PtrList, pVehicle, pPhysical, arg4, arg5, arg6, arg7, arg8, arg9);
}
