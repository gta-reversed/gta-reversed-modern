/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

/* This class is used to control 2 sounds as one. There are 2 sounds
   created with PlayTwinLoopSound(), and one of them is playing when second
   is simply muted. When time m_nTimeToSwapSounds is reached, these sounds
   are switched: second starts playing, first begins being muted.
   The time m_nTimeToSwapSounds is calculated as:
   CAEAudioUtility::GetRandomNumberInRange(m_nPlayTimeMin, m_nPlayTimeMax);
   Notice these sounds must be situated in same bank slot.
   m_pBaseAudio is a pointer to audio which created twin sound. For example,
   this could be CAEVehicleAudioEntity for playing skid sounds.              */

#include "CAEAudioEntity.h"

class CAETwinLoopSoundEntity : public CAEAudioEntity {
public:
    short           m_nBankSlotId;
    short           m_nSoundId1;
    short           m_nSoundId2;
    // char            _pad1[2];
    CAEAudioEntity* m_pBaseAudio;
    short           m_bIsInitialised;
    short           unused_field_8A;
    short           unused_field_8C;
    unsigned short  m_nPlayTimeMin;
    unsigned short  m_nPlayTimeMax;
    // char            _pad2[2];
    unsigned int    m_nTimeToSwapSounds;
    bool            m_bPlayingFirstSound;
    // char            _pad3;
    short           m_nSoundPlayStart1; // 0 - 99 percentage
    short           m_nSoundPlayStart2; // 0 - 99 percentage
    // short           _pad_field_9E;
    CAESound*       m_pSound1;
    CAESound*       m_pSound2;

public:
    CAETwinLoopSoundEntity();
    CAETwinLoopSoundEntity(short bank, short soundType1, short soundType2, CAEAudioEntity* audio, ushort minTime, ushort maxTime, short sfxPlayStart1, short sfxPlayStart2);

    ~CAETwinLoopSoundEntity();

    void Initialise(short bank, short sfx1, short sfx2, CAEAudioEntity* audio, ushort minTime, ushort maxTime, short sfxPlayStart1, short sfxPlayStart2);

    void UpdateParameters(CAESound* sound, short curPlayPos) override;

    void UpdateTwinLoopSound(CVector posn, float volume, float speed);
    void SwapSounds();
    void StopSound();
    void StopSoundAndForget();

    float GetEmittedVolume();
    void SetEmittedVolume(float volume);

    bool IsTwinLoopPlaying();
    bool DoSoundsSwitchThisFrame();

    void PlayTwinLoopSound(CVector posn, float volume, float speed, float maxDistance, float timeScale, eSoundEnvironment flags);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    void UpdateParameters_Reversed(CAESound* sound, short curPlayPos);
};

VALIDATE_SIZE(CAETwinLoopSoundEntity, 0xA8);
