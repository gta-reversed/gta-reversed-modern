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
//    RH_ScopedInstall(AddInCarAnim, 0x0);
//    RH_ScopedInstall(CarHasDoorToClose, 0x0);
//    RH_ScopedInstall(CarHasDoorToOpen, 0x0);
//    RH_ScopedInstall(CarHasOpenableDoor, 0x0);
//    RH_ScopedInstall(CarHasPartiallyOpenDoor, 0x0);
//    RH_ScopedInstall(ComputeDoorFlag, 0x0);
//    RH_ScopedInstall(ComputeOppositeDoorFlag, 0x0);
//    RH_ScopedInstall(ComputePassengerIndexFromCarDoor, 0x0);
//    RH_ScopedInstall(ComputeSlowJackedPed, 0x0);
//    RH_ScopedInstall(ComputeTargetDoorToEnterAsPassenger, 0x0);
//    RH_ScopedInstall(ComputeTargetDoorToExit, 0x0);
//    RH_ScopedInstall(GetNearestCarDoor, 0x0);
//    RH_ScopedInstall(GetNearestCarPassengerDoor, 0x0);
//    RH_ScopedInstall(GetPositionToOpenCarDoor, 0x0);
//    RH_ScopedInstall(IsCarDoorInUse, 0x0);
//    RH_ScopedInstall(IsCarDoorReady, 0x0);
//    RH_ScopedInstall(IsCarQuickJackPossible, 0x0);
//    RH_ScopedInstall(IsCarSlowJackRequired, 0x0);
//    RH_ScopedInstall(IsClearToDriveAway, 0x0);
//    RH_ScopedInstall(IsPathToDoorBlockedByVehicleCollisionModel, 0x0);
//    RH_ScopedInstall(IsPedHealthy, 0x0);
//    RH_ScopedInstall(IsPlayerToQuitCarEnter, 0x0);
//    RH_ScopedInstall(IsRoomForPedToLeaveCar, 0x0);
//    RH_ScopedInstall(IsVehicleHealthy, 0x0);
//    RH_ScopedInstall(IsVehicleStealable, 0x0);
//    RH_ScopedInstall(MakeUndraggedDriverPedLeaveCar, 0x0);
//    RH_ScopedInstall(MakeUndraggedPassengerPedsLeaveCar, 0x0);
//    RH_ScopedInstall(QuitEnteringCar, 0x0);
//    RH_ScopedInstall(RemoveCarSitAnim, 0x64F680);
//    RH_ScopedInstall(RemoveGetInAnims, 0x64F6E0);
//    RH_ScopedInstall(SetAnimOffsetForEnterOrExitVehicle, 0x64F860);
//    RH_ScopedInstall(SetPedInCarDirect, 0x650280);
}

// 0x
void CCarEnterExit::AddInCarAnim(const CVehicle* vehicle, CPed* ped, bool bAsDriver) {
    plugin::Call<0x0, const CVehicle*, CPed*, bool>(vehicle, ped, bAsDriver);
}

// 0x
bool CCarEnterExit::CarHasDoorToClose(const CVehicle* vehicle, int32 doorId) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, int32>(vehicle, doorId);
}

// 0x
bool CCarEnterExit::CarHasDoorToOpen(const CVehicle* vehicle, int32 doorId) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, int32>(vehicle, doorId);
}

// 0x
bool CCarEnterExit::CarHasOpenableDoor(const CVehicle* vehicle, int32 doorId_UnusedArg, const CPed* ped) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, int32, const CPed*>(vehicle, doorId_UnusedArg, ped);
}

// 0x
bool CCarEnterExit::CarHasPartiallyOpenDoor(const CVehicle* vehicle, int32 doorId) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, int32>(vehicle, doorId);
}

// 0x
int32 CCarEnterExit::ComputeDoorFlag(const CVehicle* vehicle, int32 doorId, bool bCheckVehicleType) {
    return plugin::CallAndReturn<int32, 0x0, const CVehicle*, int32, bool>(vehicle, doorId, bCheckVehicleType);
}

