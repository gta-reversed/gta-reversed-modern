/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CClock {
public:
    static unsigned char (&daysInMonth)[12]; // static unsigned char const daysInMonth[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    static bool& bClockHasBeenStored;
    static unsigned short& ms_Stored_nGameClockSeconds;
    static unsigned char& ms_Stored_nGameClockMinutes;
    static unsigned char& ms_Stored_nGameClockHours;
    static unsigned char& ms_Stored_nGameClockDays;
    static unsigned char& ms_Stored_nGameClockMonths;
    static unsigned char& CurrentDay;
    static unsigned short& ms_nGameClockSeconds;
    static unsigned char& ms_nGameClockMinutes;
    static unsigned char& ms_nGameClockHours;
    static unsigned char& ms_nGameClockDays;
    static unsigned char& ms_nGameClockMonth;
    static unsigned int& ms_nLastClockTick;
    static unsigned int& ms_nMillisecondsPerGameMinute;

public:
    static void InjectHooks();

    static void Initialise(unsigned int millisecondsPerGameMinute);
    static void Update();

    static unsigned short GetGameClockMinutesUntil(unsigned char hours, unsigned char minutes);
    static bool GetIsTimeInRange(unsigned char hourA, unsigned char hourB);
    static void NormaliseGameClock();
    static void OffsetClockByADay(unsigned int timeDirection);
    static void SetGameClock(unsigned char hours, unsigned char minutes, unsigned char day);
    static void StoreClock();
    static void RestoreClock();
};

//#include "meta/meta.CClock.h"
