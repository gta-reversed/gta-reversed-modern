/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RGBA.h"

struct tPickupMessage {
public:
    CVector pos;
    float   width;
    float   height;
    CRGBA   color;
    uint8   flags;
    char    field_19;
    char    _pad1A[2];
    uint32  price;
    char*   messageText;
};

VALIDATE_SIZE(tPickupMessage, 0x24);