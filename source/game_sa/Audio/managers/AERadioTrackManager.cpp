#include "StdInc.h"

#include "AERadioTrackManager.h"
#include "RadioStreamsPC.h"

#include "AEAudioHardware.h"
#include "AEUserRadioTrackManager.h"
#include "AEAudioUtility.h"
#include "AEAudioEnvironment.h"

CAERadioTrackManager& AERadioTrackManager = *(CAERadioTrackManager*)0x8CB6F8;

uint8& CAERadioTrackManager::m_nStatsLastHitTimeOutHours = *(uint8*)0xB62C58;
uint8& CAERadioTrackManager::m_nStatsLastHitGameClockHours = *(uint8*)0xB62C59;
uint8& CAERadioTrackManager::m_nStatsLastHitGameClockDays = *(uint8*)0xB62C5A;
uint8& CAERadioTrackManager::m_nStatsStartedCrash1 = *(uint8*)0xB62C5B;
uint8& CAERadioTrackManager::m_nStatsStartedCat2 = *(uint8*)0xB62C5C;
uint8& CAERadioTrackManager::m_nStatsStartedBadlands = *(uint8*)0xB62C5D;
uint8& CAERadioTrackManager::m_nStatsPassedVCrash2 = *(uint8*)0xB62C5E;
uint8& CAERadioTrackManager::m_nStatsPassedTruth2 = *(uint8*)0xB62C5F;
uint8& CAERadioTrackManager::m_nStatsPassedSweet2 = *(uint8*)0xB62C60;
uint8& CAERadioTrackManager::m_nStatsPassedStrap4 = *(uint8*)0xB62C61;
uint8& CAERadioTrackManager::m_nStatsPassedSCrash1 = *(uint8*)0xB62C62;
uint8& CAERadioTrackManager::m_nStatsPassedRiot1 = *(uint8*)0xB62C63;
uint8& CAERadioTrackManager::m_nStatsPassedRyder2 = *(uint8*)0xB62C64;
uint8& CAERadioTrackManager::m_nStatsPassedMansion2 = *(uint8*)0xB62C65;
uint8& CAERadioTrackManager::m_nStatsPassedLAFin2 = *(uint8*)0xB62C66;
uint8& CAERadioTrackManager::m_nStatsPassedFarlie3 = *(uint8*)0xB62C67;
uint8& CAERadioTrackManager::m_nStatsPassedDesert10 = *(uint8*)0xB62C68;
uint8& CAERadioTrackManager::m_nStatsPassedDesert8 = *(uint8*)0xB62C69;
uint8& CAERadioTrackManager::m_nStatsPassedDesert5 = *(uint8*)0xB62C6A;
uint8& CAERadioTrackManager::m_nStatsPassedDesert3 = *(uint8*)0xB62C6B;
uint8& CAERadioTrackManager::m_nStatsPassedDesert1 = *(uint8*)0xB62C6C;
uint8& CAERadioTrackManager::m_nStatsPassedCat1 = *(uint8*)0xB62C6D;
uint8& CAERadioTrackManager::m_nStatsPassedCasino10 = *(uint8*)0xB62C6E;
uint8& CAERadioTrackManager::m_nStatsPassedCasino6 = *(uint8*)0xB62C6F;
uint8& CAERadioTrackManager::m_nStatsPassedCasino3 = *(uint8*)0xB62C70;
uint8& CAERadioTrackManager::m_nStatsCitiesPassed = *(uint8*)0xB62C71;
uint8& CAERadioTrackManager::m_nSpecialDJBanterIndex = *(uint8*)0xB62C72;
uint8& CAERadioTrackManager::m_nSpecialDJBanterPending = *(uint8*)0xB62C73;

