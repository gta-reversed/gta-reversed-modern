/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include "CVector.h"

class FxMemoryPool_c {
public:
    char*  data;
    uint32 size;
    uint32 position;

    void Optimise();
};

VALIDATE_SIZE(FxMemoryPool_c, 0xC);