#include "StdInc.h"
#include "RunningScript.h"

// 0x47E090
OpcodeResult CRunningScript::ProcessCommands500To599(int32 commandId) {
    switch (commandId) {
    case COMMAND_IS_CAR_UPSIDEDOWN: // 0x1F4
        break;
    case COMMAND_GET_PLAYER_CHAR: // 0x1F5
        break;
    case COMMAND_CANCEL_OVERRIDE_RESTART: // 0x1F6
        break;
    case COMMAND_SET_POLICE_IGNORE_PLAYER: // 0x1F7
        break;
    case COMMAND_ADD_PAGER_MESSAGE_WITH_NUMBER: // 0x1F8
        break;
    case COMMAND_START_KILL_FRENZY: // 0x1F9
        break;
    case COMMAND_READ_KILL_FRENZY_STATUS: // 0x1FA
        break;
    case COMMAND_SQRT: // 0x1FB
        break;
    case COMMAND_LOCATE_PLAYER_ANY_MEANS_CAR_2D: // 0x1FC
        break;
    case COMMAND_LOCATE_PLAYER_ON_FOOT_CAR_2D: // 0x1FD
        break;
    case COMMAND_LOCATE_PLAYER_IN_CAR_CAR_2D: // 0x1FE
        break;
    case COMMAND_LOCATE_PLAYER_ANY_MEANS_CAR_3D: // 0x1FF
        break;
    case COMMAND_LOCATE_PLAYER_ON_FOOT_CAR_3D: // 0x200
        break;
    case COMMAND_LOCATE_PLAYER_IN_CAR_CAR_3D: // 0x201
        break;
    case COMMAND_LOCATE_CHAR_ANY_MEANS_CAR_2D: // 0x202
        break;
    case COMMAND_LOCATE_CHAR_ON_FOOT_CAR_2D: // 0x203
        break;
    case COMMAND_LOCATE_CHAR_IN_CAR_CAR_2D: // 0x204
        break;
    case COMMAND_LOCATE_CHAR_ANY_MEANS_CAR_3D: // 0x205
        break;
    case COMMAND_LOCATE_CHAR_ON_FOOT_CAR_3D: // 0x206
        break;
    case COMMAND_LOCATE_CHAR_IN_CAR_CAR_3D: // 0x207
        break;
    case COMMAND_GENERATE_RANDOM_FLOAT_IN_RANGE: // 0x208
        CollectParameters(2);
        ScriptParams[0].fParam = CGeneral::GetRandomNumberInRange(ScriptParams[0].fParam, ScriptParams[1].fParam);
        StoreParameters(1);
        return OR_CONTINUE;
    case COMMAND_GENERATE_RANDOM_INT_IN_RANGE: // 0x209
        CollectParameters(2);
        ScriptParams[0].fParam = CGeneral::GetRandomNumberInRange(ScriptParams[0].fParam, ScriptParams[1].fParam);
        StoreParameters(1);
        return OR_CONTINUE;
    case COMMAND_LOCK_CAR_DOORS: // 0x20A
        break;
    case COMMAND_EXPLODE_CAR: // 0x20B
        break;
    case COMMAND_ADD_EXPLOSION: // 0x20C
        break;
    case COMMAND_IS_CAR_UPRIGHT: // 0x20D
        break;
    case COMMAND_TURN_CHAR_TO_FACE_CHAR: // 0x20E
        break;
    case COMMAND_TURN_CHAR_TO_FACE_PLAYER: // 0x20F
        break;
    case COMMAND_TURN_PLAYER_TO_FACE_CHAR: // 0x210
        break;
    case COMMAND_SET_CHAR_OBJ_GOTO_COORD_ON_FOOT: // 0x211
        break;
    case COMMAND_SET_CHAR_OBJ_GOTO_COORD_IN_CAR: // 0x212
        break;
    case COMMAND_CREATE_PICKUP: // 0x213
        break;
    case COMMAND_HAS_PICKUP_BEEN_COLLECTED: // 0x214
        break;
    case COMMAND_REMOVE_PICKUP: // 0x215
        break;
    case COMMAND_SET_TAXI_LIGHTS: // 0x216
        break;
    case COMMAND_PRINT_BIG_Q: // 0x217
        break;
    case COMMAND_PRINT_WITH_NUMBER_BIG_Q: // 0x218
        break;
    case COMMAND_SET_GARAGE: // 0x219
        break;
    case COMMAND_SET_GARAGE_WITH_CAR_MODEL: // 0x21A
        break;
    case COMMAND_SET_TARGET_CAR_FOR_MISSION_GARAGE: // 0x21B
        break;
    case COMMAND_IS_CAR_IN_MISSION_GARAGE: // 0x21C
        break;
    case COMMAND_SET_FREE_BOMBS: // 0x21D
        break;
    case COMMAND_SET_POWERPOINT: // 0x21E
        break;
    case COMMAND_SET_ALL_TAXI_LIGHTS: // 0x21F
        break;
    case COMMAND_IS_CAR_ARMED_WITH_ANY_BOMB: // 0x220
        break;
    case COMMAND_APPLY_BRAKES_TO_PLAYERS_CAR: // 0x221
        break;
    case COMMAND_SET_PLAYER_HEALTH: // 0x222
        break;
    case COMMAND_SET_CHAR_HEALTH: // 0x223
        break;
    case COMMAND_SET_CAR_HEALTH: // 0x224
        break;
    case COMMAND_GET_PLAYER_HEALTH: // 0x225
        break;
    case COMMAND_GET_CHAR_HEALTH: // 0x226
        break;
    case COMMAND_GET_CAR_HEALTH: // 0x227
        break;
    case COMMAND_IS_CAR_ARMED_WITH_BOMB: // 0x228
        break;
    case COMMAND_CHANGE_CAR_COLOUR: // 0x229
        break;
    case COMMAND_SWITCH_PED_ROADS_ON: // 0x22A
        break;
    case COMMAND_SWITCH_PED_ROADS_OFF: // 0x22B
        break;
    case COMMAND_CHAR_LOOK_AT_CHAR_ALWAYS: // 0x22C
        break;
    case COMMAND_CHAR_LOOK_AT_PLAYER_ALWAYS: // 0x22D
        break;
    case COMMAND_PLAYER_LOOK_AT_CHAR_ALWAYS: // 0x22E
        break;
    case COMMAND_STOP_CHAR_LOOKING: // 0x22F
        break;
    case COMMAND_STOP_PLAYER_LOOKING: // 0x230
        break;
    case COMMAND_SET_SCRIPT_POLICE_HELI_TO_CHASE_CHAR: // 0x231
        break;
    case COMMAND_SET_GANG_ATTITUDE: // 0x232
        break;
    case COMMAND_SET_GANG_GANG_ATTITUDE: // 0x233
        break;
    case COMMAND_SET_GANG_PLAYER_ATTITUDE: // 0x234
        break;
    case COMMAND_SET_GANG_PED_MODELS: // 0x235
        break;
    case COMMAND_SET_GANG_CAR_MODEL: // 0x236
        break;
    case COMMAND_SET_GANG_WEAPONS: // 0x237
        break;
    case COMMAND_SET_CHAR_OBJ_RUN_TO_AREA: // 0x238
        break;
    case COMMAND_SET_CHAR_OBJ_RUN_TO_COORD: // 0x239
        break;
    case COMMAND_IS_PLAYER_TOUCHING_OBJECT_ON_FOOT: // 0x23A
        break;
    case COMMAND_IS_CHAR_TOUCHING_OBJECT_ON_FOOT: // 0x23B
        break;
    case COMMAND_LOAD_SPECIAL_CHARACTER: // 0x23C
        break;
    case COMMAND_HAS_SPECIAL_CHARACTER_LOADED: // 0x23D
        break;
    case COMMAND_FLASH_CAR: // 0x23E | NOTSA
    {
        CollectParameters(2);
        CVehicle* vehicle = GetVehiclePool()->GetAt(ScriptParams[0].iParam);
        assert(vehicle);
        // todo:
        return OR_CONTINUE;
    }
    case COMMAND_FLASH_CHAR: // 0x23F | NOTSA
    {
        CollectParameters(2);
        CPed* ped = GetPedPool()->GetAt(ScriptParams[0].iParam);
        assert(ped);
        // todo: ped->
        return OR_CONTINUE;
    }
    case COMMAND_FLASH_OBJECT: // 0x240 | NOTSA
    {
        CollectParameters(2);
        CObject* object = GetObjectPool()->GetAt(ScriptParams[0].iParam);
        assert(object);
        // todo:
        return OR_CONTINUE;
    }
    case COMMAND_IS_PLAYER_IN_REMOTE_MODE: // 0x241
        break;
    case COMMAND_ARM_CAR_WITH_BOMB: // 0x242
        break;
    case COMMAND_SET_CHAR_PERSONALITY: // 0x243
        break;
    case COMMAND_SET_CUTSCENE_OFFSET: // 0x244
        break;
    case COMMAND_SET_ANIM_GROUP_FOR_CHAR: // 0x245
        break;
    case COMMAND_SET_ANIM_GROUP_FOR_PLAYER: // 0x246
        break;
    case COMMAND_REQUEST_MODEL: // 0x247
        break;
    case COMMAND_HAS_MODEL_LOADED: // 0x248
        break;
    case COMMAND_MARK_MODEL_AS_NO_LONGER_NEEDED: // 0x249
        break;
    case COMMAND_GRAB_PHONE: // 0x24A
        break;
    case COMMAND_SET_REPEATED_PHONE_MESSAGE: // 0x24B
        break;
    case COMMAND_SET_PHONE_MESSAGE: // 0x24C
        break;
    case COMMAND_HAS_PHONE_DISPLAYED_MESSAGE: // 0x24D
        break;
    case COMMAND_TURN_PHONE_OFF: // 0x24E
        break;
    case COMMAND_DRAW_CORONA: // 0x24F
        break;
    case COMMAND_DRAW_LIGHT: // 0x250 | NOTSA
    {
        CollectParameters(6);
        CVector pos = CTheScripts::ReadCVectorFromScript(0);
        CVector color = CTheScripts::ReadCVectorFromScript(3) / 255.0f;
        CPointLights::AddLight(ePointLightType::PLTYPE_POINTLIGHT, pos, {}, 12.0f, color.x, color.y, color.z, 0, true, nullptr);
        return OR_CONTINUE;
    }
    case COMMAND_STORE_WEATHER: // 0x251 | NOTSA
        break;
    case COMMAND_RESTORE_WEATHER: // 0x252 | NOTSA
        break;
    case COMMAND_STORE_CLOCK: // 0x253
        CClock::StoreClock();
        return OR_CONTINUE;
    case COMMAND_RESTORE_CLOCK: // 0x254
        CClock::RestoreClock();
        return OR_CONTINUE;
    case COMMAND_RESTART_CRITICAL_MISSION: // 0x255 | NOTSA
        break;
    case COMMAND_IS_PLAYER_PLAYING: // 0x256
        CollectParameters(1);
        UpdateCompareFlag(FindPlayerInfo(ScriptParams[0].iParam).m_nPlayerState == PLAYERSTATE_PLAYING);
        return OR_CONTINUE;
    case COMMAND_SET_COLL_OBJ_NO_OBJ: // 0x257
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
