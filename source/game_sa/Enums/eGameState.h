#pragma once

enum eGameState : uint8 {
    GAME_STATE_INITIAL          = 0, // EAX / NVIDIA splashes
    GAME_STATE_LOGO             = 1, // Playing Logo.mpg (possibly incorrect)
    GAME_STATE_PLAYING_LOGO     = 2, // Init pads
    GAME_STATE_TITLE            = 3, // STATE_INIT_INTRO Playing GTAtitles.mpg
    GAME_STATE_PLAYING_INTRO    = 4, // Init pads (same state as 2)
    GAME_STATE_FRONTEND_LOADING = 5, // Start game loading (showing title splash)
    GAME_STATE_FRONTEND_LOADED  = 6, // End loading
    GAME_STATE_FRONTEND_IDLE    = 7, // Frontend menu (loop state)
    GAME_STATE_LOADING_STARTED  = 8, // STATE_GAME_LOADING Loading the game
    GAME_STATE_IDLE             = 9, // In-game (loop state)
};
