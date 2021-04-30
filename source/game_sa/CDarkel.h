/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CVehicle.h"

enum eDarkelStatus {
    DARKEL_STATUS_0,
    DARKEL_STATUS_1,
    DARKEL_STATUS_2,
    DARKEL_STATUS_3,
    DARKEL_STATUS_4,
};

class CDarkel {
public:
    static short** RegisteredKills; // short RegisteredKills[800][2];
    static char*& pStartMessage;
    static unsigned int& AmmoInterruptedWeapon;
    static eWeaponType& InterruptedWeaponType;
    static eWeaponType& InterruptedWeaponTypeSelected;
    static unsigned int& TimeOfFrenzyStart;
    static int* ModelToKill; // int CDarkel::ModelToKill[4];
    static eWeaponType& WeaponType;
    static eDarkelStatus& Status;

public:
    static void InjectHooks();

    static bool FrenzyOnGoing();
    static void Init();
    static void DrawMessages();
    static eDarkelStatus ReadStatus();
    static void RegisterKillNotByPlayer(CPed const* pKilledPed);
    static bool ThisPedShouldBeKilledForFrenzy(CPed const* pPed);
    static bool ThisVehicleShouldBeKilledForFrenzy(CVehicle const* pVehicle);
    static void StartFrenzy(eWeaponType weaponType, int timeLimit, unsigned short killsNeeded, int modelToKill, unsigned short* pStartMessage, int modelToKill2, int modelToKill3, int modelToKill4, bool bStandardSoundAndMessages, bool bNeedHeadShot);
    static void ResetModelsKilledByPlayer(int playerId);
    static int QueryModelsKilledByPlayer(int player, int modelId);
    static int FindTotalPedsKilledByPlayer(int player);
    static void DealWithWeaponChangeAtEndOfFrenzy();
    static bool CheckDamagedWeaponType(eWeaponType damageWeaponId, eWeaponType expectedDamageWeaponId);
    static void Update();
    static void ResetOnPlayerDeath();
    static void FailKillFrenzy();
    static void RegisterKillByPlayer(CPed const* pKilledPed, eWeaponType damageWeaponID, bool bHeadShotted, int arg4);
    static void RegisterCarBlownUpByPlayer(CVehicle* pVehicle, int arg2);
};
