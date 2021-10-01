/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "AEAudioEntity.h"

class CAEExplosionAudioEntity : public CAEAudioEntity {
public:
    char field_7C;
    char _pad7D[3];

public:
    static void StaticInitialise();
};

VALIDATE_SIZE(CAEExplosionAudioEntity, 0x80);