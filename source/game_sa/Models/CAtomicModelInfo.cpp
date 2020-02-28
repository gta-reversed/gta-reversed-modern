/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

void CAtomicModelInfo::SetAtomic(RpAtomic* atomic)
{
    ((void(__thiscall*)(CAtomicModelInfo*, RpAtomic*))plugin::GetVMT(this, 15))(this, atomic);
}

RpAtomic* CAtomicModelInfo::GetAtomicFromDistance(float distance)
{
    return ((RpAtomic * (__thiscall*)(CAtomicModelInfo*, float))0x4C44B0)(this, distance);
}