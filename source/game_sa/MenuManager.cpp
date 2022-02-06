/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "extensions/enumerate.hpp"
#include <valarray>

#include "MenuManager.h"
#include "Gamma.h"

CMenuManager& FrontEndMenuManager = *(CMenuManager*)0xBA6748;

CMenuManager& GetMenu() {
    return FrontEndMenuManager;
}

bool& CMenuManager::bInvertMouseX = *(bool*)0xBA6744;
bool& CMenuManager::bInvertMouseY = *(bool*)0xBA6745;

//int32& CMenuManager::nLastMenuPage = *(int32*)0x8CDFF0;

struct SpriteFileName {
    const char* name;
    const char* alpha;
};

struct FrontEndFilenamesType {
    union {
        struct {
            SpriteFileName Textures[25];
        };
        struct {
            SpriteFileName Radio[13];
            SpriteFileName Background[8];
            SpriteFileName AdditionalBackground[2];
            SpriteFileName Mouse[2];
        };
    };
};

#define BUILD_PC

// 0x8CDF28
SpriteFileName FrontEndFilenames[25] = {
    { "arrow",              "arrowA" },        // 0
    { "radio_playback",     "" },              // 1
    { "radio_krose",        "" },              // 2
    { "radio_KDST",         "" },              // 3
    { "radio_bounce",       "" },              // 4
    { "radio_SFUR",         "" },              // 5
    { "radio_RLS",          "" },              // 6
    { "radio_RADIOX",       "" },              // 7
    { "radio_csr",          "" },              // 8
    { "radio_kjah",         "" },              // 9
    { "radio_mastersounds", "" },              // 10
    { "radio_wctr",         "" },              // 11
    { "radio_TPLAYER",      "" },              // 12
# ifdef BUILD_XBOX
    { "CONTROLLER_XBOX",    "CONTROLLER_XBOXM" },
# endif

    { "back2",              "" },              // 13
    { "back3",              "" },              // 14
    { "back4",              "" },              // 15
    { "back5",              "" },              // 16
    { "back6",              "" },              // 17
    { "back7",              "" },              // 18
    { "back8",              "" },              // 19
    { "map",                "" },              // 20

    { "back8_top",          "" },              // 21
    { "back8_right",        "" },              // 22

# ifdef BUILD_PC
    { "mouse",              "mousea"     },    // 23
    { "crosshair",          "crosshaira" },    // 24
# endif
};

FrontEndFilenamesType FrontEndFilenamesX = reinterpret_cast<FrontEndFilenamesType&>(FrontEndFilenames); // w8 for your suggestions

