#pragma once

/*!
* Various utility commands
*/

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GENERATE_RANDOM_INT>() { // 0x099
    tScriptParam* var = GetPointerToScriptVariable(VAR_GLOBAL);
    var->iParam = CGeneral::GetRandomNumber();
    return OR_CONTINUE;
}

