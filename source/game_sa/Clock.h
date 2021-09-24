/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CClock {
public:
    static uint8 daysInMonth[12];
    static bool& bClockHasBeenStored;
    static uint16& ms_Stored_nGameClockSeconds;
    static uint8& ms_Stored_nGameClockMinutes;
    static uint8& ms_Stored_nGameClockHours;
    static uint8& ms_Stored_nGameClockDays;
    static uint8& ms_Stored_nGameClockMonths;
    static uint8& CurrentDay;
    static uint16& ms_nGameClockSeconds;
    static uint8& ms_nGameClockMinutes;
    static uint8& ms_nGameClockHours;
    static uint8& ms_nGameClockDays;
    static uint8& ms_nGameClockMonth;
    static uint32& ms_nLastClockTick;
    static uint32& ms_nMillisecondsPerGameMinute;

public:
    static void InjectHooks();

    static void Initialise(uint32 millisecondsPerGameMinute);
    static void Update();

    static uint16 GetGameClockMinutesUntil(uint8 hours, uint8 minutes);
    static bool GetIsTimeInRange(uint8 from, uint8 to);
    static void NormaliseGameClock();
    static void OffsetClockByADay(uint32 timeDirection);
    static void SetGameClock(uint8 hours, uint8 minutes, uint8 day);
    static void StoreClock();
    static void RestoreClock();

    // NOTSA
    static uint32 GetMinutesToday();
};
