/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "AEAudioEntity.h"
#include "AESound.h"
#include "AETwinLoopSoundEntity.h"

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
    void AddAudioEvent(int32 audioEventVolumeIndex, float volume, float speed, CPhysical* physical = nullptr, uint8 arg5 = 0, int32 arg7 = 0, uint32 arg8 = 0);
    void Terminate();
    static void StaticInitialise();
};

VALIDATE_SIZE(CAEPedAudioEntity, 0x15C);
