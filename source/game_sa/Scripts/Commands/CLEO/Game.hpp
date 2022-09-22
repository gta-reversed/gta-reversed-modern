#pragma once

/*!
* Various CLEO game commands
*/

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_GAME_VERSION_ORIGINAL>() { // 0x0AA9
    CollectParameters(0);
    return OR_CONTINUE;
}

