/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Audio/entities/CAEAudioEntity.h"
#include "CAESound.h"
#include "Audio/entities/CAETwinLoopSoundEntity.h"

class CPed;

class CAEPedAudioEntity : public CAEAudioEntity {
public:
    char                   field_7C;
    char                   field_7D;
    int16                  field_7E;
    int32                  field_80;
    float                  field_84;
    float                  field_88;
    char                   field_8C[8];
    CPed*                  m_pPed;
    char                   field_98;
    char                   field_99[3];
    CAESound*              field_9C;
    int32                  field_A0;
    CAESound*              field_A4;
    CAETwinLoopSoundEntity m_sTwinLoopSoundEntity;
    CAESound*              field_150;
    float                  field_154;
    float                  field_158;

public:
    void AddAudioEvent(int32 audioEventVolumeIndex, float a3, float a4, int32 argC, int32 a5, int32 a7, int32 a8);
};

VALIDATE_SIZE(CAEPedAudioEntity, 0x15C);
