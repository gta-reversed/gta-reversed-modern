#include "StdInc.h"

unsigned int CDamageManager::GetWheelStatus(int wheel)
{
    return ((unsigned int(__thiscall*)(CDamageManager*, int))0x6C21B0)(this, wheel);
}

void CDamageManager::SetEngineStatus(uint32_t status) {
    plugin::CallMethod<0x6C22A0, CDamageManager*, uint32_t>(this, status);
}

uint32_t CDamageManager::GetEngineStatus() {
    return plugin::CallMethodAndReturn<uint32_t, 0x6C22C0, CDamageManager*>(this);
}