void CMenuManager::InjectHooks()
{
    RH_ScopedClass(CMenuManager);
    RH_ScopedCategoryGlobal();

    // RH_ScopedInstall(Initialise, 0x5744D0);
    RH_ScopedInstall(LoadAllTextures, 0x572EC0);
    // RH_ScopedInstall(SwapTexturesRound, 0x5730A0);
    // RH_ScopedInstall(UnloadTextures, 0x574630);
    // RH_ScopedInstall(InitialiseChangedLanguageSettings, 0x573260);
    // RH_ScopedInstall(HasLanguageChanged, 0x573CD0);
    // RH_ScopedInstall(DoSettingsBeforeStartingAGame, 0x573330);
    // RH_ScopedInstall(StretchX, 0x5733E0);
    // RH_ScopedInstall(StretchY, 0x573410);
    // RH_ScopedInstall(SwitchToNewScreen, 0x573680);
    RH_ScopedInstall(ScrollRadioStations, 0x573A00);
    // RH_ScopedInstall(SetFrontEndRenderStates, 0x573A60);
    // RH_ScopedInstall(SetDefaultPreferences, 0x573AE0);
    // RH_ScopedInstall(GetNumberOfMenuOptions, 0x573E70);
    // RH_ScopedInstall(JumpToGenericMessageScreen, 0x576AE0);

    // RH_ScopedInstall(DrawFrontEnd, 0x57C290);
    // RH_ScopedInstall(DrawBackground, 0x57B750);
    // RH_ScopedInstall(DrawStandardMenus, 0x5794A0);
    RH_ScopedInstall(DrawWindow, 0x573EE0);
    // RH_ScopedInstall(DrawWindowedText, 0x578F50);
    // RH_ScopedInstall(DrawQuitGameScreen, 0x57D860);
    // RH_ScopedInstall(DrawControllerScreenExtraText, 0x57D8D0);
    // RH_ScopedInstall(DrawControllerBound, 0x57E6E0);
    // RH_ScopedInstall(DrawControllerSetupScreen, 0x57F300);

    // RH_ScopedInstall(CentreMousePointer, 0x57C520);
    // RH_ScopedInstall(LoadSettings, 0x57C8F0);
    // RH_ScopedInstall(SaveSettings, 0x57C660);
    // RH_ScopedInstall(SaveStatsToFile, 0x57DDE0);
    // RH_ScopedInstall(SaveLoadFileError_SetUpErrorScreen, 0x57C490);

    // RH_ScopedInstall(CheckSliderMovement, 0x573440);
    // RH_ScopedInstall(CheckFrontEndUpInput, 0x573840);
    // RH_ScopedInstall(CheckFrontEndDownInput, 0x5738B0);
    // RH_ScopedInstall(CheckFrontEndLeftInput, 0x573920);
    // RH_ScopedInstall(CheckFrontEndRightInput, 0x573990);
    // RH_ScopedInstall(CheckForMenuClosing, 0x576B70);
    RH_ScopedInstall(CheckHover, 0x57C4F0);
    // RH_ScopedInstall(CheckMissionPackValidMenu, 0x57D720);
    // RH_ScopedInstall(CheckCodesForControls, 0x57DB20);

    // RH_ScopedInstall(DisplaySlider, 0x576860);
    // RH_ScopedInstall(DisplayHelperText, 0x57E240);
    RH_ScopedInstall(SetHelperText, 0x57CD10);
    RH_ScopedInstall(ResetHelperText, 0x57CD30);
    // RH_ScopedInstall(MessageScreen, 0x579330);
    // RH_ScopedInstall(SmallMessageScreen, 0x574010);

    // RH_ScopedInstall(PrintMap, 0x575130);
    // RH_ScopedInstall(PrintStats, 0x574900);
    // RH_ScopedInstall(PrintBriefs, 0x576320);
    // RH_ScopedInstall(PrintRadioStationList, 0x5746F0);

    // RH_ScopedInstall(UserInput, 0x57FD70);
    // RH_ScopedInstall(AdditionalOptionInput, 0x5773D0);
    // RH_ScopedInstall(CheckRedefineControlInput, 0x57E4D0);
    // RH_ScopedInstall(RedefineScreenUserInput, 0x57EF50);

    RH_ScopedInstall(Process, 0x57B440);
    // RH_ScopedInstall(ProcessStreaming, 0x573CF0);
    // RH_ScopedInstall(ProcessFileActions, 0x578D60);
    // RH_ScopedInstall(ProcessUserInput, 0x57B480);
    // RH_ScopedInstall(ProcessMenuOptions, 0x576FE0);
    // RH_ScopedInstall(ProcessPCMenuOptions, 0x57CD50);
    // RH_ScopedInstall(ProcessMissionPackNewGame, 0x57D520);
}

// 0x574350
CMenuManager::CMenuManager() {
    plugin::CallMethod<0x574350>(this);
}

// 0x579440
CMenuManager::~CMenuManager() {
    plugin::CallMethod<0x579440>(this);
}

// 0x5744D0
void CMenuManager::Initialise() {
    plugin::CallMethod<0x5744D0>(this);
}

