#include "StdInc.h"

#include "RunningScript.h"
#include "Radar.h"

// 0x48B590
OpcodeResult CRunningScript::ProcessCommands1200To1299(int32 commandId) {
    switch (commandId) {
    case COMMAND_IS_INT_VAR_GREATER_THAN_CONSTANT: // 0x4B0
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        UpdateCompareFlag(var->iParam > ScriptParams[0].iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_LVAR_GREATER_THAN_CONSTANT: // 0x4B1
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        UpdateCompareFlag(var->iParam > ScriptParams[0].iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_CONSTANT_GREATER_THAN_INT_VAR: // 0x4B2
    {
        CollectParameters(1);
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        UpdateCompareFlag(ScriptParams[0].iParam > var->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_CONSTANT_GREATER_THAN_INT_LVAR: // 0x4B3
    {
        CollectParameters(1);
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        UpdateCompareFlag(ScriptParams[0].iParam > var->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_CONSTANT: // 0x4B4
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        UpdateCompareFlag(var->iParam >= ScriptParams[0].iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_CONSTANT: // 0x4B5
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        UpdateCompareFlag(var->iParam >= ScriptParams[0].iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_CONSTANT_GREATER_OR_EQUAL_TO_INT_VAR: // 0x4B6
    {
        CollectParameters(1);
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        UpdateCompareFlag(ScriptParams[0].iParam >= var->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_IS_CONSTANT_GREATER_OR_EQUAL_TO_INT_LVAR: // 0x4B7
    {
        CollectParameters(1);
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        UpdateCompareFlag(ScriptParams[0].iParam >= var->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_GET_CHAR_WEAPON_IN_SLOT: // 0x4B8
        break;
    case COMMAND_GET_CLOSEST_STRAIGHT_ROAD: // 0x4B9
        break;
    case COMMAND_SET_CAR_FORWARD_SPEED: // 0x4BA
        break;
    case COMMAND_SET_AREA_VISIBLE: // 0x4BB
        break;
    case COMMAND_SET_CUTSCENE_ANIM_TO_LOOP: // 0x4BC
        break;
    case COMMAND_MARK_CAR_AS_CONVOY_CAR: // 0x4BD
        break;
    case COMMAND_RESET_HAVOC_CAUSED_BY_PLAYER: // 0x4BE
        break;
    case COMMAND_GET_HAVOC_CAUSED_BY_PLAYER: // 0x4BF
        break;
    case COMMAND_CREATE_SCRIPT_ROADBLOCK: // 0x4C0
        break;
    case COMMAND_CLEAR_ALL_SCRIPT_ROADBLOCKS: // 0x4C1
        break;
    case COMMAND_SET_CHAR_OBJ_WALK_TO_CHAR: // 0x4C2
        break;
    case COMMAND_IS_PICKUP_IN_ZONE: // 0x4C3
        break;
    case COMMAND_GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS: // 0x4C4
        break;
    case COMMAND_HAS_CHAR_BEEN_PHOTOGRAPHED: // 0x4C5
        break;
    case COMMAND_SET_CHAR_OBJ_AIM_GUN_AT_CHAR: // 0x4C6
        break;
    case COMMAND_SWITCH_SECURITY_CAMERA: // 0x4C7
        break;
    case COMMAND_IS_CHAR_IN_FLYING_VEHICLE: // 0x4C8
        break;
    case COMMAND_IS_PLAYER_IN_FLYING_VEHICLE: // 0x4C9
        break;
    case COMMAND_HAS_SONY_CD_BEEN_READ: // 0x4CA
        break;
    case COMMAND_GET_NUMBER_OF_SONY_CDS_READ: // 0x4CB
        break;
    case COMMAND_ADD_SHORT_RANGE_BLIP_FOR_COORD_OLD: // 0x4CC
        break;
    case COMMAND_ADD_SHORT_RANGE_BLIP_FOR_COORD: // 0x4CD
        break;
    case COMMAND_ADD_SHORT_RANGE_SPRITE_BLIP_FOR_COORD: // 0x4CE 0x48BC0E
    {
        CollectParameters(4);
        CVector pos = CTheScripts::ReadCVectorFromScript(0);
        if (pos.z <= MAP_Z_LOW_LIMIT)
            pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);

        int32 index = CollectNextParameterWithoutIncreasingPC(); // pointless
        CRadar::GetActualBlipArrayIndex(index);                  // pointless

        int32 blip = CRadar::SetShortRangeCoordBlip(BLIP_COORD, pos, 5, BLIP_DISPLAY_BOTH, m_szName);
        CRadar::SetBlipSprite(blip, ScriptParams[3].iParam);
        ScriptParams[0].iParam = blip;
        StoreParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_ADD_MONEY_SPENT_ON_CLOTHES: // 0x4CF
        break;
    case COMMAND_SET_HELI_ORIENTATION: // 0x4D0
        break;
    case COMMAND_CLEAR_HELI_ORIENTATION: // 0x4D1
    {
        CollectParameters(1);
        auto* heli = GetVehiclePool()->GetAt(ScriptParams[0].iParam)->AsAutomobile();
        assert(heli && heli->IsRealHeli());
        heli->ClearHeliOrientation();
        return OR_CONTINUE;
    }
    case COMMAND_PLANE_GOTO_COORDS: // 0x4D2
        break;
    case COMMAND_GET_NTH_CLOSEST_CAR_NODE: // 0x4D3
        break;
    case COMMAND_GET_NTH_CLOSEST_CHAR_NODE: // 0x4D4
        break;
    case COMMAND_DRAW_WEAPONSHOP_CORONA: // 0x4D5
        break;
    case COMMAND_SET_ENABLE_RC_DETONATE_ON_CONTACT: // 0x4D6
        break;
    case COMMAND_FREEZE_CHAR_POSITION: // 0x4D7
        break;
    case COMMAND_SET_CHAR_DROWNS_IN_WATER: // 0x4D8
        break;
    case COMMAND_SET_OBJECT_RECORDS_COLLISIONS: // 0x4D9
        break;
    case COMMAND_HAS_OBJECT_COLLIDED_WITH_ANYTHING: // 0x4DA
        break;
    case COMMAND_REMOVE_RC_BUGGY: // 0x4DB
    {
        FindPlayerInfo(CWorld::PlayerInFocus).BlowUpRCBuggy(false);
        return OR_CONTINUE;
    }
    case COMMAND_HAS_PHOTOGRAPH_BEEN_TAKEN: // 0x4DC
        break;
    case COMMAND_GET_CHAR_ARMOUR: // 0x4DD
        break;
    case COMMAND_SET_CHAR_ARMOUR: // 0x4DE
        break;
    case COMMAND_SET_HELI_STABILISER: // 0x4DF
        break;
    case COMMAND_SET_CAR_STRAIGHT_LINE_DISTANCE: // 0x4E0
        break;
    case COMMAND_POP_CAR_BOOT: // 0x4E1
        break;
    case COMMAND_SHUT_PLAYER_UP: // 0x4E2
        break;
    case COMMAND_SET_PLAYER_MOOD: // 0x4E3
        break;
    case COMMAND_REQUEST_COLLISION: // 0x4E4
        break;
    case COMMAND_LOCATE_OBJECT_2D: // 0x4E5
        break;
    case COMMAND_LOCATE_OBJECT_3D: // 0x4E6
        break;
    case COMMAND_IS_OBJECT_IN_WATER: // 0x4E7
        break;
    case COMMAND_SET_CHAR_OBJ_STEAL_ANY_CAR_EVEN_MISSION_CAR: // 0x4E8
        break;
    case COMMAND_IS_OBJECT_IN_AREA_2D: // 0x4E9
    case COMMAND_IS_OBJECT_IN_AREA_3D: // 0x4EA
        ObjectInAreaCheckCommand(commandId);
        return OR_CONTINUE;
    case COMMAND_TASK_TOGGLE_DUCK: // 0x4EB
        break;
    case COMMAND_SET_ZONE_CIVILIAN_CAR_INFO: // 0x4EC
        break;
    case COMMAND_REQUEST_ANIMATION: // 0x4ED
        break;
    case COMMAND_HAS_ANIMATION_LOADED: // 0x4EE
        break;
    case COMMAND_REMOVE_ANIMATION: // 0x4EF
        break;
    case COMMAND_IS_CHAR_WAITING_FOR_WORLD_COLLISION: // 0x4F0
        break;
    case COMMAND_IS_CAR_WAITING_FOR_WORLD_COLLISION: // 0x4F1
        break;
    case COMMAND_IS_OBJECT_WAITING_FOR_WORLD_COLLISION: // 0x4F2
        break;
    case COMMAND_SET_CHAR_SHUFFLE_INTO_DRIVERS_SEAT: // 0x4F3
        break;
    case COMMAND_ATTACH_CHAR_TO_OBJECT: // 0x4F4
        break;
    case COMMAND_SET_CHAR_AS_PLAYER_FRIEND: // 0x4F5
        break;
    case COMMAND_DISPLAY_NTH_ONSCREEN_COUNTER: // 0x4F6
        break;
    case COMMAND_DISPLAY_NTH_ONSCREEN_COUNTER_WITH_STRING: // 0x4F7
        break;
    case COMMAND_ADD_SET_PIECE: // 0x4F8
        CollectParameters(13);
        CSetPieces::AddOne(
            ScriptParams[0].uParam,
            CTheScripts::ReadCVectorFromScript(1),
            CTheScripts::ReadCVectorFromScript(3),
            CTheScripts::ReadCVectorFromScript(5),
            CTheScripts::ReadCVectorFromScript(7),
            CTheScripts::ReadCVectorFromScript(9),
            CTheScripts::ReadCVectorFromScript(11)
        );
        return OR_CONTINUE;
    case COMMAND_SET_EXTRA_COLOURS: // 0x4F9
        break;
    case COMMAND_CLEAR_EXTRA_COLOURS: // 0x4FA
        break;
    case COMMAND_CLOSE_CAR_BOOT: // 0x4FB
        break;
    case COMMAND_GET_WHEELIE_STATS: // 0x4FC
        break;
    case COMMAND_DISARM_CHAR: // 0x4FD
        break;
    case COMMAND_BURST_CAR_TYRE: // 0x4FE
        break;
    case COMMAND_IS_CHAR_OBJ_NO_OBJ: // 0x4FF
        break;
    case COMMAND_IS_PLAYER_WEARING: // 0x500
        break;
    case COMMAND_SET_PLAYER_CAN_DO_DRIVE_BY: // 0x501
        break;
    case COMMAND_SET_CHAR_OBJ_SPRINT_TO_COORD: // 0x502
        break;
    case COMMAND_CREATE_SWAT_ROPE: // 0x503
        break;
    case COMMAND_SET_FIRST_PERSON_CONTROL_CAMERA: // 0x504
        break;
    case COMMAND_GET_NEAREST_TYRE_TO_POINT: // 0x505
        break;
    case COMMAND_SET_CAR_MODEL_COMPONENTS: // 0x506
        break;
    case COMMAND_SWITCH_LIFT_CAMERA: // 0x507
        break;
    case COMMAND_CLOSE_ALL_CAR_DOORS: // 0x508
        break;
    case COMMAND_GET_DISTANCE_BETWEEN_COORDS_2D: // 0x509
    {
        CollectParameters(4);
        ScriptParams[0].fParam = (CTheScripts::ReadCVector2DFromScript(0) - CTheScripts::ReadCVector2DFromScript(2)).Magnitude();
        StoreParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_GET_DISTANCE_BETWEEN_COORDS_3D: // 0x50A
    {
        CollectParameters(6);
        ScriptParams[0].fParam = (CTheScripts::ReadCVectorFromScript(0) - CTheScripts::ReadCVectorFromScript(3)).Magnitude();
        StoreParameters(1);
        return OR_CONTINUE;
    }
    case COMMAND_POP_CAR_BOOT_USING_PHYSICS: // 0x50B
    {
        CollectParameters(1);
        auto* car = GetVehiclePool()->GetAt(ScriptParams[0].iParam)->AsAutomobile();
        assert(car && car->IsAutomobile());
        car->PopBootUsingPhysics();
        return OR_CONTINUE;
    }
    case COMMAND_SET_FIRST_PERSON_WEAPON_CAMERA: // 0x50C
        break;
    case COMMAND_IS_CHAR_LEAVING_VEHICLE_TO_DIE: // 0x50D
        break;
    case COMMAND_SORT_OUT_OBJECT_COLLISION_WITH_CAR: // 0x50E
        break;
    case COMMAND_GET_MAX_WANTED_LEVEL: // 0x50F
        break;
    case COMMAND_IS_CHAR_WANDER_PATH_CLEAR: // 0x510
        break;
    case COMMAND_PRINT_HELP_WITH_NUMBER: // 0x511
        break;
    case COMMAND_PRINT_HELP_FOREVER: // 0x512
        break;
    case COMMAND_PRINT_HELP_FOREVER_WITH_NUMBER: // 0x513
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
