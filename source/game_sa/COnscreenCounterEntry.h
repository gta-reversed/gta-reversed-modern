/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class  COnscreenCounterEntry {
public:
    unsigned int   m_nVarId;
    unsigned int   m_nMaxVarValue;
    char           m_szDescriptionTextKey[10];
    unsigned short m_nType;                     // 0 - counter (%), 1 - line, 2 - conter counter (%/%)
    char           m_szDisplayedText[42];       // possibly 2b padding?
    bool           m_bEnabled;
    bool           m_bFlashWhenFirstDisplayed;
    unsigned char  m_nColourId;                 // color index from HudColours

public:
    static void InjectHooks();

    //! unused
    void ProcessForDisplayCounter(uint16_t type);
    //! unused
    void SetColourID(uint8_t a2);
};
VALIDATE_SIZE(COnscreenCounterEntry, 0x44);
