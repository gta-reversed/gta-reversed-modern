#include "StdInc.h"
#include "RunningScript.h"

// 0x47D210
OpcodeResult CRunningScript::ProcessCommands400To499(int32 commandId) {
    switch (commandId) {
    case COMMAND_ADD_UPSIDEDOWN_CAR_CHECK: // 0x190
        break;
    case COMMAND_REMOVE_UPSIDEDOWN_CAR_CHECK: // 0x191
        break;
    case COMMAND_SET_CHAR_OBJ_WAIT_ON_FOOT: // 0x192
        break;
    case COMMAND_SET_CHAR_OBJ_FLEE_ON_FOOT_TILL_SAFE: // 0x193
        break;
    case COMMAND_SET_CHAR_OBJ_GUARD_SPOT: // 0x194
        break;
    case COMMAND_SET_CHAR_OBJ_GUARD_AREA: // 0x195
        break;
    case COMMAND_SET_CHAR_OBJ_WAIT_IN_CAR: // 0x196
        break;
    case COMMAND_IS_PLAYER_IN_AREA_ON_FOOT_2D: // 0x197
        break;
    case COMMAND_IS_PLAYER_IN_AREA_IN_CAR_2D: // 0x198
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_AREA_2D: // 0x199
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_AREA_ON_FOOT_2D: // 0x19A
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_AREA_IN_CAR_2D: // 0x19B
        break;
    case COMMAND_IS_PLAYER_IN_AREA_ON_FOOT_3D: // 0x19C
        break;
    case COMMAND_IS_PLAYER_IN_AREA_IN_CAR_3D: // 0x19D
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_AREA_3D: // 0x19E
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_AREA_ON_FOOT_3D: // 0x19F
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_AREA_IN_CAR_3D: // 0x1A0
        break;
    case COMMAND_IS_CHAR_IN_AREA_ON_FOOT_2D: // 0x1A1
        break;
    case COMMAND_IS_CHAR_IN_AREA_IN_CAR_2D: // 0x1A2
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_AREA_2D: // 0x1A3
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_AREA_ON_FOOT_2D: // 0x1A4
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_AREA_IN_CAR_2D: // 0x1A5
        break;
    case COMMAND_IS_CHAR_IN_AREA_ON_FOOT_3D: // 0x1A6
        break;
    case COMMAND_IS_CHAR_IN_AREA_IN_CAR_3D: // 0x1A7
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_AREA_3D: // 0x1A8
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_AREA_ON_FOOT_3D: // 0x1A9
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_AREA_IN_CAR_3D: // 0x1AA
        break;
    case COMMAND_IS_CAR_STOPPED_IN_AREA_2D: // 0x1AB
        break;
    case COMMAND_IS_CAR_STOPPED_IN_AREA_3D: // 0x1AC
        break;
    case COMMAND_LOCATE_CAR_2D: // 0x1AD
        break;
    case COMMAND_LOCATE_STOPPED_CAR_2D: // 0x1AE
        break;
    case COMMAND_LOCATE_CAR_3D: // 0x1AF
        break;
    case COMMAND_LOCATE_STOPPED_CAR_3D: // 0x1B0
        break;
    case COMMAND_GIVE_WEAPON_TO_PLAYER: // 0x1B1
        break;
    case COMMAND_GIVE_WEAPON_TO_CHAR: // 0x1B2
        break;
    case COMMAND_GIVE_WEAPON_TO_CAR: // 0x1B3
        break;
    case COMMAND_SET_PLAYER_CONTROL: // 0x1B4
        break;
    case COMMAND_FORCE_WEATHER: // 0x1B5
        break;
    case COMMAND_FORCE_WEATHER_NOW: // 0x1B6
        break;
    case COMMAND_RELEASE_WEATHER: // 0x1B7
        break;
    case COMMAND_SET_CURRENT_PLAYER_WEAPON: // 0x1B8
        break;
    case COMMAND_SET_CURRENT_CHAR_WEAPON: // 0x1B9
        break;
    case COMMAND_SET_CURRENT_CAR_WEAPON: // 0x1BA
        break;
    case COMMAND_GET_OBJECT_COORDINATES: // 0x1BB
        break;
    case COMMAND_SET_OBJECT_COORDINATES: // 0x1BC
        break;
    case COMMAND_GET_GAME_TIMER: // 0x1BD
        break;
    case COMMAND_TURN_CHAR_TO_FACE_COORD: // 0x1BE
        break;
    case COMMAND_TURN_PLAYER_TO_FACE_COORD: // 0x1BF
        break;
    case COMMAND_STORE_WANTED_LEVEL: // 0x1C0
        break;
    case COMMAND_IS_CAR_STOPPED: // 0x1C1
        break;
    case COMMAND_MARK_CHAR_AS_NO_LONGER_NEEDED: // 0x1C2
        break;
    case COMMAND_MARK_CAR_AS_NO_LONGER_NEEDED: // 0x1C3
        break;
    case COMMAND_MARK_OBJECT_AS_NO_LONGER_NEEDED: // 0x1C4
        break;
    case COMMAND_DONT_REMOVE_CHAR: // 0x1C5
        break;
    case COMMAND_DONT_REMOVE_CAR: // 0x1C6
        break;
    case COMMAND_DONT_REMOVE_OBJECT: // 0x1C7
        break;
    case COMMAND_CREATE_CHAR_AS_PASSENGER: // 0x1C8
        break;
    case COMMAND_SET_CHAR_OBJ_KILL_CHAR_ON_FOOT: // 0x1C9
        break;
    case COMMAND_SET_CHAR_OBJ_KILL_PLAYER_ON_FOOT: // 0x1CA
        break;
    case COMMAND_SET_CHAR_OBJ_KILL_CHAR_ANY_MEANS: // 0x1CB
        break;
    case COMMAND_SET_CHAR_OBJ_KILL_PLAYER_ANY_MEANS: // 0x1CC
        break;
    case COMMAND_SET_CHAR_OBJ_FLEE_CHAR_ON_FOOT_TILL_SAFE: // 0x1CD
        break;
    case COMMAND_SET_CHAR_OBJ_FLEE_PLAYER_ON_FOOT_TILL_SAFE: // 0x1CE
        break;
    case COMMAND_SET_CHAR_OBJ_FLEE_CHAR_ON_FOOT_ALWAYS: // 0x1CF
        break;
    case COMMAND_SET_CHAR_OBJ_FLEE_PLAYER_ON_FOOT_ALWAYS: // 0x1D0
        break;
    case COMMAND_SET_CHAR_OBJ_GOTO_CHAR_ON_FOOT: // 0x1D1
        break;
    case COMMAND_SET_CHAR_OBJ_GOTO_PLAYER_ON_FOOT: // 0x1D2
        break;
    case COMMAND_SET_CHAR_OBJ_LEAVE_CAR: // 0x1D3
        break;
    case COMMAND_SET_CHAR_OBJ_ENTER_CAR_AS_PASSENGER: // 0x1D4
        break;
    case COMMAND_SET_CHAR_OBJ_ENTER_CAR_AS_DRIVER: // 0x1D5
        break;
    case COMMAND_SET_CHAR_OBJ_FOLLOW_CAR_IN_CAR: // 0x1D6
        break;
    case COMMAND_SET_CHAR_OBJ_FIRE_AT_OBJECT_FROM_VEHICLE: // 0x1D7
        break;
    case COMMAND_SET_CHAR_OBJ_DESTROY_OBJECT: // 0x1D8
        break;
    case COMMAND_SET_CHAR_OBJ_DESTROY_CAR: // 0x1D9
        break;
    case COMMAND_SET_CHAR_OBJ_GOTO_AREA_ON_FOOT: // 0x1DA
        break;
    case COMMAND_SET_CHAR_OBJ_GOTO_AREA_IN_CAR: // 0x1DB
        break;
    case COMMAND_SET_CHAR_OBJ_FOLLOW_CAR_ON_FOOT_WITH_OFFSET: // 0x1DC
        break;
    case COMMAND_SET_CHAR_OBJ_GUARD_ATTACK: // 0x1DD
        break;
    case COMMAND_SET_CHAR_AS_LEADER: // 0x1DE
        break;
    case COMMAND_SET_PLAYER_AS_LEADER: // 0x1DF
        break;
    case COMMAND_LEAVE_GROUP: // 0x1E0
        break;
    case COMMAND_SET_CHAR_OBJ_FOLLOW_ROUTE: // 0x1E1
        break;
    case COMMAND_ADD_ROUTE_POINT: // 0x1E2
        break;
    case COMMAND_PRINT_WITH_NUMBER_BIG: // 0x1E3
        break;
    case COMMAND_PRINT_WITH_NUMBER: // 0x1E4
        break;
    case COMMAND_PRINT_WITH_NUMBER_NOW: // 0x1E5
        break;
    case COMMAND_PRINT_WITH_NUMBER_SOON: // 0x1E6
        break;
    case COMMAND_SWITCH_ROADS_ON: // 0x1E7
        break;
    case COMMAND_SWITCH_ROADS_OFF: // 0x1E8
        break;
    case COMMAND_GET_NUMBER_OF_PASSENGERS: // 0x1E9
        break;
    case COMMAND_GET_MAXIMUM_NUMBER_OF_PASSENGERS: // 0x1EA
        break;
    case COMMAND_SET_CAR_DENSITY_MULTIPLIER: // 0x1EB
        break;
    case COMMAND_SET_CAR_HEAVY: // 0x1EC
        break;
    case COMMAND_CLEAR_CHAR_THREAT_SEARCH: // 0x1ED
        break;
    case COMMAND_ACTIVATE_CRANE: // 0x1EE
        break;
    case COMMAND_DEACTIVATE_CRANE: // 0x1EF
        break;
    case COMMAND_SET_MAX_WANTED_LEVEL: // 0x1F0
        break;
    case COMMAND_SAVE_VAR_INT: // 0x1F1
        break;
    case COMMAND_SAVE_VAR_FLOAT: // 0x1F2
        break;
    case COMMAND_IS_CAR_IN_AIR_PROPER: // 0x1F3
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
