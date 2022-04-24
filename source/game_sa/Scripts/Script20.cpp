#include "StdInc.h"
#include "RunningScript.h"

// 0x472310
OpcodeResult CRunningScript::ProcessCommands2000To2099(int32 commandId) {
    switch (commandId) {
    case COMMAND_GET_CURRENT_DAY_OF_WEEK: // 0x7D0
        break;
    case COMMAND_SET_CURRENT_DAY_OF_WEEK: // 0x7D1
        break;
    case COMMAND_ACTIVATE_INTERIORS: // 0x7D2
        break;
    case COMMAND_REGISTER_SCRIPT_BRAIN_FOR_CODE_USE: // 0x7D3
        break;
    case COMMAND_REGISTER_OBJECT_SCRIPT_BRAIN_FOR_CODE_USE: // 0x7D4
        break;
    case COMMAND_APPLY_FORCE_TO_CAR: // 0x7D5
        break;
    case COMMAND_IS_INT_LVAR_EQUAL_TO_INT_VAR: // 0x7D6
        break;
    case COMMAND_IS_FLOAT_LVAR_EQUAL_TO_FLOAT_VAR: // 0x7D7
        break;
    case COMMAND_IS_INT_LVAR_NOT_EQUAL_TO_INT_VAR: // 0x7D8
        break;
    case COMMAND_IS_FLOAT_LVAR_NOT_EQUAL_TO_FLOAT_VAR: // 0x7D9
        break;
    case COMMAND_ADD_TO_CAR_ROTATION_VELOCITY: // 0x7DA
        break;
    case COMMAND_SET_CAR_ROTATION_VELOCITY: // 0x7DB
        break;
    case COMMAND_GET_CAR_ROTATION_VELOCITY: // 0x7DC
        break;
    case COMMAND_SET_CHAR_SHOOT_RATE: // 0x7DD
        break;
    case COMMAND_IS_MODEL_IN_CDIMAGE: // 0x7DE
        break;
    case COMMAND_REMOVE_OIL_PUDDLES_IN_AREA: // 0x7DF
        break;
    case COMMAND_SET_BLIP_AS_FRIENDLY: // 0x7E0
        break;
    case COMMAND_TASK_SWIM_TO_COORD: // 0x7E1
        break;
    case COMMAND_TASK_GO_STRAIGHT_TO_COORD_WITHOUT_STOPPING: // 0x7E2
        break;
    case COMMAND_GET_BEAT_INFO_FOR_CURRENT_TRACK: // 0x7E3
        break;
    case COMMAND_GET_MODEL_DIMENSIONS: // 0x7E4
        break;
    case COMMAND_COPY_CHAR_DECISION_MAKER: // 0x7E5
        break;
    case COMMAND_COPY_GROUP_DECISION_MAKER: // 0x7E6
        break;
    case COMMAND_TASK_DRIVE_POINT_ROUTE_ADVANCED: // 0x7E7
        break;
    case COMMAND_IS_RELATIONSHIP_SET: // 0x7E8
        break;
    case COMMAND_HAS_CHAR_SPOTTED_CAR: // 0x7E9
        break;
    case COMMAND_SET_ROPE_HEIGHT_FOR_HELI: // 0x7EA
        break;
    case COMMAND_GET_ROPE_HEIGHT_FOR_HELI: // 0x7EB
        break;
    case COMMAND_IS_CAR_LOWRIDER: // 0x7EC
        break;
    case COMMAND_IS_PERFORMANCE_CAR: // 0x7ED
        break;
    case COMMAND_SET_CAR_ALWAYS_CREATE_SKIDS: // 0x7EE
        break;
    case COMMAND_GET_CITY_FROM_COORDS: // 0x7EF
        break;
    case COMMAND_HAS_OBJECT_OF_TYPE_BEEN_SMASHED: // 0x7F0
        break;
    case COMMAND_IS_PLAYER_PERFORMING_WHEELIE: // 0x7F1
        break;
    case COMMAND_IS_PLAYER_PERFORMING_STOPPIE: // 0x7F2
        break;
    case COMMAND_SET_CHECKPOINT_COORDS: // 0x7F3
        break;
    case COMMAND_SET_ONSCREEN_TIMER_DISPLAY: // 0x7F4
        break;
    case COMMAND_CONTROL_CAR_HYDRAULICS: // 0x7F5
        break;
    case COMMAND_GET_GROUP_SIZE: // 0x7F6
        break;
    case COMMAND_SET_OBJECT_COLLISION_DAMAGE_EFFECT: // 0x7F7
        break;
    case COMMAND_SET_CAR_FOLLOW_CAR: // 0x7F8
        break;
    case COMMAND_PLAYER_ENTERED_QUARRY_CRANE: // 0x7F9
        break;
    case COMMAND_PLAYER_ENTERED_LAS_VEGAS_CRANE: // 0x7FA
        break;
    case COMMAND_SWITCH_ENTRY_EXIT: // 0x7FB
        break;
    case COMMAND_DISPLAY_TEXT_WITH_FLOAT: // 0x7FC
        break;
    case COMMAND_DOES_GROUP_EXIST: // 0x7FD
        break;
    case COMMAND_GIVE_MELEE_ATTACK_TO_CHAR: // 0x7FE
        break;
    case COMMAND_SET_CAR_HYDRAULICS: // 0x7FF
        break;
    case COMMAND_IS_2PLAYER_GAME_GOING_ON: // 0x800
        break;
    case COMMAND_GET_CAMERA_FOV: // 0x801
        break;
    case COMMAND_SET_GLOBAL_PED_SEARCH_PARAMS: // 0x802
        break;
    case COMMAND_DOES_CAR_HAVE_HYDRAULICS: // 0x803
        break;
    case COMMAND_TASK_CHAR_SLIDE_TO_COORD_AND_PLAY_ANIM: // 0x804
        break;
    case COMMAND_ALLOCATE_SCRIPT_TO_OBJECT: // 0x805
        break;
    case COMMAND_GET_TOTAL_NUMBER_OF_PEDS_KILLED_BY_PLAYER: // 0x806
        break;
    case COMMAND_SET_TWO_PLAYER_CAM_MODE_SAME_CAR_SHOOTING: // 0x807
        break;
    case COMMAND_SET_TWO_PLAYER_CAM_MODE_SAME_CAR_NO_SHOOTING: // 0x808
        break;
    case COMMAND_SET_TWO_PLAYER_CAM_MODE_NOT_BOTH_IN_CAR: // 0x809
        break;
    case COMMAND_GET_LEVEL_DESIGN_COORDS_FOR_OBJECT: // 0x80A
        break;
    case COMMAND_SAVE_TEXT_LABEL_TO_DEBUG_FILE: // 0x80B
        break;
    case COMMAND_GET_CHAR_BREATH: // 0x80C
        break;
    case COMMAND_SET_CHAR_BREATH: // 0x80D
        break;
    case COMMAND_GET_CHAR_HIGHEST_PRIORITY_EVENT: // 0x80E
        break;
    case COMMAND_ARE_PATHS_LOADED_FOR_CAR: // 0x80F
        break;
    case COMMAND_GET_PARKING_NODE_IN_AREA: // 0x810
        break;
    case COMMAND_GET_CAR_CHAR_IS_USING: // 0x811
        break;
    case COMMAND_TASK_PLAY_ANIM_NON_INTERRUPTABLE: // 0x812
        break;
    case COMMAND_FORCE_NEXT_DIE_ANIM: // 0x813
        break;
    case COMMAND_ADD_STUNT_JUMP: // 0x814
        break;
    case COMMAND_SET_OBJECT_COORDINATES_AND_VELOCITY: // 0x815
        break;
    case COMMAND_SET_CHAR_KINDA_STAY_IN_SAME_PLACE: // 0x816
        break;
    case COMMAND_TASK_FOLLOW_PATROL_ROUTE: // 0x817
        break;
    case COMMAND_IS_CHAR_IN_AIR: // 0x818
        break;
    case COMMAND_GET_CHAR_HEIGHT_ABOVE_GROUND: // 0x819
        break;
    case COMMAND_SET_CHAR_WEAPON_SKILL: // 0x81A
        break;
    case COMMAND_ARE_PATHS_LOADED_IN_AREA: // 0x81B
        break;
    case COMMAND_SET_TEXT_EDGE: // 0x81C
        break;
    case COMMAND_SET_CAR_ENGINE_BROKEN: // 0x81D
        break;
    case COMMAND_IS_THIS_MODEL_A_BOAT: // 0x81E
        break;
    case COMMAND_IS_THIS_MODEL_A_PLANE: // 0x81F
        break;
    case COMMAND_IS_THIS_MODEL_A_HELI: // 0x820
        break;
    case COMMAND_IS_3D_COORD_IN_ZONE: // 0x821
        break;
    case COMMAND_SET_FIRST_PERSON_IN_CAR_CAMERA_MODE: // 0x822
        break;
    case COMMAND_TASK_GREET_PARTNER: // 0x823
        break;
    case COMMAND_GET_CLOSEST_PICKUP_COORDS_TO_COORD: // 0x824
        break;
    case COMMAND_SET_HELI_BLADES_FULL_SPEED: // 0x825
        break;
    case COMMAND_DISPLAY_HUD: // 0x826
        break;
    case COMMAND_CONNECT_LODS: // 0x827
        break;
    case COMMAND_SET_MAX_FIRE_GENERATIONS: // 0x828
        break;
    case COMMAND_TASK_DIE_NAMED_ANIM: // 0x829
        break;
    case COMMAND_SET_PLAYER_DUCK_BUTTON: // 0x82A
        break;
    case COMMAND_FIND_NEAREST_MULTIBUILDING: // 0x82B
        break;
    case COMMAND_SET_MULTIBUILDING_MODEL: // 0x82C
        break;
    case COMMAND_GET_NUMBER_MULTIBUILDING_MODELS: // 0x82D
        break;
    case COMMAND_GET_MULTIBUILDING_MODEL_INDEX: // 0x82E
        break;
    case COMMAND_SET_CURRENT_BUYABLE_PROPERTY: // 0x82F
        break;
    case COMMAND_SET_POOL_TABLE_COORDS: // 0x830
        break;
    case COMMAND_IS_AUDIO_BUILD: // 0x831
        break;
    case COMMAND_CLEAR_QUEUED_DIALOGUE: // 0x832
        break;
    case COMMAND_HAS_OBJECT_BEEN_PHOTOGRAPHED: // 0x833
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
