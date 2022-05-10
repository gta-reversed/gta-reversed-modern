/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CVehicle;

class CCarAI {
public:
    static void InjectHooks();

    static void AddAmbulanceOccupants(CVehicle* vehicle);
    static void AddFiretruckOccupants(CVehicle* vehicle);
    static void AddPoliceCarOccupants(CVehicle* vehicle, bool a2);

    static void BackToCruisingIfNoWantedLevel(CVehicle* vehicle);
    static void CarHasReasonToStop(CVehicle* vehicle);
    static void EntitiesGoHeadOn(CEntity* entity1, CEntity* entity2);

    static eCarMission FindPoliceBikeMissionForWantedLevel();
    static eCarMission FindPoliceBoatMissionForWantedLevel();
    static int8 FindPoliceCarMissionForWantedLevel();
    static int32 FindPoliceCarSpeedForWantedLevel(CVehicle* vehicle);
    static float FindSwitchDistanceClose(CVehicle* vehicle);
    static float FindSwitchDistanceFar(CVehicle* vehicle);

    static float GetCarToGoToCoors(CVehicle* vehicle, CVector* vec, int32 drivingStyle, bool bSpeedLimit20);
    static float GetCarToGoToCoorsAccurate(CVehicle* vehicle, CVector* vec, int32 drivingStyle, bool bSpeedLimit20);
    static float GetCarToGoToCoorsRacing(CVehicle* vehicle, CVector* vec, int32 drivingStyle, bool bSpeedLimit20);
    static float GetCarToGoToCoorsStraightLine(CVehicle* vehicle, CVector* vec, int32 drivingStyle, bool bSpeedLimit20);
    static float GetCarToParkAtCoors(CVehicle* vehicle, CVector* vec);

    static void MakeWayForCarWithSiren(CVehicle* vehicle);
    static void MellowOutChaseSpeed(CVehicle* vehicle);
    static void MellowOutChaseSpeedBoat(CVehicle* vehicle);

    static void TellCarToBlockOtherCar(CVehicle* vehicle1, CVehicle* vehicle2);
    static void TellCarToFollowOtherCar(CVehicle* vehicle1, CVehicle* vehicle2, float radius);
    static void TellCarToRamOtherCar(CVehicle* vehicle1, CVehicle* vehicle2);
    static void TellOccupantsToLeaveCar(CVehicle* vehicle);

    static void UpdateCarAI(CVehicle* vehicle);
};
