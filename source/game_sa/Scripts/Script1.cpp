#include "StdInc.h"
#include "RunningScript.h"

// 0x466DE0
OpcodeResult CRunningScript::ProcessCommands100To199(int32 commandId) {
    switch (commandId) {
    case COMMAND_SUB_INT_VAR_FROM_INT_LVAR: // 0x064
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->iParam -= var2->iParam;
        return OR_CONTINUE;
    }
    case COMMAND_SUB_FLOAT_VAR_FROM_FLOAT_LVAR: // 0x065
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->fParam -= var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_SUB_INT_LVAR_FROM_INT_VAR: // 0x066
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->iParam -= var2->iParam;
        return OR_CONTINUE;
    }
    case COMMAND_SUB_FLOAT_LVAR_FROM_FLOAT_VAR: // 0x067
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->fParam -= var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_MULT_INT_VAR_BY_INT_VAR: // 0x068
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->iParam *= var2->iParam;
        return OR_CONTINUE;
    }
    case COMMAND_MULT_FLOAT_VAR_BY_FLOAT_VAR: // 0x069
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->fParam *= var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_MULT_INT_LVAR_BY_INT_LVAR: // 0x06A
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->iParam *= var2->iParam;
        return OR_CONTINUE;
    }
    case COMMAND_MULT_FLOAT_LVAR_BY_FLOAT_LVAR: // 0x06B
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->fParam *= var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_MULT_INT_VAR_BY_INT_LVAR: // 0x06C
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->iParam *= var2->iParam;
        return OR_CONTINUE;
    }
    case COMMAND_MULT_FLOAT_VAR_BY_FLOAT_LVAR: // 0x06D
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->fParam *= var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_MULT_INT_LVAR_BY_INT_VAR: // 0x06E
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->iParam *= var2->iParam;
        return OR_CONTINUE;
    }
    case COMMAND_MULT_FLOAT_LVAR_BY_FLOAT_VAR: // 0x06F
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->fParam *= var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_DIV_INT_VAR_BY_INT_VAR: // 0x070
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->iParam /= var2->iParam;
        return OR_CONTINUE;
    }
    case COMMAND_DIV_FLOAT_VAR_BY_FLOAT_VAR: // 0x071
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->fParam /= var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_DIV_INT_LVAR_BY_INT_LVAR: // 0x072
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->iParam /= var2->iParam;
        return OR_CONTINUE;
    }
    case COMMAND_DIV_FLOAT_LVAR_BY_FLOAT_LVAR: // 0x073
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->fParam /= var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_DIV_INT_VAR_BY_INT_LVAR: // 0x074
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->iParam /= var2->iParam;
        return OR_CONTINUE;
    }
    case COMMAND_DIV_FLOAT_VAR_BY_FLOAT_LVAR: // 0x075
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->fParam /= var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_DIV_INT_LVAR_BY_INT_VAR: // 0x076
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->iParam /= var2->iParam;
        return OR_CONTINUE;
    }
    case COMMAND_DIV_FLOAT_LVAR_BY_FLOAT_VAR: // 0x077
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->fParam /= var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_ADD_TIMED_VAL_TO_FLOAT_VAR: // 0x078
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        var->fParam += CTimer::GetTimeStep() * ScriptParams[0].fParam;
        return OR_CONTINUE;
    }
    case COMMAND_ADD_TIMED_VAL_TO_FLOAT_LVAR: // 0x079
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        var->fParam += CTimer::GetTimeStep() * ScriptParams[0].fParam;
        return OR_CONTINUE;
    }
    case COMMAND_ADD_TIMED_FLOAT_VAR_TO_FLOAT_VAR: // 0x07A
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->fParam += CTimer::GetTimeStep() * var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_ADD_TIMED_FLOAT_LVAR_TO_FLOAT_LVAR: // 0x07B
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->fParam += CTimer::GetTimeStep() * var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_ADD_TIMED_FLOAT_VAR_TO_FLOAT_LVAR: // 0x07C
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->fParam += CTimer::GetTimeStep() * var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_ADD_TIMED_FLOAT_LVAR_TO_FLOAT_VAR: // 0x07D
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->fParam += CTimer::GetTimeStep() * var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_SUB_TIMED_VAL_FROM_FLOAT_VAR: // 0x07E
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CollectParameters(1);
        var->fParam -= CTimer::GetTimeStep() * ScriptParams[0].fParam;
        return OR_CONTINUE;
    }
    case COMMAND_SUB_TIMED_VAL_FROM_FLOAT_LVAR: // 0x07F
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        CollectParameters(1);
        var->fParam -= CTimer::GetTimeStep() * ScriptParams[0].fParam;
        return OR_CONTINUE;
    }
    case COMMAND_SUB_TIMED_FLOAT_VAR_FROM_FLOAT_VAR: // 0x080
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->fParam -= CTimer::GetTimeStep() * var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_SUB_TIMED_FLOAT_LVAR_FROM_FLOAT_LVAR: // 0x081
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->fParam -= CTimer::GetTimeStep() * var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_SUB_TIMED_FLOAT_VAR_FROM_FLOAT_LVAR: // 0x082
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->fParam -= CTimer::GetTimeStep() * var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_SUB_TIMED_FLOAT_LVAR_FROM_FLOAT_VAR: // 0x083
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->fParam -= CTimer::GetTimeStep() * var2->fParam;
        return OR_CONTINUE;
    }
    case COMMAND_SET_VAR_INT_TO_VAR_INT: // 0x084
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        *var1 = *var2;
        return OR_CONTINUE;
    }
    case COMMAND_SET_LVAR_INT_TO_LVAR_INT: // 0x085
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        *var1 = *var2;
        return OR_CONTINUE;
    }
    case COMMAND_SET_VAR_FLOAT_TO_VAR_FLOAT: // 0x086
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        *var1 = *var2;
        return OR_CONTINUE;
    }
    case COMMAND_SET_LVAR_FLOAT_TO_LVAR_FLOAT: // 0x087
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        *var1 = *var2;
        return OR_CONTINUE;
    }
    case COMMAND_SET_VAR_FLOAT_TO_LVAR_FLOAT: // 0x088
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        *var1 = *var2;
        return OR_CONTINUE;
    }
    case COMMAND_SET_LVAR_FLOAT_TO_VAR_FLOAT: // 0x089
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        *var1 = *var2;
        return OR_CONTINUE;
    }
    case COMMAND_SET_VAR_INT_TO_LVAR_INT: // 0x08A
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        *var1 = *var2;
        return OR_CONTINUE;
    }
    case COMMAND_SET_LVAR_INT_TO_VAR_INT: // 0x08B
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        *var1 = *var2;
        return OR_CONTINUE;
    }
    case COMMAND_CSET_VAR_INT_TO_VAR_FLOAT: // 0x08C
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->iParam = static_cast<int32>(var2->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_CSET_VAR_FLOAT_TO_VAR_INT: // 0x08D
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->fParam = static_cast<float>(var2->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_CSET_LVAR_INT_TO_VAR_FLOAT: // 0x08E
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->iParam = static_cast<int32>(var2->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_CSET_LVAR_FLOAT_TO_VAR_INT: // 0x08F
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
        var1->fParam = static_cast<float>(var2->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_CSET_VAR_INT_TO_LVAR_FLOAT: // 0x090
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->iParam = static_cast<int32>(var2->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_CSET_VAR_FLOAT_TO_LVAR_INT: // 0x091
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->fParam = static_cast<float>(var2->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_CSET_LVAR_INT_TO_LVAR_FLOAT: // 0x092
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->iParam = static_cast<int32>(var2->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_CSET_LVAR_FLOAT_TO_LVAR_INT: // 0x093
    {
        tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
        tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
        var1->fParam = static_cast<float>(var2->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_ABS_VAR_INT: // 0x094
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        var->iParam = std::abs(var->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_ABS_LVAR_INT: // 0x095
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        var->iParam = std::abs(var->iParam);
        return OR_CONTINUE;
    }
    case COMMAND_ABS_VAR_FLOAT: // 0x096
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        var->fParam = std::abs(var->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_ABS_LVAR_FLOAT: // 0x097
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
        var->fParam = std::abs(var->fParam);
        return OR_CONTINUE;
    }
    case COMMAND_GENERATE_RANDOM_FLOAT: // 0x098 todo: Check "Bling-bling Scramble" case
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        CGeneral::GetRandomNumber(); // For
        CGeneral::GetRandomNumber(); // Better
        CGeneral::GetRandomNumber(); // Randomness
        var->fParam = CGeneral::GetRandomNumber() / (32768.0f * 2); // 100% NOT GetRandomNumberInRange(0, 0.5f) [0.000106812, 32768]
        return OR_CONTINUE;
    }
    case COMMAND_GENERATE_RANDOM_INT: // 0x099
    {
        tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
        var->iParam = CGeneral::GetRandomNumber();
        return OR_CONTINUE;
    }
    case COMMAND_CREATE_CHAR: // 0x09A
        break;
    case COMMAND_DELETE_CHAR: // 0x09B
        break;

    // case COMMAND_CHAR_WANDER_DIR: // 0x09C
    // case COMMAND_CHAR_WANDER_RANGE: // 0x09D
    // case COMMAND_CHAR_FOLLOW_PATH: // 0x09E
    // case COMMAND_CHAR_SET_IDLE: // 0x09F

    case COMMAND_GET_CHAR_COORDINATES: // 0x0A0
        break;
    case COMMAND_SET_CHAR_COORDINATES: // 0x0A1
        break;

    // case COMMAND_IS_CHAR_STILL_ALIVE: // 0x0A2

    case COMMAND_IS_CHAR_IN_AREA_2D: // 0x0A3
        break;
    case COMMAND_IS_CHAR_IN_AREA_3D: // 0x0A4
        break;
    case COMMAND_CREATE_CAR: // 0x0A5
        break;
    case COMMAND_DELETE_CAR: // 0x0A6
        break;
    case COMMAND_CAR_GOTO_COORDINATES: // 0x0A7
        break;
    case COMMAND_CAR_WANDER_RANDOMLY: // 0x0A8
        break;
    case COMMAND_CAR_SET_IDLE: // 0x0A9
        break;
    case COMMAND_GET_CAR_COORDINATES: // 0x0AA
        break;
    case COMMAND_SET_CAR_COORDINATES: // 0x0AB
        break;

    // case COMMAND_IS_CAR_STILL_ALIVE: // 0x0AC

    case COMMAND_SET_CAR_CRUISE_SPEED: // 0x0AD
        break;
    case COMMAND_SET_CAR_DRIVING_STYLE: // 0x0AE
    {
        CollectParameters(2);
        auto* vehicle = GetVehiclePool()->GetAt(ScriptParams[0].iParam >> 8);
        assert(vehicle);
        vehicle->m_autoPilot.m_nCarDrivingStyle = static_cast<eCarDrivingStyle>(ScriptParams[1].u8Param);
        return OR_CONTINUE;
    }
    case COMMAND_SET_CAR_MISSION: // 0x0AF
        break;
    case COMMAND_IS_CAR_IN_AREA_2D: // 0x0B0
        break;
    case COMMAND_IS_CAR_IN_AREA_3D: // 0x0B1 see COMMAND_IS_PLAYER_IN_AREA_2D
        break;

    case COMMAND_SPECIAL_0: // 0x0B2 | NOTSA
    case COMMAND_SPECIAL_1: // 0x0B3 | NOTSA
    case COMMAND_SPECIAL_2: // 0x0B4 | NOTSA
    case COMMAND_SPECIAL_3: // 0x0B5 | NOTSA
    case COMMAND_SPECIAL_4: // 0x0B6 | NOTSA
    case COMMAND_SPECIAL_5: // 0x0B7 | NOTSA
    case COMMAND_SPECIAL_6: // 0x0B8 | NOTSA
    case COMMAND_SPECIAL_7: // 0x0B9 | NOTSA
        assert(0);
        return OR_CONTINUE;

    case COMMAND_PRINT_BIG: // 0x0BA
    {
        char label[8];
        ReadTextLabelFromScript(label, 8);
        char* text = TheText.Get(label);
        CollectParameters(2);
        CMessages::AddBigMessage(text, ScriptParams[0].iParam, (eMessageStyle)(ScriptParams[1].iParam - 1));
        return OR_CONTINUE;
    }
    case COMMAND_PRINT: // 0x0BB
    {
        char label[8];
        ReadTextLabelFromScript(label, 8);
        char* text = TheText.Get(label);
        CollectParameters(2);
        if (!text || text[0] != '~' || text[1] != 'z' || text[2] != '~' || FrontEndMenuManager.m_bShowSubtitles)
            CMessages::AddMessage(text, ScriptParams[0].iParam, ScriptParams[1].iParam, CTheScripts::bAddNextMessageToPreviousBriefs);
        CTheScripts::bAddNextMessageToPreviousBriefs = true;
        return OR_CONTINUE;
    }
    case COMMAND_PRINT_NOW: // 0x0BC
    {
        char label[8];
        ReadTextLabelFromScript(label, 8);
        char* text = TheText.Get(label);
        CollectParameters(2);
        if (!text || text[0] != '~' || text[1] != 'z' || text[2] != '~' || FrontEndMenuManager.m_bShowSubtitles)
            CMessages::AddMessageJumpQ(text, ScriptParams[0].iParam, ScriptParams[1].iParam, CTheScripts::bAddNextMessageToPreviousBriefs);
        CTheScripts::bAddNextMessageToPreviousBriefs = true;
        return OR_CONTINUE;
    }

    case COMMAND_PRINT_SOON: // 0x0BD | NOTSA
    {
        // CollectParameters(2);
        break;
    }
    case COMMAND_CLEAR_PRINTS: // 0x0BE
        CMessages::ClearMessages(false);
        return OR_CONTINUE;
    case COMMAND_GET_TIME_OF_DAY: // 0x0BF
        ScriptParams[0].iParam = CClock::ms_nGameClockHours;
        ScriptParams[1].iParam = CClock::ms_nGameClockMinutes;
        StoreParameters(2);
        return OR_CONTINUE;
    case COMMAND_SET_TIME_OF_DAY: // 0x0C0
        CollectParameters(2);
        CClock::SetGameClock(ScriptParams[0].iParam, ScriptParams[1].iParam, 0);
        return OR_CONTINUE;
    case COMMAND_GET_MINUTES_TO_TIME_OF_DAY: // 0x0C1
        CollectParameters(2);
        ScriptParams[0].iParam = CClock::GetGameClockMinutesUntil(ScriptParams[0].iParam, ScriptParams[1].iParam);
        StoreParameters(1);
        return OR_CONTINUE;
    case COMMAND_IS_POINT_ON_SCREEN: // 0x0C2
    {
        CollectParameters(4);
        CVector pos = CTheScripts::ReadCVectorFromScript(0);
        if (pos.z <= MAP_Z_LOW_LIMIT)
            pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y);

        UpdateCompareFlag(TheCamera.IsSphereVisible(&pos, ScriptParams[3].fParam));
        return OR_CONTINUE;
    }
    case COMMAND_DEBUG_ON: // 0x0C3
#ifndef FINAL
       CTheScripts::DbgFlag = true;
#endif
        return OR_CONTINUE;
    case COMMAND_DEBUG_OFF: // 0x0C4
#ifndef FINAL
        CTheScripts::DbgFlag = false;
#endif
        return OR_CONTINUE;
    case COMMAND_RETURN_TRUE: // 0x0C5
        UpdateCompareFlag(true);
        return OR_CONTINUE;
    case COMMAND_RETURN_FALSE: // 0x0C6
        UpdateCompareFlag(false);
        return OR_CONTINUE;
    // case COMMAND_VAR_INT: // 0x0C7
    default:
        return OR_INTERRUPT;
    }

    return OR_IMPLEMENTED_YET;
}
