/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "Hud.h"
#include "IdleCam.h"
#include "MenuSystem.h"
#include "Radar.h"
#include "GxtChar.h"
#include "Vehicle.h"

bool& CHud::bScriptDontDisplayAreaName = *(bool*)0xBAA3F8;
bool& CHud::bScriptDontDisplayVehicleName = *(bool*)0xBAA3F9;
bool& CHud::bScriptForceDisplayWithCounters = *(bool*)0xBAA3FA;
bool& CHud::bScriptDontDisplayRadar = *(bool*)0xBAA3FB;

bool& CHud::bDrawClock = *(bool*)0xBAA400;

char*& CHud::m_pVehicleNameToPrint = *(char**)0xBAA444;
int32& CHud::m_VehicleState = *(int32*)0xBAA448;
uint32& CHud::m_VehicleFadeTimer = *(uint32*)0xBAA44C;
uint32& CHud::m_VehicleNameTimer = *(uint32*)0xBAA450;
char*& CHud::m_pLastVehicleName = *(char**)0xBAA454;
char*& CHud::m_pVehicleName = *(char**)0xBAA458;

bool& CHud::m_bDraw3dMarkers = *(bool*)0xBAA45C;
bool& CHud::m_Wants_To_Draw_Hud = *(bool*)0xBAA45D;

float& CHud::m_fHelpMessageTime = *(float*)0xBAA460;
float& CHud::m_fHelpMessageBoxWidth = *(float*)0x8D0934;
bool& CHud::m_bHelpMessagePermanent = *(bool*)0xBAA464;
float& CHud::m_fHelpMessageStatUpdateValue = *(float*)0xBAA468;
uint16& CHud::m_nHelpMessageMaxStatValue = *(uint16*)0xBAA46C;
uint16& CHud::m_nHelpMessageStatId = *(uint16*)0xBAA470;
bool& CHud::m_bHelpMessageQuick = *(bool*)0xBAA472;
int32& CHud::m_nHelpMessageState = *(int32*)0xBAA474;
int32& CHud::m_nHelpMessageFadeTimer = *(int32*)0xBAA478;
int32& CHud::m_nHelpMessageTimer = *(int32*)0xBAA47C;
char (&CHud::m_pHelpMessageToPrint)[400] = *(char(*)[400])0xBAA480;
char (&CHud::m_pLastHelpMessage)[400] = *(char(*)[400])0xBAA610;
char (&CHud::m_pHelpMessage)[400] = *(char(*)[400])0xBAA7A0;
int32& CHud::m_ZoneState = *(int32*)0xBAA930;
int32& CHud::m_ZoneFadeTimer = *(int32*)0xBAA934;
int32& CHud::m_ZoneNameTimer = *(int32*)0xBAA938;
char*& CHud::m_ZoneToPrint = *(char**)0xBAB1D0;
char*& CHud::m_pLastZoneName = *(char**)0xBAB1D4;
char*& CHud::m_pZoneName = *(char**)0xBAB1D8;
int16& CHud::m_ItemToFlash = *(int16*)0xBAB1DC;
bool& CHud::bDrawingVitalStats = *(bool*)0xBAB1DE;
CSprite2d (&CHud::Sprites)[6] = *(CSprite2d(*)[6])0xBAB1FC;

int16& TimerMainCounterHideState = *(int16*)0xBAA388;
bool& TimerMainCounterWasDisplayed = *(bool*)0xBAA38A;
int16 (&TimerCounterHideState)[4] = *(int16(*)[4])0xBAA38C;
int16 (&TimerCounterWasDisplayed)[4] = *(int16(*)[4])0xBAA394;
int32& OddJob2OffTimer = *(int32*)0xBAA398;
float& OddJob2XOffset = *(float*)0xBAA39C;
int32& OddJob2Timer = *(int32*)0xBAA3A0;
float (&BigMessageAlpha)[7] = *(float(*)[7])0xBAA3A4;
float (&BigMessageInUse)[7] = *(float(*)[7])0xBAA3C0;
float (&BigMessageX)[7] = *(float(*)[7])0xBAA3DC;
char (&LastBigMessage)[7][128] = *(char(*)[7][128])0xBAABC0;
uint16& OddJob2On = *(uint16*)0xBAB1E0;
float& PagerXOffset = *(float*)0x8D0938; // 150.0
bool& HelpTripSkipShown = *(bool*)0xBAB229;

void CHud::InjectHooks() {
    RH_ScopedClass(CHud);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Initialise, 0x5BA850);
    RH_ScopedInstall(ReInitialise, 0x588880);
    RH_ScopedInstall(Shutdown, 0x588850);
    RH_ScopedInstall(Draw, 0x58FAE0);
    // RH_ScopedInstall(GetRidOfAllHudMessages, 0x588A50);
    RH_ScopedInstall(GetYPosBasedOnHealth, 0x588B60);
    RH_ScopedInstall(HelpMessageDisplayed, 0x588B50);
    // RH_ScopedInstall(ResetWastedText, 0x589070);
    // RH_ScopedInstall(SetBigMessage, 0x588FC0);
    RH_ScopedInstall(SetHelpMessage, 0x588BE0);
    RH_ScopedInstall(SetHelpMessageStatUpdate, 0x588D40);
    RH_ScopedInstall(SetHelpMessageWithNumber, 0x588E30);
    // RH_ScopedInstall(SetMessage, 0x588F60);
    RH_ScopedInstall(SetVehicleName, 0x588F50);
    RH_ScopedInstall(SetZoneName, 0x588BB0);
    RH_ScopedInstall(DrawAfterFade, 0x58D490);
    // RH_ScopedInstall(DrawAreaName, 0x58AA50);
    // RH_ScopedInstall(DrawBustedWastedMessage, 0x58CA50);
    // RH_ScopedInstall(DrawCrossHairs, 0x58E020);
    // RH_ScopedInstall(DrawFadeState, 0x58D580);
    // RH_ScopedInstall(DrawHelpText, 0x58B6E0);
    // RH_ScopedInstall(DrawMissionTimers, 0x58B180);
    // RH_ScopedInstall(DrawMissionTitle, 0x58D240);
    // RH_ScopedInstall(DrawOddJobMessage, 0x58CC80);
    // RH_ScopedInstall(DrawRadar, 0x58A330);
    // RH_ScopedInstall(DrawScriptText, 0x58C080);
    // RH_ScopedInstall(DrawSubtitles, 0x58C250);
    // RH_ScopedInstall(DrawSuccessFailedMessage, 0x58C6A0);
    RH_ScopedInstall(DrawVehicleName, 0x58AEA0);
    // RH_ScopedInstall(DrawVitalStats, 0x589650);
    RH_ScopedInstall(DrawAmmo, 0x5893B0);
    // RH_ScopedInstall(DrawPlayerInfo, 0x58EAF0);
    RH_ScopedInstall(DrawTripSkip, 0x58A160); // +
    // RH_ScopedInstall(DrawWanted, 0x58D9A0);
    RH_ScopedInstall(DrawWeaponIcon, 0x58D7D0);
    RH_ScopedInstall(RenderArmorBar, 0x5890A0);
    RH_ScopedInstall(RenderBreathBar, 0x589190);
    RH_ScopedInstall(RenderHealthBar, 0x589270);
}

