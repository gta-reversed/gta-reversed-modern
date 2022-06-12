#include "StdInc.h"
#include "RunningScript.h"

// 0x46D050
OpcodeResult CRunningScript::ProcessCommands1800To1899(int32 commandId) {
    switch (commandId) {
    case COMMAND_CLEAR_CHAR_DECISION_MAKER_EVENT_RESPONSE: // 0x708
        break;
    case COMMAND_ADD_CHAR_DECISION_MAKER_EVENT_RESPONSE: // 0x709
        break;
    case COMMAND_TASK_PICK_UP_OBJECT: // 0x70A
        break;
    case COMMAND_DROP_OBJECT: // 0x70B
        break;
    case COMMAND_EXPLODE_CAR_IN_CUTSCENE: // 0x70C
        break;
    case COMMAND_BUILD_PLAYER_MODEL: // 0x70D
        break;
    case COMMAND_PLANE_ATTACK_PLAYER: // 0x70E
        break;
    case COMMAND_PLANE_FLY_IN_DIRECTION: // 0x70F
        break;
    case COMMAND_PLANE_FOLLOW_ENTITY: // 0x710
        break;
    case COMMAND_ALLOCATE_SCRIPT_TO_PED_GENERATOR: // 0x711
        break;
    case COMMAND_ALLOCATE_SCRIPT_TO_RANDOM_PED: // 0x712
        break;
    case COMMAND_TASK_DRIVE_BY: // 0x713
        break;
    case COMMAND_SET_CAR_STAY_IN_SLOW_LANE: // 0x714
        break;
    case COMMAND_TAKE_REMOTE_CONTROL_OF_CAR: // 0x715
        break;
    case COMMAND_IS_CLOSEST_OBJECT_OF_TYPE_SMASHED_OR_DAMAGED: // 0x716
        break;
    case COMMAND_START_SETTING_UP_CONVERSATION: // 0x717
        break;
    case COMMAND_SET_UP_CONVERSATION_NODE: // 0x718
        break;
    case COMMAND_FINISH_SETTING_UP_CONVERSATION: // 0x719
        break;
    case COMMAND_IS_CONVERSATION_AT_NODE: // 0x71A
        break;
    case COMMAND_CLEAR_ALL_CONVERSATIONS: // 0x71B
        break;
    case COMMAND_GET_CHAR_LIGHTING: // 0x71C
        break;
    case COMMAND_SET_CLOSEST_OBJECT_OF_TYPE_RENDER_SCORCHED: // 0x71D
        break;
    case COMMAND_GET_OBJECT_HEALTH: // 0x71E
        break;
    case COMMAND_SET_OBJECT_HEALTH: // 0x71F
        break;
    case COMMAND_GET_VEHICLE_WHEEL_UPGRADE_CLASS: // 0x720
        break;
    case COMMAND_GET_NUM_WHEELS_IN_UPGRADE_CLASS: // 0x721
        break;
    case COMMAND_GET_WHEEL_IN_UPGRADE_CLASS: // 0x722
        break;
    case COMMAND_BREAK_OBJECT: // 0x723
        break;
    case COMMAND_HELI_ATTACK_PLAYER: // 0x724
        break;
    case COMMAND_HELI_FLY_IN_DIRECTION: // 0x725
        break;
    case COMMAND_HELI_FOLLOW_ENTITY: // 0x726
        break;
    case COMMAND_POLICE_HELI_CHASE_ENTITY: // 0x727
        break;
    case COMMAND_SET_UP_CONVERSATION_END_NODE: // 0x728
        break;
    case COMMAND_TASK_USE_MOBILE_PHONE: // 0x729
        break;
    case COMMAND_TASK_WARP_CHAR_INTO_CAR_AS_DRIVER: // 0x72A
        break;
    case COMMAND_TASK_WARP_CHAR_INTO_CAR_AS_PASSENGER: // 0x72B
        break;
    case COMMAND_SWITCH_COPS_ON_BIKES: // 0x72C
        break;
    case COMMAND_IS_FLAME_IN_ANGLED_AREA_2D: // 0x72D
        break;
    case COMMAND_IS_FLAME_IN_ANGLED_AREA_3D: // 0x72E
        break;
    case COMMAND_ADD_STUCK_CAR_CHECK_WITH_WARP: // 0x72F
        break;
    case COMMAND_DAMAGE_CAR_PANEL: // 0x730
        break;
    case COMMAND_SET_CAR_ROLL: // 0x731
        break;
    case COMMAND_SUPPRESS_CAR_MODEL: // 0x732
        break;
    case COMMAND_DONT_SUPPRESS_CAR_MODEL: // 0x733
        break;
    case COMMAND_DONT_SUPPRESS_ANY_CAR_MODELS: // 0x734
        break;
    case COMMAND_IS_PS2_KEYBOARD_KEY_PRESSED: // 0x735
        break;
    case COMMAND_IS_PS2_KEYBOARD_KEY_JUST_PRESSED: // 0x736
        break;
    case COMMAND_IS_CHAR_HOLDING_OBJECT: // 0x737
        break;
    case COMMAND_SET_ZONE_RADAR_COLOURS: // 0x738
        break;
    case COMMAND_GIVE_LOWRIDER_SUSPENSION_TO_CAR: // 0x739
        break;
    case COMMAND_DOES_CAR_HAVE_LOWRIDER_SUSPENSION: // 0x73A
        break;
    case COMMAND_SET_CAR_CAN_GO_AGAINST_TRAFFIC: // 0x73B
        break;
    case COMMAND_DAMAGE_CAR_DOOR: // 0x73C
        break;
    case COMMAND_GET_RANDOM_CAR_IN_SPHERE: // 0x73D
        break;
    case COMMAND_GET_RANDOM_CAR_IN_SPHERE_NO_SAVE: // 0x73E
        break;
    case COMMAND_GET_RANDOM_CHAR_IN_SPHERE: // 0x73F
        break;
    case COMMAND_GET_COORDS_OF_CLOSEST_COLLECTABLE1: // 0x740
        break;
    case COMMAND_HAS_CHAR_BEEN_ARRESTED: // 0x741
        break;
    case COMMAND_SET_PLANE_THROTTLE: // 0x742
        break;
    case COMMAND_HELI_LAND_AT_COORDS: // 0x743
        break;
    case COMMAND_GET_STAT_CHANGE_AMOUNT: // 0x744
        break;
    case COMMAND_PLANE_STARTS_IN_AIR: // 0x745
        break;
    case COMMAND_SET_RELATIONSHIP: // 0x746
        break;
    case COMMAND_CLEAR_RELATIONSHIP: // 0x747
        break;
    case COMMAND_CLEAR_ALL_RELATIONSHIPS: // 0x748
        break;
    case COMMAND_CLEAR_GROUP_DECISION_MAKER_EVENT_RESPONSE: // 0x749
        break;
    case COMMAND_ADD_GROUP_DECISION_MAKER_EVENT_RESPONSE: // 0x74A
        break;
    case COMMAND_DRAW_SPRITE_WITH_ROTATION: // 0x74B
        break;
    case COMMAND_TASK_USE_ATTRACTOR: // 0x74C
        break;
    case COMMAND_TASK_SHOOT_AT_CHAR: // 0x74D
        break;
    case COMMAND_SET_INFORM_RESPECTED_FRIENDS: // 0x74E
        break;
    case COMMAND_IS_CHAR_RESPONDING_TO_EVENT: // 0x74F
        break;
    case COMMAND_SET_OBJECT_VISIBLE: // 0x750
        break;
    case COMMAND_TASK_FLEE_CHAR_ANY_MEANS: // 0x751
        break;
    case COMMAND_STOP_RECORDING_CAR: // 0x752
        break;
    case COMMAND_SET_ALERTNESS: // 0x753
        break;
    case COMMAND_FLUSH_PATROL_ROUTE: // 0x754
        break;
    case COMMAND_EXTEND_PATROL_ROUTE: // 0x755
        break;
    case COMMAND_TASK_GO_ON_PATROL: // 0x756
        break;
    case COMMAND_GET_PATROL_ALERTNESS: // 0x757
        break;
    case COMMAND_SET_CHAR_SPECIAL_EVENT: // 0x758
        break;
    case COMMAND_SET_ATTRACTOR_AS_COVER_NODE: // 0x759
        break;
    case COMMAND_PLAY_OBJECT_ANIM: // 0x75A
        break;
    case COMMAND_SET_RADAR_ZOOM: // 0x75B
        break;
    case COMMAND_DOES_BLIP_EXIST: // 0x75C
        break;
    case COMMAND_LOAD_PRICES: // 0x75D
        break;
    case COMMAND_LOAD_SHOP: // 0x75E
        break;
    case COMMAND_GET_NUMBER_OF_ITEMS_IN_SHOP: // 0x75F
        break;
    case COMMAND_GET_ITEM_IN_SHOP: // 0x760
        break;
    case COMMAND_GET_PRICE_OF_ITEM: // 0x761
        break;
    case COMMAND_TASK_DEAD: // 0x762
        break;
    case COMMAND_SET_CAR_AS_MISSION_CAR: // 0x763
        break;
    case COMMAND_IS_SEARCHLIGHT_IN_ANGLED_AREA_2D: // 0x764
        break;
    case COMMAND_IS_SEARCHLIGHT_IN_ANGLED_AREA_3D: // 0x765
        break;
    case COMMAND_SWITCH_SEARCHLIGHT_BULB: // 0x766
        break;
    case COMMAND_SET_ZONE_POPULATION_TYPE: // 0x767
        break;
    case COMMAND_SET_ZONE_GANG_CAP: // 0x768
        break;
    case COMMAND_GET_ZONE_GANG_CAP: // 0x769
        break;
    case COMMAND_SET_ZONE_DEALER_STRENGTH: // 0x76A
        break;
    case COMMAND_GET_ZONE_DEALER_STRENGTH: // 0x76B
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
