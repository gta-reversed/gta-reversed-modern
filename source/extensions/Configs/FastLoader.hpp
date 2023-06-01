#pragma once
#include <cassert>
#include "app_debug.h"
#include "AudioEngine.h"
#include "Common.h"
#include "FileMgr.h"
#include "GenericGameStorage.h"
#include "MenuManager.h"

#include "extensions/Configuration.hpp"

inline struct {
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

    void Load() {
        GET_INI_CONFIG_VALUE("FastLoader", SaveGameToLoad, -1);
        GET_INI_CONFIG_VALUE("FastLoader", SkipSaveGameLoadKey, false);
        GET_INI_CONFIG_VALUE("FastLoader", SoundDelay, 50);

        GET_INI_CONFIG_VALUE("FastLoader", NoEAX, true);
        GET_INI_CONFIG_VALUE("FastLoader", NoNVidia, true);
        GET_INI_CONFIG_VALUE("FastLoader", NoLogo, true);
        GET_INI_CONFIG_VALUE("FastLoader", NoTitleOrIntro, true);
        GET_INI_CONFIG_VALUE("FastLoader", NoCopyright, true);
        GET_INI_CONFIG_VALUE("FastLoader", NoFading, true);
        GET_INI_CONFIG_VALUE("FastLoader", NoLoadScreen, true);
        GET_INI_CONFIG_VALUE("FastLoader", NoLoadBar, false);
        GET_INI_CONFIG_VALUE("FastLoader", NoLoadingTune, true);
        GET_INI_CONFIG_VALUE("FastLoader", NoDbgLogScreens, true);
        GET_INI_CONFIG_VALUE("FastLoader", RenderAtAllTimes, true);
        GET_INI_CONFIG_VALUE("FastLoader", ScreenChangeTime, 5.f);
    }

    void Save() {
        SAVE_INI_CONFIG_VALUE("FastLoader", SaveGameToLoad);
        SAVE_INI_CONFIG_VALUE("FastLoader", SkipSaveGameLoadKey);
        SAVE_INI_CONFIG_VALUE("FastLoader", SoundDelay);

        SAVE_INI_CONFIG_VALUE("FastLoader", NoEAX);
        SAVE_INI_CONFIG_VALUE("FastLoader", NoNVidia);
        SAVE_INI_CONFIG_VALUE("FastLoader", NoLogo);
        SAVE_INI_CONFIG_VALUE("FastLoader", NoTitleOrIntro);
        SAVE_INI_CONFIG_VALUE("FastLoader", NoCopyright);
        SAVE_INI_CONFIG_VALUE("FastLoader", NoFading);
        SAVE_INI_CONFIG_VALUE("FastLoader", NoLoadScreen);
        SAVE_INI_CONFIG_VALUE("FastLoader", NoLoadBar);
        SAVE_INI_CONFIG_VALUE("FastLoader", NoLoadingTune);
        SAVE_INI_CONFIG_VALUE("FastLoader", NoDbgLogScreens);
        SAVE_INI_CONFIG_VALUE("FastLoader", RenderAtAllTimes);
        SAVE_INI_CONFIG_VALUE("FastLoader", ScreenChangeTime);
    }
} g_FastLoaderConfiguration{};