// 0x572EC0
void CMenuManager::LoadAllTextures() {
    if (m_bTexturesLoaded)
        return;

    CTimer::Stop();

    // TODO: FIGURE OUT WHY BREAKPOINT DOESN'T WORKS
    const auto LoadTexture = [=](size_t memorySize, std::string_view slot, std::string_view txdName, auto& textureNames, auto& sprites) {
        CStreaming::MakeSpaceFor(memorySize);
        CStreaming::ImGonnaUseStreamingMemory();
        CGame::TidyUpMemory(false, true);
        CTxdStore::PushCurrentTxd();
        auto txdSlot = CTxdStore::FindTxdSlot(slot.data());
        if (txdSlot == -1)
            txdSlot = CTxdStore::AddTxdSlot(slot.data());
        CTxdStore::LoadTxd(txdSlot, txdName.data());
        CTxdStore::AddRef(txdSlot);
        CTxdStore::SetCurrentTxd(txdSlot);

        for (auto [index, texture] : enumerate(textureNames)) {
            // HERE, FOR EXAMPLE
            CSprite2d& sprite = sprites[index];
            sprite.SetTexture(texture.name, texture.alpha);
            sprite.SetAddressing(rwTEXTUREADDRESSCLAMP);
        }

        CTxdStore::PopCurrentTxd();
        CStreaming::IHaveUsedStreamingMemory();
    };

    LoadTexture(0x21000, "frontend1",   "MODELS\\FRONTEN1.TXD",   FrontEndFilenamesX.Radio, m_apRadioSprites);
    LoadTexture(0x3000,  "frontend_pc", "MODELS\\FRONTEN_pc.TXD", FrontEndFilenamesX.Mouse, m_apMouseTextures); // originally they wrote "MODELS/FRONTEN_pc.TXD"
    LoadTexture(0x4C000, "frontend2",   "MODELS\\FRONTEN2.TXD",   FrontEndFilenamesX.Background,  m_apBackgroundTextures);

    m_bTexturesLoaded = true;
    CTimer::Update();
}

// 0x5730A0
void CMenuManager::SwapTexturesRound(bool frontend) {
    plugin::CallMethod<0x5730A0, CMenuManager*>(this, frontend);
}

// 0x574630
void CMenuManager::UnloadTextures() {
    if (m_bTexturesLoaded) {
        SwapTexturesRound(false);

        const auto Remove = [](std::string_view slot, auto& sprites) {
            std::ranges::for_each(sprites, [](auto& sprite) { sprite.Delete(); });
            CTxdStore::RemoveTxd(CTxdStore::FindTxdSlot(slot.data()));
        };

        Remove("frontend1",   m_apRadioSprites);
        Remove("frontend_pc", m_apMouseTextures);
        Remove("frontend2",   m_apBackgroundTextures);
        // todo: R* missed m_apAdditionalBackgroundTextures?

        m_bTexturesLoaded = false;
    }
}

// 0x573260
void CMenuManager::InitialiseChangedLanguageSettings() {
    plugin::CallMethod<0x573260, CMenuManager*>(this);
}

// 0x573CD0
bool CMenuManager::HasLanguageChanged() {
    if (m_nPreviousLanguage == m_nLanguage)
        return false;

    m_nPreviousLanguage = m_nLanguage;
    return true;
}

// 0x573330
void CMenuManager::DoSettingsBeforeStartingAGame() {
    plugin::CallMethod<0x573330, CMenuManager*>(this);
}

// 0x5733E0
float CMenuManager::StretchX(float x) {
    if (SCREEN_WIDTH != DEFAULT_SCREEN_WIDTH) {
        return SCREEN_SCALE_X(x);
    }
    return x;
}

// 0x573410
float CMenuManager::StretchY(float y) {
    if (SCREEN_HEIGHT != DEFAULT_SCREEN_HEIGHT) {
        return SCREEN_SCALE_Y(y);
    }
    return y;
}

// 0x573680
void CMenuManager::SwitchToNewScreen(int8 screen) {
    plugin::CallMethod<0x573680, CMenuManager*, int8>(this, screen);
}

// 0x573A00
void CMenuManager::ScrollRadioStations(int8 numStations) {
    if (!m_nRadioStation || CAudioEngine::IsCutsceneTrackActive()) {
        return;
    }
    
    m_nRadioStation = numStations + m_nRadioStation;
    if (m_nRadioStation <= 0) {
        m_nRadioStation = RADIO_COUNT - 1;
    }
    if (m_nRadioStation >= RADIO_COUNT) {
        m_nRadioStation = 1;
    }
    AudioEngine.RetuneRadio(m_nRadioStation);
    CMenuManager::SaveSettings();
}

// 0x573A60
void CMenuManager::SetFrontEndRenderStates() {
    plugin::CallMethod<0x573A60, CMenuManager*>(this);
}