bool EachFrames(auto count) {
    return (CTimer::GetFrameCounter() & count) == 0;
}

// 0x5BA850
void CHud::Initialise() {
    static constexpr SpriteFileName textures[]= { // 0x8D128C
        { "fist",           "fistm"           },
        { "siteM16",        "siteM16m"        },
        { "siterocket",     "siterocketm"     },
        { "radardisc",      "radardiscA"      },
        { "radarRingPlane", "radarRingPlaneA" },
        { "SkipIcon",       "SkipIconA"       },
    };

    auto txd = CTxdStore::AddTxdSlot("hud");
    CTxdStore::LoadTxd(txd, "MODELS\\HUD.TXD");
    CTxdStore::AddRef(txd);
    CTxdStore::PushCurrentTxd();
    CTxdStore::SetCurrentTxd(txd);

    for (auto i = 0u; i < std::size(Sprites); i++) {
        const auto& [texture, mask] = textures[i];
        Sprites[i].SetTexture(texture, mask);
    }
    CTxdStore::PopCurrentTxd();
    ReInitialise();
}

// 0x588880
void CHud::ReInitialise() {
    memset(m_pHelpMessageToPrint, 0, sizeof(m_pHelpMessageToPrint));
    memset(m_pLastHelpMessage,    0, sizeof(m_pLastHelpMessage));
    memset(m_pHelpMessage,        0, sizeof(m_pHelpMessage));
    memset(m_Message,             0, sizeof(m_Message));
    memset(m_BigMessage,          0, sizeof(m_BigMessage));
    memset(BigMessageX,           0, sizeof(BigMessageX));

    OddJob2On       = 0;
    OddJob2Timer    = 0;
    OddJob2XOffset  = 0.0f;
    OddJob2OffTimer = 0;
    PagerXOffset    = 150.0f;

    std::ranges::fill(TimerCounterHideState, 0);
    std::ranges::fill(TimerCounterWasDisplayed, 0);
    TimerMainCounterWasDisplayed = false;
    TimerMainCounterHideState = 0;

    CPlayerInfo& playerInfo         = FindPlayerInfo();
    m_LastTimeEnergyLost            = playerInfo.m_nLastTimeEnergyLost;
    m_LastDisplayScore              = playerInfo.m_nDisplayMoney;
    m_fHelpMessageStatUpdateValue   = 0.0f;
    m_Wants_To_Draw_Hud             = true;
    m_bDraw3dMarkers                = true;
    m_ZoneNameTimer                 = 0;
    m_pZoneName                     = nullptr;
    m_pLastZoneName                 = nullptr;
    m_ZoneState                     = 0;
    m_nHelpMessageTimer             = 0;
    m_nHelpMessageFadeTimer         = 0;
    m_nHelpMessageState             = 0;
    m_bHelpMessageQuick             = false;
    m_nHelpMessageStatId            = 0;
    m_nHelpMessageMaxStatValue      = 1000;
    m_bHelpMessagePermanent         = false;
    m_fHelpMessageTime              = 1.0f;
    m_fHelpMessageBoxWidth          = 200.0f;
    m_pVehicleName                  = nullptr;
    m_pLastVehicleName              = nullptr;
    m_pVehicleNameToPrint           = nullptr;
    m_VehicleNameTimer              = 0;
    m_VehicleFadeTimer              = 0;
    m_VehicleState                  = 0;
    bScriptDontDisplayRadar         = false;
    bScriptForceDisplayWithCounters = false;
    bScriptDontDisplayVehicleName   = false;
    bScriptDontDisplayAreaName      = false;
    m_ItemToFlash                   = -1;
    m_EnergyLostTimer               = 0;
    m_EnergyLostFadeTimer           = 0;
    m_EnergyLostState               = 5;
    m_DisplayScoreTimer             = 0;
    m_DisplayScoreFadeTimer         = 0;
    m_DisplayScoreState             = 5;
    m_LastWanted                    = 0;
    m_WantedTimer                   = 0;
    m_WantedFadeTimer               = 0;
    m_WantedState                   = 5;
    m_LastWeapon                    = 0;
    m_WeaponTimer                   = 0;
    m_WeaponFadeTimer               = 0;
    m_WeaponState                   = 5;
    bDrawClock                      = true;
    m_LastBreathTime                = 0;
}

// 0x588850
void CHud::Shutdown() {
    for (auto& sprite : Sprites) {
        sprite.Delete();
    }

    CTxdStore::RemoveTxdSlot(CTxdStore::FindTxdSlot("hud"));
}

// 0x588B60
float CHud::GetYPosBasedOnHealth(uint8 playerId, float pos, int8 offset) {
    return (float)FindPlayerInfo(playerId).m_nMaxHealth < 101.0f
               ? pos - SCREEN_SCALE_Y((float)offset)
               : pos;
}

// 0x588B50
bool CHud::HelpMessageDisplayed() {
    return m_nHelpMessageState != 0;
}

// 0x589070
void CHud::ResetWastedText() {
    BigMessageX[2] = 0.0f;
    m_BigMessage[2][0] = '\0';

    BigMessageX[0] = 0.0f;
    m_BigMessage[0][0] = '\0';
}

// 0x588FC0
void CHud::SetBigMessage(char* text, uint16 style) {
    plugin::Call<0x588FC0, char*, uint16>(text, style);
}

