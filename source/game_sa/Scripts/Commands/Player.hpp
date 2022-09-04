#pragma once

#include "RunningScript.h"
#include "CommandParser/Parser.hpp"

/*!
* Various player commands
*/

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CREATE_PLAYER>() { // 0x053
    CollectParameters(4);
    int32 index = ScriptParams[0].iParam;
    if (!CStreaming::IsModelLoaded(0 /*MI_PLAYER*/)) // todo (Izzotop): rename MODEL_NULL -> MI_PLAYER
    {
        CStreaming::RequestSpecialModel(0, "player", STREAMING_GAME_REQUIRED | STREAMING_KEEP_IN_MEMORY | STREAMING_PRIORITY_REQUEST);
        CStreaming::LoadAllRequestedModels(true);
    }

    CPlayerPed::SetupPlayerPed(index);
    CPlayerInfo* playerInfo = &CWorld::Players[index];
    CPlayerPed* player = playerInfo->m_pPed;
    player->SetCharCreatedBy(PED_MISSION);
    CPlayerPed::DeactivatePlayerPed(index);

    CVector pos = CTheScripts::ReadCVectorFromScript(1);
    if (pos.z <= MAP_Z_LOW_LIMIT)
        pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);

    pos.z += player->GetDistanceFromCentreOfMassToBaseOfModel();
    player->SetPosn(pos);
    CTheScripts::ClearSpaceForMissionEntity(pos, player);
    CPlayerPed::ReactivatePlayerPed(index);
    ScriptParams[0].iParam = index;
    StoreParameters(1);

    CTask* task = new CTaskSimplePlayerOnFoot();
    player->GetTaskManager().SetTask(task, TASK_PRIMARY_DEFAULT);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_PLAYER_COORDINATES>() { // 0x054 | NOTSA
    CollectParameters(1);
    auto& playerInfo = FindPlayerInfo(ScriptParams[0].iParam);
    *(CVector*)&ScriptParams[0] = playerInfo.GetPos();
    StoreParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_PLAYER_IN_AREA_2D>() { // 0x056 | NOTSA
    CollectParameters(6);
    CPlayerPed* player = FindPlayerPed(ScriptParams[0].iParam);
    float x1 = ScriptParams[1].fParam;
    float y1 = ScriptParams[2].fParam;
    float x2 = ScriptParams[3].fParam;
    float y2 = ScriptParams[4].fParam;

    if (player->bInVehicle)
        UpdateCompareFlag(player->m_pVehicle->IsWithinArea(x1, y1, x2, y2));
    else
        UpdateCompareFlag(player->IsWithinArea(x1, y1, x2, y2));

    if (ScriptParams[5].bParam)
        CTheScripts::HighlightImportantArea(reinterpret_cast<uint32>((uint32)this + m_pCurrentIP), x1, y1, x2, y2, MAP_Z_LOW_LIMIT);

    if (CTheScripts::DbgFlag)
        CTheScripts::DrawDebugSquare(x1, y1, x2, y2);

    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_PLAYER_IN_AREA_3D>() { // 0x057 | NOTSA
    CollectParameters(8);
    CPlayerPed* player = FindPlayerPed(ScriptParams[0].iParam);
    const CVector p1 = CTheScripts::ReadCVectorFromScript(1);
    const CVector p2 = CTheScripts::ReadCVectorFromScript(4);

    if (player->bInVehicle)
        UpdateCompareFlag(player->m_pVehicle->IsWithinArea(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z));
    else
        UpdateCompareFlag(player->IsWithinArea(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z));

    if (ScriptParams[7].bParam)
        CTheScripts::HighlightImportantArea(reinterpret_cast<uint32>((uint32)this + m_pCurrentIP), p1.x, p1.y, p2.x, p2.y, (p1.z + p2.z) / 2.0f);

    if (CTheScripts::DbgFlag)
        CTheScripts::DrawDebugCube(p1, p2);

    return OR_CONTINUE;
}


auto IsPlayerPlaying(int32 playerId) -> notsa::script::CompareFlagUpdate {
    return { FindPlayerInfo(playerId).m_nPlayerState == PLAYERSTATE_PLAYING };
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_PLAYER_PLAYING, IsPlayerPlaying);

