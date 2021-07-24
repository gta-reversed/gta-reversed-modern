#include "StdInc.h"

// 0x8CCF24
unsigned char CClock::daysInMonth[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
// 0xB70144
bool CClock::bClockHasBeenStored;
unsigned short& CClock::ms_Stored_nGameClockSeconds = *reinterpret_cast<unsigned short*>(0xB70148);
unsigned char& CClock::ms_Stored_nGameClockMinutes = *reinterpret_cast<unsigned char*>(0xB7014A);
unsigned char& CClock::ms_Stored_nGameClockHours = *reinterpret_cast<unsigned char*>(0xB7014B);
unsigned char& CClock::ms_Stored_nGameClockDays = *reinterpret_cast<unsigned char*>(0xB7014C);
unsigned char& CClock::ms_Stored_nGameClockMonths = *reinterpret_cast<unsigned char*>(0xB7014D);
unsigned char& CClock::CurrentDay = *reinterpret_cast<unsigned char*>(0xB7014E);
unsigned short& CClock::ms_nGameClockSeconds = *reinterpret_cast<unsigned short*>(0xB70150);
unsigned char& CClock::ms_nGameClockMinutes = *reinterpret_cast<unsigned char*>(0xB70152);
unsigned char& CClock::ms_nGameClockHours = *reinterpret_cast<unsigned char*>(0xB70153);
unsigned char& CClock::ms_nGameClockDays = *reinterpret_cast<unsigned char*>(0xB70154);
unsigned char& CClock::ms_nGameClockMonth = *reinterpret_cast<unsigned char*>(0xB70155);
unsigned int& CClock::ms_nLastClockTick = *reinterpret_cast<unsigned int*>(0xB70158);
unsigned int& CClock::ms_nMillisecondsPerGameMinute = *reinterpret_cast<unsigned int*>(0xB7015C);

void CClock::InjectHooks() {
    ReversibleHooks::Install("CClock", "Initialise", 0x52CD90, &CClock::Initialise);
    ReversibleHooks::Install("CClock", "Update", 0x52CF10, &CClock::Update);
    ReversibleHooks::Install("CClock", "GetGameClockMinutesUntil", 0x52CEB0, &CClock::GetGameClockMinutesUntil);
    ReversibleHooks::Install("CClock", "GetIsTimeInRange", 0x52CEE0, &CClock::GetIsTimeInRange);
//    ReversibleHooks::Install("CClock", "NormaliseGameClock", 0x52CDE0, &CClock::NormaliseGameClock);
    ReversibleHooks::Install("CClock", "OffsetClockByADay", 0x52D0B0, &CClock::OffsetClockByADay);
    ReversibleHooks::Install("CClock", "SetGameClock", 0x52D150, &CClock::SetGameClock);
    ReversibleHooks::Install("CClock", "StoreClock", 0x52D020, &CClock::StoreClock);
    ReversibleHooks::Install("CClock", "RestoreClock", 0x52D070, &CClock::RestoreClock);
}

// Initializes clock
// 0x52CD90
void CClock::Initialise(unsigned int millisecondsPerGameMinute) {
    ms_nMillisecondsPerGameMinute = millisecondsPerGameMinute;
    ms_nGameClockMonth = 1;
    ms_nGameClockDays = 1;
    ms_nLastClockTick = CTimer::m_snTimeInMilliseconds;
    ms_nGameClockHours = 12;
    ms_nGameClockMinutes = 0;
    ms_nGameClockSeconds = 0;
    bClockHasBeenStored = false;
    CurrentDay = 4;
}

// Updates a time
// 0x52CF10
void CClock::Update() {
    ms_nGameClockSeconds = (CTimer::m_snTimeInMilliseconds - ms_nLastClockTick) * 60 / ms_nMillisecondsPerGameMinute;

    if (ms_nMillisecondsPerGameMinute >= (CTimer::m_snTimeInMilliseconds - ms_nLastClockTick) && !CCheat::m_aCheatsActive[CHEAT_FASTER_CLOCK])
        return;

    if (CCheat::m_aCheatsActive[CHEAT_ALWAYS_MIDNIGHT] || CCheat::m_aCheatsActive[CHEAT_STOP_GAME_CLOCK_ORANGE_SKY])
        return;

    // next minute
    ms_nGameClockMinutes++;
    ms_nLastClockTick += ms_nMillisecondsPerGameMinute;

    if (CCheat::m_aCheatsActive[CHEAT_FASTER_CLOCK])
        ms_nLastClockTick = CTimer::m_snTimeInMilliseconds;

    // next hour
    if (ms_nGameClockMinutes <= 59)
        return;

    ms_nGameClockMinutes = 0;
    ms_nGameClockHours++;

    // next day
    if (ms_nGameClockHours <= 23)
        return;

    ms_nGameClockHours = 0;
    ms_nGameClockDays++;

    if (CurrentDay == 7)
        CurrentDay = 1;
    else
        CurrentDay++;

    CStats::IncrementStat(STAT_DAYS_PASSED_IN_GAME, 1.0f);

    // next month
    if (daysInMonth[ms_nGameClockMonth] > ms_nGameClockDays)
        return;

    ms_nGameClockDays = 1;

    if (ms_nGameClockMonth == 12)
        ms_nGameClockMonth = 1;
    else
        ms_nGameClockMonth++;
}

// Returns number of minutes to specified hour & minute.
// 0x52CEB0
unsigned short CClock::GetGameClockMinutesUntil(unsigned char hours, unsigned char minutes) {
    unsigned int now = ms_nGameClockHours * 60 + ms_nGameClockMinutes;
    unsigned int then = hours * 60 + minutes;
    if (then < now) {
        then += 24 * 60; // Add one day
    }
    return then - now;
}

/**
 * Returns true if current hour greater than or equal to *from* and less than *to*.
 * ms_nGameClockHours ∈ [h1, h2)
 * @address 0x52CEE0
 */
bool CClock::GetIsTimeInRange(unsigned char from, unsigned char to) {
    if (from > to)
        return ms_nGameClockHours >= from || ms_nGameClockHours < to;
    else
        return ms_nGameClockHours >= from && ms_nGameClockHours < to;
}

// Normalizes game clock
// For example hour of 24 means new day and hour 1.
// 0x52CDE0
void CClock::NormaliseGameClock() {
    plugin::CallDynGlobal<>(0x52CDE0);
}

// Sets new day
// Directions (0 = one day backwards, 1 = one day forwards)
// 0x52D0B0
void CClock::OffsetClockByADay(unsigned int timeDirection) {
    if (timeDirection == 0) {
        ms_nGameClockDays--;

        if (ms_nGameClockDays == 0) {
            ms_nGameClockMonth--;

            if (ms_nGameClockMonth == 0)
                ms_nGameClockMonth = 12;

            ms_nGameClockDays = daysInMonth[ms_nGameClockMonth];
        }
        CurrentDay--;

        if (CurrentDay == 0)
            CurrentDay = 7;
    }
    else {
        ms_nGameClockDays++;

        if (daysInMonth[ms_nGameClockMonth] < ms_nGameClockDays) {
            ms_nGameClockMonth++;
            ms_nGameClockDays = 1;

            if (ms_nGameClockMonth > 12)
                ms_nGameClockMonth = 1;
        }

        CurrentDay++;

        if (CurrentDay > 7) {
            CurrentDay = 1;
            return;
        }
    }
}

// Sets game clock
// 0x52D150
void CClock::SetGameClock(unsigned char hours, unsigned char minutes, unsigned char day) {
    ms_nLastClockTick = CTimer::m_snTimeInMilliseconds;
    ms_nGameClockHours = hours;
    ms_nGameClockMinutes = minutes;

    if (day) {
        CurrentDay = day;
        ++ms_nGameClockDays;
    }

    ms_nGameClockSeconds = 0;
    NormaliseGameClock();
}

// Backups a clock time
// 0x52D020
void CClock::StoreClock() {
    ms_Stored_nGameClockMonths = ms_nGameClockMonth;
    ms_Stored_nGameClockDays = ms_nGameClockDays;
    ms_Stored_nGameClockHours = ms_nGameClockHours;
    ms_Stored_nGameClockMinutes = ms_nGameClockMinutes;
    ms_Stored_nGameClockSeconds = ms_nGameClockSeconds;
    bClockHasBeenStored = true;
}

// Restores a clock time
// 0x52D070
void CClock::RestoreClock() {
    ms_nGameClockMonth = ms_Stored_nGameClockMonths;
    ms_nGameClockDays = ms_Stored_nGameClockDays;
    ms_nGameClockHours = ms_Stored_nGameClockHours;
    ms_nGameClockMinutes = ms_Stored_nGameClockMinutes;
    ms_nGameClockSeconds = ms_Stored_nGameClockSeconds;
}
