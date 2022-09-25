#pragma once

/*!
* Various CLEO memory commands
*/


template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_WRITE_MEMORY>() { // 0x0A8C (int32 address, int32 size, any value, bool vp)
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_READ_MEMORY>() { // 0x0A8D (int32 address, int32 size, bool vp)
    CollectParameters(3);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_PED_POINTER>() { // 0x0A96 (Char char)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_VEHICLE_POINTER>() { // 0x0A97 (Car vehicle)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_OBJECT_POINTER>() { // 0x0A98 (Object object)
    CollectParameters(1);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_THIS_SCRIPT_STRUCT>() { // 0x0A9F
    CollectParameters(0);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CALL_FUNCTION>() { // 0x0AA5 (int32 address, int32 numParams, int32 pop, arguments funcParams)
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CALL_METHOD>() { // 0x0AA6 (int32 address, int32 struct, int32 numParams, int32 pop, arguments funcParams)
    CollectParameters(5);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CALL_FUNCTION_RETURN>() { // 0x0AA7 (int32 address, int32 numParams, int32 pop, arguments funcParams)
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CALL_METHOD_RETURN>() { // 0x0AA8 (int32 address, int32 struct, int32 numParams, int32 pop, arguments funcParams)
    CollectParameters(5);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_GET_SCRIPT_STRUCT_NAMED>() { // 0x0AAA (string scriptName)
    CollectParameters(1);
    return OR_CONTINUE;
}

