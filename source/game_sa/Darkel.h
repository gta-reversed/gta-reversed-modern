/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "eWeaponType.h"

class CVehicle;

enum eDarkelStatus {
    DARKEL_STATUS_0,
    DARKEL_STATUS_1,
    DARKEL_STATUS_2,
    DARKEL_STATUS_3,
    DARKEL_STATUS_4,
};

class CDarkel {
public:
    static int16** RegisteredKills; // int16 RegisteredKills[800][2];
    static char*& pStartMessage;
    static uint32& AmmoInterruptedWeapon;
    static eWeaponType& InterruptedWeaponType;
    static eWeaponType& InterruptedWeaponTypeSelected;
    static uint32& TimeOfFrenzyStart;
    static int32& TimeLimit;
    static int32& KillsNeeded;
    static int32* ModelToKill; // int32 CDarkel::ModelToKill[4];
    static eWeaponType& WeaponType;
    static eDarkelStatus& Status;

    inline static bool& byte_969A4A = *(bool*)0x969A4A;

public:
    static void InjectHooks();

    static bool FrenzyOnGoing();
    static void Init();
    static void DrawMessages();
    static eDarkelStatus ReadStatus();
    static void RegisterKillNotByPlayer(const CPed* killedPed);
    static bool ThisPedShouldBeKilledForFrenzy(const CPed* ped);
    static bool ThisVehicleShouldBeKilledForFrenzy(const CVehicle* vehicle);
    static void StartFrenzy(eWeaponType weaponType, int32 timeLimit, uint16 killsNeeded, int32 modelToKill, uint16* pStartMessage, int32 modelToKill2, int32 modelToKill3, int32 modelToKill4, bool bStandardSoundAndMessages, bool bNeedHeadShot);
    static void ResetModelsKilledByPlayer(int32 playerId);
    static int32 QueryModelsKilledByPlayer(int32 player, int32 modelId);
    static int32 FindTotalPedsKilledByPlayer(int32 player);
    static void DealWithWeaponChangeAtEndOfFrenzy();
    static bool CheckDamagedWeaponType(eWeaponType damageWeaponId, eWeaponType expectedDamageWeaponId);
    static void Update();
    static void ResetOnPlayerDeath();
    static void FailKillFrenzy();
    static void RegisterKillByPlayer(const CPed* killedPed, eWeaponType damageWeaponID, bool bHeadShotted, int32 arg4);
    static void RegisterCarBlownUpByPlayer(CVehicle* vehicle, int32 arg2);
};
