#include "StdInc.h"

/*
const float& CCarEnterExit::ms_fMaxSpeed_CanDragPedOut = *(float*)0x0;
const float& CCarEnterExit::ms_fMaxSpeed_PlayerCanDragPedOut = *(float*)0x0;
bool& CCarEnterExit::ms_bPedOffsetsCalculated = *(bool*)0x0;
CVector& CCarEnterExit::ms_vecPedGetUpAnimOffset = *(CVector*)0x0;
CVector& CCarEnterExit::ms_vecPedQuickDraggedOutCarAnimOffset = *(CVector*)0x0;
CVector& CCarEnterExit::ms_vecPedBedLAnimOffset = *(CVector*)0x0;
CVector& CCarEnterExit::ms_vecPedBedRAnimOffset = *(CVector*)0x0;
CVector& CCarEnterExit::ms_vecPedDeskAnimOffset = *(CVector*)0x0;
CVector& CCarEnterExit::ms_vecPedChairAnimOffset = *(CVector*)0x0;
*/

void CCarEnterExit::InjectHooks() {
//    ReversibleHooks::Install("CCarEnterExit", "AddInCarAnim", 0x0, &CCarEnterExit::AddInCarAnim);
//    ReversibleHooks::Install("CCarEnterExit", "CarHasDoorToClose", 0x0, &CCarEnterExit::CarHasDoorToClose);
//    ReversibleHooks::Install("CCarEnterExit", "CarHasDoorToOpen", 0x0, &CCarEnterExit::CarHasDoorToOpen);
//    ReversibleHooks::Install("CCarEnterExit", "CarHasOpenableDoor", 0x0, &CCarEnterExit::CarHasOpenableDoor);
//    ReversibleHooks::Install("CCarEnterExit", "CarHasPartiallyOpenDoor", 0x0, &CCarEnterExit::CarHasPartiallyOpenDoor);
//    ReversibleHooks::Install("CCarEnterExit", "ComputeDoorFlag", 0x0, &CCarEnterExit::ComputeDoorFlag);
//    ReversibleHooks::Install("CCarEnterExit", "ComputeOppositeDoorFlag", 0x0, &CCarEnterExit::ComputeOppositeDoorFlag);
//    ReversibleHooks::Install("CCarEnterExit", "ComputePassengerIndexFromCarDoor", 0x0, &CCarEnterExit::ComputePassengerIndexFromCarDoor);
//    ReversibleHooks::Install("CCarEnterExit", "ComputeSlowJackedPed", 0x0, &CCarEnterExit::ComputeSlowJackedPed);
//    ReversibleHooks::Install("CCarEnterExit", "ComputeTargetDoorToEnterAsPassenger", 0x0, &CCarEnterExit::ComputeTargetDoorToEnterAsPassenger);
//    ReversibleHooks::Install("CCarEnterExit", "ComputeTargetDoorToExit", 0x0, &CCarEnterExit::ComputeTargetDoorToExit);
//    ReversibleHooks::Install("CCarEnterExit", "GetNearestCarDoor", 0x0, &CCarEnterExit::GetNearestCarDoor);
//    ReversibleHooks::Install("CCarEnterExit", "GetNearestCarPassengerDoor", 0x0, &CCarEnterExit::GetNearestCarPassengerDoor);
//    ReversibleHooks::Install("CCarEnterExit", "GetPositionToOpenCarDoor", 0x0, &CCarEnterExit::GetPositionToOpenCarDoor);
//    ReversibleHooks::Install("CCarEnterExit", "IsCarDoorInUse", 0x0, &CCarEnterExit::IsCarDoorInUse);
//    ReversibleHooks::Install("CCarEnterExit", "IsCarDoorReady", 0x0, &CCarEnterExit::IsCarDoorReady);
//    ReversibleHooks::Install("CCarEnterExit", "IsCarQuickJackPossible", 0x0, &CCarEnterExit::IsCarQuickJackPossible);
//    ReversibleHooks::Install("CCarEnterExit", "IsCarSlowJackRequired", 0x0, &CCarEnterExit::IsCarSlowJackRequired);
//    ReversibleHooks::Install("CCarEnterExit", "IsClearToDriveAway", 0x0, &CCarEnterExit::IsClearToDriveAway);
//    ReversibleHooks::Install("CCarEnterExit", "IsPathToDoorBlockedByVehicleCollisionModel", 0x0, &CCarEnterExit::IsPathToDoorBlockedByVehicleCollisionModel);
//    ReversibleHooks::Install("CCarEnterExit", "IsPedHealthy", 0x0, &CCarEnterExit::IsPedHealthy);
//    ReversibleHooks::Install("CCarEnterExit", "IsPlayerToQuitCarEnter", 0x0, &CCarEnterExit::IsPlayerToQuitCarEnter);
//    ReversibleHooks::Install("CCarEnterExit", "IsRoomForPedToLeaveCar", 0x0, &CCarEnterExit::IsRoomForPedToLeaveCar);
//    ReversibleHooks::Install("CCarEnterExit", "IsVehicleHealthy", 0x0, &CCarEnterExit::IsVehicleHealthy);
//    ReversibleHooks::Install("CCarEnterExit", "IsVehicleStealable", 0x0, &CCarEnterExit::IsVehicleStealable);
//    ReversibleHooks::Install("CCarEnterExit", "MakeUndraggedDriverPedLeaveCar", 0x0, &CCarEnterExit::MakeUndraggedDriverPedLeaveCar);
//    ReversibleHooks::Install("CCarEnterExit", "MakeUndraggedPassengerPedsLeaveCar", 0x0, &CCarEnterExit::MakeUndraggedPassengerPedsLeaveCar);
//    ReversibleHooks::Install("CCarEnterExit", "QuitEnteringCar", 0x0, &CCarEnterExit::QuitEnteringCar);
//    ReversibleHooks::Install("CCarEnterExit", "RemoveCarSitAnim", 0x64F680, &CCarEnterExit::RemoveCarSitAnim);
//    ReversibleHooks::Install("CCarEnterExit", "RemoveGetInAnims", 0x64F6E0, &CCarEnterExit::RemoveGetInAnims);
//    ReversibleHooks::Install("CCarEnterExit", "SetAnimOffsetForEnterOrExitVehicle", 0x64F860, &CCarEnterExit::SetAnimOffsetForEnterOrExitVehicle);
//    ReversibleHooks::Install("CCarEnterExit", "SetPedInCarDirect", 0x650280, &CCarEnterExit::SetPedInCarDirect);
}

