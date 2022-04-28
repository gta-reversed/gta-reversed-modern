#include "StdInc.h"

#include "RunningScript.h"
#include "PostEffects.h"
#include "CarGenerator.h"
#include "TheCarGenerators.h"

// 0x47A760
OpcodeResult CRunningScript::ProcessCommands2500To2599(int32 commandId) {
    switch (commandId) {
    case COMMAND_SET_PETROL_TANK_WEAKPOINT: // 0x9C4
        break;
    case COMMAND_IS_CHAR_USING_MAP_ATTRACTOR: // 0x9C5
        break;
    case COMMAND_SET_ALL_CARS_IN_AREA_VISIBLE: // 0x9C6
        break;
    case COMMAND_SET_PLAYER_MODEL: // 0x9C7
        break;
    case COMMAND_ARE_SUBTITLES_SWITCHED_ON: // 0x9C8
        break;
    case COMMAND_REMOVE_CHAR_FROM_CAR_MAINTAIN_POSITION: // 0x9C9
        break;
    case COMMAND_SET_OBJECT_PROOFS: // 0x9CA
        break;
    case COMMAND_IS_CAR_TOUCHING_CAR: // 0x9CB
        break;
    case COMMAND_DOES_OBJECT_HAVE_THIS_MODEL: // 0x9CC
        break;
    case COMMAND_IS_ITALIAN_GAME: // 0x9CD
        break;
    case COMMAND_IS_SPANISH_GAME: // 0x9CE
        break;
    case COMMAND_SET_TRAIN_FORCED_TO_SLOW_DOWN: // 0x9CF
        break;
    case COMMAND_IS_VEHICLE_ON_ALL_WHEELS: // 0x9D0
        break;
    case COMMAND_DOES_PICKUP_EXIST: // 0x9D1
        break;
    case COMMAND_ENABLE_AMBIENT_CRIME: // 0x9D2
        break;
    case COMMAND_IS_AMBIENT_CRIME_ENABLED: // 0x9D3
        break;
    case COMMAND_CLEAR_WANTED_LEVEL_IN_GARAGE: // 0x9D4
        break;
    case COMMAND_SET_CHAR_SAY_CONTEXT_IMPORTANT: // 0x9D5
        break;
    case COMMAND_SET_CHAR_SAY_SCRIPT: // 0x9D6
        break;
    case COMMAND_FORCE_INTERIOR_LIGHTING_FOR_PLAYER: // 0x9D7
        break;
    case COMMAND_DISABLE_2ND_PAD_FOR_DEBUG: // 0x9D8
        break;
    case COMMAND_USE_DETONATOR: // 0x9D9
        break;
    case COMMAND_IS_MONEY_PICKUP_AT_COORDS: // 0x9DA
        break;
    case COMMAND_SET_MENU_COLUMN_WIDTH: // 0x9DB
        break;
    case COMMAND_SET_CHAR_CAN_CLIMB_OUT_WATER: // 0x9DC
        break;
    case COMMAND_MAKE_ROOM_IN_PLAYER_GANG_FOR_MISSION_PEDS: // 0x9DD
        break;
    case COMMAND_IS_CHAR_GETTING_IN_TO_A_CAR: // 0x9DE
        break;
    case COMMAND_RESTORE_PLAYER_AFTER_2P_GAME: // 0x9DF
        break;
    case COMMAND_SET_UP_SKIP_FOR_SPECIFIC_VEHICLE: // 0x9E0
        break;
    case COMMAND_GET_CAR_MODEL_VALUE: // 0x9E1
        break;
    case COMMAND_CREATE_CAR_GENERATOR_WITH_PLATE: // 0x9E2
        break;
    case COMMAND_FIND_TRAIN_DIRECTION: // 0x9E3
        break;
    case COMMAND_SET_AIRCRAFT_CARRIER_SAM_SITE: // 0x9E4
        break;
    case COMMAND_DRAW_LIGHT_WITH_RANGE: // 0x9E5
        break;
    case COMMAND_ENABLE_BURGLARY_HOUSES: // 0x9E6
        break;
    case COMMAND_IS_PLAYER_CONTROL_ON: // 0x9E7
        break;
    case COMMAND_GET_CHAR_AREA_VISIBLE: // 0x9E8
        break;
    case COMMAND_GIVE_NON_PLAYER_CAR_NITRO: // 0x9E9
        break;
    case COMMAND_PLAYER_PUT_ON_GOGGLES: // 0x9EA
        break;
    case COMMAND_PLAYER_TAKE_OFF_GOGGLES: // 0x9EB
        break;
    case COMMAND_ALLOW_FIXED_CAMERA_COLLISION: // 0x9EC
        break;
    case COMMAND_HAS_CHAR_SPOTTED_CHAR_IN_FRONT: // 0x9ED
        break;
    case COMMAND_FORCE_BIG_MESSAGE_AND_COUNTER: // 0x9EE
        break;
    case COMMAND_SET_VEHICLE_CAMERA_TWEAK: // 0x9EF
        break;
    case COMMAND_RESET_VEHICLE_CAMERA_TWEAK: // 0x9F0
        break;
    case COMMAND_REPORT_MISSION_AUDIO_EVENT_AT_CHAR: // 0x9F1
        break;
    case COMMAND_DOES_DECISION_MAKER_EXIST: // 0x9F2
        break;
    case COMMAND_GET_RANDOM_TRAIN_IN_SPHERE_NO_SAVE: // 0x9F3
        break;
    case COMMAND_IGNORE_HEIGHT_DIFFERENCE_FOLLOWING_NODES: // 0x9F4
        break;
    case COMMAND_SHUT_ALL_CHARS_UP: // 0x9F5
        break;
    case COMMAND_SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR: // 0x9F6
        break;
    case COMMAND_REPORT_MISSION_AUDIO_EVENT_AT_CAR: // 0x9F7
        break;
    case COMMAND_DO_WEAPON_STUFF_AT_START_OF_2P_GAME: // 0x9F8
        break;
    case COMMAND_SET_MENU_HEADER_ORIENTATION: // 0x9F9 | NOTSA
        break;
    case COMMAND_HAS_GAME_JUST_RETURNED_FROM_FRONTEND: // 0x9FA
        break;
    case COMMAND_GET_CURRENT_LANGUAGE: // 0x9FB
        break;
    case COMMAND_IS_OBJECT_INTERSECTING_WORLD: // 0x9FC
        break;
    case COMMAND_GET_STRING_WIDTH: // 0x9FD
        break;
    case COMMAND_RESET_VEHICLE_HYDRAULICS: // 0x9FE
        break;
    case COMMAND_SET_RESPAWN_POINT_FOR_DURATION_OF_MISSION: // 0x9FF
        break;
    case COMMAND_IS_THIS_MODEL_A_BIKE: // 0xA00
        break;
    case COMMAND_IS_THIS_MODEL_A_CAR: // 0xA01
        break;
    case COMMAND_SWITCH_ON_GROUND_SEARCHLIGHT: // 0xA02
        break;
    case COMMAND_IS_GANG_WAR_FIGHTING_GOING_ON: // 0xA03
        break;
    case COMMAND_SET_VEHICLE_FIRING_RATE_MULTIPLIER: // 0xA04
        break;
    case COMMAND_GET_VEHICLE_FIRING_RATE_MULTIPLIER: // 0xA05
        break;
    case COMMAND_IS_NEXT_STATION_ALLOWED: // 0xA06
        break;
    case COMMAND_SKIP_TO_NEXT_ALLOWED_STATION: // 0xA07
        break;
    case COMMAND_GET_STRING_WIDTH_WITH_NUMBER: // 0xA08
        break;
    case COMMAND_SHUT_CHAR_UP_FOR_SCRIPTED_SPEECH: // 0xA09
        break;
    case COMMAND_ENABLE_DISABLED_ATTRACTORS_ON_OBJECT: // 0xA0A
        break;
    case COMMAND_LOAD_SCENE_IN_DIRECTION: // 0xA0B
        break;
    case COMMAND_IS_PLAYER_USING_JETPACK: // 0xA0C
        break;
    case COMMAND_BLOCK_VEHICLE_MODEL: // 0xA0D
        break;
    case COMMAND_CLEAR_THIS_PRINT_BIG_NOW: // 0xA0E
        break;
    case COMMAND_HAS_LANGUAGE_CHANGED: // 0xA0F
        break;
    case COMMAND_INCREMENT_INT_STAT_NO_MESSAGE: // 0xA10
        break;
    case COMMAND_SET_EXTRA_CAR_COLOURS: // 0xA11
        break;
    case COMMAND_GET_EXTRA_CAR_COLOURS: // 0xA12
        break;
    case COMMAND_MANAGE_ALL_POPULATION: // 0xA13
        CPopulation::ManageAllPopulation();
        return OR_CONTINUE;
    case COMMAND_SET_NO_RESPRAYS: // 0xA14
        break;
    case COMMAND_HAS_CAR_BEEN_RESPRAYED: // 0xA15
        break;
    case COMMAND_ATTACH_MISSION_AUDIO_TO_CAR: // 0xA16
        break;
    case COMMAND_SET_HAS_BEEN_OWNED_FOR_CAR_GENERATOR: // 0xA17
        break;
    case COMMAND_SET_UP_CONVERSATION_NODE_WITH_SCRIPTED_SPEECH: // 0xA18 0x47BA77
        break;
    case COMMAND_SET_AREA_NAME: // 0xA19
        break;
    case COMMAND_TASK_PLAY_ANIM_SECONDARY: // 0xA1A
        break;
    case COMMAND_IS_CHAR_TOUCHING_CHAR: // 0xA1B
        break;
    case COMMAND_DISABLE_HELI_AUDIO: // 0xA1C
        break;
    case COMMAND_TASK_HAND_GESTURE: // 0xA1D
        break;
    case COMMAND_TAKE_PHOTO: // 0xA1E
        break;
    case COMMAND_INCREMENT_FLOAT_STAT_NO_MESSAGE: // 0xA1F
        break;
    case COMMAND_SET_PLAYER_GROUP_TO_FOLLOW_ALWAYS: // 0xA20
        break;
    case COMMAND_IMPROVE_CAR_BY_CHEATING: // 0xA21
        break;
    case COMMAND_CHANGE_CAR_COLOUR_FROM_MENU: // 0xA22
        break;
    case COMMAND_HIGHLIGHT_MENU_ITEM: // 0xA23
        break;
    case COMMAND_SET_DISABLE_MILITARY_ZONES: // 0xA24
        break;
    case COMMAND_SET_CAMERA_POSITION_UNFIXED: // 0xA25
        break;
    case COMMAND_SET_RADIO_TO_PLAYERS_FAVOURITE_STATION: // 0xA26
        break;
    case COMMAND_SET_DEATH_WEAPONS_PERSIST: // 0xA27
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
