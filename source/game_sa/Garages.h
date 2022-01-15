/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

// Based on https://gtamods.com/wiki/Garage

#include "Garage.h"
#include <Base.h>

class CVehicle;
class CObject;
class CVector;

class CGarages {
public:
    static inline CStoredCar(&aCarsInSafeHouse)[20][4] = *(CStoredCar(*)[20][4])0x96ABD4;
    static inline CGarage(&aGarages)[50] = *(CGarage(*)[50])0x96C048;
    static inline char(&MessageIDString)[8] = *(char(*)[8])0x96C014;
    static inline int32& LastGaragePlayerWasIn = *(int32*)0x96BFDC;
    static inline int32& LastTimeHelpMessage = *(int32*)0x96BFE0;
    static inline int8& bCamShouldBeOutside = *(int8*)0x96BFE4;
    static inline int32& CrushedCarId = *(int32*)0x96BFE8;
    static inline int32& CarTypesCollected = *(int32*)0x96BFEC;
    static inline int32& PoliceCarsCollected = *(int32*)0x96BFFC;
    static inline int32& BankVansCollected = *(int32*)0x96C000;
    static inline int32& CarsCollected = *(int32*)0x96C004;
    static inline bool& NoResprays = *(bool*)0x96C008;
    static inline int8& RespraysAreFree = *(int8*)0x96C009;
    static inline int8& BombsAreFree = *(int8*)0x96C00A;
    static inline int8& PlayerInGarage = *(int8*)0x96C00B;
    static inline int32& MessageNumberInString = *(int32*)0x96C00C;
    static inline int32& MessageNumberInString2 = *(int32*)0x96C010;
    static inline int32& MessageEndTime = *(int32*)0x96C01C;
    static inline int32& MessageStartTime = *(int32*)0x96C020;
    static inline int32& NumGarages = *(int32*)0x96C024;
    static inline CGarage*& pOldToGarageWeAreIn = *(CGarage**)0x96BFD8;

public:
    static void InjectHooks();

    static void Init();
    static void CloseHideOutGaragesBeforeSave();
    static void PlayerArrestedOrDied();
    static void Init_AfterRestart();
    static void AllRespraysCloseOrOpen(bool state);
    static bool IsModelIndexADoor(int32 model);
    static int32 FindSafeHouseIndexForGarageType(eGarageType gtype);
    static bool IsPointWithinHideOutGarage(const CVector& point);
    static bool IsGarageDoorClosed(int16 garageId);
    static void Update();
    static void ActivateGarage(int16 a1);
    static void SetTargetCar(int16 garageId, CVehicle* veh);
    static void TriggerMessage(const char * tagMsg, int16 msgMin, uint16 time, int16 msgMax);
    static bool IsCarSprayable(CVehicle* veh);
    static void PrintMessages();
    static void SetGarageType(int16 garageId, eGarageType type, int32 unused);
    static void AddOne(float x1, float y1, float z1, float frontX, float frontY, float x2, float y2, float z2, uint8 type, uint32 a10, char* name, uint32 argFlags);
    static void Shutdown();
    static void DeactivateGarage(int16 grgIdx);
    static bool Save();
    static bool Load();
    static int16 FindGarageForObject(CObject*);
    static int16 GetGarageNumberByName(const char* name);

    static CGarage& GetGarage(int32 iGarageInd) { return aGarages[iGarageInd]; }
    static CStoredCar* GetStoredCarsInSafehouse(int32 iSafehouseInd) { return aCarsInSafeHouse[iSafehouseInd]; }
    static CStoredCar& GetStoredCar(int32 iSafehouseInd, int32 iCarInd) { return aCarsInSafeHouse[iSafehouseInd][iCarInd]; }
};