// 0x
void CCarEnterExit::AddInCarAnim(const CVehicle* vehicle, CPed* ped, bool bAsDriver) {
    plugin::Call<0x0, const CVehicle*, CPed*, bool>(vehicle, ped, bAsDriver);
}

// 0x
bool CCarEnterExit::CarHasDoorToClose(const CVehicle* vehicle, int doorId) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, int>(vehicle, doorId);
}

// 0x
bool CCarEnterExit::CarHasDoorToOpen(const CVehicle* vehicle, int doorId) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, int>(vehicle, doorId);
}

// 0x
bool CCarEnterExit::CarHasOpenableDoor(const CVehicle* vehicle, int doorId_UnusedArg, const CPed* ped) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, int, const CPed*>(vehicle, doorId_UnusedArg, ped);
}

// 0x
bool CCarEnterExit::CarHasPartiallyOpenDoor(const CVehicle* vehicle, int doorId) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, int>(vehicle, doorId);
}

// 0x
int CCarEnterExit::ComputeDoorFlag(const CVehicle* vehicle, int doorId, bool bCheckVehicleType) {
    return plugin::CallAndReturn<int, 0x0, const CVehicle*, int, bool>(vehicle, doorId, bCheckVehicleType);
}

// 0x
int CCarEnterExit::ComputeOppositeDoorFlag(const CVehicle* vehicle, int doorId, bool bCheckVehicleType) {
    return plugin::CallAndReturn<int, 0x0, const CVehicle*, int, bool>(vehicle, doorId, bCheckVehicleType);
}

// 0x
signed int CCarEnterExit::ComputePassengerIndexFromCarDoor(const CVehicle* vehicle, int doorId) {
    return plugin::CallAndReturn<signed int, 0x0, const CVehicle*, int>(vehicle, doorId);
}

// 0x
int CCarEnterExit::ComputeSlowJackedPed(const CVehicle* vehicle, int doorId) {
    return plugin::CallAndReturn<int, 0x0, const CVehicle*, int>(vehicle, doorId);
}

// 0x
signed int CCarEnterExit::ComputeTargetDoorToEnterAsPassenger(const CVehicle* vehicle, int nPassengerNum) {
    return plugin::CallAndReturn<signed int, 0x0, const CVehicle*, int>(vehicle, nPassengerNum);
}

// 0x
int CCarEnterExit::ComputeTargetDoorToExit(const CVehicle* vehicle, const CPed* ped) {
    return plugin::CallAndReturn<int, 0x0, const CVehicle*, const CPed*>(vehicle, ped);
}