void CAERadioTrackManager::InjectHooks() {
    RH_ScopedClass(CAERadioTrackManager);
    RH_ScopedCategory("Audio/Managers");

    RH_ScopedInstall(Load, 0x5D40E0, { .reversed = false });
    RH_ScopedInstall(Save, 0x5D3EE0, { .reversed = false });
    RH_ScopedInstall(Initialise, 0x5B9390, { .reversed = false });
    RH_ScopedInstall(Service, 0x4EB9A0, { .reversed = false });
    RH_ScopedInstall(DisplayRadioStationName, 0x4E9E50);
    RH_ScopedInstall(CheckForStationRetune, 0x4EB660, { .reversed = false });
    RH_ScopedInstall(CheckForPause, 0x4EA590);
    RH_ScopedInstall(IsVehicleRadioActive, 0x4E9800, { .reversed = false });
    RH_ScopedInstall(AddDJBanterIndexToHistory, 0x4E97B0, { .reversed = false });
    RH_ScopedInstall(AddAdvertIndexToHistory, 0x4E9760, { .reversed = false });
    RH_ScopedInstall(AddIdentIndexToHistory, 0x4E9720, { .reversed = false });
    // RH_ScopedOverloadedInstall(StartRadio, "", 0x4EB3C0, void (CAERadioTrackManager::*)(int8, int8, float, uint8));
    // RH_ScopedOverloadedInstall(StartRadio, "", 0x4EB550, void (CAERadioTrackManager::*)(tVehicleAudioSettings*));
    RH_ScopedInstall(CheckForStationRetuneDuringPause, 0x4EB890, { .reversed = false });
    RH_ScopedInstall(TrackRadioStation, 0x4EAC30, { .reversed = false });
    RH_ScopedInstall(ChooseTracksForStation, 0x4EB180);
    RH_ScopedInstall(AddMusicTrackIndexToHistory, 0x4E96C0, { .reversed = false });
    RH_ScopedInstall(CheckForTrackConcatenation, 0x4EA930, { .reversed = false });
    RH_ScopedInstall(QueueUpTracksForStation, 0x4EA670, { .reversed = false });
    RH_ScopedInstall(ChooseDJBanterIndex, 0x4EA2D0, { .reversed = false });
    RH_ScopedInstall(ChooseDJBanterIndexFromList, 0x4E95E0, { .reversed = false });
    RH_ScopedInstall(ChooseAdvertIndex, 0x4E9570, { .reversed = false });
    RH_ScopedInstall(ChooseIdentIndex, 0x4E94C0, { .reversed = false });
    RH_ScopedInstall(ChooseMusicTrackIndex, 0x4EA270, { .reversed = false });
    RH_ScopedInstall(ChooseTalkRadioShow, 0x4E8E40, { .reversed = false });
    RH_ScopedInstall(CheckForMissionStatsChanges, 0x4E8410);
    RH_ScopedInstall(StartTrackPlayback, 0x4EA640);
    RH_ScopedInstall(UpdateRadioVolumes, 0x4EA010, { .reversed = false });
    RH_ScopedInstall(PlayRadioAnnouncement, 0x4E8400, { .reversed = false });
    RH_ScopedInstall(GetCurrentRadioStationID, 0x4E83F0);
    RH_ScopedInstall(GetRadioStationListenTimes, 0x4E83E0);
    RH_ScopedInstall(GetRadioStationName, 0x4E9E10);
    RH_ScopedInstall(GetRadioStationNameKey, 0x4E8380);
    RH_ScopedInstall(HasRadioRetuneJustStarted, 0x4E8370);
    RH_ScopedInstall(StopRadio, 0x4E9820, { .reversed = false });
    RH_ScopedInstall(IsRadioOn, 0x4E8350, { .reversed = false });
    RH_ScopedInstall(InitialiseRadioStationID, 0x4E8330);
    RH_ScopedInstall(SetBassEnhanceOnOff, 0x4E9DB0);
    RH_ScopedInstall(SetBassSetting, 0x4E82F0);
    RH_ScopedInstall(SetRadioAutoRetuneOnOff, 0x4E82E0);
    RH_ScopedInstall(RetuneRadio, 0x4E8290, { .reversed = false });
    RH_ScopedInstall(ResetStatistics, 0x4E8200);
    RH_ScopedInstall(Reset, 0x4E7F80, { .reversed = false });
}

// 0x5B9390
bool CAERadioTrackManager::Initialise(int32 channelId) {
    return plugin::CallMethodAndReturn<bool, 0x5B9390, CAERadioTrackManager*, int32>(this, channelId);

    *this = CAERadioTrackManager{};

    m_nChannel = channelId;
    // NOTSA: SA gets the list via CStats::GetFullFavoriteRadioStationList() but this way is much more clear.
    rng::copy(CStats::FavoriteRadioStationList, m_aListenTimes);

    for (auto i = 0u; i < RADIO_COUNT; i++) {
        m_nMusicTrackIndexHistory[i].Reset();
        m_nDJBanterIndexHistory[i].Reset();
        m_nAdvertIndexHistory[i].Reset();
        m_nIdentIndexHistory[i].Reset();
    }

    // [1st radio, off]
    settings1 = settings2 = tRadioSettings{CAEAudioUtility::GetRandomRadioStation()};

    *(uint32*)&m_iRadioStationMenuRequest = -1; // TODO: make sense of this.
    m_nUserTrackPlayMode = AEUserRadioTrackManager.GetUserTrackPlayMode();
}

// 0x4E8330
void CAERadioTrackManager::InitialiseRadioStationID(eRadioID id) {
    settings1.m_nCurrentRadioStation = id;
    settings2.m_nCurrentRadioStation = id;
}

// 0x4E7F80
void CAERadioTrackManager::Reset() {
    plugin::CallMethod<0x4E7F80, CAERadioTrackManager*>(this);
}

// 0x4E8200
void CAERadioTrackManager::ResetStatistics() {
    m_nStatsCitiesPassed = 0;
    m_nStatsLastHitGameClockDays = -1;
    m_nStatsLastHitGameClockHours = -1;
    m_nStatsLastHitTimeOutHours = -1;
    m_nStatsPassedCasino3 = false;
    m_nStatsPassedCasino6 = false;
    m_nStatsPassedCasino10 = false;
    m_nStatsPassedCat1 = false;
    m_nStatsPassedDesert1 = false;
    m_nStatsPassedDesert3 = false;
    m_nStatsPassedDesert5 = false;
    m_nStatsPassedDesert8 = false;
    m_nStatsPassedDesert10 = false;
    m_nStatsPassedFarlie3 = false;
    m_nStatsPassedLAFin2 = false;
    m_nStatsPassedMansion2 = false;
    m_nStatsPassedRyder2 = false;
    m_nStatsPassedRiot1 = false;
    m_nStatsPassedSCrash1 = false;
    m_nStatsPassedStrap4 = false;
    m_nStatsPassedSweet2 = false;
    m_nStatsPassedTruth2 = false;
    m_nStatsPassedVCrash2 = false;
    m_nStatsStartedBadlands = false;
    m_nStatsStartedCat2 = false;
    m_nStatsStartedCrash1 = false;
}

