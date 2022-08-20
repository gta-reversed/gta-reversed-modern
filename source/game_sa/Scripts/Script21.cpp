#include "StdInc.h"
#include "RunningScript.h"

// 0x470A90
OpcodeResult CRunningScript::ProcessCommands2100To2199(int32 commandId) {
    switch (commandId) {
    case COMMAND_DO_CAMERA_BUMP: // 0x834
        break;
    case COMMAND_GET_CURRENT_DATE: // 0x835
        break;
    case COMMAND_SET_OBJECT_ANIM_SPEED: // 0x836
        break;
    case COMMAND_IS_OBJECT_PLAYING_ANIM: // 0x837
        break;
    case COMMAND_SET_OBJECT_ANIM_PLAYING_FLAG: // 0x838
        break;
    case COMMAND_GET_OBJECT_ANIM_CURRENT_TIME: // 0x839
        break;
    case COMMAND_SET_OBJECT_ANIM_CURRENT_TIME: // 0x83A
        break;
    case COMMAND_GET_OBJECT_ANIM_TOTAL_TIME: // 0x83B
        break;
    case COMMAND_SET_CHAR_VELOCITY: // 0x83C
        break;
    case COMMAND_GET_CHAR_VELOCITY: // 0x83D
        break;
    case COMMAND_SET_CHAR_ROTATION: // 0x83E
        break;
    case COMMAND_GET_CAR_UPRIGHT_VALUE: // 0x83F
        break;
    case COMMAND_SET_VEHICLE_AREA_VISIBLE: // 0x840
        break;
    case COMMAND_SELECT_WEAPONS_FOR_VEHICLE: // 0x841
        break;
    case COMMAND_GET_CITY_PLAYER_IS_IN: // 0x842
        break;
    case COMMAND_GET_NAME_OF_ZONE: // 0x843
        break;
    case COMMAND_IS_VAR_TEXT_LABEL_EMPTY: // 0x844
        break;
    case COMMAND_IS_LVAR_TEXT_LABEL_EMPTY: // 0x845
        break;
    case COMMAND_IS_VAR_TEXT_LABEL16_EMPTY: // 0x846
        break;
    case COMMAND_IS_LVAR_TEXT_LABEL16_EMPTY: // 0x847
        break;
    case COMMAND_SWITCH: // 0x848
        break;
    case COMMAND_ENDSWITCH: // 0x849
        break;
    case COMMAND_CASE: // 0x84A
        break;
    case COMMAND_DEFAULT: // 0x84B
        break;
    case COMMAND_BREAK: // 0x84C
        break;
    case COMMAND_ACTIVATE_INTERIOR_PEDS: // 0x84D
        break;
    case COMMAND_SET_VEHICLE_CAN_BE_TARGETTED: // 0x84E
        break;
    case COMMAND_GET_GROUP_LEADER: // 0x84F
        break;
    case COMMAND_TASK_FOLLOW_FOOTSTEPS: // 0x850
        break;
    case COMMAND_DAMAGE_CHAR: // 0x851
        break;
    case COMMAND_SET_CAR_CAN_BE_VISIBLY_DAMAGED: // 0x852
        break;
    case COMMAND_SET_HELI_REACHED_TARGET_DISTANCE: // 0x853
        break;
    case COMMAND_BLOCK_NODES_IN_AREA: // 0x854
        break;
    case COMMAND_GET_SOUND_LEVEL_AT_COORDS: // 0x855
        break;
    case COMMAND_SET_CHAR_ALLOWED_TO_DUCK: // 0x856
        break;
    case COMMAND_SET_WATER_CONFIGURATION: // 0x857
        break;
    case COMMAND_SET_HEADING_FOR_ATTACHED_PLAYER: // 0x858
        break;
    case COMMAND_TASK_WALK_ALONGSIDE_CHAR: // 0x859
        break;
    case COMMAND_CREATE_EMERGENCY_SERVICES_CAR: // 0x85A
        break;
    case COMMAND_TASK_KINDA_STAY_IN_SAME_PLACE: // 0x85B
        break;
    case COMMAND_TASK_USE_ATTRACTOR_ADVANCED: // 0x85C
        break;
    case COMMAND_TASK_FOLLOW_PATH_NODES_TO_COORD_SHOOTING: // 0x85D
        break;
    case COMMAND_START_PLAYBACK_RECORDED_CAR_LOOPED: // 0x85E
        break;
    case COMMAND_START_PLAYBACK_RECORDED_CAR_USING_AI_LOOPED: // 0x85F
        break;
    case COMMAND_SET_CHAR_AREA_VISIBLE: // 0x860
        break;
    case COMMAND_IS_ATTACHED_PLAYER_HEADING_ACHIEVED: // 0x861
        break;
    case COMMAND_GET_MODEL_NAME_FOR_DEBUG_ONLY: // 0x862
        break;
    case COMMAND_TASK_USE_NEARBY_ENTRY_EXIT: // 0x863
        break;
    case COMMAND_ENABLE_ENTRY_EXIT_PLAYER_GROUP_WARPING: // 0x864
        break;
    case COMMAND_FREEZE_STATE_OF_INTERIORS: // 0x865
        break;
    case COMMAND_GET_CLOSEST_STEALABLE_OBJECT: // 0x866
        break;
    case COMMAND_IS_PROCEDURAL_INTERIOR_ACTIVE: // 0x867
        break;
    case COMMAND_CLEAR_THIS_VIEW_INTEGER_VARIABLE: // 0x868
        break;
    case COMMAND_CLEAR_THIS_VIEW_FLOAT_VARIABLE: // 0x869
        break;
    case COMMAND_CLEAR_ALL_VIEW_VARIABLES: // 0x86A
        break;
    case COMMAND_CLEAR_THIS_INTEGER_WATCHPOINT: // 0x86B
        break;
    case COMMAND_CLEAR_THIS_FLOAT_WATCHPOINT: // 0x86C
        break;
    case COMMAND_CLEAR_ALL_BREAKPOINTS: // 0x86D
        break;
    case COMMAND_CLEAR_ALL_WATCHPOINTS: // 0x86E
        break;
    case COMMAND_IS_THIS_MODEL_A_TRAIN: // 0x86F
        break;
    case COMMAND_GET_VEHICLE_CHAR_IS_STANDING_ON: // 0x870
        break;
    case COMMAND_SWITCH_START: // 0x871
        break;
    case COMMAND_SWITCH_CONTINUED: // 0x872
        break;
    case COMMAND_REMOVE_CAR_RECORDING: // 0x873
        break;
    case COMMAND_SET_ZONE_POPULATION_RACE: // 0x874
        break;
    case COMMAND_SET_OBJECT_ONLY_DAMAGED_BY_PLAYER: // 0x875
        break;
    case COMMAND_CREATE_BIRDS: // 0x876
        break;
    case COMMAND_GET_VEHICLE_DIRT_LEVEL: // 0x877
        break;
    case COMMAND_SET_VEHICLE_DIRT_LEVEL: // 0x878
        break;
    case COMMAND_SET_GANG_WARS_ACTIVE: // 0x879
        break;
    case COMMAND_IS_GANG_WAR_GOING_ON: // 0x87A
        break;
    case COMMAND_GIVE_PLAYER_CLOTHES_OUTSIDE_SHOP: // 0x87B
        break;
    case COMMAND_CLEAR_LOADED_SHOP: // 0x87C
        break;
    case COMMAND_SET_GROUP_SEQUENCE: // 0x87D
        break;
    case COMMAND_SET_CHAR_DROPS_WEAPONS_WHEN_DEAD: // 0x87E
        break;
    case COMMAND_SET_CHAR_NEVER_LEAVES_GROUP: // 0x87F
        break;
    case COMMAND_DRAW_RECT_WITH_TITLE: // 0x880
        break;
    case COMMAND_SET_PLAYER_FIRE_BUTTON: // 0x881
        break;
    case COMMAND_SET_ATTRACTOR_RADIUS: // 0x882
        break;
    case COMMAND_ATTACH_FX_SYSTEM_TO_CHAR_BONE: // 0x883
        break;
    case COMMAND_REGISTER_ATTRACTOR_SCRIPT_BRAIN_FOR_CODE_USE: // 0x884
        break;
    case COMMAND_CONST_INT: // 0x885
        break;
    case COMMAND_CONST_FLOAT: // 0x886
        break;
    case COMMAND_SET_HEADING_LIMIT_FOR_ATTACHED_CHAR: // 0x887
        break;
    case COMMAND_ADD_BLIP_FOR_DEAD_CHAR: // 0x888
        break;
    case COMMAND_GET_DEAD_CHAR_COORDINATES: // 0x889
        break;
    case COMMAND_TASK_PLAY_ANIM_WITH_FLAGS: // 0x88A
        break;
    case COMMAND_SET_VEHICLE_AIR_RESISTANCE_MULTIPLIER: // 0x88B
        break;
    case COMMAND_SET_CAR_COORDINATES_NO_OFFSET: // 0x88C
        break;
    case COMMAND_SET_USES_COLLISION_OF_CLOSEST_OBJECT_OF_TYPE: // 0x88D
        break;
    case COMMAND_SET_TIME_ONE_DAY_FORWARD: // 0x88E
        break;
    case COMMAND_SET_TIME_ONE_DAY_BACK: // 0x88F
        break;
    case COMMAND_SET_TIMER_BEEP_COUNTDOWN_TIME: // 0x890
        break;
    case COMMAND_TASK_SIT_IN_RESTAURANT: // 0x891
        break;
    case COMMAND_GET_RANDOM_ATTRACTOR_ON_CLOSEST_OBJECT_OF_TYPE: // 0x892
        break;
    case COMMAND_ATTACH_TRAILER_TO_CAB: // 0x893
        break;
    case COMMAND_ADD_INTERESTING_ENTITY_FOR_CHAR: // 0x894
        break;
    case COMMAND_CLEAR_INTERESTING_ENTITIES_FOR_CHAR: // 0x895
        break;
    case COMMAND_GET_CLOSEST_ATTRACTOR: // 0x896
        break;
    case COMMAND_IS_VEHICLE_TOUCHING_OBJECT: // 0x897
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
