#pragma once

#include "CommandParser/Parser.hpp"
using namespace notsa::script;

/*!
* Various clock commands
*/

/// Get hours and minutes
REGISTER_COMMAND_HANDLER(COMMAND_GET_TIME_OF_DAY, ([]() -> MultiRet<uint8, uint8> { return {CClock::ms_nGameClockHours, CClock::ms_nGameClockMinutes}; }));

REGISTER_COMMAND_HANDLER(COMMAND_SET_TIME_OF_DAY, [](uint8 hours, uint8 minutes) { CClock::SetGameClock(hours, minutes, 0); });

REGISTER_COMMAND_HANDLER(COMMAND_GET_MINUTES_TO_TIME_OF_DAY, [](uint8 hours, uint8 minutes) { return CClock::GetGameClockMinutesUntil(hours, minutes); });

REGISTER_COMMAND_HANDLER(COMMAND_STORE_CLOCK, []() { CClock::StoreClock(); });

REGISTER_COMMAND_HANDLER(COMMAND_RESTORE_CLOCK, []() { CClock::RestoreClock(); });