// 0x
bool CCarEnterExit::GetNearestCarDoor(const CPed* ped, const CVehicle* vehicle, CVector* outPos, int doorId) {
    return plugin::CallAndReturn<bool, 0x0, const CPed*, const CVehicle*, CVector*, int>(ped, vehicle, outPos, doorId);
}

// 0x
bool CCarEnterExit::GetNearestCarPassengerDoor(const CPed* ped, const CVehicle* vehicle, CVector* outVec, int* doorId, bool flag1, bool flag2, bool flag3) {
    return plugin::CallAndReturn<bool, 0x0, const CPed*, const CVehicle*, CVector*, int*, bool, bool, bool>(ped, vehicle, outVec, doorId, flag1, flag2, flag3);
}

// 0x
CVector* CCarEnterExit::GetPositionToOpenCarDoor(CVector* out, const CVehicle* vehicle, int doorId) {
    return plugin::CallAndReturn<CVector*, 0x0, CVector*, const CVehicle*, int>(out, vehicle, doorId);
}

// 0x
bool CCarEnterExit::IsCarDoorInUse(const CVehicle* vehicle, int firstDoorId, int secondDoorId) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, int, int>(vehicle, firstDoorId, secondDoorId);
}

// 0x
bool CCarEnterExit::IsCarDoorReady(const CVehicle* vehicle, int doorId) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, int>(vehicle, doorId);
}

// 0x
bool CCarEnterExit::IsCarQuickJackPossible(const CVehicle* vehicle, int doorId, const CPed* ped) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, int, const CPed*>(vehicle, doorId, ped);
}

// 0x
bool CCarEnterExit::IsCarSlowJackRequired(const CVehicle* vehicle, int doorId) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, int>(vehicle, doorId);
}

// 0x
bool CCarEnterExit::IsClearToDriveAway(const CVehicle* outVehicle) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*>(outVehicle);
}

// 0x
bool CCarEnterExit::IsPathToDoorBlockedByVehicleCollisionModel(const CPed* ped, CVehicle* vehicle, const CVector* pos) {
    return plugin::CallAndReturn<bool, 0x0, const CPed*, CVehicle*, const CVector*>(ped, vehicle, pos);
}

// 0x
bool CCarEnterExit::IsPedHealthy(CPed* vehicle) {
    return plugin::CallAndReturn<bool, 0x0, CPed*>(vehicle);
}

// 0x
bool CCarEnterExit::IsPlayerToQuitCarEnter(const CPed* ped, const CVehicle* vehicle, int startTime, CTask* task) {
    return plugin::CallAndReturn<bool, 0x0, const CPed*, const CVehicle*, int, CTask*>(ped, vehicle, startTime, task);
}

// 0x
bool CCarEnterExit::IsRoomForPedToLeaveCar(const CVehicle* vehicle, int doorId, CVector* pos) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, int, CVector*>(vehicle, doorId, pos);
}

// 0x
bool CCarEnterExit::IsVehicleHealthy(const CVehicle* vehicle) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*>(vehicle);
}

// 0x
bool CCarEnterExit::IsVehicleStealable(const CVehicle* vehicle, const CPed* ped) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, const CPed*>(vehicle, ped);
}

void CCarEnterExit::MakeUndraggedDriverPedLeaveCar(const CVehicle* vehicle, const CPed* ped) {
    plugin::Call<0x0, const CVehicle*, const CPed*>(vehicle, ped);
}

void CCarEnterExit::MakeUndraggedPassengerPedsLeaveCar(const CVehicle* targetVehicle, const CPed* draggedPed, const CPed* ped) {
    plugin::Call<0x0, const CVehicle*, const CPed*, const CPed*>(targetVehicle, draggedPed, ped);
}

// unused
void CCarEnterExit::QuitEnteringCar(CPed* ped, CVehicle* vehicle, int doorId, bool bCarWasBeingJacked) {}

// 0x64F680
void CCarEnterExit::RemoveCarSitAnim(CPed* ped) {
    plugin::Call<0x64F680, CPed*>(ped);
}

// 0x64F6E0
void CCarEnterExit::RemoveGetInAnims(const CPed* ped) {
    plugin::Call<0x64F6E0, const CPed*>(ped);
}

// 0x64F860
void CCarEnterExit::SetAnimOffsetForEnterOrExitVehicle() {
    plugin::Call<0x64F860>();
}

// 0x650280
void CCarEnterExit::SetPedInCarDirect(CPed* ped, CVehicle* vehicle, int seatNumber, bool bAsDriver) {
    plugin::Call<0x650280, CPed*, CVehicle*, int, bool>(ped, vehicle, seatNumber, bAsDriver);
}
