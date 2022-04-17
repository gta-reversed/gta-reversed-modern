#include "StdInc.h"
#include "RunningScript.h"

// 0x48CDD0
OpcodeResult CRunningScript::ProcessCommands1300To1399(int32 commandId) {
    switch (commandId) {
    case COMMAND_SET_CHAR_CAN_BE_DAMAGED_BY_MEMBERS_OF_GANG: // 0x514
        break;
    case COMMAND_LOAD_AND_LAUNCH_MISSION_EXCLUSIVE: // 0x515
        break;
    case COMMAND_IS_MISSION_AUDIO_PLAYING: // 0x516
        break;
    case COMMAND_CREATE_LOCKED_PROPERTY_PICKUP: // 0x517
        break;
    case COMMAND_CREATE_FORSALE_PROPERTY_PICKUP: // 0x518
        break;
    case COMMAND_FREEZE_CAR_POSITION: // 0x519
        break;
    case COMMAND_HAS_CHAR_BEEN_DAMAGED_BY_CHAR: // 0x51A
        break;
    case COMMAND_HAS_CHAR_BEEN_DAMAGED_BY_CAR: // 0x51B
        break;
    case COMMAND_HAS_CAR_BEEN_DAMAGED_BY_CHAR: // 0x51C
        break;
    case COMMAND_HAS_CAR_BEEN_DAMAGED_BY_CAR: // 0x51D
        break;
    case COMMAND_GET_RADIO_CHANNEL: // 0x51E
        break;
    case COMMAND_DISPLAY_TEXT_WITH_3_NUMBERS: // 0x51F
        break;
    case COMMAND_IS_CAR_DROWNING_IN_WATER: // 0x520
        break;
    case COMMAND_IS_CHAR_DROWNING_IN_WATER: // 0x521
        break;
    case COMMAND_DISABLE_CUTSCENE_SHADOWS: // 0x522
        break;
    case COMMAND_HAS_GLASS_BEEN_SHATTERED_NEARBY: // 0x523
        break;
    case COMMAND_ATTACH_CUTSCENE_OBJECT_TO_BONE: // 0x524
        break;
    case COMMAND_ATTACH_CUTSCENE_OBJECT_TO_COMPONENT: // 0x525
        break;
    case COMMAND_SET_CHAR_STAY_IN_CAR_WHEN_JACKED: // 0x526
        break;
    case COMMAND_IS_MISSION_AUDIO_LOADING: // 0x527
        break;
    case COMMAND_ADD_MONEY_SPENT_ON_WEAPONS: // 0x528
        break;
    case COMMAND_ADD_MONEY_SPENT_ON_PROPERTY: // 0x529
        break;
    case COMMAND_ADD_MONEY_SPENT_ON_AUTO_PAINTING: // 0x52A
        break;
    case COMMAND_SET_CHAR_ANSWERING_MOBILE: // 0x52B
        break;
    case COMMAND_SET_PLAYER_DRUNKENNESS: // 0x52C
        break;
    case COMMAND_GET_PLAYER_DRUNKENNESS: // 0x52D
        break;
    case COMMAND_SET_PLAYER_DRUG_LEVEL: // 0x52E
        break;
    case COMMAND_GET_PLAYER_DRUG_LEVEL: // 0x52F
        break;
    case COMMAND_ADD_LOAN_SHARK_VISITS: // 0x530
        break;
    case COMMAND_ADD_STORES_KNOCKED_OFF: // 0x531
        break;
    case COMMAND_ADD_MOVIE_STUNTS: // 0x532
        break;
    case COMMAND_ADD_NUMBER_OF_ASSASSINATIONS: // 0x533
        break;
    case COMMAND_ADD_PIZZAS_DELIVERED: // 0x534
        break;
    case COMMAND_ADD_GARBAGE_PICKUPS: // 0x535
        break;
    case COMMAND_ADD_ICE_CREAMS_SOLD: // 0x536
        break;
    case COMMAND_SET_TOP_SHOOTING_RANGE_SCORE: // 0x537
        break;
    case COMMAND_ADD_SHOOTING_RANGE_RANK: // 0x538
        break;
    case COMMAND_ADD_MONEY_SPENT_ON_GAMBLING: // 0x539
        break;
    case COMMAND_ADD_MONEY_WON_ON_GAMBLING: // 0x53A
        break;
    case COMMAND_SET_LARGEST_GAMBLING_WIN: // 0x53B
        break;
    case COMMAND_SET_CHAR_IN_PLAYERS_GROUP_CAN_FIGHT: // 0x53C
        break;
    case COMMAND_CLEAR_CHAR_WAIT_STATE: // 0x53D
        break;
    case COMMAND_GET_RANDOM_CAR_OF_TYPE_IN_AREA_NO_SAVE: // 0x53E
        break;
    case COMMAND_SET_CAN_BURST_CAR_TYRES: // 0x53F
        break;
    case COMMAND_SET_PLAYER_AUTO_AIM: // 0x540
        break;
    case COMMAND_FIRE_HUNTER_GUN: // 0x541
        break;
    case COMMAND_SET_PROPERTY_AS_OWNED: // 0x542
        break;
    case COMMAND_ADD_BLOOD_RING_KILLS: // 0x543
        break;
    case COMMAND_SET_LONGEST_TIME_IN_BLOOD_RING: // 0x544
        break;
    case COMMAND_REMOVE_EVERYTHING_FOR_HUGE_CUTSCENE: // 0x545
        break;
    case COMMAND_IS_PLAYER_TOUCHING_VEHICLE: // 0x546
        break;
    case COMMAND_IS_CHAR_TOUCHING_VEHICLE: // 0x547
        break;
    case COMMAND_CHECK_FOR_PED_MODEL_AROUND_PLAYER: // 0x548
        break;
    case COMMAND_CLEAR_CHAR_FOLLOW_PATH: // 0x549
        break;
    case COMMAND_SET_CHAR_CAN_BE_SHOT_IN_VEHICLE: // 0x54A
        break;
    case COMMAND_ATTACH_CUTSCENE_OBJECT_TO_VEHICLE: // 0x54B
        break;
    case COMMAND_LOAD_MISSION_TEXT: // 0x54C
        break;
    case COMMAND_SET_TONIGHTS_EVENT: // 0x54D
        break;
    case COMMAND_CLEAR_CHAR_LAST_DAMAGE_ENTITY: // 0x54E
        break;
    case COMMAND_CLEAR_CAR_LAST_DAMAGE_ENTITY: // 0x54F
        break;
    case COMMAND_FREEZE_OBJECT_POSITION: // 0x550
        break;
    case COMMAND_SET_PLAYER_HAS_MET_DEBBIE_HARRY: // 0x551
        break;
    case COMMAND_SET_RIOT_INTENSITY: // 0x552
        break;
    case COMMAND_IS_CAR_IN_ANGLED_AREA_2D: // 0x553
        break;
    case COMMAND_IS_CAR_IN_ANGLED_AREA_3D: // 0x554
        break;
    case COMMAND_REMOVE_WEAPON_FROM_CHAR: // 0x555
        break;
    case COMMAND_SET_UP_TAXI_SHORTCUT: // 0x556
        break;
    case COMMAND_CLEAR_TAXI_SHORTCUT: // 0x557
        break;
    case COMMAND_SET_CHAR_OBJ_GOTO_CAR_ON_FOOT: // 0x558
        break;
    case COMMAND_GET_CLOSEST_WATER_NODE: // 0x559
        break;
    case COMMAND_ADD_PORN_LEAFLET_TO_RUBBISH: // 0x55A
        break;
    case COMMAND_CREATE_CLOTHES_PICKUP: // 0x55B
        break;
    case COMMAND_CHANGE_BLIP_THRESHOLD: // 0x55C
        break;
    case COMMAND_MAKE_PLAYER_FIRE_PROOF: // 0x55D
        break;
    case COMMAND_INCREASE_PLAYER_MAX_HEALTH: // 0x55E
        break;
    case COMMAND_INCREASE_PLAYER_MAX_ARMOUR: // 0x55F
        break;
    case COMMAND_CREATE_RANDOM_CHAR_AS_DRIVER: // 0x560
        break;
    case COMMAND_CREATE_RANDOM_CHAR_AS_PASSENGER: // 0x561
        break;
    case COMMAND_SET_CHAR_IGNORE_THREATS_BEHIND_OBJECTS: // 0x562
        break;
    case COMMAND_ENSURE_PLAYER_HAS_DRIVE_BY_WEAPON: // 0x563
        break;
    case COMMAND_MAKE_HELI_COME_CRASHING_DOWN: // 0x564
        break;
    case COMMAND_ADD_EXPLOSION_NO_SOUND: // 0x565
        break;
    case COMMAND_SET_OBJECT_AREA_VISIBLE: // 0x566
        break;
    case COMMAND_WAS_VEHICLE_EVER_POLICE: // 0x567
        break;
    case COMMAND_SET_CHAR_NEVER_TARGETTED: // 0x568
        break;
    case COMMAND_LOAD_UNCOMPRESSED_ANIM: // 0x569
        break;
    case COMMAND_WAS_CUTSCENE_SKIPPED: // 0x56A
        break;
    case COMMAND_SET_CHAR_CROUCH_WHEN_THREATENED: // 0x56B
        break;
    case COMMAND_IS_CHAR_IN_ANY_POLICE_VEHICLE: // 0x56C
        break;
    case COMMAND_DOES_CHAR_EXIST: // 0x56D
        break;
    case COMMAND_DOES_VEHICLE_EXIST: // 0x56E
        break;
    case COMMAND_ADD_SHORT_RANGE_BLIP_FOR_CONTACT_POINT: // 0x56F
        break;
    case COMMAND_ADD_SHORT_RANGE_SPRITE_BLIP_FOR_CONTACT_POINT: // 0x570
        break;
    case COMMAND_IS_CHAR_STUCK: // 0x571
        break;
    case COMMAND_SET_ALL_TAXIS_HAVE_NITRO: // 0x572
        CollectParameters(1);
        if (ScriptParams[0].iParam) {
            CCheat::EnableLegitimateCheat(CHEAT_ALL_TAXIS_NITRO);
        } else {
            CCheat::Disable(CHEAT_ALL_TAXIS_NITRO);
        }
        return OR_CONTINUE;
    case COMMAND_SET_CHAR_STOP_SHOOT_DONT_SEEK_ENTITY: // 0x573
        break;
    case COMMAND_FREEZE_CAR_POSITION_AND_DONT_LOAD_COLLISION: // 0x574
        break;
    case COMMAND_FREEZE_CHAR_POSITION_AND_DONT_LOAD_COLLISION: // 0x575
        break;
    case COMMAND_FREEZE_OBJECT_POSITION_AND_DONT_LOAD_COLLISION: // 0x576
        break;
    case COMMAND_SET_FADE_AND_JUMPCUT_AFTER_RC_EXPLOSION: // 0x577
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