// 0x588BE0
void CHud::SetHelpMessage(const char* text, bool quickMessage, bool permanent, bool addToBrief) {
    if (m_BigMessage[4][0] || CGarages::MessageIDString[0] || CReplay::Mode == MODE_PLAYBACK || CCutsceneMgr::IsRunning()) {
        return;
    }

    memset(m_pHelpMessageToPrint, 0, sizeof(m_pHelpMessageToPrint));
    memset(m_pLastHelpMessage, 0, sizeof(m_pLastHelpMessage));
    memset(m_pHelpMessage, 0, sizeof(m_pHelpMessage));

    CMessages::StringCopy(m_pHelpMessage, const_cast<char*>(text), sizeof(m_pHelpMessage));
    CMessages::InsertPlayerControlKeysInString(m_pHelpMessage);
    if (m_nHelpMessageState && CMessages::StringCompare(m_pHelpMessage, m_pHelpMessageToPrint, sizeof(m_pHelpMessage)))
        return;

    memset(m_pLastHelpMessage, 0, sizeof(m_pLastHelpMessage));
    if (!text) {
        m_pHelpMessage[0] = '\0';
        m_pHelpMessageToPrint[0] = '\0';
    }

    if (permanent) {
        m_nHelpMessageState = 1;
        CMessages::StringCopy(m_pHelpMessageToPrint, m_pHelpMessage, sizeof(m_pHelpMessage));
        CMessages::StringCopy(m_pLastHelpMessage, m_pHelpMessage, sizeof(m_pHelpMessage));
    } else {
        m_nHelpMessageState = 0;
    }

    if (addToBrief)
        CMessages::AddToPreviousBriefArray(const_cast<char*>(text));

    m_bHelpMessagePermanent = permanent;
    m_bHelpMessageQuick = quickMessage;
    m_nHelpMessageStatId = 0;
    m_nHelpMessageMaxStatValue = 1000;
    m_fHelpMessageStatUpdateValue = 0.0f;
}

// 0x588D40
void CHud::SetHelpMessageStatUpdate(eStatUpdateState state, uint16 statId, float diff, float max) {
    if (m_BigMessage[4][0] || CGarages::MessageIDString[0] || CReplay::Mode == MODE_PLAYBACK || CCutsceneMgr::IsCutsceneProcessing()) {
        return;
    }

    memset(m_pHelpMessageToPrint, 0, sizeof(m_pHelpMessageToPrint));
    memset(m_pLastHelpMessage, 0, sizeof(m_pLastHelpMessage));
    memset(m_pHelpMessage, 0, sizeof(m_pHelpMessage));

    if (m_nHelpMessageState && CMessages::StringCompare(m_pHelpMessage, m_pHelpMessageToPrint, sizeof(m_pHelpMessage)))
        return;

    memset(m_pLastHelpMessage, 0, sizeof(m_pLastHelpMessage));
    m_nHelpMessageState = 0;
    m_bHelpMessageQuick = false;
    m_bHelpMessagePermanent = false;
    m_nHelpMessageStatId = statId;
    m_fHelpMessageStatUpdateValue = diff;
    m_nHelpMessageMaxStatValue = (uint32)max;
    // *(_WORD *)gString = 2 * (state == STAT_UPDATE_DECREASE) + '+';
    // AsciiToGxtChar(gString, m_pHelpMessage);
}

// 0x588E30
void CHud::SetHelpMessageWithNumber(const char* text, int32 number, bool quickMessage, bool permanent) {
    if (m_BigMessage[4][0] || CGarages::MessageIDString[0] || CReplay::Mode == MODE_PLAYBACK || CCutsceneMgr::IsCutsceneProcessing()) {
        return;
    }

    char str[800];
    CMessages::InsertNumberInString(const_cast<char*>(text), number, -1, -1, -1, -1, -1, str);
    CMessages::GetStringLength(str);
    CMessages::StringCopy(m_pHelpMessage, str, sizeof(m_pHelpMessage));
    CMessages::InsertPlayerControlKeysInString(m_pHelpMessage);

    memset(m_pLastHelpMessage, 0, sizeof(m_pLastHelpMessage));
    if (permanent) {
        m_nHelpMessageState = 1;
        CMessages::StringCopy(m_pHelpMessageToPrint, m_pHelpMessage, sizeof(m_pHelpMessage));
        CMessages::StringCopy(m_pLastHelpMessage, m_pHelpMessage, sizeof(m_pHelpMessage));
    } else {
        m_nHelpMessageState = 0;
    }

    m_bHelpMessagePermanent = permanent;
    m_bHelpMessageQuick = quickMessage;
    m_nHelpMessageStatId = 0;
    m_nHelpMessageMaxStatValue = 1000;
    m_fHelpMessageStatUpdateValue = 0.0f;
}

// 0x588F60
void CHud::SetMessage(char* text) {
    plugin::Call<0x588F60, char*>(text);
}

// 0x588F50
void CHud::SetVehicleName(char* name) {
    m_pVehicleName = name;
}

// 0x588BB0
void CHud::SetZoneName(char* name, uint8 displayState) {
    if (displayState || (!CGame::currArea && m_ZoneState == NAME_DONT_SHOW)) { // '&&' within '||'
        m_pZoneName = name;
    }
}

// called each frame from Render2dStuff()
// 0x58FAE0
void CHud::Draw() {
    if (CReplay::Mode == MODE_PLAYBACK || CWeapon::ms_bTakePhoto || FrontEndMenuManager.m_bActivateMenuNextFrame || gbCineyCamProcessedOnFrame == CTimer::GetFrameCounter())
        return;

    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER,        RWRSTATE(rwFILTERNEAREST));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,    RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,            RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,             RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,            RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,    RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER,        RWRSTATE(rwFILTERLINEAR));
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS,       RWRSTATE(rwTEXTUREADDRESSCLAMP));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,        RWRSTATE(NULL));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,            RWRSTATE(rwSHADEMODEFLAT));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION,    RWRSTATE(rwALPHATESTFUNCTIONGREATER));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, RWRSTATE(NULL));

    if (!TheCamera.m_bWideScreenOn) {
        DrawCrossHairs();
        if (FrontEndMenuManager.m_bHudOn && CTheScripts::bDisplayHud) {
            DrawPlayerInfo();
            DrawWanted();
        }
        if (!bScriptDontDisplayVehicleName) {
            DrawVehicleName();
        }
        DrawMissionTimers();
    }

    if (!bScriptDontDisplayRadar && !TheCamera.m_bWideScreenOn) {
        CPed* player = FindPlayerPed();
        CPad* pad = CPad::GetPad();
        if (!pad->GetDisplayVitalStats(player) || FindPlayerVehicle()) {
            bDrawingVitalStats = false;
            DrawRadar();
        } else {
            bDrawingVitalStats = true;
            DrawVitalStats();
        }
        if (!CGameLogic::SkipCanBeActivated() || bDrawingVitalStats) {
            HelpTripSkipShown = false;
        } else {
            DrawTripSkip();
            if (!HelpTripSkipShown) {
                const char* text = TheText.Get("SKIP_1");
                SetHelpMessage(text, true, false, false);
                HelpTripSkipShown = true;
            }
        }
    }

    if (m_bDraw3dMarkers && !TheCamera.m_bWideScreenOn) {
        CRadar::Draw3dMarkers();
    }

    if (!CTimer::GetIsUserPaused()) {
        if (!m_BigMessage[0][0]) {
            if (CMenuSystem::GetNumMenusInUse()) {
                CMenuSystem::Process(CMenuSystem::MENU_UNDEFINED);
            }
            DrawScriptText(1);
        }
        if (CTheScripts::bDrawSubtitlesBeforeFade) {
            DrawSubtitles();
        }
        DrawHelpText();
        DrawOddJobMessage(1);
        DrawSuccessFailedMessage();
        DrawBustedWastedMessage();
    }
}

