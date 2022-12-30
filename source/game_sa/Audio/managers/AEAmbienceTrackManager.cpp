#include "StdInc.h"

#include "AEAmbienceTrackManager.h"
#include "AEAudioHardware.h"
#include "AEAudioUtility.h"

CAEAmbienceTrackManager& AEAmbienceTrackManager = *(CAEAmbienceTrackManager*)0x8AC15C;

void CAEAmbienceTrackManager::InjectHooks() {
    RH_ScopedClass(CAEAmbienceTrackManager);
    RH_ScopedCategory("Audio/Managers");

    RH_ScopedInstall(Reset, 0x4D6CA0);
    RH_ScopedInstall(IsAmbienceTrackActive, 0x4D6CF0);
    RH_ScopedInstall(IsAmbienceRadioActive, 0x4D6D40);
    RH_ScopedInstall(PlaySpecialMissionAmbienceTrack, 0x4D6D50);
    RH_ScopedInstall(StopSpecialMissionAmbienceTrack, 0x4D6D60);
    RH_ScopedInstall(UpdateAmbienceTrackAndVolume, 0x4D6E60, { .reversed = false });
    RH_ScopedInstall(Service, 0x4D76C0);
}

// 0x5B9660
bool CAEAmbienceTrackManager::Initialise(int32 channelId) {
    m_nChannel    = channelId;
    m_nTrackId    = -1;
    dword24       = -1;
    m_nState      = STATE_8;
    m_nVolume     = -100.0f;
    m_fFreqFactor = 1.0f;
    byte28        = 3;
    return true;
}

// 0x4D6CA0
void CAEAmbienceTrackManager::Reset() {
    m_nSpecialMissionAmbienceTrack = -1;
    m_bStop                        = false;
    m_bStopPrev                    = false;
    m_nTrackPlayTime               = -1;
    m_nTimeInMs                    = 0;
    m_b3                           = false;
    m_IsAmbienceRadioActive        = -1;
}

// 0x4D6CF0
bool CAEAmbienceTrackManager::IsAmbienceTrackActive() const {
    return m_nState != STATE_8;
}

// 0x4D6D40
bool CAEAmbienceTrackManager::IsAmbienceRadioActive() const {
    return m_IsAmbienceRadioActive >= 0;
}

// 0x4D6D50
void CAEAmbienceTrackManager::PlaySpecialMissionAmbienceTrack(eAudioEvents event) {
    m_nSpecialMissionAmbienceTrack = event;
}

// 0x4D6D60
void CAEAmbienceTrackManager::StopSpecialMissionAmbienceTrack() {
    switch (m_nState) {
    case STATE_0:
    case PLAY_TRACK:
    case START_TRACK_PLAYBACK:
    case SET_CHANNEL_VOLUME:
        m_nState = STOP_AMBIENCE_TRACK;
        break;
    }

    Reset();
}

// 0x4D6E60
void CAEAmbienceTrackManager::UpdateAmbienceTrackAndVolume() {
    return plugin::CallMethod<0x4D6E60, CAEAmbienceTrackManager*>(this);
}

// 0x4D76C0
void CAEAmbienceTrackManager::Service(int32 trackPlayTime) {
    if (
        !AudioEngine.IsCutsceneTrackActive()
        && !CTimer::GetIsPaused()
        && !FrontEndMenuManager.m_bMainMenuSwitch
    ) {
        UpdateAmbienceTrackAndVolume();
    }

    switch (m_nState) {
    case STATE_0:
        int32 random;

        if (m_b3) {
            random = 0;
        } else {
            if (m_nTrackPlayTime < 0) {
                random = CAEAudioUtility::GetRandomNumberInRange(0, 600000);
            } else {
                random = m_nTrackPlayTime;
                if (m_nTimeInMs)
                    random = CTimer::GetTimeInMS() - m_nTimeInMs + m_nTrackPlayTime;

                random = std::max(random, m_nTrackPlayTime + 7000);
            }
        }

        AEAudioHardware.PlayTrack(m_nTrackId, -1, random, byte28, false, false);
        m_nState = PLAY_TRACK;
        break;
    case PLAY_TRACK:
        if (trackPlayTime == -2) {
            m_nState = START_TRACK_PLAYBACK;
        }
        break;
    case START_TRACK_PLAYBACK:
        StartTrackPlayback();
        m_nState = SET_CHANNEL_VOLUME;
        break;
    case SET_CHANNEL_VOLUME:
        CheckForPause();
        AEAudioHardware.SetChannelVolume(m_nChannel, 0, m_nVolume, 0);
        break;
    case STOP_AMBIENCE_TRACK:
        if (m_nTrackId == m_nSpecialMissionAmbienceTrack) {
            m_nTrackPlayTime = -1;
            m_nTimeInMs = 0;
        } else {
            m_nTrackPlayTime = trackPlayTime;
            m_nTimeInMs = CTimer::GetTimeInMS();
        }
        m_nVolume = -100.0f;
        AEAudioHardware.StopTrack();
        m_nState = STOP_TRACK;
        break;
    case STATE_5:
        AEAudioHardware.StopSound(m_nChannel, 0);
        m_nState = STOP_SOUND;
        break;
    case STOP_SOUND:
        AEAudioHardware.StopTrack();
        m_nState = STOP_TRACK;
        break;
    case STOP_TRACK:
        if (trackPlayTime == -6) {
            m_nState = STATE_8;
        } else if (trackPlayTime == -7 || trackPlayTime == -2) {
            AEAudioHardware.StopTrack();
        }
        break;
    default:
        return;
    }
}

// 0x4D6CC0
void CAEAmbienceTrackManager::StopAmbienceTrack() {
    switch (m_nState) {
    case STATE_0:
    case PLAY_TRACK:
    case START_TRACK_PLAYBACK:
    case SET_CHANNEL_VOLUME:
        m_nState = STOP_AMBIENCE_TRACK;
        break;
    }

    m_bStop     = false;
    m_bStopPrev = false;
    m_b3        = false;
}

// 0x4D6DA0
void CAEAmbienceTrackManager::StartTrackPlayback() const {
    AEAudioHardware.DisableBassEq();
    AEAudioHardware.SetChannelVolume(m_nChannel, 0, m_nVolume, 0);
    AEAudioHardware.SetChannelFlags(m_nChannel, 0, 33);
    AEAudioHardware.StartTrackPlayback();
}

//  0x4D6DF0
void CAEAmbienceTrackManager::CheckForPause() const {
    float freqFactor = CTimer::GetIsPaused() || FrontEndMenuManager.m_bMainMenuSwitch ? 0.0f : m_fFreqFactor;
    AEAudioHardware.SetChannelFrequencyScalingFactor(m_nChannel, 0, freqFactor);
    AEAudioHardware.SetChannelFrequencyScalingFactor(m_nChannel, 0, freqFactor);
}
