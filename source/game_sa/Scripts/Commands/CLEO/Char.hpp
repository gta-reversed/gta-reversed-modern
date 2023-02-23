#pragma once

/*!
* Various utility commands
*/

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_STORE_CLOSEST_ENTITIES>() { // 0x0AB5 (Char self)
    CollectParameters(1);
    return OR_CONTINUE;
}

