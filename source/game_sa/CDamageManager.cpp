#include "StdInc.h"

unsigned int CDamageManager::GetWheelStatus(int wheel)
{
    return ((unsigned int(__thiscall*)(CDamageManager*, int))0x6C21B0)(this, wheel);
}
