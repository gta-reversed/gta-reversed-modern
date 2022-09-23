#pragma once

#include "CommandParser/Parser.hpp"
using namespace notsa::script;

/*!
* Various clock commands
*/

/// Get hours and minutes
MultiRet<uint8, uint8> GetTimeOfDay() {
    return { CClock::ms_nGameClockHours, CClock::ms_nGameClockMinutes };
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_TIME_OF_DAY, GetTimeOfDay);

void SetTimeOfDay(uint8 hours, uint8 minutes) {
    CClock::SetGameClock(hours, minutes, 0);
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_TIME_OF_DAY, SetTimeOfDay);

uint16 GetMinutesToTimeOfDay(uint8 hours, uint8 minutes) {
    return CClock::GetGameClockMinutesUntil(hours, minutes);
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_MINUTES_TO_TIME_OF_DAY, GetMinutesToTimeOfDay);

void StoreClock() {
    CClock::StoreClock();
}
REGISTER_COMMAND_HANDLER(COMMAND_STORE_CLOCK, StoreClock);

void RestoreClock() {
    CClock::RestoreClock();
}
REGISTER_COMMAND_HANDLER(COMMAND_RESTORE_CLOCK, RestoreClock);
