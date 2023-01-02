#include <StdInc.h>

#include "./Commands.hpp"
#include <CommandParser/Parser.hpp>

#include <TaskTypes/TaskSimplePlayerOnFoot.h>
#include <TaskTypes/TaskSimpleSwim.h>

#include <RunningScript.h>

using namespace notsa::script;
/*!
* Various player commands
*/

/*!
* @brief Create a player at the given world position
* @param playerId Player's id (0 or 1)
* @param pos      World position
*/
int32 CreatePlayer(int32 playerId, CVector pos) {
    if (!CStreaming::IsModelLoaded(MODEL_PLAYER)) {
        CStreaming::RequestSpecialModel(0, "player", STREAMING_GAME_REQUIRED | STREAMING_KEEP_IN_MEMORY | STREAMING_PRIORITY_REQUEST);
        CStreaming::LoadAllRequestedModels(true);
    }

    // Create
    CPlayerPed::SetupPlayerPed(playerId);
    auto player = FindPlayerPed(playerId);
    player->SetCharCreatedBy(PED_MISSION);
    CPlayerPed::DeactivatePlayerPed(playerId);

    // Position in the world
    if (pos.z <= MAP_Z_LOW_LIMIT) {
        pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);
    }
    pos.z += player->GetDistanceFromCentreOfMassToBaseOfModel();
    player->SetPosn(pos);
    CTheScripts::ClearSpaceForMissionEntity(pos, player);
    CPlayerPed::ReactivatePlayerPed(playerId);

    // Set task
    player->GetTaskManager().SetTask(new CTaskSimplePlayerOnFoot(), TASK_PRIMARY_DEFAULT);

    return playerId;
}

/// Get the position of a player
CVector GetPlayerCoordinates(CPlayerInfo& pinfo) {
    return pinfo.GetPos();
}

bool IsPlayerInArea2D(CRunningScript* S, CPlayerPed& player, CRect area, bool highlightArea) {
    if (highlightArea) {
        CTheScripts::HighlightImportantArea((uint32)S + (uint32)S->m_IP, area, MAP_Z_LOW_LIMIT);
    }

    if (CTheScripts::DbgFlag) {
        CTheScripts::DrawDebugSquare(area);
    }

    return player.bInVehicle
        ? player.m_pVehicle->IsWithinArea(area.left, area.top, area.right, area.bottom)
        : player.IsWithinArea(area.left, area.top, area.right, area.bottom);
}

bool IsPlayerInArea3D(CRunningScript* S, CPlayerPed& player, CVector p1, CVector p2, bool highlightArea) {
    if (highlightArea) {
        CTheScripts::HighlightImportantArea((uint32)S + (uint32)S->m_IP, p1.x, p1.y, p2.x, p2.y, (p1.z + p2.z) / 2.0f);
    }

    if (CTheScripts::DbgFlag) {
        CTheScripts::DrawDebugCube(p1, p2);
    }

    return player.bInVehicle
        ? player.m_pVehicle->IsWithinArea(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z)
        : player.IsWithinArea(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z);
}

auto IsPlayerPlaying(CPlayerInfo& player) -> notsa::script::CompareFlagUpdate {
    return { player.m_nPlayerState == PLAYERSTATE_PLAYING };
}

bool IsPlayerClimbing(CPlayerPed& player) {
    return player.GetIntelligence()->GetTaskClimb();
}

void SetSwimSpeed(CPlayerPed& player, float speed) {
    if (auto swim = player.GetIntelligence()->GetTaskSwim())
        swim->m_fAnimSpeed = speed;
}

void SetPlayerGroupToFollowAlways(CPlayerPed& player, bool enable) {
    player.ForceGroupToAlwaysFollow(enable);
}

void SetPlayerAbleToUseCrouch(uint32 playerIdx, bool enable) {
    CPad::GetPad(playerIdx)->bDisablePlayerDuck = !enable;
}