// 0x
int32 CCarEnterExit::ComputeOppositeDoorFlag(const CVehicle* vehicle, int32 doorId, bool bCheckVehicleType) {
    return plugin::CallAndReturn<int32, 0x0, const CVehicle*, int32, bool>(vehicle, doorId, bCheckVehicleType);
}

// 0x
signed int CCarEnterExit::ComputePassengerIndexFromCarDoor(const CVehicle* vehicle, int32 doorId) {
    return plugin::CallAndReturn<signed int, 0x0, const CVehicle*, int32>(vehicle, doorId);
}

// 0x
int32 CCarEnterExit::ComputeSlowJackedPed(const CVehicle* vehicle, int32 doorId) {
    return plugin::CallAndReturn<int32, 0x0, const CVehicle*, int32>(vehicle, doorId);
}

// 0x
signed int CCarEnterExit::ComputeTargetDoorToEnterAsPassenger(const CVehicle* vehicle, int32 nPassengerNum) {
    return plugin::CallAndReturn<signed int, 0x0, const CVehicle*, int32>(vehicle, nPassengerNum);
}

// 0x
int32 CCarEnterExit::ComputeTargetDoorToExit(const CVehicle* vehicle, const CPed* ped) {
    return plugin::CallAndReturn<int32, 0x0, const CVehicle*, const CPed*>(vehicle, ped);
}

// 0x
bool CCarEnterExit::GetNearestCarDoor(const CPed* ped, const CVehicle* vehicle, CVector* outPos, int32 doorId) {
    return plugin::CallAndReturn<bool, 0x0, const CPed*, const CVehicle*, CVector*, int32>(ped, vehicle, outPos, doorId);
}

// 0x
bool CCarEnterExit::GetNearestCarPassengerDoor(const CPed* ped, const CVehicle* vehicle, CVector* outVec, int32* doorId, bool flag1, bool flag2, bool flag3) {
    return plugin::CallAndReturn<bool, 0x0, const CPed*, const CVehicle*, CVector*, int32*, bool, bool, bool>(ped, vehicle, outVec, doorId, flag1, flag2, flag3);
}

// 0x
CVector* CCarEnterExit::GetPositionToOpenCarDoor(CVector* out, const CVehicle* vehicle, int32 doorId) {
    return plugin::CallAndReturn<CVector*, 0x0, CVector*, const CVehicle*, int32>(out, vehicle, doorId);
}

// 0x
bool CCarEnterExit::IsCarDoorInUse(const CVehicle* vehicle, int32 firstDoorId, int32 secondDoorId) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, int32, int32>(vehicle, firstDoorId, secondDoorId);
}

// 0x
bool CCarEnterExit::IsCarDoorReady(const CVehicle* vehicle, int32 doorId) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, int32>(vehicle, doorId);
}

// 0x
bool CCarEnterExit::IsCarQuickJackPossible(const CVehicle* vehicle, int32 doorId, const CPed* ped) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, int32, const CPed*>(vehicle, doorId, ped);
}

// 0x
bool CCarEnterExit::IsCarSlowJackRequired(const CVehicle* vehicle, int32 doorId) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, int32>(vehicle, doorId);
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
bool CCarEnterExit::IsPlayerToQuitCarEnter(const CPed* ped, const CVehicle* vehicle, int32 startTime, CTask* task) {
    return plugin::CallAndReturn<bool, 0x0, const CPed*, const CVehicle*, int32, CTask*>(ped, vehicle, startTime, task);
}

// 0x
bool CCarEnterExit::IsRoomForPedToLeaveCar(const CVehicle* vehicle, int32 doorId, CVector* pos) {
    return plugin::CallAndReturn<bool, 0x0, const CVehicle*, int32, CVector*>(vehicle, doorId, pos);
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
void CCarEnterExit::QuitEnteringCar(CPed* ped, CVehicle* vehicle, int32 doorId, bool bCarWasBeingJacked) {}

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
void CCarEnterExit::SetPedInCarDirect(CPed* ped, CVehicle* vehicle, int32 seatNumber, bool bAsDriver) {
    plugin::Call<0x650280, CPed*, CVehicle*, int32, bool>(ped, vehicle, seatNumber, bAsDriver);
}