// 0x4E8350
bool CAERadioTrackManager::IsRadioOn() const {
    return m_nMode != eRadioTrackMode::UNK_7 || m_bInitialised || m_nStationsListed || m_nStationsListDown;
}

// 0x4E8370
bool CAERadioTrackManager::HasRadioRetuneJustStarted() const {
    return m_bRetuneJustStarted;
}

// 0x4E83E0
int32* CAERadioTrackManager::GetRadioStationListenTimes() {
    return m_aListenTimes;
}

// 0x4E83F0
eRadioID CAERadioTrackManager::GetCurrentRadioStationID() const {
    return settings1.m_nCurrentRadioStation == RADIO_INVALID ? RADIO_OFF : settings1.m_nCurrentRadioStation;
}

// 0x4E82E0
void CAERadioTrackManager::SetRadioAutoRetuneOnOff(bool enable) {
    m_bRadioAutoSelect = enable;
}

// 0x4E82F0
void CAERadioTrackManager::SetBassSetting(int8 nBassSet, float fBassGrain) {
    settings1.m_fBassGain = settings2.m_fBassGain = fBassGrain;
    settings1.m_nBassSet = settings2.m_nBassSet = nBassSet;
    AEAudioHardware.SetBassSetting(m_bBassEnhance ? nBassSet : 0, fBassGrain);
}

// 0x4E9DB0
void CAERadioTrackManager::SetBassEnhanceOnOff(bool enable) {
    m_bBassEnhance = enable;
    if (m_nMode == eRadioTrackMode::UNK_2) {
        settings1.m_nBassSet = settings2.m_nBassSet;
        settings1.m_fBassGain = settings2.m_fBassGain;
        if (enable) {
            AEAudioHardware.SetBassSetting(settings2.m_nBassSet, settings2.m_fBassGain);
        } else {
            AEAudioHardware.SetBassSetting(0, settings2.m_fBassGain);
        }
    }
}

// 0x4E8290
void CAERadioTrackManager::RetuneRadio(eRadioID id) {
    return plugin::CallMethod<0x4E8290, CAERadioTrackManager*, eRadioID>(this, id);

    const auto retunedStation = [id] {
        if (id == RADIO_USER_TRACKS && !AEUserRadioTrackManager.m_nUserTracksCount) {
            return RADIO_OFF;
        } else {
            return id;
        }
    }();

    if (CTimer::GetIsPaused()) {
        m_iRadioStationMenuRequest = retunedStation;
        m_nRetuneStartedTime = CTimer::GetTimeInMSPauseMode();
    } else {
        field_7C = retunedStation;
    }
}

// 0x4E9E50
void CAERadioTrackManager::DisplayRadioStationName() {
    if (CTimer::GetIsPaused())
        return;

    if (TheCamera.m_bWideScreenOn)
        return;

    if (!FindPlayerVehicle())
        return;

    if (CReplay::Mode == MODE_PLAYBACK)
        return;

    if (m_bDisplayStationName && IsVehicleRadioActive()) {
        m_nTimeToDisplayRadioName = CTimer::GetTimeInMS() + 2500;
        m_bDisplayStationName = false;
    }

    if (CTimer::GetTimeInMS() < m_nTimeToDisplayRadioName) {
        int station = m_nStationsListed + settings1.m_nCurrentRadioStation;
        if (station) {
            if (station >= RADIO_COUNT) {
                station %= RADIO_COUNT;
            } else if (station <= 0) {
                station += 13;
            }

            CFont::SetFontStyle(eFontStyle::FONT_MENU);
            CFont::SetJustify(false);
            CFont::SetBackground(false, false);
            CFont::SetScale(SCREEN_SCALE_X(0.6f), SCREEN_SCALE_Y(0.9f));
            CFont::SetProportional(true);
            CFont::SetOrientation(eFontAlignment::ALIGN_CENTER);
            CFont::SetRightJustifyWrap(0.0f);
            CFont::SetEdge(1);
            CFont::SetDropColor(CRGBA(0, 0, 0, 255));
            CFont::SetColor(HudColour.GetRGB(m_nStationsListed || m_nStationsListDown ? HUD_COLOUR_DARK_GRAY : HUD_COLOUR_GOLD));
            CFont::PrintString(SCREEN_WIDTH / 2, SCREEN_SCALE_Y(22.0f), GetRadioStationName((eRadioID)station));
            CFont::DrawFonts();
        }
    }
}

// 0x4E9E10
const char* CAERadioTrackManager::GetRadioStationName(eRadioID id) {
    if (id <= 0)
        return nullptr;

    char str[8];
    GetRadioStationNameKey(id, str);
    return TheText.Get(str);
}