bool IsPlayerTouchingObject(CPlayerPed& player, CObject& object) {
#ifdef IMPLEMENT_UNSUPPORTED_OPCODES
    return GetPedOrItsVehicle(player).GetHasCollidedWith(&object);
#endif
}

bool IsPlayerTouchingObjectOnFoot(CPlayerPed& player, CObject& object) {
#ifdef IMPLEMENT_UNSUPPORTED_OPCODES
    return player.GetHasCollidedWith(&object);
#endif
}

void notsa::script::commands::player::RegisterHandlers() {
    REGISTER_COMMAND_HANDLER(COMMAND_CREATE_PLAYER, CreatePlayer);
    REGISTER_COMMAND_HANDLER(COMMAND_GET_PLAYER_COORDINATES, GetPlayerCoordinates);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_PLAYER_IN_AREA_2D, IsPlayerInArea2D);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_PLAYER_IN_AREA_3D, IsPlayerInArea3D);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_PLAYER_PLAYING, IsPlayerPlaying);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_PLAYER_CLIMBING, IsPlayerClimbing);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_SWIM_SPEED, SetSwimSpeed);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_PLAYER_GROUP_TO_FOLLOW_ALWAYS, SetPlayerGroupToFollowAlways);
    REGISTER_COMMAND_HANDLER(COMMAND_SET_PLAYER_DUCK_BUTTON, SetPlayerAbleToUseCrouch);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_PLAYER_TOUCHING_OBJECT, IsPlayerTouchingObject);
    REGISTER_COMMAND_HANDLER(COMMAND_IS_PLAYER_TOUCHING_OBJECT_ON_FOOT, IsPlayerTouchingObjectOnFoot);

    REGISTER_COMMAND_UNIMPLEMENTED(COMMAND_SET_PLAYER_HEED_THREATS);
    REGISTER_COMMAND_UNIMPLEMENTED(COMMAND_IS_PLAYER_STOPPED);
    REGISTER_COMMAND_UNIMPLEMENTED(COMMAND_IS_PLAYER_IN_ANGLED_AREA_2D);
    REGISTER_COMMAND_UNIMPLEMENTED(COMMAND_IS_PLAYER_IN_ANGLED_AREA_ON_FOOT_2D);
    REGISTER_COMMAND_UNIMPLEMENTED(COMMAND_IS_PLAYER_IN_ANGLED_AREA_IN_CAR_2D);
    REGISTER_COMMAND_UNIMPLEMENTED(COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_2D);
    REGISTER_COMMAND_UNIMPLEMENTED(COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_ON_FOOT_2D);
    REGISTER_COMMAND_UNIMPLEMENTED(COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_IN_CAR_2D);
    REGISTER_COMMAND_UNIMPLEMENTED(COMMAND_IS_PLAYER_IN_ANGLED_AREA_3D);
    REGISTER_COMMAND_UNIMPLEMENTED(COMMAND_IS_PLAYER_IN_ANGLED_AREA_ON_FOOT_3D);
    REGISTER_COMMAND_UNIMPLEMENTED(COMMAND_IS_PLAYER_IN_ANGLED_AREA_IN_CAR_3D);
    REGISTER_COMMAND_UNIMPLEMENTED(COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_3D);
    REGISTER_COMMAND_UNIMPLEMENTED(COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_ON_FOOT_3D);
    REGISTER_COMMAND_UNIMPLEMENTED(COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_IN_CAR_3D);
    REGISTER_COMMAND_UNIMPLEMENTED(COMMAND_IS_PLAYER_SHOOTING_IN_AREA);
    REGISTER_COMMAND_UNIMPLEMENTED(COMMAND_IS_CURRENT_PLAYER_WEAPON);
    REGISTER_COMMAND_UNIMPLEMENTED(COMMAND_IS_PLAYER_IN_TAXI);
    REGISTER_COMMAND_UNIMPLEMENTED(COMMAND_IS_PLAYER_SHOOTING);
}