// 0x58D490
void CHud::DrawAfterFade() {
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER,     RWRSTATE(rwFILTERNEAREST));
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS,    RWRSTATE(rwTEXTUREADDRESSCLAMP));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(FALSE));

    if (CTimer::GetIsUserPaused() || CReplay::Mode == MODE_PLAYBACK || CWeapon::ms_bTakePhoto)
        return;

    auto vehicle = FindPlayerVehicle();
    if (!vehicle || (!vehicle->IsSubPlane() && !vehicle->IsSubHeli())) { // '&&' within '||'
        if (!CCutsceneMgr::ms_cutsceneProcessing) {
            if (!FrontEndMenuManager.m_bMenuActive && !TheCamera.m_bWideScreenOn && !bScriptDontDisplayAreaName) {
                DrawAreaName();
            }
        }
    }

    if (!m_BigMessage[0][0]) {
        DrawScriptText(0);
    }

    if (!CTheScripts::bDrawSubtitlesBeforeFade) {
        DrawSubtitles();
    }

    DrawMissionTitle();
    DrawOddJobMessage(0);
}

// 0x58AA50
void CHud::DrawAreaName() {
    plugin::Call<0x58AA50>();
}

// 0x58CA50
void CHud::DrawBustedWastedMessage() {
    plugin::Call<0x58CA50>();
}

// 0x58E020
void CHud::DrawCrossHairs() {
    plugin::Call<0x58E020>();
}

// 0x58D580
float CHud::DrawFadeState(DRAW_FADE_STATE fadeState, int32 arg1) {
    return plugin::CallAndReturn<float, 0x58D580, DRAW_FADE_STATE, int32>(fadeState, arg1);
}

// 0x58B6E0
void CHud::DrawHelpText() {
    plugin::Call<0x58B6E0>();
}

// 0x58B180
void CHud::DrawMissionTimers() {
    plugin::Call<0x58B180>();
}

// 0x58D240
void CHud::DrawMissionTitle() {
    plugin::Call<0x58D240>();
}

// 0x58CC80
void CHud::DrawOddJobMessage(uint8 priority) {
    plugin::Call<0x58CC80, uint8>(priority);
}

// 0x58A330
void CHud::DrawRadar() {
    plugin::Call<0x58A330>();
}

// 0x58C080
void CHud::DrawScriptText(uint8 priority) {
    plugin::Call<0x58C080, uint8>(priority);
}

// 0x58C250
void CHud::DrawSubtitles() {
    plugin::Call<0x58C250>();
}

// 0x58C6A0
void CHud::DrawSuccessFailedMessage() {
    plugin::Call<0x58C6A0>();
}

// 0x58AEA0
void CHud::DrawVehicleName() {
    if (!m_pVehicleName) {
        m_VehicleState = 0;
        m_VehicleNameTimer = 0;
        m_VehicleFadeTimer = 0;
        m_pLastVehicleName = nullptr;
        return;
    }

    auto savedState = m_VehicleState;
    auto savedLastVehicleName = m_pLastVehicleName;
    if (m_pVehicleName != m_pLastVehicleName) {
        if (m_VehicleState) {
            if (m_VehicleState > 0 && m_VehicleState <= 4) {
                savedState = 4;
                m_VehicleState = 4;
                m_VehicleNameTimer = 0;
            }
        } else {
            savedState = 2;
            m_VehicleState = 2;
            m_VehicleNameTimer = 0;
            m_VehicleFadeTimer = 0;
            m_pVehicleNameToPrint = m_pVehicleName;
            if (m_ZoneState == NAME_SHOW || m_ZoneState == NAME_FADE_IN) {
                m_ZoneState = NAME_FADE_OUT;
            }
        }
        savedLastVehicleName = m_pVehicleName;
        m_pLastVehicleName = m_pVehicleName;
    }

    if (!savedState)
        return;

    float alpha{};
    switch (savedState) {
    case 1:
        if (m_VehicleNameTimer > 3000.0f) {
            m_VehicleState = 3;
            m_VehicleFadeTimer = 1000;
        }
        alpha = 255.0f;
        break;
    case 2:
        m_VehicleFadeTimer += CTimer::GetTimeStepInMS();
        if ((float)m_VehicleFadeTimer > 1000.0f) {
            m_VehicleFadeTimer = 1000;
            m_VehicleState = 1;
        }
        alpha = (float)m_VehicleFadeTimer / 1000.0f * 255.0f;
        break;
    case 3:
        m_VehicleFadeTimer += CTimer::GetTimeStepInMS();
        if (m_VehicleFadeTimer >= 0) {
            alpha = (float)m_VehicleFadeTimer / 1000.0f * 255.0f;
            break;
        }

        m_VehicleFadeTimer = 0;
        m_VehicleState = 0;
        break;
    case 4:
        m_VehicleFadeTimer += CTimer::GetTimeStepInMS();
        if (m_VehicleFadeTimer >= 0) {
            alpha = (float)m_VehicleFadeTimer / 1000.0f * 255.0f;
            break;
        }

        m_VehicleFadeTimer = 0;
        m_VehicleNameTimer = 0;
        m_VehicleState = 2;
        m_pVehicleNameToPrint = savedLastVehicleName;
        break;
    default:
        break;
    }

    if (!m_Message[0]) {
        m_VehicleNameTimer += CTimer::GetTimeStepInMS();
        CFont::SetProportional(true);
        CFont::SetBackground(false, false);
        CFont::SetScaleForCurrentLanguage(SCREEN_STRETCH_X(1.0f), SCREEN_STRETCH_Y(1.5f));
        CFont::SetOrientation(eFontAlignment::ALIGN_RIGHT);
        CFont::SetRightJustifyWrap(0.0f);
        CFont::SetFontStyle(eFontStyle::FONT_MENU);
        CFont::SetEdge(2);
        CFont::SetColor(HudColour.GetRGBA(HUD_COLOUR_GREEN, (uint8)alpha));
        CFont::SetDropColor(CRGBA(0, 0, 0, (uint8)alpha));
        if (CTheScripts::bDisplayHud) {
            CFont::PrintString(
                SCREEN_WIDTH - SCREEN_STRETCH_X(32.0f),
                SCREEN_HEIGHT - SCREEN_STRETCH_Y(104.0f),
                m_pVehicleNameToPrint
            );
        }
        CFont::SetSlant(0.0f);
    }
}

