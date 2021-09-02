/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CAEAudioEntity.h"
#include "CAESound.h"

enum eAudioPedType {
    PED_TYPE_GEN = 0,
    PED_TYPE_EMG = 1,
    PED_TYPE_PLAYER = 2,
    PED_TYPE_GANG = 3,
    PED_TYPE_GFD = 4,
    PED_TYPE_SPC = 5
};

class CAEPedSpeechAudioEntity : public CAEAudioEntity {
public:
    char      field_7C[20];
    char      field_90;
    char      field_91;
    int16     m_nVoiceType; // see eAudioPedType
    int16     m_nVoiceID;
    int16     m_nVoiceGender;
    char      field_98;
    bool      m_bEnableVocalType;
    bool      m_bMuted;
    char      m_nVocalEnableFlag;
    char      field_9C;
    char      field_9D;
    char      field_9E;
    char      field_9F;
    CAESound* m_pSound;
    int16     field_A4;
    int16     field_A6;
    int16     field_A8;
    int16     field_AA;
    float     m_fVoiceVolume;
    int16     m_nCurrentPhraseId;
    int16     field_B2;
    int32     field_B4[19];

public:
    static bool RequestPedConversation(CPed* ped1, CPed* ped2);
    static bool ReleasePedConversation();
};

VALIDATE_SIZE(CAEPedSpeechAudioEntity, 0x100);
