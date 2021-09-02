/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

// Based on https://gtamods.com/wiki/Garage
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
    static constexpr int32_t MAX_NUM_SAFEHOUSES = 20;
    static constexpr int32_t MAX_CARS_IN_SAFEHOUSE = 4;
    static CStoredCar (&aCarsInSafeHouse)[MAX_NUM_SAFEHOUSES][MAX_CARS_IN_SAFEHOUSE]; // Access using GetStoredCar() or GetStoredCarsInSafehouse()

    static constexpr int32_t MAX_NUM_GARAGES = 50;
    static CGarage (&aGarages)[MAX_NUM_GARAGES]; // Access using GetGarage()

    static CGarage*& LastGaragePlayerWasIn;
    static uint32& LastTimeHelpMessage;
    static bool& bCamShouldBeOutside;
    static int32_t& CrushedCarId; // Unused in SA
    static uint32 (&CarTypesCollected)[4];
    static uint32& PoliceCarsCollected;
    static uint32& BankVansCollected;
    static uint32& CarsCollected;
    static bool& NoResprays;
    static bool& RespraysAreFree;
    static bool& BombsAreFree;
    static bool& PlayerInGarage;
    static int32_t& MessageNumberInString;
    static int32_t& MessageNumberInString2;
    static char (&MessageIDString)[8];
    static uint32& MessageEndTime;
    static uint32& MessageStartTime;
    static int32_t& NumGarages;

public:
    static void InjectHooks();

    static void Init();
    static void Init_AfterRestart();
    static void Update();
    static void Shutdown();

    static void Save();
    static void Load();
    static void TriggerMessage(char* cTagMsg, int16_t wMsgMin, uint16 ucTime, int16_t wMsgMax);
    static void PrintMessages();
    static int32_t FindGarageIndex(char*);
    static int32_t FindGarageForObject(CObject* pObject);
    static float FindDoorHeightForMI(int16_t);
    static int32_t FindSafeHouseIndexForGarageType(int32_t);
    static void AddOne(float x1, float y1, float z1, float frontX, float frontY, float x2, float y2, float z2, eGarageType type, uint32 a10, char* name, uint32 door);
    static bool IsModelIndexADoor(int32_t nModelIndex);
    static void ChangeGarageType(int16_t, uint16, uint32);
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
    static int32_t CountCarsInHideoutGarage(uint16);
    static void CloseHideOutGaragesBeforeSave();
    static void StoreCarInNearestImpoundingGarage(CVehicle* pVehicle);
    static void AllRespraysCloseOrOpen(bool);

public:
    static CGarage& GetGarage(int32_t iGarageInd) { return aGarages[iGarageInd]; }
    static CStoredCar* GetStoredCarsInSafehouse(int32_t iSafehouseInd) { return aCarsInSafeHouse[iSafehouseInd]; }
    static CStoredCar& GetStoredCar(int32_t iSafehouseInd, int32_t iCarInd) { return aCarsInSafeHouse[iSafehouseInd][iCarInd]; }
};

extern CGarage*& pOldToGarageWeAreIn;
