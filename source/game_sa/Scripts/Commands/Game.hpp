#pragma once
#include "AudioEngine.h"
#include "CullZones.h"
#include "MenuManager.h"
#include "World.h"
#include "Stats.h"
#include "TaskComplexProstituteSolicit.h"
#include "Population.h"
#include "PostEffects.h"
#include "Restart.h"
#include "Garages.h"
#include "CommandParser/Parser.hpp"

/*!
* Various game realted commands
*/

void SetAllTaxisHaveNitro(bool enabled) {
    (enabled ? CCheat::ApplyCheat : CCheat::Disable)(CHEAT_ALL_TAXIS_NITRO);
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_ALL_TAXIS_HAVE_NITRO, SetAllTaxisHaveNitro);

bool AreAnyCarCheatsActivated() {
    return rng::any_of(std::array{CHEAT_PERFECT_HANDLING, CHEAT_CARS_ON_WATER, CHEAT_BOATS_FLY}, CCheat::IsActive);
}
REGISTER_COMMAND_HANDLER(COMMAND_ARE_ANY_CAR_CHEATS_ACTIVATED, AreAnyCarCheatsActivated);

void FailCurrentMission() {
    CTheScripts::FailCurrentMission = 2;
}
REGISTER_COMMAND_HANDLER(COMMAND_FAIL_CURRENT_MISSION, FailCurrentMission);

float GetGroundZFor3DCoord(CVector coord) {
    return CWorld::FindGroundZFor3DCoord(coord, nullptr, nullptr);
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_GROUND_Z_FOR_3D_COORD, GetGroundZFor3DCoord);

void PlayerMadeProgress() {
    return CStats::IncrementStat(STAT_PROGRESS_MADE);
}
REGISTER_COMMAND_HANDLER(COMMAND_PLAYER_MADE_PROGRESS, PlayerMadeProgress);

void RegisterMissionGiven() {
    CStats::IncrementStat(STAT_MISSION_ATTEMPTS);
}
REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_MISSION_GIVEN, RegisterMissionGiven);

void SetPedDensityMultiplier(float mult) {
    CPopulation::PedDensityMultiplier = mult;
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_PED_DENSITY_MULTIPLIER, SetPedDensityMultiplier);

bool IsJapaneseVersion() {
    return false; // TODO: make this configurable perhaps?
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_JAPANESE_VERSION, IsJapaneseVersion);

bool IsWidescreenOnInOptions() {
    return FrontEndMenuManager.m_bWidescreenOn;
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_WIDESCREEN_ON_IN_OPTIONS, IsWidescreenOnInOptions);

void GetRidOfPlayerProstitute() {
    CTaskComplexProstituteSolicit::GetRidOfPlayerProstitute();
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_RID_OF_PLAYER_PROSTITUTE, GetRidOfPlayerProstitute);

void ActivatePimpCheat(bool activate) {
    if (activate) {
        CCheat::ApplyCheat(CHEAT_PROSTITUTES_PAY_YOU);
    } else {
        CCheat::Disable(CHEAT_PROSTITUTES_PAY_YOU);
    }
}
REGISTER_COMMAND_HANDLER(COMMAND_ACTIVATE_PIMP_CHEAT, ActivatePimpCheat);

void SetDeathWeaponPersist(CPed& ped, bool enable) {
    ped.bDeathPickupsPersist = enable;
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_DEATH_WEAPONS_PERSIST, SetDeathWeaponPersist);

void SetAreaName(const char* key) {
    CHud::SetZoneName(TheText.Get(key), true);
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_AREA_NAME, SetAreaName);

void SetRadioToPlayersFavorite() {
    AudioEngine.RetuneRadio(CStats::FindMostFavoriteRadioStation());
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_RADIO_TO_PLAYERS_FAVOURITE_STATION, SetRadioToPlayersFavorite);

