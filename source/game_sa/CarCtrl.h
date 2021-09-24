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
    static bool& bCarsGeneratedAroundCamera;

public:
    static void InjectHooks();

    static int32 ChooseBoatModel();
    static int32 ChooseCarModelToLoad(int32 arg1);
    static int32 ChooseModel(int32* arg1);
    static int32 ChoosePoliceCarModel(uint32 arg0);
    static int32 ChooseGangCarModel(int32 loadedCarGroupId);
    static void ClearInterestingVehicleList();
    static void ClipTargetOrientationToLink(CVehicle* pVehicle, CCarPathLinkAddress arg2, char arg3, float* arg4, float arg5, float arg6);
    static CVehicle* CreateCarForScript(int32 modelid, CVector posn, uint8 doMissionCleanup);
    static bool CreateConvoy(CVehicle* pVehicle, int32 arg2);
    static bool CreatePoliceChase(CVehicle* pVehicle, int32 arg2, CNodeAddress NodeAddress);
    static bool DealWithBend_Racing(CVehicle* pVehicle, CCarPathLinkAddress LinkAddress1, CCarPathLinkAddress LinkAddress2, CCarPathLinkAddress LinkAddress3, CCarPathLinkAddress LinkAddress4, char arg6, char arg7, char arg8, char arg9, float arg10, float* arg11, float* arg12, float* arg13, float* arg14, CVector* pVector);
    static void DragCarToPoint(CVehicle* pVehicle, CVector* pVector);
    static float FindAngleToWeaveThroughTraffic(CVehicle* pVehicle, CPhysical* pPhysical, float arg3, float arg4, float arg5);
    static void FindIntersection2Lines(float arg1, float arg2, float arg3, float arg4, float arg5, float arg6, float arg7, float arg8, float* arg9, float* arg10);
    static void FindLinksToGoWithTheseNodes(CVehicle* pVehicle);
    static float FindMaximumSpeedForThisCarInTraffic(CVehicle* pVehicle);
    static void FindNodesThisCarIsNearestTo(CVehicle* pVehicle, CNodeAddress& NodeAddress1, CNodeAddress& NodeAddress2);
    static char FindPathDirection(CNodeAddress NodeAddress1, CNodeAddress NodeAddress2, CNodeAddress NodeAddress3, bool* arg4);
    static float FindPercDependingOnDistToLink(CVehicle* pVehicle, CCarPathLinkAddress LinkAddress);
    static int32 FindSequenceElement(int32 arg1);
    static float FindSpeedMultiplier(float arg1, float arg2, float arg3, float arg4);
    static float FindSpeedMultiplierWithSpeedFromNodes(char arg1);
    static float FindGhostRoadHeight(CVehicle* pVehicle);
    static void FireHeliRocketsAtTarget(CAutomobile* pEntityLauncher, CEntity* pEntity);
    static void FlyAIHeliInCertainDirection(CHeli* pHeli, float arg2, float arg3, bool arg4);
    static void FlyAIHeliToTarget_FixedOrientation(CHeli* pHeli, float Orientation, CVector posn);
    static void FlyAIPlaneInCertainDirection(CPlane* pPlane);
    static bool GenerateCarCreationCoors2(CVector posn, float radius, float arg3, float arg4, bool arg5, float arg6, float arg7, CVector* pOrigin, CNodeAddress* pNodeAddress1, CNodeAddress* pNodeAddress12, float* arg11, bool arg12, bool arg13);
    static void GenerateEmergencyServicesCar();
    static bool GenerateOneEmergencyServicesCar(uint32 modelID, CVector posn);
    static void GenerateOneRandomCar();
    static void GenerateRandomCars();
    static void GetAIHeliToAttackPlayer(CAutomobile* pAutomobile);
    static void GetAIHeliToFlyInDirection(CAutomobile* pAutomobile);
    static void GetAIPlaneToAttackPlayer(CAutomobile* pAutomobile);
    static void GetAIPlaneToDoDogFight(CAutomobile* pAutomobile);
    static void GetAIPlaneToDoDogFightAgainstPlayer(CAutomobile* pAutomobile);
    static CVehicle* GetNewVehicleDependingOnCarModel(int32 modelID, uint8 createdBy);
    static void Init();
    static void InitSequence(int32 SequenceElements);
    static bool IsAnyoneParking();
    static bool IsThisAnAppropriateNode(CVehicle* pVehicle, CNodeAddress NodeAddress1, CNodeAddress NodeAddress2, CNodeAddress NodeAddress3, bool arg5);
    static bool IsThisVehicleInteresting(CVehicle* pVehicle);
    static void JoinCarWithRoadAccordingToMission(CVehicle* pVehicle);
    static void JoinCarWithRoadSystem(CVehicle* pVehicle);
    static bool JoinCarWithRoadSystemGotoCoors(CVehicle* pVehicle, CVector const& posn, bool unused, bool bIsBoat);
    static bool PickNextNodeAccordingStrategy(CVehicle* pVehicle);
    static void PickNextNodeRandomly(CVehicle* pVehicle);
    static bool PickNextNodeToChaseCar(CVehicle* pVehicle, float x_dest, float y_dest, float z_dest);
    static bool PickNextNodeToFollowPath(CVehicle* pVehicle);
    static void PossiblyFireHSMissile(CVehicle* pEntityLauncher, CEntity* pTargetEntity);
    static void PossiblyRemoveVehicle(CVehicle* pVehicle);
    static void PruneVehiclesOfInterest();
    static void ReInit();
    static void ReconsiderRoute(CVehicle* pVehicle);
    static void RegisterVehicleOfInterest(CVehicle* pVehicle);
    static void RemoveCarsIfThePoolGetsFull();
    static void RemoveDistantCars();
    static void RemoveFromInterestingVehicleList(CVehicle* pVehicle);
    static void ScanForPedDanger(CVehicle* pVehicle);
    static bool ScriptGenerateOneEmergencyServicesCar(uint32 modelID, CVector posn);
    static void SetCoordsOfScriptCar(CVehicle* pVehicle, float x, float y, float z, uint8 arg5, uint8 arg6);
    static void SetUpDriverAndPassengersForVehicle(CVehicle* pVehicle, int32 arg2, int32 arg3, bool arg4, bool arg5, int32 passengersNum);
    static void SlowCarDownForCarsSectorList(CPtrList& PtrList, CVehicle* pVehicle, float arg3, float arg4, float arg5, float arg6, float* arg7, float arg8);
    static void SlowCarDownForObject(CEntity* pEntity, CVehicle* pVehicle, float* arg3, float arg4);
    static void SlowCarDownForObjectsSectorList(CPtrList& PtrList, CVehicle* pVehicle, float arg3, float arg4, float arg5, float arg6, float* arg7, float arg8);
    static void SlowCarDownForOtherCar(CEntity* pCar1, CVehicle* pCar2, float* arg3, float arg4);
    static void SlowCarDownForPedsSectorList(CPtrList& PtrList, CVehicle* pVehicle, float arg3, float arg4, float arg5, float arg6, float* arg7, float arg8);
    static void SlowCarOnRailsDownForTrafficAndLights(CVehicle* pVehicle);
    static void SteerAIBoatWithPhysicsAttackingPlayer(CVehicle* pVehicle, float* arg2, float* arg3, float* arg4, bool* arg5);
    static void SteerAIBoatWithPhysicsCirclingPlayer(CVehicle* pVehicle, float* arg2, float* arg3, float* arg4, bool* arg5);
    static void SteerAIBoatWithPhysicsHeadingForTarget(CVehicle* pVehicle, float arg2, float arg3, float* arg4, float* arg5, float* arg6);
    static void SteerAICarBlockingPlayerForwardAndBack(CVehicle* pVehicle, float* arg2, float* arg3, float* arg4, bool* arg5);
    static void SteerAICarParkParallel(CVehicle* pVehicle, float* arg2, float* arg3, float* arg4, bool* arg5);
    static void SteerAICarParkPerpendicular(CVehicle* pVehicle, float* arg2, float* arg3, float* arg4, bool* arg5);
    static void SteerAICarTowardsPointInEscort(CVehicle* pVehicle1, CVehicle* pVehicle2, float arg3, float arg4, float* arg5, float* arg6, float* arg7, bool* arg8);
    static void SteerAICarWithPhysics(CVehicle* pVehicle);
    static void SteerAICarWithPhysicsFollowPath(CVehicle* pVehicle, float* arg2, float* arg3, float* arg4, bool* arg5);
    static void SteerAICarWithPhysicsFollowPath_Racing(CVehicle* pVehicle, float* arg2, float* arg3, float* arg4, bool* arg5);
    static void SteerAICarWithPhysicsFollowPreRecordedPath(CVehicle* pVehicle, float* arg2, float* arg3, float* arg4, bool* arg5);
    static void SteerAICarWithPhysicsHeadingForTarget(CVehicle* pVehicle, CPhysical* pTarget, float arg3, float arg4, float* arg5, float* arg6, float* arg7, bool* arg8);
    static void SteerAICarWithPhysicsTryingToBlockTarget(CVehicle* pVehicle, CEntity* Unusued, float arg3, float arg4, float arg5, float arg6, float* arg7, float* arg8, float* arg9, bool* arg10);
    static void SteerAICarWithPhysicsTryingToBlockTarget_Stop(CVehicle* pVehicle, float x, float y, float arg4, float arg5, float* arg6, float* arg7, float* arg8, bool* arg9);
    static void SteerAICarWithPhysics_OnlyMission(CVehicle* pVehicle, float* arg2, float* arg3, float* arg4, bool* arg5);
    static void SteerAIHeliAsPoliceHeli(CAutomobile* pAutomobile);
    static void SteerAIHeliFlyingAwayFromPlayer(CAutomobile* pAutomobile);
    static void SteerAIHeliToCrashAndBurn(CAutomobile* pAutomobile);
    static void SteerAIHeliToFollowEntity(CAutomobile* pAutomobile);
    static void SteerAIHeliToKeepEntityInView(CAutomobile* pAutomobile);
    static void SteerAIHeliToLand(CAutomobile* pAutomobile);
    static void SteerAIHeliTowardsTargetCoors(CAutomobile* pAutomobile);
    static void SteerAIPlaneToCrashAndBurn(CAutomobile* pAutomobile);
    static void SteerAIPlaneToFollowEntity(CAutomobile* pAutomobile);
    static void SteerAIPlaneTowardsTargetCoors(CAutomobile* pAutomobile);
    static bool StopCarIfNodesAreInvalid(CVehicle* pVehicle);
    static void SwitchBetweenPhysicsAndGhost(CVehicle* pVehicle);
    static void SwitchVehicleToRealPhysics(CVehicle* pVehicle);
    static float TestCollisionBetween2MovingRects(CVehicle* pVehicle1, CVehicle* pVehicle2, float arg3, float arg4, CVector* pVector1, CVector* pVector2);
    static float TestCollisionBetween2MovingRects_OnlyFrontBumper(CVehicle* pVehicle1, CVehicle* pVehicle2, float arg3, float arg4, CVector* pVector1, CVector* pVector2);
    static void TestWhetherToFirePlaneGuns(CVehicle* pVehicle, CEntity* pTarget);
    static bool ThisVehicleShouldTryNotToTurn(CVehicle* pVehicle);
    static void TriggerDogFightMoves(CVehicle* pVehicle1, CVehicle* pVehicle2);
    static void UpdateCarCount(CVehicle* pVehicle, uint8 bDecrease);
    static void UpdateCarOnRails(CVehicle* pVehicle);
    static void WeaveForObject(CEntity* pEntity, CVehicle* pVehicle, float* arg3, float* arg4);
    static void WeaveForOtherCar(CEntity* pEntity, CVehicle* pVehicle, float* arg3, float* arg4);
    static void WeaveThroughCarsSectorList(CPtrList& PtrList, CVehicle* pVehicle, CPhysical* pPhysical, float arg4, float arg5, float arg6, float arg7, float* arg8, float* arg9);
    static void WeaveThroughObjectsSectorList(CPtrList& PtrList, CVehicle* pVehicle, float arg3, float arg4, float arg5, float arg6, float* arg7, float* arg8);
    static void WeaveThroughPedsSectorList(CPtrList& PtrList, CVehicle* pVehicle, CPhysical* pPhysical, float arg4, float arg5, float arg6, float arg7, float* arg8, float* arg9);
};