// 0x589650
void CHud::DrawVitalStats() {
    plugin::Call<0x589650>();
}

// 0x588A50
void CHud::GetRidOfAllHudMessages(uint8 arg0) {
    plugin::Call<0x588A50, uint8>(arg0);
}

// 0x5893B0
void CHud::DrawAmmo(CPed* ped, int32 x, int32 y, float alpha) {
    const auto& weapon = ped->GetActiveWeapon();
    const auto& totalAmmo = weapon.m_nTotalAmmo;
    const auto& ammoClip = CWeaponInfo::GetWeaponInfo(weapon.m_nType, ped->GetWeaponSkill())->m_nAmmoClip;
    const auto& ammoInClip = weapon.m_nAmmoInClip;

    if (ammoClip <= 1 || ammoClip >= 1000) {
        sprintf(gString, "%d", totalAmmo);
    } else {
        uint32 total, current;

        if (weapon.m_nType == WEAPON_FLAMETHROWER ) {
            auto out = 9999;
            if ((totalAmmo - ammoInClip) / 10 <= 9999) {
                out = (totalAmmo - ammoInClip) / 10;
            }
            total = out;

            current = ammoInClip / 10;
        } else {
            auto out = totalAmmo - ammoInClip;
            if (totalAmmo - ammoInClip > 9999)
                out = 9999;
            total = out;

            current = ammoInClip;
        }
        sprintf(gString, "%d-%d", total, current);
    }
    AsciiToGxtChar(gString, gGxtString);

    CFont::SetBackground(false, false);
    CFont::SetScale(SCREEN_STRETCH_X(0.3f), SCREEN_STRETCH_Y(0.7f));
    CFont::SetOrientation(eFontAlignment::ALIGN_CENTER);
    CFont::SetCentreSize(SCREEN_STRETCH_Y(640.0f));
    CFont::SetProportional(true);
    CFont::SetEdge(1);
    CFont::SetDropColor(CRGBA(0, 0, 0, 255));
    CFont::SetFontStyle(eFontStyle::FONT_SUBTITLES);

    if (   totalAmmo - weapon.m_nAmmoInClip >= 9999.0f
        || CDarkel::FrenzyOnGoing()
        || weapon.m_nType == WEAPON_UNARMED
        || weapon.m_nType == WEAPON_DETONATOR
        || weapon.m_nType == WEAPON_DILDO1
        || weapon.m_nType == WEAPON_DILDO2
        || weapon.m_nType == WEAPON_VIBE1
        || weapon.m_nType == WEAPON_VIBE2
        || weapon.m_nType == WEAPON_FLOWERS
        || weapon.m_nType == WEAPON_CANE
        || weapon.m_nType == WEAPON_PARACHUTE
        || CWeaponInfo::GetWeaponInfo(weapon.m_nType, eWeaponSkill::STD)->m_nWeaponFire == WEAPON_FIRE_USE
        || CWeaponInfo::GetWeaponInfo(weapon.m_nType, eWeaponSkill::STD)->m_nSlot <= 1
    ) {
        CFont::SetEdge(0);
        return;
    }

    CFont::SetColor(HudColour.GetRGBA(HUD_COLOUR_LIGHT_BLUE, (uint8)alpha));
    CFont::PrintString((float)x, (float)y, gGxtString);
    CFont::SetEdge(0);
}



