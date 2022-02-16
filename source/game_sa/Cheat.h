/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "eCheats.h"
#include "eModelID.h"

class CVehicle;

class CCheat {
public:
    static constexpr auto CHEAT_STRING_SIZE{ 30 };
    static constexpr auto CHEAT_MIN_HASH_SIZE{ 6 };

    static void (*(&m_aCheatFunctions)[TOTAL_CHEATS])();
    static int32 (&m_aCheatHashKeys)[TOTAL_CHEATS];
    static char (&m_CheatString)[CHEAT_STRING_SIZE];
    static bool (&m_aCheatsActive)[TOTAL_CHEATS];
    static bool &m_bHasPlayerCheated;

public:
     static void InjectHooks();

     static void AddToCheatString(char LastPressedKey);
     static void ResetCheats();
     static void DoCheats();

     static void AdrenalineCheat();
     static void AllCarsAreGreatCheat();
     static void AllCarsAreShitCheat();
     static void ApacheCheat();
     static void BeachPartyCheat();
     static void BlackCarsCheat();
     static void BlowUpCarsCheat();
     static void CloudyWeatherCheat();
     static void CountrysideInvasionCheat();
     static void DozerCheat();
     static void DrivebyCheat();
     static void DuskCheat();
     static void ElvisLivesCheat();
     static void EverybodyAttacksPlayerCheat();
     static void ExtraSunnyWeatherCheat();
     static void FastTimeCheat();
     static void SlowTimeCheat();
     static void FatCheat();
     static void FlyboyCheat();
     static void FoggyWeatherCheat();
     static void FunhouseCheat();
     static void GangLandCheat();
     static void GangsCheat();
     static void GolfcartCheat();
     static void HandleSpecialCheats(eCheats cheat);
     static void HealthCheat();
     static void HearseCheat();
     static void JetpackCheat();
     static void LoveConquersAllCheat();
     static void LovefistCheat();
     static void MayhemCheat();
     static void MidnightCheat();
     static void MoneyArmourHealthCheat();
     static void MonsterTruckCheat();
     static void MuscleCheat();
     static void NinjaCheat();
     static void NotWantedCheat();
     static void ParachuteCheat();
     static void PinkCarsCheat();
     static void PredatorCheat();
     static void QuadCheat();
     static void RainyWeatherCheat();
     static void RiotCheat();
     static void SandstormCheat();
     static void SkinnyCheat();
     static void StaminaCheat();
     static void StockCarCheat();
     static void StockCar2Cheat();
     static void StockCar3Cheat();
     static void StockCar4Cheat();
     static void StormCheat();
     static void StuntPlaneCheat();
     static void SuicideCheat();
     static void SunnyWeatherCheat();
     static void TankCheat();
     static void TankerCheat();
     static void TrashmasterCheat();
     static CVehicle* VehicleCheat(eModelID vehicleModelId);
     static void VehicleSkillsCheat();
     static void VillagePeopleCheat();
     static void VortexCheat();
     static void WantedCheat();
     static void WantedLevelDownCheat();
     static void WantedLevelUpCheat();
     static void WeaponCheat1();
     static void WeaponCheat2();
     static void WeaponCheat3();
     static void WeaponSkillsCheat();
     static bool IsZoneStreamingAllowed();
     static void EnableLegitimateCheat(eCheats cheat);

# ifdef USE_ADDITIONAL_CHEATS
     static void WeaponCheat4();
     static void WeaponSlotCheat();
     static void TimeTravelCheat();
     static void ScriptBypassCheat();
     static void ShowMappingsCheat();
     static void TogglePlayerInvincibility();
     static void ToggleShowTapToTarget();
     static void ToggleShowTargeting();
     static void TheGamblerCheat();
# endif

     [[nodiscard]] static bool IsActive(eCheats cheat) noexcept { return m_aCheatsActive[cheat]; };
     static void Toggle(eCheats cheat)  { m_aCheatsActive[cheat] ^= true; }
     static void Enable(eCheats cheat)  { m_aCheatsActive[cheat] = true; }
     static void Disable(eCheats cheat) { m_aCheatsActive[cheat] = false; }
};
