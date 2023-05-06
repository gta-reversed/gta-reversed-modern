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
    static constexpr size_t NUM_TRACKS = 5u;

    int32 m_aTrackQueue[NUM_TRACKS]{-1};
    int32 m_iCurrentTrackID{-1};
    int32 m_iPrevTrackID{-1};
    int32 m_iTrackPlayTime{0};
    int32 m_iTrackLengthMs{0};
    int8  m_f24{2}; // TODO: enum
    eRadioID m_nCurrentRadioStation{RADIO_OFF}; // NOTSA init value.
    int8  m_nBassSet{0};
    float m_fBassGain{}; // unk. init
    int8  m_aTrackTypes[NUM_TRACKS]{TYPE_NONE};
    int8  m_iCurrentTrackType{TYPE_NONE};
    int8  m_iPrevTrackType{TYPE_NONE};
    int8  m_aTrackIndexes[NUM_TRACKS]{-1};
    int8  m_iCurrentTrackIndex{-1};
    int8  m_iPrevTrackIndex{-1};

    tRadioSettings(eRadioID currentStation = RADIO_OFF)
        : m_nCurrentRadioStation(currentStation)
    {}

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
    int32 m_aElapsed[3]{0};
    int32 m_iTimeInPauseModeInMs{-1};
    int32 m_iTimeInMs{-1};
    int32 m_iTrackPlayTime{-1};
    int32 m_aTrackQueue[3]{-1};
    int8 m_aTrackTypes[3]{TYPE_NONE};
    int8 m_nGameClockDays{-1};
    int8 m_nGameClockHours{-1};

    void Reset(bool paused = false) {
        rng::fill(m_aElapsed, 0);
        rng::fill(m_aTrackQueue, -1);
        rng::fill(m_aTrackTypes, TYPE_NONE);

        m_iTimeInMs = -1;
        if (!paused)
            m_iTimeInPauseModeInMs = -1;
        m_iTrackPlayTime = -1;
        m_nGameClockDays = -1;
        m_nGameClockHours = -1;
    }
};
VALIDATE_SIZE(tRadioState, 0x2C);

//typedef int8 RadioStationId; => eRadioID

// NOTSA
template<size_t Count>
struct tRadioIndexHistory {
    std::array<int32, Count> indices{-1};

    void Reset() {
        rng::fill(indices, -1);
    }

    void PutAtFirst(int32 index) {
        if (indices[0] == index)
            return;

        if constexpr (Count > 1) {
            // rotate all elements to right.
            std::rotate(indices.rbegin(), indices.rbegin() + 1, indices.rend());
        }
        indices[0] = index;
    }
};
VALIDATE_SIZE(tRadioIndexHistory<1>, 0x04);

//struct tMusicTrackHistory {
//    int32 historyIndices[5];
//};
using tMusicTrackHistory = tRadioIndexHistory<5>;
VALIDATE_SIZE(tMusicTrackHistory, 0x14);

enum class eRadioTrackMode {
    UNK_0,
    UNK_1,
    UNK_2,
    GAME_PAUSED, // ?
    UNK_4,
    UNK_5,
    UNK_6,
    UNK_7
};

class CAERadioTrackManager {
public:
    bool            m_bInitialised{false};
    bool            m_bDisplayStationName{false};
    char            m_prev{0}; // TODO: make sense of this.
    bool            m_bEnabledInPauseMode{false};
    bool            m_bBassEnhance{true};
    bool            m_bPauseMode{false};
    bool            m_bRetuneJustStarted{false};
    bool            m_bRadioAutoSelect{true};
    uint8           m_nTracksInARow[RADIO_COUNT]{0};
    uint8           m_nSavedGameClockDays{0};
    uint8           m_nSavedGameClockHours{0};
    int32           m_aListenTimes[RADIO_COUNT];
    uint32          m_nTimeRadioStationRetuned{0};
    uint32          m_nTimeToDisplayRadioName{0};
    uint32          m_nSavedTimeMs{0};
    uint32          m_nRetuneStartedTime;
    uint32          field_60{0};
    int32           m_nChannel;
    eRadioTrackMode m_nMode{eRadioTrackMode::UNK_7};
    int32           m_nStationsListed{0};
    int32           m_nStationsListDown{0};
    int32           m_nSavedRadioStationId{-1};
    int8            m_iRadioStationMenuRequest;
    int8            m_iRadioStationRequest;
    int32           field_7C;
    float           m_f80{0.0f}; // 80 and 84 volume related fields. See ::UpdateRadioVolumes
    float           m_f84{0.0f};
    tRadioSettings  settings1; // TODO: Maybe just make an array out of this??
    tRadioSettings  settings2;
    tRadioState     m_aRadioState[RADIO_COUNT]{};
    uint32          field_368{0};
    int8            m_nUserTrackPlayMode;

public:
    static constexpr auto DJBANTER_INDEX_HISTORY_COUNT = 15;
    static constexpr auto ADVERT_INDEX_HISTORY_COUNT   = 40;
    static constexpr auto IDENT_INDEX_HISTORY_COUNT    = 8;
    using DJBanterIndexHistory = tRadioIndexHistory<DJBANTER_INDEX_HISTORY_COUNT>;
    using AdvertIndexHistory   = tRadioIndexHistory<ADVERT_INDEX_HISTORY_COUNT>;
    using IdentIndexHistory    = tRadioIndexHistory<IDENT_INDEX_HISTORY_COUNT>;

