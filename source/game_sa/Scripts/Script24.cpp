#include "StdInc.h"
#include "RunningScript.h"

// 0x478000
OpcodeResult CRunningScript::ProcessCommands2400To2499(int32 commandId) {
    switch (commandId) {
    case COMMAND_SET_PLAYER_DISPLAY_VITAL_STATS_BUTTON: // 0x960
        break;
    case COMMAND_SET_CHAR_KEEP_TASK: // 0x961
        break;
    case COMMAND_DOES_CAR_HAVE_ROOF: // 0x962
        break;
    case COMMAND_SET_BLIP_FADE: // 0x963
        break;
    case COMMAND_CREATE_MENU_GRID: // 0x964
        break;
    case COMMAND_IS_CHAR_SWIMMING: // 0x965
        break;
    case COMMAND_GET_CHAR_SWIM_STATE: // 0x966
        break;
    case COMMAND_START_CHAR_FACIAL_TALK: // 0x967
        break;
    case COMMAND_STOP_CHAR_FACIAL_TALK: // 0x968
        break;
    case COMMAND_IS_BIG_VEHICLE: // 0x969
        break;
    case COMMAND_SWITCH_POLICE_HELIS: // 0x96A
        break;
    case COMMAND_STORE_CAR_MOD_STATE: // 0x96B
        break;
    case COMMAND_RESTORE_CAR_MOD_STATE: // 0x96C
        break;
    case COMMAND_GET_CURRENT_CAR_MOD: // 0x96D
        break;
    case COMMAND_IS_CAR_LOW_RIDER: // 0x96E
        break;
    case COMMAND_IS_CAR_STREET_RACER: // 0x96F
        break;
    case COMMAND_FORCE_DEATH_RESTART: // 0x970
        break;
    case COMMAND_SYNC_WATER: // 0x971
        break;
    case COMMAND_SET_CHAR_COORDINATES_NO_OFFSET: // 0x972
        break;
    case COMMAND_DOES_SCRIPT_FIRE_EXIST: // 0x973
        break;
    case COMMAND_RESET_STUFF_UPON_RESURRECTION: // 0x974
        break;
    case COMMAND_IS_EMERGENCY_SERVICES_VEHICLE: // 0x975
        break;
    case COMMAND_KILL_FX_SYSTEM_NOW: // 0x976
        break;
    case COMMAND_IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE: // 0x977
        break;
    case COMMAND_COPY_SHARED_CHAR_DECISION_MAKER: // 0x978
        break;
    case COMMAND_LOAD_SHARED_CHAR_DECISION_MAKER: // 0x979
        break;
    case COMMAND_REPORT_MISSION_AUDIO_EVENT_AT_POSITION: // 0x97A
        break;
    case COMMAND_REPORT_MISSION_AUDIO_EVENT_AT_OBJECT: // 0x97B
        break;
    case COMMAND_ATTACH_MISSION_AUDIO_TO_OBJECT: // 0x97C
        break;
    case COMMAND_GET_NUM_CAR_COLOURS: // 0x97D
        break;
    case COMMAND_IS_POLICE_VEHICLE_IN_PURSUIT: // 0x97E
        break;
    case COMMAND_GET_CAR_COLOUR_FROM_MENU_INDEX: // 0x97F
        break;
    case COMMAND_EXTINGUISH_FIRE_AT_POINT: // 0x980
        break;
    case COMMAND_HAS_TRAIN_DERAILED: // 0x981
        break;
    case COMMAND_SET_CHAR_FORCE_DIE_IN_CAR: // 0x982
        break;
    case COMMAND_SET_ONLY_CREATE_GANG_MEMBERS: // 0x983
        break;
    case COMMAND_GET_OBJECT_MODEL: // 0x984
        break;
    case COMMAND_SET_CHAR_USES_COLLISION_CLOSEST_OBJECT_OF_TYPE: // 0x985
        break;
    case COMMAND_CLEAR_ALL_SCRIPT_FIRE_FLAGS: // 0x986
        break;
    case COMMAND_GET_CAR_BLOCKING_CAR: // 0x987
        break;
    case COMMAND_GET_CURRENT_VEHICLE_PAINTJOB: // 0x988
        break;
    case COMMAND_SET_HELP_MESSAGE_BOX_SIZE: // 0x989
        break;
    case COMMAND_SET_GUNSHOT_SENSE_RANGE_FOR_RIOT2: // 0x98A
        break;
    case COMMAND_STRING_CAT16: // 0x98B
        break;
    case COMMAND_STRING_CAT8: // 0x98C
        break;
    case COMMAND_GET_CAR_MOVING_COMPONENT_OFFSET: // 0x98D
        break;
    case COMMAND_SET_NAMED_ENTRY_EXIT_FLAG: // 0x98E
        break;
    case COMMAND_RADIANS_TO_DEGREES: // 0x98F
        break;
    case COMMAND_DEGREES_TO_RADIANS: // 0x990
        break;
    case COMMAND_PAUSE_CURRENT_BEAT_TRACK: // 0x991
        break;
    case COMMAND_SET_PLAYER_CYCLE_WEAPON_BUTTON: // 0x992
        break;
    case COMMAND_SET_CHAR_AIR_RESISTANCE_MULTIPLIER: // 0x993
        break;
    case COMMAND_MARK_ROAD_NODE_AS_DONT_WANDER: // 0x994
        break;
    case COMMAND_UNMARK_ALL_ROAD_NODES_AS_DONT_WANDER: // 0x995
        break;
    case COMMAND_SET_CHECKPOINT_HEADING: // 0x996
        break;
    case COMMAND_SET_MISSION_RESPECT_TOTAL: // 0x997
        break;
    case COMMAND_AWARD_PLAYER_MISSION_RESPECT: // 0x998
        break;
    case COMMAND_SET_PLAYER_FIRE_WITH_SHOULDER_BUTTON: // 0x999
        break;
    case COMMAND_SET_CAR_COLLISION: // 0x99A
        break;
    case COMMAND_CHANGE_PLAYBACK_TO_USE_AI: // 0x99B
        break;
    case COMMAND_CAMERA_SET_SHAKE_SIMULATION_SIMPLE: // 0x99C
        break;
    case COMMAND_IS_NIGHT_VISION_ACTIVE: // 0x99D
        break;
    case COMMAND_SET_CREATE_RANDOM_COPS: // 0x99E
        break;
    case COMMAND_TASK_SET_IGNORE_WEAPON_RANGE_FLAG: // 0x99F
        break;
    case COMMAND_TASK_PICK_UP_SECOND_OBJECT: // 0x9A0
        break;
    case COMMAND_DROP_SECOND_OBJECT: // 0x9A1
        break;
    case COMMAND_REMOVE_OBJECT_ELEGANTLY: // 0x9A2
        break;
    case COMMAND_DRAW_CROSSHAIR: // 0x9A3
        break;
    case COMMAND_SET_UP_CONVERSATION_NODE_WITH_SPEECH: // 0x9A4
        break;
    case COMMAND_SET_CCTV_EFFECT: // 0x9A5
        break;
    case COMMAND_SHOW_BLIPS_ON_ALL_LEVELS: // 0x9A6
        break;
    case COMMAND_SET_CHAR_DRUGGED_UP: // 0x9A7
        break;
    case COMMAND_IS_CHAR_HEAD_MISSING: // 0x9A8
        break;
    case COMMAND_GET_HASH_KEY: // 0x9A9
        break;
    case COMMAND_SET_UP_CONVERSATION_END_NODE_WITH_SPEECH: // 0x9AA
        break;
    case COMMAND_RANDOM_PASSENGER_SAY: // 0x9AB
        break;
    case COMMAND_HIDE_ALL_FRONTEND_BLIPS: // 0x9AC
        break;
    case COMMAND_SET_PLAYER_IN_CAR_CAMERA_MODE: // 0x9AD
        break;
    case COMMAND_IS_CHAR_IN_ANY_TRAIN: // 0x9AE
        break;
    case COMMAND_SET_UP_SKIP_AFTER_MISSION: // 0x9AF
        break;
    case COMMAND_SET_VEHICLE_IS_CONSIDERED_BY_PLAYER: // 0x9B0
        break;
    case COMMAND_GET_CPU_LEVEL: // 0x9B1
        break;
    case COMMAND_GET_RANDOM_CAR_MODEL_IN_MEMORY: // 0x9B2
        break;
    case COMMAND_GET_CAR_DOOR_LOCK_STATUS: // 0x9B3
        break;
    case COMMAND_SET_CLOSEST_ENTRY_EXIT_FLAG: // 0x9B4
        break;
    case COMMAND_SET_CHAR_SIGNAL_AFTER_KILL: // 0x9B5
        break;
    case COMMAND_SET_CHAR_WANTED_BY_POLICE: // 0x9B6
        break;
    case COMMAND_SET_ZONE_NO_COPS: // 0x9B7
        break;
    case COMMAND_ADD_BLOOD: // 0x9B8
        break;
    case COMMAND_DISPLAY_CAR_NAMES: // 0x9B9
        break;
    case COMMAND_DISPLAY_ZONE_NAMES: // 0x9BA
        break;
    case COMMAND_IS_CAR_DOOR_DAMAGED: // 0x9BB
        break;
    case COMMAND_SET_CHAR_COORDINATES_DONT_WARP_GANG_NO_OFFSET: // 0x9BC
        break;
    case COMMAND_SET_MINIGAME_IN_PROGRESS: // 0x9BD
        break;
    case COMMAND_IS_MINIGAME_IN_PROGRESS: // 0x9BE
        break;
    case COMMAND_SET_FORCE_RANDOM_CAR_MODEL: // 0x9BF
        break;
    case COMMAND_GET_RANDOM_CAR_OF_TYPE_IN_ANGLED_AREA_NO_SAVE: // 0x9C0
        break;
    case COMMAND_ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS: // 0x9C1
        break;
    case COMMAND_FAIL_KILL_FRENZY: // 0x9C2
        break;
    case COMMAND_IS_COP_VEHICLE_IN_AREA_3D_NO_SAVE: // 0x9C3
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
