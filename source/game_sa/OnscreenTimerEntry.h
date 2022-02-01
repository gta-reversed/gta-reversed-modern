/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class COnscreenTimerEntry {
public:
    uint32 m_nVarId;
    char   m_szDescriptionTextKey[10];
    char   m_szDisplayedText[42]; // possibly 2b padding?
    bool   m_bEnabled;
    uint8  m_nTimerDirection;
    uint32 m_nClockBeepCountdownSecs;

    void Process();
    //! unused
    void ProcessForDisplayClock();
};
VALIDATE_SIZE(COnscreenTimerEntry, 0x40);
