#pragma once
#include <cassert>
#include "app_debug.h"
#include "AudioEngine.h"
#include "Common.h"
#include "FileMgr.h"
#include "GenericGameStorage.h"
#include "MenuManager.h"

#include "extensions/Configuration.hpp"

inline struct FastLoaderConfig {
    bool TriedLoadingSaveGame = false; //< [Runtime Var] Whenever `SaveGameToLoad` was tried to be loaded

    INI_CONFIG_SECTION("FastLoader");

    int32  SaveGameToLoad       = -2;         //< -2 - Don't load, -1 = Load first available, 0 <= - load from save slot
    uint32 SkipSaveGameLoadKey  = VK_CONTROL; //< Skip auto-loading save game (If enabled)
    uint32 SoundDelay           = 50;

    bool  NoEAX            = false; //< Skip EAX splash
    bool  NoNVidia         = false; //< Skip nVidia splash
    bool  NoLogo           = false; //< Skip Logo.mpg
    bool  NoTitleOrIntro   = false; //< Skip GTAtitles.mpg
    bool  NoCopyright      = false; //< Skip Copyright screen
    bool  NoFading         = false; //< Skip fading (takes quite a bit of time)
    bool  NoLoadScreen     = false; //< Skip load pre-game screen 
    bool  NoLoadBar        = false; //< Skip load bar in pre-game load screen
    bool  NoLoadingTune    = false; //< Skip GTA theme music
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

    void Load() {
#ifdef EXT_FAST_LOADER
        GET_INI_CONFIG_VALUE(SaveGameToLoad, -1);
        GET_INI_CONFIG_VALUE(SkipSaveGameLoadKey, false);
        GET_INI_CONFIG_VALUE(SoundDelay, 50);

        GET_INI_CONFIG_VALUE(NoEAX, true);
        GET_INI_CONFIG_VALUE(NoNVidia, true);
        GET_INI_CONFIG_VALUE(NoLogo, true);
        GET_INI_CONFIG_VALUE(NoTitleOrIntro, true);
        GET_INI_CONFIG_VALUE(NoCopyright, true);
        GET_INI_CONFIG_VALUE(NoFading, true);
        GET_INI_CONFIG_VALUE(NoLoadScreen, true);
        GET_INI_CONFIG_VALUE(NoLoadBar, false);
        GET_INI_CONFIG_VALUE(NoLoadingTune, true);
        GET_INI_CONFIG_VALUE(NoDbgLogScreens, true);
        GET_INI_CONFIG_VALUE(RenderAtAllTimes, true);
        GET_INI_CONFIG_VALUE(ScreenChangeTime, 5.f);
#endif
    }
} g_FastLoaderConfig{};
