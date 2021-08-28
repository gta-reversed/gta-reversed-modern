#include "StdInc.h"

#include "CAEAudioUtility.h"
#include "CAESoundManager.h"

// 0x4F63B0
CAETwinLoopSoundEntity::CAETwinLoopSoundEntity() : CAEAudioEntity() {
    m_bIsInitialised = 0;
    m_pSound1 = nullptr;
    m_pSound2 = nullptr;
}

// 0x4F2AE0
CAETwinLoopSoundEntity::CAETwinLoopSoundEntity(short bankSlotId, short soundType1, short soundType2, CAEAudioEntity* audio, uint16_t minTime, uint16_t maxTime, short sfxPlayStart1, short sfxPlayStart2) : CAEAudioEntity() {
    Initialise(bankSlotId, soundType1, soundType2, audio, minTime, maxTime, sfxPlayStart1, sfxPlayStart2);
}

// 0x4F2B80
CAETwinLoopSoundEntity::~CAETwinLoopSoundEntity() {
    if (!m_bIsInitialised)
        return;

    StopSoundAndForget();

    m_bIsInitialised = 0;
}

// 0x4F28A0
void CAETwinLoopSoundEntity::Initialise(short bankSlotId, short sfx1, short sfx2, CAEAudioEntity* audio, uint16_t minTime, uint16_t maxTime, short sfxPlayStart1, short sfxPlayStart2) {
    m_nBankSlotId        = bankSlotId;
    m_nSoundId1          = sfx1;
    m_nSoundId2          = sfx2;
    m_pBaseAudio         = audio;
    m_nPlayTimeMin       = minTime;
    m_nPlayTimeMax       = maxTime;
    m_nSoundPlayStart1   = sfxPlayStart1;
    m_nSoundPlayStart2   = sfxPlayStart2;
    unused_field_8A      = -1;
    unused_field_8C      = -1;
    m_pSound1            = nullptr;
    m_pSound2            = nullptr;
    m_bPlayingFirstSound = true;
    m_bIsInitialised     = 1;
}

// 0x4F29A0
void CAETwinLoopSoundEntity::UpdateTwinLoopSound(CVector posn, float volume, float speed) {
    if (m_pSound1) {
        m_pSound1->SetPosition(posn);
        if (m_bPlayingFirstSound)
            m_pSound1->m_fVolume = volume;

        m_pSound1->m_fSpeed = speed;
    }

    if (m_pSound2) {
        m_pSound2->SetPosition(posn);
        if (!m_bPlayingFirstSound)
            m_pSound2->m_fVolume = volume;

        m_pSound2->m_fSpeed = speed;
    }
}

// 0x4F2E90
void CAETwinLoopSoundEntity::UpdateParameters(CAESound* sound, short curPlayPos) {
    if (curPlayPos == -1) {
        if (sound == m_pSound1)
            m_pSound1 = nullptr;

        if (sound == m_pSound2)
            m_pSound2 = nullptr;
    }

    if (sound == m_pSound1 && CTimer::m_snTimeInMillisecondsPauseMode > m_nTimeToSwapSounds)
        SwapSounds();
}

// 0x4F2C10
void CAETwinLoopSoundEntity::SwapSounds() {
    if (m_pSound1 && m_pSound2) {
        if (m_bPlayingFirstSound) {
            m_pSound2->m_fVolume = m_pSound1->m_fVolume;
            m_pSound1->m_fVolume = -100.0f;
            m_bPlayingFirstSound = false;
        } else {
            m_pSound1->m_fVolume = m_pSound2->m_fVolume;
            m_pSound2->m_fVolume = -100.0f;
            m_bPlayingFirstSound = true;
        }
        m_nTimeToSwapSounds = CTimer::m_snTimeInMillisecondsPauseMode + CAEAudioUtility::GetRandomNumberInRange(m_nPlayTimeMin, m_nPlayTimeMax);
    }
}

// unused
// 0x4F2930
void CAETwinLoopSoundEntity::StopSound() {
    if (m_pSound1)
        m_pSound1->StopSound();

    if (m_pSound2)
        m_pSound2->StopSound();
}

// 0x4F2960
void CAETwinLoopSoundEntity::StopSoundAndForget() {
    if (m_pSound1) {
        m_pSound1->StopSoundAndForget();
        m_pSound1 = nullptr;
    }

    if (m_pSound2) {
        m_pSound2->StopSoundAndForget();
        m_pSound2 = nullptr;
    }

    m_bIsInitialised = 0;
}

