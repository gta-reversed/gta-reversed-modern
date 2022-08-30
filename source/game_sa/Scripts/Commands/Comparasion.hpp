#pragma once

/*!
* Comparasion commands
*/

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
