/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CVehicle.h"
#include "CVector.h"
#include "CPed.h"
#include "CTask.h"

class CCarEnterExit {
public:
    static const float& ms_fMaxSpeed_CanDragPedOut;
    static const float& ms_fMaxSpeed_PlayerCanDragPedOut;
    static bool& ms_bPedOffsetsCalculated;
    static CVector& ms_vecPedGetUpAnimOffset;
    static CVector& ms_vecPedQuickDraggedOutCarAnimOffset;
    static CVector& ms_vecPedBedLAnimOffset;
    static CVector& ms_vecPedBedRAnimOffset;
    static CVector& ms_vecPedDeskAnimOffset;
    static CVector& ms_vecPedChairAnimOffset;

public:
    static void InjectHooks();

    static void AddInCarAnim(const CVehicle* vehicle, CPed* ped, bool bAsDriver);
    static bool CarHasDoorToClose(const CVehicle* vehicle, int doorId);
    static bool CarHasDoorToOpen(const CVehicle* vehicle, int doorId);
    static bool CarHasOpenableDoor(const CVehicle* vehicle, int doorId_UnusedArg, const CPed* ped);
    static bool CarHasPartiallyOpenDoor(const CVehicle* vehicle, int doorId);
    static int ComputeDoorFlag(const CVehicle* vehicle, int doorId, bool bCheckVehicleType);
    static int ComputeOppositeDoorFlag(const CVehicle* vehicle, int doorId, bool bCheckVehicleType);
    static signed int ComputePassengerIndexFromCarDoor(const CVehicle* vehicle, int doorId);
    static int ComputeSlowJackedPed(const CVehicle* vehicle, int doorId);
    static signed int ComputeTargetDoorToEnterAsPassenger(const CVehicle* vehicle, int nPassengerNum);
    static int ComputeTargetDoorToExit(const CVehicle* vehicle, const CPed* ped);
    static bool GetNearestCarDoor(const CPed* ped, const CVehicle* vehicle, CVector* outPos, int doorId);
    static bool GetNearestCarPassengerDoor(const CPed* ped, const CVehicle* vehicle, CVector* outVec, int* doorId, bool flag1, bool flag2, bool flag3);
    static CVector* GetPositionToOpenCarDoor(CVector* out, const CVehicle* vehicle, int doorId);
    static bool IsCarDoorInUse(const CVehicle* vehicle, int firstDoorId, int secondDoorId);
    static bool IsCarDoorReady(const CVehicle* vehicle, int doorId);
    static bool IsCarQuickJackPossible(const CVehicle* vehicle, int doorId, const CPed* ped);
    static bool IsCarSlowJackRequired(const CVehicle* vehicle, int doorId);
    static bool IsClearToDriveAway(const CVehicle* outVehicle);
    static bool IsPathToDoorBlockedByVehicleCollisionModel(const CPed* ped, CVehicle* vehicle, const CVector* pos);
    static bool IsPedHealthy(CPed* vehicle);
    static bool IsPlayerToQuitCarEnter(const CPed* ped, const CVehicle* vehicle, int startTime, CTask* task);
    static bool IsRoomForPedToLeaveCar(const CVehicle* vehicle, int doorId, CVector* pos);
    static bool IsVehicleHealthy(const CVehicle* vehicle);
    static bool IsVehicleStealable(const CVehicle* vehicle, const CPed* ped);
    static void MakeUndraggedDriverPedLeaveCar(const CVehicle* vehicle, const CPed* ped);
    static void MakeUndraggedPassengerPedsLeaveCar(const CVehicle* targetVehicle, const CPed* draggedPed, const CPed* ped);
    static void QuitEnteringCar(CPed* ped, CVehicle* vehicle, int doorId, bool bCarWasBeingJacked);
    static void RemoveCarSitAnim(CPed* ped);
    static void RemoveGetInAnims(const CPed* ped);
    static void SetAnimOffsetForEnterOrExitVehicle();
    static void SetPedInCarDirect(CPed* ped, CVehicle* vehicle, int seatNumber, bool bAsDriver);
};
