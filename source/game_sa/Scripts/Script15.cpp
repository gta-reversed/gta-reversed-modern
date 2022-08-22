#include "StdInc.h"
#include "RunningScript.h"

// 0x490DB0
OpcodeResult CRunningScript::ProcessCommands1500To1599(int32 commandId) {
    switch (commandId) {
    case COMMAND_TASK_SMART_FLEE_POINT: // 0x5DC
        break;
    case COMMAND_TASK_SMART_FLEE_CHAR: // 0x5DD
        break;
    case COMMAND_TASK_WANDER_STANDARD: // 0x5DE
        break;
    case COMMAND_TASK_WANDER_COP: // 0x5DF
        break;
    case COMMAND_TASK_WANDER_CRIMINAL: // 0x5E0
        break;
    case COMMAND_TASK_FOLLOW_LEADER_IN_FORMATION: // 0x5E1
        break;
    case COMMAND_TASK_KILL_CHAR_ON_FOOT: // 0x5E2
        break;
    case COMMAND_START_ADDING_STUNT_POINTS: // 0x5E3
        break;
    case COMMAND_ADD_STUNT_POINT: // 0x5E4
        break;
    case COMMAND_START_PLAYING_STUNT: // 0x5E5
        break;
    case COMMAND_HAS_STUNT_ENDED: // 0x5E6
        break;
    case COMMAND_HAS_STUNT_FAILED: // 0x5E7
        break;
    case COMMAND_START_RECORDING_STUNT: // 0x5E8
        break;
    case COMMAND_START_RECORDING_CAR: // 0x5E9
        break;
    case COMMAND_STOP_RECORDING_CARS: // 0x5EA
        break;
    case COMMAND_START_PLAYBACK_RECORDED_CAR: // 0x5EB
        break;
    case COMMAND_STOP_PLAYBACK_RECORDED_CAR: // 0x5EC
        break;
    case COMMAND_PAUSE_PLAYBACK_RECORDED_CAR: // 0x5ED
        break;
    case COMMAND_UNPAUSE_PLAYBACK_RECORDED_CAR: // 0x5EE
        break;
    case COMMAND_SET_CAR_PROTECT_CAR_REAR: // 0x5EF
        break;
    case COMMAND_SET_CAR_PROTECT_CAR_FRONT: // 0x5F0
        break;
    case COMMAND_SET_CAR_ESCORT_CAR_LEFT: // 0x5F1
        break;
    case COMMAND_SET_CAR_ESCORT_CAR_RIGHT: // 0x5F2
        break;
    case COMMAND_SET_CAR_ESCORT_CAR_REAR: // 0x5F3
        break;
    case COMMAND_SET_CAR_ESCORT_CAR_FRONT: // 0x5F4
        break;
    case COMMAND_TASK_FOLLOW_PATH_NODES_TO_COORD: // 0x5F5
        break;
    case COMMAND_IS_CHAR_IN_ANGLED_AREA_2D: // 0x5F6
        break;
    case COMMAND_IS_CHAR_IN_ANGLED_AREA_ON_FOOT_2D: // 0x5F7
        break;
    case COMMAND_IS_CHAR_IN_ANGLED_AREA_IN_CAR_2D: // 0x5F8
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_ANGLED_AREA_2D: // 0x5F9
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_ANGLED_AREA_ON_FOOT_2D: // 0x5FA
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_ANGLED_AREA_IN_CAR_2D: // 0x5FB
        break;
    case COMMAND_IS_CHAR_IN_ANGLED_AREA_3D: // 0x5FC
        break;
    case COMMAND_IS_CHAR_IN_ANGLED_AREA_ON_FOOT_3D: // 0x5FD
        break;
    case COMMAND_IS_CHAR_IN_ANGLED_AREA_IN_CAR_3D: // 0x5FE
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_ANGLED_AREA_3D: // 0x5FF
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_ANGLED_AREA_ON_FOOT_3D: // 0x600
        break;
    case COMMAND_IS_CHAR_STOPPED_IN_ANGLED_AREA_IN_CAR_3D: // 0x601
        break;
    case COMMAND_IS_CHAR_IN_TAXI: // 0x602
        break;
    case COMMAND_TASK_GO_TO_COORD_ANY_MEANS: // 0x603
        break;
    case COMMAND_GET_HEADING_FROM_VECTOR_2D: // 0x604
        break;
    case COMMAND_TASK_PLAY_ANIM: // 0x605
        break;
    case COMMAND_LOAD_PATH_NODES_IN_AREA: // 0x606
        break;
    case COMMAND_RELEASE_PATH_NODES: // 0x607
        break;
    case COMMAND_HAVE_PATH_NODES_BEEN_LOADED: // 0x608
        break;
    case COMMAND_LOAD_ALL_PATH_NODES_FOR_DEBUG: // 0x609
        break;
    case COMMAND_LOAD_CHAR_DECISION_MAKER: // 0x60A
        break;
    case COMMAND_SET_CHAR_DECISION_MAKER: // 0x60B
        break;
    case COMMAND_CLEAR_ALL_DECISION_MAKERS: // 0x60C
        break;
    case COMMAND_SET_TEXT_DROPSHADOW: // 0x60D
        break;
    case COMMAND_IS_PLAYBACK_GOING_ON_FOR_CAR: // 0x60E
        break;
    case COMMAND_SET_SENSE_RANGE: // 0x60F
        break;
    case COMMAND_SET_HEARING_RANGE: // 0x610
        break;
    case COMMAND_IS_CHAR_PLAYING_ANIM: // 0x611
        break;
    case COMMAND_SET_CHAR_ANIM_PLAYING_FLAG: // 0x612
        break;
    case COMMAND_GET_CHAR_ANIM_CURRENT_TIME: // 0x613
        break;
    case COMMAND_SET_CHAR_ANIM_CURRENT_TIME: // 0x614
        break;
    case COMMAND_OPEN_SEQUENCE_TASK: // 0x615
        break;
    case COMMAND_CLOSE_SEQUENCE_TASK: // 0x616
        break;
    case COMMAND_SCRIPT_EVENT: // 0x617
        break;
    case COMMAND_PERFORM_SEQUENCE_TASK: // 0x618
        break;
    case COMMAND_SET_CHAR_COLLISION: // 0x619
        break;
    case COMMAND_GET_CHAR_ANIM_TOTAL_TIME: // 0x61A
        break;
    case COMMAND_CLEAR_SEQUENCE_TASK: // 0x61B
        break;
    case COMMAND_CLEAR_ALL_SEQUENCE_TASKS: // 0x61C
        break;
    case COMMAND_ADD_ATTRACTOR: // 0x61D
        break;
    case COMMAND_CLEAR_ATTRACTOR: // 0x61E
        break;
    case COMMAND_CLEAR_ALL_ATTRACTORS: // 0x61F
        break;
    case COMMAND_TASK_PLAY_ANIM_FOR_TIME: // 0x620
        break;
    case COMMAND_CREATE_CHAR_AT_ATTRACTOR: // 0x621
        break;
    case COMMAND_TASK_LEAVE_CAR_IMMEDIATELY: // 0x622
        break;
    case COMMAND_INCREMENT_INT_STAT: // 0x623
        break;
    case COMMAND_INCREMENT_FLOAT_STAT: // 0x624
        break;
    case COMMAND_DECREMENT_INT_STAT: // 0x625
        break;
    case COMMAND_DECREMENT_FLOAT_STAT: // 0x626
        break;
    case COMMAND_REGISTER_INT_STAT: // 0x627
        break;
    case COMMAND_REGISTER_FLOAT_STAT: // 0x628
        break;
    case COMMAND_SET_INT_STAT: // 0x629
        break;
    case COMMAND_SET_FLOAT_STAT: // 0x62A
        break;
    case COMMAND_GET_ATTEMPTS_FOR_THIS_MISSION: // 0x62B
        break;
    case COMMAND_REGISTER_THIS_MISSION_HAS_BEEN_ATTEMPTED: // 0x62C
        break;
    case COMMAND_REGISTER_THIS_MISSION_HAS_BEEN_PASSED: // 0x62D
        break;
    case COMMAND_GET_SCRIPT_TASK_STATUS: // 0x62E
        break;
    case COMMAND_CREATE_GROUP: // 0x62F
        break;
    case COMMAND_SET_GROUP_LEADER: // 0x630
        break;
    case COMMAND_SET_GROUP_MEMBER: // 0x631
        break;
    case COMMAND_REMOVE_GROUP: // 0x632
        break;
    case COMMAND_TASK_LEAVE_ANY_CAR: // 0x633
        break;
    case COMMAND_TASK_KILL_CHAR_ON_FOOT_WHILE_DUCKING: // 0x634
        break;
    case COMMAND_TASK_AIM_GUN_AT_CHAR: // 0x635
        break;
    case COMMAND_TASK_SIDE_STEP_AND_SHOOT: // 0x636
        break;
    case COMMAND_TASK_GO_TO_COORD_WHILE_SHOOTING: // 0x637
        break;
    case COMMAND_TASK_STAY_IN_SAME_PLACE: // 0x638
        break;
    case COMMAND_TASK_TURN_CHAR_TO_FACE_CHAR: // 0x639
        break;
    case COMMAND_OPEN_THREAT_LIST: // 0x63A
        break;
    case COMMAND_CLOSE_THREAT_LIST: // 0x63B
        break;
    case COMMAND_SET_PEDMODEL_AS_THREAT: // 0x63C
        break;
    case COMMAND_SET_CHAR_THREAT_LIST: // 0x63D
        break;
    case COMMAND_REMOVE_THREAT_LIST: // 0x63E
        break;
    case COMMAND_PERFORM_SEQUENCE_TASK_REPEATEDLY: // 0x63F
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
