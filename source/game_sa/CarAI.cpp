/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "CarAI.h"

// 0x41BFA0
void CCarAI::BackToCruisingIfNoWantedLevel(CVehicle* vehicle) {
    plugin::Call<0x41BFA0, CVehicle*>(vehicle);
}

// 0x41C050
void CCarAI::CarHasReasonToStop(CVehicle* vehicle) {
    plugin::Call<0x41C050, CVehicle*>(vehicle);
}

// 0x41C070
void CCarAI::AddPoliceCarOccupants(CVehicle* vehicle, bool arg2) {
    plugin::Call<0x41C070, CVehicle*, bool>(vehicle, arg2);
}

// 0x41C4A0
void CCarAI::AddAmbulanceOccupants(CVehicle* vehicle) {
    plugin::Call<0x41C4A0, CVehicle*>(vehicle);
}

// 0x41C600
void CCarAI::AddFiretruckOccupants(CVehicle* vehicle) {
    plugin::Call<0x41C600, CVehicle*>(vehicle);
}

// 0x41C760
void CCarAI::TellOccupantsToLeaveCar(CVehicle* vehicle) {
    plugin::Call<0x41C760, CVehicle*>(vehicle);
}

// 0x41C960
void CCarAI::TellCarToFollowOtherCar(CVehicle* vehicle1, CVehicle* vehicle2, float radius) {
    plugin::Call<0x41C960, CVehicle*, CVehicle*, float>(vehicle1, vehicle2, radius);
}

// 0x2B
char CCarAI::FindPoliceBikeMissionForWantedLevel() {
    return plugin::CallAndReturn<char, 0x41CA40>();
}

// 0x41CA50
char CCarAI::FindPoliceBoatMissionForWantedLevel() {
    return plugin::CallAndReturn<char, 0x41CA50>();
}

// 0x41CAA0
int32 CCarAI::FindPoliceCarSpeedForWantedLevel(CVehicle* vehicle) {
    return plugin::CallAndReturn<int32, 0x41CAA0, CVehicle*>(vehicle);
}

// 0x41CE30
float CCarAI::GetCarToGoToCoors(CVehicle* vehicle1, CVector* vec, int32 drivingStyle, bool bSpeedLimit20) {
    return plugin::CallAndReturn<float, 0x41CE30, CVehicle*, CVector*, int32, bool>(vehicle1, vec, drivingStyle, bSpeedLimit20);
}

// 0x41D350
float CCarAI::GetCarToParkAtCoors(CVehicle* vehicle, CVector* vec) {
    return plugin::CallAndReturn<float, 0x41D350, CVehicle*, CVector*>(vehicle, vec);
}

// 0x41D3D0
void CCarAI::MellowOutChaseSpeed(CVehicle* vehicle) {
    plugin::Call<0x41D3D0, CVehicle*>(vehicle);
}

// 0x41D660
void CCarAI::MakeWayForCarWithSiren(CVehicle* vehicle) {
    plugin::Call<0x41D660, CVehicle*>(vehicle);
}

// 0x41DA30
void CCarAI::UpdateCarAI(CVehicle* vehicle) {
    plugin::Call<0x41DA30, CVehicle*>(vehicle);
}

// 0x41C9D0
char CCarAI::FindPoliceCarMissionForWantedLevel() {
    return plugin::CallAndReturn<char, 0x41C9D0>();
}
