/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

// Based on https://gtamods.com/wiki/Garage
enum eGarageType : uint8_t {
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

enum eGarageDoorState : uint8_t
{
    GARAGE_DOOR_CLOSED = 0,
    GARAGE_DOOR_OPEN = 1,
    GARAGE_DOOR_CLOSING = 2,
    GARAGE_DOOR_OPENING = 3,
    GARAGE_DOOR_WAITING_PLAYER_TO_EXIT = 4,
    GARAGE_DOOR_CLOSED_DROPPED_CAR = 5,
};

class  CGarages
{
public:
    static constexpr int MAX_NUM_SAFEHOUSES = 20;
    static constexpr int MAX_CARS_IN_SAFEHOUSE = 4;
    static CStoredCar(&aCarsInSafeHouse)[MAX_NUM_SAFEHOUSES][MAX_CARS_IN_SAFEHOUSE]; // Access using GetStoredCar() or GetStoredCarsInSafehouse()

    static constexpr int MAX_NUM_GARAGES = 50;
    static CGarage(&aGarages)[MAX_NUM_GARAGES]; // Access using GetGarage()

    static CGarage*& LastGaragePlayerWasIn;
    static uint32_t& LastTimeHelpMessage;
    static bool& bCamShouldBeOutside;
    static int32_t& CrushedCarId; // Unused in SA
    static uint32_t(&CarTypesCollected)[4];
    static uint32_t& PoliceCarsCollected;
    static uint32_t& BankVansCollected;
    static uint32_t& CarsCollected;
    static bool& NoResprays;
    static bool& RespraysAreFree;
    static bool& BombsAreFree;
    static bool& PlayerInGarage;
    static int32_t& MessageNumberInString;
    static int32_t& MessageNumberInString2;
    static char(&MessageIDString)[8];
    static uint32_t& MessageEndTime;
    static uint32_t& MessageStartTime;
    static int32_t& NumGarages;

public:
    static void InjectHooks();

    static void Init();
    static void Shutdown();
    static void Init_AfterRestart();
    static void Update();
    static void Save();
    static void Load();
    static void TriggerMessage(char* cTagMsg, short wMsgMin, unsigned short ucTime, short wMsgMax);
    static void PrintMessages();
    static int FindGarageIndex(char*);
    static int FindGarageForObject(CObject* pObject);
    static float FindDoorHeightForMI(int16_t);
    static int FindSafeHouseIndexForGarageType(int32_t);
    static void AddOne(float, float, float, float, char, int, char* src, int);
    static bool IsModelIndexADoor(int nModelIndex);
    static void ChangeGarageType(int16_t, uint8_t, uint32_t);
    static bool IsCarSprayable(CVehicle* pVehicle);
    static void SetTargetCarForMissionGarage(int16_t, CAutomobile* pCar);
    static bool HasCarBeenDroppedOffYet(int16_t);
    static void DeActivateGarage(int16_t);
    static void ActivateGarage(int16_t);
    static bool IsGarageOpen(int16_t);
    static bool IsGarageClosed(int16_t);
    static bool HasResprayHappened(int16_t);
    static bool CameraShouldBeOutside(int16_t);
    static void GivePlayerDetonator();
    static void PlayerArrestedOrDied();
    static bool IsPointInAGarageCameraZone(CVector vecPos);
    static bool IsThisCarWithingGarageArea(int16_t, CEntity* pEntity);
    static void StopCarFromBlowingUp(CAutomobile* pCar);
    static bool IsPointWithinHideOutGarage(CVector& vecPos);
    static bool IsPointWithinAnyGarage(CVector& vecPos);
    static int CountCarsInHideoutGarage(uint8_t);
    static void CloseHideOutGaragesBeforeSave();
    static void StoreCarInNearestImpoundingGarage(CVehicle* pVehicle);
    static void AllRespraysCloseOrOpen(bool);

public:
    static CGarage& GetGarage(int iGarageInd) { return aGarages[iGarageInd]; }
    static CStoredCar* GetStoredCarsInSafehouse(int iSafehouseInd) { return aCarsInSafeHouse[iSafehouseInd]; }
    static CStoredCar& GetStoredCar(int iSafehouseInd, int iCarInd) { return aCarsInSafeHouse[iSafehouseInd][iCarInd]; }
};

extern CGarage*& pOldToGarageWeAreIn;
