/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVehicle.h"
#include "CVector.h"
#include "CPed.h"
#include "CTask.h"

class  CCarEnterExit {
public:
     static float const &ms_fMaxSpeed_CanDragPedOut;
     static float const &ms_fMaxSpeed_PlayerCanDragPedOut;
     static bool &ms_bPedOffsetsCalculated;
     static CVector &ms_vecPedGetUpAnimOffset;
     static CVector &ms_vecPedQuickDraggedOutCarAnimOffset;
     static CVector &ms_vecPedBedLAnimOffset;
     static CVector &ms_vecPedBedRAnimOffset;
     static CVector &ms_vecPedDeskAnimOffset;
     static CVector &ms_vecPedChairAnimOffset;

     static void AddInCarAnim(CVehicle const *vehicle, CPed *ped, bool bAsDriver);
     static bool CarHasDoorToClose(CVehicle const *vehicle, int doorId);
     static bool CarHasDoorToOpen(CVehicle const *vehicle, int doorID);
     static bool CarHasOpenableDoor(CVehicle const *vehicle, int DoorID_UnusedArg, CPed const *ped);
     static bool CarHasPartiallyOpenDoor(CVehicle const *vehicle, int doorID);
     static int ComputeDoorFlag(CVehicle const *vehicle, int doorId, bool bCheckVehicleType);
     static int ComputeOppositeDoorFlag(CVehicle const *vehicle, int doorId, bool bCheckVehicleType);
     static signed int ComputePassengerIndexFromCarDoor(CVehicle const *vehicle, int doorID);
     static int ComputeSlowJackedPed(CVehicle const *vehicle, int doorID);
     static signed int ComputeTargetDoorToEnterAsPassenger(CVehicle const *pVehicle, int nPassengerNum);
     static int ComputeTargetDoorToExit(CVehicle const *pVehicle, CPed const *pPed);
     static bool GetNearestCarDoor(CPed const *pPed, CVehicle const *pVehicle, CVector *outPos, int doorID);
     static bool GetNearestCarPassengerDoor(CPed const *ped, CVehicle const *vehicle, CVector *outVec, int *doorId, bool flag1, bool flag2, bool flag3);
     static CVector *GetPositionToOpenCarDoor(CVector *out, CVehicle const *vehicle, int doorId);
     static bool IsCarDoorInUse(CVehicle const *vehicle, int door1Id, int door2Id);
     static bool IsCarDoorReady(CVehicle const *vehicle, int doorID);
     static bool IsCarQuickJackPossible(CVehicle const *vehicle, int doorID, CPed const *ped);
     static bool IsCarSlowJackRequired(CVehicle const *vehicle, int doorID);
     static bool IsClearToDriveAway(CVehicle const *outVehicle);
     static bool IsPathToDoorBlockedByVehicleCollisionModel(CPed const *ped, CVehicle *vehicle, CVector const *pos);
     static bool IsPedHealthy(CPed *vehicle);
     static bool IsPlayerToQuitCarEnter(CPed const *ped, CVehicle const *vehicle, int StartTime, CTask *task);
     static bool IsRoomForPedToLeaveCar(CVehicle const *veh, int doorID, CVector *pos);
     static bool IsVehicleHealthy(CVehicle const *vehicle);
     static bool IsVehicleStealable(CVehicle const *vehicle, CPed const *ped);
     static void MakeUndraggedDriverPedLeaveCar(CVehicle const *vehicle, CPed const *ped);
     static void MakeUndraggedPassengerPedsLeaveCar(CVehicle const *targetVehicle, CPed const *draggedPed, CPed const *ped);
    //! unused
     static void QuitEnteringCar(CPed *ped, CVehicle *vehicle, int doorID, bool bCarWasBeingJacked);
     static void RemoveCarSitAnim(CPed* ped);
     static void RemoveGetInAnims(CPed const *ped);
     static void SetAnimOffsetForEnterOrExitVehicle();
     static void SetPedInCarDirect(CPed *ped, CVehicle *vehicle, int seatNumber, bool bAsDriver);
};

//#include "meta/meta.CCarEnterExit.h"