// 0x58EAF0
void CHud::DrawPlayerInfo() {
    // plugin::Call<0x58EAF0>();

    if (bDrawClock) {
        DrawClock();
    }

    auto ped = FindPlayerPed();
    auto& playerInfo = FindPlayerInfo();

    auto ped1 = FindPlayerPed(1);
    auto& playerInfo1 = FindPlayerInfo(1);

    if (playerInfo.m_nLastTimeEnergyLost != m_LastTimeEnergyLost) {
        if (m_EnergyLostState) {
            if (m_EnergyLostState != 1 && m_EnergyLostState != 3) {
                if (!m_EnergyLostState || m_EnergyLostState == 5) {
                    goto LABEL_18;
                }
                goto LABEL_9;
            }
        } else {
            m_EnergyLostFadeTimer = 0;
        }
        m_EnergyLostState = 2;
        m_EnergyLostTimer = 5;
    LABEL_9:
        if (m_EnergyLostState == 2) {
            m_EnergyLostFadeTimer += CTimer::GetTimeStepInMS();
            if (m_EnergyLostFadeTimer > 1000.0) {
                m_EnergyLostState = 1;
                m_EnergyLostFadeTimer = 1000;
            }
        } else if (m_EnergyLostState == 3) {
            m_EnergyLostFadeTimer += -CTimer::GetTimeStepInMS();
            if (m_EnergyLostFadeTimer < 0.0) {
                m_EnergyLostState = 0;
                m_EnergyLostFadeTimer = 0;
            }
        }
        m_EnergyLostTimer += CTimer::GetTimeStepInMS();
    LABEL_18:
        m_LastTimeEnergyLost = playerInfo.m_nLastTimeEnergyLost;
        goto LABEL_31;
    }

    switch (m_EnergyLostState) {
    case 1:
        m_EnergyLostFadeTimer = 1000;
        if (m_EnergyLostTimer > 10000) {
            m_EnergyLostState = 3;
            m_EnergyLostFadeTimer = 3000;
        }
        m_EnergyLostTimer += CTimer::GetTimeStepInMS();
        break;
    case 2:
        m_EnergyLostFadeTimer += CTimer::GetTimeStepInMS();
        if (m_EnergyLostFadeTimer > 1000) {
            m_EnergyLostState = 1;
            m_EnergyLostFadeTimer = 1000;
        }
        m_EnergyLostTimer += CTimer::GetTimeStepInMS();
        break;
    case 3:
        m_EnergyLostFadeTimer += -CTimer::GetTimeStepInMS();
        if (m_EnergyLostFadeTimer < 0) {
            m_EnergyLostState = 0;
            m_EnergyLostFadeTimer = 0;
        }
        m_EnergyLostTimer += CTimer::GetTimeStepInMS();
        break;
    default:
        break;
    }
LABEL_31:
    // if (!m_EnergyLostState)
    //     goto LABEL_59;

    /*
     * Health Bar
     * */
    const auto healthPosX = SCREEN_WIDTH - SCREEN_STRETCH_X(141.0f);
    RenderHealthBar(CWorld::PlayerInFocus, (int32)healthPosX, (int32)GetYPosBasedOnHealth(CWorld::PlayerInFocus, SCREEN_STRETCH_Y(77.0f), 10));
    if (ped1) {
        RenderHealthBar(1, (int32)healthPosX, (int32)GetYPosBasedOnHealth(1u, GetYPosBasedOnHealth(CWorld::PlayerInFocus, SCREEN_STRETCH_Y(194.0f), 12), 12));
    }

    /*
     * Armor Bar
     * */
    const auto armorPosX = SCREEN_WIDTH - SCREEN_STRETCH_X(94.0f);
    RenderArmorBar(CWorld::PlayerInFocus, (int32)armorPosX, (int32)GetYPosBasedOnHealth(CWorld::PlayerInFocus, SCREEN_STRETCH_Y(48.0f), 3));
    if (ped1) {
        RenderArmorBar(1, (int32)armorPosX, (int32)GetYPosBasedOnHealth(1u, GetYPosBasedOnHealth(CWorld::PlayerInFocus, SCREEN_STRETCH_Y(164.0f), 12), 12));
    }

    /*
     * Breath Bar
     * */
    const auto ShouldDrawBreathBar = [](CPlayerPed* ped) {
        if (ped->GetIntelligence()->GetTaskSwim() ||
            (
                ped->bInVehicle &&
                ped->m_pVehicle &&
                ped->m_pVehicle->physicalFlags.bSubmergedInWater &&
                ped->m_pVehicle->vehicleFlags.bIsDrowning
                )
            ||
            (
                CStats::GetFatAndMuscleModifier(STAT_MOD_AIR_IN_LUNG) > ped->m_pPlayerData->m_fBreath &&
                m_LastBreathTime + 500 > CTimer::GetTimeInMS() // todo: this line should be applied only for ped0
            )
        ) {
            m_LastBreathTime = CTimer::GetTimeInMS();
            return true;
        }
        return false;
    };
    const auto breathPosX = SCREEN_STRETCH_X(94.0f);
    if (ShouldDrawBreathBar(ped)) {
        RenderBreathBar(CWorld::PlayerInFocus, (int32)breathPosX, (int32)GetYPosBasedOnHealth(CWorld::PlayerInFocus, SCREEN_STRETCH_Y(62.0f), 6));
    }
    if (ped1 && ShouldDrawBreathBar(ped1)) {
        RenderBreathBar(1, (int32)breathPosX, (int32)GetYPosBasedOnHealth(1u, GetYPosBasedOnHealth(CWorld::PlayerInFocus, SCREEN_STRETCH_Y(179.0f), 12), 12));
    }

/*
LABEL_59:
    float alpha = 255.0f;
    auto v14 = m_DisplayScoreFadeTimer;
    auto v16 = m_DisplayScoreTimer;
    auto displayScoreState = m_DisplayScoreState;
    if (m_LastDisplayScore != playerInfo.m_nDisplayMoney) {
        if (m_DisplayScoreState) {
            if (m_DisplayScoreState != 1 && m_DisplayScoreState != 3) {
                if (!m_DisplayScoreState || m_DisplayScoreState == 5)
                    goto LABEL_76;
            LABEL_65:
                if (displayScoreState == 2) {
                    v14 += CTimer::GetTimeStepInMS();
                    a1 = v14;
                    if (v14 <= 1000.0)
                        goto LABEL_70;
                    v14 = 1000;
                    displayScoreState = 1;
                } else {
                    if (displayScoreState != 3) {
                    LABEL_75:
                        v16 += CTimer::GetTimeStepInMS();
                    LABEL_76:
                        m_DisplayScoreState = displayScoreState;
                        m_DisplayScoreTimer = v16;
                        m_DisplayScoreFadeTimer = v14;
                        alpha = std::clamp(alpha, 0.0f, 255.0f);
                        m_LastDisplayScore = playerInfo.m_nDisplayMoney;

                        goto LABEL_99;
                    }
                    v14 += -CTimer::GetTimeStepInMS();
                    a1 = v14;
                    if (v14 >= 0.0) {
                    LABEL_70:
                        alpha = a1 * 0.001f * 255.0f;
                        goto LABEL_75;
                    }
                    v14 = 0;
                    displayScoreState = 0;
                }
                a1 = v14;
                goto LABEL_70;
            }
        } else {
            v14 = 0;
        }
        v16 = 5;
        displayScoreState = 2;
        goto LABEL_65;
    }

    if (m_DisplayScoreState && m_DisplayScoreState != 5) {
        switch (m_DisplayScoreState) {
        case 1:
            v14 = 1000;
            alpha = 255.0;
            if (m_DisplayScoreTimer > 10000.0) {
                displayScoreState = 3;
                v14 = 3000;
            }
            goto LABEL_94;
        case 2:
            v14 += CTimer::GetTimeStepInMS();
            a1a = v14;
            if (v14 <= 1000.0)
                goto LABEL_89;
            v14 = 1000;
            displayScoreState = 1;
            break;
        case 3:
            v14 = +-CTimer::GetTimeStepInMS();
            a1a = v14;
            if (v14 >= 0.0) {
            LABEL_89:
                v13 = a1a * 0.001 * 255.0;
                goto LABEL_94;
            }
            v14 = 0;
            displayScoreState = 0;
            break;
        default:
        LABEL_94:
            v16 += CTimer::GetTimeStepInMS();
            goto LABEL_95;
        }
        a1a = v14;
        goto LABEL_89;
    }
LABEL_95:
    m_DisplayScoreState = displayScoreState;
    m_DisplayScoreTimer = v16;
    m_DisplayScoreFadeTimer = v14;
    alpha = std::clamp(alpha, 0.0f, 255.0f);

LABEL_99:
    if (displayScoreState) {
        DrawMoney(playerInfo, alpha);
    }

    auto v24 = 255.0f; // alpha
    if (m_LastWeapon != ped->GetActiveWeapon().m_nType) {
        if (m_WeaponState) {
            if (m_WeaponState != 1 && m_WeaponState != 3) {
                if (!m_WeaponState || m_WeaponState == 5)
                    goto LABEL_125;
            LABEL_114:
                if (m_WeaponState == 2) {
                    m_WeaponFadeTimer += CTimer::GetTimeStepInMS();
                    if (m_WeaponFadeTimer > 1000.0) {
                        m_WeaponFadeTimer = 1000;
                        m_WeaponState = 1;
                        goto LABEL_122;
                    }
                } else {
                    if (m_WeaponState != 3) {
                    LABEL_124:
                        m_WeaponTimer += CTimer::GetTimeStepInMS();
                    LABEL_125:
                        v24 = std::clamp(v24, 0.0f, 255.0f);
                        m_LastWeapon = ped->GetActiveWeapon().m_nType;
                        goto LABEL_148;
                    }
                    m_WeaponFadeTimer += -CTimer::GetTimeStepInMS();
                    if (m_WeaponFadeTimer < 0.0f) {
                        m_WeaponFadeTimer = 0;
                        m_WeaponState = 0;
                    }
                }
                v24 = m_WeaponFadeTimer * 0.001f * 255.0f;
                goto LABEL_124;
            }
        } else {
            m_WeaponFadeTimer = 0;
        }
        m_WeaponTimer = 5;
        m_WeaponState = 2;
        goto LABEL_114;
    }

    if (m_WeaponState && m_WeaponState != 5) {
        switch (m_WeaponState) {
        case 1:
            m_WeaponFadeTimer = 1000;
            if (m_WeaponTimer > 10000.0f) {
                m_WeaponState = 3;
                m_WeaponFadeTimer = 3000;
            }
            v24 = 255.0f;
            m_WeaponTimer += CTimer::GetTimeStepInMS();
            break;
        case 2:
            m_WeaponFadeTimer += CTimer::GetTimeStepInMS();
            if (m_WeaponFadeTimer > 1000) {
                m_WeaponFadeTimer = 1000;
                m_WeaponState = 1;
            }
            v24 = m_WeaponFadeTimer * 0.001f * 255.0f;
            m_WeaponTimer += CTimer::GetTimeStepInMS();
            break;
        case 3:
            m_WeaponFadeTimer += -CTimer::GetTimeStepInMS();
            if (m_WeaponFadeTimer < 0) {
                m_WeaponFadeTimer = 0;
                m_WeaponState = 0;
            }
            v24 = m_WeaponFadeTimer * 0.001f * 255.0f;
            m_WeaponTimer += CTimer::GetTimeStepInMS();
            break;
        default:
            m_WeaponTimer += CTimer::GetTimeStepInMS();
            break;
        }
    }
    m_WeaponFadeTimer = std::clamp((float)m_WeaponFadeTimer, 0.0f, 255.0f);

LABEL_148:
*/
    DrawWeapon(ped, ped1);
}

