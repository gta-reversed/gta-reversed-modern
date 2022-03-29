#include "StdInc.h"

#include "AEFrontendAudioEntity.h"

#include "AETwinLoopSoundEntity.h"
#include "AEAudioHardware.h"
#include "AESoundManager.h"
#include "AEAudioUtility.h"
#include "AESound.h"

#include "config/eAudioBank.h"
#include "config/eSFX.h"
#include "config/eAudioSlot.h"

// 0x5B9AB0
void CAEFrontendAudioEntity::Initialise() {
    m_bAmplifierWakeUp = false;
    m_pAmplifierWakeUp = nullptr;

    AEAudioHardware.LoadSoundBank(BANK_FRONTEND, SLOT_FRONTEND);
    AEAudioHardware.LoadSoundBank(BANK_EXTRAS, SLOT_EXTRAS);
    AEAudioHardware.LoadSoundBank(BANK_WEAPON_BULLET_SWISH, SLOT_WEAPON_BULLET_SWISH);

    m_nbLoadingTuneSeed = CAEAudioUtility::GetRandomNumberInRange(0, 3);
    AEAudioHardware.LoadSound(BANK_LOADING_TUNE, 2 * m_nbLoadingTuneSeed + 0, SLOT_LOADING_TUNE_LEFT);
    AEAudioHardware.LoadSound(BANK_LOADING_TUNE, 2 * m_nbLoadingTuneSeed + 1, SLOT_LOADING_TUNE_RIGHT);
}

// 0x4DD440
void CAEFrontendAudioEntity::Reset() {
    m_nLastFrameGeneral_or_nFrameCount = 0;
    m_nLastFrameMissionComplete        = 0;
    m_nLastFrameBulletPass             = 0;
    m_nNumBulletSounds                 = 0;
    m_f7E                              = -1;
    AESoundManager.CancelSoundsOfThisEventPlayingForThisEntity(AE_FRONTEND_SCANNER_NOISE_START, this);
}

// 0x4DD4A0
void CAEFrontendAudioEntity::AddAudioEvent(int32 eventCode, float fVolumeBoost, float fSpeed) {
    plugin::CallMethod<0x4DD4A0, CAEFrontendAudioEntity*, int32, float, float>(this, eventCode, fVolumeBoost, fSpeed);
}

// 0x4DD480
bool CAEFrontendAudioEntity::IsRadioTuneSoundActive() {
    if (CTimer::GetIsPaused())
        return m_objRetunePaused.m_bIsInitialised;
    else
        return m_objRetune.m_bIsInitialised;
}

// 0x4DD470
bool CAEFrontendAudioEntity::IsLoadingTuneActive() {
    return AESoundManager.AreSoundsOfThisEventPlayingForThisEntity(AE_FRONTEND_LOADING_TUNE_START, this);
}

// 0x4DEDA0
void CAEFrontendAudioEntity::UpdateParameters(CAESound* sound, int16 curPlayPos) {
    if (!sound)
        return;

    const float REAR = curPlayPos * 0.0028571428f + curPlayPos * 0.0028571428f - 1.0f;
    const float FRONT = 1.0f - (curPlayPos * 0.0028571428f + curPlayPos * 0.0028571428f);

    const auto BulletSound = [&](const float x, const float z) {
        if (curPlayPos >= 0 && curPlayPos <= 350) {
            sound->SetPosition({-0.1f, 0.0f, REAR});
        }
    };

    switch (sound->m_nEvent) {
    case AE_FRONTEND_CAR_RESPRAY:
        if (curPlayPos > 0) {
            if (!(CTimer::GetTimeInMS() <= m_nLastTimeCarRespray + 1900))
                sound->StopSoundAndForget();
        }
        break;
    case AE_FRONTEND_BULLET_PASS_LEFT_REAR:
        BulletSound(-0.1f, REAR);
        break;
    case AE_FRONTEND_BULLET_PASS_LEFT_FRONT:
        BulletSound(-0.1f, FRONT);
        break;
    case AE_FRONTEND_BULLET_PASS_RIGHT_REAR:
        BulletSound(0.1f, REAR);
        break;
    case AE_FRONTEND_BULLET_PASS_RIGHT_FRONT:
        BulletSound(0.1f, FRONT);
        break;
    case AE_FRONTEND_TIMER_COUNT:
        if (curPlayPos > 0) {
            if (!(CTimer::GetTimeInMS() <= m_nLatestTimerCount + 100))
                sound->StopSoundAndForget();
        }
        break;
    default:
        break;
    }

    if (sound == m_pAmplifierWakeUp && curPlayPos == -1) {
        m_pAmplifierWakeUp = nullptr;
        m_bAmplifierWakeUp = false;
    }
}

void CAEFrontendAudioEntity::InjectHooks() {
    RH_ScopedClass(CAEFrontendAudioEntity);
    RH_ScopedCategory("Audio/Entities");

    RH_ScopedInstall(Initialise, 0x5B9AB0);
    RH_ScopedInstall(Reset, 0x4DD440);
    // RH_ScopedInstall(AddAudioEvent, 0x4DD4A0);
    RH_ScopedInstall(IsRadioTuneSoundActive, 0x4DD480);
    RH_ScopedInstall(IsLoadingTuneActive, 0x4DD470);
    RH_ScopedVirtualInstall(UpdateParameters, 0x4DEDA0);
}

void CAEFrontendAudioEntity::UpdateParameters_Reversed(CAESound* sound, int16 curPlayPos) {
    CAEFrontendAudioEntity::UpdateParameters(sound, curPlayPos);
}
