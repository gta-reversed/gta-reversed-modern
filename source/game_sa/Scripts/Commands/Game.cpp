#include <StdInc.h>

#include "./Commands.hpp"
#include <CommandParser/Parser.hpp>
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
#include "MenuSystem.h"
#include "CommandParser/Parser.hpp"

/*!
* Various game realted commands
*/

void SetAllTaxisHaveNitro(bool enabled) {
    (enabled ? CCheat::ApplyCheat : CCheat::Disable)(CHEAT_ALL_TAXIS_NITRO);
}

void ActivatePimpCheat(bool enabled) {
    (enabled ? CCheat::ApplyCheat : CCheat::Disable)(CHEAT_PROSTITUTES_PAY_YOU);
}

bool AreAnyCarCheatsActivated() {
    return rng::any_of(std::array{CHEAT_PERFECT_HANDLING, CHEAT_CARS_ON_WATER, CHEAT_BOATS_FLY}, CCheat::IsActive);
}

void FailCurrentMission() {
    CTheScripts::FailCurrentMission = 2;
}

float GetGroundZFor3DCoord(CVector coord) {
    return CWorld::FindGroundZFor3DCoord(coord, nullptr, nullptr);
}

void PlayerMadeProgress() {
    return CStats::IncrementStat(STAT_PROGRESS_MADE);
}

void RegisterMissionGiven() {
    CStats::IncrementStat(STAT_MISSION_ATTEMPTS);
}

void SetPedDensityMultiplier(float mult) {
    CPopulation::PedDensityMultiplier = mult;
}

bool IsJapaneseVersion() {
    return false; // TODO: make this configurable perhaps?
}

bool IsWidescreenOnInOptions() {
    return FrontEndMenuManager.m_bWidescreenOn;
}

void GetRidOfPlayerProstitute() {
    CTaskComplexProstituteSolicit::GetRidOfPlayerProstitute();
}

void SetAreaName(const char* key) {
    CHud::SetZoneName(TheText.Get(key), true);
}

void SetRadioToPlayersFavorite() {
    AudioEngine.RetuneRadio(CStats::FindMostFavoriteRadioStation());
}

void SetDisableMilitaryZones(bool disable) {
    CCullZones::bMilitaryZonesDisabled = disable;
}

void IncrementFloatStatNoMessage(eStats stat, float value) {
    CStats::IncrementStat(stat, value);
}

void TakePhoto(bool save) {
    CWeapon::ms_bTakePhoto = true;
    CPostEffects::m_bSavePhotoFromScript = save;
}

void SetNoResprays(bool enabled) {
    CGarages::NoResprays = enabled;
    CGarages::AllRespraysCloseOrOpen(enabled);
}

void SetRespawnPointForDurationOfMission(CVector point) {
    CRestart::SetRespawnPointForDurationOfMission(point);
}

eLanguage GetCurrentLanguage() {
    return FrontEndMenuManager.m_nPrefsLanguage;
}

void DoWeaponStuffAtStartOf2PlayerGame() {
    CGameLogic::DoWeaponStuffAtStartOf2PlayerGame(true);
}

void DisplayRadar(bool enable) {
    // izzotop: CTheScripts::HideAllFrontEndMapBlips = enable;
    CHud::bScriptDontDisplayRadar = !enable;
}

void RegisterBestPosition(uint8 stat, int32 position) {
    CStats::RegisterBestPosition(static_cast<eStats>(stat), position);
}

void SetMenuHeaderOrientation() {
    // NOP

    // CMenuSystem::SetHeaderOrientation();
}

void SetFloatStat(eStats stat, float value) {
    CStats::SetStatValue(stat, value);
    CStats::DisplayScriptStatUpdateMessage(STAT_UPDATE_INCREASE, stat, value);
}

#ifdef IMPLEMENT_UNSUPPORTED_OPCODES
void RegisterJumpDistance(float distance) {
    CStats::SetStatValue(STAT_MAXIMUM_INSANE_JUMP_DISTANCE, std::max(
        CStats::GetStatValue(STAT_MAXIMUM_INSANE_JUMP_DISTANCE),
        distance
    ));
}

void RegisterJumpHeight(float height) {
    CStats::SetStatValue(STAT_MAXIMUM_INSANE_JUMP_FLIPS, std::max(
        CStats::GetStatValue(STAT_MAXIMUM_INSANE_JUMP_FLIPS),
        height
    ));
}

void RegisterJumpSpins(float rotation) {
    CStats::SetStatValue(STAT_MAXIMUM_INSANE_JUMP_ROTATION, std::max(
        CStats::GetStatValue(STAT_MAXIMUM_INSANE_JUMP_ROTATION),
        rotation
    ));
}

