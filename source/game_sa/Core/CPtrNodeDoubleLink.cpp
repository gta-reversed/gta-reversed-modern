/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

// Converted from cdecl void* CPtrNodeDoubleLink::operator new(uint size) 0x5523C0
void* CPtrNodeDoubleLink::operator_new() {
    return plugin::CallAndReturn<void*, 0x5523C0>();
}

// Converted from cdecl void CPtrNodeDoubleLink::operator delete(void *data) 0x5523D0
void CPtrNodeDoubleLink::operator delete(void* data) {
    plugin::Call<0x5523D0, void*>(data);
}