/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

// Converted from cdecl bool NodeNamePluginAttach(void) 0x72FAB0
bool NodeNamePluginAttach() {
    return ((bool(__cdecl*)())0x72FAB0)();
}

// Converted from cdecl void SetFrameNodeName(RwFrame *frame,char const*name) 0x72FB00
void SetFrameNodeName(RwFrame* frame, char const* name) {
    ((void(__cdecl*)(RwFrame*, char const*))0x72FB00)(frame, name);
}

// Converted from cdecl char* GetFrameNodeName(RwFrame *frame) 0x72FB30
char* GetFrameNodeName(RwFrame* frame) {
    return ((char* (__cdecl*)(RwFrame*))0x72FB30)(frame);
}