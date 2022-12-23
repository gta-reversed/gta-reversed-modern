#pragma once

#include "TaskSimpleSwim.h"
#include "RunningScript.h"
#include "CommandParser/Parser.hpp"

/*!
* Various player commands
*/

/*!
* @brief Create a player at the given world position
* @param playerId Player's id (0 or 1)
* @param pos      World position
*/
int32 CreatePlayer(int32 playerId, CVector pos) {
    if (!CStreaming::IsModelLoaded(0 /*MI_PLAYER*/)) // todo (Izzotop): rename MODEL_NULL -> MI_PLAYER
    {
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
REGISTER_COMMAND_HANDLER(COMMAND_CREATE_PLAYER, CreatePlayer);

/// Get the position of a player
CVector GetPlayerCoordinates(CPlayerInfo& pinfo) {
    return pinfo.GetPos();
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_PLAYER_COORDINATES, GetPlayerCoordinates);

bool IsPlyerInArea2D(CRunningScript* S, CPlayerPed& player, CRect area, bool highlightArea) {
    if (highlightArea) {
        CTheScripts::HighlightImportantArea((uint32)S + (uint32)S->m_pCurrentIP, area, MAP_Z_LOW_LIMIT);
    }

    if (CTheScripts::DbgFlag) {
        CTheScripts::DrawDebugSquare(area);
    }

    return player.bInVehicle
        ? player.m_pVehicle->IsWithinArea(area.left, area.top, area.right, area.bottom)
        : player.IsWithinArea(area.left, area.top, area.right, area.bottom);
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_PLAYER_IN_AREA_2D, IsPlyerInArea2D);

bool IsPlyerInArea3D(CRunningScript* S, CPlayerPed& player, CVector p1, CVector p2, bool highlightArea) {
    if (highlightArea) {
        CTheScripts::HighlightImportantArea((uint32)S + (uint32)S->m_pCurrentIP, p1.x, p1.y, p2.x, p2.y, (p1.z + p2.z) / 2.0f);
    }

    if (CTheScripts::DbgFlag) {
        CTheScripts::DrawDebugCube(p1, p2);
    }

    return player.bInVehicle
        ? player.m_pVehicle->IsWithinArea(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z)
        : player.IsWithinArea(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z);
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_PLAYER_IN_AREA_3D, IsPlyerInArea3D);

auto IsPlayerPlaying(int32 playerId) -> notsa::script::CompareFlagUpdate {
    return { FindPlayerInfo(playerId).m_nPlayerState == PLAYERSTATE_PLAYING };
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_PLAYER_PLAYING, IsPlayerPlaying);

bool IsPlayerClimbing(int32 playerId) {
    assert(FindPlayerPed(playerId));
    return FindPlayerPed(playerId)->GetIntelligence()->GetTaskClimb();
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_PLAYER_CLIMBING, IsPlayerClimbing);

void SetSwimSpeed(int32 playerId, float speed) {
    if (!FindPlayerPed(playerId))
        return;

    if (auto swim = FindPlayerPed(playerId)->GetIntelligence()->GetTaskSwim())
        swim->m_fAnimSpeed = speed;
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_SWIM_SPEED, SetSwimSpeed);

void SetPlayerGroupToFollowAlways(int32 playerId, bool enable) {
    FindPlayerPed(playerId)->ForceGroupToAlwaysFollow(enable);
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_PLAYER_GROUP_TO_FOLLOW_ALWAYS, SetPlayerGroupToFollowAlways);
