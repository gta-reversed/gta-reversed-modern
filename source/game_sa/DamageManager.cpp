#include "StdInc.h"

uint32 CDamageManager::GetWheelStatus(int32 wheel)
{
    return ((uint32(__thiscall*)(CDamageManager*, int32))0x6C21B0)(this, wheel);
}

void CDamageManager::SetEngineStatus(uint32_t status) {
    plugin::CallMethod<0x6C22A0, CDamageManager*, uint32_t>(this, status);
}

uint32_t CDamageManager::GetEngineStatus() {
    return plugin::CallMethodAndReturn<uint32_t, 0x6C22C0, CDamageManager*>(this);
}

