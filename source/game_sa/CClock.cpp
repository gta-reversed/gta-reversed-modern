#include "StdInc.h"

unsigned char (&CClock::daysInMonth)[12] = *reinterpret_cast<unsigned char (*)[12]>(0x8CCF24);
bool& CClock::bClockHasBeenStored = *reinterpret_cast<bool*>(0xB70144);
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
//    ReversibleHooks::Install("CClock", "Update", 0x52CF10, &CClock::Update);
//    ReversibleHooks::Install("CClock", "GetGameClockMinutesUntil", 0x52CEB0, &CClock::GetGameClockMinutesUntil);
//    ReversibleHooks::Install("CClock", "GetIsTimeInRange", 0x52CEE0, &CClock::GetIsTimeInRange);
//    ReversibleHooks::Install("CClock", "NormaliseGameClock", 0x52CDE0, &CClock::NormaliseGameClock);
//    ReversibleHooks::Install("CClock", "OffsetClockByADay", 0x52D0B0, &CClock::OffsetClockByADay);
    ReversibleHooks::Install("CClock", "SetGameClock", 0x52D150, &CClock::SetGameClock);
    ReversibleHooks::Install("CClock", "StoreClock", 0x52D020, &CClock::StoreClock);
    ReversibleHooks::Install("CClock", "RestoreClock", 0x52D070, &CClock::RestoreClock);
}

// Initializes clock
// 0x52CD90
void CClock::Initialise(unsigned int millisecondsPerGameMinute) {
    CClock::ms_nMillisecondsPerGameMinute = millisecondsPerGameMinute;
    CClock::ms_nGameClockMonth = 1;
    CClock::ms_nGameClockDays = 1;
    CClock::ms_nLastClockTick = CTimer::m_snTimeInMilliseconds;
    CClock::ms_nGameClockHours = 12;
    CClock::ms_nGameClockMinutes = 0;
    CClock::ms_nGameClockSeconds = 0;
    CClock::bClockHasBeenStored = false;
    CClock::CurrentDay = 4;
}

// Updates a time
// 0x52CF10
void CClock::Update() {
    plugin::CallDynGlobal<>(0x52CF10);
}

// Returns number of minutes to specified hour & minute.
// 0x52CEB0
unsigned short CClock::GetGameClockMinutesUntil(unsigned char hours, unsigned char minutes) {
    return plugin::CallAndReturnDynGlobal<unsigned short, unsigned char, unsigned char>(0x52CEB0, hours, minutes);
}

// Returns true current hour is in range of two specified hours.
// 0x52CEE0
bool CClock::GetIsTimeInRange(unsigned char hourA, unsigned char hourB) {
    return plugin::CallAndReturnDynGlobal<bool, unsigned char, unsigned char>(0x52CEE0, hourA, hourB);
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
    plugin::CallDynGlobal<unsigned int>(0x52D0B0, timeDirection);
}

// Sets game clock
// 0x52D150
void CClock::SetGameClock(unsigned char hours, unsigned char minutes, unsigned char day) {
    CClock::ms_nLastClockTick = CTimer::m_snTimeInMilliseconds;
    CClock::ms_nGameClockHours = hours;
    CClock::ms_nGameClockMinutes = minutes;
    if (day) {
        CClock::CurrentDay = day;
        ++CClock::ms_nGameClockDays;
    }
    CClock::ms_nGameClockSeconds = 0;
    CClock::NormaliseGameClock();
}

// Backups a clock time
// 0x52D020
void CClock::StoreClock() {
    CClock::ms_Stored_nGameClockMonths = CClock::ms_nGameClockMonth;
    CClock::ms_Stored_nGameClockDays = CClock::ms_nGameClockDays;
    CClock::ms_Stored_nGameClockHours = CClock::ms_nGameClockHours;
    CClock::ms_Stored_nGameClockMinutes = CClock::ms_nGameClockMinutes;
    CClock::ms_Stored_nGameClockSeconds = CClock::ms_nGameClockSeconds;
    CClock::bClockHasBeenStored = true;
}

// Restores a clock time
// 0x52D070
void CClock::RestoreClock() {
    CClock::ms_nGameClockMonth = CClock::ms_Stored_nGameClockMonths;
    CClock::ms_nGameClockDays = CClock::ms_Stored_nGameClockDays;
    CClock::ms_nGameClockHours = CClock::ms_Stored_nGameClockHours;
    CClock::ms_nGameClockMinutes = CClock::ms_Stored_nGameClockMinutes;
    CClock::ms_nGameClockSeconds = CClock::ms_Stored_nGameClockSeconds;
}
