#pragma once

/*!
* Various game realted commands
*/

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_SET_ALL_TAXIS_HAVE_NITRO>() {
    CollectParameters(1);
    if (ScriptParams[0].iParam) {
        CCheat::ApplyCheat(CHEAT_ALL_TAXIS_NITRO);
    }
    else {
        CCheat::Disable(CHEAT_ALL_TAXIS_NITRO);
    }
    return OR_CONTINUE;
}

