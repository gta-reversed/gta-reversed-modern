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

enum eGarageType : uint8 {
    ONLY_TARGET_VEH = 1,
    BOMBSHOP_TIMED = 2,
    BOMBSHOP_ENGINE = 3,
    BOMBSHOP_REMOTE = 4,
    PAYNSPRAY = 5,

    UNKN_CLOSESONTOUCH = 11,
    OPEN_FOR_TARGET_FREEZE_PLAYER = 14,
    SCRIPT_ONLY_OPEN = 15,

    SAFEHOUSE_GANTON = 16,
    SAFEHOUSE_SANTAMARIA = 17,
    SAGEHOUSE_ROCKSHORE = 18,

    SCRIPT_CONTROLLED = 19,
    STAY_OPEN_WITH_CAR_INSIDE = 20,
    CLOSE_WITH_CAR_DONT_OPEN_AGAIN = 21,
    SCRIPT_OPEN_FREEZE_WHEN_CLOSING = 23,

    SAFEHOUSE_FORTCARSON = 24,
    SAFEHOUSE_VERDANTMEADOWS = 25,
    SAFEHOUSE_DILLIMORE = 26,
    SAFEHOUSE_PRICKLEPINE = 27,
    SAFEHOUSE_WHITEWOOD = 28,
    SAFEHOUSE_PALOMINOCREEK = 29,
    SAFEHOUSE_REDSANDSWEST = 30,
    SAFEHOUSE_ELCORONA = 31,
    SAFEHOUSE_MULHOLLAND = 32,

    IMPOUND_LS = 33,
    IMPOUND_SF = 34,
    IMPOUND_LV = 35,

    TUNING_LOCO_LOW_CO = 36,
    TUNING_WHEEL_ARCH_ANGELS = 37,
    TUNING_TRANSFENDER = 38,

    SAFEHOUSE_CALTONHEIGHTS = 39,
    SAFEHOUSE_PARADISO = 40,
    SAFEHOUSE_DOHERTY = 41,
    SAFEHOUSE_HASHBURY = 42,

    BURGLARY = 43,

    HANGAR_AT400 = 44,
    HANGAR_ABANDONED_AIRPORT = 45
};

enum eGarageDoorState : uint8 {
    GARAGE_DOOR_CLOSED = 0,
    GARAGE_DOOR_OPEN = 1,
    GARAGE_DOOR_CLOSING = 2,
    GARAGE_DOOR_OPENING = 3,
    GARAGE_DOOR_WAITING_PLAYER_TO_EXIT = 4,
    GARAGE_DOOR_CLOSED_DROPPED_CAR = 5,
};

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
    static inline int8& NoResprays = *(int8*)0x96C008;
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
    static int32 FindSafeHouseIndexForGarageType(int32 gtype);
    static bool IsPointWithinHideOutGarage(const CVector& point);
    static bool isGarageDoorClosed(int16 garageId);
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
