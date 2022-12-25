#pragma once
#include <functional>
#include "CommandParser/Parser.hpp"

/*
* Basic language feature commands (Comparasions, assingments, etc...)
*/

OpcodeResult Wait(CRunningScript& S, uint32 duration) {
    S.m_nWakeTime = CTimer::GetTimeInMS() + duration;
    return OR_WAIT;
}
REGISTER_COMMAND_HANDLER(COMMAND_WAIT, Wait);

REGISTER_COMMAND_HANDLER(COMMAND_GOTO, [](CRunningScript& S, int32 address) -> void { S.UpdatePC(address); });

REGISTER_COMMAND_HANDLER(COMMAND_SET_VAR_INT,  [](uint32& var, uint32 value) { var = value; });
REGISTER_COMMAND_HANDLER(COMMAND_SET_VAR_FLOAT,  [](float& var, float value) { var = value; });
REGISTER_COMMAND_HANDLER(COMMAND_SET_LVAR_INT, [](uint32& var, uint32 value) { var = value; });
REGISTER_COMMAND_HANDLER(COMMAND_SET_LVAR_FLOAT, [](float& var, float value) { var = value; });

REGISTER_COMMAND_HANDLER(COMMAND_ADD_VAL_TO_INT_VAR,  [](uint32& var, uint32 value) { var += value; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_VAL_TO_FLOAT_VAR,  [](float& var, float value) { var += value; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_VAL_TO_INT_LVAR, [](uint32& var, uint32 value) { var += value; });
REGISTER_COMMAND_HANDLER(COMMAND_ADD_VAL_TO_FLOAT_LVAR, [](float& var, float value) { var += value; });

REGISTER_COMMAND_HANDLER(COMMAND_SUB_VAL_FROM_INT_VAR,  [](uint32& var, uint32 value) { var -= value; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_VAL_FROM_FLOAT_VAR,  [](float& var, float value) { var -= value; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_VAL_FROM_INT_LVAR, [](uint32& var, uint32 value) { var -= value; });
REGISTER_COMMAND_HANDLER(COMMAND_SUB_VAL_FROM_FLOAT_LVAR, [](float& var, float value) { var -= value; });

REGISTER_COMMAND_HANDLER(COMMAND_MULT_INT_VAR_BY_VAL,  [](uint32& var, uint32 value) { var *= value; });
REGISTER_COMMAND_HANDLER(COMMAND_MULT_FLOAT_VAR_BY_VAL,  [](float& var, float value) { var *= value; });
REGISTER_COMMAND_HANDLER(COMMAND_MULT_INT_LVAR_BY_VAL, [](uint32& var, uint32 value) { var *= value; });
REGISTER_COMMAND_HANDLER(COMMAND_MULT_FLOAT_LVAR_BY_VAL, [](float& var, float value) { var *= value; });

REGISTER_COMMAND_HANDLER(COMMAND_DIV_INT_VAR_BY_VAL,  [](uint32& var, uint32 value) { var /= value; });
REGISTER_COMMAND_HANDLER(COMMAND_DIV_FLOAT_VAR_BY_VAL,  [](float& var, float value) { var /= value; });
REGISTER_COMMAND_HANDLER(COMMAND_DIV_INT_LVAR_BY_VAL, [](uint32& var, uint32 value) { var /= value; });
REGISTER_COMMAND_HANDLER(COMMAND_DIV_FLOAT_LVAR_BY_VAL, [](float& var, float value) { var /= value; });


/*
template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_GREATER_THAN_NUMBER>() { // 0x018
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam > ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_GREATER_THAN_NUMBER>() { // 0x019
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam > ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_NUMBER_GREATER_THAN_INT_VAR>() { // 0x01A
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(ScriptParams[0].iParam > var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_NUMBER_GREATER_THAN_INT_LVAR>() { // 0x01B
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(ScriptParams[0].iParam > var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_GREATER_THAN_INT_VAR>() { // 0x01C
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->iParam > var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_GREATER_THAN_INT_LVAR>() { // 0x01D
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->iParam > var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_GREATER_THAN_INT_LVAR>() { // 0x01E
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->iParam > var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_GREATER_THAN_INT_VAR>() { // 0x01F
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->iParam > var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_VAR_GREATER_THAN_NUMBER>() { // 0x020
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    UpdateCompareFlag(var->fParam > ScriptParams[0].fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_LVAR_GREATER_THAN_NUMBER>() { // 0x021
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    UpdateCompareFlag(var->fParam > ScriptParams[0].fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_NUMBER_GREATER_THAN_FLOAT_VAR>() { // 0x022
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(ScriptParams[0].fParam > var->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_NUMBER_GREATER_THAN_FLOAT_LVAR>() { // 0x023
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(ScriptParams[0].fParam > var->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_VAR_GREATER_THAN_FLOAT_VAR>() { // 0x024
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->fParam > var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_LVAR_GREATER_THAN_FLOAT_LVAR>() { // 0x025
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->fParam > var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_VAR_GREATER_THAN_FLOAT_LVAR>() { // 0x026
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->fParam > var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_LVAR_GREATER_THAN_FLOAT_VAR>() { // 0x027
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->fParam > var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_NUMBER>() { // 0x028
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam >= ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_NUMBER>() { // 0x029
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam >= ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_INT_VAR>() { // 0x02A
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(ScriptParams[0].iParam >= var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_INT_LVAR>() { // 0x02B
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(ScriptParams[0].iParam >= var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_INT_VAR>() { // 0x02C
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->iParam >= var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_INT_LVAR>() { // 0x02D
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->iParam >= var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_INT_LVAR>() { // 0x02E
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->iParam >= var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_INT_VAR>() { // 0x02F
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->iParam >= var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_VAR_GREATER_OR_EQUAL_TO_NUMBER>() { // 0x030
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    UpdateCompareFlag(var->fParam >= ScriptParams[0].fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_NUMBER>() { // 0x031
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    UpdateCompareFlag(var->fParam >= ScriptParams[0].fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_FLOAT_VAR>() { // 0x032
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(ScriptParams[0].fParam >= var->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_NUMBER_GREATER_OR_EQUAL_TO_FLOAT_LVAR>() { // 0x033
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(ScriptParams[0].fParam >= var->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_VAR_GREATER_OR_EQUAL_TO_FLOAT_VAR>() { // 0x034
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->fParam >= var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_FLOAT_LVAR>() { // 0x035
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->fParam >= var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_VAR_GREATER_OR_EQUAL_TO_FLOAT_LVAR>() { // 0x036
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->fParam >= var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_LVAR_GREATER_OR_EQUAL_TO_FLOAT_VAR>() { // 0x037
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->fParam >= var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_EQUAL_TO_NUMBER>() { // 0x038
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam == ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_EQUAL_TO_NUMBER>() { // 0x039
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam == ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_EQUAL_TO_INT_VAR>() { // 0x03A
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->iParam == var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_EQUAL_TO_INT_LVAR>() { // 0x03B
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->iParam == var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_EQUAL_TO_INT_LVAR>() { // 0x03C
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->iParam == var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_VAR_EQUAL_TO_NUMBER>() { // 0x042
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    UpdateCompareFlag(var->fParam == ScriptParams[0].fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_LVAR_EQUAL_TO_NUMBER>() { // 0x043
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    UpdateCompareFlag(var->fParam == ScriptParams[0].fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_VAR_EQUAL_TO_FLOAT_VAR>() { // 0x044
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(var1->fParam == var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_LVAR_EQUAL_TO_FLOAT_LVAR>() { // 0x045
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->fParam == var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_FLOAT_VAR_EQUAL_TO_FLOAT_LVAR>() { // 0x046
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(var1->fParam == var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_INT_VAR_FROM_INT_LVAR>() {
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam -= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_FLOAT_VAR_FROM_FLOAT_LVAR>() { // 0x065
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam -= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_INT_LVAR_FROM_INT_VAR>() { // 0x066
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam -= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_FLOAT_LVAR_FROM_FLOAT_VAR>() { // 0x067
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam -= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_INT_VAR_BY_INT_VAR>() { // 0x068
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam *= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_FLOAT_VAR_BY_FLOAT_VAR>() { // 0x069
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam *= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_INT_LVAR_BY_INT_LVAR>() { // 0x06A
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam *= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_FLOAT_LVAR_BY_FLOAT_LVAR>() { // 0x06B
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam *= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_INT_VAR_BY_INT_LVAR>() { // 0x06C
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam *= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_FLOAT_VAR_BY_FLOAT_LVAR>() { // 0x06D
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam *= var2->fParam;
    return OR_CONTINUE;
}
*/
template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_INT_LVAR_BY_INT_VAR>() { // 0x06E
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam *= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_MULT_FLOAT_LVAR_BY_FLOAT_VAR>() { // 0x06F
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam *= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_INT_VAR_BY_INT_VAR>() { // 0x070
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam /= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_FLOAT_VAR_BY_FLOAT_VAR>() { // 0x071
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam /= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_INT_LVAR_BY_INT_LVAR>() { // 0x072
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam /= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_FLOAT_LVAR_BY_FLOAT_LVAR>() { // 0x073
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam /= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_INT_VAR_BY_INT_LVAR>() { // 0x074
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam /= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_FLOAT_VAR_BY_FLOAT_LVAR>() { // 0x075
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam /= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_INT_LVAR_BY_INT_VAR>() { // 0x076
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam /= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DIV_FLOAT_LVAR_BY_FLOAT_VAR>() { // 0x077
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam /= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_TIMED_VAL_TO_FLOAT_VAR>() { // 0x078
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    var->fParam += CTimer::GetTimeStep() * ScriptParams[0].fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_TIMED_VAL_TO_FLOAT_LVAR>() { // 0x079
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    var->fParam += CTimer::GetTimeStep() * ScriptParams[0].fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_TIMED_FLOAT_VAR_TO_FLOAT_VAR>() { // 0x07A
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam += CTimer::GetTimeStep() * var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_TIMED_FLOAT_LVAR_TO_FLOAT_LVAR>() { // 0x07B
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam += CTimer::GetTimeStep() * var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_TIMED_FLOAT_VAR_TO_FLOAT_LVAR>() { // 0x07C
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam += CTimer::GetTimeStep() * var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_TIMED_FLOAT_LVAR_TO_FLOAT_VAR>() { // 0x07D
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam += CTimer::GetTimeStep() * var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_TIMED_VAL_FROM_FLOAT_VAR>() { // 0x07E
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    var->fParam -= CTimer::GetTimeStep() * ScriptParams[0].fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_TIMED_VAL_FROM_FLOAT_LVAR>() { // 0x07F
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    var->fParam -= CTimer::GetTimeStep() * ScriptParams[0].fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_TIMED_FLOAT_VAR_FROM_FLOAT_VAR>() { // 0x080
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam -= CTimer::GetTimeStep() * var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_TIMED_FLOAT_LVAR_FROM_FLOAT_LVAR>() { // 0x081
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam -= CTimer::GetTimeStep() * var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_TIMED_FLOAT_VAR_FROM_FLOAT_LVAR>() { // 0x082
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam -= CTimer::GetTimeStep() * var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_TIMED_FLOAT_LVAR_FROM_FLOAT_VAR>() { // 0x083
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam -= CTimer::GetTimeStep() * var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_VAR_INT_TO_VAR_INT>() { // 0x084
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    *var1 = *var2;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_LVAR_INT_TO_LVAR_INT>() { // 0x085
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    *var1 = *var2;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_VAR_FLOAT_TO_VAR_FLOAT>() { // 0x086
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    *var1 = *var2;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_LVAR_FLOAT_TO_LVAR_FLOAT>() { // 0x087
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    *var1 = *var2;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_VAR_FLOAT_TO_LVAR_FLOAT>() { // 0x088
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    *var1 = *var2;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_LVAR_FLOAT_TO_VAR_FLOAT>() { // 0x089
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    *var1 = *var2;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_VAR_INT_TO_LVAR_INT>() { // 0x08A
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    *var1 = *var2;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_LVAR_INT_TO_VAR_INT>() { // 0x08B
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    *var1 = *var2;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CSET_VAR_INT_TO_VAR_FLOAT>() { // 0x08C
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam = static_cast<int32>(var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CSET_VAR_FLOAT_TO_VAR_INT>() { // 0x08D
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam = static_cast<float>(var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CSET_LVAR_INT_TO_VAR_FLOAT>() { // 0x08E
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam = static_cast<int32>(var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CSET_LVAR_FLOAT_TO_VAR_INT>() { // 0x08F
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam = static_cast<float>(var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CSET_VAR_INT_TO_LVAR_FLOAT>() { // 0x090
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam = static_cast<int32>(var2->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CSET_VAR_FLOAT_TO_LVAR_INT>() { // 0x091
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam = static_cast<float>(var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CSET_LVAR_INT_TO_LVAR_FLOAT>() { // 0x092
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam = static_cast<int32>(var2->fParam);
    return OR_CONTINUE;
}


template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CSET_LVAR_FLOAT_TO_LVAR_INT>() { // 0x093
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam = static_cast<float>(var2->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ABS_VAR_INT>() { // 0x094
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    var->iParam = std::abs(var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ABS_LVAR_INT>() { // 0x095
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    var->iParam = std::abs(var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ABS_VAR_FLOAT>() { // 0x096
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    var->fParam = std::abs(var->fParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ABS_LVAR_FLOAT>() { // 0x097
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    var->fParam = std::abs(var->fParam);
    return OR_CONTINUE;
}

/*
void GoToIfFalse(CRunningScript& S, int32 label) { // COMMAND_GOTO_IF_FALSE
    if (S.m_bCondResult) {
        S.UpdatePC(label);
    }
}
REGISTER_COMMAND_HANDLER(COMMAND_GOTO_IF_FALSE, GoToIfFalse);
*/

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DEBUG_ON>() { // 0x0C3
#ifndef FINAL
    CTheScripts::DbgFlag = true;
#endif
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_DEBUG_OFF>() { // 0x0C4
#ifndef FINAL
    CTheScripts::DbgFlag = false;
#endif
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_RETURN_TRUE>() { // 0x0C5
    UpdateCompareFlag(true);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_RETURN_FALSE>() { // 0x0C6
    UpdateCompareFlag(false);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SPECIAL_0>() { // 0x0B2 | NOTSA
    NOTSA_UNREACHABLE();
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SPECIAL_1>() { // 0x0B3 | NOTSA
    NOTSA_UNREACHABLE();
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SPECIAL_2>() { // 0x0B4 | NOTSA
    NOTSA_UNREACHABLE();
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SPECIAL_3>() { // 0x0B5 | NOTSA
    NOTSA_UNREACHABLE();
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SPECIAL_4>() { // 0x0B6 | NOTSA
    NOTSA_UNREACHABLE();
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SPECIAL_5>() { // 0x0B7 | NOTSA
    NOTSA_UNREACHABLE();
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SPECIAL_6>() { // 0x0B8 | NOTSA
    NOTSA_UNREACHABLE();
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SPECIAL_7>() { // 0x0B9 | NOTSA
    NOTSA_UNREACHABLE();
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_TERMINATE_THIS_SCRIPT>() { // 0x04E 
    if (m_bIsMission)
        CTheScripts::bAlreadyRunningAMissionScript = false;
    RemoveScriptFromList(&CTheScripts::pActiveScripts);
    AddScriptToList(&CTheScripts::pIdleScripts);
    ShutdownThisScript();
    return OR_WAIT;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_START_NEW_SCRIPT>() { // 0x04F
    CollectParameters(1);

    int32 offset = ScriptParams[0].iParam;
    if (offset < 0) // This doesn't make sense
        offset = COMMAND_START_NEW_SCRIPT; // For Mobile, offset is set to 0 here. WD fix perhaps?

    CRunningScript* script = CTheScripts::StartNewScript(&CTheScripts::ScriptSpace[offset]);
    ReadParametersForNewlyStartedScript(script);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GOSUB>() { // 0x050 
    CollectParameters(1);
    m_apStack[m_nSP++] = m_pCurrentIP;
    UpdatePC(ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_RETURN>() { // 0x051
    m_pCurrentIP = m_apStack[--m_nSP];
    return OR_CONTINUE;
}


template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_INT_VAR_TO_INT_VAR>() { // 0x058
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam += var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_FLOAT_VAR_TO_FLOAT_VAR>() { // 0x059
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam += var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_INT_LVAR_TO_INT_LVAR>() { // 0x05A
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam += var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_FLOAT_LVAR_TO_FLOAT_LVAR>() { // 0x05B
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam += var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_INT_VAR_TO_INT_LVAR>() { // 0x05C
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam += var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_FLOAT_VAR_TO_FLOAT_LVAR>() { // 0x05D
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam += var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_INT_LVAR_TO_INT_VAR>() { // 0x05E
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam += var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ADD_FLOAT_LVAR_TO_FLOAT_VAR>() { // 0x05F
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam += var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_INT_VAR_FROM_INT_VAR>() { // 0x060
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->iParam -= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_FLOAT_VAR_FROM_FLOAT_VAR>() { // 0x061
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_GLOBAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_GLOBAL);
    var1->fParam -= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_INT_LVAR_FROM_INT_LVAR>() { // 0x062
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->iParam -= var2->iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SUB_FLOAT_LVAR_FROM_FLOAT_LVAR>() { // 0x063
    tScriptParam* var1 = GetPointerToScriptVariable(VAR_LOCAL);
    tScriptParam* var2 = GetPointerToScriptVariable(VAR_LOCAL);
    var1->fParam -= var2->fParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_ANDOR>() { // 0x0D6
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
}


template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_GREATER_THAN_CONSTANT>() {
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam > ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_GREATER_THAN_CONSTANT>() {
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam > ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_CONSTANT_GREATER_THAN_INT_VAR>() {
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(ScriptParams[0].iParam > var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_CONSTANT_GREATER_THAN_INT_LVAR>() {
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(ScriptParams[0].iParam > var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_VAR_GREATER_OR_EQUAL_TO_CONSTANT>() {
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam >= ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_INT_LVAR_GREATER_OR_EQUAL_TO_CONSTANT>() {
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    UpdateCompareFlag(var->iParam >= ScriptParams[0].iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_CONSTANT_GREATER_OR_EQUAL_TO_INT_VAR>() {
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    UpdateCompareFlag(ScriptParams[0].iParam >= var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_CONSTANT_GREATER_OR_EQUAL_TO_INT_LVAR>() {
    CollectParameters(1);
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    UpdateCompareFlag(ScriptParams[0].iParam >= var->iParam);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_VAR_INT_TO_CONSTANT>() {
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    CollectParameters(1);
    var->iParam = ScriptParams[0].iParam;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_LVAR_INT_TO_CONSTANT>() {
    tScriptParam* var = GetPointerToScriptVariable(VAR_LOCAL);
    CollectParameters(1);
    var->iParam = ScriptParams[0].iParam;
    return OR_CONTINUE;
}
