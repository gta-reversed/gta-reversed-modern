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
REGISTER_COMMAND_HANDLER(COMMAND_CREATE_PLAYER, [](int32 playerId, CVector pos) {
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
});

/// Get the position of a player
REGISTER_COMMAND_HANDLER(COMMAND_GET_PLAYER_COORDINATES, [](CPlayerInfo& pinfo) { return pinfo.GetPos(); });

REGISTER_COMMAND_HANDLER(COMMAND_IS_PLAYER_IN_AREA_2D, [](CRunningScript* S, CPlayerPed& player, CRect area, bool highlightArea) {
    if (highlightArea) {
        CTheScripts::HighlightImportantArea((uint32)S + (uint32)S->m_IP, area, MAP_Z_LOW_LIMIT);
    }

    if (CTheScripts::DbgFlag) {
        CTheScripts::DrawDebugSquare(area);
    }

    return player.bInVehicle
        ? player.m_pVehicle->IsWithinArea(area.left, area.top, area.right, area.bottom)
        : player.IsWithinArea(area.left, area.top, area.right, area.bottom);
});

REGISTER_COMMAND_HANDLER(COMMAND_IS_PLAYER_IN_AREA_3D, [](CRunningScript* S, CPlayerPed& player, CVector p1, CVector p2, bool highlightArea) {
    if (highlightArea) {
        CTheScripts::HighlightImportantArea((uint32)S + (uint32)S->m_IP, p1.x, p1.y, p2.x, p2.y, (p1.z + p2.z) / 2.0f);
    }

    if (CTheScripts::DbgFlag) {
        CTheScripts::DrawDebugCube(p1, p2);
    }

    return player.bInVehicle
        ? player.m_pVehicle->IsWithinArea(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z)
        : player.IsWithinArea(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z);
});

REGISTER_COMMAND_HANDLER(COMMAND_IS_PLAYER_PLAYING, [](CPlayerInfo& player) { return player.m_nPlayerState == PLAYERSTATE_PLAYING; });

REGISTER_COMMAND_HANDLER(COMMAND_IS_PLAYER_CLIMBING, [](CPlayerPed& player) { return player.GetIntelligence()->GetTaskClimb() != nullptr; });

REGISTER_COMMAND_HANDLER(COMMAND_SET_SWIM_SPEED, [](CPlayerPed& player, float speed) {
    if (auto swim = player.GetIntelligence()->GetTaskSwim())
        swim->m_fAnimSpeed = speed;
});

REGISTER_COMMAND_HANDLER(COMMAND_SET_PLAYER_GROUP_TO_FOLLOW_ALWAYS, [](CPlayerPed& player, bool enable) { player.ForceGroupToAlwaysFollow(enable); });
