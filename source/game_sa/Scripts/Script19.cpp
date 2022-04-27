#include "StdInc.h"
#include "RunningScript.h"

// 0x46B460
OpcodeResult CRunningScript::ProcessCommands1900To1999(int32 commandId) {
    switch (commandId) {
    case COMMAND_SET_ZONE_GANG_STRENGTH: // 0x76C
        break;
    case COMMAND_GET_ZONE_GANG_STRENGTH: // 0x76D
        break;
    case COMMAND_SET_NO_POLICE_DURING_LA_RIOTS: // 0x76E
        break;
    case COMMAND_IS_MESSAGE_BEING_DISPLAYED: // 0x76F
        break;
    case COMMAND_SET_CHAR_IS_TARGET_PRIORITY: // 0x770
        break;
    case COMMAND_CUSTOM_PLATE_DESIGN_FOR_NEXT_CAR: // 0x771
        break;
    case COMMAND_TASK_GOTO_CAR: // 0x772
        break;
    case COMMAND_CLEAR_HELP_WITH_THIS_LABEL: // 0x773
        break;
    case COMMAND_IS_SEARCHLIGHT_BULB_ON: // 0x774
        break;
    case COMMAND_CREATE_OIL_PUDDLE: // 0x775
        break;
    case COMMAND_REQUEST_IPL: // 0x776
        break;
    case COMMAND_REMOVE_IPL: // 0x777
        break;
    case COMMAND_REMOVE_IPL_DISCREETLY: // 0x778
        break;
    case COMMAND_TASK_OPEN_PASSENGER_DOOR: // 0x779
        break;
    case COMMAND_SET_CHAR_RELATIONSHIP: // 0x77A
        break;
    case COMMAND_CLEAR_CHAR_RELATIONSHIP: // 0x77B
        break;
    case COMMAND_CLEAR_ALL_CHAR_RELATIONSHIPS: // 0x77C
        break;
    case COMMAND_GET_CAR_PITCH: // 0x77D
        break;
    case COMMAND_GET_AREA_VISIBLE: // 0x77E
        break;
    case COMMAND_ADD_INT_TO_VAR_CONSOLE: // 0x77F
        break;
    case COMMAND_HELI_KEEP_ENTITY_IN_VIEW: // 0x780
        break;
    case COMMAND_GET_WEAPONTYPE_MODEL: // 0x781
        break;
    case COMMAND_GET_WEAPONTYPE_SLOT: // 0x782
        break;
    case COMMAND_GET_SHOPPING_EXTRA_INFO: // 0x783
        break;
    case COMMAND_GIVE_PLAYER_CLOTHES: // 0x784
        break;
    case COMMAND_GIVE_PLAYER_TATTOO: // 0x785
        break;
    case COMMAND_GET_NUMBER_OF_FIRES_IN_AREA: // 0x786
        break;
    case COMMAND_SET_CHAR_TYRES_CAN_BE_BURST: // 0x787
        break;
    case COMMAND_ATTACH_WINCH_TO_HELI: // 0x788
        break;
    case COMMAND_RELEASE_ENTITY_FROM_WINCH: // 0x789
        break;
    case COMMAND_GET_TRAIN_CARRIAGE: // 0x78A
        break;
    case COMMAND_GRAB_ENTITY_ON_WINCH: // 0x78B
        break;
    case COMMAND_GET_NAME_OF_ITEM: // 0x78C
        break;
    case COMMAND_ADD_FLOAT_TO_VAR_CONSOLE: // 0x78D
        break;
    case COMMAND_TASK_DRAG_CHAR_FROM_CAR: // 0x78E
        break;
    case COMMAND_TASK_CLIMB: // 0x78F
        break;
    case COMMAND_BUY_ITEM: // 0x790
        break;
    case COMMAND_BUY_TATTOO: // 0x791
        break;
    case COMMAND_CLEAR_CHAR_TASKS_IMMEDIATELY: // 0x792
        break;
    case COMMAND_STORE_CLOTHES_STATE: // 0x793
        break;
    case COMMAND_RESTORE_CLOTHES_STATE: // 0x794
        break;
    case COMMAND_DELETE_WINCH_FOR_HELI: // 0x795
        break;
    case COMMAND_GET_ROPE_HEIGHT_FOR_OBJECT: // 0x796
        break;
    case COMMAND_SET_ROPE_HEIGHT_FOR_OBJECT: // 0x797
        break;
    case COMMAND_GRAB_ENTITY_ON_ROPE_FOR_OBJECT: // 0x798
        break;
    case COMMAND_RELEASE_ENTITY_FROM_ROPE_FOR_OBJECT: // 0x799
        break;
    case COMMAND_ATTACH_CAR_TO_ROPE_FOR_OBJECT: // 0x79A
        break;
    case COMMAND_ATTACH_CHAR_TO_ROPE_FOR_OBJECT: // 0x79B
        break;
    case COMMAND_ATTACH_OBJECT_TO_ROPE_FOR_OBJECT: // 0x79C
        break;
    case COMMAND_PLAYER_ENTERED_DOCK_CRANE: // 0x79D
        break;
    case COMMAND_PLAYER_ENTERED_BUILDINGSITE_CRANE: // 0x79E
        break;
    case COMMAND_PLAYER_LEFT_CRANE: // 0x79F
        break;
    case COMMAND_PERFORM_SEQUENCE_TASK_FROM_PROGRESS: // 0x7A0
        break;
    case COMMAND_SET_NEXT_DESIRED_MOVE_STATE: // 0x7A1
        break;
    case COMMAND_SET_NEXT_EVENT_RESPONSE_SEQUENCE: // 0x7A2
        break;
    case COMMAND_TASK_GOTO_CHAR_AIMING: // 0x7A3
        break;
    case COMMAND_GET_SEQUENCE_PROGRESS_RECURSIVE: // 0x7A4
        break;
    case COMMAND_TASK_KILL_CHAR_ON_FOOT_TIMED: // 0x7A5
        break;
    case COMMAND_GET_NEAREST_TAG_POSITION: // 0x7A6
        break;
    case COMMAND_TASK_JETPACK: // 0x7A7
        break;
    case COMMAND_SET_AREA51_SAM_SITE: // 0x7A8
        break;
    case COMMAND_IS_CHAR_IN_ANY_SEARCHLIGHT: // 0x7A9
        break;
    case COMMAND_GET_SEARCHLIGHT_COORDS: // 0x7AA
        break;
    case COMMAND_IS_TRAILER_ATTACHED_TO_CAB: // 0x7AB
        break;
    case COMMAND_DETACH_TRAILER_FROM_CAB: // 0x7AC
        break;
    case COMMAND_GET_TRAILER_ATTACHED_TO_CAB: // 0x7AD
        break;
    case COMMAND_GET_CAB_ATTACHED_TO_TRAILER: // 0x7AE
        break;
    case COMMAND_GET_PLAYER_GROUP: // 0x7AF
        break;
    case COMMAND_GET_LOADED_SHOP: // 0x7B0
        break;
    case COMMAND_GET_BEAT_PROXIMITY: // 0x7B1
        break;
    case COMMAND_SET_BEAT_ZONE_SIZE: // 0x7B2
        break;
    case COMMAND_SET_GROUP_DEFAULT_TASK_ALLOCATOR: // 0x7B3
        break;
    case COMMAND_SET_PLAYER_GROUP_RECRUITMENT: // 0x7B4
        break;
    case COMMAND_DISPLAY_TWO_ONSCREEN_COUNTERS: // 0x7B5
        break;
    case COMMAND_DISPLAY_TWO_ONSCREEN_COUNTERS_WITH_STRING: // 0x7B6
        break;
    case COMMAND_DISPLAY_NTH_TWO_ONSCREEN_COUNTERS: // 0x7B7
        break;
    case COMMAND_DISPLAY_NTH_TWO_ONSCREEN_COUNTERS_WITH_STRING: // 0x7B8
        break;
    case COMMAND_TASK_KILL_CHAR_ON_FOOT_PATROL: // 0x7B9
        break;
    case COMMAND_HELI_AIM_AHEAD_OF_TARGET_ENTITY: // 0x7BA
        break;
    case COMMAND_ACTIVATE_HELI_SPEED_CHEAT: // 0x7BB
        break;
    case COMMAND_TASK_SET_CHAR_DECISION_MAKER: // 0x7BC
        break;
    case COMMAND_DELETE_MISSION_TRAIN: // 0x7BD
        break;
    case COMMAND_MARK_MISSION_TRAIN_AS_NO_LONGER_NEEDED: // 0x7BE
        break;
    case COMMAND_SET_BLIP_ALWAYS_DISPLAY_ON_ZOOMED_RADAR: // 0x7BF
        break;
    case COMMAND_REQUEST_CAR_RECORDING: // 0x7C0
        break;
    case COMMAND_HAS_CAR_RECORDING_BEEN_LOADED: // 0x7C1
        break;
    case COMMAND_DISPLAY_PLAYBACK_RECORDED_CAR: // 0x7C2
        break;
    case COMMAND_GET_OBJECT_QUATERNION: // 0x7C3
        break;
    case COMMAND_SET_OBJECT_QUATERNION: // 0x7C4
        break;
    case COMMAND_GET_VEHICLE_QUATERNION: // 0x7C5
        break;
    case COMMAND_SET_VEHICLE_QUATERNION: // 0x7C6
        break;
    case COMMAND_SET_MISSION_TRAIN_COORDINATES: // 0x7C7
        break;
    case COMMAND_DISPLAY_DEBUG_MESSAGE: // 0x7C8
        break;
    case COMMAND_TASK_COMPLEX_PICKUP_OBJECT: // 0x7C9
        break;
    case COMMAND_TASK_SIMPLE_PUTDOWN_OBJECT: // 0x7CA
        break;
    case COMMAND_LISTEN_TO_PLAYER_GROUP_COMMANDS: // 0x7CB
        break;
    case COMMAND_SET_PLAYER_ENTER_CAR_BUTTON: // 0x7CC
        break;
    case COMMAND_TASK_CHAR_SLIDE_TO_COORD: // 0x7CD
        break;
    case COMMAND_SET_BULLET_WHIZZ_BY_DISTANCE: // 0x7CE
        break;
    case COMMAND_SET_TWO_PLAYER_CAM_MODE_SEPARATE_CARS: // 0x7CF
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
