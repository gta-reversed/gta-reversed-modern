/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "RenderWare.h"

struct RpHAnimBlendInterpFrame {
    RtQuat orientation;
    RwV3d translation;
};

VALIDATE_SIZE(RpHAnimBlendInterpFrame, 0x1C);