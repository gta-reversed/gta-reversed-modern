#include "StdInc.h"
#include "RunningScript.h"

// 0x493FE0
OpcodeResult CRunningScript::ProcessCommands1600To1699(int32 commandId) {
    switch (commandId) {
    case COMMAND_SET_PEDTYPE_AS_THREAT: // 0x640
        break;
    case COMMAND_CLEAR_CHAR_THREATS: // 0x641
        break;
    case COMMAND_IS_CHAR_AT_SCRIPTED_ATTRACTOR: // 0x642
        break;
    case COMMAND_SET_SEQUENCE_TO_REPEAT: // 0x643
        break;
    case COMMAND_CREATE_PED_GENERATOR: // 0x644
        break;
    case COMMAND_SWITCH_PED_GENERATOR: // 0x645
        break;
    case COMMAND_GET_SEQUENCE_PROGRESS: // 0x646
        break;
    case COMMAND_CLEAR_LOOK_AT: // 0x647
        break;
    case COMMAND_SET_FOLLOW_NODE_THRESHOLD_DISTANCE: // 0x648
        break;
    case COMMAND_SET_CHAR_ZONE_DISTANCE: // 0x649
        break;
    case COMMAND_ADD_PEDMODEL_AS_ATTRACTOR_USER: // 0x64A
        break;
    case COMMAND_CREATE_FX_SYSTEM: // 0x64B
        break;
    case COMMAND_PLAY_FX_SYSTEM: // 0x64C
        break;
    case COMMAND_PAUSE_FX_SYSTEM: // 0x64D
        break;
    case COMMAND_STOP_FX_SYSTEM: // 0x64E
        break;
    case COMMAND_PLAY_AND_KILL_FX_SYSTEM: // 0x64F
        break;
    case COMMAND_KILL_FX_SYSTEM: // 0x650
        break;
    case COMMAND_CREATE_FX_SYSTEM_WITH_DIRECTION: // 0x651
        break;
    case COMMAND_GET_INT_STAT: // 0x652
        break;
    case COMMAND_GET_FLOAT_STAT: // 0x653
        break;
    case COMMAND_SET_OBJECT_RENDER_SCORCHED: // 0x654
        break;
    case COMMAND_TASK_LOOK_AT_OBJECT: // 0x655
        break;
    case COMMAND_LIMIT_ANGLE: // 0x656
        break;
    case COMMAND_OPEN_CAR_DOOR: // 0x657
        break;
    case COMMAND_SET_GROUP_DEFAULT_LEADER_TASK: // 0x658
        break;
    case COMMAND_SET_ATTRACTOR_PAIR: // 0x659
        break;
    case COMMAND_PLACE_CHAR_AT_ATTRACTOR: // 0x65A
        break;
    case COMMAND_GET_PICKUP_COORDINATES: // 0x65B
        break;
    case COMMAND_REMOVE_DECISION_MAKER: // 0x65C
        break;
    case COMMAND_VIEW_INTEGER_VARIABLE: // 0x65D
        break;
    case COMMAND_VIEW_FLOAT_VARIABLE: // 0x65E
        break;
    case COMMAND_WATCH_INTEGER_VARIABLE: // 0x65F
        break;
    case COMMAND_WATCH_FLOAT_VARIABLE: // 0x660
        break;
    case COMMAND_BREAKPOINT: // 0x661
        break;
    case COMMAND_WRITE_DEBUG: // 0x662
        break;
    case COMMAND_WRITE_DEBUG_WITH_INT: // 0x663
        break;
    case COMMAND_WRITE_DEBUG_WITH_FLOAT: // 0x664
        break;
    case COMMAND_GET_CHAR_MODEL: // 0x665
        break;
    case COMMAND_IS_CHAR_TOUCHING_ANY_OBJECT: // 0x666
        break;
    case COMMAND_TASK_AIM_GUN_AT_COORD: // 0x667
        break;
    case COMMAND_TASK_SHOOT_AT_COORD: // 0x668
        break;
    case COMMAND_CREATE_FX_SYSTEM_ON_CHAR: // 0x669
        break;
    case COMMAND_CREATE_FX_SYSTEM_ON_CHAR_WITH_DIRECTION: // 0x66A
        break;
    case COMMAND_CREATE_FX_SYSTEM_ON_CAR: // 0x66B
        break;
    case COMMAND_CREATE_FX_SYSTEM_ON_CAR_WITH_DIRECTION: // 0x66C
        break;
    case COMMAND_CREATE_FX_SYSTEM_ON_OBJECT: // 0x66D
        break;
    case COMMAND_CREATE_FX_SYSTEM_ON_OBJECT_WITH_DIRECTION: // 0x66E
        break;
    case COMMAND_ADD_QUEUED_DIALOGUE: // 0x66F
        break;
    case COMMAND_IS_DIALOGUE_FINISHED: // 0x670
        break;
    case COMMAND_IS_DIALOGUE_PLAYING: // 0x671
        break;
    case COMMAND_TASK_DESTROY_CAR: // 0x672
        break;
    case COMMAND_TASK_DIVE_AND_GET_UP: // 0x673
        break;
    case COMMAND_CUSTOM_PLATE_FOR_NEXT_CAR: // 0x674
        break;
    case COMMAND_CREATE_PED_GENERATOR_AT_ATTRACTOR: // 0x675
        break;
    case COMMAND_TASK_SHUFFLE_TO_NEXT_CAR_SEAT: // 0x676
        break;
    case COMMAND_TASK_CHAT_WITH_CHAR: // 0x677
        break;
    case COMMAND_GET_CHAR_AT_SCRIPTED_ATTRACTOR: // 0x678
        break;
    case COMMAND_ATTACH_CAMERA_TO_VEHICLE: // 0x679
        break;
    case COMMAND_ATTACH_CAMERA_TO_VEHICLE_LOOK_AT_VEHICLE: // 0x67A
        break;
    case COMMAND_ATTACH_CAMERA_TO_VEHICLE_LOOK_AT_CHAR: // 0x67B
        break;
    case COMMAND_ATTACH_CAMERA_TO_CHAR: // 0x67C
        break;
    case COMMAND_ATTACH_CAMERA_TO_CHAR_LOOK_AT_VEHICLE: // 0x67D
        break;
    case COMMAND_ATTACH_CAMERA_TO_CHAR_LOOK_AT_CHAR: // 0x67E
        break;
    case COMMAND_FORCE_CAR_LIGHTS: // 0x67F
        break;
    case COMMAND_ADD_PEDTYPE_AS_ATTRACTOR_USER: // 0x680
        break;
    case COMMAND_ATTACH_OBJECT_TO_CAR: // 0x681
        break;
    case COMMAND_DETACH_OBJECT: // 0x682
        break;
    case COMMAND_ATTACH_CAR_TO_CAR: // 0x683
        break;
    case COMMAND_DETACH_CAR: // 0x684
        break;
    case COMMAND_IS_OBJECT_ATTACHED: // 0x685
        break;
    case COMMAND_IS_VEHICLE_ATTACHED: // 0x686
        break;
    case COMMAND_CLEAR_CHAR_TASKS: // 0x687
        break;
    case COMMAND_TASK_TOGGLE_PED_THREAT_SCANNER: // 0x688
        break;
    case COMMAND_POP_CAR_DOOR: // 0x689
        break;
    case COMMAND_FIX_CAR_DOOR: // 0x68A
        break;
    case COMMAND_TASK_EVERYONE_LEAVE_CAR: // 0x68B
        break;
    case COMMAND_IS_PLAYER_TARGETTING_ANYTHING: // 0x68C
        break;
    case COMMAND_GET_ACTIVE_CAMERA_COORDINATES: // 0x68D
        break;
    case COMMAND_GET_ACTIVE_CAMERA_POINT_AT: // 0x68E
        break;
    case COMMAND_GET_CLOSEST_BUYABLE_OBJECT_TO_PLAYER: // 0x68F
        break;
    case COMMAND_OPEN_FRIEND_LIST: // 0x690
        break;
    case COMMAND_CLOSE_FRIEND_LIST: // 0x691
        break;
    case COMMAND_REMOVE_FRIEND_LIST: // 0x692
        break;
    case COMMAND_SET_PEDMODEL_AS_FRIEND: // 0x693
        break;
    case COMMAND_SET_PEDTYPE_AS_FRIEND: // 0x694
        break;
    case COMMAND_CLEAR_CHAR_FRIENDS: // 0x695
        break;
    case COMMAND_SET_CHAR_FRIEND_LIST: // 0x696
        break;
    case COMMAND_POP_CAR_PANEL: // 0x697
        break;
    case COMMAND_FIX_CAR_PANEL: // 0x698
        break;
    case COMMAND_FIX_CAR_TYRE: // 0x699
        break;
    case COMMAND_ATTACH_OBJECT_TO_OBJECT: // 0x69A
        break;
    case COMMAND_ATTACH_OBJECT_TO_CHAR: // 0x69B
        break;
    case COMMAND_ATTACH_CAMERA_TO_OBJECT: // 0x69C
        break;
    case COMMAND_ATTACH_CAMERA_TO_OBJECT_LOOK_AT_VEHICLE: // 0x69D
        break;
    case COMMAND_ATTACH_CAMERA_TO_OBJECT_LOOK_AT_CHAR: // 0x69E
        break;
    case COMMAND_ATTACH_CAMERA_TO_OBJECT_LOOK_AT_OBJECT: // 0x69F
        break;
    case COMMAND_ATTACH_CAMERA_TO_CHAR_LOOK_AT_OBJECT: // 0x6A0
        break;
    case COMMAND_ATTACH_CAMERA_TO_VEHICLE_LOOK_AT_OBJECT: // 0x6A1
        break;
    case COMMAND_GET_CAR_SPEED_VECTOR: // 0x6A2
        break;
    case COMMAND_GET_CAR_MASS: // 0x6A3
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
