/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CBox.h"

class CTimeCycleBox {
public:
    CBox  box;
    int16 farclip;
    uint8 lodDistMult;
    int32 extraColor;
    float strength;
    float falloff;
};

VALIDATE_SIZE(CTimeCycleBox, 0x28);