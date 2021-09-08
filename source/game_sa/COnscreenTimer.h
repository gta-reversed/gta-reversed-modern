/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "COnscreenTimerEntry.h"
#include "COnscreenCounterEntry.h"

#include "CHudColours.h"
#include "eOnscreenCounter.h"

class COnscreenTimer {
public:
    COnscreenTimerEntry   m_Clock;
    COnscreenCounterEntry m_aCounters[4];
    bool                  m_bDisplay;
    bool                  m_bPaused;

public:
    static void InjectHooks();

    void Init();

#if ANDROID
    void Load();
    void Save();
#endif

    void AddClock(uint32 varId, char* gxt, eTimerDirection nTimerDirection);
    void ClearClock(uint32 varId);
    void SetClockBeepCountdownSecs(uint32 varId, uint32 time);

    void AddCounter(uint32 varId, eOnscreenCounter type, char* gxt, uint16 counterIndex);
    void AddCounterCounter(uint32 varId, uint32 maxValue, char* gxt, uint16 lineId);
    void ClearCounter(uint32 varId);
    void SetCounterColourID(uint32 varId, eHudColours colorId);
    void SetCounterFlashWhenFirstDisplayed(uint32 varId, bool bFlashWhenFirstDisplayed);

    void Process();
    void ProcessForDisplay();
};

VALIDATE_SIZE(COnscreenTimer, 0x154);
