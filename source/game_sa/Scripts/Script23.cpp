#include "StdInc.h"
#include "RunningScript.h"

// 0x4762D0
OpcodeResult CRunningScript::ProcessCommands2300To2399(int32 commandId) {
    switch (commandId) {
    case COMMAND_GET_MENU_POSITION: // 0x8FC
        break;
    case COMMAND_SET_HEATHAZE_EFFECT: // 0x8FD
        break;
    case COMMAND_IS_HELP_MESSAGE_BEING_DISPLAYED: // 0x8FE
        break;
    case COMMAND_HAS_OBJECT_BEEN_DAMAGED_BY_WEAPON: // 0x8FF
        break;
    case COMMAND_CLEAR_OBJECT_LAST_WEAPON_DAMAGE: // 0x900
        break;
    case COMMAND_SET_PLAYER_JUMP_BUTTON: // 0x901
        break;
    case COMMAND_SET_OBJECT_BEEN_PHOTOGRAPHED_FLAG: // 0x902
        break;
    case COMMAND_SET_CHAR_BEEN_PHOTOGRAPHED_FLAG: // 0x903
        break;
    case COMMAND_GET_HUD_COLOUR: // 0x904
        break;
    case COMMAND_LOCK_DOOR: // 0x905
        break;
    case COMMAND_SET_OBJECT_MASS: // 0x906
        break;
    case COMMAND_GET_OBJECT_MASS: // 0x907
        break;
    case COMMAND_SET_OBJECT_TURN_MASS: // 0x908
        break;
    case COMMAND_GET_OBJECT_TURN_MASS: // 0x909
        break;
    case COMMAND_IS_PLAYBACK_FOR_CAR_PAUSED: // 0x90A
        break;
    case COMMAND_TRIGGER_PED_BOUNCE: // 0x90B
        break;
    case COMMAND_SET_SPECIFIC_ZONE_TO_TRIGGER_GANG_WAR: // 0x90C
        break;
    case COMMAND_CLEAR_SPECIFIC_ZONES_TO_TRIGGER_GANG_WAR: // 0x90D
        break;
    case COMMAND_SET_ACTIVE_MENU_ITEM: // 0x90E
        break;
    case COMMAND_MARK_STREAMED_SCRIPT_AS_NO_LONGER_NEEDED: // 0x90F
        break;
    case COMMAND_REMOVE_STREAMED_SCRIPT: // 0x910
        break;
    case COMMAND_REGISTER_STREAMED_SCRIPT: // 0x911
        break;
    case COMMAND_SET_MESSAGE_FORMATTING: // 0x912
        break;
    case COMMAND_START_NEW_STREAMED_SCRIPT: // 0x913
        break;
    case COMMAND_REGISTER_STREAMED_SCRIPT_INTERNAL: // 0x914
        break;
    case COMMAND_SET_WEATHER_TO_APPROPRIATE_TYPE_NOW: // 0x915
        break;
    case COMMAND_WINCH_CAN_PICK_OBJECT_UP: // 0x916
        break;
    case COMMAND_SWITCH_AUDIO_ZONE: // 0x917
        break;
    case COMMAND_SET_CAR_ENGINE_ON: // 0x918
        break;
    case COMMAND_SET_CAR_LIGHTS_ON: // 0x919
        break;
    case COMMAND_GET_LATEST_CONSOLE_COMMAND: // 0x91A
        break;
    case COMMAND_RESET_LATEST_CONSOLE_COMMAND: // 0x91B
        break;
    case COMMAND_GET_USER_OF_CLOSEST_MAP_ATTRACTOR: // 0x91C
        break;
    case COMMAND_SWITCH_ROADS_BACK_TO_ORIGINAL: // 0x91D
        break;
    case COMMAND_SWITCH_PED_ROADS_BACK_TO_ORIGINAL: // 0x91E
        break;
    case COMMAND_GET_PLANE_UNDERCARRIAGE_POSITION: // 0x91F
        break;
    case COMMAND_CAMERA_SET_VECTOR_TRACK: // 0x920
        break;
    case COMMAND_CAMERA_SET_SHAKE_SIMULATION: // 0x921
        break;
    case COMMAND_CAMERA_SET_LERP_FOV: // 0x922
        break;
    case COMMAND_SWITCH_AMBIENT_PLANES: // 0x923
        break;
    case COMMAND_SET_DARKNESS_EFFECT: // 0x924
        break;
    case COMMAND_CAMERA_RESET_NEW_SCRIPTABLES: // 0x925
        break;
    case COMMAND_GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT: // 0x926
        break;
    case COMMAND_ALLOCATE_STREAMED_SCRIPT_TO_PED_GENERATOR: // 0x927
        break;
    case COMMAND_ALLOCATE_STREAMED_SCRIPT_TO_RANDOM_PED: // 0x928
        break;
    case COMMAND_ALLOCATE_STREAMED_SCRIPT_TO_OBJECT: // 0x929
        break;
    case COMMAND_SET_PLAYER_CAN_BE_DAMAGED: // 0x92A
        break;
    case COMMAND_GET_GROUP_MEMBER: // 0x92B
        break;
    case COMMAND_GET_PLAYERS_GANG_IN_CAR_ACTIVE: // 0x92C
        break;
    case COMMAND_SET_PLAYERS_GANG_IN_CAR_ACTIVE: // 0x92D
        break;
    case COMMAND_GET_WATER_HEIGHT_AT_COORDS: // 0x92E
        break;
    case COMMAND_CAMERA_PERSIST_TRACK: // 0x92F
        break;
    case COMMAND_CAMERA_PERSIST_POS: // 0x930
        break;
    case COMMAND_CAMERA_PERSIST_FOV: // 0x931
        break;
    case COMMAND_CAMERA_IS_FOV_RUNNING: // 0x932
        break;
    case COMMAND_CAMERA_IS_VECTOR_MOVE_RUNNING: // 0x933
        break;
    case COMMAND_CAMERA_IS_VECTOR_TRACK_RUNNING: // 0x934
        break;
    case COMMAND_CAMERA_IS_SHAKE_RUNNING: // 0x935
        break;
    case COMMAND_CAMERA_SET_VECTOR_MOVE: // 0x936
        break;
    case COMMAND_DRAW_WINDOW: // 0x937
        break;
    case COMMAND_CLEAR_ALL_QUEUED_DIALOGUE: // 0x938
        break;
    case COMMAND_ATTACH_CAR_TO_OBJECT: // 0x939
        break;
    case COMMAND_SET_GARAGE_RESPRAY_FREE: // 0x93A
        break;
    case COMMAND_SET_CHAR_BULLETPROOF_VEST: // 0x93B
        break;
    case COMMAND_SET_ONSCREEN_COUNTER_COLOUR: // 0x93C
        break;
    case COMMAND_SET_CINEMA_CAMERA: // 0x93D
        break;
    case COMMAND_SET_CHAR_FIRE_DAMAGE_MULTIPLIER: // 0x93E
        break;
    case COMMAND_IS_FIRE_BUTTON_PRESSED: // 0x93F
        break;
    case COMMAND_SET_GROUP_FOLLOW_STATUS: // 0x940
        break;
    case COMMAND_SET_SEARCHLIGHT_CLIP_IF_COLLIDING: // 0x941
        break;
    case COMMAND_HAS_PLAYER_BOUGHT_ITEM: // 0x942
        break;
    case COMMAND_SET_CAMERA_BEHIND_CHAR: // 0x943
        break;
    case COMMAND_SET_CAMERA_IN_FRONT_OF_CHAR: // 0x944
        break;
    case COMMAND_GET_PLAYER_MAX_ARMOUR: // 0x945
        break;
    case COMMAND_SET_CHAR_USES_UPPERBODY_DAMAGE_ANIMS_ONLY: // 0x946
        break;
    case COMMAND_SET_CHAR_SAY_CONTEXT: // 0x947
        break;
    case COMMAND_ADD_EXPLOSION_VARIABLE_SHAKE: // 0x948
        break;
    case COMMAND_ATTACH_MISSION_AUDIO_TO_CHAR: // 0x949
        break;
    case COMMAND_UPDATE_PICKUP_MONEY_PER_DAY: // 0x94A
        break;
    case COMMAND_GET_NAME_OF_ENTRY_EXIT_CHAR_USED: // 0x94B
        break;
    case COMMAND_GET_POSITION_OF_ENTRY_EXIT_CHAR_USED: // 0x94C
        break;
    case COMMAND_IS_CHAR_TALKING: // 0x94D
        break;
    case COMMAND_DISABLE_CHAR_SPEECH: // 0x94E
        break;
    case COMMAND_ENABLE_CHAR_SPEECH: // 0x94F
        break;
    case COMMAND_SET_UP_SKIP: // 0x950
        break;
    case COMMAND_CLEAR_SKIP: // 0x951
        break;
    case COMMAND_PRELOAD_BEAT_TRACK: // 0x952
        break;
    case COMMAND_GET_BEAT_TRACK_STATUS: // 0x953
        break;
    case COMMAND_PLAY_BEAT_TRACK: // 0x954
        break;
    case COMMAND_STOP_BEAT_TRACK: // 0x955
        break;
    case COMMAND_FIND_MAX_NUMBER_OF_GROUP_MEMBERS: // 0x956
        break;
    case COMMAND_VEHICLE_DOES_PROVIDE_COVER: // 0x957
        break;
    case COMMAND_CREATE_SNAPSHOT_PICKUP: // 0x958
        break;
    case COMMAND_CREATE_HORSESHOE_PICKUP: // 0x959
        break;
    case COMMAND_CREATE_OYSTER_PICKUP: // 0x95A
        break;
    case COMMAND_HAS_OBJECT_BEEN_UPROOTED: // 0x95B
        break;
    case COMMAND_ADD_SMOKE_PARTICLE: // 0x95C
        break;
    case COMMAND_IS_CHAR_STUCK_UNDER_CAR: // 0x95D
        break;
    case COMMAND_CONTROL_CAR_DOOR: // 0x95E
        break;
    case COMMAND_GET_DOOR_ANGLE_RATIO: // 0x95F
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
