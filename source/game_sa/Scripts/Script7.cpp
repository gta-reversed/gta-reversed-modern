#include "StdInc.h"

#include "RunningScript.h"
#include "FireManager.h"

// 0x47FA30
OpcodeResult CRunningScript::ProcessCommands700To799(int32 commandId) {
    switch (commandId) {
    case COMMAND_SET_SWAT_REQUIRED: // 0x2BC
        break;
    case COMMAND_SET_FBI_REQUIRED: // 0x2BD
        break;
    case COMMAND_SET_ARMY_REQUIRED: // 0x2BE
        break;
    case COMMAND_IS_CAR_IN_WATER: // 0x2BF
        break;
    case COMMAND_GET_CLOSEST_CHAR_NODE: // 0x2C0
        break;
    case COMMAND_GET_CLOSEST_CAR_NODE: // 0x2C1
        break;
    case COMMAND_CAR_GOTO_COORDINATES_ACCURATE: // 0x2C2
        break;
    case COMMAND_START_PACMAN_RACE: // 0x2C3
        break;
    case COMMAND_START_PACMAN_RECORD: // 0x2C4
        break;
    case COMMAND_GET_NUMBER_OF_POWER_PILLS_EATEN: // 0x2C5
        break;
    case COMMAND_CLEAR_PACMAN: // 0x2C6
        break;
    case COMMAND_START_PACMAN_SCRAMBLE: // 0x2C7
        break;
    case COMMAND_GET_NUMBER_OF_POWER_PILLS_CARRIED: // 0x2C8
        break;
    case COMMAND_CLEAR_NUMBER_OF_POWER_PILLS_CARRIED: // 0x2C9
        break;
    case COMMAND_IS_CAR_ON_SCREEN: // 0x2CA
        break;
    case COMMAND_IS_CHAR_ON_SCREEN: // 0x2CB
        break;
    case COMMAND_IS_OBJECT_ON_SCREEN: // 0x2CC
        break;
    case COMMAND_GOSUB_FILE: // 0x2CD
        break;
    case COMMAND_GET_GROUND_Z_FOR_3D_COORD: // 0x2CE
        break;
    case COMMAND_START_SCRIPT_FIRE: // 0x2CF
    {
        CollectParameters(5);
        CVector pos = CTheScripts::ReadCVectorFromScript(0);
        if (pos.z <= MAP_Z_LOW_LIMIT)
            pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);

        ScriptParams[0].iParam = gFireManager.StartScriptFire(pos, nullptr, 0.8f, 1, ScriptParams[3].iParam, ScriptParams[4].iParam);
        StoreParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_IS_SCRIPT_FIRE_EXTINGUISHED: // 0x2D0
        break;
    case COMMAND_REMOVE_SCRIPT_FIRE: // 0x2D1
        break;
    case COMMAND_SET_COMEDY_CONTROLS: // 0x2D2
        break;
    case COMMAND_BOAT_GOTO_COORDS: // 0x2D3
        break;
    case COMMAND_BOAT_STOP: // 0x2D4
        break;
    case COMMAND_IS_PLAYER_SHOOTING_IN_AREA: // 0x2D5
        break;
    case COMMAND_IS_CHAR_SHOOTING_IN_AREA: // 0x2D6
        break;
    case COMMAND_IS_CURRENT_PLAYER_WEAPON: // 0x2D7
        break;
    case COMMAND_IS_CURRENT_CHAR_WEAPON: // 0x2D8
        break;
    case COMMAND_CLEAR_NUMBER_OF_POWER_PILLS_EATEN: // 0x2D9
        break;
    case COMMAND_ADD_POWER_PILL: // 0x2DA
        break;
    case COMMAND_SET_BOAT_CRUISE_SPEED: // 0x2DB
        break;
    case COMMAND_GET_RANDOM_CHAR_IN_AREA: // 0x2DC
        break;
    case COMMAND_GET_RANDOM_CHAR_IN_ZONE: // 0x2DD
        break;
    case COMMAND_IS_PLAYER_IN_TAXI: // 0x2DE
        break;
    case COMMAND_IS_PLAYER_SHOOTING: // 0x2DF
        break;
    case COMMAND_IS_CHAR_SHOOTING: // 0x2E0
        break;
    case COMMAND_CREATE_MONEY_PICKUP: // 0x2E1
        break;
    case COMMAND_SET_CHAR_ACCURACY: // 0x2E2
        break;
    case COMMAND_GET_CAR_SPEED: // 0x2E3
        break;
    case COMMAND_LOAD_CUTSCENE: // 0x2E4
        break;
    case COMMAND_CREATE_CUTSCENE_OBJECT: // 0x2E5
        break;
    case COMMAND_SET_CUTSCENE_ANIM: // 0x2E6
        break;
    case COMMAND_START_CUTSCENE: // 0x2E7
        break;
    case COMMAND_GET_CUTSCENE_TIME: // 0x2E8
        break;
    case COMMAND_HAS_CUTSCENE_FINISHED: // 0x2E9
        break;
    case COMMAND_CLEAR_CUTSCENE: // 0x2EA
        break;
    case COMMAND_RESTORE_CAMERA_JUMPCUT: // 0x2EB
        break;
    case COMMAND_CREATE_COLLECTABLE1: // 0x2EC
        break;
    case COMMAND_SET_COLLECTABLE1_TOTAL: // 0x2ED
        break;
    case COMMAND_IS_PROJECTILE_IN_AREA: // 0x2EE
        break;
    case COMMAND_DESTROY_PROJECTILES_IN_AREA: // 0x2EF
        break;
    case COMMAND_DROP_MINE: // 0x2F0
        break;
    case COMMAND_DROP_NAUTICAL_MINE: // 0x2F1
        break;
    case COMMAND_IS_CHAR_MODEL: // 0x2F2
        break;
    case COMMAND_LOAD_SPECIAL_MODEL: // 0x2F3
        break;
    case COMMAND_CREATE_CUTSCENE_HEAD: // 0x2F4
        break;
    case COMMAND_SET_CUTSCENE_HEAD_ANIM: // 0x2F5
        break;
    case COMMAND_SIN: // 0x2F6
        break;
    case COMMAND_COS: // 0x2F7
        break;
    case COMMAND_GET_CAR_FORWARD_X: // 0x2F8
        break;
    case COMMAND_GET_CAR_FORWARD_Y: // 0x2F9
        break;
    case COMMAND_CHANGE_GARAGE_TYPE: // 0x2FA
        break;
    case COMMAND_ACTIVATE_CRUSHER_CRANE: // 0x2FB
        break;
    case COMMAND_PRINT_WITH_2_NUMBERS: // 0x2FC
        break;
    case COMMAND_PRINT_WITH_2_NUMBERS_NOW: // 0x2FD
        break;
    case COMMAND_PRINT_WITH_2_NUMBERS_SOON: // 0x2FE
        break;
    case COMMAND_PRINT_WITH_3_NUMBERS: // 0x2FF
        break;
    case COMMAND_PRINT_WITH_3_NUMBERS_NOW: // 0x300
        break;
    case COMMAND_PRINT_WITH_3_NUMBERS_SOON: // 0x301
        break;
    case COMMAND_PRINT_WITH_4_NUMBERS: // 0x302
        break;
    case COMMAND_PRINT_WITH_4_NUMBERS_NOW: // 0x303
        break;
    case COMMAND_PRINT_WITH_4_NUMBERS_SOON: // 0x304
        break;
    case COMMAND_PRINT_WITH_5_NUMBERS: // 0x305
        break;
    case COMMAND_PRINT_WITH_5_NUMBERS_NOW: // 0x306
        break;
    case COMMAND_PRINT_WITH_5_NUMBERS_SOON: // 0x307
        break;
    case COMMAND_PRINT_WITH_6_NUMBERS: // 0x308
        break;
    case COMMAND_PRINT_WITH_6_NUMBERS_NOW: // 0x309
        break;
    case COMMAND_PRINT_WITH_6_NUMBERS_SOON: // 0x30A
        break;
    case COMMAND_SET_CHAR_OBJ_FOLLOW_CHAR_IN_FORMATION: // 0x30B
        break;
    case COMMAND_PLAYER_MADE_PROGRESS: // 0x30C
        break;
    case COMMAND_SET_PROGRESS_TOTAL: // 0x30D
        break;
    case COMMAND_REGISTER_JUMP_HEIGHT: // 0x30F | NOTSA
        break;
    case COMMAND_REGISTER_JUMP_FLIPS: // 0x310 | NOTSA
        break;
    case COMMAND_REGISTER_JUMP_SPINS: // 0x311 | NOTSA
        break;
    case COMMAND_REGISTER_JUMP_STUNT: // 0x312 | NOTSA
        break;
    case COMMAND_REGISTER_UNIQUE_JUMP_FOUND: // 0x313 | NOTSA
        break;
    case COMMAND_SET_UNIQUE_JUMPS_TOTAL: // 0x314 | NOTSA
        break;
    case COMMAND_REGISTER_PASSENGER_DROPPED_OFF_TAXI: // 0x315 | NOTSA
        break;
    case COMMAND_REGISTER_MONEY_MADE_TAXI: // 0x316 | NOTSA
        break;
    case COMMAND_REGISTER_MISSION_GIVEN: // 0x317
        break;
    case COMMAND_REGISTER_MISSION_PASSED: // 0x318
        break;
    case COMMAND_SET_CHAR_RUNNING: // 0x319
        break;
    case COMMAND_REMOVE_ALL_SCRIPT_FIRES: // 0x31A
        break;
    case COMMAND_IS_FIRST_CAR_COLOUR: // 0x31B
        break;
    case COMMAND_IS_SECOND_CAR_COLOUR: // 0x31C
        break;
    case COMMAND_HAS_CHAR_BEEN_DAMAGED_BY_WEAPON: // 0x31D
        break;
    case COMMAND_HAS_CAR_BEEN_DAMAGED_BY_WEAPON: // 0x31E
        break;
    case COMMAND_IS_CHAR_IN_CHARS_GROUP: // 0x31F
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
