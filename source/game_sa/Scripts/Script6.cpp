#include "StdInc.h"
#include "RunningScript.h"

// 0x47F370
OpcodeResult CRunningScript::ProcessCommands600To699(int32 commandId) {
    switch (commandId) {
    case COMMAND_SET_COLL_OBJ_WAIT_ON_FOOT: // 0x258
        break;
    case COMMAND_SET_COLL_OBJ_FLEE_ON_FOOT_TILL_SAFE: // 0x259
        break;
    case COMMAND_SET_COLL_OBJ_GUARD_SPOT: // 0x25A
        break;
    case COMMAND_SET_COLL_OBJ_GUARD_AREA: // 0x25B
        break;
    case COMMAND_SET_COLL_OBJ_WAIT_IN_CAR: // 0x25C
        break;
    case COMMAND_SET_COLL_OBJ_KILL_CHAR_ON_FOOT: // 0x25D
        break;
    case COMMAND_SET_COLL_OBJ_KILL_PLAYER_ON_FOOT: // 0x25E
        break;
    case COMMAND_SET_COLL_OBJ_KILL_CHAR_ANY_MEANS: // 0x25F
        break;
    case COMMAND_SET_COLL_OBJ_KILL_PLAYER_ANY_MEANS: // 0x260
        break;
    case COMMAND_SET_COLL_OBJ_FLEE_CHAR_ON_FOOT_TILL_SAFE: // 0x261
        break;
    case COMMAND_SET_COLL_OBJ_FLEE_PLAYER_ON_FOOT_TILL_SAFE: // 0x262
        break;
    case COMMAND_SET_COLL_OBJ_FLEE_CHAR_ON_FOOT_ALWAYS: // 0x263
        break;
    case COMMAND_SET_COLL_OBJ_FLEE_PLAYER_ON_FOOT_ALWAYS: // 0x264
        break;
    case COMMAND_SET_COLL_OBJ_GOTO_CHAR_ON_FOOT: // 0x265
        break;
    case COMMAND_SET_COLL_OBJ_GOTO_PLAYER_ON_FOOT: // 0x266
        break;
    case COMMAND_SET_COLL_OBJ_LEAVE_CAR: // 0x267
        break;
    case COMMAND_SET_COLL_OBJ_ENTER_CAR_AS_PASSENGER: // 0x268
        break;
    case COMMAND_SET_COLL_OBJ_ENTER_CAR_AS_DRIVER: // 0x269
        break;
    case COMMAND_SET_COLL_OBJ_FOLLOW_CAR_IN_CAR: // 0x26A
        break;
    case COMMAND_SET_COLL_OBJ_FIRE_AT_OBJECT_FROM_VEHICLE: // 0x26B
        break;
    case COMMAND_SET_COLL_OBJ_DESTROY_OBJECT: // 0x26C
        break;
    case COMMAND_SET_COLL_OBJ_DESTROY_CAR: // 0x26D
        break;
    case COMMAND_SET_COLL_OBJ_GOTO_AREA_ON_FOOT: // 0x26E
        break;
    case COMMAND_SET_COLL_OBJ_GOTO_AREA_IN_CAR: // 0x26F
        break;
    case COMMAND_SET_COLL_OBJ_FOLLOW_CAR_ON_FOOT_WITH_OFFSET: // 0x270
        break;
    case COMMAND_SET_COLL_OBJ_GUARD_ATTACK: // 0x271
        break;
    case COMMAND_SET_COLL_OBJ_FOLLOW_ROUTE: // 0x272
        break;
    case COMMAND_SET_COLL_OBJ_GOTO_COORD_ON_FOOT: // 0x273
        break;
    case COMMAND_SET_COLL_OBJ_GOTO_COORD_IN_CAR: // 0x274
        break;
    case COMMAND_SET_COLL_OBJ_RUN_TO_AREA: // 0x275
        break;
    case COMMAND_SET_COLL_OBJ_RUN_TO_COORD: // 0x276
        break;
    case COMMAND_ADD_PEDS_IN_AREA_TO_COLL: // 0x277
        break;
    case COMMAND_ADD_PEDS_IN_VEHICLE_TO_COLL: // 0x278
        break;
    case COMMAND_CLEAR_COLL: // 0x279
        break;
    case COMMAND_IS_COLL_IN_CARS: // 0x27A
        break;
    case COMMAND_LOCATE_COLL_ANY_MEANS_2D: // 0x27B
        break;
    case COMMAND_LOCATE_COLL_ON_FOOT_2D: // 0x27C
        break;
    case COMMAND_LOCATE_COLL_IN_CAR_2D: // 0x27D
        break;
    case COMMAND_LOCATE_STOPPED_COLL_ANY_MEANS_2D: // 0x27E
        break;
    case COMMAND_LOCATE_STOPPED_COLL_ON_FOOT_2D: // 0x27F
        break;
    case COMMAND_LOCATE_STOPPED_COLL_IN_CAR_2D: // 0x280
        break;
    case COMMAND_LOCATE_COLL_ANY_MEANS_CHAR_2D: // 0x281
        break;
    case COMMAND_LOCATE_COLL_ON_FOOT_CHAR_2D: // 0x282
        break;
    case COMMAND_LOCATE_COLL_IN_CAR_CHAR_2D: // 0x283
        break;
    case COMMAND_LOCATE_COLL_ANY_MEANS_CAR_2D: // 0x284
        break;
    case COMMAND_LOCATE_COLL_ON_FOOT_CAR_2D: // 0x285
        break;
    case COMMAND_LOCATE_COLL_IN_CAR_CAR_2D: // 0x286
        break;
    case COMMAND_LOCATE_COLL_ANY_MEANS_PLAYER_2D: // 0x287
        break;
    case COMMAND_LOCATE_COLL_ON_FOOT_PLAYER_2D: // 0x288
        break;
    case COMMAND_LOCATE_COLL_IN_CAR_PLAYER_2D: // 0x289
        break;
    case COMMAND_IS_COLL_IN_AREA_2D: // 0x28A
        break;
    case COMMAND_IS_COLL_IN_AREA_ON_FOOT_2D: // 0x28B
        break;
    case COMMAND_IS_COLL_IN_AREA_IN_CAR_2D: // 0x28C
        break;
    case COMMAND_IS_COLL_STOPPED_IN_AREA_2D: // 0x28D
        break;
    case COMMAND_IS_COLL_STOPPED_IN_AREA_ON_FOOT_2D: // 0x28E
        break;
    case COMMAND_IS_COLL_STOPPED_IN_AREA_IN_CAR_2D: // 0x28F
        break;
    case COMMAND_GET_NUMBER_OF_PEDS_IN_COLL: // 0x290
        break;
    case COMMAND_SET_CHAR_HEED_THREATS: // 0x291
        break;
    case COMMAND_SET_PLAYER_HEED_THREATS: // 0x292
        break;
    case COMMAND_GET_CONTROLLER_MODE: // 0x293
        break;
    case COMMAND_SET_CAN_RESPRAY_CAR: // 0x294
        break;
    case COMMAND_IS_TAXI: // 0x295
        break;
    case COMMAND_UNLOAD_SPECIAL_CHARACTER: // 0x296
        break;
    case COMMAND_RESET_NUM_OF_MODELS_KILLED_BY_PLAYER: // 0x297
        break;
    case COMMAND_GET_NUM_OF_MODELS_KILLED_BY_PLAYER: // 0x298
        break;
    case COMMAND_ACTIVATE_GARAGE: // 0x299
        break;
    case COMMAND_SWITCH_TAXI_TIMER: // 0x29A
        break;
    case COMMAND_CREATE_OBJECT_NO_OFFSET: // 0x29B
        break;
    case COMMAND_IS_BOAT: // 0x29C
        break;
    case COMMAND_SET_CHAR_OBJ_GOTO_AREA_ANY_MEANS: // 0x29D
        break;
    case COMMAND_SET_COLL_OBJ_GOTO_AREA_ANY_MEANS: // 0x29E
        break;
    case COMMAND_IS_PLAYER_STOPPED: // 0x29F
        break;
    case COMMAND_IS_CHAR_STOPPED: // 0x2A0
        break;
    case COMMAND_MESSAGE_WAIT: // 0x2A1
        break;
    case COMMAND_ADD_PARTICLE_EFFECT: // 0x2A2
        break;
    case COMMAND_SWITCH_WIDESCREEN: // 0x2A3
        break;
    case COMMAND_ADD_SPRITE_BLIP_FOR_CAR: // 0x2A4
        break;
    case COMMAND_ADD_SPRITE_BLIP_FOR_CHAR: // 0x2A5
        break;
    case COMMAND_ADD_SPRITE_BLIP_FOR_OBJECT: // 0x2A6
        break;
    case COMMAND_ADD_SPRITE_BLIP_FOR_CONTACT_POINT: // 0x2A7
        break;
    case COMMAND_ADD_SPRITE_BLIP_FOR_COORD: // 0x2A8
        break;
    case COMMAND_SET_CHAR_ONLY_DAMAGED_BY_PLAYER: // 0x2A9
        break;
    case COMMAND_SET_CAR_ONLY_DAMAGED_BY_PLAYER: // 0x2AA
        break;
    case COMMAND_SET_CHAR_PROOFS: // 0x2AB
    {
        CollectParameters(6);
        auto* ped = GetPedPool()->GetAt(ScriptParams[0].iParam >> 8);
        assert(ped);
        ped->physicalFlags.bBulletProof    = ScriptParams[1].uParam;
        ped->physicalFlags.bFireProof      = ScriptParams[2].uParam;
        ped->physicalFlags.bExplosionProof = ScriptParams[3].uParam;
        ped->physicalFlags.bCollisionProof = ScriptParams[4].uParam;
        ped->physicalFlags.bMeleeProof     = ScriptParams[5].uParam;
        return OR_CONTINUE;
    }
    case COMMAND_SET_CAR_PROOFS: // 0x2AC
    {
        CollectParameters(6);
        auto* vehicle = GetVehiclePool()->GetAt(ScriptParams[0].iParam >> 8);
        assert(vehicle);
        vehicle->physicalFlags.bBulletProof    = ScriptParams[1].uParam;
        vehicle->physicalFlags.bFireProof      = ScriptParams[2].uParam;
        vehicle->physicalFlags.bExplosionProof = ScriptParams[3].uParam;
        vehicle->physicalFlags.bCollisionProof = ScriptParams[4].uParam;
        vehicle->physicalFlags.bMeleeProof     = ScriptParams[5].uParam;
        return OR_CONTINUE;
    }
    case COMMAND_IS_PLAYER_IN_ANGLED_AREA_2D: // 0x2AD
        break;
    case COMMAND_IS_PLAYER_IN_ANGLED_AREA_ON_FOOT_2D: // 0x2AE
        break;
    case COMMAND_IS_PLAYER_IN_ANGLED_AREA_IN_CAR_2D: // 0x2AF
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_2D: // 0x2B0
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_ON_FOOT_2D: // 0x2B1
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_IN_CAR_2D: // 0x2B2
        break;
    case COMMAND_IS_PLAYER_IN_ANGLED_AREA_3D: // 0x2B3
        break;
    case COMMAND_IS_PLAYER_IN_ANGLED_AREA_ON_FOOT_3D: // 0x2B4
        break;
    case COMMAND_IS_PLAYER_IN_ANGLED_AREA_IN_CAR_3D: // 0x2B5
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_3D: // 0x2B6
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_ON_FOOT_3D: // 0x2B7
        break;
    case COMMAND_IS_PLAYER_STOPPED_IN_ANGLED_AREA_IN_CAR_3D: // 0x2B8
        break;
    case COMMAND_DEACTIVATE_GARAGE: // 0x2B9
        break;
    case COMMAND_GET_NUMBER_OF_CARS_COLLECTED_BY_GARAGE: // 0x2BA
        break;
    case COMMAND_HAS_CAR_BEEN_TAKEN_TO_GARAGE: // 0x2BB
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
