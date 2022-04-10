#include "StdInc.h"
#include "RunningScript.h"

// 0x48EAA0
OpcodeResult CRunningScript::ProcessCommands1400To1499(int32 commandId) {
    switch (commandId) {
    case COMMAND_REGISTER_VIGILANTE_LEVEL: // 0x578
        break;
    case COMMAND_CLEAR_ALL_CHAR_ANIMS: // 0x579
        break;
    case COMMAND_SET_MAXIMUM_NUMBER_OF_CARS_IN_GARAGE: // 0x57A
        break;
    case COMMAND_WANTED_STARS_ARE_FLASHING: // 0x57B
        break;
    case COMMAND_SET_ALLOW_HURRICANES: // 0x57C
        break;
    case COMMAND_PLAY_ANNOUNCEMENT: // 0x57D
        break;
    case COMMAND_SET_PLAYER_IS_IN_STADIUM: // 0x57E
        CollectParameters(1);
        CTheScripts::bPlayerIsOffTheMap = ScriptParams[0].bParam;
        return OR_CONTINUE;
    case COMMAND_GET_BUS_FARES_COLLECTED_BY_PLAYER: // 0x57F
        break;
    case COMMAND_SET_CHAR_OBJ_BUY_ICE_CREAM: // 0x580
        break;
    case COMMAND_DISPLAY_RADAR: // 0x581 | NOTSA
        CollectParameters(1);
        CTheScripts::HideAllFrontEndMapBlips = ScriptParams[0].bParam;
        return OR_CONTINUE;
    case COMMAND_REGISTER_BEST_POSITION: // 0x582
        CollectParameters(2);
        CStats::RegisterBestPosition(static_cast<eStats>(ScriptParams[0].uParam), ScriptParams[1].fParam);
        return OR_CONTINUE;
    case COMMAND_IS_PLAYER_IN_INFO_ZONE: // 0x583
        break;
    case COMMAND_CLEAR_CHAR_ICE_CREAM_PURCHASE: // 0x584
        break;
    case COMMAND_IS_IN_CAR_FIRE_BUTTON_PRESSED: // 0x585
        break;
    case COMMAND_HAS_CHAR_ATTEMPTED_ATTRACTOR: // 0x586
        break;
    case COMMAND_SET_LOAD_COLLISION_FOR_CAR_FLAG: // 0x587
        break;
    case COMMAND_SET_LOAD_COLLISION_FOR_CHAR_FLAG: // 0x588
        break;
    case COMMAND_SET_LOAD_COLLISION_FOR_OBJECT_FLAG: // 0x589
        break;
    case COMMAND_ADD_BIG_GUN_FLASH: // 0x58A
    {
        CollectParameters(6);
        auto origin = CTheScripts::ReadCVectorFromScript(0);
        auto target = CTheScripts::ReadCVectorFromScript(3) - origin;
        target.Normalise();
        CPointLights::AddLight(ePointLightType::PLTYPE_POINTLIGHT, origin, {}, 5.0f, 1.0f, 0.8f, 0.0f, 0, false, nullptr);
        g_fx.TriggerGunshot(0, origin, target, true);
        return OR_CONTINUE;
    }
    case COMMAND_HAS_CHAR_BOUGHT_ICE_CREAM: // 0x58B
        break;
    case COMMAND_GET_PROGRESS_PERCENTAGE: // 0x58C
        break;
    case COMMAND_SET_SHORTCUT_PICKUP_POINT: // 0x58D
        break;
    case COMMAND_SET_SHORTCUT_DROPOFF_POINT_FOR_MISSION: // 0x58E
        break;
    case COMMAND_GET_RANDOM_ICE_CREAM_CUSTOMER_IN_AREA: // 0x58F
        break;
    case COMMAND_GET_RANDOM_ICE_CREAM_CUSTOMER_IN_ZONE: // 0x590
        break;
    case COMMAND_UNLOCK_ALL_CAR_DOORS_IN_AREA: // 0x591
        break;
    case COMMAND_SET_GANG_ATTACK_PLAYER_WITH_COPS: // 0x592
        break;
    case COMMAND_SET_CHAR_FRIGHTENED_IN_JACKED_CAR: // 0x593
        break;
    case COMMAND_SET_VEHICLE_TO_FADE_IN: // 0x594
        break;
    case COMMAND_REGISTER_ODDJOB_MISSION_PASSED: // 0x595
        break;
    case COMMAND_IS_PLAYER_IN_SHORTCUT_TAXI: // 0x596
        break;
    case COMMAND_IS_CHAR_DUCKING: // 0x597
        break;
    case COMMAND_CREATE_DUST_EFFECT_FOR_CUTSCENE_HELI: // 0x598
        break;
    case COMMAND_REGISTER_FIRE_LEVEL: // 0x599
        break;
    case COMMAND_IS_AUSTRALIAN_GAME: // 0x59A
        break;
    case COMMAND_DISARM_CAR_BOMB: // 0x59B
        break;
    case COMMAND_SET_ONSCREEN_COUNTER_FLASH_WHEN_FIRST_DISPLAYED: // 0x59C
        break;
    case COMMAND_SHUFFLE_CARD_DECKS: // 0x59D
        break;
    case COMMAND_FETCH_NEXT_CARD: // 0x59E
        break;
    case COMMAND_GET_OBJECT_VELOCITY: // 0x59F
        break;
    case COMMAND_IS_DEBUG_CAMERA_ON: // 0x5A0
        break;
    case COMMAND_ADD_TO_OBJECT_ROTATION_VELOCITY: // 0x5A1
        break;
    case COMMAND_SET_OBJECT_ROTATION_VELOCITY: // 0x5A2
        break;
    case COMMAND_IS_OBJECT_STATIC: // 0x5A3
        break;
    case COMMAND_GET_ANGLE_BETWEEN_2D_VECTORS: // 0x5A4
        break;
    case COMMAND_DO_2D_RECTANGLES_COLLIDE: // 0x5A5
        break;
    case COMMAND_GET_OBJECT_ROTATION_VELOCITY: // 0x5A6
        break;
    case COMMAND_ADD_VELOCITY_RELATIVE_TO_OBJECT_VELOCITY: // 0x5A7
        break;
    case COMMAND_GET_OBJECT_SPEED: // 0x5A8
        break;
    case COMMAND_SET_VAR_TEXT_LABEL: // 0x5A9
        break;
    case COMMAND_SET_LVAR_TEXT_LABEL: // 0x5AA
        break;
    case COMMAND_VAR_TEXT_LABEL: // 0x5AB
        break;
    case COMMAND_LVAR_TEXT_LABEL: // 0x5AC
        break;
    case COMMAND_IS_VAR_TEXT_LABEL_EQUAL_TO_TEXT_LABEL: // 0x5AD
        break;
    case COMMAND_IS_LVAR_TEXT_LABEL_EQUAL_TO_TEXT_LABEL: // 0x5AE
        break;
    case COMMAND_DO_2D_LINES_INTERSECT: // 0x5AF
        break;
    case COMMAND_GET_2D_LINES_INTERSECT_POINT: // 0x5B0
        break;
    case COMMAND_IS_2D_POINT_IN_TRIANGLE: // 0x5B1
        break;
    case COMMAND_IS_2D_POINT_IN_RECTANGLE_ON_LEFT_SIDE_OF_LINE: // 0x5B2
        break;
    case COMMAND_IS_2D_POINT_ON_LEFT_SIDE_OF_2D_LINE: // 0x5B3
        break;
    case COMMAND_CHAR_LOOK_AT_OBJECT_ALWAYS: // 0x5B4
        break;
    case COMMAND_APPLY_COLLISION_ON_OBJECT: // 0x5B5
        break;
    case COMMAND_SAVE_STRING_TO_DEBUG_FILE: // 0x5B6
        break;
    case COMMAND_TASK_PLAYER_ON_FOOT: // 0x5B7
        break;
    case COMMAND_TASK_PLAYER_IN_CAR: // 0x5B8
        break;
    case COMMAND_TASK_PAUSE: // 0x5B9
        break;
    case COMMAND_TASK_STAND_STILL: // 0x5BA
        break;
    case COMMAND_TASK_FALL_AND_GET_UP: // 0x5BB
        break;
    case COMMAND_TASK_JUMP: // 0x5BC
        break;
    case COMMAND_TASK_TIRED: // 0x5BD
        break;
    case COMMAND_TASK_DIE: // 0x5BE
        break;
    case COMMAND_TASK_LOOK_AT_CHAR: // 0x5BF
        break;
    case COMMAND_TASK_LOOK_AT_VEHICLE: // 0x5C0
        break;
    case COMMAND_TASK_SAY: // 0x5C1
        break;
    case COMMAND_TASK_SHAKE_FIST: // 0x5C2
        break;
    case COMMAND_TASK_COWER: // 0x5C3
        break;
    case COMMAND_TASK_HANDS_UP: // 0x5C4
        break;
    case COMMAND_TASK_DUCK: // 0x5C5
        break;
    case COMMAND_TASK_DETONATE: // 0x5C6
        break;
    case COMMAND_TASK_USE_ATM: // 0x5C7
        break;
    case COMMAND_TASK_SCRATCH_HEAD: // 0x5C8
        break;
    case COMMAND_TASK_LOOK_ABOUT: // 0x5C9
        break;
    case COMMAND_TASK_ENTER_CAR_AS_PASSENGER: // 0x5CA
        break;
    case COMMAND_TASK_ENTER_CAR_AS_DRIVER: // 0x5CB
        break;
    case COMMAND_TASK_STEAL_CAR: // 0x5CC
        break;
    case COMMAND_TASK_LEAVE_CAR: // 0x5CD
        break;
    case COMMAND_TASK_LEAVE_CAR_AND_DIE: // 0x5CE
        break;
    case COMMAND_TASK_LEAVE_CAR_AND_FLEE: // 0x5CF
        break;
    case COMMAND_TASK_CAR_DRIVE: // 0x5D0
        break;
    case COMMAND_TASK_CAR_DRIVE_TO_COORD: // 0x5D1
        break;
    case COMMAND_TASK_CAR_DRIVE_WANDER: // 0x5D2
        break;
    case COMMAND_TASK_GO_STRAIGHT_TO_COORD: // 0x5D3
        break;
    case COMMAND_TASK_ACHIEVE_HEADING: // 0x5D4
        break;
    case COMMAND_SET_CHAR_IN_DISGUISE: // 0x5D5
        break;
    case COMMAND_FLUSH_ROUTE: // 0x5D6
        break;
    case COMMAND_EXTEND_ROUTE: // 0x5D7
        break;
    case COMMAND_TASK_FOLLOW_POINT_ROUTE: // 0x5D8
        break;
    case COMMAND_TASK_GOTO_CHAR: // 0x5D9
        break;
    case COMMAND_TASK_FLEE_POINT: // 0x5DA
        break;
    case COMMAND_TASK_FLEE_CHAR: // 0x5DB
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}