// 0x4E8380
void CAERadioTrackManager::GetRadioStationNameKey(eRadioID id, char* outStr) {
    switch (id) {
    case RADIO_OFF:
        strcpy_s(outStr, 8u, "FEA_MON");
        break;
    case RADIO_USER_TRACKS:
        strcpy_s(outStr, 8u, "FEA_MP3");
        break;
    default:
        assert(0 <= id && id < RADIO_USER_TRACKS);
        sprintf_s(outStr, 8u, "FEA_R%d", id - 1);
        break;
    }
}

// 0x4E9800
bool CAERadioTrackManager::IsVehicleRadioActive() {
    if (const auto opts = CAEVehicleAudioEntity::StaticGetPlayerVehicleAudioSettingsForRadio()) {
        switch (opts->m_nRadioType) {
        case RADIO_CIVILIAN:
        case RADIO_EMERGENCY:
        case RADIO_UNKNOWN:
            return true;
        default:
            break;
        }
    }
    return false;
}

// 0x4E8410
void CAERadioTrackManager::CheckForMissionStatsChanges() {
    if (m_nSpecialDJBanterPending != 3) {
        int32 days = CClock::GetGameClockDays() - m_nStatsLastHitGameClockDays;
        if (days < 0) {
            auto month = CClock::GetGameClockMonth() - 1;
            if (month < 0) {
                month += 12;
            }
            days += CClock::daysInMonth[month];
        }
        if (CClock::GetGameClockHours() + 24 * days - m_nStatsLastHitGameClockHours >= m_nStatsLastHitTimeOutHours) {
            m_nSpecialDJBanterPending = 3;
        }
    }

    float statsCitiesPassed = CStats::GetStatValue(STAT_CITY_UNLOCKED);
    if ((float)m_nStatsCitiesPassed < statsCitiesPassed) {
        m_nStatsCitiesPassed = (uint8)statsCitiesPassed;
        if (statsCitiesPassed == 1 || statsCitiesPassed == 2) {
            m_nStatsLastHitGameClockDays = CClock::GetGameClockDays();
            m_nStatsLastHitGameClockHours = CClock::GetGameClockHours();
            m_nStatsLastHitTimeOutHours = 24;
            m_nSpecialDJBanterPending = 1;
            m_nSpecialDJBanterIndex = m_nStatsCitiesPassed - 1;
        }
    }

    const auto Update = [](uint8& inputStat, const eStats stat, const auto specialDJBanterIndex) {
        float statValue = CStats::GetStatValue(stat);
        if ((float)inputStat < statValue) {
            inputStat = (uint8)statValue;
            if (inputStat == 1) {
                m_nStatsLastHitGameClockDays = CClock::GetGameClockDays();
                m_nStatsLastHitGameClockHours = CClock::GetGameClockHours();
                m_nStatsLastHitTimeOutHours = 24 * 7;
                m_nSpecialDJBanterPending = 2;
                m_nSpecialDJBanterIndex = specialDJBanterIndex;
            }
        }
    };

    Update(m_nStatsPassedCasino3, STAT_LEAST_FAVORITE_RADIO_STATION, 0);
    Update(m_nStatsPassedCasino6, STAT_CURRENT_WEAPON_SKILL, 1);
    Update(m_nStatsPassedCasino10, STAT_WEAPON_SKILL_LEVELS, 2);
    Update(m_nStatsPassedCat1, STAT_LOCAL_LIQUOR_STORE_MISSION_ACCOMPLISHED, 3);
    Update(m_nStatsPassedDesert1, STAT_PLAYING_TIME, 4);
    Update(m_nStatsPassedDesert3, STAT_PILOT_RANKING, 5);
    Update(m_nStatsPassedDesert5, STAT_STRONGEST_GANG, 6);
    Update(m_nStatsPassedDesert8, STAT_2ND_STRONGEST_GANG, 7);
    Update(m_nStatsPassedDesert10, STAT_3RD_STRONGEST_GANG, 8);
    Update(m_nStatsPassedFarlie3, STAT_MIKE_TORENO_MISSION_ACCOMPLISHED, 9);
    Update(m_nStatsPassedLAFin2, STAT_LEAST_FAVORITE_GANG, 10);
    Update(m_nStatsPassedMansion2, STAT_A_HOME_IN_THE_HILLS_MISSION_ACCOMPLISHED, 11);
    Update(m_nStatsPassedRyder2, STAT_RYDERS_MISSION_ROBBING_UNCLE_SAM_ACCOMPLISHED, 12);
    Update(m_nStatsPassedRiot1, STAT_RIOT_MISSION_ACCOMPLISHED, 13);
    Update(m_nStatsPassedSCrash1, STAT_GANG_STRENGTH, 14);
    Update(m_nStatsPassedStrap4, STAT_TERRITORY_UNDER_CONTROL, 15);
    Update(m_nStatsPassedSweet2, STAT_DRIVE_THRU_MISSION_ACCOMPLISHED, 16);
    Update(m_nStatsPassedTruth2, STAT_ARE_YOU_GOING_TO_SAN_FIERRO_MISSION_ACCOMPLISHED, 17);
    Update(m_nStatsPassedVCrash2, STAT_HIGH_NOON_MISSION_ACCOMPLISHED, 18);
    Update(m_nStatsStartedBadlands, STAT_THE_GREEN_SABRE_MISSION_ACCOMPLISHED, 19);
    Update(m_nStatsStartedCat2, STAT_MAYBE_CATALINA_MEETING, 20);
    Update(m_nStatsStartedCrash1, STAT_MAYBE_WU_ZI_MEETING, 21);
}

