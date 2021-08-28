/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CClock {
public:
    static uint8_t daysInMonth[12];
    static bool& bClockHasBeenStored;
    static uint16_t& ms_Stored_nGameClockSeconds;
    static uint8_t& ms_Stored_nGameClockMinutes;
    static uint8_t& ms_Stored_nGameClockHours;
    static uint8_t& ms_Stored_nGameClockDays;
    static uint8_t& ms_Stored_nGameClockMonths;
    static uint8_t& CurrentDay;
    static uint16_t& ms_nGameClockSeconds;
    static uint8_t& ms_nGameClockMinutes;
    static uint8_t& ms_nGameClockHours;
    static uint8_t& ms_nGameClockDays;
    static uint8_t& ms_nGameClockMonth;
    static uint32_t& ms_nLastClockTick;
    static uint32_t& ms_nMillisecondsPerGameMinute;

public:
    static void InjectHooks();

    static void Initialise(uint32_t millisecondsPerGameMinute);
    static void Update();

    static uint16_t GetGameClockMinutesUntil(uint8_t hours, uint8_t minutes);
    static bool GetIsTimeInRange(uint8_t from, uint8_t to);
    static void NormaliseGameClock();
    static void OffsetClockByADay(uint32_t timeDirection);
    static void SetGameClock(uint8_t hours, uint8_t minutes, uint8_t day);
    static void StoreClock();
    static void RestoreClock();
};