inline void CHud::DrawClock() {
    char ascii[16];
    char text[16];
    CFont::SetBackground(false, false);
    CFont::SetScale(SCREEN_STRETCH_X(0.55f), SCREEN_STRETCH_Y(1.1f));
    CFont::SetProportional(false);
    CFont::SetFontStyle(FONT_PRICEDOWN);
    CFont::SetOrientation(eFontAlignment::ALIGN_RIGHT);
    CFont::SetRightJustifyWrap(0.0);
    CFont::SetEdge(2);
    CFont::SetDropColor({0, 0, 0, 255});
    sprintf(ascii, "%02d:%02d", CClock::ms_nGameClockHours, CClock::ms_nGameClockMinutes);
    AsciiToGxtChar(ascii, text);
    CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_LIGHT_GRAY));
    CFont::PrintString(SCREEN_WIDTH - SCREEN_STRETCH_X(32.0f), SCREEN_STRETCH_Y(22.0f), text);
    CFont::SetEdge(0);
}

inline void CHud::DrawMoney(const CPlayerInfo& playerInfo, uint8 alpha) {
    char ascii[16];
    char text[16];

    if (playerInfo.m_nDisplayMoney < 0) {
        CFont::SetColor(HudColour.GetRGBA(HUD_COLOUR_RED, alpha));
        auto m_nDisplayMoney = playerInfo.m_nDisplayMoney;
        if (m_nDisplayMoney < 0) {
            m_nDisplayMoney = -m_nDisplayMoney;
        }
        sprintf(ascii, "-$%07d", m_nDisplayMoney);
    } else {
        CFont::SetColor(HudColour.GetRGBA(HUD_COLOUR_GREEN, alpha));
        auto v19 = playerInfo.m_nDisplayMoney;
        if (v19 < 0)
            v19 = -v19;
        sprintf(ascii, "$%08d", v19);
    }
    AsciiToGxtChar(ascii, text);
    CFont::SetProportional(false);
    CFont::SetBackground(false, false);
    CFont::SetScale(SCREEN_STRETCH_X(0.55f), SCREEN_STRETCH_Y(1.1f));
    CFont::SetOrientation(eFontAlignment::ALIGN_RIGHT);
    CFont::SetRightJustifyWrap(0.0);
    CFont::SetFontStyle(FONT_PRICEDOWN);
    CFont::SetDropShadowPosition(0);
    CFont::SetEdge(2);
    CFont::SetDropColor({0, 0, 0, uint8(alpha)});
    CFont::PrintString(SCREEN_WIDTH - SCREEN_STRETCH_X(32.0f), GetYPosBasedOnHealth(CWorld::PlayerInFocus, SCREEN_STRETCH_Y(89.0f), 12), text);
    CFont::SetEdge(0);
}

inline void CHud::DrawWeapon(CPlayerPed* ped0, CPlayerPed* ped1) {
    const auto magic = SCREEN_WIDTH * 0.17343046f;
    if (m_WeaponState) {
        DrawWeaponIcon(ped0, SCREEN_WIDTH - (SCREEN_STRETCH_X(32.0f) + magic), SCREEN_STRETCH_Y(20.0f), (float)m_WeaponFadeTimer);
        if (ped1) {
            const auto posX = (int32)(SCREEN_WIDTH - (SCREEN_STRETCH_X(32.0f) + 111.0f));
            const auto posY = (int32)GetYPosBasedOnHealth(CWorld::PlayerInFocus, SCREEN_STRETCH_Y(138.0f), 12);
            DrawWeaponIcon(ped1, posX, posY, (float)m_WeaponFadeTimer);
        }

        const auto ammoPosX = (int32)(SCREEN_WIDTH - (magic + SCREEN_STRETCH_X(32.0f)) + SCREEN_STRETCH_X(47.0f / 2.0f));
        const auto ammoPosY = SCREEN_STRETCH_Y(43.0f);
        DrawAmmo(ped0, ammoPosX, (int32)ammoPosY + (int32)SCREEN_STRETCH_Y(20.0f), (float)m_WeaponFadeTimer);
        if (ped1) {
            const auto posY = (int32)GetYPosBasedOnHealth(CWorld::PlayerInFocus, ammoPosY + SCREEN_STRETCH_Y(138.0f), 12);
            DrawAmmo(ped1, ammoPosX, posY, (float)m_WeaponFadeTimer);
        }
    }
}

