#pragma once

/*!
* Various CLEO car commands
*/



template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_CAR_NUMBER_OF_GEARS>() { // 0x0AB7 (Car self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_CAR_CURRENT_GEAR>() { // 0x0AB8 (Car self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_CAR_SIREN_ON>() { // 0x0ABD (Car self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_IS_CAR_ENGINE_ON>() { // 0x0ABE (Car self)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CLEO_SET_CAR_ENGINE_ON>() { // 0x0ABF (Car self, bool state)
    CollectParameters(2);
    return OR_CONTINUE;
}

