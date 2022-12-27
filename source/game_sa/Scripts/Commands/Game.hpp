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
#include "MenuSystem.h"
#include "CommandParser/Parser.hpp"

/*!
* Various game realted commands
*/

REGISTER_COMMAND_HANDLER(COMMAND_SET_ALL_TAXIS_HAVE_NITRO, [](bool enabled) { (enabled ? CCheat::ApplyCheat : CCheat::Disable)(CHEAT_ALL_TAXIS_NITRO); });

REGISTER_COMMAND_HANDLER(COMMAND_ACTIVATE_PIMP_CHEAT, [](bool enabled) { (enabled ? CCheat::ApplyCheat : CCheat::Disable)(CHEAT_PROSTITUTES_PAY_YOU); });

REGISTER_COMMAND_HANDLER(COMMAND_ARE_ANY_CAR_CHEATS_ACTIVATED, []() {
    return rng::any_of(std::array{CHEAT_PERFECT_HANDLING, CHEAT_CARS_ON_WATER, CHEAT_BOATS_FLY}, CCheat::IsActive);
});

REGISTER_COMMAND_HANDLER(COMMAND_FAIL_CURRENT_MISSION, []() { CTheScripts::FailCurrentMission = 2; });

REGISTER_COMMAND_HANDLER(COMMAND_GET_GROUND_Z_FOR_3D_COORD, [](CVector coord) {
    return CWorld::FindGroundZFor3DCoord(coord, nullptr, nullptr);
});

REGISTER_COMMAND_HANDLER(COMMAND_PLAYER_MADE_PROGRESS, []() { return CStats::IncrementStat(STAT_PROGRESS_MADE); });

REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_MISSION_GIVEN, []() { CStats::IncrementStat(STAT_MISSION_ATTEMPTS); });

REGISTER_COMMAND_HANDLER(COMMAND_SET_PED_DENSITY_MULTIPLIER, [](float mult) {
    CPopulation::PedDensityMultiplier = mult;
});

REGISTER_COMMAND_HANDLER(COMMAND_IS_JAPANESE_VERSION, []() {
    return false; // TODO: make this configurable perhaps?
});

REGISTER_COMMAND_HANDLER(COMMAND_IS_WIDESCREEN_ON_IN_OPTIONS, []() -> bool { return FrontEndMenuManager.m_bWidescreenOn; });

REGISTER_COMMAND_HANDLER(COMMAND_GET_RID_OF_PLAYER_PROSTITUTE, CTaskComplexProstituteSolicit::GetRidOfPlayerProstitute);

REGISTER_COMMAND_HANDLER(COMMAND_SET_AREA_NAME, [](const char* key) { CHud::SetZoneName(TheText.Get(key), true); });

REGISTER_COMMAND_HANDLER(COMMAND_SET_RADIO_TO_PLAYERS_FAVOURITE_STATION, []() { AudioEngine.RetuneRadio(CStats::FindMostFavoriteRadioStation()); });

REGISTER_COMMAND_HANDLER(COMMAND_SET_DISABLE_MILITARY_ZONES, [](bool disable) { CCullZones::bMilitaryZonesDisabled = disable; });

REGISTER_COMMAND_HANDLER(COMMAND_INCREMENT_FLOAT_STAT_NO_MESSAGE, CStats::IncrementStat);
REGISTER_COMMAND_HANDLER(COMMAND_INCREMENT_INT_STAT_NO_MESSAGE, CStats::IncrementStat);

REGISTER_COMMAND_HANDLER(COMMAND_TAKE_PHOTO, [](bool save) {
    CWeapon::ms_bTakePhoto = true;
    CPostEffects::m_bSavePhotoFromScript = save;
});

REGISTER_COMMAND_HANDLER(COMMAND_SET_NO_RESPRAYS, [](bool enabled) {
    CGarages::NoResprays = enabled;
    CGarages::AllRespraysCloseOrOpen(enabled);
});

REGISTER_COMMAND_HANDLER(COMMAND_SET_RESPAWN_POINT_FOR_DURATION_OF_MISSION, CRestart::SetRespawnPointForDurationOfMission);

REGISTER_COMMAND_HANDLER(COMMAND_GET_CURRENT_LANGUAGE, []() { return FrontEndMenuManager.m_nPrefsLanguage; });

REGISTER_COMMAND_HANDLER(COMMAND_DO_WEAPON_STUFF_AT_START_OF_2P_GAME, []() { CGameLogic::DoWeaponStuffAtStartOf2PlayerGame(true); });

REGISTER_COMMAND_HANDLER(COMMAND_DISPLAY_RADAR, [](bool enable) {
    // izzotop: CTheScripts::HideAllFrontEndMapBlips = enable;
    CHud::bScriptDontDisplayRadar = !enable;
});

REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_BEST_POSITION, CStats::RegisterBestPosition);

REGISTER_COMMAND_HANDLER(COMMAND_SET_MENU_HEADER_ORIENTATION, []() {
    // NOP

    // CMenuSystem::SetHeaderOrientation();
});

#ifdef IMPLEMENT_UNSUPPORTED_OPCODES
REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_JUMP_DISTANCE, [](float distance) {
    CStats::SetStatValue(STAT_MAXIMUM_INSANE_JUMP_DISTANCE, std::max(
        CStats::GetStatValue(STAT_MAXIMUM_INSANE_JUMP_DISTANCE),
        distance
    ));
});

REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_JUMP_HEIGHT, [](float height) {
    CStats::SetStatValue(STAT_MAXIMUM_INSANE_JUMP_FLIPS, std::max(
        CStats::GetStatValue(STAT_MAXIMUM_INSANE_JUMP_FLIPS),
        height
    ));
});

REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_JUMP_SPINS, [](float rotation) {
    CStats::SetStatValue(STAT_MAXIMUM_INSANE_JUMP_ROTATION, std::max(
        CStats::GetStatValue(STAT_MAXIMUM_INSANE_JUMP_ROTATION),
        rotation
    ));
});

REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_JUMP_STUNT, [](float stunt) {
    CStats::SetStatValue(STAT_BEST_INSANE_STUNT_AWARDED, std::max(
        CStats::GetStatValue(STAT_BEST_INSANE_STUNT_AWARDED),
        stunt
    ));
});

REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_UNIQUE_JUMP_FOUND, []() { CStats::IncrementStat(STAT_UNIQUE_JUMPS_FOUND); });

REGISTER_COMMAND_HANDLER(COMMAND_SET_UNIQUE_JUMPS_TOTAL, [](float amount) { CStats::SetStatValue(STAT_UNIQUE_JUMPS_DONE, amount); });

REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_PASSENGER_DROPPED_OFF_TAXI, []() { CStats::IncrementStat(STAT_PASSENGERS_DROPPED_OFF); });

REGISTER_COMMAND_HANDLER(COMMAND_REGISTER_MONEY_MADE_TAXI, [](float amount) { CStats::SetStatValue(STAT_CASH_MADE_IN_A_TAXI, amount); });
#endif
