#include "StdInc.h"
#include "RunningScript.h"

// 0x489500
OpcodeResult CRunningScript::ProcessCommands1000To1099(int32 commandId) {
    switch (commandId) {
    case COMMAND_FLASH_RADAR_BLIP: // 0x3E8
        break;
    case COMMAND_IS_CHAR_IN_CONTROL: // 0x3E9
        break;
    case COMMAND_SET_GENERATE_CARS_AROUND_CAMERA: // 0x3EA
        break;
    case COMMAND_CLEAR_SMALL_PRINTS: // 0x3EB
        break;
    case COMMAND_HAS_MILITARY_CRANE_COLLECTED_ALL_CARS: // 0x3EC
        break;
    case COMMAND_SET_UPSIDEDOWN_CAR_NOT_DAMAGED: // 0x3ED
        break;
    case COMMAND_CAN_PLAYER_START_MISSION: // 0x3EE
        break;
    case COMMAND_MAKE_PLAYER_SAFE_FOR_CUTSCENE: // 0x3EF
        break;
    case COMMAND_USE_TEXT_COMMANDS: // 0x3F0
        break;
    case COMMAND_SET_THREAT_FOR_PED_TYPE: // 0x3F1
        break;
    case COMMAND_CLEAR_THREAT_FOR_PED_TYPE: // 0x3F2
        break;
    case COMMAND_GET_CAR_COLOURS: // 0x3F3
        break;
    case COMMAND_SET_ALL_CARS_CAN_BE_DAMAGED: // 0x3F4
        break;
    case COMMAND_SET_CAR_CAN_BE_DAMAGED: // 0x3F5
        break;
    case COMMAND_MAKE_PLAYER_UNSAFE: // 0x3F6
        break;
    case COMMAND_LOAD_COLLISION: // 0x3F7
        break;
    case COMMAND_GET_BODY_CAST_HEALTH: // 0x3F8
        break;
    case COMMAND_SET_CHARS_CHATTING: // 0x3F9
        break;
    case COMMAND_MAKE_PLAYER_SAFE: // 0x3FA
        break;
    case COMMAND_SET_CAR_STAYS_IN_CURRENT_LEVEL: // 0x3FB
        break;
    case COMMAND_SET_CHAR_STAYS_IN_CURRENT_LEVEL: // 0x3FC
        break;
    case COMMAND_SET_DRUNK_INPUT_DELAY: // 0x3FD
        break;
    case COMMAND_SET_CHAR_MONEY: // 0x3FE
        break;
    case COMMAND_INCREASE_CHAR_MONEY: // 0x3FF
        break;
    case COMMAND_GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS: // 0x400
        break;
    case COMMAND_REGISTER_LIFE_SAVED: // 0x401
        break;
    case COMMAND_REGISTER_CRIMINAL_CAUGHT: // 0x402
        break;
    case COMMAND_REGISTER_AMBULANCE_LEVEL: // 0x403
        break;
    case COMMAND_REGISTER_FIRE_EXTINGUISHED: // 0x404
        break;
    case COMMAND_TURN_PHONE_ON: // 0x405
        break;
    case COMMAND_REGISTER_LONGEST_DODO_FLIGHT: // 0x406
        break;
    case COMMAND_GET_OFFSET_FROM_CAR_IN_WORLD_COORDS: // 0x407
        break;
    case COMMAND_SET_TOTAL_NUMBER_OF_KILL_FRENZIES: // 0x408
        break;
    case COMMAND_BLOW_UP_RC_BUGGY: // 0x409
        break;
    case COMMAND_REMOVE_CAR_FROM_CHASE: // 0x40A
        break;
    case COMMAND_IS_FRENCH_GAME: // 0x40B
        break;
    case COMMAND_IS_GERMAN_GAME: // 0x40C
        break;
    case COMMAND_CLEAR_MISSION_AUDIO: // 0x40D
        break;
    case COMMAND_SET_FADE_IN_AFTER_NEXT_ARREST: // 0x40E
        break;
    case COMMAND_SET_FADE_IN_AFTER_NEXT_DEATH: // 0x40F
        break;
    case COMMAND_SET_GANG_PED_MODEL_PREFERENCE: // 0x410
        break;
    case COMMAND_SET_CHAR_USE_PEDNODE_SEEK: // 0x411
        break;
    case COMMAND_SWITCH_VEHICLE_WEAPONS: // 0x412
        break;
    case COMMAND_SET_GET_OUT_OF_JAIL_FREE: // 0x413
        break;
    case COMMAND_SET_FREE_HEALTH_CARE: // 0x414
        break;
    case COMMAND_IS_CAR_DOOR_CLOSED: // 0x415
        break;
    case COMMAND_LOAD_AND_LAUNCH_MISSION: // 0x416
        return OR_CONTINUE;
    case COMMAND_LOAD_AND_LAUNCH_MISSION_INTERNAL: // 0x417
    {
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
    case COMMAND_SET_OBJECT_DRAW_LAST: // 0x418
        break;
    case COMMAND_GET_AMMO_IN_PLAYER_WEAPON: // 0x419
        break;
    case COMMAND_GET_AMMO_IN_CHAR_WEAPON: // 0x41A
        break;
    case COMMAND_REGISTER_KILL_FRENZY_PASSED: // 0x41B
        break;
    case COMMAND_SET_CHAR_SAY: // 0x41C
        break;
    case COMMAND_SET_NEAR_CLIP: // 0x41D
        break;
    case COMMAND_SET_RADIO_CHANNEL: // 0x41E
        break;
    case COMMAND_OVERRIDE_HOSPITAL_LEVEL: // 0x41F
        break;
    case COMMAND_OVERRIDE_POLICE_STATION_LEVEL: // 0x420
        break;
    case COMMAND_FORCE_RAIN: // 0x421
        break;
    case COMMAND_DOES_GARAGE_CONTAIN_CAR: // 0x422
        break;
    case COMMAND_SET_CAR_TRACTION: // 0x423
        break;
    case COMMAND_ARE_MEASUREMENTS_IN_METRES: // 0x424
        break;
    case COMMAND_CONVERT_METRES_TO_FEET: // 0x425
        break;
    case COMMAND_MARK_ROADS_BETWEEN_LEVELS: // 0x426
        break;
    case COMMAND_MARK_PED_ROADS_BETWEEN_LEVELS: // 0x427
        break;
    case COMMAND_SET_CAR_AVOID_LEVEL_TRANSITIONS: // 0x428
        break;
    case COMMAND_SET_CHAR_AVOID_LEVEL_TRANSITIONS: // 0x429
        break;
    case COMMAND_IS_THREAT_FOR_PED_TYPE: // 0x42A
        break;
    case COMMAND_CLEAR_AREA_OF_CHARS: // 0x42B
        break;
    case COMMAND_SET_TOTAL_NUMBER_OF_MISSIONS: // 0x42C
        break;
    case COMMAND_CONVERT_METRES_TO_FEET_INT: // 0x42D
        break;
    case COMMAND_REGISTER_FASTEST_TIME: // 0x42E
        break;
    case COMMAND_REGISTER_HIGHEST_SCORE: // 0x42F
        break;
    case COMMAND_WARP_CHAR_INTO_CAR_AS_PASSENGER: // 0x430
        break;
    case COMMAND_IS_CAR_PASSENGER_SEAT_FREE: // 0x431
        break;
    case COMMAND_GET_CHAR_IN_CAR_PASSENGER_SEAT: // 0x432
        break;
    case COMMAND_SET_CHAR_IS_CHRIS_CRIMINAL: // 0x433
        break;
    case COMMAND_START_CREDITS: // 0x434
        break;
    case COMMAND_STOP_CREDITS: // 0x435
        break;
    case COMMAND_ARE_CREDITS_FINISHED: // 0x436
        break;
    case COMMAND_CREATE_SINGLE_PARTICLE: // 0x437
        break;
    case COMMAND_SET_CHAR_IGNORE_LEVEL_TRANSITIONS: // 0x438
        break;
    case COMMAND_GET_CHASE_CAR: // 0x439
        break;
    case COMMAND_START_BOAT_FOAM_ANIMATION: // 0x43A
        break;
    case COMMAND_UPDATE_BOAT_FOAM_ANIMATION: // 0x43B
        break;
    case COMMAND_SET_MUSIC_DOES_FADE: // 0x43C
        break;
    case COMMAND_SET_INTRO_IS_PLAYING: // 0x43D
        break;
    case COMMAND_SET_PLAYER_HOOKER: // 0x43E
        break;
    case COMMAND_PLAY_END_OF_GAME_TUNE: // 0x43F
        break;
    case COMMAND_STOP_END_OF_GAME_TUNE: // 0x440
        break;
    case COMMAND_GET_CAR_MODEL: // 0x441
        break;
    case COMMAND_IS_PLAYER_SITTING_IN_CAR: // 0x442
        break;
    case COMMAND_IS_PLAYER_SITTING_IN_ANY_CAR: // 0x443
        break;
    case COMMAND_SET_SCRIPT_FIRE_AUDIO: // 0x444
        break;
    case COMMAND_ARE_ANY_CAR_CHEATS_ACTIVATED: // 0x445
        break;
    case COMMAND_SET_CHAR_SUFFERS_CRITICAL_HITS: // 0x446
        break;
    case COMMAND_IS_PLAYER_LIFTING_A_PHONE: // 0x447
        break;
    case COMMAND_IS_CHAR_SITTING_IN_CAR: // 0x448
        break;
    case COMMAND_IS_CHAR_SITTING_IN_ANY_CAR: // 0x449
        break;
    case COMMAND_IS_PLAYER_ON_FOOT: // 0x44A
        break;
    case COMMAND_IS_CHAR_ON_FOOT: // 0x44B
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
