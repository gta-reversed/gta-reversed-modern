/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

// Converted from thiscall void FxSphere_c::FxSphere_c(void) 0x4A9F70
FxSphere_c::FxSphere_c() {
    ((void(__thiscall*)(FxSphere_c*))0x4A9F70)(this);
}

// Converted from cdecl void* FxSphere_c::operator new(uint32 size,int notAligned) 0x4A9F80
void* FxSphere_c::operator new(unsigned int size, int notAligned) {
    return ((void* (__cdecl*)(unsigned int, int))0x4A9F80)(size, notAligned);
}

// Converted from cdecl void FxSphere_c::operator delete(void *data) 0x4A9FB0
void FxSphere_c::operator delete(void* data) {
    ((void(__cdecl*)(void*))0x4A9FB0)(data);
}

// Converted from thiscall bool FxSphere_c::IsCollision(FxSphere_c* sphere) 0x4A9FC0
bool FxSphere_c::IsCollision(FxSphere_c* sphere) {
    return ((bool(__thiscall*)(FxSphere_c*, FxSphere_c * sphere))0x4A9FC0)(this, sphere);
}

// Converted from thiscall float FxSphere_c::GetDistToPlane(FxPlane_c *plane) 0x4AA010
float FxSphere_c::GetDistToPlane(FxPlane_c* plane) {
    return ((float(__thiscall*)(FxSphere_c*, FxPlane_c*))0x4AA010)(this, plane);
}