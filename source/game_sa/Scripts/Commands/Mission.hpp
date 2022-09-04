#pragma once

#include "CommandParser/Parser.hpp"

/*!
* Various mission commands
*/

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_LOAD_AND_LAUNCH_MISSION_INTERNAL>() {
    CollectParameters(1);
    int32 missionId = ScriptParams[0].iParam;

    // Mostly CP from StartMission @ MissionDebugModule
    if (CTheScripts::NumberOfExclusiveMissionScripts > 0) {
        if (missionId <= 65532)
            return OR_CONTINUE;
        missionId = 0xFFFF - missionId;
    }
    CTimer::Suspend();
    int32 offsetToMission = CTheScripts::MultiScriptArray[missionId];
    CFileMgr::ChangeDir("\\");
    if (CGame::bMissionPackGame) {
        size_t bytesRead = 0;
        while (FrontEndMenuManager.CheckMissionPackValidMenu()) {
            CFileMgr::SetDirMyDocuments();
            sprintf(gString, "MPACK//MPACK%d//SCR.SCM", CGame::bMissionPackGame);
            auto* file = CFileMgr::OpenFile(gString, "rb");
            if (file) {
                CFileMgr::Seek(file, offsetToMission, 0);
                bytesRead = CFileMgr::Read(file, &CTheScripts::MissionBlock[0], MISSION_SCRIPT_SIZE);
                CFileMgr::CloseFile(file);
                if (bytesRead >= 1) {
                    CTheScripts::WipeLocalVariableMemoryForMissionScript();
                    CRunningScript* script = CTheScripts::StartNewScript(&CTheScripts::MissionBlock[0]);
                    script->m_bUseMissionCleanup = true;
                    script->m_bIsMission = true;
                    script->m_pBaseIP = &CTheScripts::MissionBlock[0];
                    CTheScripts::bAlreadyRunningAMissionScript = true;
                    CGameLogic::ClearSkip(false);
                }
            }
            if (bytesRead >= 1) {
                break;
            }
        }
    }
    CFileMgr::SetDir("");
    if (!CGame::bMissionPackGame) {
        auto* file = CFileMgr::OpenFile("data\\script\\main.scm", "rb");
        CFileMgr::Seek(file, offsetToMission, 0);
        CFileMgr::Read(file, &CTheScripts::MissionBlock[0], MISSION_SCRIPT_SIZE);
        CFileMgr::CloseFile(file);

        CTheScripts::WipeLocalVariableMemoryForMissionScript();
        CRunningScript* script = CTheScripts::StartNewScript(&CTheScripts::MissionBlock[0]);
        script->m_bUseMissionCleanup = true;
        script->m_bIsMission = true;
        script->m_pBaseIP = &CTheScripts::MissionBlock[0];
        CTheScripts::bAlreadyRunningAMissionScript = true;
        CGameLogic::ClearSkip(false);
    }
    CTimer::Resume();
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SCRIPT_NAME>() {
    char str[8];
    ReadTextLabelFromScript(str, 8);

    for (int i = 0; i < 8; i++)
        str[i] = tolower(str[i]);

    strncpy(m_szName, str, 8);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_START_SCRIPT_FIRE>() { // 0x2CF
    CollectParameters(5);
    CVector pos = CTheScripts::ReadCVectorFromScript(0);
    if (pos.z <= MAP_Z_LOW_LIMIT)
        pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);

    ScriptParams[0].iParam = gFireManager.StartScriptFire(pos, nullptr, 0.8f, 1, ScriptParams[3].iParam, ScriptParams[4].iParam);
    StoreParameters(1);
    return OR_CONTINUE;
}

void LaunchMission(uint32 label) {
    CTheScripts::StartNewScript(&CTheScripts::ScriptSpace[label]);
}
REGISTER_COMMAND_HANDLER(COMMAND_LAUNCH_MISSION, LaunchMission);