// 0x4EA930
void CAERadioTrackManager::CheckForTrackConcatenation() {
    plugin::CallMethod<0x4EA930, CAERadioTrackManager*>(this);
}

// 0x4EB660
void CAERadioTrackManager::CheckForStationRetune() {
    plugin::CallMethod<0x4EB660, CAERadioTrackManager*>(this);
}

// 0x4EB890
void CAERadioTrackManager::CheckForStationRetuneDuringPause() {
    return plugin::CallMethod<0x4EB890, CAERadioTrackManager*>(this);
    if (settings2.m_nCurrentRadioStation == RADIO_EMERGENCY_AA && IsRadioOn())
        return;

    if (const auto station = m_iRadioStationMenuRequest; station != RADIO_OFF) {
        if (settings2.m_nCurrentRadioStation == RADIO_OFF) {
            AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_RADIO_CLICK_ON);
            settings2.m_nCurrentRadioStation = RADIO_INVALID;
        } else {
            AudioEngine.StopRadio(nullptr, true);
        }

        AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_RADIO_RETUNE_START);
        if (CTimer::GetTimeInMSPauseMode() > m_nRetuneStartedTime + 700u) {
            StartRadio(RADIO_OFF, settings2.m_nBassSet, settings2.m_fBassGain, 0);
            *(int32*)&m_iRadioStationMenuRequest = -1; // TODO
        }
    } else {
        AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_RADIO_CLICK_OFF);
        AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_RADIO_RETUNE_STOP);
        StartRadio(RADIO_OFF, settings2.m_nBassSet, settings2.m_fBassGain, 0);
        *(int32*)&m_iRadioStationMenuRequest = -1; // TODO
    }
}

// 0x4EA640
void CAERadioTrackManager::StartTrackPlayback() {
    AEAudioHardware.SetChannelFlags(m_nChannel, 0, 55);
    AEAudioHardware.StartTrackPlayback();
    UpdateRadioVolumes();
}

// 0x4EA010
void CAERadioTrackManager::UpdateRadioVolumes() {
    plugin::CallMethod<0x4EA010, CAERadioTrackManager*>(this);

    /*
    const auto fEffectsScalingFactor = AEAudioHardware.GetEffectsMasterScalingFactor();
    const auto fMusicScalingFactor = AEAudioHardware.GetMusicMasterScalingFactor();

    auto volume = -4.0f;
    if (!CTimer::GetIsPaused() || !m_bEnabledInPauseMode) {
        if (CTimer::GetIsSlowMotionActive()) {
            volume = -100.0f;
        }
        else if (TheCamera.m_bWideScreenOn) {
            volume = -16.0f;
        }
        else if (fEffectsScalingFactor > 0.0f && fMusicScalingFactor > 0.0f) {
            if (!CAEPedSpeechAudioEntity::s_bForceAudible) {
                auto audioEvent = 0;
                while (true) {
                    if (!AudioEngine.IsMissionAudioSampleFinished(audioEvent) && AudioEngine.GetMissionAudioEvent(audioEvent) != 0xFFFF) {
                        auto missionAudioPosition = AudioEngine.GetMissionAudioPosition(audioEvent);
                        if (!missionAudioPosition)
                            break;

                        CAEAudioEnvironment::GetPositionRelativeToCamera(&v9, missionAudioPosition);
                        if (CVector::Magnitude(&v9) <= 15.0f)
                            break;
                    }
                    if (++audioEvent >= 2) {
                        if (m_f80 >= 0.0f)
                            goto LABEL_22;

                        auto v4 = m_f84 + m_f80;
                        if (v4 >= 0.0f)
                            v4 = 0.0f;
                        m_f80 = v4;
                        goto LABEL_21;
                    }
                }
            }

            volumea = fEffectsScalingFactor;
            if (__FYL2X__(volumea / fMusicScalingFactor, 0.30102999566398119802) * 20.0f - 9.0f >= 0.0f) {
                v4 = 0.0f;
            } else {
                volumeb = fEffectsScalingFactor;
                v4 = __FYL2X__(volumeb / fMusicScalingFactor, 0.30102999566398119802) * 20.0f - 9.0f;
            }
            m_f80 = v4;
            m_f84 = -0.02 * v4;
        LABEL_21:
            volume = v4 - 4.0f;
        }
    LABEL_22:
        if (AudioEngine.IsAmbienceRadioActive())
            volume = volume - 20.0f;
    }

    if (m_bBassEnhance && settings2.m_nBassSet) {
        switch (settings2.m_nBassSet) {
        case 1:
            volume -= 2.0f;
            break;
        case 2:
            volume += 1.5f;
            break;
        }
    }

    AEAudioHardware.SetChannelVolume(m_nChannel, 0, volume, 0);
    */
}

// 0x4E8400
void CAERadioTrackManager::PlayRadioAnnouncement(uint32) {
    // NOP
}

