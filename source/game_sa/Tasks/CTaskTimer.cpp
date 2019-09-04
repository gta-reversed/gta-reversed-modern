/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

bool CTaskTimer::IsOutOfTime() {
    return ((bool(__thiscall*)(CTaskTimer*))0x420E30)(this);
}