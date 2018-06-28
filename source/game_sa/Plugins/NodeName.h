/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "RenderWare.h"

bool NodeNamePluginAttach();
void SetFrameNodeName(RwFrame* frame, char const* name);
char* GetFrameNodeName(RwFrame* frame);