// 0x4EB550
void CAERadioTrackManager::StartRadio(tVehicleAudioSettings* settings) {
    plugin::CallMethod<0x4EB550, CAERadioTrackManager*, tVehicleAudioSettings*>(this, settings);
}

// 0x4EB3C0
void CAERadioTrackManager::StartRadio(eRadioID id, int8 bassValue, float bassGain, uint8 a5) {
    plugin::CallMethod<0x4EB3C0, CAERadioTrackManager*, int8, int8, float, uint8>(this, id, bassValue, bassGain, a5);
}

// 0x4EAC30
bool CAERadioTrackManager::TrackRadioStation(eRadioID id, uint8 a2) {
    return plugin::CallMethodAndReturn<bool, 0x4EAC30, CAERadioTrackManager*, int8, uint8>(this, id, a2);
}

// 0x4EA670
bool CAERadioTrackManager::QueueUpTracksForStation(eRadioID id, int8* iTrackCount, int8 radioState, tRadioSettings& settings) {
    return plugin::CallMethodAndReturn<bool, 0x4EA670, CAERadioTrackManager*, int8, int8*, int8, tRadioSettings&>(this, id, iTrackCount, radioState, settings);
}

// 0x4E9820
void CAERadioTrackManager::StopRadio(tVehicleAudioSettings* settings, bool duringPause) {
    return plugin::CallMethod<0x4E9820, CAERadioTrackManager*, tVehicleAudioSettings*, bool>(this, settings, duringPause);
}

// 0x4E94C0
int32 CAERadioTrackManager::ChooseIdentIndex(eRadioID id) {
    return plugin::CallAndReturn<int32, 0x4E94C0, CAERadioTrackManager*, int8>(this, id);
}

// 0x4E9570
int32 CAERadioTrackManager::ChooseAdvertIndex(eRadioID id) {
    return plugin::CallAndReturn<int32, 0x4E9570, CAERadioTrackManager*, int8>(this, id);
}

// 0x4EA270
int8 CAERadioTrackManager::ChooseMusicTrackIndex(eRadioID id) {
    return plugin::CallAndReturn<int8, 0x4EA270, CAERadioTrackManager*, int8>(this, id);
}

// 0x4EA2D0
int32 CAERadioTrackManager::ChooseDJBanterIndex(eRadioID id) {
    return plugin::CallAndReturn<int32, 0x4EA2D0, CAERadioTrackManager*, int8>(this, id);
}

// 0x4E95E0
int32 CAERadioTrackManager::ChooseDJBanterIndexFromList(eRadioID id, int32** list) {
    return plugin::CallMethodAndReturn<int32, 0x4E95E0, CAERadioTrackManager*, eRadioID, int32**>(this, id, list);
}

// 0x4EB180
void CAERadioTrackManager::ChooseTracksForStation(eRadioID id) {
    int8 trackCount = 0;

    settings1.Reset();
    if (!CAEAudioUtility::ResolveProbability(0.95f)) {
        if (id) {
            if (CAEAudioUtility::ResolveProbability(0.5f))
                QueueUpTracksForStation(id, &trackCount, TYPE_INDENT, settings1);

            if (!QueueUpTracksForStation(id, &trackCount, TYPE_DJ_BANTER, settings1))
                QueueUpTracksForStation(id, &trackCount, TYPE_ADVERT, settings1);

            if (id == RADIO_USER_TRACKS) {
                QueueUpTracksForStation(RADIO_USER_TRACKS, &trackCount, TYPE_TRACK, settings1);
                return;
            }
        } else {
            QueueUpTracksForStation(RADIO_EMERGENCY_AA, &trackCount, TYPE_DJ_BANTER, settings1);
        }
        QueueUpTracksForStation(id, &trackCount, TYPE_INTRO, settings1);
        return;
    }

    if (id == RADIO_USER_TRACKS) {
        QueueUpTracksForStation(RADIO_USER_TRACKS, &trackCount, TYPE_TRACK, settings1);
        QueueUpTracksForStation(RADIO_USER_TRACKS, &trackCount, TYPE_TRACK, settings1);
        if (!FrontEndMenuManager.m_nRadioMode && CAEAudioUtility::ResolveProbability(0.17f)) {
            QueueUpTracksForStation(RADIO_USER_TRACKS, &trackCount, TYPE_ADVERT, settings1);
        }
        return;
    }

    if (CAEAudioUtility::ResolveProbability(0.9f)) {
        QueueUpTracksForStation(id, &trackCount, TYPE_TRACK, settings1);
        return;
    }

    if (CAEAudioUtility::ResolveProbability(0.5f)) {
        if (CAEAudioUtility::ResolveProbability(0.5f)) {
            QueueUpTracksForStation(id, &trackCount, TYPE_INDENT, settings1);
        }
        QueueUpTracksForStation(id, &trackCount, TYPE_INTRO, settings1);
        return;
    }

    QueueUpTracksForStation(id, &trackCount, TYPE_OUTRO, settings1);
    AddMusicTrackIndexToHistory(id, settings1.m_aTrackIndexes[trackCount - 1]);

    if (id == RADIO_EMERGENCY_AA) {
        QueueUpTracksForStation(id, &trackCount, TYPE_DJ_BANTER, settings1);
        return;
    }

    if (CAEAudioUtility::ResolveProbability(0.5f)) {
        if (CAEAudioUtility::ResolveProbability(0.5f)) {
            QueueUpTracksForStation(id, &trackCount, TYPE_INDENT, settings1);
        }
        QueueUpTracksForStation(id, &trackCount, TYPE_INTRO, settings1);
        return;
    }

    if (CAEAudioUtility::ResolveProbability(0.5f))
        QueueUpTracksForStation(id, &trackCount, TYPE_INDENT, settings1);

    if (!QueueUpTracksForStation(id, &trackCount, TYPE_DJ_BANTER, settings1))
        QueueUpTracksForStation(id, &trackCount, TYPE_ADVERT, settings1);
}

