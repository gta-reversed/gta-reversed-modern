#include "StdInc.h"
#include "RunningScript.h"

// 0x496E00
OpcodeResult CRunningScript::ProcessCommands1700To1799(int32 commandId) {
    switch (commandId) {
    case COMMAND_TASK_KILL_THREATS_ON_FOOT_WHILE_DUCKING: // 0x6A4
        break;
    case COMMAND_TASK_DIVE_FROM_ATTACHMENT_AND_GET_UP: // 0x6A5
        break;
    case COMMAND_TASK_PLAY_ANIM_WITH_VELOCITY_EXTRACTION: // 0x6A6
        break;
    case COMMAND_ATTACH_CHAR_TO_BIKE: // 0x6A7
        break;
    case COMMAND_TASK_GOTO_CHAR_OFFSET: // 0x6A8
        break;
    case COMMAND_TASK_LOOK_AT_COORD: // 0x6A9
        break;
    case COMMAND_IS_RECORDING_GOING_ON_FOR_CAR: // 0x6AA
        break;
    case COMMAND_HIDE_CHAR_WEAPON_FOR_SCRIPTED_CUTSCENE: // 0x6AB
        break;
    case COMMAND_GET_CHAR_SPEED: // 0x6AC
        break;
    case COMMAND_SET_GROUP_DECISION_MAKER: // 0x6AD
        break;
    case COMMAND_LOAD_GROUP_DECISION_MAKER: // 0x6AE
        break;
    case COMMAND_DISABLE_PLAYER_SPRINT: // 0x6AF
        break;
    case COMMAND_TASK_SIT_DOWN: // 0x6B0
        break;
    case COMMAND_CREATE_SEARCHLIGHT: // 0x6B1
        break;
    case COMMAND_DELETE_SEARCHLIGHT: // 0x6B2
        break;
    case COMMAND_DOES_SEARCHLIGHT_EXIST: // 0x6B3
        break;
    case COMMAND_MOVE_SEARCHLIGHT_BETWEEN_COORDS: // 0x6B4
        break;
    case COMMAND_POINT_SEARCHLIGHT_AT_COORD: // 0x6B5
        break;
    case COMMAND_POINT_SEARCHLIGHT_AT_CHAR: // 0x6B6
        break;
    case COMMAND_IS_CHAR_IN_SEARCHLIGHT: // 0x6B7
        break;
    case COMMAND_SET_GROUP_DEFAULT_TASK: // 0x6B8
        break;
    case COMMAND_HAS_CUTSCENE_LOADED: // 0x6B9
        break;
    case COMMAND_TASK_TURN_CHAR_TO_FACE_COORD: // 0x6BA
        break;
    case COMMAND_TASK_DRIVE_POINT_ROUTE: // 0x6BB
        break;
    case COMMAND_FIRE_SINGLE_BULLET: // 0x6BC
        break;
    case COMMAND_IS_LINE_OF_SIGHT_CLEAR: // 0x6BD
        break;
    case COMMAND_GET_CAR_ROLL: // 0x6BE
        break;
    case COMMAND_POINT_SEARCHLIGHT_AT_VEHICLE: // 0x6BF
        break;
    case COMMAND_IS_VEHICLE_IN_SEARCHLIGHT: // 0x6C0
        break;
    case COMMAND_CREATE_SEARCHLIGHT_ON_VEHICLE: // 0x6C1
        break;
    case COMMAND_TASK_GO_TO_COORD_WHILE_AIMING: // 0x6C2
        break;
    case COMMAND_GET_NUMBER_OF_FIRES_IN_RANGE: // 0x6C3
        break;
    case COMMAND_ADD_BLIP_FOR_SEARCHLIGHT: // 0x6C4
        break;
    case COMMAND_SKIP_TO_END_AND_STOP_PLAYBACK_RECORDED_CAR: // 0x6C5
        break;
    case COMMAND_TASK_OPEN_DRIVER_DOOR: // 0x6C6
        break;
    case COMMAND_TASK_CAR_TEMP_ACTION: // 0x6C7
        break;
    case COMMAND_SET_LA_RIOTS: // 0x6C8
        break;
    case COMMAND_REMOVE_CHAR_FROM_GROUP: // 0x6C9
        break;
    case COMMAND_ATTACH_SEARCHLIGHT_TO_SEARCHLIGHT_OBJECT: // 0x6CA
        break;
    case COMMAND_SET_VEHICLE_RECORDS_COLLISIONS: // 0x6CB
        break;
    case COMMAND_DRAW_CROSS_IN_FRONT_OF_DEBUG_CAMERA: // 0x6CC
        break;
    case COMMAND_DRAW_DEBUG_CUBE: // 0x6CD
        break;
    case COMMAND_GET_CAR_LAST_ROUTE_COORDS: // 0x6CE
        break;
    case COMMAND_DISPLAY_TIMER_BARS: // 0x6CF
        break;
    case COMMAND_SWITCH_EMERGENCY_SERVICES: // 0x6D0
        break;
    case COMMAND_SET_VAR_TEXT_LABEL16: // 0x6D1
        break;
    case COMMAND_SET_LVAR_TEXT_LABEL16: // 0x6D2
        break;
    case COMMAND_VAR_TEXT_LABEL16: // 0x6D3
        break;
    case COMMAND_LVAR_TEXT_LABEL16: // 0x6D4
        break;
    case COMMAND_CREATE_CHECKPOINT: // 0x6D5
        break;
    case COMMAND_DELETE_CHECKPOINT: // 0x6D6
        break;
    case COMMAND_SWITCH_RANDOM_TRAINS: // 0x6D7
        break;
    case COMMAND_CREATE_MISSION_TRAIN: // 0x6D8
        break;
    case COMMAND_DELETE_MISSION_TRAINS: // 0x6D9
        break;
    case COMMAND_MARK_MISSION_TRAINS_AS_NO_LONGER_NEEDED: // 0x6DA
        break;
    case COMMAND_DELETE_ALL_TRAINS: // 0x6DB
        break;
    case COMMAND_SET_TRAIN_SPEED: // 0x6DC
        break;
    case COMMAND_SET_TRAIN_CRUISE_SPEED: // 0x6DD
        break;
    case COMMAND_GET_TRAIN_CABOOSE: // 0x6DE
        break;
    case COMMAND_DELETE_PLAYER: // 0x6DF
        break;
    case COMMAND_SET_TWO_PLAYER_CAMERA_MODE: // 0x6E0
        break;
    case COMMAND_TASK_CAR_MISSION: // 0x6E1
        break;
    case COMMAND_TASK_GO_TO_OBJECT: // 0x6E2
        break;
    case COMMAND_TASK_WEAPON_ROLL: // 0x6E3
        break;
    case COMMAND_TASK_CHAR_ARREST_CHAR: // 0x6E4
        break;
    case COMMAND_GET_AVAILABLE_VEHICLE_MOD: // 0x6E5
        break;
    case COMMAND_GET_VEHICLE_MOD_TYPE: // 0x6E6
        break;
    case COMMAND_ADD_VEHICLE_MOD: // 0x6E7
        break;
    case COMMAND_REMOVE_VEHICLE_MOD: // 0x6E8
        break;
    case COMMAND_REQUEST_VEHICLE_MOD: // 0x6E9
        break;
    case COMMAND_HAS_VEHICLE_MOD_LOADED: // 0x6EA
        break;
    case COMMAND_MARK_VEHICLE_MOD_AS_NO_LONGER_NEEDED: // 0x6EB
        break;
    case COMMAND_GET_NUM_AVAILABLE_PAINTJOBS: // 0x6EC
        break;
    case COMMAND_GIVE_VEHICLE_PAINTJOB: // 0x6ED
        break;
    case COMMAND_IS_GROUP_MEMBER: // 0x6EE
        break;
    case COMMAND_IS_GROUP_LEADER: // 0x6EF
        break;
    case COMMAND_SET_GROUP_SEPARATION_RANGE: // 0x6F0
        break;
    case COMMAND_LIMIT_TWO_PLAYER_DISTANCE: // 0x6F1
        break;
    case COMMAND_RELEASE_TWO_PLAYER_DISTANCE: // 0x6F2
        break;
    case COMMAND_SET_PLAYER_PLAYER_TARGETTING: // 0x6F3
        break;
    case COMMAND_CREATE_SCRIPT_GANG_ROADBLOCK: // 0x6F4
        break;
    case COMMAND_GET_SCRIPT_FIRE_COORDS: // 0x6F5
        break;
    case COMMAND_CLEAR_TWO_PLAYER_CAMERA_MODE: // 0x6F6
        break;
    case COMMAND_SET_PLAYER_PASSENGER_CAN_SHOOT: // 0x6F7
        break;
    case COMMAND_GET_NTH_CLOSEST_CAR_NODE_WITH_HEADING: // 0x6F8
        break;
    case COMMAND_GET_HEIGHT_OF_CAR_WHEELS_FROM_GROUND: // 0x6F9
        break;
    case COMMAND_SET_PLAYERS_CAN_BE_IN_SEPARATE_CARS: // 0x6FA
        break;
    case COMMAND_SWITCH_PLAYER_CROSSHAIR: // 0x6FB
        break;
    case COMMAND_DOES_CAR_HAVE_STUCK_CAR_CHECK: // 0x6FC
        break;
    case COMMAND_SET_PLAYBACK_SPEED: // 0x6FD
        break;
    case COMMAND_GET_CAR_VALUE: // 0x6FE
        break;
    case COMMAND_ARE_ANY_CHARS_NEAR_CHAR: // 0x6FF
        break;
    case COMMAND_SKIP_CUTSCENE_START: // 0x700
        break;
    case COMMAND_SKIP_CUTSCENE_END: // 0x701
        break;
    case COMMAND_GET_PERCENTAGE_TAGGED_IN_AREA: // 0x702
        break;
    case COMMAND_SET_TAG_STATUS_IN_AREA: // 0x703
        break;
    case COMMAND_CAR_GOTO_COORDINATES_RACING: // 0x704
        break;
    case COMMAND_START_PLAYBACK_RECORDED_CAR_USING_AI: // 0x705
        break;
    case COMMAND_SKIP_IN_PLAYBACK_RECORDED_CAR: // 0x706
        break;
    case COMMAND_SKIP_CUTSCENE_START_INTERNAL: // 0x707
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
