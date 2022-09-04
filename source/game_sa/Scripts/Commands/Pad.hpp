#pragma once

/*!
* Various player pad commands
*/

/**/
template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_BUTTON_PRESSED>() { // 0x00E1 (Pad touch, TouchPoints touchPoints)
    CollectParameters(2);
    return OR_CONTINUE;
}

/*
template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_KEY_PRESSED>() { // 0x0AB0 (KeyCode keyCode)
    CollectParameters(1);
    return OR_CONTINUE;
}
*/
