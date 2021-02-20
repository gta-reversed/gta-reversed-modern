/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

/* This class is used to control 2 sounds as one. There are 2 sounds
   created with PlayTwinLoopSound(), and one of them is playing when second
   is simply muted. When time m_dwTimeToSwapSounds is reached, these sounds
   are switched: second starts playing, first begins being muted.
   The time m_dwTimeToSwapSounds is calcualated as:
   CAEAudioUtility::GetRandomNumberInRange(m_wPlayTimeMin, m_wPlayTimeMax);
   Notice these sounds must be situated in same bank slot.
   m_pBaseAudio is a pointer to audio which created twin sound. For example,
   this could be CAEVehicleAudioEntity for playing skid sounds.              */

#include "PluginBase.h"
#include "CAEAudioEntity.h"

class  CAETwinLoopSoundEntity : public CAEAudioEntity {
public:
    CAETwinLoopSoundEntity();
    CAETwinLoopSoundEntity(short wBankSlotId, short wSoundType1, short wSoundType2, CAEAudioEntity* pAudioEntity, short wPlayTimeMin, short wPlayTimeMax, short wStartingPlayPercent1, short wStartingPlayPercent2);

    ~CAETwinLoopSoundEntity();
public:
    short           m_nBankSlotId;
    short           m_nSoundType[2];
private:
    char _pad1[2];
public:
    CAEAudioEntity *m_pBaseAudio;
    short m_bIsInitialised;
    short field_8A;
    short field_8C;
    short           m_nPlayTimeMin;
    short           m_nPlayTimeMax;
private:
    char _pad2[2];
public:
    unsigned int    m_nTimeToSwapSounds;
    bool            m_bPlayingFirstSound;
private:
    char _pad3;
public:
    short           m_anStartingPlayPercentage[2]; // 0 - 99 percentage
    short field_9E;
    CAESound       *m_apSounds[2];
};

VALIDATE_SIZE(CAETwinLoopSoundEntity, 0xA8);
