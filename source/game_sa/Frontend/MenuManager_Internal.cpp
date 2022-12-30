#include "StdInc.h"

#include "MenuManager_Internal.h"

// 0x8CDF28
SpriteFileName FrontEndFilenames[] = {
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

#if defined BUILD_PC
    #include "FrontendScreensPC.h"
#elif defined BUILD_XBOX
    #include "config/FrontendScreensXBOX.def"
#elif defined BUILD_PS2
    #include "config/FrontendScreensPS2.def"
#endif