void RegisterJumpStunt(float stunt) {
    CStats::SetStatValue(STAT_BEST_INSANE_STUNT_AWARDED, std::max(
        CStats::GetStatValue(STAT_BEST_INSANE_STUNT_AWARDED),
        stunt
    ));
}

void RegisterUniqueJumpFound() {
    CStats::IncrementStat(STAT_UNIQUE_JUMPS_FOUND);
}

void SetUniqueJumpsTotal(float amount) {
    CStats::SetStatValue(STAT_UNIQUE_JUMPS_DONE, amount);
}

void RegisterPassengerDroppedOffTaxi() {
    CStats::IncrementStat(STAT_PASSENGERS_DROPPED_OFF);
}

void RegisterMoneyMadeTaxi(float amount) {
    CStats::SetStatValue(STAT_CASH_MADE_IN_A_TAXI, amount);
}
#endif

void notsa::script::commands::game::RegisterHandlers() {
    REGISTER_COMMAND_HANDLER(COMMAND_SET_ALL_TAXIS_HAVE_NITRO, SetAllTaxisHaveNitro);
    REGISTER_COMMAND_HANDLER(COMMAND_ACTIVATE_PIMP_CHEAT, ActivatePimpCheat);
    REGISTER_COMMAND_HANDLER(COMMAND_ARE_ANY_CAR_CHEATS_ACTIVATED, AreAnyCarCheatsActivated);
    REGISTER_COMMAND_HANDLER(COMMAND_FAIL_CURRENT_MISSION, FailCurrentMission);
    REGISTER_COMMAND_HANDLER(COMMAND_GET_GROUND_Z_FOR_3D_COORD, GetGroundZFor3DCoord);
    REGISTER_COMMAND_HANDLER(COMMAND_PLAYER_MADE_PROGRESS, PlayerMadeProgress);
    REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_MISSION_GIVEN, RegisterMissionGiven);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_PED_DENSITY_MULTIPLIER, SetPedDensityMultiplier);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_JAPANESE_VERSION, IsJapaneseVersion);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_WIDESCREEN_ON_IN_OPTIONS, IsWidescreenOnInOptions);
    REGISTER_COMMAND_HANDLER(COMMAND_GET_RID_OF_PLAYER_PROSTITUTE, GetRidOfPlayerProstitute);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_AREA_NAME, SetAreaName);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_RADIO_TO_PLAYERS_FAVOURITE_STATION, SetRadioToPlayersFavorite);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_DISABLE_MILITARY_ZONES, SetDisableMilitaryZones);
    REGISTER_COMMAND_HANDLER(COMMAND_INCREMENT_FLOAT_STAT_NO_MESSAGE, IncrementFloatStatNoMessage);
    REGISTER_COMMAND_HANDLER(COMMAND_INCREMENT_INT_STAT_NO_MESSAGE, IncrementFloatStatNoMessage);
    REGISTER_COMMAND_HANDLER(COMMAND_TAKE_PHOTO, TakePhoto);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_NO_RESPRAYS, SetNoResprays);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_RESPAWN_POINT_FOR_DURATION_OF_MISSION, SetRespawnPointForDurationOfMission);
    REGISTER_COMMAND_HANDLER(COMMAND_GET_CURRENT_LANGUAGE, GetCurrentLanguage);
    REGISTER_COMMAND_HANDLER(COMMAND_DO_WEAPON_STUFF_AT_START_OF_2P_GAME, DoWeaponStuffAtStartOf2PlayerGame);
    REGISTER_COMMAND_HANDLER(COMMAND_DISPLAY_RADAR, DisplayRadar);
    REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_BEST_POSITION, RegisterBestPosition);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_MENU_HEADER_ORIENTATION, SetMenuHeaderOrientation);
    REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_JUMP_DISTANCE, RegisterJumpDistance);
    REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_JUMP_HEIGHT, RegisterJumpHeight);
    REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_JUMP_SPINS, RegisterJumpSpins);
    REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_JUMP_STUNT, RegisterJumpStunt);
    REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_UNIQUE_JUMP_FOUND, RegisterUniqueJumpFound);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_UNIQUE_JUMPS_TOTAL, SetUniqueJumpsTotal);
    REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_PASSENGER_DROPPED_OFF_TAXI, RegisterPassengerDroppedOffTaxi);
    REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_MONEY_MADE_TAXI, RegisterMoneyMadeTaxi);

    REGISTER_COMMAND_HANDLER(COMMAND_SET_FLOAT_STAT, SetFloatStat);
}
