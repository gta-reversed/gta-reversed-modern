#pragma once

class CAEAmbienceTrackManager {
public:
    enum State : int32 {
        STATE_0              = 0,
        PLAY_TRACK           = 1,
        START_TRACK_PLAYBACK = 2,
        SET_CHANNEL_VOLUME   = 3,
        STOP_AMBIENCE_TRACK  = 4,
        STATE_5              = 5,
        STOP_SOUND           = 6,
        STOP_TRACK           = 7,
        STATE_8              = 8,
    };

    bool   m_bStop;
    bool   m_bStopPrev;
    bool   m_b3;
    int8   m_IsAmbienceRadioActive;
    int32  m_nChannel;
    State  m_nState;
    int32  m_nSpecialMissionAmbienceTrack;
    int32  m_nTrackPlayTime;
    uint32 m_nTimeInMs;
    float  m_nVolume;
    float  m_fFreqFactor;
    int32  m_nTrackId;
    int32  dword24;
    int8   byte28;

public:
    static void InjectHooks();

    bool Initialise(int32 channelId);
    void Reset();

    void CheckForPause() const;

    void StopAmbienceTrack();
    [[nodiscard]] bool IsAmbienceRadioActive() const;
    void UpdateAmbienceTrackAndVolume();

    [[nodiscard]] bool IsAmbienceTrackActive() const;

    void PlaySpecialMissionAmbienceTrack(eAudioEvents event);
    void StopSpecialMissionAmbienceTrack();

    void Service(int32 trackPlayTime);
    void StartTrackPlayback() const;
};

VALIDATE_SIZE(CAEAmbienceTrackManager, 0x2C);

extern CAEAmbienceTrackManager& AEAmbienceTrackManager;
