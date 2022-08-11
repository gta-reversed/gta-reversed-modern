#include "StdInc.h"
#include "RunningScript.h"

// 0x469390
OpcodeResult CRunningScript::ProcessCommands200To299(int32 commandId) {
    switch (commandId) {
    // case COMMAND_VAR_FLOAT: // 0x0C8
    // case COMMAND_LVAR_INT: // 0x0C9
    // case COMMAND_LVAR_FLOAT: // 0x0CA
    // case COMMAND_START_SCOPE: // 0x0CB
    // case COMMAND_END_SCOPE: // 0x0CC
    // case COMMAND_REPEAT: // 0x0CD
    // case COMMAND_ENDREPEAT: // 0x0CE
    // case COMMAND_IF: // 0x0CF
    // case COMMAND_IFNOT: // 0x0D0
    // case COMMAND_ELSE: // 0x0D1
    // case COMMAND_ENDIF: // 0x0D2
    // case COMMAND_WHILE: // 0x0D3
    // case COMMAND_WHILENOT: // 0x0D4
    // case COMMAND_ENDWHILE: // 0x0D5

    case COMMAND_ANDOR: // 0x0D6
        CollectParameters(1);
        m_nLogicalOp = ScriptParams[0].iParam;
        if (m_nLogicalOp == ANDOR_NONE)
        {
            m_bCondResult = false;
        }
        else if (m_nLogicalOp >= ANDS_1 && m_nLogicalOp <= ANDS_8)
        {
            m_nLogicalOp++;
            m_bCondResult = true;
        }
        else if (m_nLogicalOp >= ORS_1 && m_nLogicalOp <= ORS_8)
        {
            m_nLogicalOp++;
            m_bCondResult = false;
        }
        return OR_CONTINUE;
    case COMMAND_LAUNCH_MISSION: // 0x0D7
        CollectParameters(1);
        CTheScripts::StartNewScript(&CTheScripts::ScriptSpace[ScriptParams[0].iParam]);
        return OR_CONTINUE;
    case COMMAND_MISSION_HAS_FINISHED: // 0x0D8
        break;
    case COMMAND_STORE_CAR_CHAR_IS_IN: // 0x0D9
        break;
    case COMMAND_STORE_CAR_PLAYER_IS_IN: // 0x0DA
        break;
    case COMMAND_IS_CHAR_IN_CAR: // 0x0DB
        break;
    case COMMAND_IS_PLAYER_IN_CAR: // 0x0DC
        break;
    case COMMAND_IS_CHAR_IN_MODEL: // 0x0DD
        break;
    case COMMAND_IS_PLAYER_IN_MODEL: // 0x0DE
        break;
    case COMMAND_IS_CHAR_IN_ANY_CAR: // 0x0DF
        break;
    case COMMAND_IS_PLAYER_IN_ANY_CAR: // 0x0E0
        break;
    case COMMAND_IS_BUTTON_PRESSED: // 0x0E1
        break;
    case COMMAND_GET_PAD_STATE: // 0x0E2
        break;
    case COMMAND_LOCATE_PLAYER_ANY_MEANS_2D: // 0x0E3
        break;
    case COMMAND_LOCATE_PLAYER_ON_FOOT_2D: // 0x0E4
        break;
    case COMMAND_LOCATE_PLAYER_IN_CAR_2D: // 0x0E5
        break;
    case COMMAND_LOCATE_STOPPED_PLAYER_ANY_MEANS_2D: // 0x0E6
        break;
    case COMMAND_LOCATE_STOPPED_PLAYER_ON_FOOT_2D: // 0x0E7
        break;
    case COMMAND_LOCATE_STOPPED_PLAYER_IN_CAR_2D: // 0x0E8
        break;
    case COMMAND_LOCATE_PLAYER_ANY_MEANS_CHAR_2D: // 0x0E9
        break;
    case COMMAND_LOCATE_PLAYER_ON_FOOT_CHAR_2D: // 0x0EA
        break;
    case COMMAND_LOCATE_PLAYER_IN_CAR_CHAR_2D: // 0x0EB
        break;
    case COMMAND_LOCATE_CHAR_ANY_MEANS_2D: // 0x0EC
        break;
    case COMMAND_LOCATE_CHAR_ON_FOOT_2D: // 0x0ED
        break;
    case COMMAND_LOCATE_CHAR_IN_CAR_2D: // 0x0EE
        break;
    case COMMAND_LOCATE_STOPPED_CHAR_ANY_MEANS_2D: // 0x0EF
        break;
    case COMMAND_LOCATE_STOPPED_CHAR_ON_FOOT_2D: // 0x0F0
        break;
    case COMMAND_LOCATE_STOPPED_CHAR_IN_CAR_2D: // 0x0F1
        break;
    case COMMAND_LOCATE_CHAR_ANY_MEANS_CHAR_2D: // 0x0F2
        break;
    case COMMAND_LOCATE_CHAR_ON_FOOT_CHAR_2D: // 0x0F3
        break;
    case COMMAND_LOCATE_CHAR_IN_CAR_CHAR_2D: // 0x0F4
        break;
    case COMMAND_LOCATE_PLAYER_ANY_MEANS_3D: // 0x0F5
        break;
    case COMMAND_LOCATE_PLAYER_ON_FOOT_3D: // 0x0F6
        break;
    case COMMAND_LOCATE_PLAYER_IN_CAR_3D: // 0x0F7
        break;
    case COMMAND_LOCATE_STOPPED_PLAYER_ANY_MEANS_3D: // 0x0F8
        break;
    case COMMAND_LOCATE_STOPPED_PLAYER_ON_FOOT_3D: // 0x0F9
        break;
    case COMMAND_LOCATE_STOPPED_PLAYER_IN_CAR_3D: // 0x0FA
        break;
    case COMMAND_LOCATE_PLAYER_ANY_MEANS_CHAR_3D: // 0x0FB
        break;
    case COMMAND_LOCATE_PLAYER_ON_FOOT_CHAR_3D: // 0x0FC
        break;
    case COMMAND_LOCATE_PLAYER_IN_CAR_CHAR_3D: // 0x0FD
        break;
    case COMMAND_LOCATE_CHAR_ANY_MEANS_3D: // 0x0FE
        break;
    case COMMAND_LOCATE_CHAR_ON_FOOT_3D: // 0x0FF
        break;
    case COMMAND_LOCATE_CHAR_IN_CAR_3D: // 0x100
        break;
    case COMMAND_LOCATE_STOPPED_CHAR_ANY_MEANS_3D: // 0x101
        break;
    case COMMAND_LOCATE_STOPPED_CHAR_ON_FOOT_3D: // 0x102
        break;
    case COMMAND_LOCATE_STOPPED_CHAR_IN_CAR_3D: // 0x103
        break;
    case COMMAND_LOCATE_CHAR_ANY_MEANS_CHAR_3D: // 0x104
        break;
    case COMMAND_LOCATE_CHAR_ON_FOOT_CHAR_3D: // 0x105
        break;
    case COMMAND_LOCATE_CHAR_IN_CAR_CHAR_3D: // 0x106
        break;
    case COMMAND_CREATE_OBJECT: // 0x107
        break;
    case COMMAND_DELETE_OBJECT: // 0x108
        break;
    case COMMAND_ADD_SCORE: // 0x109
        break;
    case COMMAND_IS_SCORE_GREATER: // 0x10A
        break;
    case COMMAND_STORE_SCORE: // 0x10B
        break;
    case COMMAND_GIVE_REMOTE_CONTROLLED_CAR_TO_PLAYER: // 0x10C
        break;
    case COMMAND_ALTER_WANTED_LEVEL: // 0x10D
        break;
    case COMMAND_ALTER_WANTED_LEVEL_NO_DROP: // 0x10E
        break;
    case COMMAND_IS_WANTED_LEVEL_GREATER: // 0x10F
        break;
    case COMMAND_CLEAR_WANTED_LEVEL: // 0x110
        break;
    case COMMAND_SET_DEATHARREST_STATE: // 0x111
        break;
    case COMMAND_HAS_DEATHARREST_BEEN_EXECUTED: // 0x112
        break;
    case COMMAND_ADD_AMMO_TO_PLAYER: // 0x113
        break;
    case COMMAND_ADD_AMMO_TO_CHAR: // 0x114
        break;
    case COMMAND_ADD_AMMO_TO_CAR: // 0x115
        break;
    case COMMAND_IS_PLAYER_STILL_ALIVE: // 0x116
        break;
    case COMMAND_IS_PLAYER_DEAD: // 0x117
        break;
    case COMMAND_IS_CHAR_DEAD: // 0x118
        break;
    case COMMAND_IS_CAR_DEAD: // 0x119
        break;
    case COMMAND_SET_CHAR_THREAT_SEARCH: // 0x11A
        break;
    case COMMAND_SET_CHAR_THREAT_REACTION: // 0x11B
        break;
    case COMMAND_SET_CHAR_OBJ_NO_OBJ: // 0x11C
        break;
    case COMMAND_ORDER_DRIVER_OUT_OF_CAR: // 0x11D
        break;
    case COMMAND_ORDER_CHAR_TO_DRIVE_CAR: // 0x11E
        break;
    case COMMAND_ADD_PATROL_POINT: // 0x11F
        break;
    case COMMAND_IS_PLAYER_IN_GANGZONE: // 0x120
        break;
    case COMMAND_IS_PLAYER_IN_ZONE: // 0x121
        break;
    case COMMAND_IS_PLAYER_PRESSING_HORN: // 0x122
        break;
    case COMMAND_HAS_CHAR_SPOTTED_PLAYER: // 0x123
        break;
    case COMMAND_ORDER_CHAR_TO_BACKDOOR: // 0x124
        break;
    case COMMAND_ADD_CHAR_TO_GANG: // 0x125
        break;
    case COMMAND_IS_CHAR_OBJECTIVE_PASSED: // 0x126
        break;
    case COMMAND_SET_CHAR_DRIVE_AGGRESSION: // 0x127
        break;
    case COMMAND_SET_CHAR_MAX_DRIVESPEED: // 0x128
        break;
    case COMMAND_CREATE_CHAR_INSIDE_CAR: // 0x129
        break;
    case COMMAND_WARP_PLAYER_FROM_CAR_TO_COORD: // 0x12A
        break;
    case COMMAND_MAKE_CHAR_DO_NOTHING: // 0x12B
        break;
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