// unused
// 0x4F2A80
float CAETwinLoopSoundEntity::GetEmittedVolume() {
    if (m_pSound1 && m_bPlayingFirstSound)
    {
        return m_pSound1->m_fVolume;
    }
    else if (m_pSound2 != nullptr && !m_bPlayingFirstSound)
    {
        return m_pSound2->m_fVolume;
    }
    else return -100.0f;
}

// unused
// 0x4F2A40
void CAETwinLoopSoundEntity::SetEmittedVolume(float volume) {
    if (m_pSound1 && m_bPlayingFirstSound)
        m_pSound1->m_fVolume = volume;

    if (m_pSound2 && !m_bPlayingFirstSound)
        m_pSound2->m_fVolume = volume;
}

// unused
// 0x4F2AC0
bool CAETwinLoopSoundEntity::IsTwinLoopPlaying() {
    return m_pSound1 || m_pSound2;
}

// 0x4F2CA0
bool CAETwinLoopSoundEntity::DoSoundsSwitchThisFrame() {
    return CTimer::m_snTimeInMillisecondsPauseMode > m_nTimeToSwapSounds;
}

// 0x4F2CB0
void CAETwinLoopSoundEntity::PlayTwinLoopSound(CVector posn, float volume, float speed, float maxDistance, float timeScale, eSoundEnvironment flags) {
    if (m_pSound1)
        m_pSound1->StopSoundAndForget();

    if (m_pSound2)
        m_pSound2->StopSoundAndForget();

    eSoundEnvironment envFlags = static_cast<eSoundEnvironment>(flags | SOUND_REQUEST_UPDATES | SOUND_REQUEST_UPDATES);

    CAESound sound;
    sound.Initialise(m_nBankSlotId, m_nSoundId1, this, posn, volume, maxDistance, speed, timeScale, 0, envFlags, 0.0f, 0);
    sound.m_nCurrentPlayPosition = m_nSoundPlayStart1 == -1 ? CAEAudioUtility::GetRandomNumberInRange(0, 99) : m_nSoundPlayStart1;
    m_pSound1 = AESoundManager.RequestNewSound(&sound);

    sound.Initialise(m_nBankSlotId, m_nSoundId2, this, posn, -100.0f, maxDistance, speed, timeScale, 0, envFlags, 0.0f, 0);
    sound.m_nCurrentPlayPosition = m_nSoundPlayStart2 == -1 ? CAEAudioUtility::GetRandomNumberInRange(0, 99) : m_nSoundPlayStart2;
    m_pSound2 = AESoundManager.RequestNewSound(&sound);

    m_nTimeToSwapSounds = CTimer::m_snTimeInMillisecondsPauseMode + CAEAudioUtility::GetRandomNumberInRange(m_nPlayTimeMin, m_nPlayTimeMax);
    m_bPlayingFirstSound = true;
}

void CAETwinLoopSoundEntity::UpdateParameters_Reversed(CAESound* sound, short curPlayPos) {
    CAETwinLoopSoundEntity::UpdateParameters(sound, curPlayPos);
}

void CAETwinLoopSoundEntity::InjectHooks() {
    ReversibleHooks::Install("CAETwinLoopSoundEntity", "Initialise", 0x4F28A0, &CAETwinLoopSoundEntity::Initialise);
    ReversibleHooks::Install("CAETwinLoopSoundEntity", "UpdateTwinLoopSound", 0x4F29A0, &CAETwinLoopSoundEntity::UpdateTwinLoopSound);
    ReversibleHooks::Install("CAETwinLoopSoundEntity", "UpdateParameters", 0x4F2E90, &CAETwinLoopSoundEntity::UpdateParameters_Reversed);
    ReversibleHooks::Install("CAETwinLoopSoundEntity", "SwapSounds", 0x4F2C10, &CAETwinLoopSoundEntity::SwapSounds);
    ReversibleHooks::Install("CAETwinLoopSoundEntity", "StopSoundAndForget", 0x4F2960, &CAETwinLoopSoundEntity::StopSoundAndForget);
    ReversibleHooks::Install("CAETwinLoopSoundEntity", "PlayTwinLoopSound", 0x4F2CB0, &CAETwinLoopSoundEntity::PlayTwinLoopSound);
    ReversibleHooks::Install("CAETwinLoopSoundEntity", "DoSoundsSwitchThisFrame", 0x4F2CA0, &CAETwinLoopSoundEntity::DoSoundsSwitchThisFrame);
}
