#include "StdInc.h"
#include "RunningScript.h"

// 0x48A320
OpcodeResult CRunningScript::ProcessCommands1100To1199(int32 commandId) {
    switch (commandId) {
    case COMMAND_LOAD_COLLISION_WITH_SCREEN: // 0x44C
        break;
    case COMMAND_LOAD_SPLASH_SCREEN: // 0x44D
        break;
    case COMMAND_SET_CAR_IGNORE_LEVEL_TRANSITIONS: // 0x44E
        break;
    case COMMAND_MAKE_CRAIGS_CAR_A_BIT_STRONGER: // 0x44F
        break;
    case COMMAND_SET_JAMES_CAR_ON_PATH_TO_PLAYER: // 0x450
        break;
    case COMMAND_LOAD_END_OF_GAME_TUNE: // 0x451
        break;
    case COMMAND_ENABLE_PLAYER_CONTROL_CAMERA: // 0x452
        break;
    case COMMAND_SET_OBJECT_ROTATION: // 0x453
        break;
    case COMMAND_GET_DEBUG_CAMERA_COORDINATES: // 0x454
        break;
    case COMMAND_GET_DEBUG_CAMERA_FRONT_VECTOR: // 0x455
        break;
    case COMMAND_IS_PLAYER_TARGETTING_ANY_CHAR: // 0x456
        break;
    case COMMAND_IS_PLAYER_TARGETTING_CHAR: // 0x457
        break;
    case COMMAND_IS_PLAYER_TARGETTING_OBJECT: // 0x458
        break;
    case COMMAND_TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME: // 0x459
    {
        char str[8];
        ReadTextLabelFromScript(str, 8);

        for (int i = 0; i < 8; i++)
            str[i] = tolower(str[i]);

        CRunningScript *script = CTheScripts::pActiveScripts;
        while (script) {
            CRunningScript* next = script->m_pNext;
            if (!strcmp(script->m_szName, str)) {
                script->RemoveScriptFromList(&CTheScripts::pActiveScripts);
                script->AddScriptToList(&CTheScripts::pIdleScripts);
                script->ShutdownThisScript();
            }
            script = next;
        }
        return OR_CONTINUE;
    }
    case COMMAND_DISPLAY_TEXT_WITH_NUMBER: // 0x45A
        break;
    case COMMAND_DISPLAY_TEXT_WITH_2_NUMBERS: // 0x45B
        break;
    case COMMAND_FAIL_CURRENT_MISSION: // 0x45C 0x48A70D
        break;
    case COMMAND_GET_CLOSEST_OBJECT_OF_TYPE: // 0x45D
        break;
    case COMMAND_PLACE_OBJECT_RELATIVE_TO_OBJECT: // 0x45E
        break;
    case COMMAND_SET_ALL_OCCUPANTS_OF_CAR_LEAVE_CAR: // 0x45F
        break;
    case COMMAND_SET_INTERPOLATION_PARAMETERS: // 0x460
        break;
    case COMMAND_GET_CLOSEST_CAR_NODE_WITH_HEADING_TOWARDS_POINT: // 0x461
        break;
    case COMMAND_GET_CLOSEST_CAR_NODE_WITH_HEADING_AWAY_POINT: // 0x462
        break;
    case COMMAND_GET_DEBUG_CAMERA_POINT_AT: // 0x463
        break;
    case COMMAND_ATTACH_CHAR_TO_CAR: // 0x464
        break;
    case COMMAND_DETACH_CHAR_FROM_CAR: // 0x465
        break;
    case COMMAND_SET_CAR_STAY_IN_FAST_LANE: // 0x466
        break;
    case COMMAND_CLEAR_CHAR_LAST_WEAPON_DAMAGE: // 0x467
        break;
    case COMMAND_CLEAR_CAR_LAST_WEAPON_DAMAGE: // 0x468
        break;
    case COMMAND_GET_RANDOM_COP_IN_AREA: // 0x469
        break;
    case COMMAND_GET_RANDOM_COP_IN_ZONE: // 0x46A
        break;
    case COMMAND_SET_CHAR_OBJ_FLEE_CAR: // 0x46B
        break;
    case COMMAND_GET_DRIVER_OF_CAR: // 0x46C
        break;
    case COMMAND_GET_NUMBER_OF_FOLLOWERS: // 0x46D
        break;
    case COMMAND_GIVE_REMOTE_CONTROLLED_MODEL_TO_PLAYER: // 0x46E
        break;
    case COMMAND_GET_CURRENT_PLAYER_WEAPON: // 0x46F
        break;
    case COMMAND_GET_CURRENT_CHAR_WEAPON: // 0x470
        break;
    case COMMAND_LOCATE_CHAR_ANY_MEANS_OBJECT_2D: // 0x471
        break;
    case COMMAND_LOCATE_CHAR_ON_FOOT_OBJECT_2D: // 0x472
        break;
    case COMMAND_LOCATE_CHAR_IN_CAR_OBJECT_2D: // 0x473
        break;
    case COMMAND_LOCATE_CHAR_ANY_MEANS_OBJECT_3D: // 0x474
        break;
    case COMMAND_LOCATE_CHAR_ON_FOOT_OBJECT_3D: // 0x475
        break;
    case COMMAND_LOCATE_CHAR_IN_CAR_OBJECT_3D: // 0x476
        break;
    case COMMAND_SET_CAR_TEMP_ACTION: // 0x477
        break;
    case COMMAND_SET_CAR_HANDBRAKE_TURN_RIGHT: // 0x478
        break;
    case COMMAND_SET_CAR_HANDBRAKE_STOP: // 0x479
        break;
    case COMMAND_IS_CHAR_ON_ANY_BIKE: // 0x47A
        break;
    case COMMAND_LOCATE_SNIPER_BULLET_2D: // 0x47B
        break;
    case COMMAND_LOCATE_SNIPER_BULLET_3D: // 0x47C
        break;
    case COMMAND_GET_NUMBER_OF_SEATS_IN_MODEL: // 0x47D
        break;
    case COMMAND_IS_PLAYER_ON_ANY_BIKE: // 0x47E
        break;
    case COMMAND_IS_CHAR_LYING_DOWN: // 0x47F
        break;
    case COMMAND_CAN_CHAR_SEE_DEAD_CHAR: // 0x480
        break;
    case COMMAND_SET_ENTER_CAR_RANGE_MULTIPLIER: // 0x481
        break;
    case COMMAND_SET_THREAT_REACTION_RANGE_MULTIPLIER: // 0x482
        break;
    case COMMAND_SET_CHAR_CEASE_ATTACK_TIMER: // 0x483
        break;
    case COMMAND_GET_REMOTE_CONTROLLED_CAR: // 0x484
        break;
    case COMMAND_IS_PC_VERSION: // 0x485
        break;
    case COMMAND_REPLAY: // 0x486
        break;
    case COMMAND_IS_REPLAY_PLAYING: // 0x487
        break;
    case COMMAND_IS_MODEL_AVAILABLE: // 0x488
        break;
    case COMMAND_SHUT_CHAR_UP: // 0x489
        break;
    case COMMAND_SET_ENABLE_RC_DETONATE: // 0x48A
        break;
    case COMMAND_SET_CAR_RANDOM_ROUTE_SEED: // 0x48B
        break;
    case COMMAND_IS_ANY_PICKUP_AT_COORDS: // 0x48C
        break;
    case COMMAND_GET_FIRST_PICKUP_COORDS: // 0x48D
        break;
    case COMMAND_GET_NEXT_PICKUP_COORDS: // 0x48E
        break;
    case COMMAND_REMOVE_ALL_CHAR_WEAPONS: // 0x48F
        break;
    case COMMAND_HAS_PLAYER_GOT_WEAPON: // 0x490
        break;
    case COMMAND_HAS_CHAR_GOT_WEAPON: // 0x491
        break;
    case COMMAND_IS_PLAYER_FACING_CHAR: // 0x492
        break;
    case COMMAND_SET_TANK_DETONATE_CARS: // 0x493
        break;
    case COMMAND_GET_POSITION_OF_ANALOGUE_STICKS: // 0x494
        break;
    case COMMAND_IS_CAR_ON_FIRE: // 0x495
        break;
    case COMMAND_IS_CAR_TYRE_BURST: // 0x496
        break;
    case COMMAND_SET_CAR_DRIVE_STRAIGHT_AHEAD: // 0x497
        break;
    case COMMAND_SET_CAR_WAIT: // 0x498
        break;
    case COMMAND_IS_PLAYER_STANDING_ON_A_VEHICLE: // 0x499
        break;
    case COMMAND_IS_PLAYER_FOOT_DOWN: // 0x49A
        break;
    case COMMAND_IS_CHAR_FOOT_DOWN: // 0x49B
        break;
    case COMMAND_INITIALISE_OBJECT_PATH: // 0x49C
        break;
    case COMMAND_START_OBJECT_ON_PATH: // 0x49D
        break;
    case COMMAND_SET_OBJECT_PATH_SPEED: // 0x49E
        break;
    case COMMAND_SET_OBJECT_PATH_POSITION: // 0x49F
        break;
    case COMMAND_GET_OBJECT_DISTANCE_ALONG_PATH: // 0x4A0
        break;
    case COMMAND_CLEAR_OBJECT_PATH: // 0x4A1
        break;
    case COMMAND_HELI_GOTO_COORDS: // 0x4A2
        break;
    case COMMAND_IS_INT_VAR_EQUAL_TO_CONSTANT: // 0x4A3
        break;
    case COMMAND_IS_INT_LVAR_EQUAL_TO_CONSTANT: // 0x4A4
        break;
    case COMMAND_GET_DEAD_CHAR_PICKUP_COORDS: // 0x4A5
        break;
    case COMMAND_CREATE_PROTECTION_PICKUP: // 0x4A6
        break;
    case COMMAND_IS_CHAR_IN_ANY_BOAT: // 0x4A7
        break;
    case COMMAND_IS_PLAYER_IN_ANY_BOAT: // 0x4A8
        break;
    case COMMAND_IS_CHAR_IN_ANY_HELI: // 0x4A9
        break;
    case COMMAND_IS_PLAYER_IN_ANY_HELI: // 0x4AA
        break;
    case COMMAND_IS_CHAR_IN_ANY_PLANE: // 0x4AB
        break;
    case COMMAND_IS_PLAYER_IN_ANY_PLANE: // 0x4AC
        break;
    case COMMAND_IS_CHAR_IN_WATER: // 0x4AD
        break;
    case COMMAND_SET_VAR_INT_TO_CONSTANT: // 0x4AE
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        var->iParam = ScriptParams[0].iParam;
        return OR_CONTINUE;
    }
    case COMMAND_SET_LVAR_INT_TO_CONSTANT: // 0x4AF
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        var->iParam = ScriptParams[0].iParam;
        return OR_CONTINUE;
    }
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