// 0x58A160
void CHud::DrawTripSkip() {
    CRect rect{
        SCREEN_STRETCH_X(54.0f),
        SCREEN_HEIGHT - SCREEN_STRETCH_Y(104.0f) - SCREEN_STRETCH_Y(85.0f),
        SCREEN_STRETCH_X(64.0f) + SCREEN_STRETCH_X(54.0f),
        SCREEN_STRETCH_Y(64.0f) + SCREEN_HEIGHT - SCREEN_STRETCH_Y(104.0f) - SCREEN_STRETCH_Y(85.0f)
    };
    Sprites[SPRITE_SKIP_ICON].Draw(rect, CRGBA(255, 255, 255, 255));

    CFont::SetBackground(false, false);
    CFont::SetScale(SCREEN_STRETCH_X(0.3f), SCREEN_STRETCH_Y(0.7f));
    CFont::SetOrientation(eFontAlignment::ALIGN_CENTER);
    CFont::SetCentreSize(SCREEN_WIDTH);
    CFont::SetProportional(true);
    CFont::SetEdge(1);
    CFont::SetDropColor(CRGBA(0, 0, 0, 255));
    CFont::SetFontStyle(eFontStyle::FONT_MENU);
    CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_LIGHT_GRAY));
    CFont::PrintString(
        SCREEN_STRETCH_X(64.0f) / 2.0f + SCREEN_STRETCH_X(54.0f),
        SCREEN_HEIGHT - SCREEN_STRETCH_Y(104.0f) - SCREEN_STRETCH_Y(85.0f) + SCREEN_STRETCH_Y(64.0f) - SCREEN_STRETCH_Y(2.0f),
        TheText.Get("FEC_TSK") // TRIP SKIP
    );
}

// 0x58D9A0
void CHud::DrawWanted() {
    plugin::Call<0x58D9A0>();
}

// 0x58D7D0
void CHud::DrawWeaponIcon(CPed* ped, int32 x, int32 y, float alpha) {
    // plugin::Call<0x58D7D0, CPed*, int32, int32, float>(ped, x, y, alpha);

    const auto x0 = (float)x;
    const auto y0 = (float)y;
    const float width  = SCREEN_STRETCH_X(47.0f);
    const float height = SCREEN_STRETCH_Y(58.0f);
    const float halfWidth  = width / 2.0f;
    const float halfHeight = height / 2.0f;

    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, RWRSTATE(2u));

    auto modelId = CWeaponInfo::GetWeaponInfo(ped->m_aWeapons[ped->m_nActiveWeaponSlot].m_nType, eWeaponSkill::STD)->m_nModelId1;
    if (modelId <= 0) {
        CRect rect{ x0, y0, width + x0, height + y0 };
        Sprites[SPRITE_FIST].Draw(rect, CRGBA(255, 255, 255, (uint8)alpha));
    } else {
        auto mi = CModelInfo::GetModelInfo(modelId);
        auto txd = CTxdStore::ms_pTxdPool->GetAt(mi->m_nTxdIndex);
        if (!txd)
            return;

        auto texture = RwTexDictionaryFindHashNamedTexture(txd->m_pRwDictionary, CKeyGen::AppendStringToKey(mi->m_nKey, "ICON"));
        if (!texture)
            return;

        RwRenderStateSet(rwRENDERSTATEZTESTENABLE,   RWRSTATE(NULL));
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RWRSTATE(RwTextureGetRaster(texture)));
        CSprite::RenderOneXLUSprite(x0 + halfWidth, y0 + halfHeight, 1.0f, halfWidth, halfHeight, 255u, 255u, 255u, 255, 1.0f, 255, 0, 0);
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,  RWRSTATE(0));
    }
}

// 0x5890A0
void CHud::RenderArmorBar(int32 playerId, int32 x, int32 y) {
    auto* player = FindPlayerPed(playerId);
    if ((m_ItemToFlash == 3 && EachFrames(8)) || player->m_fArmour <= 1.0f)
        return;

    auto playerInfo = player->GetPlayerInfoForThisPlayerPed();
    CSprite2d::DrawBarChart(
        (float)x,
        (float)y,
        (uint16)SCREEN_STRETCH_X(62.0f),
        (uint8)SCREEN_STRETCH_Y(9.0f),
        player->m_fArmour / (float)playerInfo->m_nMaxArmour * 100.0f,
        false,
        false,
        true,
        HudColour.GetRGB(HUD_COLOUR_LIGHT_GRAY),
        CRGBA(0, 0, 0, 0)
    );
}

// 0x589190
void CHud::RenderBreathBar(int32 playerId, int32 x, int32 y) {
    if (m_ItemToFlash == 10 && EachFrames(8))
        return;

    auto* player = FindPlayerPed(playerId);
    CSprite2d::DrawBarChart(
        (float)x,
        (float)y,
        (uint16)SCREEN_STRETCH_X(2.0f),
        (uint8)SCREEN_STRETCH_Y(9.0f),
        player->m_pPlayerData->m_fBreath / CStats::GetFatAndMuscleModifier(STAT_MOD_AIR_IN_LUNG) * 100.0f,
        false,
        false,
        true,
        HudColour.GetRGB(HUD_COLOUR_LIGHT_BLUE),
        CRGBA(0, 0, 0, 0)
    );
}

// little bit different
// 0x589270
void CHud::RenderHealthBar(int32 playerId, int32 x, int32 y) {
    auto* player = FindPlayerPed(playerId);
    auto* playerInfo = player->GetPlayerInfoForThisPlayerPed();

    if (m_ItemToFlash == 4 && EachFrames(8))
        return;

    if ((int16)player->m_fHealth < 10 && EachFrames(8))
        return;

    auto totalWidth = SCREEN_STRETCH_X((float)playerInfo->m_nMaxHealth * 109.0f) / CStats::GetFatAndMuscleModifier(STAT_MOD_10);
    CSprite2d::DrawBarChart(
        SCREEN_STRETCH_X(109.0f) - totalWidth + (float)x,
        (float)y,
        (uint16)totalWidth,
        (uint8)SCREEN_STRETCH_Y(9.0f),
        player->m_fHealth * 100.0f / (float)playerInfo->m_nMaxHealth,
        false,
        false,
        true,
        HudColour.GetRGB(HUD_COLOUR_RED),
        CRGBA(0, 0, 0, 0)
    );
}
