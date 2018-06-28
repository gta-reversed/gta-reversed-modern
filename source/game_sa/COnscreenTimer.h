/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "COnscreenTimerEntry.h"
#include "COnscreenCounterEntry.h"

class  COnscreenTimer {
public:
	COnscreenTimerEntry m_Clock;
	COnscreenCounterEntry m_aCounters[4];
	bool m_bDisplay;
	bool m_bPaused;

     void AddClock(unsigned int varId, char *gxt, bool bTimerDirection);
     void AddCounter(int varId, short type, char *gxt, unsigned short counterIndex);
    //! unused
     void AddCounterCounter(unsigned int varId, unsigned int maxValue, char *gxt, unsigned short lineId);
     int ClearClock(unsigned int varId);
     void ClearCounter(unsigned int varId);
     void Init();
     void Process();
     void ProcessForDisplay();
     void SetClockBeepCountdownSecs(unsigned int varID, unsigned int time);
    //! unused
     void SetCounterColourID(unsigned int varID, unsigned char ColourID);
     void SetCounterFlashWhenFirstDisplayed(unsigned int varId, unsigned char bFlashWhenFirstDisplayed);
};
VALIDATE_SIZE(COnscreenTimer, 0x154);

//#include "meta/meta.COnscreenTimer.h"