// 0x573AE0
void CMenuManager::SetDefaultPreferences(eMenuPage screen) {
    switch (screen) {
    case MENUPAGE_AUDIO_SETTINGS:
        m_nSfxVolume       = 64;
        m_nRadioVolume     = 64;
        field_4E           = 1;
        m_bRadioEq         = true;
        m_bRadioAutoSelect = true;
        m_bTracksAutoScan  = false;
        m_nRadioMode       = 0;
        AudioEngine.SetMusicMasterVolume(GetMenu().m_nRadioVolume);
        AudioEngine.SetEffectsMasterVolume(GetMenu().m_nSfxVolume);
        AudioEngine.SetBassEnhanceOnOff(GetMenu().m_bRadioEq);
        AudioEngine.SetRadioAutoRetuneOnOff(GetMenu().m_bRadioAutoSelect);
        break;
    case MENUPAGE_DISPLAY_SETTINGS:
    case MENUPAGE_DISPLAY_ADVANCED:
        g_fx.SetFxQuality(FXQUALITY_HIGH);
        gamma.SetGamma(0.5f, true);
        m_nBrightness                  = 256;
        m_fDrawDistance                = 1.2f;
        CRenderer::ms_lodDistScale     = 1.2f;
        m_bFrameLimiterOn              = true;
        m_bHudOn                       = true;
        m_bSavePhotos                  = true;
        m_bMipMapping                  = true;
        m_nAppliedAntiAliasingLevel    = 1;
        m_nAntiAliasingLevel           = 1;
        m_bWidescreenOn                = false;
        m_bMapLegend                   = false;
        m_nRadarMode                   = 0;
        m_nResolution                  = m_nAppliedResolution;
        //field_45                       = 0x1010101;
        field_49                       = 1;
        m_bShowSubtitles               = false;
        break;
    case MENUPAGE_CONTROLLER_SETUP:
        m_nController                  = 0;
        *(bool*)0xC1CC02               = false; // todo: CVehicle::m_bEnableMouseSteering
        CVehicle::m_bEnableMouseFlying = true;
        CCamera::m_fMouseAccelHorzntl  = 0.0025f;
        CCamera::m_bUseMouse3rdPerson  = true;
        bInvertMouseY                  = false;
        m_bInvertPadX1                 = false;
        m_bInvertPadY1                 = false;
        m_bInvertPadX2                 = false;
        m_bInvertPadY2                 = false;
        m_bSwapPadAxis1                = false;
        m_bSwapPadAxis2                = false;
        break;
    }
}

// 0x573E70
uint32 CMenuManager::GetNumberOfMenuOptions() {
    return plugin::CallMethodAndReturn<uint32, 0x573E70, CMenuManager*>(this);
}

// 0x576AE0
void CMenuManager::JumpToGenericMessageScreen(eMenuPage screen, const char* titleKey, const char* textKey) {
    plugin::CallMethod<0x576AE0, CMenuManager*, eMenuPage, const char*, const char*>(this, screen, titleKey, textKey);
}

// 0x57C290
void CMenuManager::DrawFrontEnd() {
    plugin::CallMethod<0x57C290, CMenuManager*>(this);
}

// 0x57B750
void CMenuManager::DrawBackground() {
    plugin::CallMethod<0x57B750, CMenuManager*>(this);
}

// 0x5794A0
void CMenuManager::DrawStandardMenus(uint8) {
    plugin::CallMethod<0x5794A0, CMenuManager*>(this);
}

// 0x573EE0
void CMenuManager::DrawWindow(const CRect& coords, const char* key, uint8 color, CRGBA backColor, bool unused, bool background) {
    if (background) {
        CSprite2d::DrawRect(coords, backColor);
    }

    if (key && *key) {
        CFont::SetWrapx(coords.right);
        CFont::SetColor(CRGBA(225 - color, 225 - color, 225 - color, 255));
        CFont::SetDropColor(CRGBA(0, 0, 0, 255));
        CFont::SetEdge(2);
        CFont::SetOrientation(eFontAlignment::ALIGN_LEFT);
        CFont::SetFontStyle(FONT_GOTHIC);
        CFont::SetScale(SCREEN_SCALE_X(1), SCREEN_SCALE_Y(1.4f));

        float fY = std::min(coords.top, coords.bottom) - SCREEN_SCALE_Y(16);
        float fX = coords.left + SCREEN_SCALE_X(10);
        CFont::PrintString(fX, fY, TheText.Get(const_cast<char *>(key)));
    }
}

