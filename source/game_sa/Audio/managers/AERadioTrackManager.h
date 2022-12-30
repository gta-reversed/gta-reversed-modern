/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

enum {
    TYPE_INDENT      = 0,
    TYPE_ADVERT      = 1,
    TYPE_DJ_BANTER   = 2,
    TYPE_INTRO       = 3,
    TYPE_TRACK       = 4,
    TYPE_OUTRO       = 5,
    TYPE_NONE        = 6,
    TYPE_USER_TRACK  = 7,
};

struct tRadioSettings {
    int32 m_aTrackQueue[5];
    int32 m_iCurrentTrackID;
    int32 m_iPrevTrackID;
    int32 m_iTrackPlayTime;
    int32 m_iTrackLengthMs;
    int8  m_f24;
    int8  m_nCurrentRadioStation;
    int8  m_nBassSet;
    float m_fBassGain;
    int8  m_aTrackTypes[5];
    int8  m_iCurrentTrackType;
    int8  m_iPrevTrackType;
    int8  m_aTrackIndexes[5];
    int8  m_iCurrentTrackIndex;
    int8  m_iPrevTrackIndex;

    void Reset() {
        for (auto i = 0u; i < std::size(m_aTrackQueue); i++) {
            m_aTrackQueue[i]   = -1;
            m_aTrackTypes[i]   = TYPE_NONE;
            m_aTrackIndexes[i] = -1;
        }
    }
};

VALIDATE_SIZE(tRadioSettings, 0x3C);

struct tRadioState {
    int32 m_aElapsed[3];
    int32 m_iTimeInPauseModeInMs;
    int32 m_iTimeInMs;
    int32 m_iTrackPlayTime;
    int32 m_aTrackQueue[3];
    int8  m_aTrackTypes[3];
    uint8 m_nGameClockDays;
    uint8 m_nGameClockHours;
};

VALIDATE_SIZE(tRadioState, 0x2C);

struct tMusicTrackHistory {
    int8 historyIndices[20];
};

typedef int8 RadioStationId;

class CAERadioTrackManager {
public:
    bool           m_bInitialised;
    bool           m_bDisplayStationName;
    char           m_prev;
    bool           m_bEnabledInPauseMode;
    bool           m_bBassEnhance;
    bool           m_bPauseMode;
    bool           m_bRetuneJustStarted;
    bool           m_bRadioAutoSelect;
    uint8          m_nTracksInARow[RADIO_COUNT];
    uint8          m_nSavedGameClockDays;
    uint8          m_nSavedGameClockHours;
    int32          m_aListenTimes[RADIO_COUNT];
    uint32         m_nTimeRadioStationRetuned;
    uint32         m_nTimeToDisplayRadioName;
    uint32         m_nSavedTimeMs;
    uint32         m_nRetuneStartedTime;
    uint32         field_60;
    int32          m_nChannel;
    int32          m_nMode;
    int32          m_nStationsListed;
    int32          m_nStationsListDown;
    int32          m_nSavedRadioStationId;
    int8           m_iRadioStationMenuRequest;
    int8           m_iRadioStationRequest;
    int32          field_7C;
    float          m_f80; // 80 and 84 volume related fields. See ::UpdateRadioVolumes
    float          m_f84;
    tRadioSettings settings1;
    tRadioSettings settings2;
    tRadioState    m_aRadioState[RADIO_COUNT];
    uint32         field_368;
    int8           m_nUserTrackPlayMode;

public:
    static constexpr auto DJBANTER_INDEX_HISTORY_COUNT = 15;
    static constexpr auto ADVERT_INDEX_HISTORY_COUNT   = 40;
    static constexpr auto IDENT_INDEX_HISTORY_COUNT    = 8;

    static int32 (&m_nDJBanterIndexHistory)  [DJBANTER_INDEX_HISTORY_COUNT][RADIO_COUNT]; // 210
    static int32 (&m_nAdvertIndexHistory)    [ADVERT_INDEX_HISTORY_COUNT][RADIO_COUNT];   // 560
    static int32 (&m_nIdentIndexHistory)     [IDENT_INDEX_HISTORY_COUNT][RADIO_COUNT];    // 112
    static int8  (&m_nMusicTrackIndexHistory)[220];             // 220;

