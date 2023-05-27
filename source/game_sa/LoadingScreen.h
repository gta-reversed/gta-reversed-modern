/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CSprite2d;

// TODO: Move this to an appropriate place
inline struct FastLoadSettings {
    int32  SaveGameToLoad       = -1;         //< -2 - Don't load, -1 = Load first available, 0 <= - load from save slot
    bool   TriedLoadingSaveGame = false;      //< [Runtime Var] Whenever `SaveGameToLoad` was tried to be loaded
    uint32 SkipSaveGameLoadKey  = VK_CONTROL; //< Skip auto-loading save game (If enabled)
    uint32 SoundDelay           = 50;

    bool  NoEAX            = true;  //< Skip EAX splash
    bool  NoNVidia         = true;  //< Skip nVidia splash
    bool  NoLogo           = true;  //< Skip Logo.mpg
    bool  NoTitleOrIntro   = true;  //< Skip GTAtitles.mpg
    bool  NoCopyright      = true;  //< Skip Copyright screen
    bool  NoFading         = true;  //< Skip fading (takes quite a bit of time)
    bool  NoLoadScreen     = true;  //< Skip load pre-game screen 
    bool  NoLoadBar        = false; //< Skip load bar in pre-game load screen
    bool  NoLoadingTune    = true;  //< Skip GTA theme music
    bool  NoDbgLogScreens  = true;  //< Don't display [notsa] loading screen debug messages to console
    bool  RenderAtAllTimes = true;  //< Render even when minimized
    float ScreenChangeTime = 5.f;   //< Time to change splash screens in the loading screen (seconds?)

    //! If there's a game to load, but not loaded yet...
    bool ShouldLoadSaveGame() const { return SaveGameToLoad >= -1 && !TriedLoadingSaveGame; }

    //! Start the game from a slot
    //! `slot` can have the same values as `SaveGameToLoad`
    bool StartGame(int32 slot) {
        if (slot == -1) { // Find first valid slot and load that
            CFileMgr::SetDirMyDocuments();
            for (auto i = 0u; i < MAX_SAVEGAME_SLOTS; i++) {
                if (std::filesystem::exists(std::format("GTASAsf{}.b", i + 1))) { // Save file IDs start from 1, not 0
                    return StartGame(i); // Load this slot
                }
            }
            CFileMgr::ChangeDir("");
            DEV_LOG("Didn't find any savegame to load!");
            return false;
        }

        // Load game from slot
        assert(slot >= 0);

        DEV_LOG("Loading game from slot ({})", slot);

        if (!NoLoadingTune) {
            for (size_t i = 0; i < SoundDelay; i++) {
                AudioEngine.ServiceLoadingTune(1.f);
            }
        }

        // Actually load the game (By simulating the user going in the menu and doing it)
        FrontEndMenuManager.SimulateGameLoad(false, slot);

        return true;
    }
} FastLoadSettings{};

class CLoadingScreen {
public:
    static constexpr size_t MAX_SPLASHES = 7u;

    static inline char (&m_PopUpMessage)[16] = *(char (*)[16])0xBAB268;
    static inline char (&m_LoadingGxtMsg1)[80] = *(char (*)[80])0xBAB2C8;
    static inline char (&m_LoadingGxtMsg2)[80] = *(char (*)[80])0xBAB278;
    static inline std::array<CSprite2d, MAX_SPLASHES>& m_aSplashes = *(std::array<CSprite2d, MAX_SPLASHES>*)0xBAB35C;

    static inline int32& m_currDisplayedSplash = *(int32*)0x8D093C;
    static inline int32& m_numChunksLoaded = *(int32*)0x8D0940; // -1
    static inline int32& m_chunkBarAppeared = *(int32*)0x8D0944; // -1

    static inline bool& m_bActive = *(bool*)0xBAB318;
    static inline bool& m_bWantToPause = *(bool*)0xBAB319;
    static inline bool& m_bPaused = *(bool*)0xBAB31A;
    static inline bool& m_bFading = *(bool*)0xBAB31C;
    static inline bool& m_bLegalScreen = *(bool*)0xBAB31D;
    static inline bool& m_bFadeInNextSplashFromBlack = *(bool*)0xBAB31E;
    static inline bool& m_bFadeOutCurrSplashToBlack = *(bool*)0xBAB31F;
    static inline bool& m_bReadyToDelete = *(bool*)0xBAB33D;

    static inline uint8& m_FadeAlpha = *(uint8*)0xBAB320;
    static inline float& m_StartFadeTime = *(float*)0xBAB324;
    static inline float& m_ClockTimeOnPause = *(float*)0xBAB328;
    static inline float& m_PauseTime = *(float*)0xBAB32C;

    static inline float& gfLoadingPercentage = *(float*)0xBAB330;
    static inline float& m_TimeBarAppeared = *(float*)0xBAB338;

    static inline float& m_timeSinceLastScreen = *(float*)0xBAB340;

public:
    static void InjectHooks();

    static void Init(bool unusedFlag, bool loaded);
    static void Shutdown();

    static void RenderSplash();
    static void LoadSplashes(bool starting, bool nvidia);
    static void DisplayMessage(const char* message);
    static void SetLoadingBarMsg(const char* msg1, const char* msg2);
    [[nodiscard]] static float GetClockTime(bool ignorePauseTime = true);
    static void Pause();
    static void Continue();
    static void RenderLoadingBar();
    static void inline DisplayNextSplash();
    static void StartFading();
    static void inline DisplayPCScreen();
    static void DoPCTitleFadeOut();
    static void DoPCTitleFadeIn();
    static void DoPCScreenChange(uint32 finish);
    static void NewChunkLoaded();

    static void Update();

    [[nodiscard]] static bool IsActive() { return m_bActive; } // 0x744DB5
    static CSprite2d& GetCurrentDisplayedSplash() { return m_aSplashes[m_currDisplayedSplash]; }

    //! NOTSA - Skips the copyright splash
    static void SkipCopyrightSplash();
};

void LoadingScreen(const char* msg1, const char* msg2 = nullptr, const char* msg3 = nullptr);