// 0x578F50
void CMenuManager::DrawWindowedText(float a2, float a3, RwRGBA color, char *a5, char* key, float scaleY) {
    plugin::CallMethod<0x578F50, CMenuManager*, float, float, RwRGBA, char*, char*, float>(this, a2, a3, color, a5, key, scaleY);
}

// 0x57D860
void CMenuManager::DrawQuitGameScreen() {
    plugin::CallMethod<0x57D860, CMenuManager*>(this);
}

// 0x57D8D0
void CMenuManager::DrawControllerScreenExtraText(int32 a1) {
    plugin::CallMethod<0x57D8D0, CMenuManager*, int32>(this, a1);
}

// 0x57E6E0
void CMenuManager::DrawControllerBound(uint16 a1, bool a2) {
    plugin::CallMethod<0x57E6E0, CMenuManager*, uint16, bool>(this, a1, a2);
}

// 0x57F300
void CMenuManager::DrawControllerSetupScreen() {
    plugin::CallMethod<0x57F300, CMenuManager*>(this);
}

// 0x57C520
void CMenuManager::CentreMousePointer() {
    plugin::CallMethod<0x57C520, CMenuManager*>(this);
}

// 0x57C8F0
void CMenuManager::LoadSettings() {
    plugin::CallMethod<0x57C8F0, CMenuManager*>(this);
}

// 0x57C660
void CMenuManager::SaveSettings() {
    plugin::CallMethod<0x57C660, CMenuManager*>(this);
}

// 0x57DDE0
void CMenuManager::SaveStatsToFile() {
    plugin::CallMethod<0x57DDE0, CMenuManager*>(this);
}

// 0x57C490
void CMenuManager::SaveLoadFileError_SetUpErrorScreen() {
    plugin::CallMethod<0x57C490, CMenuManager*>(this);
}

// 0x573440
void CMenuManager::CheckSliderMovement(int8 unk) {
    plugin::CallMethod<0x573440, CMenuManager*, int8>(this, unk);
}

// 0x573840
bool CMenuManager::CheckFrontEndUpInput() {
    return plugin::CallMethodAndReturn<bool, 0x573840, CMenuManager*>(this);
}

// 0x5738B0
bool CMenuManager::CheckFrontEndDownInput() {
    return plugin::CallMethodAndReturn<bool, 0x5738B0, CMenuManager*>(this);
}

// 0x573920
bool CMenuManager::CheckFrontEndLeftInput() {
    return plugin::CallMethodAndReturn<bool, 0x573920, CMenuManager*>(this);
}

// 0x573990
bool CMenuManager::CheckFrontEndRightInput() {
    return plugin::CallMethodAndReturn<bool, 0x573990, CMenuManager*>(this);
}

// 0x576B70
bool CMenuManager::CheckForMenuClosing() {
    return plugin::CallMethodAndReturn<bool, 0x576B70, CMenuManager*>(this);
}

// 0x57C4F0
bool CMenuManager::CheckHover(int32 left, int32 right, int32 top, int32 bottom) {
    return (
        m_nMousePosLeft > left && m_nMousePosLeft < right &&
        m_nMousePosTop > top  && m_nMousePosTop < bottom
    );
}

// 0x57D720
bool CMenuManager::CheckMissionPackValidMenu() {
    return plugin::CallMethodAndReturn<bool, 0x57D720, CMenuManager*>(this);
}

// 0x57DB20
bool CMenuManager::CheckCodesForControls(int32 a1) {
    return plugin::CallMethodAndReturn<bool, 0x57DB20, CMenuManager*>(this, a1);
}

// 0x576860
void CMenuManager::DisplaySlider(float x, float y, float a3, float a4, float a5, float value, int32 size) {
    plugin::CallMethod<0x576860, CMenuManager*, float, float, float, float, float, float, int32>(this, x, y, a3, a4, a5, value, size);
}