// 0x4E8E40
int8 CAERadioTrackManager::ChooseTalkRadioShow() {
    return plugin::CallAndReturn<int8, 0x4E8E40>();
}

// 0x4E96C0
void CAERadioTrackManager::AddMusicTrackIndexToHistory(eRadioID id, int8 trackIndex) {
    plugin::CallMethod<0x4E96C0, CAERadioTrackManager*, int8, int8>(this, id, trackIndex);
    m_nMusicTrackIndexHistory[id].PutAtFirst(trackIndex);
    m_nTracksInARow[id]++;
}

// 0x4E9720
void CAERadioTrackManager::AddIdentIndexToHistory(eRadioID id, int8 trackIndex) {
    plugin::CallMethod<0x4E9720, CAERadioTrackManager*, eRadioID, int8>(this, id, trackIndex);
    m_nIdentIndexHistory[id].PutAtFirst(trackIndex);
    m_nTracksInARow[id]++;
}

// 0x4E9760
void CAERadioTrackManager::AddAdvertIndexToHistory(eRadioID id, int8 trackIndex) {
    plugin::CallMethod<0x4E9760, CAERadioTrackManager*, eRadioID, int8>(this, id, trackIndex);
    m_nAdvertIndexHistory[id].PutAtFirst(trackIndex);
    m_nTracksInARow[id]++;
}

// 0x4E97B0
void CAERadioTrackManager::AddDJBanterIndexToHistory(eRadioID id, int8 trackIndex) {
    return plugin::CallMethod<0x4E97B0, CAERadioTrackManager*, eRadioID, int8>(this, id, trackIndex);
    m_nDJBanterIndexHistory[id].PutAtFirst(trackIndex);
    m_nTracksInARow[id]++;
}

// 0x4EA590
void CAERadioTrackManager::CheckForPause() {
    if (CTimer::GetIsPaused()) {
        if (m_bEnabledInPauseMode) {
            AEAudioHardware.SetChannelFrequencyScalingFactor(m_nChannel, 0, 1.0f);
        } else {
            AEAudioHardware.SetChannelFrequencyScalingFactor(m_nChannel, 0, 0.0f);
        }
        m_bPauseMode = true;
    } else {
        // todo: See CAEVehicleAudioEntity::Terminate:437 m_nRadioType.
        tVehicleAudioSettings* settings = CAEVehicleAudioEntity::StaticGetPlayerVehicleAudioSettingsForRadio();
        // todo: Comparison of different enumeration types
        if (settings && (settings->m_nRadioType == RADIO_EMERGENCY_AA || settings->m_nRadioType == RADIO_CLASSIC_ROCK || settings->m_nRadioType == RADIO_COUNTRY) || AudioEngine.IsAmbienceRadioActive()) {
            m_bPauseMode = false;
            AEAudioHardware.SetChannelFrequencyScalingFactor(m_nChannel, 0, 1.0f);
        } else {
            StopRadio(nullptr, false);
            AudioEngine.ReportFrontendAudioEvent(AE_FRONTEND_RADIO_RETUNE_STOP);
            m_bPauseMode = false;
        }
    }
}

// 0x4EB9A0
void CAERadioTrackManager::Service(int32 playTime) {
    plugin::CallMethod<0x4EB9A0, CAERadioTrackManager*, int32>(this, playTime);
}

