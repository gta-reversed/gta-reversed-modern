#include "StdInc.h"
#include "RunningScript.h"

// 0x483BD0
OpcodeResult CRunningScript::ProcessCommands900To999(int32 commandId) {
    switch (commandId) {
    case COMMAND_PRINT_STRING_IN_STRING_NOW: // 0x384
        break;
    case COMMAND_PRINT_STRING_IN_STRING_SOON: // 0x385
        break;
    case COMMAND_SET_5_REPEATED_PHONE_MESSAGES: // 0x386
        break;
    case COMMAND_SET_5_PHONE_MESSAGES: // 0x387
        break;
    case COMMAND_SET_6_REPEATED_PHONE_MESSAGES: // 0x388
        break;
    case COMMAND_SET_6_PHONE_MESSAGES: // 0x389
        break;
    case COMMAND_IS_POINT_OBSCURED_BY_A_MISSION_ENTITY: // 0x38A
        break;
    case COMMAND_LOAD_ALL_MODELS_NOW: // 0x38B
        break;
    case COMMAND_ADD_TO_OBJECT_VELOCITY: // 0x38C
        break;
    case COMMAND_DRAW_SPRITE: // 0x38D
        break;
    case COMMAND_DRAW_RECT: // 0x38E
        break;
    case COMMAND_LOAD_SPRITE: // 0x38F
        break;
    case COMMAND_LOAD_TEXTURE_DICTIONARY: // 0x390
        break;
    case COMMAND_REMOVE_TEXTURE_DICTIONARY: // 0x391
        break;
    case COMMAND_SET_OBJECT_DYNAMIC: // 0x392
        break;
    case COMMAND_SET_CHAR_ANIM_SPEED: // 0x393
        break;
    case COMMAND_PLAY_MISSION_PASSED_TUNE: // 0x394
        break;
    case COMMAND_CLEAR_AREA: // 0x395
        break;
    case COMMAND_FREEZE_ONSCREEN_TIMER: // 0x396
        break;
    case COMMAND_SWITCH_CAR_SIREN: // 0x397
        break;
    case COMMAND_SWITCH_PED_ROADS_ON_ANGLED: // 0x398
        break;
    case COMMAND_SWITCH_PED_ROADS_OFF_ANGLED: // 0x399
        break;
    case COMMAND_SWITCH_ROADS_ON_ANGLED: // 0x39A
        break;
    case COMMAND_SWITCH_ROADS_OFF_ANGLED: // 0x39B
        break;
    case COMMAND_SET_CAR_WATERTIGHT: // 0x39C
        break;
    case COMMAND_ADD_MOVING_PARTICLE_EFFECT: // 0x39D
        break;
    case COMMAND_SET_CHAR_CANT_BE_DRAGGED_OUT: // 0x39E
        break;
    case COMMAND_TURN_CAR_TO_FACE_COORD: // 0x39F
        break;
    case COMMAND_IS_CRANE_LIFTING_CAR: // 0x3A0
        break;
    case COMMAND_DRAW_SPHERE: // 0x3A1
        break;
    case COMMAND_SET_CAR_STATUS: // 0x3A2
        break;
    case COMMAND_IS_CHAR_MALE: // 0x3A3
        break;
    case COMMAND_SCRIPT_NAME: // 0x3A4
        char str[8];
        ReadTextLabelFromScript(str, 8);

        for (int i = 0; i < 8; i++)
            str[i] = tolower(str[i]);

        strncpy(m_szName, str, 8);
        return OR_CONTINUE;
    case COMMAND_CHANGE_GARAGE_TYPE_WITH_CAR_MODEL: // 0x3A5
        break;
    case COMMAND_FIND_DRUG_PLANE_COORDINATES: // 0x3A6
        break;
    case COMMAND_SAVE_INT_TO_DEBUG_FILE: // 0x3A7
        break;
    case COMMAND_SAVE_FLOAT_TO_DEBUG_FILE: // 0x3A8
        break;
    case COMMAND_SAVE_NEWLINE_TO_DEBUG_FILE: // 0x3A9
        break;
    case COMMAND_POLICE_RADIO_MESSAGE: // 0x3AA
        break;
    case COMMAND_SET_CAR_STRONG: // 0x3AB
        break;
    case COMMAND_REMOVE_ROUTE: // 0x3AC
        break;
    case COMMAND_SWITCH_RUBBISH: // 0x3AD
        break;
    case COMMAND_REMOVE_PARTICLE_EFFECTS_IN_AREA: // 0x3AE
        break;
    case COMMAND_SWITCH_STREAMING: // 0x3AF
        break;
    case COMMAND_IS_GARAGE_OPEN: // 0x3B0
        break;
    case COMMAND_IS_GARAGE_CLOSED: // 0x3B1
        break;
    case COMMAND_START_CATALINA_HELI: // 0x3B2
        break;
    case COMMAND_CATALINA_HELI_TAKE_OFF: // 0x3B3
        break;
    case COMMAND_REMOVE_CATALINA_HELI: // 0x3B4
        break;
    case COMMAND_HAS_CATALINA_HELI_BEEN_SHOT_DOWN: // 0x3B5
        break;
    case COMMAND_SWAP_NEAREST_BUILDING_MODEL: // 0x3B6
        break;
    case COMMAND_SWITCH_WORLD_PROCESSING: // 0x3B7
        break;
    case COMMAND_REMOVE_ALL_PLAYER_WEAPONS: // 0x3B8
        break;
    case COMMAND_GRAB_CATALINA_HELI: // 0x3B9
        break;
    case COMMAND_CLEAR_AREA_OF_CARS: // 0x3BA
        break;
    case COMMAND_SET_ROTATING_GARAGE_DOOR: // 0x3BB
        break;
    case COMMAND_ADD_SPHERE: // 0x3BC
        break;
    case COMMAND_REMOVE_SPHERE: // 0x3BD
        break;
    case COMMAND_CATALINA_HELI_FLY_AWAY: // 0x3BE
        break;
    case COMMAND_SET_EVERYONE_IGNORE_PLAYER: // 0x3BF
        break;
    case COMMAND_STORE_CAR_CHAR_IS_IN_NO_SAVE: // 0x3C0
        break;
    case COMMAND_STORE_CAR_PLAYER_IS_IN_NO_SAVE: // 0x3C1
        break;
    case COMMAND_IS_PHONE_DISPLAYING_MESSAGE: // 0x3C2
        break;
    case COMMAND_DISPLAY_ONSCREEN_TIMER_WITH_STRING: // 0x3C3
        break;
    case COMMAND_DISPLAY_ONSCREEN_COUNTER_WITH_STRING: // 0x3C4
        break;
    case COMMAND_CREATE_RANDOM_CAR_FOR_CAR_PARK: // 0x3C5
        break;
    case COMMAND_IS_COLLISION_IN_MEMORY: // 0x3C6
        break;
    case COMMAND_SET_WANTED_MULTIPLIER: // 0x3C7
        break;
    case COMMAND_SET_CAMERA_IN_FRONT_OF_PLAYER: // 0x3C8
        break;
    case COMMAND_IS_CAR_VISIBLY_DAMAGED: // 0x3C9
        break;
    case COMMAND_DOES_OBJECT_EXIST: // 0x3CA
        break;
    case COMMAND_LOAD_SCENE: // 0x3CB
        CollectParameters(3);
        CTimer::Stop();
        CStreaming::LoadScene(CTheScripts::ReadCVectorFromScript(0));
        CTimer::Update();
        return OR_CONTINUE;
    case COMMAND_ADD_STUCK_CAR_CHECK: // 0x3CC
        CollectParameters(3);
        CTheScripts::StuckCars.AddCarToCheck(ScriptParams[0].iParam, ScriptParams[1].fParam, ScriptParams[2].uParam, 0, 0, 0, 0, 0);
        return OR_CONTINUE;
    case COMMAND_REMOVE_STUCK_CAR_CHECK: // 0x3CD
        CollectParameters(1);
        CTheScripts::StuckCars.RemoveCarFromCheck(ScriptParams[0].iParam);
        return OR_CONTINUE;
    case COMMAND_IS_CAR_STUCK: // 0x3CE
        break;
    case COMMAND_LOAD_MISSION_AUDIO: // 0x3CF
        CollectParameters(2);
        AudioEngine.PreloadMissionAudio(ScriptParams[0].u8Param - 1, ScriptParams[1].iParam);
        return OR_CONTINUE;
    case COMMAND_HAS_MISSION_AUDIO_LOADED: // 0x3D0
        break;
    case COMMAND_PLAY_MISSION_AUDIO: // 0x3D1
        CollectParameters(1);
        AudioEngine.PlayLoadedMissionAudio(ScriptParams[0].u8Param - 1);
        return OR_CONTINUE;
    case COMMAND_HAS_MISSION_AUDIO_FINISHED: // 0x3D2
        break;
    case COMMAND_GET_CLOSEST_CAR_NODE_WITH_HEADING: // 0x3D3
        break;
    case COMMAND_HAS_IMPORT_GARAGE_SLOT_BEEN_FILLED: // 0x3D4
        break;
    case COMMAND_CLEAR_THIS_PRINT: // 0x3D5
        break;
    case COMMAND_CLEAR_THIS_BIG_PRINT: // 0x3D6
        break;
    case COMMAND_SET_MISSION_AUDIO_POSITION: // 0x3D7
        break;
    case COMMAND_ACTIVATE_SAVE_MENU: // 0x3D8
        break;
    case COMMAND_HAS_SAVE_GAME_FINISHED: // 0x3D9
        break;
    case COMMAND_NO_SPECIAL_CAMERA_FOR_THIS_GARAGE: // 0x3DA
        break;
    case COMMAND_ADD_BLIP_FOR_PICKUP_OLD: // 0x3DB
        break;
    case COMMAND_ADD_BLIP_FOR_PICKUP: // 0x3DC
        break;
    case COMMAND_ADD_SPRITE_BLIP_FOR_PICKUP: // 0x3DD
        break;
    case COMMAND_SET_PED_DENSITY_MULTIPLIER: // 0x3DE
        CollectParameters(1);
        CPopulation::PedDensityMultiplier = ScriptParams[0].fParam;
        return OR_CONTINUE;
    case COMMAND_FORCE_RANDOM_PED_TYPE: // 0x3DF
        break;
    case COMMAND_SET_TEXT_DRAW_BEFORE_FADE: // 0x3E0
        break;
    case COMMAND_GET_COLLECTABLE1S_COLLECTED: // 0x3E1
        break;
    case COMMAND_SET_CHAR_OBJ_LEAVE_ANY_CAR: // 0x3E2
        break;
    case COMMAND_SET_SPRITES_DRAW_BEFORE_FADE: // 0x3E3
        break;
    case COMMAND_SET_TEXT_RIGHT_JUSTIFY: // 0x3E4
        break;
    case COMMAND_PRINT_HELP: // 0x3E5
        break;
    case COMMAND_CLEAR_HELP: // 0x3E6
        CHud::SetHelpMessage(nullptr, true, false, false);
        return OR_CONTINUE;
    case COMMAND_FLASH_HUD_OBJECT: // 0x3E7
        CollectParameters(1);
        CHud::m_ItemToFlash = ScriptParams[0].iParam;
        return OR_CONTINUE;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
