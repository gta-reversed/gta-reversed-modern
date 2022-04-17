#include "StdInc.h"
#include "RunningScript.h"

// 0x481300
OpcodeResult CRunningScript::ProcessCommands800To899(int32 commandId) {
    switch (commandId) {
    case COMMAND_IS_CHAR_IN_PLAYERS_GROUP: // 0x320
        break;
    case COMMAND_EXPLODE_CHAR_HEAD: // 0x321
        break;
    case COMMAND_EXPLODE_PLAYER_HEAD: // 0x322
        break;
    case COMMAND_ANCHOR_BOAT: // 0x323
        break;
    case COMMAND_SET_ZONE_GROUP: // 0x324
        break;
    case COMMAND_START_CAR_FIRE: // 0x325
        break;
    case COMMAND_START_CHAR_FIRE: // 0x326
        break;
    case COMMAND_GET_RANDOM_CAR_OF_TYPE_IN_AREA: // 0x327
        break;
    case COMMAND_GET_RANDOM_CAR_OF_TYPE_IN_ZONE: // 0x328
        break;
    case COMMAND_HAS_RESPRAY_HAPPENED: // 0x329
        break;
    case COMMAND_SET_CAMERA_ZOOM: // 0x32A
        break;
    case COMMAND_CREATE_PICKUP_WITH_AMMO: // 0x32B
        break;
    case COMMAND_SET_CAR_RAM_CAR: // 0x32C
        break;
    case COMMAND_SET_CAR_BLOCK_CAR: // 0x32D
        break;
    case COMMAND_SET_CHAR_OBJ_CATCH_TRAIN: // 0x32E
        break;
    case COMMAND_SET_COLL_OBJ_CATCH_TRAIN: // 0x32F
        break;
    case COMMAND_SET_PLAYER_NEVER_GETS_TIRED: // 0x330
        break;
    case COMMAND_SET_PLAYER_FAST_RELOAD: // 0x331
        break;
    case COMMAND_SET_CHAR_BLEEDING: // 0x332
        break;
    case COMMAND_SET_CAR_FUNNY_SUSPENSION: // 0x333
        break;
    case COMMAND_SET_CAR_BIG_WHEELS: // 0x334
        break;
    case COMMAND_SET_FREE_RESPRAYS: // 0x335
        break;
    case COMMAND_SET_PLAYER_VISIBLE: // 0x336
        break;
    case COMMAND_SET_CHAR_VISIBLE: // 0x337
        break;
    case COMMAND_SET_CAR_VISIBLE: // 0x338
        break;
    case COMMAND_IS_AREA_OCCUPIED: // 0x339
        break;
    case COMMAND_START_DRUG_RUN: // 0x33A
        break;
    case COMMAND_HAS_DRUG_RUN_BEEN_COMPLETED: // 0x33B
        break;
    case COMMAND_HAS_DRUG_PLANE_BEEN_SHOT_DOWN: // 0x33C
        break;
    case COMMAND_SAVE_PLAYER_FROM_FIRES: // 0x33D
        break;
    case COMMAND_DISPLAY_TEXT: // 0x33E
        break;
    case COMMAND_SET_TEXT_SCALE: // 0x33F
        break;
    case COMMAND_SET_TEXT_COLOUR: // 0x340
        break;
    case COMMAND_SET_TEXT_JUSTIFY: // 0x341
        break;
    case COMMAND_SET_TEXT_CENTRE: // 0x342
        break;
    case COMMAND_SET_TEXT_WRAPX: // 0x343
        break;
    case COMMAND_SET_TEXT_CENTRE_SIZE: // 0x344
        break;
    case COMMAND_SET_TEXT_BACKGROUND: // 0x345
        break;
    case COMMAND_SET_TEXT_BACKGROUND_COLOUR: // 0x346
        break;
    case COMMAND_SET_TEXT_BACKGROUND_ONLY_TEXT: // 0x347
        break;
    case COMMAND_SET_TEXT_PROPORTIONAL: // 0x348
        break;
    case COMMAND_SET_TEXT_FONT: // 0x349
        break;
    case COMMAND_INDUSTRIAL_PASSED: // 0x34A
        break;
    case COMMAND_COMMERCIAL_PASSED: // 0x34B
        break;
    case COMMAND_SUBURBAN_PASSED: // 0x34C
        break;
    case COMMAND_ROTATE_OBJECT: // 0x34D
        break;
    case COMMAND_SLIDE_OBJECT: // 0x34E
        break;
    case COMMAND_REMOVE_CHAR_ELEGANTLY: // 0x34F
        break;
    case COMMAND_SET_CHAR_STAY_IN_SAME_PLACE: // 0x350
        break;
    case COMMAND_IS_NASTY_GAME: // 0x351
        break;
    case COMMAND_UNDRESS_CHAR: // 0x352
        break;
    case COMMAND_DRESS_CHAR: // 0x353
        break;
    case COMMAND_START_CHASE_SCENE: // 0x354
        break;
    case COMMAND_STOP_CHASE_SCENE: // 0x355
        break;
    case COMMAND_IS_EXPLOSION_IN_AREA: // 0x356
        break;
    case COMMAND_IS_EXPLOSION_IN_ZONE: // 0x357
        break;
    case COMMAND_START_DRUG_DROP_OFF: // 0x358
        break;
    case COMMAND_HAS_DROP_OFF_PLANE_BEEN_SHOT_DOWN: // 0x359
        break;
    case COMMAND_FIND_DROP_OFF_PLANE_COORDINATES: // 0x35A
        break;
    case COMMAND_CREATE_FLOATING_PACKAGE: // 0x35B
        break;
    case COMMAND_PLACE_OBJECT_RELATIVE_TO_CAR: // 0x35C
        break;
    case COMMAND_MAKE_OBJECT_TARGETTABLE: // 0x35D
        break;
    case COMMAND_ADD_ARMOUR_TO_PLAYER: // 0x35E
        break;
    case COMMAND_ADD_ARMOUR_TO_CHAR: // 0x35F
        break;
    case COMMAND_OPEN_GARAGE: // 0x360
        break;
    case COMMAND_CLOSE_GARAGE: // 0x361
        break;
    case COMMAND_WARP_CHAR_FROM_CAR_TO_COORD: // 0x362
        break;
    case COMMAND_SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE: // 0x363
        break;
    case COMMAND_HAS_CHAR_SPOTTED_CHAR: // 0x364
        break;
    case COMMAND_SET_CHAR_OBJ_HAIL_TAXI: // 0x365
        break;
    case COMMAND_HAS_OBJECT_BEEN_DAMAGED: // 0x366
        break;
    case COMMAND_START_KILL_FRENZY_HEADSHOT: // 0x367
        break;
    case COMMAND_ACTIVATE_MILITARY_CRANE: // 0x368
        break;
    case COMMAND_WARP_PLAYER_INTO_CAR: // 0x369
        break;
    case COMMAND_WARP_CHAR_INTO_CAR: // 0x36A
        break;
    case COMMAND_SWITCH_CAR_RADIO: // 0x36B
        break;
    case COMMAND_SET_AUDIO_STREAM: // 0x36C
        break;
    case COMMAND_PRINT_WITH_2_NUMBERS_BIG: // 0x36D
        break;
    case COMMAND_PRINT_WITH_3_NUMBERS_BIG: // 0x36E
        break;
    case COMMAND_PRINT_WITH_4_NUMBERS_BIG: // 0x36F
        break;
    case COMMAND_PRINT_WITH_5_NUMBERS_BIG: // 0x370
        break;
    case COMMAND_PRINT_WITH_6_NUMBERS_BIG: // 0x371
        break;
    case COMMAND_SET_CHAR_WAIT_STATE: // 0x372
        break;
    case COMMAND_SET_CAMERA_BEHIND_PLAYER: // 0x373
        break;
    case COMMAND_SET_MOTION_BLUR: // 0x374
        break;
    case COMMAND_PRINT_STRING_IN_STRING: // 0x375
        break;
    case COMMAND_CREATE_RANDOM_CHAR: // 0x376
        break;
    case COMMAND_SET_CHAR_OBJ_STEAL_ANY_CAR: // 0x377
        break;
    case COMMAND_SET_2_REPEATED_PHONE_MESSAGES: // 0x378
        break;
    case COMMAND_SET_2_PHONE_MESSAGES: // 0x379
        break;
    case COMMAND_SET_3_REPEATED_PHONE_MESSAGES: // 0x37A
        break;
    case COMMAND_SET_3_PHONE_MESSAGES: // 0x37B
        break;
    case COMMAND_SET_4_REPEATED_PHONE_MESSAGES: // 0x37C
        break;
    case COMMAND_SET_4_PHONE_MESSAGES: // 0x37D
        break;
    case COMMAND_IS_SNIPER_BULLET_IN_AREA: // 0x37E
        break;
    case COMMAND_GIVE_PLAYER_DETONATOR: // 0x37F
        break;
    case COMMAND_SET_COLL_OBJ_STEAL_ANY_CAR: // 0x380
        break;
    case COMMAND_SET_OBJECT_VELOCITY: // 0x381
        break;
    case COMMAND_SET_OBJECT_COLLISION: // 0x382
        break;
    case COMMAND_IS_ICECREAM_JINGLE_ON: // 0x383
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
