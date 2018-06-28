/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CAEAudioEntity.h"
#include "CAESound.h"
#include "CAETwinLoopSoundEntity.h"

class CPed;

class  CAEPedAudioEntity : public CAEAudioEntity {
public:
    char field_7C;
    char field_7D;
    short field_7E;
    int field_80;
    float field_84;
    float field_88;
    char field_8C[8];
    CPed *m_pPed;
    char field_98;
    char field_99[3];
    CAESound *field_9C;
    int field_A0;
    CAESound *field_A4;
	CAETwinLoopSoundEntity TwinLoopSoundEntity;
    CAESound *field_150;
    float field_154;
    float field_158;
};

VALIDATE_SIZE(CAEPedAudioEntity, 0x15C);