    static inline DJBanterIndexHistory (&m_nDJBanterIndexHistory)[RADIO_COUNT] = *(DJBanterIndexHistory(*)[RADIO_COUNT])0xB61D78; // 210
    static inline AdvertIndexHistory (&m_nAdvertIndexHistory)[RADIO_COUNT] = *(AdvertIndexHistory(*)[RADIO_COUNT])0xB620C0;       // 560
    static inline IdentIndexHistory (&m_nIdentIndexHistory)[RADIO_COUNT] = *(IdentIndexHistory(*)[RADIO_COUNT])0xB62980;          // 112
    static inline tMusicTrackHistory (&m_nMusicTrackIndexHistory)[RADIO_COUNT] = *(tMusicTrackHistory(*)[RADIO_COUNT])0xB62B40;   // 280

    static uint8& m_nStatsLastHitTimeOutHours;   // = -1;
    static uint8& m_nStatsLastHitGameClockHours; // = -1;
    static uint8& m_nStatsLastHitGameClockDays;  // = -1;
    static uint8& m_nStatsStartedCrash1;         // = 0;
    static uint8& m_nStatsStartedCat2;           // = 0;
    static uint8& m_nStatsStartedBadlands;       // = 0;
    static uint8& m_nStatsPassedVCrash2;         // = 0;
    static uint8& m_nStatsPassedTruth2;          // = 0;
    static uint8& m_nStatsPassedSweet2;          // = 0;
    static uint8& m_nStatsPassedStrap4;          // = 0;
    static uint8& m_nStatsPassedSCrash1;         // = 0;
    static uint8& m_nStatsPassedRiot1;           // = 0;
    static uint8& m_nStatsPassedRyder2;          // = 0;
    static uint8& m_nStatsPassedMansion2;        // = 0;
    static uint8& m_nStatsPassedLAFin2;          // = 0;
    static uint8& m_nStatsPassedFarlie3;         // = 0;
    static uint8& m_nStatsPassedDesert10;        // = 0;
    static uint8& m_nStatsPassedDesert8;         // = 0;
    static uint8& m_nStatsPassedDesert5;         // = 0;
    static uint8& m_nStatsPassedDesert3;         // = 0;
    static uint8& m_nStatsPassedDesert1;         // = 0;
    static uint8& m_nStatsPassedCat1;            // = 0;
    static uint8& m_nStatsPassedCasino10;        // = 0;
    static uint8& m_nStatsPassedCasino6;         // = 0;
    static uint8& m_nStatsPassedCasino3;         // = 0;
    static uint8& m_nStatsCitiesPassed;          // = 0;
    static uint8& m_nSpecialDJBanterIndex;       // = -1;
    static uint8& m_nSpecialDJBanterPending;     // = 3; // ?

public:
    static void InjectHooks();

    CAERadioTrackManager() = default; // NOTSA
    ~CAERadioTrackManager() = default;

    bool Initialise(int32 channelId);
    void InitialiseRadioStationID(eRadioID id);

    void Reset();
    static void ResetStatistics();

    bool   IsRadioOn() const;
    bool   HasRadioRetuneJustStarted() const;
    eRadioID GetCurrentRadioStationID() const;
    int32* GetRadioStationListenTimes();
    void   SetRadioAutoRetuneOnOff(bool enable);
    void   SetBassEnhanceOnOff(bool enable);
    void   SetBassSetting(int8 nBassSet, float fBassGrain);
    void   RetuneRadio(eRadioID radioId);

    void  DisplayRadioStationName();
    const char* GetRadioStationName(eRadioID id);
    void  GetRadioStationNameKey(eRadioID id, char* outStr);
    static bool IsVehicleRadioActive();

    void StartTrackPlayback();
    void UpdateRadioVolumes();
    void PlayRadioAnnouncement(uint32);
    void StartRadio(eRadioID id, int8 bassValue, float bassGain, uint8 a5);
    void StartRadio(tVehicleAudioSettings* settings);
    void StopRadio(tVehicleAudioSettings* settings, bool bDuringPause);

    void Service(int32 playTime);

    static void Load();
    static void Save();

protected:
    void AddMusicTrackIndexToHistory(eRadioID id, int8 trackIndex);
    void AddIdentIndexToHistory(eRadioID id, int8 trackIndex);
    void AddAdvertIndexToHistory(eRadioID id, int8 trackIndex);
    void AddDJBanterIndexToHistory(eRadioID id, int8 trackIndex);

    void  ChooseTracksForStation(eRadioID id);
    int32 ChooseIdentIndex(eRadioID id);
    int32 ChooseAdvertIndex(eRadioID id);
    int32 ChooseDJBanterIndex(eRadioID id);
    int32 ChooseDJBanterIndexFromList(eRadioID id, int32** list);
    int8  ChooseMusicTrackIndex(eRadioID id);
    static int8  ChooseTalkRadioShow();

    void CheckForTrackConcatenation();
    static void CheckForMissionStatsChanges();
    void CheckForStationRetune();
    void CheckForStationRetuneDuringPause();
    void CheckForPause();

    bool QueueUpTracksForStation(eRadioID id, int8* iTrackCount, int8 radioState, tRadioSettings* settings);
    bool TrackRadioStation(eRadioID id, uint8 a2);
};
VALIDATE_SIZE(CAERadioTrackManager, 0x370);

extern CAERadioTrackManager& AERadioTrackManager;
