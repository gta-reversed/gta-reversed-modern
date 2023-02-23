#pragma once

/*!
* Various utility commands
*/

void GenerateRandomInt(CRunningScript* S) {
    S->GetPointerToScriptVariable(VAR_GLOBAL)->iParam = CGeneral::GetRandomNumber();
}
REGISTER_COMMAND_HANDLER(COMMAND_GENERATE_RANDOM_INT, GenerateRandomInt);
