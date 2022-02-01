/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "OnscreenTimerEntry.h"
#include "OnscreenCounterEntry.h"

class COnscreenTimer {
public:
    COnscreenTimerEntry   m_Clock;
    COnscreenCounterEntry m_aCounters[4];
    bool                  m_bDisplay;
    bool                  m_bPaused;

public:
    void AddClock(uint32 varId, char* gxt, bool bTimerDirection);
    void AddCounter(int32 varId, int16 type, char* gxt, uint16 counterIndex);
    //! unused
    void  AddCounterCounter(uint32 varId, uint32 maxValue, char* gxt, uint16 lineId);
    int32 ClearClock(uint32 varId);
    void  ClearCounter(uint32 varId);
    void  Init();
    void  Process();
    void  ProcessForDisplay();
    void  SetClockBeepCountdownSecs(uint32 varID, uint32 time);
    //! unused
    void SetCounterColourID(uint32 varID, uint8 ColourID);
    void SetCounterFlashWhenFirstDisplayed(uint32 varId, uint8 bFlashWhenFirstDisplayed);
};
VALIDATE_SIZE(COnscreenTimer, 0x154);
