#include "StdInc.h"

/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

// 0x41BFA0
void CCarAI::BackToCruisingIfNoWantedLevel(CVehicle* pVehicle) {
	plugin::Call<0x41BFA0, CVehicle*>(pVehicle);
}

// 0x41C050
void CCarAI::CarHasReasonToStop(CVehicle* pVehicle) {
	plugin::Call<0x41C050, CVehicle*>(pVehicle);
}

// 0x41C070
void CCarAI::AddPoliceCarOccupants(CVehicle* pVehicle, bool arg2) {
	plugin::Call<0x41C070, CVehicle*, bool>(pVehicle, arg2);
}

// 0x41C4A0
void CCarAI::AddAmbulanceOccupants(CVehicle* pVehicle) {
	plugin::Call<0x41C4A0, CVehicle*>(pVehicle);
}

// 0x41C600
void CCarAI::AddFiretruckOccupants(CVehicle* pVehicle) {
	plugin::Call<0x41C600, CVehicle*>(pVehicle);
}

// 0x41C760
void CCarAI::TellOccupantsToLeaveCar(CVehicle* pVehicle) {
	plugin::Call<0x41C760, CVehicle*>(pVehicle);
}

// 0x41C960
void CCarAI::TellCarToFollowOtherCar(CVehicle* pVehicle1, CVehicle* pVehicle2, float radius) {
	plugin::Call<0x41C960, CVehicle*, CVehicle*, float>(pVehicle1, pVehicle2, radius);
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
int32 CCarAI::FindPoliceCarSpeedForWantedLevel(CVehicle* pVehicle) {
	return plugin::CallAndReturn<int32, 0x41CAA0, CVehicle*>(pVehicle);
}

// 0x41CE30
float CCarAI::GetCarToGoToCoors(CVehicle* pVehicle1, CVector* pVector, int32 drivingStyle, bool bSpeedLimit20) {
	return plugin::CallAndReturn<float, 0x41CE30, CVehicle*, CVector*, int32, bool>(pVehicle1, pVector, drivingStyle, bSpeedLimit20);
}

// 0x41D350
float CCarAI::GetCarToParkAtCoors(CVehicle* pVehicle, CVector* pVector) {
	return plugin::CallAndReturn<float, 0x41D350, CVehicle*, CVector*>(pVehicle, pVector);
}

// 0x41D3D0
void CCarAI::MellowOutChaseSpeed(CVehicle* pVehicle) {
	plugin::Call<0x41D3D0, CVehicle*>(pVehicle);
}

// 0x41D660
void CCarAI::MakeWayForCarWithSiren(CVehicle* pVehicle) {
	plugin::Call<0x41D660, CVehicle*>(pVehicle);
}

// 0x41DA30
void CCarAI::UpdateCarAI(CVehicle* pVehicle) {
	plugin::Call<0x41DA30, CVehicle*>(pVehicle);
}

// 0x41C9D0
char CCarAI::FindPoliceCarMissionForWantedLevel() {
	return plugin::CallAndReturn<char, 0x41C9D0>();
}