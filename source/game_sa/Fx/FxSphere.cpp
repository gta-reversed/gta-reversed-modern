/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

// 0x4A9F70
FxSphere_c::FxSphere_c() {
    ((void(__thiscall*)(FxSphere_c*))0x4A9F70)(this);
}

// 0x4A9F80
void* FxSphere_c::operator new(uint32 size, int32 notAligned) {
    return ((void* (__cdecl*)(uint32, int32))0x4A9F80)(size, notAligned);
}

// 0x4A9FB0
void FxSphere_c::operator delete(void* data) {
    ((void(__cdecl*)(void*))0x4A9FB0)(data);
}

// 0x4A9FC0
bool FxSphere_c::IsCollision(FxSphere_c* sphere) {
    return ((bool(__thiscall*)(FxSphere_c*, FxSphere_c * sphere))0x4A9FC0)(this, sphere);
}

// 0x4AA010
float FxSphere_c::GetDistToPlane(FxPlane_c* plane) {
    return ((float(__thiscall*)(FxSphere_c*, FxPlane_c*))0x4AA010)(this, plane);
}