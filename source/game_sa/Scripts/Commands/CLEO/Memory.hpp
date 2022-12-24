#pragma once

#include "app_debug.h"
#include "CommandParser/Parser.hpp"
/*!
* Various CLEO memory commands
*/

void WriteMemory(uint32 address, uint32 size, uint32 value, bool virtualProtect) {
    UNUSED(virtualProtect);

    DEV_LOG("write_memory addr {} size {} value {} virtual_protect {}", address, size, value, virtualProtect);
    memcpy(reinterpret_cast<void*>(address), &value, size);
}
REGISTER_COMMAND_HANDLER(COMMAND_WRITE_MEMORY, WriteMemory);

uint32 ReadMemory(uint32 address, uint32 size, bool virtualProtect) {
    UNUSED(virtualProtect);

    DEV_LOG("read_memory addr {} size {} virtual_protect {}", address, size, virtualProtect);
    switch (size) {
    case 4:
        return *reinterpret_cast<uint32*>(address);
    case 2:
        return *reinterpret_cast<uint16*>(address);
    case 1:
    default:
        return *reinterpret_cast<uint8*>(address);
    }
}
REGISTER_COMMAND_HANDLER(COMMAND_READ_MEMORY, ReadMemory);

CPed* GetPedPointer(CPed& ped) {
    return &ped;
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_PED_POINTER, GetPedPointer);

CVehicle* GetVehiclePointer(CVehicle& vehicle) {
    return &vehicle;
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_VEHICLE_POINTER, GetVehiclePointer);

CObject* GetObjectPointer(CObject& object) {
    return &object;
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_OBJECT_POINTER, GetObjectPointer);

CRunningScript* GetThisScriptStruct(CRunningScript* S) {
    return S;
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_THIS_SCRIPT_STRUCT, GetThisScriptStruct);

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CALL_FUNCTION>() { // 0x0AA5 (int32 address, int32 numParams, int32 pop, arguments funcParams)
    // perhaps this can't be ported to new-form?
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CALL_METHOD>() { // 0x0AA6 (int32 address, int32 struct, int32 numParams, int32 pop, arguments funcParams)
    // perhaps this can't be ported to new-form?
    CollectParameters(5);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CALL_FUNCTION_RETURN>() { // 0x0AA7 (int32 address, int32 numParams, int32 pop, arguments funcParams)
    // perhaps this can't be ported to new-form?
    CollectParameters(4);
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CALL_METHOD_RETURN>() { // 0x0AA8 (int32 address, int32 struct, int32 numParams, int32 pop, arguments funcParams)
    // perhaps this can't be ported to new-form?
    CollectParameters(5);
    return OR_CONTINUE;
}

const char* GetScriptStructNamed(CRunningScript* S) {
    NOTSA_UNREACHABLE("Not implemented!");
    S->m_bCondResult = false;

    return nullptr;
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_THIS_SCRIPT_STRUCT, GetScriptStructNamed);
