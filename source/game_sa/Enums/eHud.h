#pragma once

enum eMessageStyle : uint16 {
    STYLE_MIDDLE,                // In The Middle
    STYLE_BOTTOM_RIGHT,          // At The Bottom Right
    STYLE_WHITE_MIDDLE,          // White Text In The Middle
    STYLE_MIDDLE_SMALLER,        // In The Middle Smaller
    STYLE_MIDDLE_SMALLER_HIGHER, // In The Middle Smaller A Bit Higher On The Screen
    STYLE_WHITE_MIDDLE_SMALLER,  // Small White Text In The Middle Of The Screen
    STYLE_LIGHT_BLUE_TOP,        // Light Blue Text On Top Of The Screen

    NUM_MESSAGE_STYLES
};

enum eHudItem : int16 {
    ITEM_NONE   = -1,
    ITEM_ARMOUR =  3,
    ITEM_HEALTH =  4,
    ITEM_RADAR  =  8,
    ITEM_BREATH = 10,
};

enum DRAW_FADE_STATE {
    WANTED_STATE        = 0,
    ENERGY_LOST_STATE   = 1,
    DISPLAY_SCORE_STATE = 2,
    WEAPON_STATE        = 3,
};

enum eFadeOperation {
    FADED_OUT = 0,
    START_FADE_OUT,
    FADING_IN,
    FADING_OUT,
    FADE_DISABLED = 5,
};

enum eNameState {
    NAME_DONT_SHOW = 0,
    NAME_SHOW      = 1,
    NAME_FADE_IN   = 2,
    NAME_FADE_OUT  = 3,
    NAME_SWITCH    = 4,
};

enum eHudSprite {
    SPRITE_FIST,
    SPRITE_SITE_M16,
    SPRITE_SITE_ROCKET,
    SPRITE_RADAR_DISC,
    SPRITE_RADAR_RING_PLANE,
    SPRITE_SKIP_ICON,

    NUM_HUD_SPRITES
};