// 0x5D40E0
void CAERadioTrackManager::Load() {
    return plugin::Call<0x5D40E0>();

    for (auto r = 0; r < RADIO_COUNT; r++) {
        // todo: m_nMusicTrackIndexHistory;

        for (auto i = 0; i < IDENT_INDEX_HISTORY_COUNT; i++) {
            CGenericGameStorage::LoadDataFromWorkBuffer(&m_nIdentIndexHistory[r].indices[i], sizeof(m_nIdentIndexHistory[r].indices[i]));
        }

        for (auto i = 0; i < ADVERT_INDEX_HISTORY_COUNT; i++) {
            CGenericGameStorage::LoadDataFromWorkBuffer(&m_nAdvertIndexHistory[r].indices[i], sizeof(m_nAdvertIndexHistory[r].indices[i]));
        }

        for (auto i = 0; i < DJBANTER_INDEX_HISTORY_COUNT; i++) {
            CGenericGameStorage::LoadDataFromWorkBuffer(&m_nDJBanterIndexHistory[r].indices[i], sizeof(m_nDJBanterIndexHistory[r].indices[i]));
        }
    }

    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsCitiesPassed,          sizeof(m_nStatsCitiesPassed));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedCasino3,         sizeof(m_nStatsPassedCasino3));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedCasino6,         sizeof(m_nStatsPassedCasino6));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedCasino10,        sizeof(m_nStatsPassedCasino10));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedCat1,            sizeof(m_nStatsPassedCat1));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedDesert1,         sizeof(m_nStatsPassedDesert1));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedDesert3,         sizeof(m_nStatsPassedDesert3));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedDesert5,         sizeof(m_nStatsPassedDesert5));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedDesert8,         sizeof(m_nStatsPassedDesert8));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedDesert10,        sizeof(m_nStatsPassedDesert10));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedFarlie3,         sizeof(m_nStatsPassedFarlie3));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedLAFin2,          sizeof(m_nStatsPassedLAFin2));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedMansion2,        sizeof(m_nStatsPassedMansion2));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedRyder2,          sizeof(m_nStatsPassedRyder2));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedRiot1,           sizeof(m_nStatsPassedRiot1));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedSCrash1,         sizeof(m_nStatsPassedSCrash1));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedStrap4,          sizeof(m_nStatsPassedStrap4));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedSweet2,          sizeof(m_nStatsPassedSweet2));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedTruth2,          sizeof(m_nStatsPassedTruth2));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsPassedVCrash2,         sizeof(m_nStatsPassedVCrash2));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsStartedBadlands,       sizeof(m_nStatsStartedBadlands));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsStartedCat2,           sizeof(m_nStatsStartedCat2));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsStartedCrash1,         sizeof(m_nStatsStartedCrash1));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsLastHitGameClockDays,  sizeof(m_nStatsLastHitGameClockDays));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsLastHitGameClockHours, sizeof(m_nStatsLastHitGameClockHours));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nStatsLastHitTimeOutHours,   sizeof(m_nStatsLastHitTimeOutHours));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nSpecialDJBanterPending,     sizeof(m_nSpecialDJBanterPending));
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_nSpecialDJBanterIndex,       sizeof(m_nSpecialDJBanterIndex));
}

// 0x5D3EE0
void CAERadioTrackManager::Save() {
    return plugin::Call<0x5D3EE0>();

    for (auto r = 0; r < RADIO_COUNT; r++) {
        // todo: m_nMusicTrackIndexHistory;

        for (auto i = 0; i < IDENT_INDEX_HISTORY_COUNT; i++) {
            CGenericGameStorage::SaveDataToWorkBuffer(&m_nIdentIndexHistory[r].indices[i], sizeof(m_nIdentIndexHistory[r].indices[i]));
        }

        for (auto i = 0; i < ADVERT_INDEX_HISTORY_COUNT; i++) {
            CGenericGameStorage::SaveDataToWorkBuffer(&m_nAdvertIndexHistory[r].indices[i], sizeof(m_nAdvertIndexHistory[r].indices[i]));
        }

        for (auto i = 0; i < DJBANTER_INDEX_HISTORY_COUNT; i++) {
            CGenericGameStorage::SaveDataToWorkBuffer(&m_nDJBanterIndexHistory[r].indices[i], sizeof(m_nDJBanterIndexHistory[r].indices[i]));
        }
    }

    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsCitiesPassed,          sizeof(m_nStatsCitiesPassed));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedCasino3,         sizeof(m_nStatsPassedCasino3));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedCasino6,         sizeof(m_nStatsPassedCasino6));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedCasino10,        sizeof(m_nStatsPassedCasino10));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedCat1,            sizeof(m_nStatsPassedCat1));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedDesert1,         sizeof(m_nStatsPassedDesert1));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedDesert3,         sizeof(m_nStatsPassedDesert3));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedDesert5,         sizeof(m_nStatsPassedDesert5));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedDesert8,         sizeof(m_nStatsPassedDesert8));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedDesert10,        sizeof(m_nStatsPassedDesert10));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedFarlie3,         sizeof(m_nStatsPassedFarlie3));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedLAFin2,          sizeof(m_nStatsPassedLAFin2));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedMansion2,        sizeof(m_nStatsPassedMansion2));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedRyder2,          sizeof(m_nStatsPassedRyder2));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedRiot1,           sizeof(m_nStatsPassedRiot1));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedSCrash1,         sizeof(m_nStatsPassedSCrash1));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedStrap4,          sizeof(m_nStatsPassedStrap4));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedSweet2,          sizeof(m_nStatsPassedSweet2));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedTruth2,          sizeof(m_nStatsPassedTruth2));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsPassedVCrash2,         sizeof(m_nStatsPassedVCrash2));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsStartedBadlands,       sizeof(m_nStatsStartedBadlands));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsStartedCat2,           sizeof(m_nStatsStartedCat2));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsStartedCrash1,         sizeof(m_nStatsStartedCrash1));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsLastHitGameClockDays,  sizeof(m_nStatsLastHitGameClockDays));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsLastHitGameClockHours, sizeof(m_nStatsLastHitGameClockHours));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nStatsLastHitTimeOutHours,   sizeof(m_nStatsLastHitTimeOutHours));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nSpecialDJBanterPending,     sizeof(m_nSpecialDJBanterPending));
    CGenericGameStorage::SaveDataToWorkBuffer(&m_nSpecialDJBanterIndex,       sizeof(m_nSpecialDJBanterIndex));
}