void SetDisableMilitaryZones(bool disable) {
    CCullZones::bMilitaryZonesDisabled = disable;
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_DISABLE_MILITARY_ZONES, SetDisableMilitaryZones);

void IncrementFloatStatNoMessage(eStats stat, float value) {
    CStats::IncrementStat(stat, value);
}
REGISTER_COMMAND_HANDLER(COMMAND_INCREMENT_FLOAT_STAT_NO_MESSAGE, IncrementFloatStatNoMessage);
REGISTER_COMMAND_HANDLER(COMMAND_INCREMENT_INT_STAT_NO_MESSAGE, IncrementFloatStatNoMessage);

void TakePhoto(bool save) {
    CWeapon::ms_bTakePhoto = true;
    CPostEffects::m_bSavePhotoFromScript = save;
}
REGISTER_COMMAND_HANDLER(COMMAND_TAKE_PHOTO, TakePhoto);

void SetNoResprays(bool enabled) {
    CGarages::NoResprays = enabled;
    CGarages::AllRespraysCloseOrOpen(enabled);
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_NO_RESPRAYS, SetNoResprays);

void SetRespawnPointForDurationOfMission(CVector point) {
    CRestart::SetRespawnPointForDurationOfMission(point);
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_RESPAWN_POINT_FOR_DURATION_OF_MISSION, SetRespawnPointForDurationOfMission);

eLanguage GetCurrentLanguage() {
    return FrontEndMenuManager.m_nPrefsLanguage;
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_CURRENT_LANGUAGE, GetCurrentLanguage);

#ifdef IMPLEMENT_UNSUPPORTED_OPCODES
void RegisterJumpDistance(float distance) {
    CStats::SetStatValue(STAT_MAXIMUM_INSANE_JUMP_DISTANCE, std::max(
        CStats::GetStatValue(STAT_MAXIMUM_INSANE_JUMP_DISTANCE),
        distance
    ));
}
REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_JUMP_DISTANCE, RegisterJumpDistance);

void RegisterJumpHeight(float height) {
    CStats::SetStatValue(STAT_MAXIMUM_INSANE_JUMP_FLIPS, std::max(
        CStats::GetStatValue(STAT_MAXIMUM_INSANE_JUMP_FLIPS),
        height
    ));
}
REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_JUMP_HEIGHT, RegisterJumpHeight);

void RegisterJumpSpins(float rotation) {
    CStats::SetStatValue(STAT_MAXIMUM_INSANE_JUMP_ROTATION, std::max(
        CStats::GetStatValue(STAT_MAXIMUM_INSANE_JUMP_ROTATION),
        rotation
    ));
}
REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_JUMP_SPINS, RegisterJumpSpins);

void RegisterJumpStunt(float stunt) {
    CStats::SetStatValue(STAT_BEST_INSANE_STUNT_AWARDED, std::max(
        CStats::GetStatValue(STAT_BEST_INSANE_STUNT_AWARDED),
        stunt
    ));
}
REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_JUMP_STUNT, RegisterJumpStunt);

void RegisterUniqueJumpFound() {
    CStats::IncrementStat(STAT_UNIQUE_JUMPS_FOUND);
}
REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_UNIQUE_JUMP_FOUND, RegisterUniqueJumpFound);

void SetUniqueJumpsTotal(float amount) {
    CStats::SetStatValue(STAT_UNIQUE_JUMPS_DONE, amount);
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_UNIQUE_JUMPS_TOTAL, SetUniqueJumpsTotal);

void RegisterPassengerDroppedOffTaxi() {
    CStats::IncrementStat(STAT_PASSENGERS_DROPPED_OFF);
}
REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_PASSENGER_DROPPED_OFF_TAXI, RegisterPassengerDroppedOffTaxi);

void RegisterMoneyMadeTaxi(float amount) {
    CStats::SetStatValue(STAT_CASH_MADE_IN_A_TAXI, amount);
}
REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_MONEY_MADE_TAXI, RegisterMoneyMadeTaxi);
#endif
