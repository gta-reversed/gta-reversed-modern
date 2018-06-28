/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVehicle.h"

class  CDarkel {
public:
	static short** RegisteredKills;		// short RegisteredKills[800][2];
	static char* pStartMessage;							
	static unsigned int& AmmoInterruptedWeapon;				
	static eWeaponType& InterruptedWeaponType;				
	static eWeaponType& InterruptedWeaponTypeSelected;		
	static unsigned int& TimeOfFrenzyStart;					
	static int* ModelToKill;		// int CDarkel::ModelToKill[4];
	static eWeaponType& WeaponType;				
	static short& Status;

	static bool FrenzyOnGoing();
	static void Init();
	static void DrawMessages();
	static short ReadStatus();
	static void RegisterKillNotByPlayer(CPed const* pKilledPed);
	static bool ThisPedShouldBeKilledForFrenzy(CPed const* pPed);
	static bool ThisVehicleShouldBeKilledForFrenzy(CVehicle const* pVehicle);
	static void StartFrenzy(eWeaponType weapontype, int Timelimit, unsigned short KillsNeeded, int ModelToKill, unsigned short* pStartMessage, int ModelToKill2, int ModelToKill3, int ModelToKill4, bool bStandardSoundAndMessages, bool bNeedHeadShot);
	static void ResetModelsKilledByPlayer(int playerid);
	static int QueryModelsKilledByPlayer(int player, int modelid);
	static int FindTotalPedsKilledByPlayer(int player);
	static void DealWithWeaponChangeAtEndOfFrenzy();
	static bool CheckDamagedWeaponType(int damageWeaponID, int expectedDamageWeaponID);
	static void Update();
	static void ResetOnPlayerDeath();
	static void FailKillFrenzy();
	static void RegisterKillByPlayer(CPed const* pKilledPed, eWeaponType damageWeaponID, bool bHeadShotted, int arg4);
	static void RegisterCarBlownUpByPlayer(CVehicle* pVehicle, int arg2);
};