// 0x57E240
void CMenuManager::DisplayHelperText(char* key) {
    plugin::CallMethod<0x57E240, CMenuManager*, char*>(this, key);
}

// 0x57CD10
void CMenuManager::SetHelperText(int32 messageId) {
    m_nHelperText = messageId;
    m_nHelperTextFadingAlpha = 300;
}

// 0x57CD30
void CMenuManager::ResetHelperText() {
    m_nHelperText = 0;
    m_nHelperTextFadingAlpha = 300;
}

// 0x579330
void CMenuManager::MessageScreen(const char* key, bool blackBackground, bool cameraUpdateStarted) {
    // blackBackground -> bRenderBig
    // cameraUpdateStarted -> bWithinFrame
    return plugin::CallMethod<0x579330, CMenuManager*, const char*, bool, bool>(this, key, blackBackground, cameraUpdateStarted);
}

// 0x574010
void CMenuManager::SmallMessageScreen(const char* key) {
    plugin::CallMethod<0x574010, CMenuManager*, const char*>(this, key);
}

// 0x575130
void CMenuManager::PrintMap() {
    plugin::CallMethod<0x575130, CMenuManager*>(this);
}

// 0x574900
void CMenuManager::PrintStats() {
    plugin::CallMethod<0x574900, CMenuManager*>(this);
}

// 0x576320
void CMenuManager::PrintBriefs() {
    plugin::CallMethod<0x576320, CMenuManager*>(this);
}

// 0x5746F0
void CMenuManager::PrintRadioStationList() {
    plugin::CallMethod<0x5746F0, CMenuManager*>(this);
}

// 0x57FD70
void CMenuManager::UserInput() {
    plugin::CallMethod<0x57FD70, CMenuManager*>(this);
}

// 0x5773D0
void CMenuManager::AdditionalOptionInput(bool* upPressed, bool* downPressed) {
    plugin::CallMethod<0x5773D0, CMenuManager*, bool*, bool*>(this, upPressed, downPressed);
}

// 0x57E4D0
bool CMenuManager::CheckRedefineControlInput() {
    return plugin::CallMethodAndReturn<bool, 0x57E4D0, CMenuManager*>(this);
}

// 0x57EF50
void CMenuManager::RedefineScreenUserInput(bool* accept, bool* cancel) {
    plugin::CallMethod<0x57EF50, CMenuManager*, bool*, bool*>(this, accept, cancel);
}

// 0x57B440
void CMenuManager::Process() {
    if (m_bMenuActive) {
        ProcessStreaming(m_bAllStreamingStuffLoaded);
        UserInput();
        ProcessFileActions();
        D3DResourceSystem::TidyUpD3DIndexBuffers(1);
        D3DResourceSystem::TidyUpD3DTextures(1);
    }
    CheckForMenuClosing();
}

// 0x573CF0
void CMenuManager::ProcessStreaming(bool streamAll) {
    plugin::CallMethod<0x573CF0, CMenuManager*, bool>(this, streamAll); // TODO: streamAll -> bImmediately?
}

// 0x578D60
void CMenuManager::ProcessFileActions() {
    plugin::CallMethod<0x578D60, CMenuManager*>(this);
}

// 0x57B480
void CMenuManager::ProcessUserInput(bool downPressed, bool upPressed, bool acceptPressed, bool cancelPressed, int8 pressedLR) {
    plugin::CallMethod<0x57B480, CMenuManager*, bool, bool, bool, int8>(this, downPressed, upPressed, acceptPressed, cancelPressed, pressedLR);
}

// 0x576FE0
void CMenuManager::ProcessMenuOptions(int8 pressedLR, bool* cancelPressed, bool acceptPressed) {
    plugin::CallMethod<0x576FE0, CMenuManager*, int8, bool*, bool>(this, pressedLR, cancelPressed, acceptPressed);
}

// 0x57CD50
bool CMenuManager::ProcessPCMenuOptions(int8 a1, uint8 a2) {
    return plugin::CallMethodAndReturn<bool, 0x57CD50, CMenuManager*, int8, uint8>(this, a1, a2);
}

// 0x57D520
void CMenuManager::ProcessMissionPackNewGame() {
    plugin::CallMethod<0x57D520, CMenuManager*>(this);
}