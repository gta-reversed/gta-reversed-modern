/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vehicle.h"
#include "Plane.h"
#include "Heli.h"
#include "PathFind.h"

class CCarCtrl {
public:
    static uint32& NumLawEnforcerCars;
    static uint32& NumParkedCars;
    static uint32& NumAmbulancesOnDuty;
    static uint32& NumFireTrucksOnDuty;
    static uint32& MaxNumberOfCarsInUse;
    static float& CarDensityMultiplier;
    static int32& NumRandomCars;
    static int32& NumMissionCars;
    static int32& NumPermanentVehicles;
    static int32& LastTimeAmbulanceCreated;
    static int32& LastTimeFireTruckCreated;
    static bool& bAllowEmergencyServicesToBeCreated;
    static bool& bCarsGeneratedAroundCamera;
    static int8& CountDownToCarsAtStart;
    static float& TimeNextMadDriverChaseCreated;
    static int32& SequenceElements;
    static int32& SequenceRandomOffset;
    static bool& bSequenceOtherWay;
    static int32& LastTimeLawEnforcerCreated;

public:
    static void InjectHooks();

    static int32 ChooseBoatModel();
    static int32 ChooseCarModelToLoad(int32 arg1);
    static int32 ChooseModel(int32* arg1);
    static int32 ChoosePoliceCarModel(uint32 arg0);
    static int32 ChooseGangCarModel(int32 loadedCarGroupId);
    static void ClearInterestingVehicleList();
    static void ClitargetOrientationToLink(CVehicle* vehicle, CCarPathLinkAddress arg2, int8 arg3, float* arg4, float arg5, float arg6);
    static CVehicle* CreateCarForScript(int32 modelId, CVector posn, bool doMissionCleanup);
    static bool CreateConvoy(CVehicle* vehicle, int32 arg2);
    static bool CreatePoliceChase(CVehicle* vehicle, int32 arg2, CNodeAddress NodeAddress);
    static bool DealWithBend_Racing(CVehicle* vehicle, CCarPathLinkAddress LinkAddress1, CCarPathLinkAddress LinkAddress2, CCarPathLinkAddress LinkAddress3, CCarPathLinkAddress LinkAddress4, char arg6, char arg7, char arg8, char arg9, float arg10, float* arg11, float* arg12, float* arg13, float* arg14, CVector* pos);
    static void DragCarToPoint(CVehicle* vehicle, CVector* pos);
    static float FindAngleToWeaveThroughTraffic(CVehicle* vehicle, CPhysical* pPhysical, float arg3, float arg4, float arg5);
    static void FindIntersection2Lines(float arg1, float arg2, float arg3, float arg4, float arg5, float arg6, float arg7, float arg8, float* arg9, float* arg10);
    static void FindLinksToGoWithTheseNodes(CVehicle* vehicle);
    static float FindMaximumSpeedForThisCarInTraffic(CVehicle* vehicle);
    static void FindNodesThisCarIsNearestTo(CVehicle* vehicle, CNodeAddress& nodeAddress1, CNodeAddress& nodeAddress2);
    static int8 FindPathDirection(CNodeAddress nodeAddress1, CNodeAddress nodeAddress2, CNodeAddress nodeAddress3, bool* arg4);
    static float FindPercDependingOnDistToLink(CVehicle* vehicle, CCarPathLinkAddress linkAddress);
    static int32 FindSequenceElement(int32 arg1);
    static float FindSpeedMultiplier(float arg1, float arg2, float arg3, float arg4);
    static float FindSpeedMultiplierWithSpeedFromNodes(int8 arg1);
    static float FindGhostRoadHeight(CVehicle* vehicle);
    static void FireHeliRocketsAtTarget(CAutomobile* entityLauncher, CEntity* pEntity);
    static void FlyAIHeliInCertainDirection(CHeli* heli, float arg2, float arg3, bool arg4);
    static void FlyAIHeliToTarget_FixedOrientation(CHeli* heli, float Orientation, CVector posn);
    static void FlyAIPlaneInCertainDirection(CPlane* pPlane);
    static bool GenerateCarCreationCoors2(CVector posn, float radius, float arg3, float arg4, bool arg5, float arg6, float arg7, CVector* pOrigin, CNodeAddress* pNodeAddress1, CNodeAddress* pNodeAddress12, float* arg11, bool arg12, bool arg13);
    static void GenerateEmergencyServicesCar();
    static CAutomobile* GenerateOneEmergencyServicesCar(uint32 modelID, CVector posn);
    static void GenerateOneRandomCar();
    static void GenerateRandomCars();
    static void GetAIHeliToAttackPlayer(CAutomobile* automobile);
    static void GetAIHeliToFlyInDirection(CAutomobile* automobile);
    static void GetAIPlaneToAttackPlayer(CAutomobile* automobile);
    static void GetAIPlaneToDoDogFight(CAutomobile* automobile);
    static void GetAIPlaneToDoDogFightAgainstPlayer(CAutomobile* automobile);
    static CVehicle* GetNewVehicleDependingOnCarModel(int32 modelID, uint8 createdBy);
    static void Init();
    static void InitSequence(int32 SequenceElements);
    static bool IsAnyoneParking();
    static bool IsThisAnAppropriateNode(CVehicle* vehicle, CNodeAddress nodeAddress1, CNodeAddress nodeAddress2, CNodeAddress nodeAddress3, bool arg5);
    static bool IsThisVehicleInteresting(CVehicle* vehicle);
    static void JoinCarWithRoadAccordingToMission(CVehicle* vehicle);
    static void JoinCarWithRoadSystem(CVehicle* vehicle);
    static bool JoinCarWithRoadSystemGotoCoors(CVehicle* vehicle, const CVector& posn, bool unused, bool bIsBoat);
    static bool PickNextNodeAccordingStrategy(CVehicle* vehicle);
    static void PickNextNodeRandomly(CVehicle* vehicle);
    static bool PickNextNodeToChaseCar(CVehicle* vehicle, float x_dest, float y_dest, float z_dest);
    static bool PickNextNodeToFollowPath(CVehicle* vehicle);
    static void PossiblyFireHSMissile(CVehicle* entityLauncher, CEntity* targetEntity);
    static void PossiblyRemoveVehicle(CVehicle* vehicle);
    static void PruneVehiclesOfInterest();
    static void ReInit();
    static void ReconsiderRoute(CVehicle* vehicle);
    static void RegisterVehicleOfInterest(CVehicle* vehicle);
    static void RemoveCarsIfThePoolGetsFull();
    static void RemoveDistantCars();
    static void RemoveFromInterestingVehicleList(CVehicle* vehicle);
    static void ScanForPedDanger(CVehicle* vehicle);
    static bool ScriptGenerateOneEmergencyServicesCar(uint32 modelID, CVector posn);
    static void SetCoordsOfScriptCar(CVehicle* vehicle, float x, float y, float z, uint8 arg5, uint8 arg6);
    static void SetUpDriverAndPassengersForVehicle(CVehicle* vehicle, int32 arg2, int32 arg3, bool arg4, bool arg5, int32 passengersNum);
    static void SlowCarDownForCarsSectorList(CPtrList& PtrList, CVehicle* vehicle, float arg3, float arg4, float arg5, float arg6, float* arg7, float arg8);
    static void SlowCarDownForObject(CEntity* pEntity, CVehicle* vehicle, float* arg3, float arg4);
    static void SlowCarDownForObjectsSectorList(CPtrList& PtrList, CVehicle* vehicle, float arg3, float arg4, float arg5, float arg6, float* arg7, float arg8);
    static void SlowCarDownForOtherCar(CEntity* pCar1, CVehicle* pCar2, float* arg3, float arg4);
    static void SlowCarDownForPedsSectorList(CPtrList& PtrList, CVehicle* vehicle, float arg3, float arg4, float arg5, float arg6, float* arg7, float arg8);
    static void SlowCarOnRailsDownForTrafficAndLights(CVehicle* vehicle);
    static void SteerAIBoatWithPhysicsAttackingPlayer(CVehicle* vehicle, float* arg2, float* arg3, float* arg4, bool* arg5);
    static void SteerAIBoatWithPhysicsCirclingPlayer(CVehicle* vehicle, float* arg2, float* arg3, float* arg4, bool* arg5);
    static void SteerAIBoatWithPhysicsHeadingForTarget(CVehicle* vehicle, float arg2, float arg3, float* arg4, float* arg5, float* arg6);
    static void SteerAICarBlockingPlayerForwardAndBack(CVehicle* vehicle, float* arg2, float* arg3, float* arg4, bool* arg5);
    static void SteerAICarParkParallel(CVehicle* vehicle, float* arg2, float* arg3, float* arg4, bool* arg5);
    static void SteerAICarParkPerpendicular(CVehicle* vehicle, float* arg2, float* arg3, float* arg4, bool* arg5);
    static void SteerAICarTowardsPointInEscort(CVehicle* vehicle1, CVehicle* vehicle2, float arg3, float arg4, float* arg5, float* arg6, float* arg7, bool* arg8);
    static void SteerAICarWithPhysics(CVehicle* vehicle);
    static void SteerAICarWithPhysicsFollowPath(CVehicle* vehicle, float* arg2, float* arg3, float* arg4, bool* arg5);
    static void SteerAICarWithPhysicsFollowPath_Racing(CVehicle* vehicle, float* arg2, float* arg3, float* arg4, bool* arg5);
    static void SteerAICarWithPhysicsFollowPreRecordedPath(CVehicle* vehicle, float* arg2, float* arg3, float* arg4, bool* arg5);
    static void SteerAICarWithPhysicsHeadingForTarget(CVehicle* vehicle, CPhysical* target, float arg3, float arg4, float* arg5, float* arg6, float* arg7, bool* arg8);
    static void SteerAICarWithPhysicsTryingToBlockTarget(CVehicle* vehicle, CEntity* Unusued, float arg3, float arg4, float arg5, float arg6, float* arg7, float* arg8, float* arg9, bool* arg10);
    static void SteerAICarWithPhysicsTryingToBlockTarget_Stop(CVehicle* vehicle, float x, float y, float arg4, float arg5, float* arg6, float* arg7, float* arg8, bool* arg9);
    static void SteerAICarWithPhysics_OnlyMission(CVehicle* vehicle, float* arg2, float* arg3, float* arg4, bool* arg5);
    static void SteerAIHeliAsPoliceHeli(CAutomobile* automobile);
    static void SteerAIHeliFlyingAwayFromPlayer(CAutomobile* automobile);
    static void SteerAIHeliToCrashAndBurn(CAutomobile* automobile);
    static void SteerAIHeliToFollowEntity(CAutomobile* automobile);
    static void SteerAIHeliToKeepEntityInView(CAutomobile* automobile);
    static void SteerAIHeliToLand(CAutomobile* automobile);
    static void SteerAIHeliTowardsTargetCoors(CAutomobile* automobile);
    static void SteerAIPlaneToCrashAndBurn(CAutomobile* automobile);
    static void SteerAIPlaneToFollowEntity(CAutomobile* automobile);
    static void SteerAIPlaneTowardsTargetCoors(CAutomobile* automobile);
    static bool StopCarIfNodesAreInvalid(CVehicle* vehicle);
    static void SwitchBetweenPhysicsAndGhost(CVehicle* vehicle);
    static void SwitchVehicleToRealPhysics(CVehicle* vehicle);
    static float TestCollisionBetween2MovingRects(CVehicle* vehicle1, CVehicle* vehicle2, float arg3, float arg4, CVector* pVector1, CVector* pVector2);
    static float TestCollisionBetween2MovingRects_OnlyFrontBumper(CVehicle* vehicle1, CVehicle* vehicle2, float arg3, float arg4, CVector* pVector1, CVector* pVector2);
    static void TestWhetherToFirePlaneGuns(CVehicle* vehicle, CEntity* target);
    static bool ThisVehicleShouldTryNotToTurn(CVehicle* vehicle);
    static void TriggerDogFightMoves(CVehicle* vehicle1, CVehicle* vehicle2);
    static void UpdateCarCount(CVehicle* vehicle, uint8 bDecrease);
    static void UpdateCarOnRails(CVehicle* vehicle);
    static void WeaveForObject(CEntity* pEntity, CVehicle* vehicle, float* arg3, float* arg4);
    static void WeaveForOtherCar(CEntity* pEntity, CVehicle* vehicle, float* arg3, float* arg4);
    static void WeaveThroughCarsSectorList(CPtrList& PtrList, CVehicle* vehicle, CPhysical* pPhysical, float arg4, float arg5, float arg6, float arg7, float* arg8, float* arg9);
    static void WeaveThroughObjectsSectorList(CPtrList& PtrList, CVehicle* vehicle, float arg3, float arg4, float arg5, float arg6, float* arg7, float* arg8);
    static void WeaveThroughPedsSectorList(CPtrList& PtrList, CVehicle* vehicle, CPhysical* pPhysical, float arg4, float arg5, float arg6, float arg7, float* arg8, float* arg9);
};
