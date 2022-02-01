/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CVehicle;

class CCarAI
{
public:

	static void BackToCruisingIfNoWantedLevel(CVehicle* pVehicle);
	static void CarHasReasonToStop(CVehicle* pVehicle);
	static void AddPoliceCarOccupants(CVehicle* pVehicle, bool arg2);
	static void AddAmbulanceOccupants(CVehicle* pVehicle);
	static void AddFiretruckOccupants(CVehicle* pVehicle);
	static void TellOccupantsToLeaveCar(CVehicle* pVehicle);
	static void TellCarToFollowOtherCar(CVehicle* pVehicle1, CVehicle* pVehicle2, float radius);
	static char FindPoliceBikeMissionForWantedLevel();
	static char FindPoliceBoatMissionForWantedLevel();
	static int32 FindPoliceCarSpeedForWantedLevel(CVehicle* pVehicle);
	static float GetCarToGoToCoors(CVehicle* pVehicle1, CVector* pVector, int32 drivingStyle, bool bSpeedLimit20);
	static float GetCarToParkAtCoors(CVehicle* pVehicle, CVector* pVector);
	static void MellowOutChaseSpeed(CVehicle* pVehicle);
	static void MakeWayForCarWithSiren(CVehicle* pVehicle);
	static void UpdateCarAI(CVehicle* pVehicle);
	static char FindPoliceCarMissionForWantedLevel();

};
