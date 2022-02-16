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
    static void BackToCruisingIfNoWantedLevel(CVehicle* vehicle);
    static void CarHasReasonToStop(CVehicle* vehicle);
    static void AddPoliceCarOccupants(CVehicle* vehicle, bool arg2);
    static void AddAmbulanceOccupants(CVehicle* vehicle);
    static void AddFiretruckOccupants(CVehicle* vehicle);
    static void TellOccupantsToLeaveCar(CVehicle* vehicle);
    static void TellCarToFollowOtherCar(CVehicle* vehicle1, CVehicle* vehicle2, float radius);
    static char FindPoliceBikeMissionForWantedLevel();
    static char FindPoliceBoatMissionForWantedLevel();
    static int32 FindPoliceCarSpeedForWantedLevel(CVehicle* vehicle);
    static float GetCarToGoToCoors(CVehicle* vehicle1, CVector* vec, int32 drivingStyle, bool bSpeedLimit20);
    static float GetCarToParkAtCoors(CVehicle* vehicle, CVector* vec);
    static void MellowOutChaseSpeed(CVehicle* vehicle);
    static void MakeWayForCarWithSiren(CVehicle* vehicle);
    static void UpdateCarAI(CVehicle* vehicle);
    static char FindPoliceCarMissionForWantedLevel();
};
