/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

// Based on https://gtamods.com/wiki/Garage

#include "Garage.h"

class CVehicle;
class CObject;
class CVector;

class CGarages {
public:
    static inline CStoredCar (&aCarsInSafeHouse)[20][4] = *(CStoredCar(*)[20][4])0x96ABD4;
    static inline CGarage    (&aGarages)[50] = *(CGarage(*)[50])0x96C048;
    static inline char       (&MessageIDString)[8] = *(char (*)[8])0x96C014;
    static inline int32&     LastGaragePlayerWasIn = *(int32*)0x96BFDC;
    static inline int32&     LastTimeHelpMessage = *(int32*)0x96BFE0;
    static inline int8&      bCamShouldBeOutside = *(int8*)0x96BFE4;
    static inline int32&     CrushedCarId = *(int32*)0x96BFE8;
    static inline int32      (&CarTypesCollected)[4] = *(int32(*)[4])0x96BFEC;
    static inline int32&     PoliceCarsCollected = *(int32*)0x96BFFC;
    static inline int32&     BankVansCollected = *(int32*)0x96C000;
    static inline int32&     CarsCollected = *(int32*)0x96C004;
    static inline bool&      NoResprays = *(bool*)0x96C008;
    static inline int8&      RespraysAreFree = *(int8*)0x96C009;
    static inline int8&      BombsAreFree = *(int8*)0x96C00A;
    static inline int8&      PlayerInGarage = *(int8*)0x96C00B;
    static inline int32&     MessageNumberInString = *(int32*)0x96C00C;
    static inline int32&     MessageNumberInString2 = *(int32*)0x96C010;
    static inline int32&     MessageEndTime = *(int32*)0x96C01C;
    static inline int32&     MessageStartTime = *(int32*)0x96C020;
    static inline int32&     NumGarages = *(int32*)0x96C024;
    static inline CGarage*&  pOldToGarageWeAreIn = *(CGarage**)0x96BFD8;

public:
    static void InjectHooks();

    static void Init();
    static void Init_AfterRestart();
    static void Shutdown();
    static void AddOne(float x1, float y1, float z1, float frontX, float frontY, float x2, float y2, float z2, uint8 type, uint32 a10, char* name, uint32 argFlags);
    static void CloseHideOutGaragesBeforeSave();
    static void PlayerArrestedOrDied();
    static void AllRespraysCloseOrOpen(bool state);
    static int32 FindSafeHouseIndexForGarageType(eGarageType gtype);
    static int16 FindGarageForObject(CObject*);
    static bool IsModelIndexADoor(int32 model);
    static bool IsPointWithinHideOutGarage(const CVector& point);
    static bool IsGarageOpen(int16 garageId);
    static bool IsGarageClosed(int16 garageId);
    static bool IsCarSprayable(CVehicle* vehicle);
    static void Update();
    static void ActivateGarage(int16 a1);
    static void DeactivateGarage(int16 garageId);
    static void SetTargetCar(int16 garageId, CVehicle* veh);
    static void TriggerMessage(const char* tagMsg, int16 msgMin, uint16 time, int16 msgMax);
    static void PrintMessages();
    static void SetGarageType(int16 garageId, eGarageType type, int32 unused);
    static int16 GetGarageNumberByName(const char* name);
    static bool Load();
    static bool Save();

    static CGarage& GetGarage(int32 iGarageInd) { return aGarages[iGarageInd]; }
    static CStoredCar* GetStoredCarsInSafehouse(int32 iSafehouseInd) { return aCarsInSafeHouse[iSafehouseInd]; }
    static CStoredCar& GetStoredCar(int32 iSafehouseInd, int32 iCarInd) { return aCarsInSafeHouse[iSafehouseInd][iCarInd]; }

    // todo :
    // 0x298F74 FindGarageIndex(char*)
    // 0x299008 void ChangeGarageType(int16, uchar, uint32)
    // 0x2994F8 void SetTargetCarForMissionGarage(int16, CAutomobile*)
    // 0x2995A4 bool HasCarBeenDroppedOffYet(int16 garageId) { return aGarages[garageId].m_nDoorState == GARAGE_DOOR_CLOSED_DROPPED_CAR; }
    // 0x2996BC bool HasResprayHappened(int16 garageId)
    // 0x299798 bool CameraShouldBeOutside() { return bCamShouldBeOutside; }
    // 0x299F08 void GivePlayerDetonator()
    // 0x299F24 float FindDoorHeightForMI(uint32)
    // 0x29A024 bool IsPointInAGarageCameraZone(CVector point)
    // 0x29A600 bool IsThisCarWithinGarageArea(int16 garageId, CEntity* entity) { return aGarages[garageId].IsEntityEntirelyInside3D(entity, 0.0f); }
    // 0x29AED0 StopCarFromBlowingUp(CAutomobile* vehicle)
    // 0x29B788 bool IsPointWithinAnyGarage(CVector& point)
    // 0x29B838 int32 CountCarsInHideoutGarage(uint8)
    // 0x29DC5C void StoreCarInNearestImpoundingGarage(CVehicle* vehicle)
};
