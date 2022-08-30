#pragma once

/*!
* Various CLEO world commands
*/

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_TARGET_BLIP_COORDS>() { // 0x0AB6
    CollectParameters(0);
    return OR_CONTINUE;
}

