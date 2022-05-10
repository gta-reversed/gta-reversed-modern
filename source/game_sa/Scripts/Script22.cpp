#include "StdInc.h"
#include "RunningScript.h"

// 0x474900
OpcodeResult CRunningScript::ProcessCommands2200To2299(int32 commandId) {
    switch (commandId) {
    case COMMAND_ENABLE_CRANE_CONTROLS: // 0x898
        break;
    case COMMAND_ALLOCATE_SCRIPT_TO_ATTRACTOR: // 0x899
        break;
    case COMMAND_GET_CLOSEST_ATTRACTOR_WITH_THIS_SCRIPT: // 0x89A
        break;
    case COMMAND_IS_PLAYER_IN_POSITION_FOR_CONVERSATION: // 0x89B
        break;
    case COMMAND_ENABLE_CONVERSATION: // 0x89C
        break;
    case COMMAND_GET_CONVERSATION_STATUS: // 0x89D
        break;
    case COMMAND_GET_RANDOM_CHAR_IN_SPHERE_ONLY_DRUGS_BUYERS: // 0x89E
        break;
    case COMMAND_GET_PED_TYPE: // 0x89F
        break;
    case COMMAND_TASK_USE_CLOSEST_MAP_ATTRACTOR: // 0x8A0
        break;
    case COMMAND_GET_CHAR_MAP_ATTRACTOR_STATUS: // 0x8A1
        break;
    case COMMAND_PLANE_ATTACK_PLAYER_USING_DOG_FIGHT: // 0x8A2
        break;
    case COMMAND_CAN_TRIGGER_GANG_WAR_WHEN_ON_A_MISSION: // 0x8A3
        break;
    case COMMAND_CONTROL_MOVABLE_VEHICLE_PART: // 0x8A4
        break;
    case COMMAND_WINCH_CAN_PICK_VEHICLE_UP: // 0x8A5
        break;
    case COMMAND_OPEN_CAR_DOOR_A_BIT: // 0x8A6
        break;
    case COMMAND_IS_CAR_DOOR_FULLY_OPEN: // 0x8A7
        break;
    case COMMAND_SET_ALWAYS_DRAW_3D_MARKERS: // 0x8A8
        break;
    case COMMAND_STREAM_SCRIPT: // 0x8A9
        break;
    case COMMAND_STREAM_SCRIPT_INTERNAL: // 0x8AA
        break;
    case COMMAND_HAS_STREAMED_SCRIPT_LOADED: // 0x8AB
        break;
    case COMMAND_SET_GANG_WARS_TRAINING_MISSION: // 0x8AC
        break;
    case COMMAND_SET_CHAR_HAS_USED_ENTRY_EXIT: // 0x8AD
        break;
    case COMMAND_DRAW_WINDOW_TEXT: // 0x8AE
        break;
    case COMMAND_SET_CHAR_MAX_HEALTH: // 0x8AF
        break;
    case COMMAND_SET_CAR_PITCH: // 0x8B0
        break;
    case COMMAND_SET_NIGHT_VISION: // 0x8B1
        break;
    case COMMAND_SET_INFRARED_VISION: // 0x8B2
        break;
    case COMMAND_SET_ZONE_FOR_GANG_WARS_TRAINING: // 0x8B3
        break;
    case COMMAND_IS_GLOBAL_VAR_BIT_SET_CONST: // 0x8B4
        break;
    case COMMAND_IS_GLOBAL_VAR_BIT_SET_VAR: // 0x8B5
        break;
    case COMMAND_IS_GLOBAL_VAR_BIT_SET_LVAR: // 0x8B6
        break;
    case COMMAND_IS_LOCAL_VAR_BIT_SET_CONST: // 0x8B7
        break;
    case COMMAND_IS_LOCAL_VAR_BIT_SET_VAR: // 0x8B8
        break;
    case COMMAND_IS_LOCAL_VAR_BIT_SET_LVAR: // 0x8B9
        break;
    case COMMAND_SET_GLOBAL_VAR_BIT_CONST: // 0x8BA
        break;
    case COMMAND_SET_GLOBAL_VAR_BIT_VAR: // 0x8BB
        break;
    case COMMAND_SET_GLOBAL_VAR_BIT_LVAR: // 0x8BC
        break;
    case COMMAND_SET_LOCAL_VAR_BIT_CONST: // 0x8BD
        break;
    case COMMAND_SET_LOCAL_VAR_BIT_VAR: // 0x8BE
        break;
    case COMMAND_SET_LOCAL_VAR_BIT_LVAR: // 0x8BF
        break;
    case COMMAND_CLEAR_GLOBAL_VAR_BIT_CONST: // 0x8C0
        break;
    case COMMAND_CLEAR_GLOBAL_VAR_BIT_VAR: // 0x8C1
        break;
    case COMMAND_CLEAR_GLOBAL_VAR_BIT_LVAR: // 0x8C2
        break;
    case COMMAND_CLEAR_LOCAL_VAR_BIT_CONST: // 0x8C3
        break;
    case COMMAND_CLEAR_LOCAL_VAR_BIT_VAR: // 0x8C4
        break;
    case COMMAND_CLEAR_LOCAL_VAR_BIT_LVAR: // 0x8C5
        break;
    case COMMAND_SET_CHAR_CAN_BE_KNOCKED_OFF_BIKE: // 0x8C6
        break;
    case COMMAND_SET_CHAR_COORDINATES_DONT_WARP_GANG: // 0x8C7
        break;
    case COMMAND_ADD_PRICE_MODIFIER: // 0x8C8
        break;
    case COMMAND_REMOVE_PRICE_MODIFIER: // 0x8C9
        break;
    case COMMAND_INIT_ZONE_POPULATION_SETTINGS: // 0x8CA
        break;
    case COMMAND_EXPLODE_CAR_IN_CUTSCENE_SHAKE_AND_BITS: // 0x8CB
        break;
    case COMMAND_PICK_UP_OBJECT_WITH_WINCH: // 0x8CC
        break;
    case COMMAND_PICK_UP_VEHICLE_WITH_WINCH: // 0x8CD
        break;
    case COMMAND_PICK_UP_CHAR_WITH_WINCH: // 0x8CE
        break;
    case COMMAND_STORE_CAR_IN_NEAREST_IMPOUNDING_GARAGE: // 0x8CF
        break;
    case COMMAND_IS_SKIP_CUTSCENE_BUTTON_PRESSED: // 0x8D0
        break;
    case COMMAND_GET_CUTSCENE_OFFSET: // 0x8D1
        break;
    case COMMAND_SET_OBJECT_SCALE: // 0x8D2
        break;
    case COMMAND_GET_CURRENT_POPULATION_ZONE_TYPE: // 0x8D3
        break;
    case COMMAND_CREATE_MENU: // 0x8D4
        break;
    case COMMAND_CONSTANT_INT: // 0x8D5
        break;
    case COMMAND_SET_MENU_COLUMN_ORIENTATION: // 0x8D6
        break;
    case COMMAND_GET_MENU_ITEM_SELECTED: // 0x8D7
        break;
    case COMMAND_GET_MENU_ITEM_ACCEPTED: // 0x8D8
        break;
    case COMMAND_ACTIVATE_MENU_ITEM: // 0x8D9
        break;
    case COMMAND_DELETE_MENU: // 0x8DA
        break;
    case COMMAND_SET_MENU_COLUMN: // 0x8DB
        break;
    case COMMAND_SET_BLIP_ENTRY_EXIT: // 0x8DC
        break;
    case COMMAND_SWITCH_DEATH_PENALTIES: // 0x8DD
        break;
    case COMMAND_SWITCH_ARREST_PENALTIES: // 0x8DE
        break;
    case COMMAND_SET_EXTRA_HOSPITAL_RESTART_POINT: // 0x8DF
        break;
    case COMMAND_SET_EXTRA_POLICE_STATION_RESTART_POINT: // 0x8E0
        break;
    case COMMAND_FIND_NUMBER_TAGS_TAGGED: // 0x8E1
        break;
    case COMMAND_GET_TERRITORY_UNDER_CONTROL_PERCENTAGE: // 0x8E2
        break;
    case COMMAND_IS_OBJECT_IN_ANGLED_AREA_2D: // 0x8E3
        break;
    case COMMAND_IS_OBJECT_IN_ANGLED_AREA_3D: // 0x8E4
        break;
    case COMMAND_GET_RANDOM_CHAR_IN_SPHERE_NO_BRAIN: // 0x8E5
        break;
    case COMMAND_SET_PLANE_UNDERCARRIAGE_UP: // 0x8E6
        break;
    case COMMAND_DISABLE_ALL_ENTRY_EXITS: // 0x8E7
        break;
    case COMMAND_ATTACH_ANIMS_TO_MODEL: // 0x8E8
        break;
    case COMMAND_SET_OBJECT_AS_STEALABLE: // 0x8E9
        break;
    case COMMAND_SET_CREATE_RANDOM_GANG_MEMBERS: // 0x8EA
        break;
    case COMMAND_ADD_SPARKS: // 0x8EB
        break;
    case COMMAND_GET_VEHICLE_CLASS: // 0x8EC
        break;
    case COMMAND_CLEAR_CONVERSATION_FOR_CHAR: // 0x8ED
        break;
    case COMMAND_SET_MENU_ITEM_WITH_NUMBER: // 0x8EE
        break;
    case COMMAND_SET_MENU_ITEM_WITH_2_NUMBERS: // 0x8EF
        break;
    case COMMAND_APPEND_TO_NEXT_CUTSCENE: // 0x8F0
        break;
    case COMMAND_GET_NAME_OF_INFO_ZONE: // 0x8F1
        break;
    case COMMAND_VEHICLE_CAN_BE_TARGETTED_BY_HS_MISSILE: // 0x8F2
        break;
    case COMMAND_SET_FREEBIES_IN_VEHICLE: // 0x8F3
        break;
    case COMMAND_SET_SCRIPT_LIMIT_TO_GANG_SIZE: // 0x8F4
        break;
    case COMMAND_MAKE_PLAYER_GANG_DISAPPEAR: // 0x8F5
        break;
    case COMMAND_MAKE_PLAYER_GANG_REAPPEAR: // 0x8F6
        break;
    case COMMAND_GET_CLOTHES_ITEM: // 0x8F7
        break;
    case COMMAND_SHOW_UPDATE_STATS: // 0x8F8
        break;
    case COMMAND_IS_VAR_TEXT_LABEL16_EQUAL_TO_TEXT_LABEL: // 0x8F9
        break;
    case COMMAND_IS_LVAR_TEXT_LABEL16_EQUAL_TO_TEXT_LABEL: // 0x8FA
        break;
    case COMMAND_SET_COORD_BLIP_APPEARANCE: // 0x8FB
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