    static uint8& m_nStatsLastHitTimeOutHours;
    static uint8& m_nStatsLastHitGameClockHours;
    static uint8& m_nStatsLastHitGameClockDays;
    static uint8& m_nStatsStartedCrash1;
    static uint8& m_nStatsStartedCat2;
    static uint8& m_nStatsStartedBadlands;
    static uint8& m_nStatsPassedVCrash2;
    static uint8& m_nStatsPassedTruth2;
    static uint8& m_nStatsPassedSweet2;
    static uint8& m_nStatsPassedStrap4;
    static uint8& m_nStatsPassedSCrash1;
    static uint8& m_nStatsPassedRiot1;
    static uint8& m_nStatsPassedRyder2;
    static uint8& m_nStatsPassedMansion2;
    static uint8& m_nStatsPassedLAFin2;
    static uint8& m_nStatsPassedFarlie3;
    static uint8& m_nStatsPassedDesert10;
    static uint8& m_nStatsPassedDesert8;
    static uint8& m_nStatsPassedDesert5;
    static uint8& m_nStatsPassedDesert3;
    static uint8& m_nStatsPassedDesert1;
    static uint8& m_nStatsPassedCat1;
    static uint8& m_nStatsPassedCasino10;
    static uint8& m_nStatsPassedCasino6;
    static uint8& m_nStatsPassedCasino3;
    static uint8& m_nStatsCitiesPassed;
    static uint8& m_nSpecialDJBanterIndex;
    static uint8& m_nSpecialDJBanterPending;

public:
    static void InjectHooks();

    ~CAERadioTrackManager() = default;

    bool Initialise(int32 channelId);
    void InitialiseRadioStationID(RadioStationId id);

    void Reset();
    static void ResetStatistics();

    bool   IsRadioOn() const;
    bool   HasRadioRetuneJustStarted() const;
    int8   GetCurrentRadioStationID() const;
    int32* GetRadioStationListenTimes();
    void   SetRadioAutoRetuneOnOff(bool enable);
    void   SetBassEnhanceOnOff(bool enable);
    void   SetBassSetting(int8 nBassSet, float fBassGrain);
    void   RetuneRadio(int8 radioId);

    void  DisplayRadioStationName();
    const char* GetRadioStationName(RadioStationId id);
    void  GetRadioStationNameKey(RadioStationId id, char* outStr);
    static bool IsVehicleRadioActive();

    void StartTrackPlayback();
    void UpdateRadioVolumes();
    void PlayRadioAnnouncement(uint32);
    void StartRadio(RadioStationId id, int8 bassValue, float bassGain, uint8 a5);
    void StartRadio(tVehicleAudioSettings* settings);
    void StopRadio(tVehicleAudioSettings* settings, bool bDuringPause);

    void Service(int32 playTime);

    static void Load();
    static void Save();

protected:
    void AddMusicTrackIndexToHistory(RadioStationId id, int8 trackIndex);
    void AddIdentIndexToHistory(RadioStationId id, int8 trackIndex);
    void AddAdvertIndexToHistory(RadioStationId id, int8 trackIndex);
    void AddDJBanterIndexToHistory(RadioStationId id, int8 trackIndex);

    void  ChooseTracksForStation(RadioStationId id);
    int32 ChooseIdentIndex(RadioStationId id);
    int32 ChooseAdvertIndex(RadioStationId id);
    int32 ChooseDJBanterIndex(RadioStationId id);
    int32 ChooseDJBanterIndexFromList(RadioStationId id, int32** list);
    int8  ChooseMusicTrackIndex(RadioStationId id);
    static int8  ChooseTalkRadioShow();

    void CheckForTrackConcatenation();
    static void CheckForMissionStatsChanges();
    void CheckForStationRetune();
    void CheckForStationRetuneDuringPause();
    void CheckForPause();

    bool QueueUpTracksForStation(RadioStationId id, int8* iTrackCount, int8 radioState, tRadioSettings* settings);
    bool TrackRadioStation(RadioStationId id, uint8 a2);
};

VALIDATE_SIZE(CAERadioTrackManager, 0x370);

extern CAERadioTrackManager& AERadioTrackManager;
